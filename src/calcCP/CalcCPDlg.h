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
#ifndef CALC_CP_DLG_H
#define CALC_CP_DLG_H

#include <QtWidgets/QDialog>
#include "ui_CalcCPDlg.h"

class CalcCPDlg : public QDialog
{
	Q_OBJECT

public:

	/**
	* Constructor.
	*/
	CalcCPDlg(QDialog *parent = 0);
	~CalcCPDlg();

private slots:

	void connectSignalsSlots();

	void Prev();
	void CalcCP();
	void Next();


private:



	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////


	Ui::CalcCPDlg ui;

};

#endif // CALC_CP_DLG_H
