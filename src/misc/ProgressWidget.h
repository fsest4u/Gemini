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
#ifndef PROGRESS_WIDGET_H
#define PROGRESS_WIDGET_H

#include <QtWidgets/QWidget>

class QProgressDialog;

class ProgressWidget : public QWidget
{
	Q_OBJECT

public:
	ProgressWidget();
	virtual ~ProgressWidget();

	void InitProgress(QString title, int min, int max, double curIndex, double totIndex);
	void SetValue(double curIndex);
	void Accept();

private slots:


private:

	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////

	QProgressDialog*	m_Progress;

};

#endif // PROGRESS_WIDGET_H
