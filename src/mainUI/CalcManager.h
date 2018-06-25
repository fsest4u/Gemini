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
#ifndef CALC_MANAGER_H
#define CALC_MANAGER_H

#include <QtWidgets/QWidget>

#include "calcCP/CalcCPDlg.h"

class CalcCPDlg;
class CalcTotalDlg;

class CalcManager : public QWidget
{
	Q_OBJECT

public:

	enum STEP_CALC {
		STEP_CALC_MAIN = 0
		, STEP_CALC_MAIN_NEXT
		, STEP_CALC_CP_PREV
		, STEP_CALC_CP
		, STEP_CALC_CP_NEXT
		, STEP_CALC_TOTAL_PREV
		, STEP_CALC_TOTAL
		, STEP_CALC_TOTAL_NEXT
		, STEP_CALC_CANCEL
		, STEP_CALC_MAX
	};

	/**
	* Constructor.
	*/
	CalcManager(QWidget *parent = 0);
	~CalcManager();

	bool ExecuteCalc(QHash<int, QString>&);
	int ExecuteCP(QHash<int, QString>&, bool bRefresh);
	int ExecuteTotal(bool bRefresh);

private slots:


private:



	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////
	CalcCPDlg*			m_CalcCP;
	CalcTotalDlg*		m_CalcTotal;


};

#endif // CALC_MANAGER_H
