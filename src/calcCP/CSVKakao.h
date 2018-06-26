/************************************************************************
**
**  Copyright (C) 2018  spdevapp <spdevapp@joara.com>
**
**  This file is part of Gemini.
**
**  Gemini is Joara CSV Calculator.
**
*************************************************************************/

#pragma once
#ifndef CSV_KAKAO_H
#define CSV_KAKAO_H

#include <QtCore/QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QtWidgets/QTableView>

class CSVKakao : public QObject
{
	Q_OBJECT

public:

	enum HEADER_KAKAO_TYPE {
		HEADER_KAKAO_MONTH = 0,
		HEADER_KAKAO_SERIES_ID,
		HEADER_KAKAO_SERIES_NAME,
		HEADER_KAKAO_AUTHOR,
		HEADER_KAKAO_TICKET,
		HEADER_KAKAO_PAYMENT,
		HEADER_KAKAO_TICKET_USE_COUNT,
		HEADER_KAKAO_PURCHASE_TYPE,
		HEADER_KAKAO_SALE_CASH,
		HEADER_KAKAO_ONE_CASH,
		HEADER_KAKAO_EXCHANGE_RATE,
		HEADER_KAKAO_SALE_TOTAL,
		HEADER_KAKAO_SALE_SUPPLY,
		HEADER_KAKAO_SALE_VAT,
		HEADER_KAKAO_APPLE_FEE,
		HEADER_KAKAO_OPERATING_FEE_TOTAL,
		HEADER_KAKAO_OPERATING_FEE_SUPPLY,
		HEADER_KAKAO_OPERATING_FEE_VAT,
		HEADER_KAKAO_CALCULATE,
		HEADER_KAKAO_MAX
	};

	/**
	* Constructor.
	*/
	CSVKakao();
	~CSVKakao();

	bool ReadFile(QString filepath);

	void SetItem();
	QStandardItemModel* GetItem();

	double GetTotalAmount() { return m_TotalAmount; };
	double GetCalcAmount() { return m_CalcAmount; };
	double GetAuthorAmount() { return m_AuthorAmount; };

private slots:


private:



	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////
	QList<QStringList> m_CSVData;
	QStandardItemModel *m_CSVModel;

	QStringList		m_CSVHeader;

	double			m_TotalAmount;
	double			m_CalcAmount;
	double			m_AuthorAmount;


};

#endif // CSV_KAKAO_H
