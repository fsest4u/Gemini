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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>

#include "CalcCPDlg.h"
#include "gemini_constants.h"

// The CP_TYPE and order must match.
const QStringList CP_NAME = QStringList() << "KYOBO" << "NAVER" << "RIDI" << "MUNPIA" \
							<< "MRBLUE" << "BAROBOOK" << "BOOKCUBE" << "EPYRUS" << "OEBOOK" \
							<< "ONESTORE" << "KAKAO" << "COMICO" << "TOCSODA" << "JUSTOON"  \
							<< "GOOGLE" << "KEPUB";

const int PROGRESS_BAR_MINIMUM_DURATION = 500;


CalcCPDlg::CalcCPDlg(QDialog *parent) :
	QDialog(parent)
	, m_Kyobo(NULL)
	, m_Naver(NULL)
	, m_Ridi(NULL)
	, m_Munpia(NULL)
	, m_Mrblue(NULL)
	, m_Barobook(NULL)
	, m_Bookcube(NULL)
	, m_Epyrus(NULL)
	, m_Oebook(NULL)
	, m_Onestore(NULL)
	, m_Kakao(NULL)
	, m_Comico(NULL)
	, m_Tocsoda(NULL)
	, m_Justoon(NULL)
	, m_Google(NULL)
	, m_Kepub(NULL)

{
	ui.setupUi(this);

	InitUI();

	m_CPFileList.clear();
}

CalcCPDlg::~CalcCPDlg()
{
	DeleteKyobo();
	DeleteNaver();
	DeleteRidi();
	DeleteMunpia();
	DeleteMrblue();
	DeleteBarobook();
	DeleteBookcube();
	DeleteEpyrus();
	DeleteOebook();
	DeleteOnestore();
	DeleteKakao();
	DeleteComico();
	DeleteTocsoda();
	DeleteJustoon();
	DeleteGoogle();
	DeleteKepub();

}

void CalcCPDlg::InitUI()
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

}

void CalcCPDlg::connectSignalsSlots()
{
	// prev button
	connect(ui.buttonBox->button(QDialogButtonBox::Yes), SIGNAL(clicked()), this, SLOT(Prev()));
	// calc button
	connect(ui.buttonBox->button(QDialogButtonBox::Retry), SIGNAL(clicked()), this, SLOT(ReCalcCP()));
	// next button
	connect(ui.buttonBox->button(QDialogButtonBox::No), SIGNAL(clicked()), this, SLOT(Next()));

}

void CalcCPDlg::Prev()
{
	this->done(QDialogButtonBox::YesRole);
}

void CalcCPDlg::ReCalcCP()
{
	//qDebug() << "[ReCalcCP] -----";
	// Delete and draw new
	ui.tabCP->clear();

	this->done(QDialogButtonBox::HelpRole);
}

void CalcCPDlg::Next()
{
	this->done(QDialogButtonBox::NoRole);
}

