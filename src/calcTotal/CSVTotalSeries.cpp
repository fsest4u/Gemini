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
#include "CSVTotalSeries.h"

#include "gemini_constants.h"

CSVTotalSeries::CSVTotalSeries() :
	m_CSVModel(NULL)
	, m_CSVView(NULL)
{
	//m_CSVData.clear();
	m_SeriesList.clear();
}

CSVTotalSeries::~CSVTotalSeries()
{
	if (m_CSVModel) {
		delete m_CSVModel;
		m_CSVModel = 0;
	}
}

void CSVTotalSeries::InitSeriesData()
{
	//m_TotalAmount.clear();
	//m_CalcAmount.clear();
	//m_AuthorAmount.clear();

	// table data
	if (m_CSVModel) {
		delete m_CSVModel;
		m_CSVModel = 0;
	}

	m_CSVModel = new QStandardItemModel(m_SeriesList.count() + ROW_MAX, COLUMN_MAX);

	// set header
	//m_CSVModel->setHeaderData(COLUMN_TITLE, Qt::Horizontal, QString::fromLocal8Bit("작품제목"));
	//m_CSVModel->setHeaderData(COLUMN_RANK, Qt::Horizontal, QString::fromLocal8Bit("랭킹"));
	m_CSVModel->setData(m_CSVModel->index(ROW_HEADER, COLUMN_TITLE), QString::fromLocal8Bit("작품제목"));
	m_CSVModel->setData(m_CSVModel->index(ROW_HEADER, COLUMN_RANK), QString::fromLocal8Bit("랭킹"));
	m_CSVModel->setVerticalHeaderItem(ROW_AMOUNT_NAME, new QStandardItem(QString::fromLocal8Bit("구분")));		// total
	m_CSVModel->setVerticalHeaderItem(ROW_AMOUNT, new QStandardItem(QString::fromLocal8Bit("합계")));		// calculation

	// total amount
	//m_CSVModel->setHeaderData(COLUMN_AMOUNT_TOTAL, Qt::Horizontal, QString::fromLocal8Bit("총계"));
	//m_CSVModel->setHeaderData(COLUMN_AMOUNT_TOTAL + 1, Qt::Horizontal, QString::fromLocal8Bit(""));
	//m_CSVModel->setHeaderData(COLUMN_AMOUNT_TOTAL + 2, Qt::Horizontal, QString::fromLocal8Bit(""));
	m_CSVModel->setData(m_CSVModel->index(ROW_HEADER, COLUMN_AMOUNT_TOTAL), QString::fromLocal8Bit("총계"));
	m_CSVModel->setData(m_CSVModel->index(ROW_HEADER, COLUMN_AMOUNT_TOTAL + 1), QString::fromLocal8Bit(""));
	m_CSVModel->setData(m_CSVModel->index(ROW_HEADER, COLUMN_AMOUNT_TOTAL + 2), QString::fromLocal8Bit(""));

	m_CSVModel->setData(m_CSVModel->index(ROW_AMOUNT_NAME, COLUMN_AMOUNT_TOTAL), QString::fromLocal8Bit("매출액"));
	m_CSVModel->setData(m_CSVModel->index(ROW_AMOUNT_NAME, COLUMN_AMOUNT_TOTAL + 1), QString::fromLocal8Bit("정산액"));
	m_CSVModel->setData(m_CSVModel->index(ROW_AMOUNT_NAME, COLUMN_AMOUNT_TOTAL + 2), QString::fromLocal8Bit("작가정산액"));

	// cp total amount, 3 spaces
	for (int i = 0; i < CalcCPDlg::CP_MAX; i++) {
		//m_CSVModel->setHeaderData(COLUMN_KYOBO_TOTAL + i * 3, Qt::Horizontal, QString::fromLocal8Bit(CP_NAME.at(i).toStdString().c_str()));
		//m_CSVModel->setHeaderData(COLUMN_KYOBO_TOTAL + i * 3 + 1, Qt::Horizontal, QString::fromLocal8Bit(""));
		//m_CSVModel->setHeaderData(COLUMN_KYOBO_TOTAL + i * 3 + 2, Qt::Horizontal, QString::fromLocal8Bit(""));
		m_CSVModel->setData(m_CSVModel->index(ROW_HEADER, COLUMN_KYOBO_TOTAL + i * 3), QString::fromLocal8Bit(CP_NAME.at(i).toStdString().c_str()));
		m_CSVModel->setData(m_CSVModel->index(ROW_HEADER, COLUMN_KYOBO_TOTAL + i * 3 + 1), QString::fromLocal8Bit(""));
		m_CSVModel->setData(m_CSVModel->index(ROW_HEADER, COLUMN_KYOBO_TOTAL + i * 3 + 2), QString::fromLocal8Bit(""));

		m_CSVModel->setData(m_CSVModel->index(ROW_AMOUNT_NAME, COLUMN_KYOBO_TOTAL + i * 3), QString::fromLocal8Bit("매출액"));
		m_CSVModel->setData(m_CSVModel->index(ROW_AMOUNT_NAME, COLUMN_KYOBO_TOTAL + i * 3 + 1), QString::fromLocal8Bit("정산액"));
		m_CSVModel->setData(m_CSVModel->index(ROW_AMOUNT_NAME, COLUMN_KYOBO_TOTAL + i * 3 + 2), QString::fromLocal8Bit("작가정산액"));
	}

}

