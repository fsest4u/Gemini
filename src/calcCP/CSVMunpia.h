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
#ifndef CSV_MUNPIA_H
#define CSV_MUNPIA_H

#include <QtCore/QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QtWidgets/QTableView>

class ProgressWidget;

class CSVMunpia : public QObject
{
	Q_OBJECT

public:

	enum HEADER_MUNPIA_TYPE {
		HEADER_MUNPIA_TITLE = 0,
		HEADER_MUNPIA_AUTHOR,
		HEADER_MUNPIA_COUNT,
		HEADER_MUNPIA_CANCEL,
		HEADER_MUNPIA_SALE_AMOUNT,
		HEADER_MUNPIA_CANCEL_AMOUNT,
		HEADER_MUNPIA_REAL_AMOUNT,
		HEADER_MUNPIA_CALCULATOR_AMOUNT,
		HEADER_MUNPIA_MAX
	};

	/**
	* Constructor.
	*/
	CSVMunpia();
	~CSVMunpia();

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

#endif // CSV_MUNPIA_H
