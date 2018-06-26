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
#include <QtCore/QStandardPaths>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QCheckBox>

#include "misc/LimitDate.h"
#include "misc/SettingData.h"

#include "mainwindow.h"
#include "ui_MainWindow.h"

static const QString SETTINGS_GROUP = "mainWindow";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
	, m_LastFolderOpen("")
	, m_CalcManager(NULL)
{
    ui->setupUi(this);

   	ReadSettings();
	InitUI();

}

MainWindow::~MainWindow()
{
	WriteSettings();
	delete ui;

	if (m_CalcManager) {
		delete m_CalcManager;
		m_CalcManager = 0;
	}
}

void MainWindow::InitUI()
{
	ui->toolBar->setVisible(false);
	ui->statusBar->setVisible(false);

	ui->actionNew->setVisible(false);
	ui->actionOpen->setVisible(false);
	ui->actionSave->setVisible(false);

	ui->buttonBox->button(QDialogButtonBox::Yes)->setText(tr("Calculate"));

	ConnectSignalsToSlots();

	//m_CSVFileNames.clear();
	ui->KyoboFilepath->setText(m_CSVFileNames[CalcCPDlg::CP_KYOBO]);
	ui->NaverFilepath->setText(m_CSVFileNames[CalcCPDlg::CP_NAVER]);
	ui->RidiFilepath->setText(m_CSVFileNames[CalcCPDlg::CP_RIDI]);
	ui->MunpiaFilepath->setText(m_CSVFileNames[CalcCPDlg::CP_MUNPIA]);
	ui->MrblueFilepath->setText(m_CSVFileNames[CalcCPDlg::CP_MRBLUE]);
	ui->BarobookFilepath->setText(m_CSVFileNames[CalcCPDlg::CP_BAROBOOK]);
	ui->BookcubeFilepath->setText(m_CSVFileNames[CalcCPDlg::CP_BOOKCUBE]);
	ui->EpyrusFilepath->setText(m_CSVFileNames[CalcCPDlg::CP_EPYRUS]);
	ui->OebookFilepath->setText(m_CSVFileNames[CalcCPDlg::CP_OEBOOK]);
	ui->OnestoreFilepath->setText(m_CSVFileNames[CalcCPDlg::CP_ONESTORE]);
	ui->KakaoFilepath->setText(m_CSVFileNames[CalcCPDlg::CP_KAKAO]);
	ui->ComicoFilepath->setText(m_CSVFileNames[CalcCPDlg::CP_COMICO]);
	ui->TocsodaFilepath->setText(m_CSVFileNames[CalcCPDlg::CP_TOCSODA]);
	ui->KepubFilepath->setText(m_CSVFileNames[CalcCPDlg::CP_KEPUB]);

}

void MainWindow::ReadSettings()
{
	SettingData settings;
	settings.beginGroup(SETTINGS_GROUP);
	// The size of the window and it's full screen status
	QByteArray geometry = settings.value("geometry").toByteArray();

	if (!geometry.isNull()) {
		restoreGeometry(geometry);
	}

	// The last folder used for saving and opening files
	m_LastFolderOpen = settings.value("lastfolderopen", QDir::homePath()).toString();

	m_CSVFileNames[CalcCPDlg::CP_KYOBO] = settings.value("lastcsvkyobo", QDir::homePath()).toString();
	m_CSVFileNames[CalcCPDlg::CP_NAVER] = settings.value("lastcsvnaver", QDir::homePath()).toString();
	m_CSVFileNames[CalcCPDlg::CP_RIDI] = settings.value("lastcsvridi", QDir::homePath()).toString();
	m_CSVFileNames[CalcCPDlg::CP_MUNPIA] = settings.value("lastcsvmunpia", QDir::homePath()).toString();
	m_CSVFileNames[CalcCPDlg::CP_MRBLUE] = settings.value("lastcsvmrblue", QDir::homePath()).toString();
	m_CSVFileNames[CalcCPDlg::CP_BAROBOOK] = settings.value("lastcsvbarobook", QDir::homePath()).toString();
	m_CSVFileNames[CalcCPDlg::CP_BOOKCUBE] = settings.value("lastcsvbookcube", QDir::homePath()).toString();
	m_CSVFileNames[CalcCPDlg::CP_EPYRUS] = settings.value("lastcsvepyrus", QDir::homePath()).toString();
	m_CSVFileNames[CalcCPDlg::CP_OEBOOK] = settings.value("lastcsvoebook", QDir::homePath()).toString();
	m_CSVFileNames[CalcCPDlg::CP_ONESTORE] = settings.value("lastcsvonestore", QDir::homePath()).toString();
	m_CSVFileNames[CalcCPDlg::CP_KAKAO] = settings.value("lastcsvkakao", QDir::homePath()).toString();
	m_CSVFileNames[CalcCPDlg::CP_COMICO] = settings.value("lastcsvcomico", QDir::homePath()).toString();
	m_CSVFileNames[CalcCPDlg::CP_TOCSODA] = settings.value("lastcsvtocsoda", QDir::homePath()).toString();
	m_CSVFileNames[CalcCPDlg::CP_KEPUB] = settings.value("lastcsvkepub", QDir::homePath()).toString();

	settings.endGroup();

}

