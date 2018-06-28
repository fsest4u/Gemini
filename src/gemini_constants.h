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
#ifndef GEMINI_CONSTANTS_H
#define GEMINI_CONSTANTS_H

class QString;
class QStringList;

// These enable us to use constants defined
// in one CPP file to be used in another
extern const QStringList CP_NAME;

const int CSV_START_ROW_KYOBO = 1;
const int CSV_START_ROW_NAVER = 6;
const int CSV_START_ROW_RIDI = 1;
const int CSV_START_ROW_MUNPIA = 1;
const int CSV_START_ROW_MRBLUE = 5;
const int CSV_START_ROW_BAROBOOK = 2;
const int CSV_START_ROW_BOOKCUBE = 3;
const int CSV_START_ROW_EPYRUS = 1;
const int CSV_START_ROW_OEBOOK = 1;
const int CSV_START_ROW_ONESTORE = 1;
const int CSV_START_ROW_KAKAO = 1;
const int CSV_START_ROW_COMICO = 2;
const int CSV_START_ROW_TOCSODA = 5;
const int CSV_START_ROW_KEPUB = 1;

#endif // GEMINI_CONSTANTS_H
