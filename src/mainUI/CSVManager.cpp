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

#include "CSVManager.h"

CSVManager::CSVManager(QObject *parent) :
	QObject(parent)
	, m_CSVModel(NULL)
{
	m_CSVData.clear();
}

CSVManager::~CSVManager()
{
	if (m_CSVModel) {
		delete m_CSVModel;
		m_CSVModel = 0;
	}
}

void CSVManager::ReadFile(QString filepath)
{
	m_CSVData = QtCSV::Reader::readToList(filepath);
	//for (int i = 0; i < m_CSVData.size(); ++i) {
	//	//for (int j = 0; j < m_CSVData.at(i).size(); j++) {
	//	//	qDebug() << m_CSVData.at(i).value(j);
	//	//}
	//	qDebug() << m_CSVData.at(i);
	//}
}

void CSVManager::SetItem()
{
	if (m_CSVModel) {
		delete m_CSVModel;
		m_CSVModel = 0;
	}
	qDebug() << "Table Row " << m_CSVData.size();
	qDebug() << "Table Column " << m_CSVData.at(0).size();
	m_CSVModel = new QStandardItemModel(m_CSVData.size(), m_CSVData.at(0).size()+1);

	// set header
	for (int j = 0; j < m_CSVData.at(0).size()+1; j++) {
		m_CSVModel->setHeaderData(j, Qt::Horizontal, m_CSVData.at(0).value(j));
		//qDebug() << "Header " << j << " " << m_CSVData.at(0).value(j);
	}


	for (int i = 1; i < m_CSVData.size(); i++) {
		// set line number
		m_CSVModel->setVerticalHeaderItem(i-1, new QStandardItem(QString("%1").arg(i)));
		//qDebug() << "Line Number " << i;

		// set data (start index is no.1)
		for (int j = 0; j < m_CSVData.at(i).size()+1; j++) {
			m_CSVModel->setData(m_CSVModel->index(i-1, j), m_CSVData.at(i).value(j));
			//qDebug() << "Data i [" << i << "], j [" << j << "], [" << m_CSVData.at(i).value(j) << "]";
		}
	}
}

QStandardItemModel* CSVManager::GetItem()
{
	return m_CSVModel;
}
