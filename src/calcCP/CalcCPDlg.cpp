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

#include "CalcCPDlg.h"
#include "gemini_constants.h"


const QString CPNAME_KYOBO = "KYOBO";
const QString CPNAME_NAVER = "NAVER";
const QString CPNAME_RIDI = "RIDI";
const QString CPNAME_MUNPIA = "MUNPIA";
const QString CPNAME_MRBLUE = "MRBLUE";
const QString CPNAME_BAROBOOK = "BAROBOOK";
const QString CPNAME_BOOKCUBE = "BOOKCUBE";
const QString CPNAME_EPYRUS = "EPYRUS";
const QString CPNAME_OEBOOK = "OEBOOK";
const QString CPNAME_ONESTORE = "ONESTORE";
const QString CPNAME_KAKAO = "KAKAO";
const QString CPNAME_COMICO = "COMICO";
const QString CPNAME_TOCSODA = "TOCSODA";
const QString CPNAME_KEPUB = "KEPUB";

const int PROGRESS_BAR_MINIMUM_DURATION = 500;


CalcCPDlg::CalcCPDlg(QDialog *parent) :
	QDialog(parent)
	, m_Kyobo(NULL)
	, m_Naver(NULL)
	, m_Ridi(NULL)
	, m_Munpia(NULL)
	, m_Mrblue(NULL)
	, m_Barabook(NULL)
	, m_Bookcube(NULL)
	, m_Epyrus(NULL)
	, m_Oebook(NULL)
	, m_Onestore(NULL)
	, m_Kakao(NULL)
	, m_Comico(NULL)
	, m_Tocsoda(NULL)
	, m_Kepub(NULL)
	, m_KyoboView(NULL)
	, m_NaverView(NULL)
	, m_RidiView(NULL)
	, m_MunpiaView(NULL)
	, m_MrblueView(NULL)
	, m_BarobookView(NULL)
	, m_BookcubeView(NULL)
	, m_EpyrusView(NULL)
	, m_OebookView(NULL)
	, m_OnestoreView(NULL)
	, m_KakaoView(NULL)
	, m_ComicoView(NULL)
	, m_TocsodaView(NULL)
	, m_KepubView(NULL)
	, m_Progress(NULL)

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
	DeleteKepub();

	if (m_Progress) {
		delete m_Progress;
		m_Progress = NULL;
	}

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
	qDebug() << "[CalcCP] -----";
	// Delete and draw new
	int count = ui.tabCP->count();
	for (int i = 0; i < count; i++) {
		ui.tabCP->removeTab(i);
	}

	QApplication::setOverrideCursor(Qt::WaitCursor);
	//CalcKyobo();
	//CalcNaver();
	//CalcRidi();
	//CalcMunpia();
	//CalcMrblue();
	//CalcBarobook();
	//CalcBookcube();
	//CalcEpyrus();
	//CalcOebook();
	//CalcOnestore();
	//CalcKakao();
	//CalcComico();
	//CalcTocsoda();
	//CalcKepub();

	QApplication::restoreOverrideCursor();
	this->done(QDialogButtonBox::HelpRole);
}

void CalcCPDlg::Next()
{
	this->done(QDialogButtonBox::NoRole);
}

void CalcCPDlg::SetCP(QHash<int, QString>& cpFileList)
{
	qDebug() << "[SetCP]";
	m_CPFileList = cpFileList;
	// for debug
	//foreach(const int key, m_CPFileList.keys()) {
	//	qDebug() << "[SetCPFileList] key : " << key << ", value : " << m_CPFileList.value(key);
	//}

	if (m_Progress) {
		delete m_Progress;
		m_Progress = NULL;
	}
	m_Progress = new QProgressDialog(this);
	m_Progress->setMinimumDuration(PROGRESS_BAR_MINIMUM_DURATION);
	m_Progress->setMinimum(CP_KYOBO);
	m_Progress->setMaximum(CP_KEPUB);
	m_Progress->setValue(0);
	m_Progress->setAutoClose(true);

	// Delete and draw new
	int count = ui.tabCP->count();
	for (int i = 0; i < count; i++) {
		ui.tabCP->removeTab(i);
	}

	QApplication::setOverrideCursor(Qt::WaitCursor);

	CalcKyobo();
	CalcNaver();
	CalcRidi();
	CalcMunpia();
	CalcMrblue();
	CalcBarobook();
	CalcBookcube();
	CalcEpyrus();
	CalcOebook();
	CalcOnestore();
	CalcKakao();
	CalcComico();
	CalcTocsoda();
	CalcKepub();

	m_Progress->accept();
	QApplication::restoreOverrideCursor();

}

