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

class ProgressWidget;

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

	enum COMPANY_TYPE {
		COMPANY_OEBOOK_ALL = 0,
		COMPANY_OEBOOK,
		COMPANY_OEBOOK_ROMANCE,
		COMPANY_OEBOOK_MURIM,
		COMPANY_OEBOOK_COMIC,
		COMPANY_MAX
	};


	/**
	* Constructor.
	*/
	CSVOebook();
	~CSVOebook();

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

	ProgressWidget* m_ProgressWidget;

};

#endif // CSV_OEBOOK_H