bool CalcCPDlg::SetCP(QHash<int, QString>& cpFileList)
{
	//qDebug() << "[SetCP]";
	m_CPFileList = cpFileList;
	// for debug
	//foreach(const int key, m_CPFileList.keys()) {
	//	qDebug() << "[SetCP] key : " << key << ", value : " << m_CPFileList.value(key);
	//}

	// Delete and draw new
	int count = ui.tabCP->count();
	for (int i = 0; i < count; i++) {
		ui.tabCP->removeTab(i);
	}

	QApplication::setOverrideCursor(Qt::WaitCursor);

	if (!CalcKyobo()) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("Check the %1 file.").arg(CP_NAME.at(CP_KYOBO)));

		QApplication::restoreOverrideCursor();
		return false;
	}
	if (!CalcNaver()) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("Check the %1 file.").arg(CP_NAME.at(CP_NAVER)));

		QApplication::restoreOverrideCursor();
		return false;
	}
	if (!CalcRidi()) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("Check the %1 file.").arg(CP_NAME.at(CP_RIDI)));

		QApplication::restoreOverrideCursor();
		return false;
	}
	if (!CalcMunpia()) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("Check the %1 file.").arg(CP_NAME.at(CP_MUNPIA)));

		QApplication::restoreOverrideCursor();
		return false;
	}
	if (!CalcMrblue()) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("Check the %1 file.").arg(CP_NAME.at(CP_MRBLUE)));

		QApplication::restoreOverrideCursor();
		return false;
	}
	if (!CalcBarobook()) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("Check the %1 file.").arg(CP_NAME.at(CP_BAROBOOK)));

		QApplication::restoreOverrideCursor();
		return false;
	}
	if (!CalcBookcube()) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("Check the %1 file.").arg(CP_NAME.at(CP_BOOKCUBE)));

		QApplication::restoreOverrideCursor();
		return false;
	}
	if (!CalcEpyrus()) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("Check the %1 file.").arg(CP_NAME.at(CP_EPYRUS)));

		QApplication::restoreOverrideCursor();
		return false;
	}
	if (!CalcOebook()) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("Check the %1 file.").arg(CP_NAME.at(CP_OEBOOK)));

		QApplication::restoreOverrideCursor();
		return false;
	}
	if (!CalcOnestore()) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("Check the %1 file.").arg(CP_NAME.at(CP_ONESTORE)));

		QApplication::restoreOverrideCursor();
		return false;
	}
	if (!CalcKakao()) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("Check the %1 file.").arg(CP_NAME.at(CP_KAKAO)));

		QApplication::restoreOverrideCursor();
		return false;
	}
	if (!CalcComico()) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("Check the %1 file.").arg(CP_NAME.at(CP_COMICO)));

		QApplication::restoreOverrideCursor();
		return false;
	}
	if (!CalcTocsoda()) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("Check the %1 file.").arg(CP_NAME.at(CP_TOCSODA)));

		QApplication::restoreOverrideCursor();
		return false;
	}
	if (!CalcJustoon()) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("Check the %1 file.").arg(CP_NAME.at(CP_JUSTOON)));

		QApplication::restoreOverrideCursor();
		return false;
	}
	if (!CalcGoogle()) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("Check the %1 file.").arg(CP_NAME.at(CP_GOOGLE)));

		QApplication::restoreOverrideCursor();
		return false;
	}
	if (!CalcKepub()) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("Check the %1 file.").arg(CP_NAME.at(CP_KEPUB)));

		QApplication::restoreOverrideCursor();
		return false;
	}

	QApplication::restoreOverrideCursor();

	return true;
}

bool CalcCPDlg::CalcKyobo()
{
	if (m_CPFileList.value(CP_KYOBO).isEmpty()) { return true; }

	if (!m_Kyobo) { m_Kyobo = new CSVKyobo(); }
	if (!m_Kyobo->ReadFile(m_CPFileList.value(CP_KYOBO))) { return false; }
	m_Kyobo->SetItem();

	QList<double> total = m_Kyobo->GetTotalAmount();
	QList<double> calculator = m_Kyobo->GetCalcAmount();
	QList<double> author = m_Kyobo->GetAuthorAmount();

	QTableView* view = m_Kyobo->GetView();
	//AddTab4ListLabel(view, CP_NAME.at(CP_KYOBO), total, calculator, author);
	AddTab(view, CP_NAME.at(CP_KYOBO));

	return true;
}

bool CalcCPDlg::CalcNaver()
{
	if (m_CPFileList.value(CP_NAVER).isEmpty()) { return true; }

	if (!m_Naver) { m_Naver = new CSVNaver(); }
	if (!m_Naver->ReadFile(m_CPFileList.value(CP_NAVER))) { return false; }
	m_Naver->SetItem();

	double total = m_Naver->GetTotalAmount();
	double calculator = m_Naver->GetCalcAmount();
	double author = m_Naver->GetAuthorAmount();

	QTableView* view = m_Naver->GetView();
	//AddTabLabel(view, CP_NAME.at(CP_NAVER), total, calculator, author);
	AddTab(view, CP_NAME.at(CP_NAVER));

	return true;
}

bool CalcCPDlg::CalcRidi()
{
	if (m_CPFileList.value(CP_RIDI).isEmpty()) { return true; }

	if (!m_Ridi) { m_Ridi = new CSVRidi(); }
	if (!m_Ridi->ReadFile(m_CPFileList.value(CP_RIDI))) { return false; }
	m_Ridi->SetItem();

	double total = m_Ridi->GetTotalAmount();
	double calculator = m_Ridi->GetCalcAmount();
	double author = m_Ridi->GetAuthorAmount();

	QTableView* view = m_Ridi->GetView();
	//AddTabLabel(view, CP_NAME.at(CP_RIDI), total, calculator, author);
	AddTab(view, CP_NAME.at(CP_RIDI));

	return true;
}