void CSVTotalSeries::SetSeriesTable()
{
	QMap<int, double> amountCPList;
	amountCPList.clear();

	// Total by Series
	double totalAmountSeries = 0;
	double calcAmountSeries = 0;
	double authorAmountSeries = 0;

	// Total by CP
	double tempAmountCP = 0;

	//set data
	int row = ROW_AMOUNT + 1;
	QMap<QString, QMap<int, double>>::const_iterator bookHash = m_SeriesList.constBegin();
	while (bookHash != m_SeriesList.constEnd()) {

		//qDebug() << bookHash.key() << ": " << bookHash.value();
		// set title
		m_CSVModel->setData(m_CSVModel->index(row, COLUMN_TITLE), bookHash.key());
		
		totalAmountSeries = 0;
		calcAmountSeries = 0;
		authorAmountSeries = 0;

		tempAmountCP = 0;

		QMap<int, double>::const_iterator amountHash = bookHash.value().constBegin();
		while (amountHash != bookHash.value().constEnd()) {

			//qDebug() << amountHash.key() << ": " << QString("%L1").arg(amountHash.value(), 0, 'f', 0);
			// Amount by CP
			m_CSVModel->setData(m_CSVModel->index(row, amountHash.key()), QString("%L1").arg(amountHash.value(), 0, 'f', 0));

			// Total by CP
			tempAmountCP = amountCPList.value(amountHash.key());
			tempAmountCP += amountHash.value();
			amountCPList.insert(amountHash.key(), tempAmountCP);

			if (COLUMN_KYOBO_TOTAL == amountHash.key()
				|| COLUMN_NAVER_TOTAL == amountHash.key()
				|| COLUMN_RIDI_TOTAL == amountHash.key()
				|| COLUMN_MUNPIA_TOTAL == amountHash.key()
				|| COLUMN_MRBLUE_TOTAL == amountHash.key()
				|| COLUMN_BAROBOOK_TOTAL == amountHash.key()
				|| COLUMN_BOOKCUBE_TOTAL == amountHash.key()
				|| COLUMN_EPYRUS_TOTAL == amountHash.key()
				|| COLUMN_OEBOOK_TOTAL == amountHash.key()
				|| COLUMN_ONESTORE_TOTAL == amountHash.key()
				|| COLUMN_KAKAO_TOTAL == amountHash.key()
				|| COLUMN_COMICO_TOTAL == amountHash.key()
				|| COLUMN_TOCSODA_TOTAL == amountHash.key()
				|| COLUMN_JUSTOON_TOTAL == amountHash.key()
				|| COLUMN_GOOGLE_TOTAL == amountHash.key()
				|| COLUMN_KEPUB_TOTAL == amountHash.key()) {

				totalAmountSeries += amountHash.value();
			}
			else if (COLUMN_KYOBO_CALC == amountHash.key()
				|| COLUMN_NAVER_CALC == amountHash.key()
				|| COLUMN_RIDI_CALC == amountHash.key()
				|| COLUMN_MUNPIA_CALC == amountHash.key()
				|| COLUMN_MRBLUE_CALC == amountHash.key()
				|| COLUMN_BAROBOOK_CALC == amountHash.key()
				|| COLUMN_BOOKCUBE_CALC == amountHash.key()
				|| COLUMN_EPYRUS_CALC == amountHash.key()
				|| COLUMN_OEBOOK_CALC == amountHash.key()
				|| COLUMN_ONESTORE_CALC == amountHash.key()
				|| COLUMN_KAKAO_CALC == amountHash.key()
				|| COLUMN_COMICO_CALC == amountHash.key()
				|| COLUMN_TOCSODA_CALC == amountHash.key()
				|| COLUMN_JUSTOON_CALC == amountHash.key()
				|| COLUMN_GOOGLE_CALC == amountHash.key()
				|| COLUMN_KEPUB_CALC == amountHash.key()) {

				calcAmountSeries += amountHash.value();

			}
			else if (COLUMN_KYOBO_AUTHOR == amountHash.key()
				|| COLUMN_NAVER_AUTHOR == amountHash.key()
				|| COLUMN_RIDI_AUTHOR == amountHash.key()
				|| COLUMN_MUNPIA_AUTHOR == amountHash.key()
				|| COLUMN_MRBLUE_AUTHOR == amountHash.key()
				|| COLUMN_BAROBOOK_AUTHOR == amountHash.key()
				|| COLUMN_BOOKCUBE_AUTHOR == amountHash.key()
				|| COLUMN_EPYRUS_AUTHOR == amountHash.key()
				|| COLUMN_OEBOOK_AUTHOR == amountHash.key()
				|| COLUMN_ONESTORE_AUTHOR == amountHash.key()
				|| COLUMN_KAKAO_AUTHOR == amountHash.key()
				|| COLUMN_COMICO_AUTHOR == amountHash.key()
				|| COLUMN_TOCSODA_AUTHOR == amountHash.key()
				|| COLUMN_JUSTOON_AUTHOR == amountHash.key()
				|| COLUMN_GOOGLE_AUTHOR == amountHash.key()
				|| COLUMN_KEPUB_AUTHOR == amountHash.key()) {

				authorAmountSeries += amountHash.value();
			}
			amountHash++;
		}
		// Total by book
		m_CSVModel->setData(m_CSVModel->index(row, COLUMN_AMOUNT_TOTAL), QString("%L1").arg(totalAmountSeries, 0, 'f', 0) );
		m_CSVModel->setData(m_CSVModel->index(row, COLUMN_AMOUNT_CALC), QString("%L1").arg(calcAmountSeries, 0, 'f', 0) );
		m_CSVModel->setData(m_CSVModel->index(row, COLUMN_AMOUNT_AUTHOR), QString("%L1").arg(authorAmountSeries, 0, 'f', 0) );

		// Total Sum
		tempAmountCP = amountCPList.value(COLUMN_AMOUNT_TOTAL);
		tempAmountCP += totalAmountSeries;
		amountCPList.insert(COLUMN_AMOUNT_TOTAL, tempAmountCP);

		tempAmountCP = amountCPList.value(COLUMN_AMOUNT_CALC);
		tempAmountCP += calcAmountSeries;
		amountCPList.insert(COLUMN_AMOUNT_CALC, tempAmountCP);

		tempAmountCP = amountCPList.value(COLUMN_AMOUNT_AUTHOR);
		tempAmountCP += authorAmountSeries;
		amountCPList.insert(COLUMN_AMOUNT_AUTHOR, tempAmountCP);

		row++; bookHash++;
	}

	// Total List by CP & Total Sum
	for (int i = COLUMN_AMOUNT_TOTAL; i < COLUMN_MAX; i++) {
		m_CSVModel->setData(m_CSVModel->index(ROW_AMOUNT, i), QString("%L1").arg(amountCPList.value(i), 0, 'f', 0) );
	}
}

// todo - rank
void CSVTotalSeries::SetSeriesRank()
{
	//int rank = m_RankAmount.count();
	//QMapIterator<double, int> i(m_RankAmount);
	//while (i.hasNext()) {
	//	i.next();

	//	// for debug
	//	QString amount = QString("%L1").arg(i.key(), 0, 'f', 0);
	//	qDebug() << "Rank : " << rank << ", Amount : " << amount << ", Column : " << i.value();

	//	m_CSVModel->setData(m_CSVModel->index(ROW_AMOUNT_RANK, i.value()), rank);
	//	rank--;	// because of ascend order
	//}
}