void MainWindow::WriteSettings()
{
	SettingData settings;
	settings.beginGroup(SETTINGS_GROUP);
	// The size of the window and it's full screen status
	settings.setValue("geometry", saveGeometry());

	// The last folders used for saving and opening files
	settings.setValue("lastfolderopen", m_LastFolderOpen);

	settings.setValue("lastcsvkyobo", m_CSVFileNames[CalcCPDlg::CP_KYOBO]);
	settings.setValue("lastcsvnaver", m_CSVFileNames[CalcCPDlg::CP_NAVER]);
	settings.setValue("lastcsvridi", m_CSVFileNames[CalcCPDlg::CP_RIDI]);
	settings.setValue("lastcsvmunpia", m_CSVFileNames[CalcCPDlg::CP_MUNPIA]);
	settings.setValue("lastcsvmrblue", m_CSVFileNames[CalcCPDlg::CP_MRBLUE]);
	settings.setValue("lastcsvbarobook", m_CSVFileNames[CalcCPDlg::CP_BAROBOOK]);
	settings.setValue("lastcsvbookcube", m_CSVFileNames[CalcCPDlg::CP_BOOKCUBE]);
	settings.setValue("lastcsvepyrus", m_CSVFileNames[CalcCPDlg::CP_EPYRUS]);
	settings.setValue("lastcsvoebook", m_CSVFileNames[CalcCPDlg::CP_OEBOOK]);
	settings.setValue("lastcsvonestore", m_CSVFileNames[CalcCPDlg::CP_ONESTORE]);
	settings.setValue("lastcsvkakao", m_CSVFileNames[CalcCPDlg::CP_KAKAO]);
	settings.setValue("lastcsvcomico", m_CSVFileNames[CalcCPDlg::CP_COMICO]);
	settings.setValue("lastcsvtocsoda", m_CSVFileNames[CalcCPDlg::CP_TOCSODA]);
	settings.setValue("lastcsvkepub", m_CSVFileNames[CalcCPDlg::CP_KEPUB]);


	settings.endGroup();
}

void MainWindow::ConnectSignalsToSlots()
{
	connect(ui->KyoboCheckBox, SIGNAL(stateChanged(int)), this, SLOT(SetCheckKyobo(int)));
	connect(ui->NaverCheckBox, SIGNAL(stateChanged(int)), this, SLOT(SetCheckNaver(int)));
	connect(ui->RidiCheckBox, SIGNAL(stateChanged(int)), this, SLOT(SetCheckRidi(int)));
	connect(ui->MunpiaCheckBox, SIGNAL(stateChanged(int)), this, SLOT(SetCheckMunpia(int)));
	connect(ui->MrblueCheckBox, SIGNAL(stateChanged(int)), this, SLOT(SetCheckMrblue(int)));
	connect(ui->BarobookCheckBox, SIGNAL(stateChanged(int)), this, SLOT(SetCheckBarobook(int)));
	connect(ui->BookcubeCheckBox, SIGNAL(stateChanged(int)), this, SLOT(SetCheckBookcube(int)));
	connect(ui->EpyrusCheckBox, SIGNAL(stateChanged(int)), this, SLOT(SetCheckEpyrus(int)));
	connect(ui->OebookCheckBox, SIGNAL(stateChanged(int)), this, SLOT(SetCheckOebook(int)));
	connect(ui->OnestoreCheckBox, SIGNAL(stateChanged(int)), this, SLOT(SetCheckOnestore(int)));
	connect(ui->KakaoCheckBox, SIGNAL(stateChanged(int)), this, SLOT(SetCheckKakao(int)));
	connect(ui->ComicoCheckBox, SIGNAL(stateChanged(int)), this, SLOT(SetCheckComico(int)));
	connect(ui->TocsodaCheckBox, SIGNAL(stateChanged(int)), this, SLOT(SetCheckTocsoda(int)));
	connect(ui->KepubCheckBox, SIGNAL(stateChanged(int)), this, SLOT(SetCheckKepub(int)));

	connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(SetCPFiles()));

}

