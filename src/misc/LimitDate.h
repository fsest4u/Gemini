/************************************************************************
**
**  Copyright (C) 2017  spdevapp  <spdevapp@joara.com>
**
**  This file is part of Viewporter.
**
*************************************************************************/

#pragma once
#ifndef LIMIT_DATE_H
#define LIMIT_DATE_H

#include <QtCore/QObject>
#include <QtCore/QDate>
#include <QHostAddress>

/**
 * limit date for function (joara)
 */
class LimitDate : public QObject
{
    Q_OBJECT

public:

    /**
     * Constructor.
     */
	LimitDate(QObject *parent = 0);
	~LimitDate();

	bool CheckExpiredDate();
	QDate GetExpiredDate();

private slots:


private:


	void ReadSettings();
	void WriteSettings();

	QByteArray GetKey();
	//QString GetMacAddress();

	QDate DecryptDate(QByteArray data);
	QByteArray EncryptDate(QDate date);

	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////

	// last date application executed
	QDate	m_LastExecuteDate;

	// expired date for application
	QDate	m_ExpiredDate;




};

#endif // LIMIT_DATE_H


