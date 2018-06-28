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
#ifndef CALC_TOTAL_DLG_H
#define CALC_TOTAL_DLG_H

#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QDialog>
#include <QtWidgets/QProgressDialog>

#include "ui_CalcTotalDlg.h"

class CalcCPDlg;
class CSVTotalCP;
class CSVTotalBook;
class CSVTotalSeries;

class CalcTotalDlg : public QDialog
{
	Q_OBJECT

public:

	/**
	* Constructor.
	*/
	CalcTotalDlg(QDialog *parent = 0);
	~CalcTotalDlg();

	void SetTotal(CalcCPDlg*);

private slots:

	void connectSignalsSlots();

	void Prev();
	void ReCalcTotal();
	void Extract();

private:

	void InitUI();

	void SetCPData(CalcCPDlg*);
	void SetBookData(CalcCPDlg*);
	void SetSeriesData(CalcCPDlg*);

	void AddTab(QTableView* table, const QString cpName);


	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////

	CSVTotalCP*			m_TotalCP;
	CSVTotalBook*		m_TotalBook;
	CSVTotalSeries*		m_TotalSeries;

	QProgressDialog*	m_Progress;

	Ui::CalcTotalDlg ui;

};

#endif // CALC_TOTAL_DLG_H