void CalcCPDlg::CalcKyobo()
{
	m_Progress->setLabelText(QString("Calculate %1 Data ...").arg(CPNAME_KYOBO));
	m_Progress->setValue(CP_KYOBO);
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

	if (m_CPFileList.value(CP_KYOBO).isEmpty()) { return; }

	if (!m_Kyobo) { m_Kyobo = new CSVKyobo(); }
	m_Kyobo->ReadFile(m_CPFileList.value(CP_KYOBO));
	m_Kyobo->SetItem();

	QList<double> total = m_Kyobo->GetTotalAmount();
	QList<double> calculator = m_Kyobo->GetCalcAmount();
	QList<double> author = m_Kyobo->GetAuthorAmount();

	if (!m_KyoboView) { m_KyoboView = new QTableView(); }
	m_KyoboView->setModel(m_Kyobo->GetItem());

	AddTab4List(m_KyoboView, CPNAME_KYOBO, total, calculator, author);
}

void CalcCPDlg::CalcNaver()
{
	m_Progress->setLabelText(QString("Calculate %1 Data ...").arg(CP_NAVER));
	m_Progress->setValue(CP_NAVER);
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

	if (m_CPFileList.value(CP_NAVER).isEmpty()) { return; }

	if (!m_Naver) { m_Naver = new CSVNaver(); }
	m_Naver->ReadFile(m_CPFileList.value(CP_NAVER));
	m_Naver->SetItem();

	double total = m_Naver->GetTotalAmount();
	double calculator = m_Naver->GetCalcAmount();
	double author = m_Naver->GetAuthorAmount();

	if (!m_NaverView) { m_NaverView = new QTableView(); }
	m_NaverView->setModel(m_Naver->GetItem());

	AddTab(m_NaverView, CPNAME_NAVER, total, calculator, author);
}

void CalcCPDlg::CalcRidi()
{
	m_Progress->setLabelText(QString("Calculate %1 Data ...").arg(CPNAME_RIDI));
	m_Progress->setValue(CP_RIDI);
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

	if (m_CPFileList.value(CP_RIDI).isEmpty()) { return; }

	if (!m_Ridi) { m_Ridi = new CSVRidi(); }
	m_Ridi->ReadFile(m_CPFileList.value(CP_RIDI));
	m_Ridi->SetItem();

	double total = m_Ridi->GetTotalAmount();
	double calculator = m_Ridi->GetCalcAmount();
	double author = m_Ridi->GetAuthorAmount();

	if (!m_RidiView) { m_RidiView = new QTableView(); }
	m_RidiView->setModel(m_Ridi->GetItem());

	AddTab(m_RidiView, CPNAME_RIDI, total, calculator, author);
}

void CalcCPDlg::CalcMunpia()
{
	m_Progress->setLabelText(QString("Calculate %1 Data ...").arg(CPNAME_MUNPIA));
	m_Progress->setValue(CP_MUNPIA);
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

	if (m_CPFileList.value(CP_MUNPIA).isEmpty()) { return; }

	if (!m_Munpia) { m_Munpia = new CSVMunpia(); }
	m_Munpia->ReadFile(m_CPFileList.value(CP_MUNPIA));
	m_Munpia->SetItem();

	double total = m_Munpia->GetTotalAmount();
	double calculator = m_Munpia->GetCalcAmount();
	double author = m_Munpia->GetAuthorAmount();

	if (!m_MunpiaView) { m_MunpiaView = new QTableView(); }
	m_MunpiaView->setModel(m_Munpia->GetItem());

	AddTab(m_MunpiaView, CPNAME_MUNPIA, total, calculator, author);
}

void CalcCPDlg::CalcMrblue()
{
	m_Progress->setLabelText(QString("Calculate %1 Data ...").arg(CPNAME_MRBLUE));
	m_Progress->setValue(CP_MRBLUE);
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

	if (m_CPFileList.value(CP_MRBLUE).isEmpty()) { return; }

	if (!m_Mrblue) { m_Mrblue = new CSVMrblue(); }
	m_Mrblue->ReadFile(m_CPFileList.value(CP_MRBLUE));
	m_Mrblue->SetItem();

	double total = m_Mrblue->GetTotalAmount();
	double calculator = m_Mrblue->GetCalcAmount();
	double author = m_Mrblue->GetAuthorAmount();

	if (!m_MrblueView) { m_MrblueView = new QTableView(); }
	m_MrblueView->setModel(m_Mrblue->GetItem());

	AddTab(m_MrblueView, CPNAME_MRBLUE, total, calculator, author);
}