bool CalcCPDlg::CalcMunpia()
{
	if (m_CPFileList.value(CP_MUNPIA).isEmpty()) { return true; }

	if (!m_Munpia) { m_Munpia = new CSVMunpia(); }
	if (!m_Munpia->ReadFile(m_CPFileList.value(CP_MUNPIA))) { return false; }
	m_Munpia->SetItem();

	double total = m_Munpia->GetTotalAmount();
	double calculator = m_Munpia->GetCalcAmount();
	double author = m_Munpia->GetAuthorAmount();

	QTableView* view = m_Munpia->GetView();
	//AddTabLabel(view, CP_NAME.at(CP_MUNPIA), total, calculator, author);
	AddTab(view, CP_NAME.at(CP_MUNPIA));

	return true;
}

bool CalcCPDlg::CalcMrblue()
{
	if (m_CPFileList.value(CP_MRBLUE).isEmpty()) { return true; }

	if (!m_Mrblue) { m_Mrblue = new CSVMrblue(); }
	if (!m_Mrblue->ReadFile(m_CPFileList.value(CP_MRBLUE))) { return false; }
	m_Mrblue->SetItem();

	double total = m_Mrblue->GetTotalAmount();
	double calculator = m_Mrblue->GetCalcAmount();
	double author = m_Mrblue->GetAuthorAmount();

	QTableView* view = m_Mrblue->GetView();
	//AddTabLabel(view, CP_NAME.at(CP_MRBLUE), total, calculator, author);
	AddTab(view, CP_NAME.at(CP_MRBLUE));

	return true;
}

bool CalcCPDlg::CalcBarobook()
{
	if (m_CPFileList.value(CP_BAROBOOK).isEmpty()) { return true; }

	if (!m_Barobook) { m_Barobook = new CSVBarobook(); }
	if (!m_Barobook->ReadFile(m_CPFileList.value(CP_BAROBOOK))) { return false; }
	m_Barobook->SetItem();

	double total = m_Barobook->GetTotalAmount();
	double calculator = m_Barobook->GetCalcAmount();
	double author = m_Barobook->GetAuthorAmount();

	QTableView* view = m_Barobook->GetView();
	//AddTabLabel(view, CP_NAME.at(CP_BAROBOOK), total, calculator, author);
	AddTab(view, CP_NAME.at(CP_BAROBOOK));

	return true;
}

bool CalcCPDlg::CalcBookcube()
{
	if (m_CPFileList.value(CP_BOOKCUBE).isEmpty()) { return true; }

	if (!m_Bookcube) { m_Bookcube = new CSVBookcube(); }
	if (!m_Bookcube->ReadFile(m_CPFileList.value(CP_BOOKCUBE))) { return false; }
	m_Bookcube->SetItem();

	double total = m_Bookcube->GetTotalAmount();
	double calculator = m_Bookcube->GetCalcAmount();
	double author = m_Bookcube->GetAuthorAmount();

	QTableView* view = m_Bookcube->GetView();
	//AddTabLabel(view, CP_NAME.at(CP_BOOKCUBE), total, calculator, author);
	AddTab(view, CP_NAME.at(CP_BOOKCUBE));

	return true;
}

bool CalcCPDlg::CalcEpyrus()
{
	if (m_CPFileList.value(CP_EPYRUS).isEmpty()) { return true; }

	if (!m_Epyrus) { m_Epyrus = new CSVEpyrus(); }
	if (!m_Epyrus->ReadFile(m_CPFileList.value(CP_EPYRUS))) { return false; }
	m_Epyrus->SetItem();

	double total = m_Epyrus->GetTotalAmount();
	double calculator = m_Epyrus->GetCalcAmount();
	double author = m_Epyrus->GetAuthorAmount();

	QTableView* view = m_Epyrus->GetView();
	//AddTabLabel(view, CP_NAME.at(CP_EPYRUS), total, calculator, author);
	AddTab(view, CP_NAME.at(CP_EPYRUS));

	return true;
}

bool CalcCPDlg::CalcOebook()
{
	if (m_CPFileList.value(CP_OEBOOK).isEmpty()) { return true; }

	if (!m_Oebook) { m_Oebook = new CSVOebook(); }
	if (!m_Oebook->ReadFile(m_CPFileList.value(CP_OEBOOK))) { return false; }
	m_Oebook->SetItem();

	QList<double> total = m_Oebook->GetTotalAmount();
	QList<double> calculator = m_Oebook->GetCalcAmount();
	QList<double> author = m_Oebook->GetAuthorAmount();

	QTableView* view = m_Oebook->GetView();
	//AddTab4ListLabel(view, CP_NAME.at(CP_OEBOOK), total, calculator, author);
	AddTab(view, CP_NAME.at(CP_OEBOOK));

	return true;
}