void CSVTotalSeries::MakeSeriesKyobo(QStandardItemModel* item)
{
	int headerTitle = 0;
	int headerTotal = -1;
	int headerCalc = -1;
	int headerAuthor = -1;

	int bookTotal = 0;
	int bookCalc = 0;
	int bookAuthor = 0;

	headerTitle = CSVKyobo::HEADER_KYOBO_TITLE;
	headerTotal = CSVKyobo::HEADER_KYOBO_SALE_AMOUNT;
	headerCalc = CSVKyobo::HEADER_KYOBO_CALCULATOR_AMOUNT;

	bookTotal = COLUMN_KYOBO_TOTAL;
	bookCalc = COLUMN_KYOBO_CALC;
	bookAuthor = COLUMN_KYOBO_AUTHOR;

	QString title;

	double total = 0;
	double calc = 0;
	double author = 0;

	QMap<int, double> amountList;

	for (int row = CSV_TOTAL_ROW; row < item->rowCount(); row++) {

		amountList.clear();

		total = 0;
		calc = 0;
		author = 0;

		title = GetSeriesName(item->data(item->index(row, headerTitle)).toString());
		if (title.isEmpty()) { continue; }

		total += item->data(item->index(row, headerTotal)).toString().replace(",", "").toDouble();
		calc = item->data(item->index(row, headerCalc)).toString().replace(",", "").toDouble();
		author = calc * 0.7;

		// exist
		if (m_SeriesList.contains(title)) {
			// find book
			amountList = m_SeriesList.value(title);
			// update amount
			total += amountList.value(bookTotal);
			calc += amountList.value(bookCalc);
			author += amountList.value(bookAuthor);
		}
		//for debug
		//qDebug() << "[MakeSeriesKyobo]-----------------------------";
		//qDebug() << "Title : " << title;
		//qDebug() << QString("Total Amount : %L1").arg(total, 0, 'f', 0);
		//qDebug() << QString("Calculate Amount : %L1").arg(calc, 0, 'f', 0);
		//qDebug() << QString("Author Amount : %L1").arg(author, 0, 'f', 0);

		amountList.insert(bookTotal, total);
		amountList.insert(bookCalc, calc);
		amountList.insert(bookAuthor, author);

		// update book
		m_SeriesList.insert(title, amountList);	// replace item
	}
}

void CSVTotalSeries::MakeSeriesNaver(QStandardItemModel* item)
{
	int headerTitle = 0;
	int headerTotal = -1;
	int headerCalc = -1;
	int headerAuthor = -1;

	int bookTotal = 0;
	int bookCalc = 0;
	int bookAuthor = 0;

	headerTitle = CSVNaver::HEADER_NAVER_TITILE;
	headerTotal = CSVNaver::HEADER_NAVER_SALE_AMOUNT;

	bookTotal = COLUMN_NAVER_TOTAL;
	bookCalc = COLUMN_NAVER_CALC;
	bookAuthor = COLUMN_NAVER_AUTHOR;

	QString title;

	double total = 0;
	double calc = 0;
	double author = 0;

	QMap<int, double> amountList;
	
	for (int row = CSV_TOTAL_ROW; row < item->rowCount(); row++) {

		amountList.clear();
		
		total = 0;
		calc = 0;
		author = 0;

		title = GetSeriesName(item->data(item->index(row, headerTitle)).toString());
		if (title.isEmpty()) { continue; }

		total += item->data(item->index(row, headerTotal)).toString().replace(",", "").toDouble();
		// case naver, munpia, onestore
		calc = total * 0.7;
		author = calc * 0.7;

		// exist
		if (m_SeriesList.contains(title)) {
			// find book
			amountList = m_SeriesList.value(title);
			// update amount
			total += amountList.value(bookTotal);
			calc += amountList.value(bookCalc);
			author += amountList.value(bookAuthor);
		}
		//for debug
		//qDebug() << "[MakeSeriesNaver]-----------------------------";
		//qDebug() << "Title : " << title;
		//qDebug() << QString("Total Amount : %L1").arg(total, 0, 'f', 0);
		//qDebug() << QString("Calculate Amount : %L1").arg(calc, 0, 'f', 0);
		//qDebug() << QString("Author Amount : %L1").arg(author, 0, 'f', 0);

		amountList.insert(bookTotal, total);
		amountList.insert(bookCalc, calc);
		amountList.insert(bookAuthor, author);

		// update book
		m_SeriesList.insert(title, amountList);	// replace item
	}
}

void CSVTotalSeries::MakeSeriesRidi(QStandardItemModel* item)
{
	int headerTitle = 0;
	QList<int> headerTotal;	headerTotal.clear();
	int headerCalc = -1;
	int headerAuthor = -1;

	int bookTotal = 0;
	int bookCalc = 0;
	int bookAuthor = 0;

	headerTitle = CSVRidi::HEADER_RIDI_TITLE;
	headerTotal.insert(0, CSVRidi::HEADER_RIDI_BOOK_AMOUNT);
	headerTotal.insert(1, CSVRidi::HEADER_RIDI_RENTAL_AMOUNT);
	headerTotal.insert(2, CSVRidi::HEADER_RIDI_SET_AMOUNT);
	headerTotal.insert(3, CSVRidi::HEADER_RIDI_SET_RENTAL_AMOUNT);
	headerTotal.insert(4, CSVRidi::HEADER_RIDI_CANCEL_AMOUNT);
	headerCalc = CSVRidi::HEADER_RIDI_CALCULATOR_AMOUNT;

	bookTotal = COLUMN_RIDI_TOTAL;
	bookCalc = COLUMN_RIDI_CALC;
	bookAuthor = COLUMN_RIDI_AUTHOR;

	QString title;

	double total = 0;
	double calc = 0;
	double author = 0;

	QMap<int, double> amountList;
	
	for (int row = CSV_TOTAL_ROW; row < item->rowCount(); row++) {

		amountList.clear();
		
		total = 0;
		calc = 0;
		author = 0;

		title = GetSeriesName(item->data(item->index(row, headerTitle)).toString());
		if (title.isEmpty()) { continue; }

		// case ridi, comico, kepub
		for (int i = 0; i < headerTotal.count(); i++) {
			total += item->data(item->index(row, headerTotal.at(i))).toString().replace(",", "").toDouble();
		}

		calc = item->data(item->index(row, headerCalc)).toString().replace(",", "").toDouble();
		author = calc * 0.7;

		// exist
		if (m_SeriesList.contains(title)) {
			// find book
			amountList = m_SeriesList.value(title);
			// update amount
			total += amountList.value(bookTotal);
			calc += amountList.value(bookCalc);
			author += amountList.value(bookAuthor);
		}
		//for debug
		//qDebug() << "[MakeSeriesRidi]-----------------------------";
		//qDebug() << "Title : " << title;
		//qDebug() << QString("Total Amount : %L1").arg(total, 0, 'f', 0);
		//qDebug() << QString("Calculate Amount : %L1").arg(calc, 0, 'f', 0);
		//qDebug() << QString("Author Amount : %L1").arg(author, 0, 'f', 0);

		amountList.insert(bookTotal, total);
		amountList.insert(bookCalc, calc);
		amountList.insert(bookAuthor, author);

		// update book
		m_SeriesList.insert(title, amountList);	// replace item
	}
}

