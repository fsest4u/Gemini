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
#ifndef CSV_MRBLUE_H
#define CSV_MRBLUE_H

#include <QtCore/QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QtWidgets/QTableView>

class CSVMrblue : public QObject
{
	Q_OBJECT

public:

	enum HEADER_MRBLUE_TYPE {
		HEADER_MRBLUE_DAY = 0,
		HEADER_MRBLUE_TITLE,
		HEADER_MRBLUE_AUTHOR,
		HEADER_MRBLUE_BOOK_CODE,
		HEADER_MRBLUE_FIXED_COUNT,
		HEADER_MRBLUE_FIXED_SALE_AMOUNT,
		HEADER_MRBLUE_FIXED_CALCULATOR_AMOUNT,
		HEADER_MRBLUE_WEIGHT_BOOK_COUNT,
		HEADER_MRBLUE_WEIGHT_BOOK_USE_COUNT,
		HEADER_MRBLUE_WEIGHT_BOOK_SALE_AMOUNT,
		HEADER_MRBLUE_WEIGHT_SERIES_COUNT,
		HEADER_MRBLUE_WEIGHT_SERIES_USE_COUNT,
		HEADER_MRBLUE_WEIGHT_SERIES_SALE_AMOUNT,
		HEADER_MRBLUE_WEIGHT_TOTAL_COUNT,
		HEADER_MRBLUE_WEIGHT_TOTAL_USE_COUNT,
		HEADER_MRBLUE_WEIGHT_TOTAL_AMOUNT,
		HEADER_MRBLUE_WEIGHT_CALCULATOR_AMOUNT,
		HEADER_MRBLUE_TOTAL_AMOUNT,
		HEADER_MRBLUE_CALCULATOR_AMOUNT,
		HEADER_KAKAO_MAX
	};

	/**
	* Constructor.
	*/
	CSVMrblue();
	~CSVMrblue();

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

#endif // CSV_MRBLUE_H