bool CalcCPDlg::CalcOnestore()
{
	if (m_CPFileList.value(CP_ONESTORE).isEmpty()) { return true; }

	if (!m_Onestore) { m_Onestore = new CSVOnestore(); }
	if (!m_Onestore->ReadFile(m_CPFileList.value(CP_ONESTORE))) { return false; }
	m_Onestore->SetItem();

	double total = m_Onestore->GetTotalAmount();
	double calculator = m_Onestore->GetCalcAmount();
	double author = m_Onestore->GetAuthorAmount();

	QTableView* view = m_Onestore->GetView();
	//AddTabLabel(view, CP_NAME.at(CP_ONESTORE), total, calculator, author);
	AddTab(view, CP_NAME.at(CP_ONESTORE));

	return true;
}

bool CalcCPDlg::CalcKakao()
{
	if (m_CPFileList.value(CP_KAKAO).isEmpty()) { return true; }

	if (!m_Kakao) { m_Kakao = new CSVKakao(); }
	if (!m_Kakao->ReadFile(m_CPFileList.value(CP_KAKAO))) { return false; }
	m_Kakao->SetItem();

	double total = m_Kakao->GetTotalAmount();
	double calculator = m_Kakao->GetCalcAmount();
	double author = m_Kakao->GetAuthorAmount();

	QTableView* view = m_Kakao->GetView();
	//AddTabLabel(view, CP_NAME.at(CP_KAKAO), total, calculator, author);
	AddTab(view, CP_NAME.at(CP_KAKAO));

	return true;
}

bool CalcCPDlg::CalcComico()
{
	if (m_CPFileList.value(CP_COMICO).isEmpty()) { return true; }

	if (!m_Comico) { m_Comico = new CSVComico(); }
	if (!m_Comico->ReadFile(m_CPFileList.value(CP_COMICO))) { return false; }
	m_Comico->SetItem();

	double total = m_Comico->GetTotalAmount();
	double calculator = m_Comico->GetCalcAmount();
	double author = m_Comico->GetAuthorAmount();

	QTableView* view = m_Comico->GetView();
	//AddTabLabel(view, CP_NAME.at(CP_COMICO), total, calculator, author);
	AddTab(view, CP_NAME.at(CP_COMICO));

	return true;
}

bool CalcCPDlg::CalcTocsoda()
{
	if (m_CPFileList.value(CP_TOCSODA).isEmpty()) { return true; }

	if (!m_Tocsoda) { m_Tocsoda = new CSVTocsoda(); }
	if (!m_Tocsoda->ReadFile(m_CPFileList.value(CP_TOCSODA))) { return false; }
	m_Tocsoda->SetItem();

	double total = m_Tocsoda->GetTotalAmount();
	double calculator = m_Tocsoda->GetCalcAmount();
	double author = m_Tocsoda->GetAuthorAmount();

	QTableView* view = m_Tocsoda->GetView();
	//AddTabLabel(view, CP_NAME.at(CP_TOCSODA), total, calculator, author);
	AddTab(view, CP_NAME.at(CP_TOCSODA));

	return true;
}

bool CalcCPDlg::CalcJustoon()
{
	if (m_CPFileList.value(CP_JUSTOON).isEmpty()) { return true; }

	if (!m_Justoon) { m_Justoon = new CSVJustoon(); }
	if (!m_Justoon->ReadFile(m_CPFileList.value(CP_JUSTOON))) { return false; }
	m_Justoon->SetItem();

	double total = m_Justoon->GetTotalAmount();
	double calculator = m_Justoon->GetCalcAmount();
	double author = m_Justoon->GetAuthorAmount();

	QTableView* view = m_Justoon->GetView();
	AddTab(view, CP_NAME.at(CP_JUSTOON));

	return true;
}

bool CalcCPDlg::CalcGoogle()
{
	if (m_CPFileList.value(CP_GOOGLE).isEmpty()) { return true; }

	if (!m_Google) { m_Google = new CSVGoogle(); }
	if (!m_Google->ReadFile(m_CPFileList.value(CP_GOOGLE))) { return false; }
	m_Google->SetItem();

	double total = m_Google->GetTotalAmount();
	double calculator = m_Google->GetCalcAmount();
	double author = m_Google->GetAuthorAmount();

	QTableView* view = m_Google->GetView();
	AddTab(view, CP_NAME.at(CP_GOOGLE));

	return true;
}