void CSVTotalSeries::MakeSeriesMunpia(QStandardItemModel* item)
{
	int headerTitle = 0;
	int headerTotal = -1;
	int headerCalc = -1;
	int headerAuthor = -1;

	int bookTotal = 0;
	int bookCalc = 0;
	int bookAuthor = 0;

	headerTitle = CSVMunpia::HEADER_MUNPIA_TITLE;
	headerTotal = CSVMunpia::HEADER_MUNPIA_REAL_AMOUNT;

	bookTotal = COLUMN_MUNPIA_TOTAL;
	bookCalc = COLUMN_MUNPIA_CALC;
	bookAuthor = COLUMN_MUNPIA_AUTHOR;

	QString title;

	double total = 0;
	double calc = 0;
	double author = 0;

	QMap<int, double> amountList;
	
	for (int row = CSV_TOTAL_ROW; row < item->rowCount() - 1; row++) {

		amountList.clear();
		
		total = 0;
		calc = 0;
		author = 0;

		title = GetSeriesName(item->data(item->index(row, headerTitle)).toString());
		if (title.isEmpty()) { continue; }

		total += item->data(item->index(row, headerTotal)).toString().replace(",", "").toDouble();
		// case naver, munpia, onestore
		calc = total * 0.7;
		author = calc * 0.7;

		// exist
		if (m_SeriesList.contains(title)) {
			// find book
			amountList = m_SeriesList.value(title);
			// update amount
			total += amountList.value(bookTotal);
			calc += amountList.value(bookCalc);
			author += amountList.value(bookAuthor);
		}
		//for debug
		//qDebug() << "[MakeSeriesMunpia]-----------------------------";
		//qDebug() << "Title : " << title;
		//qDebug() << QString("Total Amount : %L1").arg(total, 0, 'f', 0);
		//qDebug() << QString("Calculate Amount : %L1").arg(calc, 0, 'f', 0);
		//qDebug() << QString("Author Amount : %L1").arg(author, 0, 'f', 0);

		amountList.insert(bookTotal, total);
		amountList.insert(bookCalc, calc);
		amountList.insert(bookAuthor, author);

		// update book
		m_SeriesList.insert(title, amountList);	// replace item
	}
}

void CSVTotalSeries::MakeSeriesMrblue(QStandardItemModel* item)
{
	int headerTitle = 0;
	int headerTotal = -1;
	int headerCalc = -1;
	int headerAuthor = -1;

	int bookTotal = 0;
	int bookCalc = 0;
	int bookAuthor = 0;

	headerTitle = CSVMrblue::HEADER_MRBLUE_TITLE;
	headerTotal = CSVMrblue::HEADER_MRBLUE_TOTAL_AMOUNT;
	headerCalc = CSVMrblue::HEADER_MRBLUE_CALCULATOR_AMOUNT;

	bookTotal = COLUMN_MRBLUE_TOTAL;
	bookCalc = COLUMN_MRBLUE_CALC;
	bookAuthor = COLUMN_MRBLUE_AUTHOR;

	QString title;

	double total = 0;
	double calc = 0;
	double author = 0;

	QMap<int, double> amountList;
	
	for (int row = CSV_TOTAL_ROW; row < item->rowCount(); row++) {

		amountList.clear();
		
		total = 0;
		calc = 0;
		author = 0;

		title = GetSeriesName(item->data(item->index(row, headerTitle)).toString());
		if (title.isEmpty()) { continue; }

		total += item->data(item->index(row, headerTotal)).toString().replace(",", "").toDouble();
		calc = item->data(item->index(row, headerCalc)).toString().replace(",", "").toDouble();
		author = calc * 0.7;

		// exist
		if (m_SeriesList.contains(title)) {
			// find book
			amountList = m_SeriesList.value(title);
			// update amount
			total += amountList.value(bookTotal);
			calc += amountList.value(bookCalc);
			author += amountList.value(bookAuthor);
		}
		//for debug
		//qDebug() << "[MakeSeriesMrblue]-----------------------------";
		//qDebug() << "Title : " << title;
		//qDebug() << QString("Total Amount : %L1").arg(total, 0, 'f', 0);
		//qDebug() << QString("Calculate Amount : %L1").arg(calc, 0, 'f', 0);
		//qDebug() << QString("Author Amount : %L1").arg(author, 0, 'f', 0);

		amountList.insert(bookTotal, total);
		amountList.insert(bookCalc, calc);
		amountList.insert(bookAuthor, author);

		// update book
		m_SeriesList.insert(title, amountList);	// replace item
	}
}

void CSVTotalSeries::MakeSeriesBarobook(QStandardItemModel* item)
{
	int headerTitle = 0;
	int headerTotal = -1;
	int headerCalc = -1;
	int headerAuthor = -1;

	int bookTotal = 0;
	int bookCalc = 0;
	int bookAuthor = 0;

	headerTitle = CSVBarobook::HEADER_BAROBOOK_TITLE;
	headerCalc = CSVBarobook::HEADER_BAROBOOK_TOTAL_AMOUNT;

	bookTotal = COLUMN_BAROBOOK_TOTAL;
	bookCalc = COLUMN_BAROBOOK_CALC;
	bookAuthor = COLUMN_BAROBOOK_AUTHOR;

	QString title;

	double total = 0;
	double calc = 0;
	double author = 0;

	QMap<int, double> amountList;
	
	for (int row = CSV_TOTAL_ROW; row < item->rowCount(); row++) {

		amountList.clear();
		
		total = 0;
		calc = 0;
		author = 0;

		title = GetSeriesName(item->data(item->index(row, headerTitle)).toString());
		if (title.isEmpty()) { continue; }

		calc = item->data(item->index(row, headerCalc)).toString().replace(",", "").toDouble();
		// case barobook
		total = calc / 0.7;
		author = calc * 0.7;

		// exist
		if (m_SeriesList.contains(title)) {
			// find book
			amountList = m_SeriesList.value(title);
			// update amount
			total += amountList.value(bookTotal);
			calc += amountList.value(bookCalc);
			author += amountList.value(bookAuthor);
		}
		//for debug
		//qDebug() << "[MakeSeriesBarobook]-----------------------------";
		//qDebug() << "Title : " << title;
		//qDebug() << QString("Total Amount : %L1").arg(total, 0, 'f', 0);
		//qDebug() << QString("Calculate Amount : %L1").arg(calc, 0, 'f', 0);
		//qDebug() << QString("Author Amount : %L1").arg(author, 0, 'f', 0);

		amountList.insert(bookTotal, total);
		amountList.insert(bookCalc, calc);
		amountList.insert(bookAuthor, author);

		// update book
		m_SeriesList.insert(title, amountList);	// replace item
	}
}

