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
#ifndef CSV_KEPUB_H
#define CSV_KEPUB_H

#include <QtCore/QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QtWidgets/QTableView>

class CSVKepub : public QObject
{
	Q_OBJECT

public:

	enum HEADER_KEPUB_TYPE {
		HEADER_KEPUB_SEQ_NUMBER = 0,
		HEADER_KEPUB_TITLE,
		HEADER_KEPUB_PUBLISHER,
		HEADER_KEPUB_PRICE,
		HEADER_KEPUB_BOOK_STORE,
		HEADER_KEPUB_STORE_PRICE,
		HEADER_KEPUB_STORE_REFUND_PRICE,
		HEADER_KEPUB_PRICE_RATE,
		HEADER_KEPUB_CALCULATOR_AMOUNT,
		HEADER_KEPUB_EVENT_TYPE,
		HEADER_KEPUB_PURCHASE_TYPE,
		HEADER_KEPUB_EVENT_AMOUNT,
		HEADER_KEPUB_AUTHOR,
		HEADER_KEPUB_BOOK_ID,
		HEADER_KEPUB_EPUB_ID,
		HEADER_KEPUB_BOOK_ISBN,
		HEADER_KEPUB_EBOOK_ISBN,
		HEADER_KEPUB_PURCHASE_DAY,
		HEADER_KEPUB_REFUND_DAY,
		HEADER_KAKAO_MAX
	};

	enum STORE_TYPE {
		STORE_ALL = 0,
		STORE_YES24,
		STORE_ALADDIN,
		STORE_BANDI,
		STORE_MAX
	};


	/**
	* Constructor.
	*/
	CSVKepub();
	~CSVKepub();

	void ReadFile(QString filepath);

	void SetItem();
	QStandardItemModel* GetItem();

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

	QStringList		m_CSVHeader;

	QList<double>	m_TotalAmount;
	QList<double>	m_CalcAmount;
	QList<double>	m_AuthorAmount;

};

#endif // CSV_KEPUB_H