bool CalcCPDlg::CalcKepub()
{
	if (m_CPFileList.value(CP_KEPUB).isEmpty()) { return true; }

	if (!m_Kepub) { m_Kepub = new CSVKepub(); }
	if (!m_Kepub->ReadFile(m_CPFileList.value(CP_KEPUB))) { return false; }
	m_Kepub->SetItem();

	QList<double> total = m_Kepub->GetTotalAmount();
	QList<double> calculator = m_Kepub->GetCalcAmount();
	QList<double> author = m_Kepub->GetAuthorAmount();

	QTableView* view = m_Kepub->GetView();
	//AddTab4ListLabel(view, CP_NAME.at(CP_KEPUB), total, calculator, author);
	AddTab(view, CP_NAME.at(CP_KEPUB));

	return true;
}

void CalcCPDlg::DeleteKyobo()
{
	if (m_Kyobo) {
		delete m_Kyobo;
		m_Kyobo = 0;
	}
}

void CalcCPDlg::DeleteNaver()
{
	if (m_Naver) {
		delete m_Naver;
		m_Naver = 0;
	}
}

void CalcCPDlg::DeleteRidi()
{
	if (m_Ridi) {
		delete m_Ridi;
		m_Ridi = 0;
	}
}

void CalcCPDlg::DeleteMunpia()
{
	if (m_Munpia) {
		delete m_Munpia;
		m_Munpia = 0;
	}
}

void CalcCPDlg::DeleteMrblue()
{
	if (m_Mrblue) {
		delete m_Mrblue;
		m_Mrblue = 0;
	}
}

void CalcCPDlg::DeleteBarobook()
{
	if (m_Barobook) {
		delete m_Barobook;
		m_Barobook = 0;
	}
}

void CalcCPDlg::DeleteBookcube()
{
	if (m_Bookcube) {
		delete m_Bookcube;
		m_Bookcube = 0;
	}
}

void CalcCPDlg::DeleteEpyrus()
{
	if (m_Epyrus) {
		delete m_Epyrus;
		m_Epyrus = 0;
	}
}

void CalcCPDlg::DeleteOebook()
{
	if (m_Oebook) {
		delete m_Oebook;
		m_Oebook = 0;
	}
}

void CalcCPDlg::DeleteOnestore()
{
	if (m_Onestore) {
		delete m_Onestore;
		m_Onestore = 0;
	}
}

void CalcCPDlg::DeleteKakao()
{
	if (m_Kakao) {
		delete m_Kakao;
		m_Kakao = 0;
	}
}

void CalcCPDlg::DeleteComico()
{
	if (m_Comico) {
		delete m_Comico;
		m_Comico = 0;
	}
}

void CalcCPDlg::DeleteTocsoda()
{
	if (m_Tocsoda) {
		delete m_Tocsoda;
		m_Tocsoda = 0;
	}
}

void CalcCPDlg::DeleteJustoon()
{
	if (m_Justoon) {
		delete m_Justoon;
		m_Justoon = 0;
	}
}

void CalcCPDlg::DeleteGoogle()
{
	if (m_Google) {
		delete m_Google;
		m_Google = 0;
	}
}

void CalcCPDlg::DeleteKepub()
{
	if (m_Kepub) {
		delete m_Kepub;
		m_Kepub = 0;
	}
}

void CalcCPDlg::AddTab(QTableView* table, const QString cpName)
{
	//qDebug() << "[CalcCPDlg AddTab] - " << cpName;
	// Draw Widget
	QGridLayout* defalutLayout = new QGridLayout();
	defalutLayout->addWidget(table);

	QWidget* defaultWidget = new QWidget();
	defaultWidget->setLayout(defalutLayout);

	ui.tabCP->addTab(defaultWidget, cpName);

}

