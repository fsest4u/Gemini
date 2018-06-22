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

#include "CSVOebook.h"

const int CSV_HEADER_ROW = 0;
const int CSV_START_ROW = 1;

CSVOebook::CSVOebook() :
	m_CSVModel(NULL)
{
	m_CSVData.clear();
	m_CSVHeader << "";
}

CSVOebook::~CSVOebook()
{
	if (m_CSVModel) {
		delete m_CSVModel;
		m_CSVModel = 0;
	}
}

void CSVOebook::ReadFile(QString filepath)
{
	m_CSVData = QtCSV::Reader::readToList(filepath);
}

void CSVOebook::SetItem()
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

		m_TotalAmount += m_CSVData.at(i).value(HEADER_OEBOOK_TOTAL_AMOUNT).replace(",", "").toDouble();
		m_CalcAmount += m_CSVData.at(i).value(HEADER_OEBOOK_CALCURATE_AMOUNT).replace(",", "").toDouble();
		m_AuthorAmount += m_CSVData.at(i).value(HEADER_OEBOOK_CALCURATE_AMOUNT).replace(",", "").toDouble() * 0.7;
	}

	qDebug() << "[OEBOOK]-----------------------------";
	qDebug() << "Row Count : " << m_CSVData.size();
	qDebug() << "Column Count : " << m_CSVData.at(0).size();
	qDebug() << QString("Total Amount : %L1").arg(m_TotalAmount, 0, 'f', 0);
	qDebug() << QString("Calculate Amount : %L1").arg(m_CalcAmount, 0, 'f', 0);
	qDebug() << QString("Author Amount : %L1").arg(m_AuthorAmount, 0, 'f', 0);
}

QStandardItemModel* CSVOebook::GetItem()
{
	return m_CSVModel;
}

