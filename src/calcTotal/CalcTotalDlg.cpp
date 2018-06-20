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

#include "CalcTotalDlg.h"

CalcTotalDlg::CalcTotalDlg(QDialog *parent) :
	QDialog(parent)
{
	ui.setupUi(this);

	connectSignalsSlots();

}

CalcTotalDlg::~CalcTotalDlg()
{
}

void CalcTotalDlg::connectSignalsSlots()
{
	// prev button
	connect(ui.buttonBox->button(QDialogButtonBox::Yes), SIGNAL(clicked()), this, SLOT(Prev()));
	// calc button
	connect(ui.buttonBox->button(QDialogButtonBox::Retry), SIGNAL(clicked()), this, SLOT(CalcCP()));
	// next button
	connect(ui.buttonBox->button(QDialogButtonBox::No), SIGNAL(clicked()), this, SLOT(Next()));

}

void CalcTotalDlg::Prev()
{
	this->done(QDialogButtonBox::YesRole);
}

void CalcTotalDlg::CalcCP()
{
	this->done(QDialogButtonBox::HelpRole);
}

void CalcTotalDlg::Next()
{
	this->done(QDialogButtonBox::NoRole);
}

