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

#include "calcCP/CalcCpDlg.h"
#include "CSVTotalCP.h"

#include "gemini_constants.h"

CSVTotalCP::CSVTotalCP() :
	m_CSVModel(NULL)
	, m_CSVView(NULL)
{
	m_CSVData.clear();
}

CSVTotalCP::~CSVTotalCP()
{
	if (m_CSVModel) {
		delete m_CSVModel;
		m_CSVModel = 0;
	}
}

void CSVTotalCP::InitCPData()
{
	m_TotalAmount = 0;
	m_CalcAmount = 0;
	m_AuthorAmount = 0;

	// table data
	if (m_CSVModel) {
		delete m_CSVModel;
		m_CSVModel = 0;
	}
	m_CSVModel = new QStandardItemModel(ROW_AMOUNT_MAX, CalcCPDlg::CP_MAX + 4);

	// set header
	m_CSVModel->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("ÃÑ°è"));

	// set line number
	m_CSVModel->setVerticalHeaderItem(ROW_AMOUNT_TOTAL, new QStandardItem("Total Amount"));		// total
	m_CSVModel->setVerticalHeaderItem(ROW_AMOUNT_CALCULATOR, new QStandardItem("Calc Amount"));		// calculation
	m_CSVModel->setVerticalHeaderItem(ROW_AMOUNT_AUTHOR, new QStandardItem("Author Amount"));	// author
	m_CSVModel->setVerticalHeaderItem(ROW_AMOUNT_RANK, new QStandardItem("Rank"));				// rank

}

void CSVTotalCP::SetCPTable(int column, QString total, QString calc, QString author, QString rank)
{
	//set data
	m_CSVModel->setData(m_CSVModel->index(ROW_AMOUNT_TOTAL, column), total);
	m_CSVModel->setData(m_CSVModel->index(ROW_AMOUNT_CALCULATOR, column), calc);
	m_CSVModel->setData(m_CSVModel->index(ROW_AMOUNT_AUTHOR, column), author);
	m_CSVModel->setData(m_CSVModel->index(ROW_AMOUNT_RANK, column), rank);

	// if column is not zero, add amount.
	if (0 < column && column <= (CalcCPDlg::CP_MAX)) {
		m_TotalAmount += total.replace(",", "").toDouble();
		m_CalcAmount += calc.replace(",", "").toDouble();
		m_AuthorAmount += author.replace(",", "").toDouble();
		m_RankAmount.insert(total.toDouble(), column);
	}
}

void CSVTotalCP::SetCPRank()
{
	int rankKepub = (m_RankAmount.count() - CalcCPDlg::CP_MAX > 0) ? m_RankAmount.count() - CalcCPDlg::CP_MAX : 0;
	int rank = m_RankAmount.count() - rankKepub;
	QMapIterator<double, int> i(m_RankAmount);
	while (i.hasNext()) {
		i.next();
		if (CalcCPDlg::CP_MAX - 3 != i.value()
			&& CalcCPDlg::CP_MAX - 2 != i.value()
			&& CalcCPDlg::CP_MAX - 1 != i.value()) {

			// for debug
			QString amount = QString("%L1").arg(i.key(), 0, 'f', 0);
			qDebug() << "Rank : " << rank << ", Amount : " << amount << ", Column : " << i.value();

			m_CSVModel->setData(m_CSVModel->index(ROW_AMOUNT_RANK, i.value()), rank);
			rank--;	// because of ascend order
		}
		else {
			// for debug
			QString amount = QString("%L1").arg(i.key(), 0, 'f', 0);
			qDebug() << "Kepub Rank : " << rankKepub << ", Amount : " << amount << ", Column : " << i.value();

			m_CSVModel->setData(m_CSVModel->index(ROW_AMOUNT_RANK, i.value()), rankKepub);
			rankKepub--;	// because of ascend order
		}
	}
}


