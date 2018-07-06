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
#ifndef CSV_COMICO_H
#define CSV_COMICO_H

#include <QtCore/QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QtWidgets/QTableView>

class ProgressWidget;

class CSVComico : public QObject
{
	Q_OBJECT

public:

	enum HEADER_COMICO_TYPE {
		HEADER_COMICO_PLATFORM = 0,
		HEADER_COMICO_TYPE,
		HEADER_COMICO_AUTHOR,
		HEADER_COMICO_CP_NAME,
		HEADER_COMICO_PRODUCT_NUMBER,
		HEADER_COMICO_TITLE,
		HEADER_COMICO_CHAPTER,
		HEADER_COMICO_SUBTITLE,
		HEADER_COMICO_IOS_PURCHASE_COUNT,
		HEADER_COMICO_IOS_PURCHASE_COIN,
		HEADER_COMICO_IOS_RENTAL_COUNT,
		HEADER_COMICO_IOS_RENTAL_COIN,
		HEADER_COMICO_IOS_EVENT_COUNT,
		HEADER_COMICO_IOS_EVENT_COIN,
		HEADER_COMICO_IOS_TOTAL_AMOUNT,
		HEADER_COMICO_IOS_CALCULATOR_AMOUNT,
		HEADER_COMICO_ANDROID_PURCHASE_COUNT,
		HEADER_COMICO_ANDROID_PURCHASE_COIN,
		HEADER_COMICO_ANDROID_RENTAL_COUNT,
		HEADER_COMICO_ANDROID_RENTAL_COIN,
		HEADER_COMICO_ANDROID_EVENT_COUNT,
		HEADER_COMICO_ANDROID_EVENT_COIN,
		HEADER_COMICO_ANDROID_TOTAL_AMOUNT,
		HEADER_COMICO_ANDROID_CALCULATOR_AMOUNT,
		HEADER_COMICO_CALCULATOR_AMOUNT,
		HEADER_COMICO_MAX
	};

	/**
	* Constructor.
	*/
	CSVComico();
	~CSVComico();

	bool ReadFile(QString filepath);
	void WriteFile(QString filepath);

	void SetItem();
	QStandardItemModel* GetItem() { return m_CSVModel; }
	QTableView* GetView();

	double GetTotalAmount() { return m_TotalAmount; };
	double GetCalcAmount() { return m_CalcAmount; };
	double GetAuthorAmount() { return m_AuthorAmount; };

private slots:


private:



	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////
	QList<QStringList> m_CSVData;
	QStandardItemModel *m_CSVModel;
	QTableView*			m_CSVView;

	QStringList		m_CSVHeader;

	double			m_TotalAmount;
	double			m_CalcAmount;
	double			m_AuthorAmount;

	ProgressWidget* m_ProgressWidget;

};

#endif // CSV_COMICO_H
