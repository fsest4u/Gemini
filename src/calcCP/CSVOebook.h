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
#ifndef CSV_OEBOOK_H
#define CSV_OEBOOK_H

#include <QtCore/QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QtWidgets/QTableView>

class CSVOebook : public QObject
{
	Q_OBJECT

public:

	enum HEADER_OEBOOK_TYPE {
		HEADER_OEBOOK_BOOKCODE = 0,
		HEADER_OEBOOK_COMPANY,
		HEADER_OEBOOK_TITLE,
		HEADER_OEBOOK_RENT_DAY,
		HEADER_OEBOOK_AUTHOR,
		HEADER_OEBOOK_PUBULISHER,
		HEADER_OEBOOK_CONTRACTOR,
		HEADER_OEBOOK_PRICE,
		HEADER_OEBOOK_SALE_PRICE,
		HEADER_OEBOOK_COUNT,
		HEADER_OEBOOK_FEE,
		HEADER_OEBOOK_TOTAL_AMOUNT,
		HEADER_OEBOOK_PURCHASE_TYPE,
		HEADER_OEBOOK_CALCURATE_RATE,
		HEADER_OEBOOK_CALCURATE_AMOUNT,
		HEADER_OEBOOK_PURCHASE_DAY,
		HEADER_OEBOOK_MAX,
	};

	/**
	* Constructor.
	*/
	CSVOebook();
	~CSVOebook();

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

#endif // CSV_OEBOOK_H
