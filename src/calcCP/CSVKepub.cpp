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

#include "CSVKepub.h"

const int CSV_HEADER_ROW = 0;
const int CSV_START_ROW = 1;

CSVKepub::CSVKepub() :
	m_CSVModel(NULL)
{
	m_CSVData.clear();
	m_CSVHeader << "";
}

CSVKepub::~CSVKepub()
{
	if (m_CSVModel) {
		delete m_CSVModel;
		m_CSVModel = 0;
	}
}

bool CSVKepub::ReadFile(QString filepath)
{
	m_CSVData = QtCSV::Reader::readToList(filepath);
	if (m_CSVData.at(CSV_START_ROW).size() == HEADER_KEPUB_MAX) {
		return true;
	}
	return false;
}

void CSVKepub::SetItem()
{
	double totalAmount = 0;
	double calcAmount = 0;
	double authorAmount = 0;

	double totalAmountYes24 = 0;
	double calcAmountYes24 = 0;
	double authorAmountYes24 = 0;

	double totalAmountAladdin = 0;
	double calcAmountAladdin = 0;
	double authorAmountAladdin = 0;

	double totalAmountBandi = 0;
	double calcAmountBandi = 0;
	double authorAmountBandi = 0;

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

		totalAmount += m_CSVData.at(i).value(HEADER_KEPUB_STORE_PRICE).replace(",", "").toDouble();
		totalAmount -= m_CSVData.at(i).value(HEADER_KEPUB_STORE_REFUND_PRICE).replace(",", "").toDouble();
		calcAmount += m_CSVData.at(i).value(HEADER_KEPUB_CALCULATOR_AMOUNT).replace(",", "").toDouble();
		authorAmount += m_CSVData.at(i).value(HEADER_KEPUB_CALCULATOR_AMOUNT).replace(",", "").toDouble() * 0.7;

		// yes24
		if (!m_CSVData.at(i).value(HEADER_KEPUB_BOOK_STORE).compare("YES24")) {
			totalAmountYes24 += m_CSVData.at(i).value(HEADER_KEPUB_STORE_PRICE).replace(",", "").toDouble();
			totalAmountYes24 -= m_CSVData.at(i).value(HEADER_KEPUB_STORE_REFUND_PRICE).replace(",", "").toDouble();
			calcAmountYes24 += m_CSVData.at(i).value(HEADER_KEPUB_CALCULATOR_AMOUNT).replace(",", "").toDouble();
			authorAmountYes24 += m_CSVData.at(i).value(HEADER_KEPUB_CALCULATOR_AMOUNT).replace(",", "").toDouble() * 0.7;
		}
		// aladdin
		else if (!m_CSVData.at(i).value(HEADER_KEPUB_BOOK_STORE).compare(QString::fromLocal8Bit("¾Ë¶óµò"))) {
			totalAmountAladdin += m_CSVData.at(i).value(HEADER_KEPUB_STORE_PRICE).replace(",", "").toDouble();
			totalAmountAladdin -= m_CSVData.at(i).value(HEADER_KEPUB_STORE_REFUND_PRICE).replace(",", "").toDouble();
			calcAmountAladdin += m_CSVData.at(i).value(HEADER_KEPUB_CALCULATOR_AMOUNT).replace(",", "").toDouble();
			authorAmountAladdin += m_CSVData.at(i).value(HEADER_KEPUB_CALCULATOR_AMOUNT).replace(",", "").toDouble() * 0.7;
		}
		// bandinrunis
		else if (!m_CSVData.at(i).value(HEADER_KEPUB_BOOK_STORE).compare(QString::fromLocal8Bit("¹Ýµð¾Ø·ç´Ï½º"))) {
			totalAmountBandi += m_CSVData.at(i).value(HEADER_KEPUB_STORE_PRICE).replace(",", "").toDouble();
			totalAmountBandi -= m_CSVData.at(i).value(HEADER_KEPUB_STORE_REFUND_PRICE).replace(",", "").toDouble();
			calcAmountBandi += m_CSVData.at(i).value(HEADER_KEPUB_CALCULATOR_AMOUNT).replace(",", "").toDouble();
			authorAmountBandi += m_CSVData.at(i).value(HEADER_KEPUB_CALCULATOR_AMOUNT).replace(",", "").toDouble() * 0.7;
		}
	}

	//qDebug() << "[KEPUB]-----------------------------";
	//qDebug() << "Row Count : " << m_CSVData.size();
	//qDebug() << "Column Count : " << m_CSVData.at(0).size();
	//qDebug() << QString("Total Amount : %L1").arg(totalAmount, 0, 'f', 0);
	//qDebug() << QString("Calculate Amount : %L1").arg(calcAmount, 0, 'f', 0);
	//qDebug() << QString("Author Amount : %L1").arg(authorAmount, 0, 'f', 0);
	//qDebug() << QString("Total Amount Yes24 : %L1").arg(totalAmountYes24, 0, 'f', 0);
	//qDebug() << QString("Calculate Amount Yes24 : %L1").arg(calcAmountYes24, 0, 'f', 0);
	//qDebug() << QString("Author Amount Yes24 : %L1").arg(authorAmountYes24, 0, 'f', 0);
	//qDebug() << QString("Total Amount Aladdin : %L1").arg(totalAmountAladdin, 0, 'f', 0);
	//qDebug() << QString("Calculate Amount Aladdin : %L1").arg(calcAmountAladdin, 0, 'f', 0);
	//qDebug() << QString("Author Amount Aladdin : %L1").arg(authorAmountAladdin, 0, 'f', 0);
	//qDebug() << QString("Total Amount Bandi : %L1").arg(totalAmountBandi, 0, 'f', 0);
	//qDebug() << QString("Calculate Amount Bandi : %L1").arg(calcAmountBandi, 0, 'f', 0);
	//qDebug() << QString("Author Amount Bandi : %L1").arg(authorAmountBandi, 0, 'f', 0);

	m_TotalAmount.append(totalAmount);
	m_TotalAmount.append(totalAmountYes24);
	m_TotalAmount.append(totalAmountAladdin);
	m_TotalAmount.append(totalAmountBandi);

	m_CalcAmount.append(calcAmount);
	m_CalcAmount.append(calcAmountYes24);
	m_CalcAmount.append(calcAmountAladdin);
	m_CalcAmount.append(calcAmountBandi);

	m_AuthorAmount.append(authorAmount);
	m_AuthorAmount.append(authorAmountYes24);
	m_AuthorAmount.append(authorAmountAladdin);
	m_AuthorAmount.append(authorAmountBandi);

}

QStandardItemModel* CSVKepub::GetItem()
{
	return m_CSVModel;
}
