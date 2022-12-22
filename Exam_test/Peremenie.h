#pragma once
#include "Header.h"
HWND hKey[27] ,hPole, hMistake, hSec, hStart, hResult, hKeyBefore = NULL;
TCHAR Text[255], buffer_string[255];
HANDLE Timer_Thread;
string bufer;
fstream slova;
WCHAR str[50];
int mistake = 0, result = 0;
int randomer, char_count = 0, timer = 0;