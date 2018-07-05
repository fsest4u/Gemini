/************************************************************************
**
**  Copyright (C) 2018  spdevapp <spdevapp@joara.com>
**
**  This file is part of Gemini.
**
**  Gemini is Joara CSV Calculator.
**
*************************************************************************/

#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "CalcManager.h"

namespace Ui {
class MainWindow;
}

class CalcManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

	void on_actionNew_triggered();
	void on_actionOpen_triggered();
	void on_actionSave_triggered();
	void on_actionExit_triggered();
	void on_actionAbout_triggered();

	void SetCheckKyobo(int);
	void SetCheckNaver(int);
	void SetCheckRidi(int);
	void SetCheckMunpia(int);
	void SetCheckMrblue(int);
	void SetCheckBarobook(int);
	void SetCheckBookcube(int);
	void SetCheckEpyrus(int);
	void SetCheckOebook(int);
	void SetCheckOnestore(int);
	void SetCheckKakao(int);
	void SetCheckComico(int);
	void SetCheckTocsoda(int);
	void SetCheckKepub(int);
	void SetCheckJustoon(int);
	void SetCheckGoogle(int);

	void on_KyoboFileButton_clicked();
	void on_NaverFileButton_clicked();
	void on_RidiFileButton_clicked();
	void on_MunpiaFileButton_clicked();
	void on_MrblueFileButton_clicked();
	void on_BarobookFileButton_clicked();
	void on_BookcubeFileButton_clicked();
	void on_EpyrusFileButton_clicked();
	void on_OebookFileButton_clicked();
	void on_OnestoreFileButton_clicked();
	void on_KakaoFileButton_clicked();
	void on_ComicoFileButton_clicked();
	void on_TocsodaFileButton_clicked();
	void on_KepubFileButton_clicked();
	void on_JustoonFileButton_clicked();
	void on_GoogleFileButton_clicked();


	void SetCPFiles();

private:
	/**
	* Reads all the stored application settings like
	* window position, geometry etc.
	*/
	void ReadSettings();

	/**
	* Writes all the stored application settings like
	* window position, geometry etc.
	*/
	void WriteSettings();

	void ConnectSignalsToSlots();

	void InitUI();
	bool OnCheckLimited();

	void SetFilePath(int type);


	QString					m_LastFolderOpen;
	QMap<int, QString>		m_CSVFileNames;

	CalcManager* m_CalcManager;


    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
