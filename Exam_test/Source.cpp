#include "Peremenie.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void KeyDownHandler(HWND hwnd, WPARAM wParam, LPARAM lParam);
DWORD WINAPI Timer(LPVOID lp);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	srand(time(0));
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		for (int i = 0; i < 27; i++)
		{
			hKey[i] = GetDlgItem(hwnd, IDC_A + i);
		}
		slova.open(TEXT("Madness.txt"));
		randomer = rand() % (1 - 10) + 1;
		for (int i = 0; i < randomer; i++)
		{
			getline(slova, bufer);
		}
		for (int i = 0; i < bufer.size(); i++)
		{
			Text[i] = bufer[i];
		}
		char_count = _tcslen(Text);
		hStart = GetDlgItem(hwnd, IDC_BUTTON1);
		hPole = GetDlgItem(hwnd, IDC_EDIT1);
		hMistake = GetDlgItem(hwnd, IDC_EDIT2);
		hSec = GetDlgItem(hwnd, IDC_EDIT3);
		hResult = GetDlgItem(hwnd, IDC_EDIT4);
		ShowWindow(hResult, FALSE);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			SetWindowText(hPole, Text);
			SetWindowText(hMistake, TEXT("0"));
			EnableWindow(hStart, FALSE);
			Timer_Thread = CreateThread(NULL, 0, Timer, NULL, NULL, NULL);
		}
		break;
	}
	case WM_SYSKEYDOWN:
		KeyDownHandler(hwnd, wParam, lParam);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return TRUE;
}

void KeyDownHandler(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	int num_key = 65;
	int vkey = (TCHAR)wParam;
	EnableWindow(hKeyBefore, FALSE);
	wsprintf(str, L"vkey: %c", vkey);
	if (TCHAR(vkey + 32) == (int)Text[0] || (vkey == 32 && Text[0] == ' '))
	{
		for (int i = 1; i < char_count; i++)
		{
			Text[i - 1] = Text[i];
			Text[char_count - 1] = '\0';
		}
		char_count--;
		SetWindowText(hPole, Text);
	}
	else
	{
		mistake++;
		wsprintf(buffer_string, TEXT("%d"), mistake);
		SetWindowText(hMistake, buffer_string);
	}
	for (int i = 0; num_key <= 90; i++, num_key++)
	{
		if (vkey == num_key)
		{
			EnableWindow(hKey[i], TRUE);
			hKeyBefore = hKey[i];
		}
		else if (vkey == 32)
		{
			EnableWindow(hKey[26], TRUE);
			hKeyBefore = hKey[26];
		}
	}
	if (Text[0] == '\0')
	{
		TerminateThread(Timer_Thread, 0);
		result = 12 - mistake;
		if (result < 0)
		{
			result = 0;
		}
		wsprintf(buffer_string, TEXT("Ваша оценка = %d / 12"), result);
		SetFocus(hResult);
		ShowWindow(hResult, TRUE);
		SetWindowText(hResult, buffer_string);
	}
}

DWORD WINAPI Timer(LPVOID lp)
{
	TCHAR buf[32];
	SetWindowText(hSec, TEXT("0 секунд"));
	while (true)
	{
		Sleep(1000);
		timer++;
		wsprintf(buf, TEXT("%d секунд"), timer);
		SetWindowText(hSec, buf);
	}
}