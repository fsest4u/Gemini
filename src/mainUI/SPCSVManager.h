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
#ifndef SP_CSV_MANAGER_H
#define SP_CSV_MANAGER_H

#include <QtCore/QObject>

class SPCSVManager : public QObject
{
	Q_OBJECT

public:

	/**
	* Constructor.
	*/
	SPCSVManager(QObject *parent = 0);
	~SPCSVManager();

	void OpenFile(QString filepath);

private slots:


private:



	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////




};

#endif // SP_CSV_MANAGER_H
