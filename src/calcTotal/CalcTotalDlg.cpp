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
#include "CalcTotalDlg.h"

#include "../gemini_constants.h"

const int PROGRESS_BAR_MINIMUM_DURATION = 500;


CalcTotalDlg::CalcTotalDlg(QDialog *parent) :
	QDialog(parent)
	, m_TotalCP(NULL)
	, m_TotalBookView(NULL)
	, m_TotalSeriesView(NULL)
	, m_TotalMemoView(NULL)
	, m_Progress(NULL)

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

	if (m_TotalBookView) {
		delete m_TotalBookView;
		m_TotalBookView = 0;
	}

	if (m_TotalSeriesView) {
		delete m_TotalSeriesView;
		m_TotalSeriesView = 0;
	}

	if (m_TotalMemoView) {
		delete m_TotalMemoView;
		m_TotalMemoView = 0;
	}

	if (m_Progress) {
		delete m_Progress;
		m_Progress = NULL;
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
	qDebug() << "[ReCalcTotal] -----";
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
	//m_Progress->setLabelText(QString("Calculate %1 Data ...").arg("Total"));
	//m_Progress->setValue(ROW_AMOUNT_TOTAL);
	//qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

	if (!m_TotalCP) { m_TotalCP = new CSVTotalCP(); }
	m_TotalCP->SetItem(cpData);

	// Add TabWidget
	QTableView* view = m_TotalCP->GetView();
	AddTab(view, "Total CP");

}

void CalcTotalDlg::SetTotal(CalcCPDlg* cpData)
{
	qDebug() << "[SetTotal]";

	//if (m_Progress) {
	//	delete m_Progress;
	//	m_Progress = NULL;
	//}
	//m_Progress = new QProgressDialog(this);
	//m_Progress->setMinimumDuration(PROGRESS_BAR_MINIMUM_DURATION);
	//m_Progress->setMinimum(ROW_AMOUNT_TOTAL);
	//m_Progress->setMaximum(ROW_AMOUNT_RANK);
	//m_Progress->setValue(0);
	//m_Progress->setAutoClose(true);

	// Delete and draw new
	ui.tabTotal->clear();

	QApplication::setOverrideCursor(Qt::WaitCursor);

	SetCPData(cpData);

	//m_Progress->accept();
	QApplication::restoreOverrideCursor();

}

void CalcTotalDlg::AddTab(QTableView* table, const QString cpName)
{
	qDebug() << "[CalcCPDlg AddTab] - " << cpName;

	QGridLayout* defalutLayout = new QGridLayout();
	defalutLayout->addWidget(table);

	QWidget* defaultWidget = new QWidget();
	defaultWidget->setLayout(defalutLayout);

	ui.tabTotal->addTab(defaultWidget, "Total");

}
