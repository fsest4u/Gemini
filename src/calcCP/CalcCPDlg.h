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

	void SetCPFileList(QHash<int, QString>&);



private slots:

	void connectSignalsSlots();

	void Prev();
	void CalcCP();
	void Next();


private:


	void InitUI();
	void AddTab(QTableView* table, const QString cpName, double total, double calculator, double author);
	void AddTab4List(QTableView* table, const QString cpName, QList<double> total, QList<double> calculator, QList<double> author);


	void CalcKyobo();
	void CalcNaver();
	void CalcRidi();
	void CalcMunpia();
	void CalcMrblue();
	void CalcBarobook();
	void CalcBookcube();
	void CalcEpyrus();
	void CalcOebook();
	void CalcOnestore();
	void CalcKakao();
	void CalcComico();
	void CalcTocsoda();
	void CalcKepub();

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

	QTableView*			m_KyoboView;
	QTableView*			m_NaverView;
	QTableView*			m_RidiView;
	QTableView*			m_MunpiaView;
	QTableView*			m_MrblueView;
	QTableView*			m_BarobookView;
	QTableView*			m_BookcubeView;
	QTableView*			m_EpyrusView;
	QTableView*			m_OebookView;
	QTableView*			m_OnestoreView;
	QTableView*			m_KakaoView;
	QTableView*			m_ComicoView;
	QTableView*			m_TocsodaView;
	QTableView*			m_KepubView;

	QProgressDialog*	m_Progress;


	Ui::CalcCPDlg ui;

};

#endif // CALC_CP_DLG_H
