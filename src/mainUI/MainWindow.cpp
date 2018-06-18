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
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

#include "misc/LimitDate.h"
#include "misc/SettingData.h"

#include "SPCSVManager.h"
#include "mainwindow.h"
#include "ui_MainWindow.h"

static const QString SETTINGS_GROUP = "mainWindow";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
	, m_LastFolderOpen("")
	, m_CSVFileName("")
{
    ui->setupUi(this);

   	ReadSettings();

}

MainWindow::~MainWindow()
{
	WriteSettings();
	delete ui;
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

	settings.endGroup();
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

	// Get the filename to use
	QString default_filter = "*";
	QString baseName = QFileInfo(m_CSVFileName).baseName();
	m_CSVFileName = QFileDialog::getOpenFileName(this,
												tr("Open CSV File"),
												m_LastFolderOpen + "/" + baseName,
												tr("CSV Files (*.csv)"),
												&default_filter);

	if (!m_CSVFileName.isEmpty())
		m_LastFolderOpen = QFileInfo(m_CSVFileName).absolutePath();

	SPCSVManager* csvManager = new SPCSVManager();
	csvManager->OpenFile(m_CSVFileName);


	QMessageBox::about(this, tr(QCoreApplication::applicationName().toStdString().c_str()), tr("This function is not yet."));

}

void MainWindow::on_actionSave_triggered()
{
	qDebug() << "on_actionSave_triggered()";
	if (!OnCheckLimited()) { return; }

	// Get the filename to use
	QString default_filter = "*";
	QString baseName = QFileInfo(m_CSVFileName).baseName();
	m_CSVFileName = QFileDialog::getSaveFileName(this,
												tr("Save CSV File"),
												m_LastFolderOpen + "/" + baseName,
												tr("CSV Files (*.csv)"),
												&default_filter);
	
	if (!m_CSVFileName.isEmpty())
		m_LastFolderOpen = QFileInfo(m_CSVFileName).absolutePath();

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
