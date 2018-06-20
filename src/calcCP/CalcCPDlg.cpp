/************************************************************************
**
**  Copyright (C) 2018  spdevapp <spdevapp@joara.com>
**
**  This file is part of Gemini.
**
**  Gemini is Joara CSV Calculator.
**
*************************************************************************/

#include <QtDebug>
#include <QtCore/QObject>
#include <QtWidgets/QPushButton>

#include "CalcCPDlg.h"

CalcCPDlg::CalcCPDlg(QDialog *parent) :
	QDialog(parent)
{
	ui.setupUi(this);

	connectSignalsSlots();
}

CalcCPDlg::~CalcCPDlg()
{
}

void CalcCPDlg::connectSignalsSlots()
{
	// prev button
	connect(ui.buttonBox->button(QDialogButtonBox::Yes), SIGNAL(clicked()), this, SLOT(Prev()));
	// calc button
	connect(ui.buttonBox->button(QDialogButtonBox::Retry), SIGNAL(clicked()), this, SLOT(CalcCP()));
	// next button
	connect(ui.buttonBox->button(QDialogButtonBox::No), SIGNAL(clicked()), this, SLOT(Next()));

}

void CalcCPDlg::Prev()
{
	this->done(QDialogButtonBox::YesRole);
}

void CalcCPDlg::CalcCP()
{
	this->done(QDialogButtonBox::HelpRole);
}

void CalcCPDlg::Next()
{
	this->done(QDialogButtonBox::NoRole);
}