bool MainWindow::OnCheckLimited()
{
	bool ret = false;

	LimitDate* limitDate = new LimitDate();
	if (limitDate->CheckExpiredDate()) {
		QDate date = limitDate->GetExpiredDate();
		QMessageBox::critical(this, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("The function has expired. %1.%2.%3").arg(date.year()).arg(date.month()).arg(date.day()));

		ret = false;
	}
	else {
		ret = true;
	}

	if (limitDate) {
		delete limitDate;
		limitDate = 0;
	}

	return ret;
}


void MainWindow::on_actionNew_triggered()
{
	qDebug() << "on_actionNew_triggered()";
	if (!OnCheckLimited()) { return; }

	QMessageBox::about(this, tr(QCoreApplication::applicationName().toStdString().c_str()), tr("This function is not yet."));

}

void MainWindow::on_actionOpen_triggered()
{
	qDebug() << "on_actionOpen_triggered()";
	if (!OnCheckLimited()) { return; }

	QMessageBox::about(this, tr(QCoreApplication::applicationName().toStdString().c_str()), tr("This function is not yet."));

}

void MainWindow::on_actionSave_triggered()
{
	qDebug() << "on_actionSave_triggered()";
	if (!OnCheckLimited()) { return; }

	QMessageBox::about(this, tr(QCoreApplication::applicationName().toStdString().c_str()), tr("This function is not yet."));

}

void MainWindow::on_actionExit_triggered()
{
	qDebug() << "on_actionExit_triggered()";
	QMessageBox::StandardButton btn;
	btn = QMessageBox::question(this, tr(QCoreApplication::applicationName().toStdString().c_str()), tr("Are you sure you want to exit the application?"), QMessageBox::Ok | QMessageBox::Cancel);

	if (btn == QMessageBox::Ok) {
		this->close();
		return;
	}
}

void MainWindow::on_actionAbout_triggered()
{
	qDebug() << "on_actionAbout_triggered()";
	QMessageBox::about(this, tr(QCoreApplication::applicationName().toStdString().c_str()), tr("Gemini is CSV Calculator for JOARA Publishing Team."));

}

void MainWindow::SetCheckKyobo(int state)
{
	if (Qt::Checked == state) {
		ui->KyoboFilepath->setEnabled(true);
		ui->KyoboFileButton->setEnabled(true);
	}
	else {
		ui->KyoboFilepath->setEnabled(false);
		ui->KyoboFileButton->setEnabled(false);
	}
}

void MainWindow::SetCheckNaver(int state)
{
	if (Qt::Checked == state) {
		ui->NaverFilepath->setEnabled(true);
		ui->NaverFileButton->setEnabled(true);
	}
	else {
		ui->NaverFilepath->setEnabled(false);
		ui->NaverFileButton->setEnabled(false);
	}
}

void MainWindow::SetCheckRidi(int state)
{
	if (Qt::Checked == state) {
		ui->RidiFilepath->setEnabled(true);
		ui->RidiFileButton->setEnabled(true);
	}
	else {
		ui->RidiFilepath->setEnabled(false);
		ui->RidiFileButton->setEnabled(false);
	}
}

void MainWindow::SetCheckMunpia(int state)
{
	if (Qt::Checked == state) {
		ui->MunpiaFilepath->setEnabled(true);
		ui->MunpiaFileButton->setEnabled(true);
	}
	else {
		ui->MunpiaFilepath->setEnabled(false);
		ui->MunpiaFileButton->setEnabled(false);
	}
}

void MainWindow::SetCheckMrblue(int state)
{
	if (Qt::Checked == state) {
		ui->MrblueFilepath->setEnabled(true);
		ui->MrblueFileButton->setEnabled(true);
	}
	else {
		ui->MrblueFilepath->setEnabled(false);
		ui->MrblueFileButton->setEnabled(false);
	}
}

void MainWindow::SetCheckBarobook(int state)
{
	if (Qt::Checked == state) {
		ui->BarobookFilepath->setEnabled(true);
		ui->BarobookFileButton->setEnabled(true);
	}
	else {
		ui->BarobookFilepath->setEnabled(false);
		ui->BarobookFileButton->setEnabled(false);
	}
}