void CSVTotalSeries::MakeSeriesBookcube(QStandardItemModel* item)
{
	int headerTitle = 0;
	int headerTotal = -1;
	int headerCalc = -1;
	int headerAuthor = -1;

	int bookTotal = 0;
	int bookCalc = 0;
	int bookAuthor = 0;

	headerTitle = CSVBookcube::HEADER_BOOKCUBE_TITLE;
	headerTotal = CSVBookcube::HEADER_BOOKCUBE_CALCULATOR_RELATIVE;			// todo - check HEADER_BOOKCUBE_CALCULATOR ?
	headerCalc = CSVBookcube::HEADER_BOOKCUBE_CALCULATOR;

	bookTotal = COLUMN_BOOKCUBE_TOTAL;
	bookCalc = COLUMN_BOOKCUBE_CALC;
	bookAuthor = COLUMN_BOOKCUBE_AUTHOR;

	QString title;

	double total = 0;
	double calc = 0;
	double author = 0;

	QMap<int, double> amountList;
	
	for (int row = CSV_TOTAL_ROW; row < item->rowCount(); row++) {

		amountList.clear();
		
		total = 0;
		calc = 0;
		author = 0;

		title = GetSeriesName(item->data(item->index(row, headerTitle)).toString());
		if (title.isEmpty()) { continue; }

		total += item->data(item->index(row, headerTotal)).toString().replace(",", "").toDouble();
		calc = item->data(item->index(row, headerCalc)).toString().replace(",", "").toDouble();
		author = calc * 0.7;

		// exist
		if (m_SeriesList.contains(title)) {
			// find book
			amountList = m_SeriesList.value(title);
			// update amount
			total += amountList.value(bookTotal);
			calc += amountList.value(bookCalc);
			author += amountList.value(bookAuthor);
		}
		//for debug
		//qDebug() << "[MakeSeriesBookcube]-----------------------------";
		//qDebug() << "Title : " << title;
		//qDebug() << QString("Total Amount : %L1").arg(total, 0, 'f', 0);
		//qDebug() << QString("Calculate Amount : %L1").arg(calc, 0, 'f', 0);
		//qDebug() << QString("Author Amount : %L1").arg(author, 0, 'f', 0);

		amountList.insert(bookTotal, total);
		amountList.insert(bookCalc, calc);
		amountList.insert(bookAuthor, author);

		// update book
		m_SeriesList.insert(title, amountList);	// replace item
	}
}

void CSVTotalSeries::MakeSeriesEpyrus(QStandardItemModel* item)
{
	int headerTitle = 0;
	int headerTotal = -1;
	int headerCalc = -1;
	int headerAuthor = -1;

	int bookTotal = 0;
	int bookCalc = 0;
	int bookAuthor = 0;

	headerTitle = CSVEpyrus::HEADER_EPYRUS_TITLE;
	headerTotal = CSVEpyrus::HEADER_EPYRUS_SALE_AMOUNT;
	headerCalc = CSVEpyrus::HEADER_EPYRUS_CALCULATOR_AMOUNT;

	bookTotal = COLUMN_EPYRUS_TOTAL;
	bookCalc = COLUMN_EPYRUS_CALC;
	bookAuthor = COLUMN_EPYRUS_AUTHOR;

	QString title;

	double total = 0;
	double calc = 0;
	double author = 0;

	QMap<int, double> amountList;
	
	for (int row = CSV_TOTAL_ROW; row < item->rowCount(); row++) {

		amountList.clear();
		
		total = 0;
		calc = 0;
		author = 0;

		title = GetSeriesName(item->data(item->index(row, headerTitle)).toString());
		if (title.isEmpty()) { continue; }

		total += item->data(item->index(row, headerTotal)).toString().replace(",", "").toDouble();
		calc = item->data(item->index(row, headerCalc)).toString().replace(",", "").toDouble();
		author = calc * 0.7;

		// exist
		if (m_SeriesList.contains(title)) {
			// find book
			amountList = m_SeriesList.value(title);
			// update amount
			total += amountList.value(bookTotal);
			calc += amountList.value(bookCalc);
			author += amountList.value(bookAuthor);
		}
		//for debug
		//qDebug() << "[MakeSeriesEpyrus]-----------------------------";
		//qDebug() << "Title : " << title;
		//qDebug() << QString("Total Amount : %L1").arg(total, 0, 'f', 0);
		//qDebug() << QString("Calculate Amount : %L1").arg(calc, 0, 'f', 0);
		//qDebug() << QString("Author Amount : %L1").arg(author, 0, 'f', 0);

		amountList.insert(bookTotal, total);
		amountList.insert(bookCalc, calc);
		amountList.insert(bookAuthor, author);

		// update book
		m_SeriesList.insert(title, amountList);	// replace item
	}
}

void CSVTotalSeries::MakeSeriesOebook(QStandardItemModel* item)
{
	int headerTitle = 0;
	int headerTotal = -1;
	int headerCalc = -1;
	int headerAuthor = -1;

	int bookTotal = 0;
	int bookCalc = 0;
	int bookAuthor = 0;

	headerTitle = CSVOebook::HEADER_OEBOOK_TITLE;
	headerTotal = CSVOebook::HEADER_OEBOOK_TOTAL_AMOUNT;
	headerCalc = CSVOebook::HEADER_OEBOOK_CALCURATE_AMOUNT;

	bookTotal = COLUMN_OEBOOK_TOTAL;
	bookCalc = COLUMN_OEBOOK_CALC;
	bookAuthor = COLUMN_OEBOOK_AUTHOR;

	QString title;

	double total = 0;
	double calc = 0;
	double author = 0;

	QMap<int, double> amountList;
	
	for (int row = CSV_TOTAL_ROW; row < item->rowCount(); row++) {

		amountList.clear();
		
		total = 0;
		calc = 0;
		author = 0;

		title = GetSeriesName(item->data(item->index(row, headerTitle)).toString());
		if (title.isEmpty()) { continue; }

		total += item->data(item->index(row, headerTotal)).toString().replace(",", "").toDouble();
		calc = item->data(item->index(row, headerCalc)).toString().replace(",", "").toDouble();
		author = calc * 0.7;

		// exist
		if (m_SeriesList.contains(title)) {
			// find book
			amountList = m_SeriesList.value(title);
			// update amount
			total += amountList.value(bookTotal);
			calc += amountList.value(bookCalc);
			author += amountList.value(bookAuthor);
		}
		//for debug
		//qDebug() << "[MakeSeriesOebook]-----------------------------";
		//qDebug() << "Title : " << title;
		//qDebug() << QString("Total Amount : %L1").arg(total, 0, 'f', 0);
		//qDebug() << QString("Calculate Amount : %L1").arg(calc, 0, 'f', 0);
		//qDebug() << QString("Author Amount : %L1").arg(author, 0, 'f', 0);

		amountList.insert(bookTotal, total);
		amountList.insert(bookCalc, calc);
		amountList.insert(bookAuthor, author);

		// update book
		m_SeriesList.insert(title, amountList);	// replace item
	}
}

