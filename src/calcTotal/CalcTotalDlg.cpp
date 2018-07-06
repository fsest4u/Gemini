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
#include <QtCore/QString>
#include <QtWidgets/QPushButton>

#include "calcCP/CalcCpDlg.h"
#include "calcTotal/CSVTotalCP.h"
#include "calcTotal/CSVTotalBook.h"
#include "calcTotal/CSVTotalSeries.h"
#include "CalcTotalDlg.h"

#include "gemini_constants.h"

const int PROGRESS_BAR_MINIMUM_DURATION = 50;


CalcTotalDlg::CalcTotalDlg(QDialog *parent) :
	QDialog(parent)
	, m_TotalCP(NULL)
	, m_TotalBook(NULL)
	, m_TotalSeries(NULL)

{
	ui.setupUi(this);

	InitUI();

}

CalcTotalDlg::~CalcTotalDlg()
{
	if (m_TotalCP) {
		delete m_TotalCP;
		m_TotalCP = 0;
	}

	if (m_TotalBook) {
		delete m_TotalBook;
		m_TotalBook = 0;
	}

	if (m_TotalSeries) {
		delete m_TotalSeries;
		m_TotalSeries = 0;
	}

}

void CalcTotalDlg::InitUI()
{

	ui.buttonBox->button(QDialogButtonBox::Yes)->setText(tr("Prev"));
	ui.buttonBox->button(QDialogButtonBox::Retry)->setText(tr("Re-Calculate"));
	ui.buttonBox->button(QDialogButtonBox::No)->setText(tr("Extract"));

	connectSignalsSlots();

	setWindowFlags(windowFlags() |
		Qt::CustomizeWindowHint |
		Qt::WindowMinimizeButtonHint |
		Qt::WindowMaximizeButtonHint |
		Qt::WindowCloseButtonHint);

}


void CalcTotalDlg::connectSignalsSlots()
{
	// prev button
	connect(ui.buttonBox->button(QDialogButtonBox::Yes), SIGNAL(clicked()), this, SLOT(Prev()));
	// calc button
	connect(ui.buttonBox->button(QDialogButtonBox::Retry), SIGNAL(clicked()), this, SLOT(ReCalcTotal()));
	// next button
	connect(ui.buttonBox->button(QDialogButtonBox::No), SIGNAL(clicked()), this, SLOT(Extract()));

}

void CalcTotalDlg::Prev()
{
	this->done(QDialogButtonBox::YesRole);
}

void CalcTotalDlg::ReCalcTotal()
{
	//qDebug() << "[ReCalcTotal] -----";
	// Delete and draw new
	ui.tabTotal->clear();

	this->done(QDialogButtonBox::HelpRole);
}

void CalcTotalDlg::Extract()
{
	this->done(QDialogButtonBox::NoRole);
}


void CalcTotalDlg::SetCPData(CalcCPDlg* cpData)
{
	if (!m_TotalCP) { m_TotalCP = new CSVTotalCP(); }
	m_TotalCP->SetItem(cpData);

	// Add TabWidget
	QTableView* view = m_TotalCP->GetView();
	AddTab(view, "Total By CP");

}

void CalcTotalDlg::SetBookData(CalcCPDlg* cpData)
{
	if (!m_TotalBook) { m_TotalBook = new CSVTotalBook(); }
	m_TotalBook->SetItem(cpData);

	// Add TabWidget
	QTableView* view = m_TotalBook->GetView();
	AddTab(view, "Total By Book");
}

void CalcTotalDlg::SetSeriesData(CalcCPDlg* cpData)
{
	if (!m_TotalSeries) { m_TotalSeries = new CSVTotalSeries(); }
	m_TotalSeries->SetItem(cpData);

	// Add TabWidget
	QTableView* view = m_TotalSeries->GetView();
	AddTab(view, "Total By Series");
}


void CalcTotalDlg::SetTotal(CalcCPDlg* cpData)
{
	//qDebug() << "[SetTotal]";
	// Delete and draw new
	ui.tabTotal->clear();

	QApplication::setOverrideCursor(Qt::WaitCursor);

	SetCPData(cpData);

	SetBookData(cpData);

	SetSeriesData(cpData);
	// todo - send notes

	QApplication::restoreOverrideCursor();
}

void CalcTotalDlg::AddTab(QTableView* table, const QString cpName)
{
	//qDebug() << "[CalcCPDlg AddTab] - " << cpName;

	QGridLayout* defalutLayout = new QGridLayout();
	defalutLayout->addWidget(table);

	QWidget* defaultWidget = new QWidget();
	defaultWidget->setLayout(defalutLayout);

	ui.tabTotal->addTab(defaultWidget, cpName);

}

bool CalcTotalDlg::ExtractCSV(QString lastFolderOpen)
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	QString temp;
	if (m_TotalCP) {
		temp = lastFolderOpen + "\\TotalCP.csv";
		m_TotalCP->WriteFile(temp);

	}
	if (m_TotalBook) {
		temp = lastFolderOpen + "\\TotalBook.csv";
		m_TotalBook->WriteFile(temp);

	}
	if (m_TotalSeries) {
		temp = lastFolderOpen + "\\TotalSeries.csv";
		m_TotalSeries->WriteFile(temp);

	}

	QApplication::restoreOverrideCursor();
	return true;
}