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

#include "CSVOnestore.h"

const int CSV_HEADER_ROW = 0;
const int CSV_START_ROW = 1;

CSVOnestore::CSVOnestore() :
	m_CSVModel(NULL)
{
	m_CSVData.clear();
	m_CSVHeader << "";
}

CSVOnestore::~CSVOnestore()
{
	if (m_CSVModel) {
		delete m_CSVModel;
		m_CSVModel = 0;
	}
}

bool CSVOnestore::ReadFile(QString filepath)
{
	m_CSVData = QtCSV::Reader::readToList(filepath);
	if (m_CSVData.at(CSV_START_ROW).size() == HEADER_ONESTORE_MAX) {
		return true;
	}
	return false;
}

void CSVOnestore::SetItem()
{
	m_TotalAmount = 0;
	m_CalcAmount = 0;
	m_AuthorAmount = 0;

	if (m_CSVModel) {
		delete m_CSVModel;
		m_CSVModel = 0;
	}
	m_CSVModel = new QStandardItemModel(m_CSVData.size(), m_CSVData.at(0).size() + 1);

	// set header
	for (int j = 0; j < m_CSVData.at(0).size(); j++) {
		m_CSVModel->setHeaderData(j, Qt::Horizontal, m_CSVData.at(CSV_HEADER_ROW).value(j));
	}

	for (int i = CSV_START_ROW; i < m_CSVData.size(); i++) {
		// set line number
		m_CSVModel->setVerticalHeaderItem(i - 1, new QStandardItem(QString("%1").arg(i)));

		for (int j = 0; j < m_CSVData.at(i).size() + 1; j++) {
			m_CSVModel->setData(m_CSVModel->index(i - CSV_START_ROW, j), m_CSVData.at(i).value(j));
		}

		m_TotalAmount += m_CSVData.at(i).value(HEADER_ONESTORE_CUSTOM_CHARGE).replace(",", "").toDouble();
		m_CalcAmount += m_CSVData.at(i).value(HEADER_ONESTORE_CUSTOM_CHARGE).replace(",", "").toDouble() * 0.7;
		m_AuthorAmount += m_CSVData.at(i).value(HEADER_ONESTORE_CUSTOM_CHARGE).replace(",", "").toDouble() * 0.49;
	}

	//qDebug() << "[ONESTORE]-----------------------------";
	//qDebug() << "Row Count : " << m_CSVData.size();
	//qDebug() << "Column Count : " << m_CSVData.at(0).size();
	//qDebug() << QString("Total Amount : %L1").arg(m_TotalAmount, 0, 'f', 0);
	//qDebug() << QString("Calculate Amount : %L1").arg(m_CalcAmount, 0, 'f', 0);
	//qDebug() << QString("Author Amount : %L1").arg(m_AuthorAmount, 0, 'f', 0);
}

QStandardItemModel* CSVOnestore::GetItem()
{
	return m_CSVModel;
}

