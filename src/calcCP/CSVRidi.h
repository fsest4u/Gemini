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
#ifndef CSV_RIDI_H
#define CSV_RIDI_HCSV_RIDI_H

#include <QtCore/QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QtWidgets/QTableView>

class CSVRidi : public QObject
{
	Q_OBJECT

public:

	enum HEADER_RIDI_TYPE {
		HEADER_RIDI_BOOK_ID = 0,
		HEADER_RIDI_TITLE,
		HEADER_RIDI_SERIES_NUMBER,
		HEADER_RIDI_AUTHOR,
		HEADER_RIDI_TRANSLATOR,
		HEADER_RIDI_ARTIST,
		HEADER_RIDI_PUBLISHER,
		HEADER_RIDI_SERIES_NAME,
		HEADER_RIDI_EBOOK_PRICE,
		HEADER_RIDI_BOOK_AMOUNT,
		HEADER_RIDI_BOOK_COUNT,
		HEADER_RIDI_BOOK_FREE_COUNT,
		HEADER_RIDI_RENTAL_AMOUNT,
		HEADER_RIDI_RENTAL_COUNT,
		HEADER_RIDI_FREE_DOWN_AMOUNT,
		HEADER_RIDI_FREE_DOWN_COUNT,
		HEADER_RIDI_SET_AMOUNT,
		HEADER_RIDI_SET_COUNT,
		HEADER_RIDI_SET_RENTAL_AMOUNT,
		HEADER_RIDI_SET_RENTAL_COUNT,
		HEADER_RIDI_CANCEL_AMOUNT,
		HEADER_RIDI_CANCEL_COUNT,
		HEADER_RIDI_CALCULATOR_AMOUNT,
		HEADER_RIDI_BOOK_ISBN10,
		HEADER_RIDI_BOOK_ISBN13,
		HEADER_RIDI_EBOOK_ISBN10,
		HEADER_RIDI_EBOOK_ISBN13,
		HEADER_RIDI_CP_ID,
		HEADER_RIDI_CATEGORY1,
		HEADER_RIDI_CATEGORY2,
		HEADER_RIDI_MAX
	};

	/**
	* Constructor.
	*/
	CSVRidi();
	~CSVRidi();

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

};

#endif // CSV_RIDI_H
