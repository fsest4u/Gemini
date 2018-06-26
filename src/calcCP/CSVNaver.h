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
#ifndef CSV_NAVER_H
#define CSV_NAVER_H

#include <QtCore/QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QtWidgets/QTableView>

class CSVNaver : public QObject
{
	Q_OBJECT

public:

	enum HEADER_NAVER_TYPE {
		HEADER_NAVER_TITILE = 0,
		HEADER_NAVER_BOOK_NUMBER,
		HEADER_NAVER_SUPPLY_CDE,
		HEADER_NAVER_CP_NAME,
		HEADER_NAVER_AUTHOR,
		HEADER_NAVER_PUBLISHER,
		HEADER_NAVER_AGE,
		HEADER_NAVER_SERVICE_DAY,
		HEADER_NAVER_RENTAL_BOOK_COUNT,
		HEADER_NAVER_RENTAL_BOOK_AMOUNT,
		HEADER_NAVER_RENTAL_SERIES_COUNT,
		HEADER_NAVER_RENTAL_SERIES_AMOUNT,
		HEADER_NAVER_PURCHASE_BOOK_COUNT,
		HEADER_NAVER_PURCHASE_BOOK_AMOUNT,
		HEADER_NAVER_PURCHASE_SERIES_COUNT,
		HEADER_NAVER_PURCHASE_SERIES_AMOUNT,
		HEADER_NAVER_RENTAL_COOKIE_COUNT,
		HEADER_NAVER_RENTAL_COOKIE_PAY_AMOUNT,
		HEADER_NAVER_RENTAL_COOKIE_FREE_AMOUNT,
		HEADER_NAVER_PURCHASE_COOKIE_COUNT,
		HEADER_NAVER_PURCHASE_COOKIE_PAY_AMOUNT,
		HEADER_NAVER_PURCHASE_COOKIE_FREE_AMOUNT,
		HEADER_NAVER_RENTAL_I_COOKIE_COUNT,
		HEADER_NAVER_RENTAL_I_COOKIE_PAY_AMOUNT,
		HEADER_NAVER_RENTAL_I_COOKIE_FREE_AMOUNT,
		HEADER_NAVER_PURCHASE_I_COOKIE_COUNT,
		HEADER_NAVER_PURCHASE_I_COOKIE_PAY_AMOUNT,
		HEADER_NAVER_PURCHASE_I_COOKIE_FREE_AMOUNT,
		HEADER_NAVER_FREE_TICKET,
		HEADER_NAVER_SALE_AMOUNT,
		HEADER_NAVER_MAX
	};

	/**
	* Constructor.
	*/
	CSVNaver();
	~CSVNaver();

	bool ReadFile(QString filepath);

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

};

#endif // CSV_NAVER_H
