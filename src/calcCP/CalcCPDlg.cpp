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

#include "CSVKyobo.h"
#include "CSVNaver.h"
#include "CSVRidi.h"
#include "CSVMunpia.h"
#include "CSVMrblue.h"
#include "CSVBarobook.h"
#include "CSVBookcube.h"
#include "CSVEpyrus.h"
#include "CSVOebook.h"
#include "CSVOnestore.h"
#include "CSVKakao.h"
#include "CSVComico.h"
#include "CSVTocsoda.h"
#include "CSVKepub.h"

#include "CalcCPDlg.h"


const QString CPNAME_KYOBO = "KYOBO";
const QString CPNAME_NAVER = "NAVER";
const QString CPNAME_RIDI = "RIDI";
const QString CPNAME_MUNPIA = "MUNPIA";
const QString CPNAME_MRBLUE = "MRBLUE";
const QString CPNAME_BARABOOK = "BARABOOK";
const QString CPNAME_BOOKCUBE = "BOOKCUBE";
const QString CPNAME_EPYRUS = "EPYRUS";
const QString CPNAME_OEBOOK = "OEBOOK";
const QString CPNAME_ONESTORE = "ONESTORE";
const QString CPNAME_KAKAO = "KAKAO";
const QString CPNAME_COMICO = "COMICO";
const QString CPNAME_TOCSODA = "TOCSODA";
const QString CPNAME_KEPUB = "KEPUB";

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
}

void CalcCPDlg::InitUI()
{
	ui.buttonBox->button(QDialogButtonBox::Yes)->setText(tr("Prev"));
	ui.buttonBox->button(QDialogButtonBox::Retry)->setText(tr("Calculate"));
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

void CalcCPDlg::SetCPFileList(QHash<int, QString>& cpFileList)
{
	m_CPFileList = cpFileList;
	// for debug
	foreach(const int key, m_CPFileList.keys()) {
		qDebug() << "[SetCPFileList] key : " << key << ", value : " << m_CPFileList.value(key);
	}

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
}

void CalcCPDlg::Prev()
{
	this->done(QDialogButtonBox::YesRole);
}

void CalcCPDlg::CalcCP()
{
	// Delete and draw new
	int count = ui.tabCP->count();
	for (int i = 0; i < count; i++) {
		ui.tabCP->removeTab(i);
	}

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

	this->done(QDialogButtonBox::HelpRole);
}

void CalcCPDlg::Next()
{
	this->done(QDialogButtonBox::NoRole);
}

void CalcCPDlg::CalcKyobo()
{
	if (m_CPFileList.value(CP_KYOBO).isEmpty()) { return; }

	if (!m_Kyobo) { m_Kyobo = new CSVKyobo(); }
	m_Kyobo->ReadFile(m_CPFileList.value(CP_KYOBO));
	m_Kyobo->SetItem();

	double total = m_Kyobo->GetTotalAmount();
	double calculator = m_Kyobo->GetCalcAmount();
	double author = m_Kyobo->GetAuthorAmount();

	if (!m_KyoboView) { m_KyoboView = new QTableView(); }
	m_KyoboView->setModel(m_Kyobo->GetItem());

	AddTab(m_KyoboView, CPNAME_KYOBO, total, calculator, author);
}

void CalcCPDlg::CalcNaver()
{
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
	if (m_CPFileList.value(CP_BAROBOOK).isEmpty()) { return; }

	if (!m_Barabook) { m_Barabook = new CSVBarobook(); }
	m_Barabook->ReadFile(m_CPFileList.value(CP_BAROBOOK));
	m_Barabook->SetItem();

	double total = m_Barabook->GetTotalAmount();
	double calculator = m_Barabook->GetCalcAmount();
	double author = m_Barabook->GetAuthorAmount();

	if (!m_BarobookView) { m_BarobookView = new QTableView(); }
	m_BarobookView->setModel(m_Barabook->GetItem());

	AddTab(m_BarobookView, CPNAME_BARABOOK, total, calculator, author);
}

void CalcCPDlg::CalcBookcube()
{
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
	if (m_CPFileList.value(CP_OEBOOK).isEmpty()) { return; }

	if (!m_Oebook) { m_Oebook = new CSVOebook(); }
	m_Oebook->ReadFile(m_CPFileList.value(CP_OEBOOK));
	m_Oebook->SetItem();

	double total = m_Oebook->GetTotalAmount();
	double calculator = m_Oebook->GetCalcAmount();
	double author = m_Oebook->GetAuthorAmount();

	if (!m_OebookView) { m_OebookView = new QTableView(); }
	m_OebookView->setModel(m_Oebook->GetItem());

	AddTab(m_OebookView, CPNAME_OEBOOK, total, calculator, author);
}

void CalcCPDlg::CalcOnestore()
{
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
	if (m_CPFileList.value(CP_KAKAO).isEmpty()) { return; }

	if (!m_Kakao) { m_Kakao = new CSVKakao(); }
	m_Kakao->ReadFile(m_CPFileList.value(CP_KAKAO));
	m_Kakao->SetItem();

	double total = m_Kakao->GetTotalAmount();
	double calculator = m_Kakao->GetCalcAmount();
	double author = m_Kakao->GetAuthorAmount();

	if (!m_KakaoView) { m_KakaoView = new QTableView(); }
	m_KakaoView->setModel(m_Kakao->GetItem());

	qDebug() << "[CalcKakao] - AddTab";
	AddTab(m_KakaoView, CPNAME_KAKAO, total, calculator, author);
}

void CalcCPDlg::CalcComico()
{
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
	if (m_CPFileList.value(CP_KEPUB).isEmpty()) { return; }

	if (!m_Kepub) { m_Kepub = new CSVKepub(); }
	m_Kepub->ReadFile(m_CPFileList.value(CP_KEPUB));
	m_Kepub->SetItem();

	double total = m_Kepub->GetTotalAmount();
	double calculator = m_Kepub->GetCalcAmount();
	double author = m_Kepub->GetAuthorAmount();

	if (!m_KepubView) { m_KepubView = new QTableView(); }
	m_KepubView->setModel(m_Kepub->GetItem());

	AddTab(m_KepubView, CPNAME_KEPUB, total, calculator, author);
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