/************************************************************************
**
**  Copyright (C) 2018  spdevapp <spdevapp@joara.com>
**
**  This file is part of Gemini.
**
**  Gemini is Joara CSV Calculator.
**
*************************************************************************/

#pragma once
#ifndef CSV_TOTAL_SERIES_H
#define CSV_TOTAL_SERIES_H

#include <QtCore/QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QtWidgets/QTableView>

class CalcCPDlg;

class CSVTotalSeries : public QObject
{
	Q_OBJECT

public:

	enum ROW_TYPE {
		ROW_AMOUNT_NAME = 0,
		ROW_AMOUNT,
		ROW_MAX
	};

	enum COLUMN_TYPE {
		COLUMN_TITLE = 0,
		COLUMN_RANK,
		COLUMN_AMOUNT_TOTAL,
		COLUMN_AMOUNT_CALC,
		COLUMN_AMOUNT_AUTHOR,
		COLUMN_KYOBO_TOTAL,
		COLUMN_KYOBO_CALC,
		COLUMN_KYOBO_AUTHOR,
		COLUMN_NAVER_TOTAL,
		COLUMN_NAVER_CALC,
		COLUMN_NAVER_AUTHOR,
		COLUMN_RIDI_TOTAL,
		COLUMN_RIDI_CALC,
		COLUMN_RIDI_AUTHOR,
		COLUMN_MUNPIA_TOTAL,
		COLUMN_MUNPIA_CALC,
		COLUMN_MUNPIA_AUTHOR,
		COLUMN_MRBLUE_TOTAL,
		COLUMN_MRBLUE_CALC,
		COLUMN_MRBLUE_AUTHOR,
		COLUMN_BAROBOOK_TOTAL,
		COLUMN_BAROBOOK_CALC,
		COLUMN_BAROBOOK_AUTHOR,
		COLUMN_BOOKCUBE_TOTAL,
		COLUMN_BOOKCUBE_CALC,
		COLUMN_BOOKCUBE_AUTHOR,
		COLUMN_EPYRUS_TOTAL,
		COLUMN_EPYRUS_CALC,
		COLUMN_EPYRUS_AUTHOR,
		COLUMN_OEBOOK_TOTAL,
		COLUMN_OEBOOK_CALC,
		COLUMN_OEBOOK_AUTHOR,
		COLUMN_ONESTORE_TOTAL,
		COLUMN_ONESTORE_CALC,
		COLUMN_ONESTORE_AUTHOR,
		COLUMN_KAKAO_TOTAL,
		COLUMN_KAKAO_CALC,
		COLUMN_KAKAO_AUTHOR,
		COLUMN_COMICO_TOTAL,
		COLUMN_COMICO_CALC,
		COLUMN_COMICO_AUTHOR,
		COLUMN_TOCSODA_TOTAL,
		COLUMN_TOCSODA_CALC,
		COLUMN_TOCSODA_AUTHOR,
		COLUMN_KEPUB_TOTAL,
		COLUMN_KEPUB_CALC,
		COLUMN_KEPUB_AUTHOR,
		COLUMN_MAX
	};

	/**
	* Constructor.
	*/
	CSVTotalSeries();
	~CSVTotalSeries();

	void InitSeriesData();

	void SetSeriesTable();
	void SetSeriesRank();
	QString GetSeriesName(QString titleName);

	void MakeSeriesKyobo(QStandardItemModel* item);
	void MakeSeriesNaver(QStandardItemModel* item);
	void MakeSeriesRidi(QStandardItemModel* item);
	void MakeSeriesMunpia(QStandardItemModel* item);
	void MakeSeriesMrblue(QStandardItemModel* item);
	void MakeSeriesBarobook(QStandardItemModel* item);
	void MakeSeriesBookcube(QStandardItemModel* item);
	void MakeSeriesEpyrus(QStandardItemModel* item);
	void MakeSeriesOebook(QStandardItemModel* item);
	void MakeSeriesOnestore(QStandardItemModel* item);
	void MakeSeriesKakao(QStandardItemModel* item);
	void MakeSeriesComico(QStandardItemModel* item);
	void MakeSeriesTocsoda(QStandardItemModel* item);
	void MakeSeriesKepub(QStandardItemModel* item);

	void SetItem(CalcCPDlg* cpData);
	QStandardItemModel* GetItem() { return m_CSVModel; }
	QTableView* GetView();

	//double GetTotalAmount() { return m_TotalAmount; };
	//double GetCalcAmount() { return m_CalcAmount; };
	//double GetAuthorAmount() { return m_AuthorAmount; };
	
	void WriteFile(QString filepath);


private slots:


private:



	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////
	//QList<QStringList>	m_CSVData;
	QStandardItemModel*	m_CSVModel;
	QTableView*			m_CSVView;

	QMap<QString, QMap<int, double>>		m_SeriesList;
	//QHash<int, double>						m_AmountList;

	//QList<double>		m_TotalAmount;
	//QList<double>		m_CalcAmount;
	//QList<double>		m_AuthorAmount;

	QMap<double, int>	m_RankAmount;

};

#endif // CSV_TOTAL_SERIES_H
