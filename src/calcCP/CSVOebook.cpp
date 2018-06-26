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

bool CSVOebook::ReadFile(QString filepath)
{
	m_CSVData = QtCSV::Reader::readToList(filepath);
	if (m_CSVData.at(CSV_START_ROW).size() == HEADER_OEBOOK_MAX) {
		return true;
	}
	return false;
}

void CSVOebook::SetItem()
{
	double totalAmount = 0;
	double calcAmount = 0;
	double authorAmount = 0;

	double totalAmountOebook = 0;
	double calcAmountOebook = 0;
	double authorAmountOebook = 0;

	double totalAmountOebookRomance = 0;
	double calcAmountOebookRomance = 0;
	double authorAmountOebookRomance = 0;

	double totalAmountOebookMurim = 0;
	double calcAmountOebookMurim = 0;
	double authorAmountOebookMurim = 0;

	double totalAmountOebookComic = 0;
	double calcAmountOebookComic = 0;
	double authorAmountOebookComic = 0;

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
			m_CSVModel->setData(m_CSVModel->index(i - CSV_START_ROW, j), m_CSVData.at(i).value(j));
		}

		totalAmount += m_CSVData.at(i).value(HEADER_OEBOOK_TOTAL_AMOUNT).replace(",", "").toDouble();
		calcAmount += m_CSVData.at(i).value(HEADER_OEBOOK_CALCURATE_AMOUNT).replace(",", "").toDouble();
		authorAmount += m_CSVData.at(i).value(HEADER_OEBOOK_CALCURATE_AMOUNT).replace(",", "").toDouble() * 0.7;

		// oebook
		if (!m_CSVData.at(i).value(HEADER_OEBOOK_COMPANY).compare(QString::fromLocal8Bit("ø¿¿Ã∫œ"))) {
			totalAmountOebook += m_CSVData.at(i).value(HEADER_OEBOOK_TOTAL_AMOUNT).replace(",", "").toDouble();
			calcAmountOebook += m_CSVData.at(i).value(HEADER_OEBOOK_CALCURATE_AMOUNT).replace(",", "").toDouble();
			authorAmountOebook += m_CSVData.at(i).value(HEADER_OEBOOK_CALCURATE_AMOUNT).replace(",", "").toDouble() * 0.7;
		}
		// oebook romance
		else if (!m_CSVData.at(i).value(HEADER_OEBOOK_COMPANY).compare(QString::fromLocal8Bit("ø¿¿Ã∫œ(∑Œ∏¡)"))) {
			totalAmountOebookRomance += m_CSVData.at(i).value(HEADER_OEBOOK_TOTAL_AMOUNT).replace(",", "").toDouble();
			calcAmountOebookRomance += m_CSVData.at(i).value(HEADER_OEBOOK_CALCURATE_AMOUNT).replace(",", "").toDouble();
			authorAmountOebookRomance += m_CSVData.at(i).value(HEADER_OEBOOK_CALCURATE_AMOUNT).replace(",", "").toDouble() * 0.7;
		}
		// oebook murim
		else if (!m_CSVData.at(i).value(HEADER_OEBOOK_COMPANY).compare(QString::fromLocal8Bit("ø¿¿Ã∫œ(π´∏≤)"))) {
			totalAmountOebookMurim += m_CSVData.at(i).value(HEADER_OEBOOK_TOTAL_AMOUNT).replace(",", "").toDouble();
			calcAmountOebookMurim += m_CSVData.at(i).value(HEADER_OEBOOK_CALCURATE_AMOUNT).replace(",", "").toDouble();
			authorAmountOebookMurim += m_CSVData.at(i).value(HEADER_OEBOOK_CALCURATE_AMOUNT).replace(",", "").toDouble() * 0.7;
		}
		// oebook comic
		else if (!m_CSVData.at(i).value(HEADER_OEBOOK_COMPANY).compare(QString::fromLocal8Bit("ø¿¿Ã∫œ(ƒ⁄πÕ«√∑ØΩ∫)"))) {
			totalAmountOebookComic += m_CSVData.at(i).value(HEADER_OEBOOK_TOTAL_AMOUNT).replace(",", "").toDouble();
			calcAmountOebookComic += m_CSVData.at(i).value(HEADER_OEBOOK_CALCURATE_AMOUNT).replace(",", "").toDouble();
			authorAmountOebookComic += m_CSVData.at(i).value(HEADER_OEBOOK_CALCURATE_AMOUNT).replace(",", "").toDouble() * 0.7;
		}
	}

	qDebug() << "[OEBOOK]-----------------------------";
	qDebug() << "Row Count : " << m_CSVData.size();
	qDebug() << "Column Count : " << m_CSVData.at(0).size();
	qDebug() << QString("Total Amount : %L1").arg(totalAmount, 0, 'f', 0);
	qDebug() << QString("Calculate Amount : %L1").arg(calcAmount, 0, 'f', 0);
	qDebug() << QString("Author Amount : %L1").arg(authorAmount, 0, 'f', 0);
	qDebug() << QString("Total Amount Oebook: %L1").arg(totalAmountOebook, 0, 'f', 0);
	qDebug() << QString("Calculate Amount Oebook: %L1").arg(calcAmountOebook, 0, 'f', 0);
	qDebug() << QString("Author Amount Oebook: %L1").arg(authorAmountOebook, 0, 'f', 0);
	qDebug() << QString("Total Amount Romance : %L1").arg(totalAmountOebookRomance, 0, 'f', 0);
	qDebug() << QString("Calculate Amount Romance: %L1").arg(calcAmountOebookRomance, 0, 'f', 0);
	qDebug() << QString("Author Amount Romance: %L1").arg(authorAmountOebookRomance, 0, 'f', 0);
	qDebug() << QString("Total Amount Murim : %L1").arg(totalAmountOebookMurim, 0, 'f', 0);
	qDebug() << QString("Calculate Amount Murim: %L1").arg(calcAmountOebookMurim, 0, 'f', 0);
	qDebug() << QString("Author Amount Murim: %L1").arg(authorAmountOebookMurim, 0, 'f', 0);
	qDebug() << QString("Total Amount Comic: %L1").arg(totalAmountOebookComic, 0, 'f', 0);
	qDebug() << QString("Calculate Amount Comic: %L1").arg(calcAmountOebookComic, 0, 'f', 0);
	qDebug() << QString("Author Amount Comic: %L1").arg(authorAmountOebookComic, 0, 'f', 0);

	m_TotalAmount.append(totalAmount);
	m_TotalAmount.append(totalAmountOebook);
	m_TotalAmount.append(totalAmountOebookRomance);
	m_TotalAmount.append(totalAmountOebookMurim);
	m_TotalAmount.append(totalAmountOebookComic);

	m_CalcAmount.append(calcAmount);
	m_CalcAmount.append(calcAmountOebook);
	m_CalcAmount.append(calcAmountOebookRomance);
	m_CalcAmount.append(calcAmountOebookMurim);
	m_CalcAmount.append(calcAmountOebookComic);

	m_AuthorAmount.append(authorAmount);
	m_AuthorAmount.append(authorAmountOebook);
	m_AuthorAmount.append(authorAmountOebookRomance);
	m_AuthorAmount.append(authorAmountOebookMurim);
	m_AuthorAmount.append(authorAmountOebookComic);
}

QStandardItemModel* CSVOebook::GetItem()
{
	return m_CSVModel;
}

