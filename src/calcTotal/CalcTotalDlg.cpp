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
#include "CalcTotalDlg.h"

#include "../gemini_constants.h"

const int PROGRESS_BAR_MINIMUM_DURATION = 500;


CalcTotalDlg::CalcTotalDlg(QDialog *parent) :
	QDialog(parent)
	, m_TotalView(NULL)
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
	if (m_TotalView) {
		delete m_TotalView;
		m_TotalView = 0;
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
	ui.buttonBox->button(QDialogButtonBox::No)->setText(tr("Next"));

	connectSignalsSlots();

	setWindowFlags(windowFlags() |
		Qt::CustomizeWindowHint |
		Qt::WindowMinimizeButtonHint |
		Qt::WindowMaximizeButtonHint |
		Qt::WindowCloseButtonHint);

	InitCPData();

}


void CalcTotalDlg::connectSignalsSlots()
{
	// prev button
	connect(ui.buttonBox->button(QDialogButtonBox::Yes), SIGNAL(clicked()), this, SLOT(Prev()));
	// calc button
	connect(ui.buttonBox->button(QDialogButtonBox::Retry), SIGNAL(clicked()), this, SLOT(CalcTotal()));
	// next button
	connect(ui.buttonBox->button(QDialogButtonBox::No), SIGNAL(clicked()), this, SLOT(Next()));

}

void CalcTotalDlg::Prev()
{
	this->done(QDialogButtonBox::YesRole);
}

void CalcTotalDlg::CalcTotal()
{
	qDebug() << "[CalcTotal] -----";
	// Delete and draw new
	int count = ui.tabTotal->count();
	for (int i = 0; i < count; i++) {
		ui.tabTotal->removeTab(i);
	}

	QApplication::setOverrideCursor(Qt::WaitCursor);

	QApplication::restoreOverrideCursor();

	this->done(QDialogButtonBox::HelpRole);
}

void CalcTotalDlg::Next()
{
	this->done(QDialogButtonBox::NoRole);
}

void CalcTotalDlg::InitCPData()
{
	// table data
	m_TotalAmountModel = new QStandardItemModel(ROW_AMOUNT_MAX, CalcCPDlg::CP_TYPE::CP_MAX + 4);

	// set header
	m_TotalAmountModel->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("ÃÑ°è"));

	// set line number
	m_TotalAmountModel->setVerticalHeaderItem(ROW_AMOUNT_TOTAL, new QStandardItem("Total Amount"));		// total
	m_TotalAmountModel->setVerticalHeaderItem(ROW_AMOUNT_CALCULATOR, new QStandardItem("Calc Amount"));		// calculation
	m_TotalAmountModel->setVerticalHeaderItem(ROW_AMOUNT_AUTHOR, new QStandardItem("Author Amount"));	// author
	m_TotalAmountModel->setVerticalHeaderItem(ROW_AMOUNT_RANK, new QStandardItem("Rank"));				// rank

	m_totalAmount = 0;
	m_calcAmount = 0;
	m_authorAmount = 0;

}

void CalcTotalDlg::SetCPTable(int column, QString total, QString calc, QString author)
{
	//set data
	m_TotalAmountModel->setData(m_TotalAmountModel->index(ROW_AMOUNT_TOTAL, column), total);
	m_TotalAmountModel->setData(m_TotalAmountModel->index(ROW_AMOUNT_CALCULATOR, column), calc);
	m_TotalAmountModel->setData(m_TotalAmountModel->index(ROW_AMOUNT_AUTHOR, column), author);

	// if column is not zero, add amount.
	if (column) {
		m_totalAmount += total.replace(",", "").toDouble();
		m_calcAmount += calc.replace(",", "").toDouble();
		m_authorAmount += author.replace(",", "").toDouble();
	}
}


