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

class CalcCPDlg;
class CalcTotalDlg;

class CalcManager : public QWidget
{
	Q_OBJECT

public:

	/**
	* Constructor.
	*/
	CalcManager(QWidget *parent = 0);
	~CalcManager();

	bool ExecuteCalc(QHash<int, QString>&);
	int ExecuteCP();
	int ExecuteTotal();

private slots:


private:



	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////
	CalcCPDlg*			m_CalcCP;
	CalcTotalDlg*		m_CalcTotal;


};

#endif // CALC_MANAGER_H
