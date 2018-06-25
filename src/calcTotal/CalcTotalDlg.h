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

class CalcTotalDlg : public QDialog
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
	CalcTotalDlg(QDialog *parent = 0);
	~CalcTotalDlg();

	void SetTotal(CalcCPDlg*);

private slots:

	void connectSignalsSlots();

	void Prev();
	void CalcTotal();
	void Next();

private:

	void InitUI();

	void InitCPData();
	void SetCPTable(int column, QString total, QString calc, QString author);
	void SetCPData(CalcCPDlg*);

	void AddTab(QTableView* table, const QString cpName);


	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////

	double				m_totalAmount;
	double				m_calcAmount;
	double				m_authorAmount;

	QStandardItemModel *m_TotalAmountModel;

	QTableView*			m_TotalView;
	QTableView*			m_TotalBookView;
	QTableView*			m_TotalSeriesView;
	QTableView*			m_TotalMemoView;

	QProgressDialog*	m_Progress;

	Ui::CalcTotalDlg ui;

};

#endif // CALC_TOTAL_DLG_H