void CalcCPDlg::CalcBarobook()
{
	m_Progress->setLabelText(QString("Calculate %1 Data ...").arg(CPNAME_BAROBOOK));
	m_Progress->setValue(CP_BAROBOOK);
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

	if (m_CPFileList.value(CP_BAROBOOK).isEmpty()) { return; }

	if (!m_Barabook) { m_Barabook = new CSVBarobook(); }
	m_Barabook->ReadFile(m_CPFileList.value(CP_BAROBOOK));
	m_Barabook->SetItem();

	double total = m_Barabook->GetTotalAmount();
	double calculator = m_Barabook->GetCalcAmount();
	double author = m_Barabook->GetAuthorAmount();

	if (!m_BarobookView) { m_BarobookView = new QTableView(); }
	m_BarobookView->setModel(m_Barabook->GetItem());

	AddTab(m_BarobookView, CPNAME_BAROBOOK, total, calculator, author);
}

void CalcCPDlg::CalcBookcube()
{
	m_Progress->setLabelText(QString("Calculate %1 Data ...").arg(CPNAME_BOOKCUBE));
	m_Progress->setValue(CP_BOOKCUBE);
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

	if (m_CPFileList.value(CP_BOOKCUBE).isEmpty()) { return; }

	if (!m_Bookcube) { m_Bookcube = new CSVBookcube(); }
	m_Bookcube->ReadFile(m_CPFileList.value(CP_BOOKCUBE));
	m_Bookcube->SetItem();

	double total = m_Bookcube->GetTotalAmount();
	double calculator = m_Bookcube->GetCalcAmount();
	double author = m_Bookcube->GetAuthorAmount();

	if (!m_BookcubeView) { m_BookcubeView = new QTableView(); }
	m_BookcubeView->setModel(m_Bookcube->GetItem());

	AddTab(m_BookcubeView, CPNAME_BOOKCUBE, total, calculator, author);
}

void CalcCPDlg::CalcEpyrus()
{
	m_Progress->setLabelText(QString("Calculate %1 Data ...").arg(CPNAME_EPYRUS));
	m_Progress->setValue(CP_EPYRUS);
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

	if (m_CPFileList.value(CP_EPYRUS).isEmpty()) { return; }

	if (!m_Epyrus) { m_Epyrus = new CSVEpyrus(); }
	m_Epyrus->ReadFile(m_CPFileList.value(CP_EPYRUS));
	m_Epyrus->SetItem();

	double total = m_Epyrus->GetTotalAmount();
	double calculator = m_Epyrus->GetCalcAmount();
	double author = m_Epyrus->GetAuthorAmount();

	if (!m_EpyrusView) { m_EpyrusView = new QTableView(); }
	m_EpyrusView->setModel(m_Epyrus->GetItem());

	AddTab(m_EpyrusView, CPNAME_EPYRUS, total, calculator, author);
}

void CalcCPDlg::CalcOebook()
{
	m_Progress->setLabelText(QString("Calculate %1 Data ...").arg(CPNAME_OEBOOK));
	m_Progress->setValue(CP_OEBOOK);
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

	if (m_CPFileList.value(CP_OEBOOK).isEmpty()) { return; }

	if (!m_Oebook) { m_Oebook = new CSVOebook(); }
	m_Oebook->ReadFile(m_CPFileList.value(CP_OEBOOK));
	m_Oebook->SetItem();

	QList<double> total = m_Oebook->GetTotalAmount();
	QList<double> calculator = m_Oebook->GetCalcAmount();
	QList<double> author = m_Oebook->GetAuthorAmount();

	if (!m_OebookView) { m_OebookView = new QTableView(); }
	m_OebookView->setModel(m_Oebook->GetItem());

	AddTab4List(m_OebookView, CPNAME_OEBOOK, total, calculator, author);
}

