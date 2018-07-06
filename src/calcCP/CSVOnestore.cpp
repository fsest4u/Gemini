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
#include "qtcsv/writer.h"
#include "qtcsv/stringdata.h"

#include "CSVOnestore.h"
#include "gemini_constants.h"

const int CSV_HEADER_ROW = 0;
const int CSV_START_ROW = 1;

CSVOnestore::CSVOnestore() :
	m_CSVModel(NULL)
	, m_CSVView(NULL)
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

void CSVOnestore::WriteFile(QString filepath)
{
	QStringList rowData;
	QtCSV::StringData strData;
	strData.clear();
	for (int row = 0; row < m_CSVModel->rowCount(); row++) {
		rowData.clear();
		for (int col = 0; col < m_CSVModel->columnCount(); col++) {
			rowData << m_CSVModel->index(row, col).data().toString();
		}
		//qDebug() << rowData;
		strData.addRow(rowData);
	}

	QtCSV::Writer::write(filepath, strData);
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
	m_CSVModel = new QStandardItemModel(m_CSVData.size() + CSV_TOTAL_ROW - CSV_START_ROW, m_CSVData.at(CSV_START_ROW).size());

	// set header
	for (int j = 0; j < m_CSVData.at(CSV_HEADER_ROW).size(); j++) {
		//m_CSVModel->setHeaderData(j, Qt::Horizontal, m_CSVData.at(CSV_HEADER_ROW).value(j));
		m_CSVModel->setData(m_CSVModel->index(CSV_TOTAL_ROW - 1, j), m_CSVData.at(CSV_HEADER_ROW).value(j));
	}

	for (int i = CSV_START_ROW; i < m_CSVData.size(); i++) {
		// set line number
		m_CSVModel->setVerticalHeaderItem(i - 1, new QStandardItem(QString("%1").arg(i)));

		for (int j = 0; j < m_CSVData.at(i).size(); j++) {
			m_CSVModel->setData(m_CSVModel->index(i - CSV_START_ROW + CSV_TOTAL_ROW, j), m_CSVData.at(i).value(j));
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

	m_CSVModel->setData(m_CSVModel->index(0, 0), QString::fromLocal8Bit("Total Amount"));
	m_CSVModel->setData(m_CSVModel->index(0, 1), QString("%L1").arg(m_TotalAmount, 0, 'f', 0));

	m_CSVModel->setData(m_CSVModel->index(1, 0), QString::fromLocal8Bit("Calculate Amount"));
	m_CSVModel->setData(m_CSVModel->index(1, 1), QString("%L1").arg(m_CalcAmount, 0, 'f', 0));

	m_CSVModel->setData(m_CSVModel->index(2, 0), QString::fromLocal8Bit("Author Amount"));
	m_CSVModel->setData(m_CSVModel->index(2, 1), QString("%L1").arg(m_AuthorAmount, 0, 'f', 0));
}

QTableView* CSVOnestore::GetView()
{
	if (!m_CSVView) { m_CSVView = new QTableView(); }
	m_CSVView->setModel(GetItem());

	return m_CSVView;
}
