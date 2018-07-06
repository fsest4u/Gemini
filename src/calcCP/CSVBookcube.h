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
#ifndef CSV_BOOKCUBE_H
#define CSV_BOOKCUBE_H

#include <QtCore/QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QtWidgets/QTableView>

class QProgressDialog;

class CSVBookcube : public QObject
{
	Q_OBJECT

public:

	enum HEADER_BOOKCUBE_TYPE {
		HEADER_BOOKCUBE_TITLE = 0,
		HEADER_BOOKCUBE_AUTHOR,
		HEADER_BOOKCUBE_PUBLISHER,
		HEADER_BOOKCUBE_BUSINESS_TYPE,
		HEADER_BOOKCUBE_PURCHASE_TYPE,
		HEADER_BOOKCUBE_COUNT,
		HEADER_BOOKCUBE_PRICE,
		HEADER_BOOKCUBE_SALE_PRICE,
		HEADER_BOOKCUBE_DISCOUNT,
		HEADER_BOOKCUBE_FEE,
		HEADER_BOOKCUBE_CALCULATOR_RELATIVE,
		HEADER_BOOKCUBE_CALCULATOR,
		HEADER_BOOKCUBE_BOOK_NUMBER,
		HEADER_BOOKCUBE_ISBN,
		HEADER_BOOKCUBE_E_ISBN_PDF,
		HEADER_BOOKCUBE_E_ISBN_EPUB,
		HEADER_BOOKCUBE_MAX
	};

	/**
	* Constructor.
	*/
	CSVBookcube();
	~CSVBookcube();

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

	QProgressDialog*	m_Progress;

};

#endif // CSV_BOOKCUBE_H
