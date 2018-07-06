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

class QProgressDialog;

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
		HEADER_KYOBO_MAX
	};

	enum BUSINESS_TYPE {
		BUSINESS_ALL = 0,
		BUSINESS_B2C,
		BUSINESS_B2BC,
		BUSINESS_MAX
	};

	/**
	* Constructor.
	*/
	CSVKyobo();
	~CSVKyobo();

	bool ReadFile(QString filepath);
	void WriteFile(QString filepath);

	void SetItem();
	QStandardItemModel* GetItem() { return m_CSVModel; }
	QTableView* GetView();

	QList<double> GetTotalAmount() { return m_TotalAmount; };
	QList<double> GetCalcAmount() { return m_CalcAmount; };
	QList<double> GetAuthorAmount() { return m_AuthorAmount; };

private slots:


private:



	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////
	QList<QStringList> m_CSVData;
	QStandardItemModel *m_CSVModel;
	QTableView*			m_CSVView;

	QStringList		m_CSVHeader;

	QList<double>	m_TotalAmount;
	QList<double>	m_CalcAmount;
	QList<double>	m_AuthorAmount;

	QProgressDialog*	m_Progress;

};

#endif // CSV_KYOBO_H