void CalcCPDlg::CalcOnestore()
{
	m_Progress->setLabelText(QString("Calculate %1 Data ...").arg(CPNAME_ONESTORE));
	m_Progress->setValue(CP_ONESTORE);
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

	if (m_CPFileList.value(CP_ONESTORE).isEmpty()) { return; }

	if (!m_Onestore) { m_Onestore = new CSVOnestore(); }
	m_Onestore->ReadFile(m_CPFileList.value(CP_ONESTORE));
	m_Onestore->SetItem();

	double total = m_Onestore->GetTotalAmount();
	double calculator = m_Onestore->GetCalcAmount();
	double author = m_Onestore->GetAuthorAmount();

	if (!m_OnestoreView) { m_OnestoreView = new QTableView(); }
	m_OnestoreView->setModel(m_Onestore->GetItem());

	AddTab(m_OnestoreView, CPNAME_ONESTORE, total, calculator, author);
}

void CalcCPDlg::CalcKakao()
{
	m_Progress->setLabelText(QString("Calculate %1 Data ...").arg(CPNAME_KAKAO));
	m_Progress->setValue(CP_KAKAO);
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

	if (m_CPFileList.value(CP_KAKAO).isEmpty()) { return; }

	if (!m_Kakao) { m_Kakao = new CSVKakao(); }
	m_Kakao->ReadFile(m_CPFileList.value(CP_KAKAO));
	m_Kakao->SetItem();

	double total = m_Kakao->GetTotalAmount();
	double calculator = m_Kakao->GetCalcAmount();
	double author = m_Kakao->GetAuthorAmount();

	if (!m_KakaoView) { m_KakaoView = new QTableView(); }
	m_KakaoView->setModel(m_Kakao->GetItem());

	AddTab(m_KakaoView, CPNAME_KAKAO, total, calculator, author);
}

void CalcCPDlg::CalcComico()
{
	m_Progress->setLabelText(QString("Calculate %1 Data ...").arg(CPNAME_COMICO));
	m_Progress->setValue(CP_COMICO);
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

	if (m_CPFileList.value(CP_COMICO).isEmpty()) { return; }

	if (!m_Comico) { m_Comico = new CSVComico(); }
	m_Comico->ReadFile(m_CPFileList.value(CP_COMICO));
	m_Comico->SetItem();

	double total = m_Comico->GetTotalAmount();
	double calculator = m_Comico->GetCalcAmount();
	double author = m_Comico->GetAuthorAmount();

	if (!m_ComicoView) { m_ComicoView = new QTableView(); }
	m_ComicoView->setModel(m_Comico->GetItem());

	AddTab(m_ComicoView, CPNAME_COMICO, total, calculator, author);
}

void CalcCPDlg::CalcTocsoda()
{
	m_Progress->setLabelText(QString("Calculate %1 Data ...").arg(CPNAME_TOCSODA));
	m_Progress->setValue(CP_TOCSODA);
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

	if (m_CPFileList.value(CP_TOCSODA).isEmpty()) { return; }

	if (!m_Tocsoda) { m_Tocsoda = new CSVTocsoda(); }
	m_Tocsoda->ReadFile(m_CPFileList.value(CP_TOCSODA));
	m_Tocsoda->SetItem();

	double total = m_Tocsoda->GetTotalAmount();
	double calculator = m_Tocsoda->GetCalcAmount();
	double author = m_Tocsoda->GetAuthorAmount();

	if (!m_TocsodaView) { m_TocsodaView = new QTableView(); }
	m_TocsodaView->setModel(m_Tocsoda->GetItem());

	AddTab(m_TocsodaView, CPNAME_TOCSODA, total, calculator, author);
}

void CalcCPDlg::CalcKepub()
{
	m_Progress->setLabelText(QString("Calculate %1 Data ...").arg(CPNAME_KEPUB));
	m_Progress->setValue(CP_KEPUB);
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

	if (m_CPFileList.value(CP_KEPUB).isEmpty()) { return; }

	if (!m_Kepub) { m_Kepub = new CSVKepub(); }
	m_Kepub->ReadFile(m_CPFileList.value(CP_KEPUB));
	m_Kepub->SetItem();

	QList<double> total = m_Kepub->GetTotalAmount();
	QList<double> calculator = m_Kepub->GetCalcAmount();
	QList<double> author = m_Kepub->GetAuthorAmount();

	if (!m_KepubView) { m_KepubView = new QTableView(); }
	m_KepubView->setModel(m_Kepub->GetItem());

	AddTab4List(m_KepubView, CPNAME_KEPUB, total, calculator, author);
}

void CalcCPDlg::DeleteKyobo()
{
	if (m_Kyobo) {
		delete m_Kyobo;
		m_Kyobo = 0;
	}

	if (m_KyoboView) {
		delete m_KyoboView;
		m_KyoboView = 0;
	}
}

