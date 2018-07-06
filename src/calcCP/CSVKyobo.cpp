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

#include "misc/ProgressWidget.h"
#include "CalcCPDlg.h"
#include "CSVKyobo.h"
#include "gemini_constants.h"

const int CSV_HEADER_ROW = 0;
const int CSV_START_ROW = 1;

CSVKyobo::CSVKyobo() :
	m_CSVModel(NULL)
	, m_CSVView(NULL)
	, m_ProgressWidget(NULL)
{
	m_CSVData.clear();
	m_CSVHeader << "";

	m_ProgressWidget = new ProgressWidget();
}

CSVKyobo::~CSVKyobo()
{
	if (m_CSVModel) {
		delete m_CSVModel;
		m_CSVModel = 0;
	}

	if (m_ProgressWidget) {
		delete m_ProgressWidget;
		m_ProgressWidget = NULL;
	}
}

bool CSVKyobo::ReadFile(QString filepath)
{
	m_CSVData = QtCSV::Reader::readToList(filepath);
	if (m_CSVData.at(CSV_START_ROW).size() == HEADER_KYOBO_MAX) {
		return true;
	}
	return false;
}

void CSVKyobo::WriteFile(QString filepath)
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

void CSVKyobo::SetItem()
{
	m_ProgressWidget->InitProgress("Calculate", CSV_START_ROW, m_CSVData.size(), CalcCPDlg::CP_KYOBO, CalcCPDlg::CP_MAX);

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

		totalAmount += m_CSVData.at(i).value(HEADER_KYOBO_SALE_AMOUNT).replace(",", "").toDouble();
		calcAmount += m_CSVData.at(i).value(HEADER_KYOBO_CALCULATOR_AMOUNT).replace(",", "").toDouble();
		// todo - 60 ~ 70%
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

		m_ProgressWidget->SetValue(i);
	}
	m_ProgressWidget->Accept();

	//qDebug() << "[KYOBO]-----------------------------";
	//qDebug() << "Row Count : " << m_CSVData.size();
	//qDebug() << "Column Count : " << m_CSVData.at(0).size();
	//qDebug() << QString("Total Amount : %L1").arg(totalAmount, 0, 'f', 0);
	//qDebug() << QString("Calculate Amount : %L1").arg(calcAmount, 0, 'f', 0);
	//qDebug() << QString("Author Amount : %L1").arg(authorAmount, 0, 'f', 0);
	//qDebug() << QString("Total Amount B2C: %L1").arg(totalAmountB2C, 0, 'f', 0);
	//qDebug() << QString("Calculate Amount B2C: %L1").arg(calcAmountB2C, 0, 'f', 0);
	//qDebug() << QString("Author Amount B2C: %L1").arg(authorAmountB2C, 0, 'f', 0);
	//qDebug() << QString("Total Amount B2BC: %L1").arg(totalAmountB2BC, 0, 'f', 0);
	//qDebug() << QString("Calculate Amount B2BC: %L1").arg(calcAmountB2BC, 0, 'f', 0);
	//qDebug() << QString("Author Amount B2BC: %L1").arg(authorAmountB2BC, 0, 'f', 0);

	m_TotalAmount.append(totalAmount);
	m_TotalAmount.append(totalAmountB2C);
	m_TotalAmount.append(totalAmountB2BC);

	m_CalcAmount.append(calcAmount);
	m_CalcAmount.append(calcAmountB2C);
	m_CalcAmount.append(calcAmountB2BC);

	m_AuthorAmount.append(authorAmount);
	m_AuthorAmount.append(authorAmountB2C);
	m_AuthorAmount.append(authorAmountB2BC);

	m_CSVModel->setData(m_CSVModel->index(0, 0), QString::fromLocal8Bit("Total Amount"));
	m_CSVModel->setData(m_CSVModel->index(0, 1), QString("%L1").arg(totalAmount, 0, 'f', 0));
	m_CSVModel->setData(m_CSVModel->index(0, 2), QString::fromLocal8Bit("Total B2C"));
	m_CSVModel->setData(m_CSVModel->index(0, 3), QString("%L1").arg(totalAmountB2C, 0, 'f', 0));
	m_CSVModel->setData(m_CSVModel->index(0, 4), QString::fromLocal8Bit("Total B2BC"));
	m_CSVModel->setData(m_CSVModel->index(0, 5), QString("%L1").arg(totalAmountB2BC, 0, 'f', 0));

	m_CSVModel->setData(m_CSVModel->index(1, 0), QString::fromLocal8Bit("Calculate Amount"));
	m_CSVModel->setData(m_CSVModel->index(1, 1), QString("%L1").arg(calcAmount, 0, 'f', 0));
	m_CSVModel->setData(m_CSVModel->index(1, 2), QString::fromLocal8Bit("Calculate B2C"));
	m_CSVModel->setData(m_CSVModel->index(1, 3), QString("%L1").arg(calcAmountB2C, 0, 'f', 0));
	m_CSVModel->setData(m_CSVModel->index(1, 4), QString::fromLocal8Bit("Calculate B2BC"));
	m_CSVModel->setData(m_CSVModel->index(1, 5), QString("%L1").arg(calcAmountB2BC, 0, 'f', 0));

	m_CSVModel->setData(m_CSVModel->index(2, 0), QString::fromLocal8Bit("Author Amount"));
	m_CSVModel->setData(m_CSVModel->index(2, 1), QString("%L1").arg(authorAmount, 0, 'f', 0));
	m_CSVModel->setData(m_CSVModel->index(2, 2), QString::fromLocal8Bit("Author B2C"));
	m_CSVModel->setData(m_CSVModel->index(2, 3), QString("%L1").arg(authorAmountB2C, 0, 'f', 0));
	m_CSVModel->setData(m_CSVModel->index(2, 4), QString::fromLocal8Bit("Author B2BC"));
	m_CSVModel->setData(m_CSVModel->index(2, 5), QString("%L1").arg(authorAmountB2BC, 0, 'f', 0));

}

QTableView* CSVKyobo::GetView()
{
	if (!m_CSVView) { m_CSVView = new QTableView(); }
	m_CSVView->setModel(GetItem());

	return m_CSVView;
}


