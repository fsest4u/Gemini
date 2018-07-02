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

#include "CSVMrblue.h"

const int CSV_HEADER_ROW = 4;
const int CSV_START_ROW = 5;
const int CSV_TOTAL_ROW = 4;

CSVMrblue::CSVMrblue() :
	m_CSVModel(NULL)
	, m_CSVView(NULL)
{
	m_CSVData.clear();
	m_CSVHeader << "";
}

CSVMrblue::~CSVMrblue()
{
	if (m_CSVModel) {
		delete m_CSVModel;
		m_CSVModel = 0;
	}
}

bool CSVMrblue::ReadFile(QString filepath)
{
	m_CSVData = QtCSV::Reader::readToList(filepath);
	if (m_CSVData.at(CSV_START_ROW).size() == HEADER_MRBLUE_MAX) {
		return true;
	}
	return false;
}

void CSVMrblue::WriteFile(QString filepath)
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

void CSVMrblue::SetItem()
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

	// because of last row is sum data, -1
	for (int i = CSV_START_ROW; i < m_CSVData.size() - 1; i++) {
		// set line number
		m_CSVModel->setVerticalHeaderItem(i - 1, new QStandardItem(QString("%1").arg(i)));

		for (int j = 0; j < m_CSVData.at(i).size() + 1; j++) {
			m_CSVModel->setData(m_CSVModel->index(i - CSV_START_ROW + CSV_TOTAL_ROW, j), m_CSVData.at(i).value(j));
		}

		m_TotalAmount += m_CSVData.at(i).value(HEADER_MRBLUE_TOTAL_AMOUNT).replace(",", "").toDouble();
		m_CalcAmount += m_CSVData.at(i).value(HEADER_MRBLUE_CALCULATOR_AMOUNT).replace(",", "").toDouble();
		m_AuthorAmount += m_CSVData.at(i).value(HEADER_MRBLUE_CALCULATOR_AMOUNT).replace(",", "").toDouble() * 0.7;
	}

	//qDebug() << "[MRBLUE]-----------------------------";
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

QTableView* CSVMrblue::GetView()
{
	if (!m_CSVView) { m_CSVView = new QTableView(); }
	m_CSVView->setModel(GetItem());

	return m_CSVView;
}

