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
#ifndef CSV_BAROBOOK_H
#define CSV_BAROBOOK_H

#include <QtCore/QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QtWidgets/QTableView>

class CSVBarobook : public QObject
{
	Q_OBJECT

public:

	enum HEADER_BAROBOOK_TYPE {
		HEADER_BAROBOOK_MONTH = 0,
		HEADER_BAROBOOK_BOOK_NUMBER,
		HEADER_BAROBOOK_TITLE,
		HEADER_BAROBOOK_AUTHOR,
		HEADER_BAROBOOK_PUBLISHER,
		HEADER_BAROBOOK_CP_BOOK_NUMBER,
		HEADER_BAROBOOK_SERVICE,
		HEADER_BAROBOOK_PRICE,
		HEADER_BAROBOOK_BOOK_COUNT,
		HEADER_BAROBOOK_BOOK_PRICE,
		HEADER_BAROBOOK_BOOK_DISCOUNT_CHARGE,
		HEADER_BAROBOOK_SERIES_COUNT,
		HEADER_BAROBOOK_SERIES_PRICE,
		HEADER_BAROBOOK_SERIES_DISCOUNT_CHARGE,
		HEADER_BAROBOOK_PACKAGE_COUNT,
		HEADER_BAROBOOK_PACKAGE_PRICE,
		HEADER_BAROBOOK_PACKAGE_DISCOUNT_CHARGE,
		HEADER_BAROBOOK_RENTAL_COUNT,
		HEADER_BAROBOOK_RENTAL_PRICE,
		HEADER_BAROBOOK_FIXED_COUNT,
		HEADER_BAROBOOK_FIXED_PRICE,
		HEADER_BAROBOOK_EVENT_COUNT,
		HEADER_BAROBOOK_EVENT_PRICE,
		HEADER_BAROBOOK_BOOKPACK_COUNT,
		HEADER_BAROBOOK_BOOKPACK_PRICE,
		HEADER_BAROBOOK_TOTAL_AMOUNT,
		HEADER_BAROBOOK_MAX
	};

	/**
	* Constructor.
	*/
	CSVBarobook();
	~CSVBarobook();

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

#endif // CSV_BAROBOOK_H
