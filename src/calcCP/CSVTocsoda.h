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
#ifndef CSV_TOCSODA_H
#define CSV_TOCSODA_H

#include <QtCore/QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QtWidgets/QTableView>

class CSVTocsoda : public QObject
{
	Q_OBJECT

public:

	enum HEADER_TOCSODA_TYPE {
		HEADER_TOCSODA_PRODUCT_BARCODE = 0,
		HEADER_TOCSODA_CP_BARCODE,
		HEADER_TOCSODA_TITLE,
		HEADER_TOCSODA_AUTHOR,
		HEADER_TOCSODA_PC_AMOUNT,
		HEADER_TOCSODA_ANDROID_AMOUNT,
		HEADER_TOCSODA_IOS_AMOUNT,
		HEADER_TOCSODA_IOS_IAP_AMOUNT,
		HEADER_TOCSODA_TOTAL_AMOUNT,
		HEADER_TOCSODA_CALCULATOR_AMOUNT,
		HEADER_TOCSODA_MAX
	};

	/**
	* Constructor.
	*/
	CSVTocsoda();
	~CSVTocsoda();

	void ReadFile(QString filepath);

	void SetItem();
	QStandardItemModel* GetItem();

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

	QStringList		m_CSVHeader;

	double			m_TotalAmount;
	double			m_CalcAmount;
	double			m_AuthorAmount;

};

#endif // CSV_TOCSODA_H
