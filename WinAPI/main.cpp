#include<Windows.h>

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	MessageBox(NULL, "Hello World!", "Info", MB_OK | MB_ICONINFORMATION);

	return 0;
}