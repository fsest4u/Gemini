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
#ifndef CSV_KYOBO_H
#define CSV_KYOBO_H

#include <QtCore/QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QtWidgets/QTableView>

class CSVKyobo : public QObject
{
	Q_OBJECT

public:

	enum HEADER_KYOBO_TYPE {
		HEADER_KYOBO_BUSINESS_TYPE = 0,
		HEADER_KYOBO_PURCHASE_TYPE,
		HEADER_KYOBO_PRODUCT_TYPE,
		HEADER_KYOBO_CLASSIFICATION,
		HEADER_KYOBO_ISBN,
		HEADER_KYOBO_TITLE,
		HEADER_KYOBO_SERIES_NUMBER,
		HEADER_KYOBO_AUTHOR,
		HEADER_KYOBO_PRICE,
		HEADER_KYOBO_SALE_PRICE,
		HEADER_KYOBO_COUNT,
		HEADER_KYOBO_DOWNLOAD_COUNT,
		HEADER_KYOBO_SALE_AMOUNT,
		HEADER_KYOBO_CALCULATOR_AMOUNT,
		HEADER_KYOBO_CALCULATOR_RATE,
		HEADER_KAKAO_MAX
	};

	/**
	* Constructor.
	*/
	CSVKyobo();
	~CSVKyobo();

	void ReadFile(QString filepath);

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

#endif // CSV_KYOBO_H
