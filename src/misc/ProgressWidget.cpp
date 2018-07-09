/************************************************************************
**
**  Copyright (C) 2018  spdevapp <spdevapp@joara.com>
**
**  This file is part of Gemini.
**
**  Gemini is Joara CSV Calculator.
**
*************************************************************************/

#include <QtWidgets/QProgressDialog>
#include <QtWidgets/QApplication>

#include "calcCP/CalcCPDlg.h"
#include "ProgressWidget.h"
#include "gemini_constants.h"



ProgressWidget::ProgressWidget() :
	m_Progress(NULL)
{
}


ProgressWidget::~ProgressWidget()
{
	if (m_Progress) {
		delete m_Progress;
		m_Progress = NULL;
	}
}

void ProgressWidget::InitProgress(QString title, int min, int max, double curIndex, double maxIndex)
{
	if (m_Progress) {
		delete m_Progress;
		m_Progress = NULL;
	}
	m_Progress = new QProgressDialog();
	m_Progress->setMinimumDuration(100);
	m_Progress->setMinimum(min);
	m_Progress->setMaximum(max);
	m_Progress->setValue(0);
	m_Progress->setAutoClose(true);
	QString label = "[" + QString::number(curIndex) + "/" + QString::number(maxIndex) + "] " 
					+ title + QString(" Data %1 ... ").arg(CP_NAME.at(curIndex));
	m_Progress->setLabelText(label);
}

void ProgressWidget::InitProgressSubtitle(QString title, QString subtitle, int min, int max, double curIndex, double maxIndex)
{
	if (m_Progress) {
		delete m_Progress;
		m_Progress = NULL;
	}
	m_Progress = new QProgressDialog();
	m_Progress->setMinimumDuration(100);
	m_Progress->setMinimum(min);
	m_Progress->setMaximum(max);
	m_Progress->setValue(0);
	m_Progress->setAutoClose(true);
	QString label = "[" + QString::number(curIndex) + "/" + QString::number(maxIndex) + "] "
		+ title + QString(" Data %1 ... ").arg(subtitle);
	m_Progress->setLabelText(label);
}

void ProgressWidget::SetValue(double curIndex)
{
	m_Progress->setValue(curIndex);
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
}

void ProgressWidget::Accept()
{
	m_Progress->accept();
}

