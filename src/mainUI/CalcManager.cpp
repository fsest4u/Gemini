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
#include <QtWidgets/QDialogButtonBox>

#include "calcTotal/CalcTotalDlg.h"

#include "CalcManager.h"


CalcManager::CalcManager(QWidget *parent) :
	QWidget(parent)
	, m_CalcCP(NULL)
	, m_CalcTotal(NULL)
{
}

CalcManager::~CalcManager()
{
	if (m_CalcCP) {
		delete m_CalcCP;
		m_CalcCP = 0;
	}

	if (m_CalcTotal) {
		delete m_CalcTotal;
		m_CalcTotal = 0;
	}

}

bool CalcManager::ExecuteCalc(QHash<int, QString>& cpFileList)
{
	// for debug
	foreach(const int key, cpFileList.keys()) {
		qDebug() << "[SetCPList] key : " << key << ", value : " << cpFileList.value(key);
	}

	int status = STEP_CALC_MAIN_NEXT;
	while (STEP_CALC_CANCEL > status 
		&& STEP_CALC_MAIN < status)
	{
		switch (status)
		{
		case STEP_CALC_CP_PREV:
			if (m_CalcCP) {
				delete m_CalcCP;
				m_CalcCP = 0;
			}
			status = STEP_CALC_CANCEL;
			break;
		case STEP_CALC_MAIN_NEXT:
			//qDebug() << "go to calculate cp dialog";
			status = ExecuteCP(cpFileList, true);
			break;
		case STEP_CALC_CP:
			//qDebug() << "go to calculate cp dialog";
			status = ExecuteCP(cpFileList, true);
			break;
		case STEP_CALC_CP_NEXT:
			//qDebug() << "go to calculate total dialog";
			status = ExecuteTotal(true);
			break;
		case STEP_CALC_TOTAL:
			//qDebug() << "go to calculate total dialog";
			status = ExecuteTotal(true);
			break;
		case STEP_CALC_TOTAL_PREV:
			//qDebug() << "go to calculate cp dialog";
			if (m_CalcTotal) {
				delete m_CalcTotal;
				m_CalcTotal = 0;
			}
			status = ExecuteCP(cpFileList, false);
			break;
			break;
		case STEP_CALC_TOTAL_NEXT:
			//qDebug() << "calculate total data";
			if (m_CalcCP) {
				delete m_CalcCP;
				m_CalcCP = 0;
			}
			if (m_CalcTotal) {
				delete m_CalcTotal;
				m_CalcTotal = 0;
			}
			status = STEP_CALC_MAX;
			break;
		}
	}

	if (STEP_CALC_CANCEL == status) { return false; }
	else { return true; }


}

int CalcManager::ExecuteCP(QHash<int, QString>& cpFileList, bool bRefresh)
{
	if (!m_CalcCP) { 
		m_CalcCP = new CalcCPDlg();
	}
	if (bRefresh) {
		m_CalcCP->SetCP(cpFileList);
	}
	int ret = m_CalcCP->exec();
	if (QDialogButtonBox::YesRole == ret)
		return STEP_CALC_CP_PREV;
	else if (QDialogButtonBox::HelpRole == ret)
		return STEP_CALC_CP;
	else if (QDialogButtonBox::NoRole == ret)
		return STEP_CALC_CP_NEXT;
	else
		return STEP_CALC_CANCEL;

}

int CalcManager::ExecuteTotal(bool bRefresh)
{
	if (!m_CalcTotal) {
		m_CalcTotal = new CalcTotalDlg();
	}
	if (bRefresh) {
		m_CalcTotal->SetTotal(m_CalcCP);
	}
	int ret = m_CalcTotal->exec();
	if (QDialogButtonBox::YesRole == ret)
		return STEP_CALC_TOTAL_PREV;
	else if (QDialogButtonBox::HelpRole == ret)
		return STEP_CALC_TOTAL;
	else if (QDialogButtonBox::NoRole == ret)
		return STEP_CALC_TOTAL_NEXT;
	else
		return STEP_CALC_CANCEL;

}