// no_use
void CalcCPDlg::AddTabLabel(QTableView* table, const QString cpName, double total, double calculator, double author)
{
	//qDebug() << "[CalcCPDlg AddTabLabel] - " << cpName;
	// Draw Widget
	QLabel* totalLabel = new QLabel(QString("Total Amount : %L1").arg(total, 0, 'f', 0));
	QLabel* calcLabel = new QLabel(QString("Calculate Amount : %L1").arg(calculator, 0, 'f', 0));
	QLabel* authorLabel = new QLabel(QString("Author Amount : %L1").arg(author, 0, 'f', 0));

	QGridLayout* defalutLayout = new QGridLayout();
	defalutLayout->addWidget(totalLabel);
	defalutLayout->addWidget(calcLabel);
	defalutLayout->addWidget(authorLabel);
	defalutLayout->addWidget(table);

	QWidget* defaultWidget = new QWidget();
	defaultWidget->setLayout(defalutLayout);

	ui.tabCP->addTab(defaultWidget, cpName);

}
// no_use
void CalcCPDlg::AddTab4ListLabel(QTableView* table, const QString cpName, QList<double> total, QList<double> calculator, QList<double> author)
{
	//qDebug() << "[CalcCPDlg AddTab4ListLabel] - " << cpName;
	QGridLayout* defalutLayout = new QGridLayout();
	QHBoxLayout* totalLayout = new QHBoxLayout();
	QHBoxLayout* calcLayout = new QHBoxLayout();
	QHBoxLayout* authorLayout = new QHBoxLayout();
	// kyobo
	if (!cpName.compare(CP_NAME.at(CP_KYOBO))) {

		QLabel* totalAll = new QLabel(QString("Total Amount : %L1").arg(total.at(CSVKyobo::BUSINESS_ALL), 0, 'f', 0));
		QLabel* calcAll = new QLabel(QString("Calculate Amount : %L1").arg(calculator.at(CSVKyobo::BUSINESS_ALL), 0, 'f', 0));
		QLabel* authorAll = new QLabel(QString("Author Amount : %L1").arg(author.at(CSVKyobo::BUSINESS_ALL), 0, 'f', 0));

		QLabel* totalB2C = new QLabel(QString("Total B2C : %L1").arg(total.at(CSVKyobo::BUSINESS_B2C), 0, 'f', 0));
		QLabel* calcB2C = new QLabel(QString("Calculate B2C : %L1").arg(calculator.at(CSVKyobo::BUSINESS_B2C), 0, 'f', 0));
		QLabel* authorB2C = new QLabel(QString("Author B2C : %L1").arg(author.at(CSVKyobo::BUSINESS_B2C), 0, 'f', 0));

		QLabel* totalB2BC = new QLabel(QString("Total B2BC : %L1").arg(total.at(CSVKyobo::BUSINESS_B2BC), 0, 'f', 0));
		QLabel* calcB2BC = new QLabel(QString("Calculate B2BC : %L1").arg(calculator.at(CSVKyobo::BUSINESS_B2BC), 0, 'f', 0));
		QLabel* authorB2BC = new QLabel(QString("Author B2BC : %L1").arg(author.at(CSVKyobo::BUSINESS_B2BC), 0, 'f', 0));

		totalLayout->addWidget(totalAll);
		totalLayout->addWidget(totalB2C);
		totalLayout->addWidget(totalB2BC);

		calcLayout->addWidget(calcAll);
		calcLayout->addWidget(calcB2C);
		calcLayout->addWidget(calcB2BC);

		authorLayout->addWidget(authorAll);
		authorLayout->addWidget(authorB2C);
		authorLayout->addWidget(authorB2BC);

	}
	// oebook
	else if (!cpName.compare(CP_NAME.at(CP_OEBOOK))) {

		QLabel* totalAll = new QLabel(QString("Total Amount : %L1").arg(total.at(CSVOebook::COMPANY_OEBOOK_ALL), 0, 'f', 0));
		QLabel* calcAll = new QLabel(QString("Calculate Amount : %L1").arg(calculator.at(CSVOebook::COMPANY_OEBOOK_ALL), 0, 'f', 0));
		QLabel* authorAll = new QLabel(QString("Author Amount : %L1").arg(author.at(CSVOebook::COMPANY_OEBOOK_ALL), 0, 'f', 0));

		QLabel* totalOebook = new QLabel(QString("Total Oebook : %L1").arg(total.at(CSVOebook::COMPANY_OEBOOK), 0, 'f', 0));
		QLabel* calcOebook = new QLabel(QString("Calculate Oebook : %L1").arg(calculator.at(CSVOebook::COMPANY_OEBOOK), 0, 'f', 0));
		QLabel* authorOebook = new QLabel(QString("Author Oebook : %L1").arg(author.at(CSVOebook::COMPANY_OEBOOK), 0, 'f', 0));

		QLabel* totalOebookRomance = new QLabel(QString("Total Oebook Romance: %L1").arg(total.at(CSVOebook::COMPANY_OEBOOK_ROMANCE), 0, 'f', 0));
		QLabel* calcOebookRomance = new QLabel(QString("Calculate Oebook Romance: %L1").arg(calculator.at(CSVOebook::COMPANY_OEBOOK_ROMANCE), 0, 'f', 0));
		QLabel* authorOebookRomance = new QLabel(QString("Author Oebook Romance: %L1").arg(author.at(CSVOebook::COMPANY_OEBOOK_ROMANCE), 0, 'f', 0));

		QLabel* totalOebookMurim = new QLabel(QString("Total Oebook Murim: %L1").arg(total.at(CSVOebook::COMPANY_OEBOOK_MURIM), 0, 'f', 0));
		QLabel* calcOebookMurim = new QLabel(QString("Calculate Oebook Murim: %L1").arg(calculator.at(CSVOebook::COMPANY_OEBOOK_MURIM), 0, 'f', 0));
		QLabel* authorOebookMurim = new QLabel(QString("Author Oebook Murim: %L1").arg(author.at(CSVOebook::COMPANY_OEBOOK_MURIM), 0, 'f', 0));

		QLabel* totalOebookComic = new QLabel(QString("Total Oebook Comic: %L1").arg(total.at(CSVOebook::COMPANY_OEBOOK_COMIC), 0, 'f', 0));
		QLabel* calcOebookComic = new QLabel(QString("Calculate Oebook Comic: %L1").arg(calculator.at(CSVOebook::COMPANY_OEBOOK_COMIC), 0, 'f', 0));
		QLabel* authorOebookComic = new QLabel(QString("Author Oebook Comic: %L1").arg(author.at(CSVOebook::COMPANY_OEBOOK_COMIC), 0, 'f', 0));

		totalLayout->addWidget(totalAll);
		totalLayout->addWidget(totalOebook);
		totalLayout->addWidget(totalOebookRomance);
		totalLayout->addWidget(totalOebookMurim);
		totalLayout->addWidget(totalOebookComic);

		calcLayout->addWidget(calcAll);
		calcLayout->addWidget(calcOebook);
		calcLayout->addWidget(calcOebookRomance);
		calcLayout->addWidget(calcOebookMurim);
		calcLayout->addWidget(calcOebookComic);

		authorLayout->addWidget(authorAll);
		authorLayout->addWidget(authorOebook);
		authorLayout->addWidget(authorOebookRomance);
		authorLayout->addWidget(authorOebookMurim);
		authorLayout->addWidget(authorOebookComic);

	}
	// kepub
	else if (!cpName.compare(CP_NAME.at(CP_KEPUB))) {

		QLabel* totalAll = new QLabel(QString("Total Amount : %L1").arg(total.at(CSVKepub::STORE_ALL), 0, 'f', 0));
		QLabel* calcAll = new QLabel(QString("Calculate Amount : %L1").arg(calculator.at(CSVKepub::STORE_ALL), 0, 'f', 0));
		QLabel* authorAll = new QLabel(QString("Author Amount : %L1").arg(author.at(CSVKepub::STORE_ALL), 0, 'f', 0));

		QLabel* totalYES24 = new QLabel(QString("Total YES24 : %L1").arg(total.at(CSVKepub::STORE_YES24), 0, 'f', 0));
		QLabel* calcYES24 = new QLabel(QString("Calculate YES24 : %L1").arg(calculator.at(CSVKepub::STORE_YES24), 0, 'f', 0));
		QLabel* authorYES24 = new QLabel(QString("Author YES24 : %L1").arg(author.at(CSVKepub::STORE_YES24), 0, 'f', 0));

		QLabel* totalAladdin = new QLabel(QString("Total Aladdin: %L1").arg(total.at(CSVKepub::STORE_ALADDIN), 0, 'f', 0));
		QLabel* calcAladdin = new QLabel(QString("Calculate Aladdin: %L1").arg(calculator.at(CSVKepub::STORE_ALADDIN), 0, 'f', 0));
		QLabel* authorAladdin = new QLabel(QString("Author Aladdin: %L1").arg(author.at(CSVKepub::STORE_ALADDIN), 0, 'f', 0));

		QLabel* totalBandi= new QLabel(QString("Total BandinLunis: %L1").arg(total.at(CSVKepub::STORE_BANDI), 0, 'f', 0));
		QLabel* calcBandi = new QLabel(QString("Calculate BandinLunis: %L1").arg(calculator.at(CSVKepub::STORE_BANDI), 0, 'f', 0));
		QLabel* authorBandi = new QLabel(QString("Author BandinLunis: %L1").arg(author.at(CSVKepub::STORE_BANDI), 0, 'f', 0));

		totalLayout->addWidget(totalAll);
		totalLayout->addWidget(totalYES24);
		totalLayout->addWidget(totalAladdin);
		totalLayout->addWidget(totalBandi);

		calcLayout->addWidget(calcAll);
		calcLayout->addWidget(calcYES24);
		calcLayout->addWidget(calcAladdin);
		calcLayout->addWidget(calcBandi);

		authorLayout->addWidget(authorAll);
		authorLayout->addWidget(authorYES24);
		authorLayout->addWidget(authorAladdin);
		authorLayout->addWidget(authorBandi);

	}

	defalutLayout->addLayout(totalLayout, 0, 0);
	defalutLayout->addLayout(calcLayout, 1, 0);
	defalutLayout->addLayout(authorLayout, 2, 0);

	defalutLayout->addWidget(table);

	QWidget* defaultWidget = new QWidget();
	defaultWidget->setLayout(defalutLayout);

	ui.tabCP->addTab(defaultWidget, cpName);

}

