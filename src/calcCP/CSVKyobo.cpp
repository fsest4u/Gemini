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

#include "CSVKyobo.h"

const int CSV_HEADER_ROW = 0;
const int CSV_START_ROW = 1;

CSVKyobo::CSVKyobo() :
	m_CSVModel(NULL)
{
	m_CSVData.clear();
	m_CSVHeader << "";
}

CSVKyobo::~CSVKyobo()
{
	if (m_CSVModel) {
		delete m_CSVModel;
		m_CSVModel = 0;
	}
}

void CSVKyobo::ReadFile(QString filepath)
{
	m_CSVData = QtCSV::Reader::readToList(filepath);
}

void CSVKyobo::SetItem()
{
	double totalAmount = 0;
	double calcAmount = 0;
	double authorAmount = 0;

	double totalAmountB2C = 0;
	double calcAmountB2C = 0;
	double authorAmountB2C = 0;

	double totalAmountB2BC = 0;
	double calcAmountB2BC = 0;
	double authorAmountB2BC = 0;

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

		totalAmount += m_CSVData.at(i).value(HEADER_KYOBO_SALE_AMOUNT).replace(",", "").toDouble();
		calcAmount += m_CSVData.at(i).value(HEADER_KYOBO_CALCULATOR_AMOUNT).replace(",", "").toDouble();
		authorAmount += m_CSVData.at(i).value(HEADER_KYOBO_CALCULATOR_AMOUNT).replace(",", "").toDouble() * 0.7;

		// b2c
		if (!m_CSVData.at(i).value(HEADER_KYOBO_BUSINESS_TYPE).compare("B2C")) {
			totalAmountB2C += m_CSVData.at(i).value(HEADER_KYOBO_SALE_AMOUNT).replace(",", "").toDouble();
			calcAmountB2C += m_CSVData.at(i).value(HEADER_KYOBO_CALCULATOR_AMOUNT).replace(",", "").toDouble();
			authorAmountB2C += m_CSVData.at(i).value(HEADER_KYOBO_CALCULATOR_AMOUNT).replace(",", "").toDouble() * 0.7;
		}
		// b2bc
		else if (!m_CSVData.at(i).value(HEADER_KYOBO_BUSINESS_TYPE).compare("B2BC")) {
			totalAmountB2BC += m_CSVData.at(i).value(HEADER_KYOBO_SALE_AMOUNT).replace(",", "").toDouble();
			calcAmountB2BC += m_CSVData.at(i).value(HEADER_KYOBO_CALCULATOR_AMOUNT).replace(",", "").toDouble();
			authorAmountB2BC += m_CSVData.at(i).value(HEADER_KYOBO_CALCULATOR_AMOUNT).replace(",", "").toDouble() * 0.7;
		}
	}

	qDebug() << "[KYOBO]-----------------------------";
	qDebug() << "Row Count : " << m_CSVData.size();
	qDebug() << "Column Count : " << m_CSVData.at(0).size();
	qDebug() << QString("Total Amount : %L1").arg(totalAmount, 0, 'f', 0);
	qDebug() << QString("Calculate Amount : %L1").arg(calcAmount, 0, 'f', 0);
	qDebug() << QString("Author Amount : %L1").arg(authorAmount, 0, 'f', 0);
	qDebug() << QString("Total Amount B2C: %L1").arg(totalAmountB2C, 0, 'f', 0);
	qDebug() << QString("Calculate Amount B2C: %L1").arg(calcAmountB2C, 0, 'f', 0);
	qDebug() << QString("Author Amount B2C: %L1").arg(authorAmountB2C, 0, 'f', 0);
	qDebug() << QString("Total Amount B2BC: %L1").arg(totalAmountB2BC, 0, 'f', 0);
	qDebug() << QString("Calculate Amount B2BC: %L1").arg(calcAmountB2BC, 0, 'f', 0);
	qDebug() << QString("Author Amount B2BC: %L1").arg(authorAmountB2BC, 0, 'f', 0);

	m_TotalAmount.append(totalAmount);
	m_TotalAmount.append(totalAmountB2C);
	m_TotalAmount.append(totalAmountB2BC);

	m_CalcAmount.append(calcAmount);
	m_CalcAmount.append(calcAmountB2C);
	m_CalcAmount.append(calcAmountB2BC);

	m_AuthorAmount.append(authorAmount);
	m_AuthorAmount.append(authorAmountB2C);
	m_AuthorAmount.append(authorAmountB2BC);

}

QStandardItemModel* CSVKyobo::GetItem()
{
	return m_CSVModel;
}

