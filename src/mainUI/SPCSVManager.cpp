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

#include "qtcsv/reader.h"

#include "SPCSVManager.h"

SPCSVManager::SPCSVManager(QObject *parent) :
	QObject(parent)
{
}

SPCSVManager::~SPCSVManager()
{
}

void SPCSVManager::OpenFile(QString filepath)
{

	QList<QStringList> readData = QtCSV::Reader::readToList(filepath);
	for (int i = 0; i < readData.size(); ++i) {
		for (int j = 0; j < readData.at(i).size(); j++) {
			qDebug() << readData.at(i).value(j);
		}
		//qDebug() << readData.at(i).mid(2, 1);
	}
}