void MainWindow::SetCheckBookcube(int state)
{
	if (Qt::Checked == state) {
		ui->BookcubeFilepath->setEnabled(true);
		ui->BookcubeFileButton->setEnabled(true);
	}
	else {
		ui->BookcubeFilepath->setEnabled(false);
		ui->BookcubeFileButton->setEnabled(false);
	}
}

void MainWindow::SetCheckEpyrus(int state)
{
	if (Qt::Checked == state) {
		ui->EpyrusFilepath->setEnabled(true);
		ui->EpyrusFileButton->setEnabled(true);
	}
	else {
		ui->EpyrusFilepath->setEnabled(false);
		ui->EpyrusFileButton->setEnabled(false);
	}
}

void MainWindow::SetCheckOebook(int state)
{
	if (Qt::Checked == state) {
		ui->OebookFilepath->setEnabled(true);
		ui->OebookFileButton->setEnabled(true);
	}
	else {
		ui->OebookFilepath->setEnabled(false);
		ui->OebookFileButton->setEnabled(false);
	}
}

void MainWindow::SetCheckOnestore(int state)
{
	if (Qt::Checked == state) {
		ui->OnestoreFilepath->setEnabled(true);
		ui->OnestoreFileButton->setEnabled(true);
	}
	else {
		ui->OnestoreFilepath->setEnabled(false);
		ui->OnestoreFileButton->setEnabled(false);
	}
}

void MainWindow::SetCheckKakao(int state)
{
	if (Qt::Checked == state) {
		ui->KakaoFilepath->setEnabled(true);
		ui->KakaoFileButton->setEnabled(true);
	}
	else {
		ui->KakaoFilepath->setEnabled(false);
		ui->KakaoFileButton->setEnabled(false);
	}
}

void MainWindow::SetCheckComico(int state)
{
	if (Qt::Checked == state) {
		ui->ComicoFilepath->setEnabled(true);
		ui->ComicoFileButton->setEnabled(true);
	}
	else {
		ui->ComicoFilepath->setEnabled(false);
		ui->ComicoFileButton->setEnabled(false);
	}
}

void MainWindow::SetCheckTocsoda(int state)
{
	if (Qt::Checked == state) {
		ui->TocsodaFilepath->setEnabled(true);
		ui->TocsodaFileButton->setEnabled(true);
	}
	else {
		ui->TocsodaFilepath->setEnabled(false);
		ui->TocsodaFileButton->setEnabled(false);
	}
}

void MainWindow::SetCheckKepub(int state)
{
	if (Qt::Checked == state) {
		ui->KepubFilepath->setEnabled(true);
		ui->KepubFileButton->setEnabled(true);
	}
	else {
		ui->KepubFilepath->setEnabled(false);
		ui->KepubFileButton->setEnabled(false);
	}
}

void MainWindow::SetFilePath(int type)
{
	QString filepath;
	filepath = m_CSVFileNames[type];

	// Get the filename to use
	QString default_filter = "*";
	QString basename = QFileInfo(ui->KyoboFilepath->text()).baseName();
	QString filename = QFileDialog::getOpenFileName(this,
													tr("Open CSV File"),
													m_LastFolderOpen + "/" + basename,
													tr("CSV Files (*.csv)"),
													&default_filter);

	m_CSVFileNames[type] = filename;
	switch (type)
	{
	case CalcCPDlg::CP_KYOBO:
		ui->KyoboFilepath->setText(filename);
		break;
	case CalcCPDlg::CP_NAVER:
		ui->NaverFilepath->setText(filename);
		break;
	case CalcCPDlg::CP_RIDI:
		ui->RidiFilepath->setText(filename);
		break;
	case CalcCPDlg::CP_MUNPIA:
		ui->MunpiaFilepath->setText(filename);
		break;
	case CalcCPDlg::CP_MRBLUE:
		ui->MrblueFilepath->setText(filename);
		break;
	case CalcCPDlg::CP_BAROBOOK:
		ui->BarobookFilepath->setText(filename);
		break;
	case CalcCPDlg::CP_BOOKCUBE:
		ui->BookcubeFilepath->setText(filename);
		break;
	case CalcCPDlg::CP_EPYRUS:
		ui->EpyrusFilepath->setText(filename);
		break;
	case CalcCPDlg::CP_OEBOOK:
		ui->OebookFilepath->setText(filename);
		break;
	case CalcCPDlg::CP_ONESTORE:
		ui->OnestoreFilepath->setText(filename);
		break;
	case CalcCPDlg::CP_KAKAO:
		ui->KakaoFilepath->setText(filename);
		break;
	case CalcCPDlg::CP_COMICO:
		ui->ComicoFilepath->setText(filename);
		break;
	case CalcCPDlg::CP_TOCSODA:
		ui->TocsodaFilepath->setText(filename);
		break;
	case CalcCPDlg::CP_KEPUB:
		ui->KepubFilepath->setText(filename);
		break;
	}

	if (!filename.isEmpty())
		m_LastFolderOpen = QFileInfo(filename).absolutePath();
}

