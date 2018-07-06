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
#ifndef CSV_ONESTORE_H
#define CSV_ONESTORE_H

#include <QtCore/QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QtWidgets/QTableView>

class ProgressWidget;

class CSVOnestore : public QObject
{
	Q_OBJECT

public:

	enum HEADER_ONESTORE_TYPE {
		HEADER_ONESTORE_DAY = 0,
		HEADER_ONESTORE_PURCHASE_STATUS,
		HEADER_ONESTORE_PRODUCT_TYPE,
		HEADER_ONESTORE_MAIN_CATEGORY,
		HEADER_ONESTORE_SUB_CATEGORY,
		HEADER_ONESTORE_MEDIA,
		HEADER_ONESTORE_SECTION,
		HEADER_ONESTORE_CAMPAIGN,
		HEADER_ONESTORE_PID,
		HEADER_ONESTORE_CHANNEL_PID,
		HEADER_ONESTORE_PARTNER_NAME,
		HEADER_ONESTORE_PARTNER_ID,
		HEADER_ONESTORE_PUBLISHER,
		HEADER_ONESTORE_AUTHOR,
		HEADER_ONESTORE_ARTIST,
		HEADER_ONESTORE_CHANNEL_TITLE,
		HEADER_ONESTORE_TITLE,
		HEADER_ONESTORE_SERIES_NUMBER,
		HEADER_ONESTORE_BOOK_TYPE,
		HEADER_ONESTORE_BP_ID,
		HEADER_ONESTORE_PRICE,
		HEADER_ONESTORE_SALE_AMOUNT,
		HEADER_ONESTORE_COUNT,
		HEADER_ONESTORE_DISCOUNT,
		HEADER_ONESTORE_CUSTOM_CHARGE,
		HEADER_ONESTORE_MARKET_SITE,
		HEADER_ONESTORE_SALES_SITE,
		HEADER_ONESTORE_MAX
	};

	/**
	* Constructor.
	*/
	CSVOnestore();
	~CSVOnestore();

	bool ReadFile(QString filepath);
	void WriteFile(QString filepath);

	void SetItem();
	QStandardItemModel* GetItem() { return m_CSVModel; }
	QTableView* GetView();

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
	QTableView*			m_CSVView;

	QStringList		m_CSVHeader;

	double			m_TotalAmount;
	double			m_CalcAmount;
	double			m_AuthorAmount;

	ProgressWidget* m_ProgressWidget;

};

#endif // CSV_ONESTORE_H
