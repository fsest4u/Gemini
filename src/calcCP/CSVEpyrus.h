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
#ifndef CSV_EPYRUS_H
#define CSV_EPYRUS_H

#include <QtCore/QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QtWidgets/QTableView>

class ProgressWidget;

class CSVEpyrus : public QObject
{
	Q_OBJECT

public:

	enum HEADER_EPYRUS_TYPE {
		HEADER_EPYRUS_TYPE = 0,
		HEADER_EPYRUS_TITLE,
		HEADER_EPYRUS_AUTHOR,
		HEADER_EPYRUS_PUBLISHER,
		HEADER_EPYRUS_COUNT,
		HEADER_EPYRUS_SALE_AMOUNT,
		HEADER_EPYRUS_FEE,
		HEADER_EPYRUS_CALCULATOR_AMOUNT,
		HEADER_EPYRUS_ISBN,
		HEADER_EPYRUS_MAX
	};

	/**
	* Constructor.
	*/
	CSVEpyrus();
	~CSVEpyrus();

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

#endif // CSV_EPYRUS_HCSV_EPYRUS_H
