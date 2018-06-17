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
#ifndef SETTINGDATA_H
#define SETTINGDATA_H

#include <QtCore/QSettings>

class SettingData : public QSettings
{
public:
	SettingData();
	virtual ~SettingData();


private:


};

#endif // SETTINGDATA_H
