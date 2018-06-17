/************************************************************************
**
**  Copyright (C) 2017  spdevapp  <spdevapp@joara.com>
**
**  This file is part of Viewporter.
**
*************************************************************************/

#include <QtCore/QCryptographicHash>
#include <QtCore/QtGlobal>
#include <QtNetwork/QNetworkInterface>
#include <QtWidgets/QApplication>

#include "LimitDate.h"
#include "SettingData.h"

#include "TinyAES.h"
//#include "vpeditor_constants.h"

const QString SETTINGS_GROUP = "limitdate";

const int EXPIRED_YEAR = 2018;
const int EXPIRED_MONTH = 06;
const int EXPIRED_DAY = 30;

const int KEY_SIZE = 16;      // 16 : 128, 24 : 192, 32 : 256
const QString JOARA_KEY = "spdevapp";

LimitDate::LimitDate(QObject *parent) : 
	QObject(parent)
{
	m_ExpiredDate = QDate(EXPIRED_YEAR, EXPIRED_MONTH, EXPIRED_DAY);
	m_LastExecuteDate = QDate::currentDate();

	QApplication::setOverrideCursor(Qt::WaitCursor);
	ReadSettings();
	QApplication::restoreOverrideCursor();
}

LimitDate::~LimitDate()
{
	WriteSettings();
}

void LimitDate::ReadSettings()
{
	SettingData settings;
	settings.beginGroup(SETTINGS_GROUP);

	QByteArray temp;

	// expired_date
	//temp = settings.value("expired_date").toByteArray();
	//if (temp.isEmpty()) {
	//	m_ExpiredDate = QDate(EXPIRED_YEAR, EXPIRED_MONTH, EXPIRED_DAY);
	//}
	//else {
	//	m_ExpiredDate = DecryptDate(temp);
	//}
	// last_execute_date
	temp = settings.value("last_execute_date").toByteArray();
	if (temp.isEmpty()) {
		m_LastExecuteDate = QDate::currentDate();
	}
	else {
		m_LastExecuteDate = DecryptDate(temp);
	}

	settings.endGroup();
}

void LimitDate::WriteSettings()
{
	SettingData settings;
	settings.beginGroup(SETTINGS_GROUP);

	TinyAES aes;
	QByteArray encrypt;
	
	//if (m_ExpiredDate.toJulianDay() != 0 && m_ExpiredDate.isValid()) {
	//	encrypt = EncryptDate(m_ExpiredDate);
	//	settings.setValue("expired_date", encrypt);
	//}

	if (m_LastExecuteDate.toJulianDay() != 0 && m_LastExecuteDate.isValid()) {
		encrypt = EncryptDate(m_LastExecuteDate);
		settings.setValue("last_execute_date", encrypt);
	}

	settings.endGroup();
}

QDate LimitDate::DecryptDate(QByteArray data)
{
	TinyAES aes;
	QByteArray temp = aes.Decrypt(data, GetKey());
	QDate date = QDate::fromJulianDay(temp.toLongLong());
	qDebug() << "Before Decrypt Date is =>" << data;
	qDebug() << "After Decrypt String is =>" << temp;
	qDebug() << "After Decrypt Date is =>" << date;

	return date;
}

QByteArray LimitDate::EncryptDate(QDate date)
{
	TinyAES aes;
	QString temp = QString::number(date.toJulianDay());
	QByteArray encrypt = aes.Encrypt(temp.toLatin1(), GetKey());
	qDebug() << "Before Encrypt Date is =>" << date;
	qDebug() << "Before Encrypt String is =>" << temp;
	qDebug() << "After Encrypt Date is =>" << encrypt;

	return encrypt;
}

QByteArray LimitDate::GetKey()
{
	QString address = JOARA_KEY;
	QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
	foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces()) {
		if (!netInterface.hardwareAddress().isEmpty()) {
			address += ";" + netInterface.hardwareAddress();
		}
	}
	QByteArray retKey = QCryptographicHash::hash(address.toUtf8(), QCryptographicHash::Md5);
	retKey.resize(KEY_SIZE);
	qDebug() << "Key is =>" << retKey;
	return retKey;
}

//QString LimitDate::GetMacAddress()
//{
//	foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces()) {
//		// Return only the first non-loopback MAC Address
//		if (!(netInterface.flags() & QNetworkInterface::IsLoopBack))
//			return netInterface.hardwareAddress();
//	}
//	return QString();
//}


bool LimitDate::CheckExpiredDate()
{
	bool bExpired = false;
	QDate cDate = QDate::currentDate();

	qDebug() << "**************************************";
	qDebug() << "Expire  => " << m_ExpiredDate.day() << "." << m_ExpiredDate.month() << "." << m_ExpiredDate.year();
	qDebug() << "Excute  => " << m_LastExecuteDate.day() << "." << m_LastExecuteDate.month() << "." << m_LastExecuteDate.year();
	qDebug() << "Current => " << cDate.day() << "." << cDate.month() << "." << cDate.year();

	if (m_ExpiredDate.toJulianDay() == 0 || m_LastExecuteDate.toJulianDay() == 0) {
		bExpired = true;
		qDebug() << "Function is " << (bExpired ? "Expired." : "not Expired.");
		qDebug() << "**************************************";
		return bExpired;
	}

	if (cDate < m_LastExecuteDate || m_ExpiredDate < cDate) {
		bExpired = true;
	}

	qDebug() << "Function is " << (bExpired ? "Expired." : "not Expired.");
	qDebug() << "**************************************";

	m_LastExecuteDate = qMax(cDate, m_LastExecuteDate);

	return bExpired;
}

QDate LimitDate::GetExpiredDate()
{
	QDate date;
	if (m_ExpiredDate.toJulianDay() == 0) {
		date = QDate(EXPIRED_YEAR, EXPIRED_MONTH, EXPIRED_DAY);
	}
	else {
		date = m_ExpiredDate;
	}

	return date;
}

