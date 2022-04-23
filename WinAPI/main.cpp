//#include<winapifamily.h>
#include<Windows.h>
#include"resource.h"

CONST CHAR g_szLoginDefaulMessage[] = "Введите логин";
CONST CHAR g_szPasswordDefaulMessage[] = "Введите пароль";


BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM LParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//MessageBox(FindWindow(NULL, "UML - Microsoft Visual Studio"), "Hello World!", "Info", MB_YESNOCANCEL | MB_ICONINFORMATION | MB_HELP | MB_APPLMODAL);

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM LParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG://здесь создаются элементы интерфейса и производится начальная настройка окна.
		//Эот кейс отрабатывает только при первом запуске
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		HWND hPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
		SendMessage(hLogin, WM_SETTEXT, 0, (LPARAM)g_szLoginDefaulMessage);
		SendMessage(hPassword, WM_SETTEXT, 0, (LPARAM)g_szPasswordDefaulMessage);
	}
		break;
	case WM_COMMAND: //обрабатывает нажатие кнопок и любые обращения к элементам окна.
	{
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE] = {};
		HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		HWND hPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);

		switch (LOWORD(wParam))
		{
		case IDOK: MessageBox(hwnd, "Была нажата кнопка OK", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
			/////////////////////////
		case IDC_BUTTON_COPY:
		{
			//CONST INT SIZE = 256;
			//CHAR sz_buffer[SIZE] = {};
			//HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			//HWND hPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		////////////////////////
		case IDC_EDIT_LOGIN:
			if (HIWORD(wParam) == EN_SETFOCUS)
			{
				/*CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				HWND hLoggin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);*/
				SendMessage(hLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				if (strcmp(sz_buffer, g_szLoginDefaulMessage) == 0)
					SendMessage(hLogin, WM_SETTEXT, 0, (LPARAM)"");
			}
			else if (HIWORD(wParam) == EN_KILLFOCUS)
			{
				/*CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				HWND hPassword = GetDlgItem(hwnd, IDC_EDIT_LOGIN);*/
				SendMessage(hPassword, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				if (strlen(sz_buffer) == 0)
					SendMessage(hPassword, WM_SETTEXT, 0, (LPARAM)g_szLoginDefaulMessage);
			}
			break;
		}
		break;
	}
	case WM_CLOSE: //Обрабатывает нажатие на крестик.
		EndDialog(hwnd, 0);
	}
	return FALSE;
}