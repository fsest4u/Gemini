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
#ifndef CALC_CP_DLG_H
#define CALC_CP_DLG_H

#include <QtWidgets/QDialog>

#include "CSVKyobo.h"
#include "CSVNaver.h"
#include "CSVRidi.h"
#include "CSVMunpia.h"
#include "CSVMrblue.h"
#include "CSVBarobook.h"
#include "CSVBookcube.h"
#include "CSVEpyrus.h"
#include "CSVOebook.h"
#include "CSVOnestore.h"
#include "CSVKakao.h"
#include "CSVComico.h"
#include "CSVTocsoda.h"
#include "CSVJustoon.h"
#include "CSVGoogle.h"
#include "CSVKepub.h"

#include "ui_CalcCPDlg.h"

class CalcCPDlg : public QDialog
{
	Q_OBJECT

public:

	enum CP_TYPE {
		CP_KYOBO = 0,
		CP_NAVER,
		CP_RIDI,
		CP_MUNPIA,
		CP_MRBLUE,
		CP_BAROBOOK,
		CP_BOOKCUBE,
		CP_EPYRUS,
		CP_OEBOOK,
		CP_ONESTORE,
		CP_KAKAO,
		CP_COMICO,
		CP_TOCSODA,
		CP_JUSTOON,
		CP_GOOGLE,
		CP_KEPUB,
		CP_MAX
	};

	/**
	* Constructor.
	*/
	CalcCPDlg(QDialog *parent = 0);
	~CalcCPDlg();

	bool SetCP(QHash<int, QString>&);
	bool ExtractCSV(QString lastFolderOpen);


	CSVKyobo*			GetKyobo() { return m_Kyobo; }
	CSVNaver*			GetNaver() { return m_Naver; }
	CSVRidi*			GetRidi() { return m_Ridi; }
	CSVMunpia*			GetMunpia() { return m_Munpia; }
	CSVMrblue*			GetMrblue() { return m_Mrblue; }
	CSVBarobook*		GetBarobook() { return m_Barobook; }
	CSVBookcube*		GetBookcube() { return m_Bookcube; }
	CSVEpyrus*			GetEpyrus() { return m_Epyrus; }
	CSVOebook*			GetOebook() { return m_Oebook; }
	CSVOnestore*		GetOnestore() { return m_Onestore; }
	CSVKakao*			GetKakao() { return m_Kakao; }
	CSVComico*			GetComico() { return m_Comico; }
	CSVTocsoda*			GetTocsoda() { return m_Tocsoda; }
	CSVJustoon*			GetJustoon() { return m_Justoon; }
	CSVGoogle*			GetGoogle() { return m_Google; }
	CSVKepub*			GetKepub() { return m_Kepub; }

private slots:

	void connectSignalsSlots();

	void Prev();
	void ReCalcCP();
	void Next();


private:


	void InitUI();
	void AddTabLabel(QTableView* table, const QString cpName, double total, double calculator, double author);
	void AddTab4ListLabel(QTableView* table, const QString cpName, QList<double> total, QList<double> calculator, QList<double> author);

	void AddTab(QTableView* table, const QString cpName);


	bool CalcKyobo();
	bool CalcNaver();
	bool CalcRidi();
	bool CalcMunpia();
	bool CalcMrblue();
	bool CalcBarobook();
	bool CalcBookcube();
	bool CalcEpyrus();
	bool CalcOebook();
	bool CalcOnestore();
	bool CalcKakao();
	bool CalcComico();
	bool CalcTocsoda();
	bool CalcJustoon();
	bool CalcGoogle();
	bool CalcKepub();

	void DeleteKyobo();
	void DeleteNaver();
	void DeleteRidi();
	void DeleteMunpia();
	void DeleteMrblue();
	void DeleteBarobook();
	void DeleteBookcube();
	void DeleteEpyrus();
	void DeleteOebook();
	void DeleteOnestore();
	void DeleteKakao();
	void DeleteComico();
	void DeleteTocsoda();
	void DeleteJustoon();
	void DeleteGoogle();
	void DeleteKepub();

	


	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////
	QHash<int, QString>	m_CPFileList;

	CSVKyobo*			m_Kyobo;
	CSVNaver*			m_Naver;
	CSVRidi*			m_Ridi;
	CSVMunpia*			m_Munpia;
	CSVMrblue*			m_Mrblue;
	CSVBarobook*		m_Barobook;
	CSVBookcube*		m_Bookcube;
	CSVEpyrus*			m_Epyrus;
	CSVOebook*			m_Oebook;
	CSVOnestore*		m_Onestore;
	CSVKakao*			m_Kakao;
	CSVComico*			m_Comico;
	CSVTocsoda*			m_Tocsoda;
	CSVJustoon*			m_Justoon;
	CSVGoogle*			m_Google;
	CSVKepub*			m_Kepub;

	Ui::CalcCPDlg ui;

};

#endif // CALC_CP_DLG_H
