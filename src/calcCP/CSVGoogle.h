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
#ifndef CSV_GOOGLE_H
#define CSV_GOOGLE_H

#include <QtCore/QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QtWidgets/QTableView>

class CSVGoogle : public QObject
{
	Q_OBJECT

public:

	enum HEADER_GOOGLE_TYPE {
		 HEADER_GOOGLE_TITLE = 0,
		 HEADER_GOOGLE_AUTHOR,
		 HEADER_GOOGLE_ISBN,
		 HEADER_GOOGLE_COUNTRY,
		 HEADER_GOOGLE_PURCHASE_COUNT,
		 HEADER_GOOGLE_REFUND_COUNT,
		 HEADER_GOOGLE_SOLD_COUNT,
		 HEADER_GOOGLE_TOTAL_AMOUNT,
		 HEADER_GOOGLE_MAX
	};

	/**
	* Constructor.
	*/
	CSVGoogle();
	~CSVGoogle();

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

#endif // CSV_GOOGLE_H
