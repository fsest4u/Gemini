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
#include <QtWidgets/QProgressDialog>

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
#include "CSVKepub.h"

#include "ui_CalcCPDlg.h"

class CSVKyobo;		
class CSVNaver;		
class CSVRidi;		
class CSVMunpia;		
class CSVMrblue;		
class CSVBarobook;	
class CSVBookcube;	
class CSVEpyrus;		
class CSVOebook;		
class CSVOnestore;	
class CSVKakao;		
class CSVComico;		
class CSVTocsoda;		
class CSVKepub;		

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
		CP_KEPUB,
		CP_MAX
	};

	/**
	* Constructor.
	*/
	CalcCPDlg(QDialog *parent = 0);
	~CalcCPDlg();

	bool SetCP(QHash<int, QString>&);

	CSVKyobo*			GetKyobo() { return m_Kyobo; }
	CSVNaver*			GetNaver() { return m_Naver; }
	CSVRidi*			GetRidi() { return m_Ridi; }
	CSVMunpia*			GetMunpia() { return m_Munpia; }
	CSVMrblue*			GetMrblue() { return m_Mrblue; }
	CSVBarobook*		GetBarobook() { return m_Barabook; }
	CSVBookcube*		GetBookcube() { return m_Bookcube; }
	CSVEpyrus*			GetEpyrus() { return m_Epyrus; }
	CSVOebook*			GetOebook() { return m_Oebook; }
	CSVOnestore*		GetOnestore() { return m_Onestore; }
	CSVKakao*			GetKakao() { return m_Kakao; }
	CSVComico*			GetComico() { return m_Comico; }
	CSVTocsoda*			GetTocsoda() { return m_Tocsoda; }
	CSVKepub*			GetKepub() { return m_Kepub; }

private slots:

	void connectSignalsSlots();

	void Prev();
	void ReCalcCP();
	void Next();


private:


	void InitUI();
	void AddTab(QTableView* table, const QString cpName, double total, double calculator, double author);
	void AddTab4List(QTableView* table, const QString cpName, QList<double> total, QList<double> calculator, QList<double> author);


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
	CSVBarobook*		m_Barabook;
	CSVBookcube*		m_Bookcube;
	CSVEpyrus*			m_Epyrus;
	CSVOebook*			m_Oebook;
	CSVOnestore*		m_Onestore;
	CSVKakao*			m_Kakao;
	CSVComico*			m_Comico;
	CSVTocsoda*			m_Tocsoda;
	CSVKepub*			m_Kepub;

	QProgressDialog*	m_Progress;


	Ui::CalcCPDlg ui;

};

#endif // CALC_CP_DLG_H