void CalcCPDlg::DeleteNaver()
{
	if (m_Naver) {
		delete m_Naver;
		m_Naver = 0;
	}

	if (m_NaverView) {
		delete m_NaverView;
		m_NaverView = 0;
	}
}

void CalcCPDlg::DeleteRidi()
{
	if (m_Ridi) {
		delete m_Ridi;
		m_Ridi = 0;
	}

	if (m_RidiView) {
		delete m_RidiView;
		m_RidiView = 0;
	}
}

void CalcCPDlg::DeleteMunpia()
{
	if (m_Munpia) {
		delete m_Munpia;
		m_Munpia = 0;
	}

	if (m_MunpiaView) {
		delete m_MunpiaView;
		m_MunpiaView = 0;
	}
}

void CalcCPDlg::DeleteMrblue()
{
	if (m_Mrblue) {
		delete m_Mrblue;
		m_Mrblue = 0;
	}

	if (m_MrblueView) {
		delete m_MrblueView;
		m_MrblueView = 0;
	}
}

void CalcCPDlg::DeleteBarobook()
{
	if (m_Barabook) {
		delete m_Barabook;
		m_Barabook = 0;
	}

	if (m_BarobookView) {
		delete m_BarobookView;
		m_BarobookView = 0;
	}
}

void CalcCPDlg::DeleteBookcube()
{
	if (m_Bookcube) {
		delete m_Bookcube;
		m_Bookcube = 0;
	}

	if (m_BookcubeView) {
		delete m_BookcubeView;
		m_BookcubeView = 0;
	}
}

void CalcCPDlg::DeleteEpyrus()
{
	if (m_Epyrus) {
		delete m_Epyrus;
		m_Epyrus = 0;
	}

	if (m_EpyrusView) {
		delete m_EpyrusView;
		m_EpyrusView = 0;
	}
}

void CalcCPDlg::DeleteOebook()
{
	if (m_Oebook) {
		delete m_Oebook;
		m_Oebook = 0;
	}

	if (m_OebookView) {
		delete m_OebookView;
		m_OebookView = 0;
	}
}

void CalcCPDlg::DeleteOnestore()
{
	if (m_Onestore) {
		delete m_Onestore;
		m_Onestore = 0;
	}

	if (m_OnestoreView) {
		delete m_OnestoreView;
		m_OnestoreView = 0;
	}
}

void CalcCPDlg::DeleteKakao()
{
	if (m_Kakao) {
		delete m_Kakao;
		m_Kakao = 0;
	}

	if (m_KakaoView) {
		delete m_KakaoView;
		m_KakaoView = 0;
	}
}

void CalcCPDlg::DeleteComico()
{
	if (m_Comico) {
		delete m_Comico;
		m_Comico = 0;
	}

	if (m_ComicoView) {
		delete m_ComicoView;
		m_ComicoView = 0;
	}
}

void CalcCPDlg::DeleteTocsoda()
{
	if (m_Tocsoda) {
		delete m_Tocsoda;
		m_Tocsoda = 0;
	}

	if (m_TocsodaView) {
		delete m_TocsodaView;
		m_TocsodaView = 0;
	}
}

void CalcCPDlg::DeleteKepub()
{
	if (m_Kepub) {
		delete m_Kepub;
		m_Kepub = 0;
	}

	if (m_KepubView) {
		delete m_KepubView;
		m_KepubView = 0;
	}
}

void CalcCPDlg::AddTab(QTableView* table, const QString cpName, double total, double calculator, double author)
{
	qDebug() << "[CalcCPDlg AddTab] - " << cpName;
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

void CalcCPDlg::AddTab4List(QTableView* table, const QString cpName, QList<double> total, QList<double> calculator, QList<double> author)
{
	qDebug() << "[CalcCPDlg AddTab4List] - " << cpName;
	QGridLayout* defalutLayout = new QGridLayout();
	QHBoxLayout* totalLayout = new QHBoxLayout();
	QHBoxLayout* calcLayout = new QHBoxLayout();
	QHBoxLayout* authorLayout = new QHBoxLayout();
	// kyobo
	if (!cpName.compare(CPNAME_KYOBO)) {

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
	else if (!cpName.compare(CPNAME_OEBOOK)) {

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
	else if (!cpName.compare(CPNAME_KEPUB)) {

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