void MainWindow::on_KyoboFileButton_clicked() {
	SetFilePath(CalcCPDlg::CP_KYOBO);
}

void MainWindow::on_NaverFileButton_clicked() {
	SetFilePath(CalcCPDlg::CP_NAVER);
}

void MainWindow::on_RidiFileButton_clicked(){ 
	SetFilePath(CalcCPDlg::CP_RIDI);
}

void MainWindow::on_MunpiaFileButton_clicked(){
	SetFilePath(CalcCPDlg::CP_MUNPIA);
}

void MainWindow::on_MrblueFileButton_clicked(){
	SetFilePath(CalcCPDlg::CP_MRBLUE);
}

void MainWindow::on_BarobookFileButton_clicked(){
	SetFilePath(CalcCPDlg::CP_BAROBOOK);
}

void MainWindow::on_BookcubeFileButton_clicked(){
	SetFilePath(CalcCPDlg::CP_BOOKCUBE);
}

void MainWindow::on_EpyrusFileButton_clicked(){
	SetFilePath(CalcCPDlg::CP_EPYRUS);
}

void MainWindow::on_OebookFileButton_clicked(){
	SetFilePath(CalcCPDlg::CP_OEBOOK);
}

void MainWindow::on_OnestoreFileButton_clicked(){
	SetFilePath(CalcCPDlg::CP_ONESTORE);
}

void MainWindow::on_KakaoFileButton_clicked(){
	SetFilePath(CalcCPDlg::CP_KAKAO);
}

void MainWindow::on_ComicoFileButton_clicked(){
	SetFilePath(CalcCPDlg::CP_COMICO);
}

void MainWindow::on_TocsodaFileButton_clicked(){
	SetFilePath(CalcCPDlg::CP_TOCSODA);
}

void MainWindow::on_KepubFileButton_clicked(){
	SetFilePath(CalcCPDlg::CP_KEPUB);
}

