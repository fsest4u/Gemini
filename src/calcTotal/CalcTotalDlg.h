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

#include <QtWidgets/QDialog>
#include "ui_CalcTotalDlg.h"

class CalcTotalDlg : public QDialog
{
	Q_OBJECT

public:

	/**
	* Constructor.
	*/
	CalcTotalDlg(QDialog *parent = 0);
	~CalcTotalDlg();

private slots:

	void connectSignalsSlots();

	void Prev();
	void CalcCP();
	void Next();

private:



	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////


	Ui::CalcTotalDlg ui;

};

#endif // CALC_TOTAL_DLG_H
