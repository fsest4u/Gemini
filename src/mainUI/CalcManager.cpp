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
#include <QtWidgets/QFileDialog>

#include "calcTotal/CalcTotalDlg.h"

#include "CalcManager.h"

#include "gemini_constants.h"


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

bool CalcManager::ExecuteCalc(QHash<int, QString>& cpFileList, QString lastFolderOpen)
{
	// for debug
	//foreach(const int key, cpFileList.keys()) {
	//	qDebug() << "[SetCPList] key : " << key << ", value : " << cpFileList.value(key);
	//}

	m_LastFolderOpen = lastFolderOpen;

	int status = STEP_CALC_MAIN_NEXT;
	while (STEP_CALC_CANCEL > status 
		&& STEP_CALC_MAIN < status)
	{
		switch (status)
		{
		case STEP_CALC_CP_PREV:
			qDebug() << "Goto Main UI Prev";
			if (m_CalcCP) {
				delete m_CalcCP;
				m_CalcCP = 0;
			}
			status = STEP_CALC_CANCEL;
			break;
		case STEP_CALC_MAIN_NEXT:
		case STEP_CALC_CP:
			qDebug() << "Goto Calc CP UI";
			status = ExecuteCP(cpFileList, true);
			break;
		case STEP_CALC_TOTAL_PREV:
			qDebug() << "Goto Calc CP UI Prev";
			if (m_CalcTotal) {
				delete m_CalcTotal;
				m_CalcTotal = 0;
			}
			status = ExecuteCP(cpFileList, false);
			break;
		case STEP_CALC_CP_NEXT:
		case STEP_CALC_TOTAL:
			qDebug() << "Goto Calc Total UI";
			status = ExecuteTotal(true);
			break;
		case STEP_CALC_TOTAL_NEXT:
			qDebug() << "Extract CSV Files";
			status = ExtractCSV();
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
		if (!m_CalcCP->SetCP(cpFileList)) {
			return STEP_CALC_CANCEL;
		}
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

int CalcManager::ExtractCSV()
{

	if (!m_CalcCP || !m_CalcTotal) {
		return STEP_CALC_CANCEL;
	}

	QString dir = QFileDialog::getExistingDirectory(this, tr("Save CSV File"), m_LastFolderOpen);
	
	// CP Data
	if (m_CalcCP) {
		m_CalcCP->ExtractCSV(dir);

		delete m_CalcCP;
		m_CalcCP = 0;
	}

	// Total Data
	if (m_CalcTotal) {
		m_CalcTotal->ExtractCSV(dir);
	
		delete m_CalcTotal;
		m_CalcTotal = 0;
	}

	return STEP_CALC_MAX;

}

