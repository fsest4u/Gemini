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
#ifndef CSV_TOTAL_CP_H
#define CSV_TOTAL_CP_H

#include <QtCore/QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QtWidgets/QTableView>

class CalcCPDlg;

class CSVTotalCP : public QObject
{
	Q_OBJECT

public:

	enum ROW_AMOUNT_TYPE {
		ROW_AMOUNT_TOTAL = 0,
		ROW_AMOUNT_CALCULATOR,
		ROW_AMOUNT_AUTHOR,
		ROW_AMOUNT_RANK,
		ROW_AMOUNT_MAX
	};

	/**
	* Constructor.
	*/
	CSVTotalCP();
	~CSVTotalCP();

	void InitCPData();

	void SetCPTable(int column, QString total, QString calc, QString author, QString rank = "");
	void SetCPRank();

	void SetItem(CalcCPDlg* cpData);
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
	QList<QStringList>	m_CSVData;
	QStandardItemModel*	m_CSVModel;
	QTableView*			m_CSVView;

	double				m_TotalAmount;
	double				m_CalcAmount;
	double				m_AuthorAmount;
	QMap<double, int>	m_RankAmount;

};

#endif // CSV_TOTAL_CP_H
