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

#include "CSVKakao.h"

const int CSV_HEADER_ROW = 0;
const int CSV_START_ROW = 1;

CSVKakao::CSVKakao() :
	m_CSVModel(NULL)
	, m_CSVView(NULL)
{
	m_CSVData.clear();
	m_CSVHeader << "";
}

CSVKakao::~CSVKakao()
{
	if (m_CSVModel) {
		delete m_CSVModel;
		m_CSVModel = 0;
	}
}

bool CSVKakao::ReadFile(QString filepath)
{
	m_CSVData = QtCSV::Reader::readToList(filepath);
	// for debug
	//for (int i = 0; i < m_CSVData.size(); ++i) {
	//	for (int j = 0; j < m_CSVData.at(i).size(); j++) {
	//		qDebug() << m_CSVData.at(i).value(j);
	//	}
	//	qDebug() << m_CSVData.at(i);
	//}
	if (m_CSVData.at(CSV_START_ROW).size() == HEADER_KAKAO_MAX) {
		return true;
	}
	return false;
}

void CSVKakao::SetItem()
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

		m_TotalAmount += m_CSVData.at(i).value(HEADER_KAKAO_SALE_TOTAL).replace(",", "").toDouble();
		m_CalcAmount += m_CSVData.at(i).value(HEADER_KAKAO_CALCULATE).replace(",", "").toDouble();
		m_AuthorAmount += m_CSVData.at(i).value(HEADER_KAKAO_CALCULATE).replace(",", "").toDouble() * 0.7;
	}

	//qDebug() << "[KAKAO]-----------------------------";
	//qDebug() << "Row Count : " << m_CSVData.size();
	//qDebug() << "Column Count : " << m_CSVData.at(0).size();
	//qDebug() << QString("Total Amount : %L1").arg(m_TotalAmount, 0, 'f', 0);
	//qDebug() << QString("Calculate Amount : %L1").arg(m_CalcAmount, 0, 'f', 0);
	//qDebug() << QString("Author Amount : %L1").arg(m_AuthorAmount, 0, 'f', 0);
}

QTableView* CSVKakao::GetView()
{
	if (!m_CSVView) { m_CSVView = new QTableView(); }
	m_CSVView->setModel(GetItem());

	return m_CSVView;
}
