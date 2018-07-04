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
#ifndef CSV_JUSTOON_H
#define CSV_JUSTOON_H

#include <QtCore/QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QtWidgets/QTableView>

class CSVJustoon : public QObject
{
	Q_OBJECT

public:

	enum HEADER_JUSTOON_TYPE {
		 HEADER_JUSTOON_NUMBER = 0,
		 HEADER_JUSTOON_CP_NAME,
		 HEADER_JUSTOON_TITLE,
		 HEADER_JUSTOON_AUTHOR,
		 HEADER_JUSTOON_PUBLISHER,
		 HEADER_JUSTOON_PURCHASE_TYPE,
		 HEADER_JUSTOON_COIN_RENTAL_PRICE,
		 HEADER_JUSTOON_COIN_PURCHASE_PRICE,
		 HEADER_JUSTOON_COIN_RENTAL_CANCEL,
		 HEADER_JUSTOON_COIN_PURCHASE_CANCEL,
		 HEADER_JUSTOON_COIN_TOTAL,
		 HEADER_JUSTOON_COIN_PRICE,
		 HEADER_JUSTOON_COIN_AMOUNT,
		 HEADER_JUSTOON_TOTAL_AMOUNT,
		 HEADER_JUSTOON_COMMISSION_RATE,
		 HEADER_JUSTOON_RS_RATE,
		 HEADER_JUSTOON_RS_AMOUNT,
		 HEADER_JUSTOON_TOTAL_RS_AMOUNT,
		 HEADER_JUSTOON_MAX
	};

	/**
	* Constructor.
	*/
	CSVJustoon();
	~CSVJustoon();

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

#endif // CSV_JUSTOON_H