void MainWindow::SetCPFiles()
{
	QHash<int, QString> cpFileList;
	if (Qt::Checked == ui->KyoboCheckBox->checkState()) {
		if (ui->KyoboFilepath->text().isEmpty()) {
			QMessageBox::warning(this
				, tr(QCoreApplication::applicationName().toStdString().c_str())
				, tr("Kyobo file path is empty."));
			return;
		}
		cpFileList[CalcCPDlg::CP_KYOBO] = ui->KyoboFilepath->text();
	}
	if (Qt::Checked == ui->NaverCheckBox->checkState()) {
		if (ui->NaverFilepath->text().isEmpty()) {
			QMessageBox::warning(this
				, tr(QCoreApplication::applicationName().toStdString().c_str())
				, tr("Naver file path is empty."));
			return;
		}
		cpFileList[CalcCPDlg::CP_NAVER] = ui->NaverFilepath->text();
	}
	if (Qt::Checked == ui->RidiCheckBox->checkState()) {
		if (ui->RidiFilepath->text().isEmpty()) {
			QMessageBox::warning(this
				, tr(QCoreApplication::applicationName().toStdString().c_str())
				, tr("Ridi file path is empty."));
			return;
		}
		cpFileList[CalcCPDlg::CP_RIDI] = ui->RidiFilepath->text();
	}
	if (Qt::Checked == ui->MunpiaCheckBox->checkState()) {
		if (ui->MunpiaFilepath->text().isEmpty()) {
			QMessageBox::warning(this
				, tr(QCoreApplication::applicationName().toStdString().c_str())
				, tr("Munpia file path is empty."));
			return;
		}
		cpFileList[CalcCPDlg::CP_MUNPIA] = ui->MunpiaFilepath->text();
	}
	if (Qt::Checked == ui->MrblueCheckBox->checkState()) {
		if (ui->MrblueFilepath->text().isEmpty()) {
			QMessageBox::warning(this
				, tr(QCoreApplication::applicationName().toStdString().c_str())
				, tr("Mrblue file path is empty."));
			return;
		}
		cpFileList[CalcCPDlg::CP_MRBLUE] = ui->MrblueFilepath->text();
	}
	if (Qt::Checked == ui->BarobookCheckBox->checkState()) {
		if (ui->BarobookFilepath->text().isEmpty()) {
			QMessageBox::warning(this
				, tr(QCoreApplication::applicationName().toStdString().c_str())
				, tr("Barobook file path is empty."));
			return;
		}
		cpFileList[CalcCPDlg::CP_BAROBOOK] = ui->BarobookFilepath->text();
	}
	if (Qt::Checked == ui->BookcubeCheckBox->checkState()) {
		if (ui->BookcubeFilepath->text().isEmpty()) {
			QMessageBox::warning(this
				, tr(QCoreApplication::applicationName().toStdString().c_str())
				, tr("Bookcube file path is empty."));
			return;
		}
		cpFileList[CalcCPDlg::CP_BOOKCUBE] = ui->BookcubeFilepath->text();
	}
	if (Qt::Checked == ui->EpyrusCheckBox->checkState()) {
		if (ui->EpyrusFilepath->text().isEmpty()) {
			QMessageBox::warning(this
				, tr(QCoreApplication::applicationName().toStdString().c_str())
				, tr("Epyrus file path is empty."));
			return;
		}
		cpFileList[CalcCPDlg::CP_EPYRUS] = ui->EpyrusFilepath->text();
	}
	if (Qt::Checked == ui->OebookCheckBox->checkState()) {
		if (ui->OebookFilepath->text().isEmpty()) {
			QMessageBox::warning(this
				, tr(QCoreApplication::applicationName().toStdString().c_str())
				, tr("Oebook file path is empty."));
			return;
		}
		cpFileList[CalcCPDlg::CP_OEBOOK] = ui->OebookFilepath->text();
	}
	if (Qt::Checked == ui->OnestoreCheckBox->checkState()) {
		if (ui->OnestoreFilepath->text().isEmpty()) {
			QMessageBox::warning(this
				, tr(QCoreApplication::applicationName().toStdString().c_str())
				, tr("Onestore file path is empty."));
			return;
		}
		cpFileList[CalcCPDlg::CP_ONESTORE] = ui->OnestoreFilepath->text();
	}
	if (Qt::Checked == ui->KakaoCheckBox->checkState()) {
		if (ui->KakaoFilepath->text().isEmpty()) {
			QMessageBox::warning(this
				, tr(QCoreApplication::applicationName().toStdString().c_str())
				, tr("Kakao file path is empty."));
			return;
		}
		cpFileList[CalcCPDlg::CP_KAKAO] = ui->KakaoFilepath->text();
	}
	if (Qt::Checked == ui->ComicoCheckBox->checkState()) {
		if (ui->ComicoFilepath->text().isEmpty()) {
			QMessageBox::warning(this
				, tr(QCoreApplication::applicationName().toStdString().c_str())
				, tr("Comico file path is empty."));
			return;
		}
		cpFileList[CalcCPDlg::CP_COMICO] = ui->ComicoFilepath->text();
	}
	if (Qt::Checked == ui->TocsodaCheckBox->checkState()) {
		if (ui->TocsodaFilepath->text().isEmpty()) {
			QMessageBox::warning(this
				, tr(QCoreApplication::applicationName().toStdString().c_str())
				, tr("Tocsoda file path is empty."));
			return;
		}
		cpFileList[CalcCPDlg::CP_TOCSODA] = ui->TocsodaFilepath->text();
	}
	if (Qt::Checked == ui->KepubCheckBox->checkState()) {
		if (ui->KepubFilepath->text().isEmpty()) {
			QMessageBox::warning(this
				, tr(QCoreApplication::applicationName().toStdString().c_str())
				, tr("Kepub file path is empty."));
			return;
		}
		cpFileList[CalcCPDlg::CP_KEPUB] = ui->KepubFilepath->text();
	}

	// for debug
	//foreach (const int key, cpFileList.keys()) {
	//	qDebug() << " key : " << key << ", value : " << cpFileList.value(key);
	//}

	// open dialog for calculation
	if (!m_CalcManager) {
		m_CalcManager = new CalcManager();
	}
	if (!m_CalcManager->ExecuteCalc(cpFileList)) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("Calculation service canceled."));
	}
}