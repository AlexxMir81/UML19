#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"

//#define IDC_STATIC 1000 //Ресурс для static text

CONST CHAR g_szClassName[] = "MyWindowClass"; //имя класса окна
CONST CHAR g_szWindowTitle[] = "My first Window"; //заголовок окна
//g_ - Global
//sz - string zero (NULL Terminated Line) Венгерская нотация
//wvWidgets библиотека для работы с окнами

CONST INT g_iBtnSize = 50; //размер кнопки в пикселях
CONST INT g_INTERVAL = 2;   //интервал между кнопками в пикселях
CONST INT g_START_X = 10;
CONST INT g_START_Y = 10;

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//1) Регистрация класса окна:
	WNDCLASSEX wc; //wc- Windows Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = 0;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_TOWER));  //отображается в панели задач
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_CHIP)); //SmallIcon от отображается в строке заголовка
	//wc.hIcon = (HICON)LoadImage(hInstance, "radiotower.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE),
	//wc.hIconSm = (HICON)LoadImage(hInstance, "card_sim.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE),
	wc.hCursor = LoadCursor(hInstance, LPCSTR(IDC_CURSOR1));
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = (WNDPROC)WndProc; //имя фукции - это указатель на функцию, оно содержить адрес,
	//по которому функция загружена в память
	wc.lpszClassName = g_szClassName;
	wc.lpszMenuName = NULL;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed! :(", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	//2) Создание окна:
	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	int window_width = screen_width * .75;
	int window_height = screen_height * .75;
	int start_x = screen_width * 0.125;
	int start_y = screen_height * 0.125;

	HWND hwnd = CreateWindowEx
	(
		NULL, //exStyle дополнительные стили
		g_szClassName,
		g_szWindowTitle,
		WS_OVERLAPPEDWINDOW, //Главное окно, у которого есть строка заголовка, 
							//кнопки управления окном, может изменяться по размерам
		start_x, start_y, //положение окна на экране в пикселях
		window_width, window_height, // размер окна в писелях
		NULL,  //родительское окно Parent Window
		NULL,  //меню(в данном случае нет ID ресурса меню, если окно главное (OVERLAPPED),
			   //или ID этого окна, если окно дочернее
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed!", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow); //задает режим отображения окна
	UpdateWindow(hwnd); //рисует окно
		//3) Запуск цикла сообщений:
	MSG msg;
	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
		return msg.wParam;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		//CreateWindowExA - ANSI-кодиоовка
		//CreateWindowExW - Wide-кодиоовка (Unicode)
		//Create IDC_Static:
		/*HWND hStatic = CreateWindowEx
		(
			0,
			"Static",
			"Эта статическая строка будет отображать размер окна и его положение на экране",
			WS_CHILD | WS_VISIBLE,
			10, 10,
			800,
			50,
			hwnd,
			(HMENU)IDC_STATIC,
			GetModuleHandle(NULL), //возвращает hInstance
			0
		);*/

		int digit = 1;
		char sz_digit[] = "0";
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				sz_digit[0] ='0'+ digit;
				CreateWindowEx
				(
					0, "Button", sz_digit,
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					g_START_X + (g_iBtnSize + g_INTERVAL)*j,
					g_START_Y + (g_iBtnSize + g_INTERVAL)*(2-i),
					g_iBtnSize, g_iBtnSize,
					hwnd, (HMENU)(IDC_BUTTON_0+digit),
					GetModuleHandle(NULL), NULL
				);
				digit++;
			}
		}

	}
		break;
	case WM_COMMAND: break;
	case WM_SIZE:
	case WM_MOVE:
	{
		CONST INT SIZE = 256;
		CHAR sz_msg[SIZE] = {};
		RECT rect; //прямоугольник окна
		GetWindowRect(hwnd, &rect);
		int window_width = rect.right - rect.left;
		int window_heght = rect.bottom - rect.top;
		sprintf(sz_msg, "%s - Size:%ix%i, Position: %ix%i", g_szWindowTitle, window_width, window_heght, rect.left, rect.top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_msg);
	//	SendMessage(GetDlgItem(hwnd, IDC_STATIC), WM_SETTEXT, 0, (LPARAM)sz_msg);
	}
		break;
	case WM_CLOSE: 
		if(MessageBox(hwnd, "Выдействительно хотите закрыть окно?","Question", MB_YESNO|MB_ICONQUESTION)==IDYES)
			DestroyWindow(hwnd); break;
	case WM_DESTROY: PostQuitMessage(NULL); break;  //уничтожить окно
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}