void CSVTotalCP::SetItem(CalcCPDlg* cpData)
{
	InitCPData();

	if (cpData->GetKyobo()) {
		m_CSVModel->setHeaderData(CalcCPDlg::CP_KYOBO + 1, Qt::Horizontal, QString::fromLocal8Bit(CP_NAME.at(CalcCPDlg::CP_KYOBO).toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_KYOBO + 1
			, QString("%L1").arg(cpData->GetKyobo()->GetTotalAmount().at(CSVKyobo::BUSINESS_ALL), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKyobo()->GetCalcAmount().at(CSVKyobo::BUSINESS_ALL), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKyobo()->GetAuthorAmount().at(CSVKyobo::BUSINESS_ALL), 0, 'f', 0));
	}
	if (cpData->GetNaver()) {
		m_CSVModel->setHeaderData(CalcCPDlg::CP_NAVER + 1, Qt::Horizontal, QString::fromLocal8Bit(CP_NAME.at(CalcCPDlg::CP_NAVER).toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_NAVER + 1
			, QString("%L1").arg(cpData->GetNaver()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetNaver()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetNaver()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetRidi()) {
		m_CSVModel->setHeaderData(CalcCPDlg::CP_RIDI + 1, Qt::Horizontal, QString::fromLocal8Bit(CP_NAME.at(CalcCPDlg::CP_RIDI).toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_RIDI + 1
			, QString("%L1").arg(cpData->GetRidi()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetRidi()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetRidi()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetMunpia()) {
		m_CSVModel->setHeaderData(CalcCPDlg::CP_MUNPIA + 1, Qt::Horizontal, QString::fromLocal8Bit(CP_NAME.at(CalcCPDlg::CP_MUNPIA).toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_MUNPIA + 1
			, QString("%L1").arg(cpData->GetMunpia()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetMunpia()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetMunpia()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetMrblue()) {
		m_CSVModel->setHeaderData(CalcCPDlg::CP_MRBLUE + 1, Qt::Horizontal, QString::fromLocal8Bit(CP_NAME.at(CalcCPDlg::CP_MRBLUE).toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_MRBLUE + 1
			, QString("%L1").arg(cpData->GetMrblue()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetMrblue()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetMrblue()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetBarobook()) {
		m_CSVModel->setHeaderData(CalcCPDlg::CP_BAROBOOK + 1, Qt::Horizontal, QString::fromLocal8Bit(CP_NAME.at(CalcCPDlg::CP_BAROBOOK).toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_BAROBOOK + 1
			, QString("%L1").arg(cpData->GetBarobook()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetBarobook()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetBarobook()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetBookcube()) {
		m_CSVModel->setHeaderData(CalcCPDlg::CP_BOOKCUBE + 1, Qt::Horizontal, QString::fromLocal8Bit(CP_NAME.at(CalcCPDlg::CP_BOOKCUBE).toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_BOOKCUBE + 1
			, QString("%L1").arg(cpData->GetBookcube()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetBookcube()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetBookcube()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetEpyrus()) {
		m_CSVModel->setHeaderData(CalcCPDlg::CP_EPYRUS + 1, Qt::Horizontal, QString::fromLocal8Bit(CP_NAME.at(CalcCPDlg::CP_EPYRUS).toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_EPYRUS + 1
			, QString("%L1").arg(cpData->GetEpyrus()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetEpyrus()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetEpyrus()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetOebook()) {
		m_CSVModel->setHeaderData(CalcCPDlg::CP_OEBOOK + 1, Qt::Horizontal, QString::fromLocal8Bit(CP_NAME.at(CalcCPDlg::CP_OEBOOK).toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_OEBOOK + 1
			, QString("%L1").arg(cpData->GetOebook()->GetTotalAmount().at(CSVOebook::COMPANY_OEBOOK_ALL), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetOebook()->GetCalcAmount().at(CSVOebook::COMPANY_OEBOOK_ALL), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetOebook()->GetAuthorAmount().at(CSVOebook::COMPANY_OEBOOK_ALL), 0, 'f', 0));
	}
	if (cpData->GetOnestore()) {
		m_CSVModel->setHeaderData(CalcCPDlg::CP_ONESTORE + 1, Qt::Horizontal, QString::fromLocal8Bit(CP_NAME.at(CalcCPDlg::CP_ONESTORE).toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_ONESTORE + 1
			, QString("%L1").arg(cpData->GetOnestore()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetOnestore()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetOnestore()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetKakao()) {
		m_CSVModel->setHeaderData(CalcCPDlg::CP_KAKAO + 1, Qt::Horizontal, QString::fromLocal8Bit(CP_NAME.at(CalcCPDlg::CP_KAKAO).toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_KAKAO + 1
			, QString("%L1").arg(cpData->GetKakao()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKakao()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKakao()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetComico()) {
		m_CSVModel->setHeaderData(CalcCPDlg::CP_COMICO + 1, Qt::Horizontal, QString::fromLocal8Bit(CP_NAME.at(CalcCPDlg::CP_COMICO).toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_COMICO + 1
			, QString("%L1").arg(cpData->GetComico()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetComico()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetComico()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetTocsoda()) {
		m_CSVModel->setHeaderData(CalcCPDlg::CP_TOCSODA + 1, Qt::Horizontal, QString::fromLocal8Bit(CP_NAME.at(CalcCPDlg::CP_TOCSODA).toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_TOCSODA + 1
			, QString("%L1").arg(cpData->GetTocsoda()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetTocsoda()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetTocsoda()->GetAuthorAmount(), 0, 'f', 0));
	}
	if (cpData->GetKepub()) {
		m_CSVModel->setHeaderData(CalcCPDlg::CP_KEPUB + 1, Qt::Horizontal, QString::fromLocal8Bit(CP_NAME.at(CalcCPDlg::CP_KEPUB).toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_KEPUB + 1
			, QString("%L1").arg(cpData->GetKepub()->GetTotalAmount().at(CSVKepub::STORE_ALL), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKepub()->GetCalcAmount().at(CSVKepub::STORE_ALL), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKepub()->GetAuthorAmount().at(CSVKepub::STORE_ALL), 0, 'f', 0));

		// YES24
		m_CSVModel->setHeaderData(CalcCPDlg::CP_KEPUB + 2, Qt::Horizontal, QString::fromLocal8Bit("YES24"));
		SetCPTable(CalcCPDlg::CP_KEPUB + 2
			, QString("%L1").arg(cpData->GetKepub()->GetTotalAmount().at(CSVKepub::STORE_YES24), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKepub()->GetCalcAmount().at(CSVKepub::STORE_YES24), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKepub()->GetAuthorAmount().at(CSVKepub::STORE_YES24), 0, 'f', 0));
		// ALADDIN
		m_CSVModel->setHeaderData(CalcCPDlg::CP_KEPUB + 3, Qt::Horizontal, QString::fromLocal8Bit("ALADDIN"));
		SetCPTable(CalcCPDlg::CP_KEPUB + 3
			, QString("%L1").arg(cpData->GetKepub()->GetTotalAmount().at(CSVKepub::STORE_ALADDIN), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKepub()->GetCalcAmount().at(CSVKepub::STORE_ALADDIN), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKepub()->GetAuthorAmount().at(CSVKepub::STORE_ALADDIN), 0, 'f', 0));
		// BANDI
		m_CSVModel->setHeaderData(CalcCPDlg::CP_KEPUB + 4, Qt::Horizontal, QString::fromLocal8Bit("BANDI"));
		SetCPTable(CalcCPDlg::CP_KEPUB + 4
			, QString("%L1").arg(cpData->GetKepub()->GetTotalAmount().at(CSVKepub::STORE_BANDI), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKepub()->GetCalcAmount().at(CSVKepub::STORE_BANDI), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetKepub()->GetAuthorAmount().at(CSVKepub::STORE_BANDI), 0, 'f', 0));
	}
	if (cpData->GetJustoon()) {
		m_CSVModel->setHeaderData(CalcCPDlg::CP_JUSTOON + 1, Qt::Horizontal, QString::fromLocal8Bit(CP_NAME.at(CalcCPDlg::CP_JUSTOON).toStdString().c_str()));
		SetCPTable(CalcCPDlg::CP_JUSTOON + 1
			, QString("%L1").arg(cpData->GetJustoon()->GetTotalAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetJustoon()->GetCalcAmount(), 0, 'f', 0)
			, QString("%L1").arg(cpData->GetJustoon()->GetAuthorAmount(), 0, 'f', 0));
	}

	// total amount
	SetCPTable(0
		, QString("%L1").arg(m_TotalAmount, 0, 'f', 0)
		, QString("%L1").arg(m_CalcAmount, 0, 'f', 0)
		, QString("%L1").arg(m_AuthorAmount, 0, 'f', 0)
		, QString("%L1").arg(m_CalcAmount - m_AuthorAmount, 0, 'f', 0));

	// rank
	SetCPRank();

}

QTableView* CSVTotalCP::GetView()
{
	if (!m_CSVView) { m_CSVView = new QTableView(); }
	m_CSVView->setModel(GetItem());

	return m_CSVView;
}


void CSVTotalCP::WriteFile(QString filepath)
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