void CalcTotalDlg::SetCPData(CalcCPDlg* cpData)
{
	//m_Progress->setLabelText(QString("Calculate %1 Data ...").arg("Total"));
	//m_Progress->setValue(ROW_AMOUNT_TOTAL);
	//qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

	if (cpData->GetKyobo()) {
		m_TotalAmountModel->setHeaderData(CalcCPDlg::CP_KYOBO + 1, Qt::Horizontal, QString::fromLocal8Bit(CPNAME_KYOBO.toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_KYOBO + 1
			, QString("%L1").arg(cpData->GetKyobo()->GetTotalAmount().at(CSVKyobo::BUSINESS_ALL), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKyobo()->GetCalcAmount().at(CSVKyobo::BUSINESS_ALL), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKyobo()->GetAuthorAmount().at(CSVKyobo::BUSINESS_ALL), 0, 'f', 0));
	}
	if (cpData->GetNaver()) {
		m_TotalAmountModel->setHeaderData(CalcCPDlg::CP_NAVER + 1, Qt::Horizontal, QString::fromLocal8Bit(CPNAME_NAVER.toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_NAVER + 1
			, QString("%L1").arg(cpData->GetNaver()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetNaver()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetNaver()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetRidi()) {
		m_TotalAmountModel->setHeaderData(CalcCPDlg::CP_RIDI + 1, Qt::Horizontal, QString::fromLocal8Bit(CPNAME_RIDI.toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_RIDI + 1
			, QString("%L1").arg(cpData->GetRidi()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetRidi()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetRidi()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetMunpia()) {
		m_TotalAmountModel->setHeaderData(CalcCPDlg::CP_MUNPIA + 1, Qt::Horizontal, QString::fromLocal8Bit(CPNAME_MUNPIA.toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_MUNPIA + 1
			, QString("%L1").arg(cpData->GetMunpia()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetMunpia()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetMunpia()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetMrblue()) {
		m_TotalAmountModel->setHeaderData(CalcCPDlg::CP_MRBLUE + 1, Qt::Horizontal, QString::fromLocal8Bit(CPNAME_MRBLUE.toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_MRBLUE + 1
			, QString("%L1").arg(cpData->GetMrblue()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetMrblue()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetMrblue()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetBarobook()) {
		m_TotalAmountModel->setHeaderData(CalcCPDlg::CP_BAROBOOK + 1, Qt::Horizontal, QString::fromLocal8Bit(CPNAME_BAROBOOK.toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_BAROBOOK + 1
			, QString("%L1").arg(cpData->GetBarobook()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetBarobook()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetBarobook()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetBookcube()) {
		m_TotalAmountModel->setHeaderData(CalcCPDlg::CP_BOOKCUBE + 1, Qt::Horizontal, QString::fromLocal8Bit(CPNAME_BOOKCUBE.toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_BOOKCUBE + 1
			, QString("%L1").arg(cpData->GetBookcube()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetBookcube()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetBookcube()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetEpyrus()) {
		m_TotalAmountModel->setHeaderData(CalcCPDlg::CP_EPYRUS + 1, Qt::Horizontal, QString::fromLocal8Bit(CPNAME_EPYRUS.toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_EPYRUS + 1
			, QString("%L1").arg(cpData->GetEpyrus()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetEpyrus()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetEpyrus()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetOebook()) {
		m_TotalAmountModel->setHeaderData(CalcCPDlg::CP_OEBOOK + 1, Qt::Horizontal, QString::fromLocal8Bit(CPNAME_OEBOOK.toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_OEBOOK + 1
			, QString("%L1").arg(cpData->GetOebook()->GetTotalAmount().at(CSVOebook::COMPANY_OEBOOK_ALL), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetOebook()->GetCalcAmount().at(CSVOebook::COMPANY_OEBOOK_ALL), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetOebook()->GetAuthorAmount().at(CSVOebook::COMPANY_OEBOOK_ALL), 0, 'f', 0));
	}
	if (cpData->GetOnestore()) {
		m_TotalAmountModel->setHeaderData(CalcCPDlg::CP_ONESTORE + 1, Qt::Horizontal, QString::fromLocal8Bit(CPNAME_ONESTORE.toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_ONESTORE + 1
			, QString("%L1").arg(cpData->GetOnestore()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetOnestore()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetOnestore()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetKakao()) {
		m_TotalAmountModel->setHeaderData(CalcCPDlg::CP_KAKAO + 1, Qt::Horizontal, QString::fromLocal8Bit(CPNAME_KAKAO.toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_KAKAO + 1
			, QString("%L1").arg(cpData->GetKakao()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKakao()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKakao()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetComico()) {
		m_TotalAmountModel->setHeaderData(CalcCPDlg::CP_COMICO + 1, Qt::Horizontal, QString::fromLocal8Bit(CPNAME_COMICO.toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_COMICO + 1
			, QString("%L1").arg(cpData->GetComico()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetComico()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetComico()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetTocsoda()) {
		m_TotalAmountModel->setHeaderData(CalcCPDlg::CP_TOCSODA + 1, Qt::Horizontal, QString::fromLocal8Bit(CPNAME_TOCSODA.toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_TOCSODA + 1
			, QString("%L1").arg(cpData->GetTocsoda()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetTocsoda()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetTocsoda()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetKepub()) {
		m_TotalAmountModel->setHeaderData(CalcCPDlg::CP_KEPUB + 1, Qt::Horizontal, QString::fromLocal8Bit(CPNAME_KEPUB.toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_KEPUB + 1
			, QString("%L1").arg(cpData->GetKepub()->GetTotalAmount().at(CSVKepub::STORE_ALL), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKepub()->GetCalcAmount().at(CSVKepub::STORE_ALL), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKepub()->GetAuthorAmount().at(CSVKepub::STORE_ALL), 0, 'f', 0));

		// YES24
		m_TotalAmountModel->setHeaderData(CalcCPDlg::CP_KEPUB + 2, Qt::Horizontal, QString::fromLocal8Bit("YES24"));
		SetCPTable(CalcCPDlg::CP_KEPUB + 2
			, QString("%L1").arg(cpData->GetKepub()->GetTotalAmount().at(CSVKepub::STORE_YES24), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKepub()->GetCalcAmount().at(CSVKepub::STORE_YES24), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKepub()->GetAuthorAmount().at(CSVKepub::STORE_YES24), 0, 'f', 0));
		// ALADDIN
		m_TotalAmountModel->setHeaderData(CalcCPDlg::CP_KEPUB + 3, Qt::Horizontal, QString::fromLocal8Bit("ALADDIN"));
		SetCPTable(CalcCPDlg::CP_KEPUB + 3
			, QString("%L1").arg(cpData->GetKepub()->GetTotalAmount().at(CSVKepub::STORE_ALADDIN), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKepub()->GetCalcAmount().at(CSVKepub::STORE_ALADDIN), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKepub()->GetAuthorAmount().at(CSVKepub::STORE_ALADDIN), 0, 'f', 0));
		// BANDI
		m_TotalAmountModel->setHeaderData(CalcCPDlg::CP_KEPUB + 4, Qt::Horizontal, QString::fromLocal8Bit("BANDI"));
		SetCPTable(CalcCPDlg::CP_KEPUB + 4
			, QString("%L1").arg(cpData->GetKepub()->GetTotalAmount().at(CSVKepub::STORE_BANDI), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKepub()->GetCalcAmount().at(CSVKepub::STORE_BANDI), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKepub()->GetAuthorAmount().at(CSVKepub::STORE_BANDI), 0, 'f', 0));
	}
		
	// total amount
	SetCPTable(0
		, QString("%L1").arg(m_totalAmount, 0, 'f', 0)
		, QString("%L1").arg(m_calcAmount, 0, 'f', 0)
		, QString("%L1").arg(m_authorAmount, 0, 'f', 0));

	// Add TabWidget
	if (!m_TotalView) { m_TotalView = new QTableView(); }
	m_TotalView->setModel(m_TotalAmountModel);
	AddTab(m_TotalView, "Total");

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
	int count = ui.tabTotal->count();
	for (int i = 0; i < count; i++) {
		ui.tabTotal->removeTab(i);
	}

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