void CSVTotalSeries::MakeSeriesOnestore(QStandardItemModel* item)
{
	int headerTitle = 0;
	int headerTotal = -1;
	int headerCalc = -1;
	int headerAuthor = -1;

	int bookTotal = 0;
	int bookCalc = 0;
	int bookAuthor = 0;

	headerTitle = CSVOnestore::HEADER_ONESTORE_TITLE;
	headerTotal = CSVOnestore::HEADER_ONESTORE_CUSTOM_CHARGE;

	bookTotal = COLUMN_ONESTORE_TOTAL;
	bookCalc = COLUMN_ONESTORE_CALC;
	bookAuthor = COLUMN_ONESTORE_AUTHOR;

	QString title;

	double total = 0;
	double calc = 0;
	double author = 0;

	QMap<int, double> amountList;
	
	for (int row = CSV_TOTAL_ROW; row < item->rowCount(); row++) {

		amountList.clear();
		
		total = 0;
		calc = 0;
		author = 0;

		title = GetSeriesName(item->data(item->index(row, headerTitle)).toString());
		if (title.isEmpty()) { continue; }

		total += item->data(item->index(row, headerTotal)).toString().replace(",", "").toDouble();
		// case naver, munpia, onestore
		calc = total * 0.7;
		author = calc * 0.7;

		// exist
		if (m_SeriesList.contains(title)) {
			// find book
			amountList = m_SeriesList.value(title);
			// update amount
			total += amountList.value(bookTotal);
			calc += amountList.value(bookCalc);
			author += amountList.value(bookAuthor);
		}
		//for debug
		//qDebug() << "[MakeSeriesOnestore]-----------------------------";
		//qDebug() << "Title : " << title;
		//qDebug() << QString("Total Amount : %L1").arg(total, 0, 'f', 0);
		//qDebug() << QString("Calculate Amount : %L1").arg(calc, 0, 'f', 0);
		//qDebug() << QString("Author Amount : %L1").arg(author, 0, 'f', 0);

		amountList.insert(bookTotal, total);
		amountList.insert(bookCalc, calc);
		amountList.insert(bookAuthor, author);

		// update book
		m_SeriesList.insert(title, amountList);	// replace item
	}
}

void CSVTotalSeries::MakeSeriesKakao(QStandardItemModel* item)
{
	int headerTitle = 0;
	int headerTotal = -1;
	int headerCalc = -1;
	int headerAuthor = -1;

	int bookTotal = 0;
	int bookCalc = 0;
	int bookAuthor = 0;

	headerTitle = CSVKakao::HEADER_KAKAO_TITLE;
	headerTotal = CSVKakao::HEADER_KAKAO_SALE_TOTAL;
	headerCalc = CSVKakao::HEADER_KAKAO_CALCULATE;

	bookTotal = COLUMN_KAKAO_TOTAL;
	bookCalc = COLUMN_KAKAO_CALC;
	bookAuthor = COLUMN_KAKAO_AUTHOR;

	QString title;

	double total = 0;
	double calc = 0;
	double author = 0;

	QMap<int, double> amountList;
	
	for (int row = CSV_TOTAL_ROW; row < item->rowCount(); row++) {

		amountList.clear();
		
		total = 0;
		calc = 0;
		author = 0;

		title = GetSeriesName(item->data(item->index(row, headerTitle)).toString());
		if (title.isEmpty()) { continue; }

		total += item->data(item->index(row, headerTotal)).toString().replace(",", "").toDouble();
		calc = item->data(item->index(row, headerCalc)).toString().replace(",", "").toDouble();
		author = calc * 0.7;

		// exist
		if (m_SeriesList.contains(title)) {
			// find book
			amountList = m_SeriesList.value(title);
			// update amount
			total += amountList.value(bookTotal);
			calc += amountList.value(bookCalc);
			author += amountList.value(bookAuthor);
		}
		//for debug
		//qDebug() << "[MakeSeriesKakao]-----------------------------";
		//qDebug() << "Title : " << title;
		//qDebug() << QString("Total Amount : %L1").arg(total, 0, 'f', 0);
		//qDebug() << QString("Calculate Amount : %L1").arg(calc, 0, 'f', 0);
		//qDebug() << QString("Author Amount : %L1").arg(author, 0, 'f', 0);

		amountList.insert(bookTotal, total);
		amountList.insert(bookCalc, calc);
		amountList.insert(bookAuthor, author);

		// update book
		m_SeriesList.insert(title, amountList);	// replace item
	}
}

void CSVTotalSeries::MakeSeriesComico(QStandardItemModel* item)
{
	int headerTitle = 0;
	QList<int> headerTotal;	headerTotal.clear();
	int headerCalc = -1;
	int headerAuthor = -1;

	int bookTotal = 0;
	int bookCalc = 0;
	int bookAuthor = 0;

	headerTitle = CSVComico::HEADER_COMICO_TITLE;
	headerTotal.insert(0, CSVComico::HEADER_COMICO_IOS_TOTAL_AMOUNT);
	headerTotal.insert(1, CSVComico::HEADER_COMICO_ANDROID_TOTAL_AMOUNT);
	headerCalc = CSVComico::HEADER_COMICO_CALCULATOR_AMOUNT;

	bookTotal = COLUMN_COMICO_TOTAL;
	bookCalc = COLUMN_COMICO_CALC;
	bookAuthor = COLUMN_COMICO_AUTHOR;

	QString title;

	double total = 0;
	double calc = 0;
	double author = 0;

	QMap<int, double> amountList;
	
	for (int row = CSV_TOTAL_ROW; row < item->rowCount(); row++) {

		amountList.clear();
		
		total = 0;
		calc = 0;
		author = 0;

		title = GetSeriesName(item->data(item->index(row, headerTitle)).toString());
		if (title.isEmpty()) { continue; }

		// case ridi, comico, kepub
		for (int i = 0; i < headerTotal.count(); i++) {
			total += item->data(item->index(row, headerTotal.at(i))).toString().replace(",", "").toDouble();
		}

		calc = item->data(item->index(row, headerCalc)).toString().replace(",", "").toDouble();
		author = calc * 0.7;

		// exist
		if (m_SeriesList.contains(title)) {
			// find book
			amountList = m_SeriesList.value(title);
			// update amount
			total += amountList.value(bookTotal);
			calc += amountList.value(bookCalc);
			author += amountList.value(bookAuthor);
		}
		//for debug
		//qDebug() << "[MakeSeriesComico]-----------------------------";
		//qDebug() << "Title : " << title;
		//qDebug() << QString("Total Amount : %L1").arg(total, 0, 'f', 0);
		//qDebug() << QString("Calculate Amount : %L1").arg(calc, 0, 'f', 0);
		//qDebug() << QString("Author Amount : %L1").arg(author, 0, 'f', 0);

		amountList.insert(bookTotal, total);
		amountList.insert(bookCalc, calc);
		amountList.insert(bookAuthor, author);

		// update book
		m_SeriesList.insert(title, amountList);	// replace item
	}
}

