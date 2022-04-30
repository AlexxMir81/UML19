﻿#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR* string[] = { "this", "is", "my", "first", "list", "box", "1024", "256" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < sizeof(string) / sizeof(string[0]); i++)
		{
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)string[i]);
		}
		SendMessage(hListBox, LB_SETCURSEL, 4, 0);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
			int i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);
			CHAR sz_msg[SIZE] = {};
			sprintf(sz_msg, "Вы выбрали элемент N%d, со строкой %s", i, sz_buffer);
			MessageBox(hwnd, sz_msg, "info", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		case IDC_BUTTON_ADD:
		{
			DialogBox(GetModuleHandle(NULL), LPCTSTR(IDD_DIALOG2), hwnd, (DLGPROC)DlgProc);
		}
			break;
		case IDOK_ADD:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_ADD);
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
		/*	if (GetDlgItem(hwnd, 123))
			{
				MessageBox(hwnd, "ItemOK", "Info", MB_OK);
			}
			else
			{
				MessageBox(hwnd, "NoItemFound", "Info", MB_OK);

			}*/
			HWND parent = GetParent(hwnd);
			if (sz_buffer != NULL)
				SendMessage(GetDlgItem(parent, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)sz_buffer);
			EndDialog(hwnd, 0);
		}
			break;
		case IDC_BUTTON_DELETE:
		{
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
			int i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			SendMessage(hListBox, LB_DELETESTRING, i, 0);
		}
			break;
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}