bool CalcCPDlg::ExtractCSV(QString lastFolderOpen)
{
	QApplication::setOverrideCursor(Qt::WaitCursor);

	QString temp;
	if (m_Kyobo) {
		temp = lastFolderOpen + "\\" + CP_NAME.at(CalcCPDlg::CP_KYOBO) + ".csv";
		m_Kyobo->WriteFile(temp);
	}
	if (m_Naver) {
		temp = lastFolderOpen + "\\" + CP_NAME.at(CalcCPDlg::CP_NAVER) + ".csv";
		m_Naver->WriteFile(temp);
	}
	if (m_Ridi) {
		temp = lastFolderOpen + "\\" + CP_NAME.at(CalcCPDlg::CP_RIDI) + ".csv";
		m_Ridi->WriteFile(temp);
	}
	if (m_Munpia) {
		temp = lastFolderOpen + "\\" + CP_NAME.at(CalcCPDlg::CP_MUNPIA) + ".csv";
		m_Munpia->WriteFile(temp);
	}
	if (m_Mrblue) {
		temp = lastFolderOpen + "\\" + CP_NAME.at(CalcCPDlg::CP_MRBLUE) + ".csv";
		m_Mrblue->WriteFile(temp);
	}
	if (m_Barobook) {
		temp = lastFolderOpen + "\\" + CP_NAME.at(CalcCPDlg::CP_BAROBOOK) + ".csv";
		m_Barobook->WriteFile(temp);
	}
	if (m_Bookcube) {
		temp = lastFolderOpen + "\\" + CP_NAME.at(CalcCPDlg::CP_BOOKCUBE) + ".csv";
		m_Bookcube->WriteFile(temp);
	}
	if (m_Epyrus) {
		temp = lastFolderOpen + "\\" + CP_NAME.at(CalcCPDlg::CP_EPYRUS) + ".csv";
		m_Epyrus->WriteFile(temp);
	}
	if (m_Oebook) {
		temp = lastFolderOpen + "\\" + CP_NAME.at(CalcCPDlg::CP_OEBOOK) + ".csv";
		m_Oebook->WriteFile(temp);
	}
	if (m_Onestore) {
		temp = lastFolderOpen + "\\" + CP_NAME.at(CalcCPDlg::CP_ONESTORE) + ".csv";
		m_Onestore->WriteFile(temp);
	}
	if (m_Kakao) {
		temp = lastFolderOpen + "\\" + CP_NAME.at(CalcCPDlg::CP_KAKAO) + ".csv";
		m_Kakao->WriteFile(temp);
	}
	if (m_Comico) {
		temp = lastFolderOpen + "\\" + CP_NAME.at(CalcCPDlg::CP_COMICO) + ".csv";
		m_Comico->WriteFile(temp);
	}
	if (m_Tocsoda) {
		temp = lastFolderOpen + "\\" + CP_NAME.at(CalcCPDlg::CP_TOCSODA) + ".csv";
		m_Tocsoda->WriteFile(temp);
	}
	if (m_Justoon) {
		temp = lastFolderOpen + "\\" + CP_NAME.at(CalcCPDlg::CP_JUSTOON) + ".csv";
		m_Justoon->WriteFile(temp);
	}
	if (m_Google) {
		temp = lastFolderOpen + "\\" + CP_NAME.at(CalcCPDlg::CP_GOOGLE) + ".csv";
		m_Google->WriteFile(temp);
	}
	if (m_Kepub) {
		temp = lastFolderOpen + "\\" + CP_NAME.at(CalcCPDlg::CP_KEPUB) + ".csv";
		m_Kepub->WriteFile(temp);
	}

	QApplication::restoreOverrideCursor();
	return true;
}