void CSVTotalSeries::MakeSeriesTocsoda(QStandardItemModel* item)
{
	int headerTitle = 0;
	int headerTotal = -1;
	int headerCalc = -1;
	int headerAuthor = -1;

	int bookTotal = 0;
	int bookCalc = 0;
	int bookAuthor = 0;

	headerTitle = CSVTocsoda::HEADER_TOCSODA_TITLE;
	headerTotal = CSVTocsoda::HEADER_TOCSODA_TOTAL_AMOUNT;
	headerCalc = CSVTocsoda::HEADER_TOCSODA_CALCULATOR_AMOUNT;

	bookTotal = COLUMN_TOCSODA_TOTAL;
	bookCalc = COLUMN_TOCSODA_CALC;
	bookAuthor = COLUMN_TOCSODA_AUTHOR;

	QString title;

	double total = 0;
	double calc = 0;
	double author = 0;

	QMap<int, double> amountList;
	
	for (int row = CSV_TOTAL_ROW; row < item->rowCount(); row++) {

		amountList.clear();
		
		total = 0;
		calc = 0;
		author = 0;

		title = GetSeriesName(item->data(item->index(row, headerTitle)).toString());
		if (title.isEmpty()) { continue; }

		total += item->data(item->index(row, headerTotal)).toString().replace(",", "").toDouble();
		calc = item->data(item->index(row, headerCalc)).toString().replace(",", "").toDouble();
		author = calc * 0.7;

		// exist
		if (m_SeriesList.contains(title)) {
			// find book
			amountList = m_SeriesList.value(title);
			// update amount
			total += amountList.value(bookTotal);
			calc += amountList.value(bookCalc);
			author += amountList.value(bookAuthor);
		}
		//for debug
		//qDebug() << "[MakeSeriesTocsoda]-----------------------------";
		//qDebug() << "Title : " << title;
		//qDebug() << QString("Total Amount : %L1").arg(total, 0, 'f', 0);
		//qDebug() << QString("Calculate Amount : %L1").arg(calc, 0, 'f', 0);
		//qDebug() << QString("Author Amount : %L1").arg(author, 0, 'f', 0);

		amountList.insert(bookTotal, total);
		amountList.insert(bookCalc, calc);
		amountList.insert(bookAuthor, author);

		// update book
		m_SeriesList.insert(title, amountList);	// replace item
	}
}

void CSVTotalSeries::MakeSeriesJustoon(QStandardItemModel* item)
{
	int headerTitle = 0;
	int headerTotal = -1;
	int headerCalc = -1;
	int headerAuthor = -1;

	int bookTotal = 0;
	int bookCalc = 0;
	int bookAuthor = 0;

	headerTitle = CSVJustoon::HEADER_JUSTOON_TITLE;
	headerTotal = CSVJustoon::HEADER_JUSTOON_TOTAL_AMOUNT;
	headerCalc = CSVJustoon::HEADER_JUSTOON_TOTAL_RS_AMOUNT;

	bookTotal = COLUMN_JUSTOON_TOTAL;
	bookCalc = COLUMN_JUSTOON_CALC;
	bookAuthor = COLUMN_JUSTOON_AUTHOR;

	QString title;

	double total = 0;
	double calc = 0;
	double author = 0;

	QMap<int, double> amountList;

	for (int row = CSV_TOTAL_ROW; row < item->rowCount(); row++) {

		amountList.clear();

		total = 0;
		calc = 0;
		author = 0;

		title = GetSeriesName(item->data(item->index(row, headerTitle)).toString());
		if (title.isEmpty()) { continue; }

		total += item->data(item->index(row, headerTotal)).toString().replace(",", "").toDouble();
		total += item->data(item->index(row + 1, headerTotal)).toString().replace(",", "").toDouble();	// inapp for google
		total += item->data(item->index(row + 2, headerTotal)).toString().replace(",", "").toDouble();	// inapp for ios
		total += item->data(item->index(row + 3, headerTotal)).toString().replace(",", "").toDouble();	// inapp for onestore
		calc = item->data(item->index(row, headerCalc)).toString().replace(",", "").toDouble();
		author = calc * 0.7;

		// exist
		if (m_SeriesList.contains(title)) {
			// find book
			amountList = m_SeriesList.value(title);
			// update amount
			total += amountList.value(bookTotal);
			calc += amountList.value(bookCalc);
			author += amountList.value(bookAuthor);
		}
		//for debug
		//qDebug() << "[MakeSeriesJustoon]-----------------------------";
		//qDebug() << "Title : " << title;
		//qDebug() << QString("Total Amount : %L1").arg(total, 0, 'f', 0);
		//qDebug() << QString("Calculate Amount : %L1").arg(calc, 0, 'f', 0);
		//qDebug() << QString("Author Amount : %L1").arg(author, 0, 'f', 0);

		amountList.insert(bookTotal, total);
		amountList.insert(bookCalc, calc);
		amountList.insert(bookAuthor, author);

		// update book
		m_SeriesList.insert(title, amountList);	// replace item
	}
}

void CSVTotalSeries::MakeSeriesGoogle(QStandardItemModel* item)
{
	int headerTitle = 0;
	int headerTotal = -1;
	int headerCalc = -1;
	int headerAuthor = -1;

	int bookTotal = 0;
	int bookCalc = 0;
	int bookAuthor = 0;

	headerTitle = CSVGoogle::HEADER_GOOGLE_TITLE;
	headerTotal = CSVGoogle::HEADER_GOOGLE_TOTAL_AMOUNT;

	bookTotal = COLUMN_GOOGLE_TOTAL;
	bookCalc = COLUMN_GOOGLE_CALC;
	bookAuthor = COLUMN_GOOGLE_AUTHOR;

	QString title;

	double total = 0;
	double calc = 0;
	double author = 0;

	QMap<int, double> amountList;

	for (int row = CSV_TOTAL_ROW; row < item->rowCount(); row++) {

		amountList.clear();

		total = 0;
		calc = 0;
		author = 0;

		title = GetSeriesName(item->data(item->index(row, headerTitle)).toString());
		if (title.isEmpty()) { continue; }

		total += item->data(item->index(row, headerTotal)).toString().replace(",", "").toDouble();
		// case naver, munpia, onestore
		calc = total * 0.7;
		author = calc * 0.7;

		// exist
		if (m_SeriesList.contains(title)) {
			// find book
			amountList = m_SeriesList.value(title);
			// update amount
			total += amountList.value(bookTotal);
			calc += amountList.value(bookCalc);
			author += amountList.value(bookAuthor);
		}
		//for debug
		//qDebug() << "[MakeSeriesGoogle]-----------------------------";
		//qDebug() << "Title : " << title;
		//qDebug() << QString("Total Amount : %L1").arg(total, 0, 'f', 0);
		//qDebug() << QString("Calculate Amount : %L1").arg(calc, 0, 'f', 0);
		//qDebug() << QString("Author Amount : %L1").arg(author, 0, 'f', 0);

		amountList.insert(bookTotal, total);
		amountList.insert(bookCalc, calc);
		amountList.insert(bookAuthor, author);

		// update book
		m_SeriesList.insert(title, amountList);	// replace item
	}
}

