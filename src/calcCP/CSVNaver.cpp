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

#include "CSVNaver.h"

const int CSV_HEADER_ROW_NAVER = 2;
const int CSV_START_ROW_NAVER = 6;

CSVNaver::CSVNaver() :
	m_CSVModel(NULL)
	, m_CSVView(NULL)
{
	m_CSVData.clear();
	m_CSVHeader << "";
}

CSVNaver::~CSVNaver()
{
	if (m_CSVModel) {
		delete m_CSVModel;
		m_CSVModel = 0;
	}
}

bool CSVNaver::ReadFile(QString filepath)
{
	m_CSVData = QtCSV::Reader::readToList(filepath);
	if (m_CSVData.at(CSV_START_ROW_NAVER).size() == HEADER_NAVER_MAX) {
		return true;
	}
	return false;
}

void CSVNaver::WriteFile(QString filepath)
{
	//QtCSV::Writer::write(filepath, );
}

void CSVNaver::SetItem()
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
		m_CSVModel->setHeaderData(j, Qt::Horizontal, m_CSVData.at(CSV_HEADER_ROW_NAVER).value(j));
	}

	// because of last row is sum data, -1
	for (int i = CSV_START_ROW_NAVER; i < m_CSVData.size() - 1; i++) {
		// set line number
		m_CSVModel->setVerticalHeaderItem(i - 1, new QStandardItem(QString("%1").arg(i)));

		for (int j = 0; j < m_CSVData.at(i).size() + 1; j++) {
			m_CSVModel->setData(m_CSVModel->index(i - CSV_START_ROW_NAVER, j), m_CSVData.at(i).value(j));
		}

		m_TotalAmount += m_CSVData.at(i).value(HEADER_NAVER_SALE_AMOUNT).replace(",", "").toDouble();
		m_CalcAmount += m_CSVData.at(i).value(HEADER_NAVER_SALE_AMOUNT).replace(",", "").toDouble() * 0.7;
		m_AuthorAmount += m_CSVData.at(i).value(HEADER_NAVER_SALE_AMOUNT).replace(",", "").toDouble() * 0.49;
	}

	//qDebug() << "[NAVER]-----------------------------";
	//qDebug() << "Row Count : " << m_CSVData.size();
	//qDebug() << "Column Count : " << m_CSVData.at(0).size();
	//qDebug() << QString("Total Amount : %L1").arg(m_TotalAmount, 0, 'f', 0);
	//qDebug() << QString("Calculate Amount : %L1").arg(m_CalcAmount, 0, 'f', 0);
	//qDebug() << QString("Author Amount : %L1").arg(m_AuthorAmount, 0, 'f', 0);
}

QTableView* CSVNaver::GetView()
{
	if (!m_CSVView) { m_CSVView = new QTableView(); }
	m_CSVView->setModel(GetItem());

	return m_CSVView;
}
