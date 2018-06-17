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

namespace Ui {
class MainWindow;
}

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

	bool OnCheckLimited();


	QString		m_LastFolderOpen;


    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