void CSVTotalSeries::MakeSeriesKepub(QStandardItemModel* item)
{
	int headerTitle = 0;
	QList<int> headerTotal;	headerTotal.clear();
	int headerCalc = -1;
	int headerAuthor = -1;

	int bookTotal = 0;
	int bookCalc = 0;
	int bookAuthor = 0;

	headerTitle = CSVKepub::HEADER_KEPUB_TITLE;
	headerTotal.insert(0, CSVKepub::HEADER_KEPUB_STORE_PRICE);
	headerTotal.insert(1, CSVKepub::HEADER_KEPUB_STORE_REFUND_PRICE);
	headerCalc = CSVKepub::HEADER_KEPUB_CALCULATOR_AMOUNT;

	bookTotal = COLUMN_KEPUB_TOTAL;
	bookCalc = COLUMN_KEPUB_CALC;
	bookAuthor = COLUMN_KEPUB_AUTHOR;

	QString title;

	double total = 0;
	double calc = 0;
	double author = 0;

	QMap<int, double> amountList;

	for (int row = CSV_TOTAL_ROW; row < item->rowCount(); row++) {

		amountList.clear();

		total = 0;
		calc = 0;
		author = 0;

		title = GetSeriesName(item->data(item->index(row, headerTitle)).toString());
		if (title.isEmpty()) { continue; }

		// case ridi, comico, kepub
		total += item->data(item->index(row, headerTotal.at(0))).toString().replace(",", "").toDouble();
		total -= item->data(item->index(row, headerTotal.at(1))).toString().replace(",", "").toDouble();

		calc = item->data(item->index(row, headerCalc)).toString().replace(",", "").toDouble();
		author = calc * 0.7;

		// exist
		if (m_SeriesList.contains(title)) {
			// find book
			amountList = m_SeriesList.value(title);
			// update amount
			total += amountList.value(bookTotal);
			calc += amountList.value(bookCalc);
			author += amountList.value(bookAuthor);
		}
		//for debug
		//qDebug() << "[MakeSeriesKepub]-----------------------------";
		//qDebug() << "Title : " << title;
		//qDebug() << QString("Total Amount : %L1").arg(total, 0, 'f', 0);
		//qDebug() << QString("Calculate Amount : %L1").arg(calc, 0, 'f', 0);
		//qDebug() << QString("Author Amount : %L1").arg(author, 0, 'f', 0);

		amountList.insert(bookTotal, total);
		amountList.insert(bookCalc, calc);
		amountList.insert(bookAuthor, author);

		// update book
		m_SeriesList.insert(title, amountList);	// replace item
	}
}

void CSVTotalSeries::SetItem(CalcCPDlg* cpData)
{
	m_SeriesList.clear();

	// make book data
	if (cpData->GetKyobo()) {
		MakeSeriesKyobo(cpData->GetKyobo()->GetItem());
	}
	if (cpData->GetNaver()) {
		MakeSeriesNaver(cpData->GetNaver()->GetItem());
	}
	if (cpData->GetRidi()) {
		MakeSeriesRidi(cpData->GetRidi()->GetItem());
	}
	if (cpData->GetMunpia()) {
		MakeSeriesMunpia(cpData->GetMunpia()->GetItem());
	}
	if (cpData->GetMrblue()) {
		MakeSeriesMrblue(cpData->GetMrblue()->GetItem());
	}
	if (cpData->GetBarobook()) {
		MakeSeriesBarobook(cpData->GetBarobook()->GetItem());
	}
	if (cpData->GetBookcube()) {
		MakeSeriesBookcube(cpData->GetBookcube()->GetItem());
	}
	if (cpData->GetEpyrus()) {
		MakeSeriesEpyrus(cpData->GetEpyrus()->GetItem());
	}
	if (cpData->GetOebook()) {
		MakeSeriesOebook(cpData->GetOebook()->GetItem());
	}
	if (cpData->GetOnestore()) {
		MakeSeriesOnestore(cpData->GetOnestore()->GetItem());
	}
	if (cpData->GetKakao()) {
		MakeSeriesKakao(cpData->GetKakao()->GetItem());
	}
	if (cpData->GetComico()) {
		MakeSeriesComico(cpData->GetComico()->GetItem());
	}
	if (cpData->GetTocsoda()) {
		MakeSeriesTocsoda(cpData->GetTocsoda()->GetItem());
	}
	if (cpData->GetJustoon()) {
		MakeSeriesJustoon(cpData->GetJustoon()->GetItem());
	}
	if (cpData->GetGoogle()) {
		MakeSeriesGoogle(cpData->GetGoogle()->GetItem());
	}
	if (cpData->GetKepub()) {
		MakeSeriesKepub(cpData->GetKepub()->GetItem());
	}

	// init book list
	InitSeriesData();

	// set book list
	SetSeriesTable();
}

QTableView* CSVTotalSeries::GetView()
{
	if (!m_CSVView) { m_CSVView = new QTableView(); }
	m_CSVView->setModel(GetItem());

	return m_CSVView;
}

void CSVTotalSeries::WriteFile(QString filepath)
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

QString CSVTotalSeries::GetSeriesName(QString titleName)
{
	QString retName;
	int index = 0;
	//qDebug() << "GetSeriesName before : " << titleName;
	if (titleName.endsWith(QString::fromLocal8Bit("권"))) {
		index = titleName.lastIndexOf(" ");
		//qDebug() << "fine kwon : " << index;
		retName = titleName.left(index);
	}
	else if (titleName.endsWith(QString::fromLocal8Bit("화"))) {
		index = titleName.lastIndexOf(" ");
		//qDebug() << "fine hwa : " << index;
		retName = titleName.left(index);
	}
	else if (titleName.endsWith("1")
		|| titleName.endsWith("2")
		|| titleName.endsWith("3")
		|| titleName.endsWith("4")
		|| titleName.endsWith("5")
		|| titleName.endsWith("6")
		|| titleName.endsWith("7")
		|| titleName.endsWith("8")
		|| titleName.endsWith("9")) {
		index = titleName.lastIndexOf(" ");
		//qDebug() << "fine number : " << index;
		retName = titleName.left(index);
	}
	else {
		retName = titleName;
	}
	//qDebug() << "GetSeriesName after : " << retName;
	return retName;
}
