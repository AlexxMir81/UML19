#include<winapifamily.h>
#include<Windows.h>
#include"resource.h"

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
	}
		break;
	case WM_COMMAND: //обрабатывает нажатие кнопок и любые обращения к элементам окна.
		switch (LOWORD(wParam))
		{
		case IDOK: MessageBox(hwnd, "Была нажата кнопка OK", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE: //Обрабатывает нажатие на крестик.
		EndDialog(hwnd, 0);
	}
	return FALSE;
}