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

#include "calcCP/CalcCPDlg.h"
#include "calcTotal/CalcTotalDlg.h"

#include "CalcManager.h"

enum STEP_CALC {
	STEP_CALC_MAIN = 0
	, STEP_CALC_CP
	, STEP_CALC_CP_ING
	, STEP_CALC_TOTAL
	, STEP_CALC_TOTAL_ING
	, STEP_CALC_CANCEL
	, STEP_CALC_MAX
};

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

	int status = STEP_CALC_CP;
	while (STEP_CALC_CANCEL > status 
		&& STEP_CALC_MAIN < status)
	{
		switch (status)
		{
		case STEP_CALC_CP:
			qDebug() << "go to calculate cp dialog";
			status = ExecuteCP();
			break;
		case STEP_CALC_CP_ING:
			qDebug() << "calculate cp data";
			status = STEP_CALC_CP;
			break;
		case STEP_CALC_TOTAL:
			qDebug() << "go to calculate total dialog";
			status = ExecuteTotal();
			break;
		case STEP_CALC_TOTAL_ING:
			qDebug() << "calculate total data";
			status = STEP_CALC_TOTAL;
			break;
		}
	}

	if (STEP_CALC_CANCEL == status) { return false; }
	else { return true; }


}

int CalcManager::ExecuteCP()
{
	if (!m_CalcCP) { 
		m_CalcCP = new CalcCPDlg();
	}

	int ret = m_CalcCP->exec();
	if (QDialogButtonBox::YesRole == ret)
		return STEP_CALC_MAIN;
	else if (QDialogButtonBox::HelpRole == ret)
		return STEP_CALC_CP_ING;
	else if (QDialogButtonBox::NoRole == ret)
		return STEP_CALC_TOTAL;
	else
		return STEP_CALC_CANCEL;

}

int CalcManager::ExecuteTotal()
{
	if (!m_CalcTotal) {
		m_CalcTotal = new CalcTotalDlg();
	}

	int ret = m_CalcTotal->exec();
	if (QDialogButtonBox::YesRole == ret)
		return STEP_CALC_CP;
	else if (QDialogButtonBox::HelpRole == ret)
		return STEP_CALC_TOTAL_ING;
	else if (QDialogButtonBox::NoRole == ret)
		return STEP_CALC_MAX;
	else
		return STEP_CALC_CANCEL;

}

