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
#ifndef CSV_MANAGER_H
#define CSV_MANAGER_H

#include <QtCore/QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QtWidgets/QTableView>

class CSVManager : public QObject
{
	Q_OBJECT

public:

	/**
	* Constructor.
	*/
	CSVManager(QObject *parent = 0);
	~CSVManager();

	void ReadFile(QString filepath);

	void SetItem();
	QStandardItemModel* GetItem();

private slots:


private:



	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////
	QList<QStringList> m_CSVData;
	QStandardItemModel *m_CSVModel;


};

#endif // CSV_MANAGER_H
