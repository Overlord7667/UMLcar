#include <Windows.h>
#include"resource.h"
//#define MESAGE_BOX

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef MESAGE_BOX
	MessageBox(NULL, "Hello World", "Info",
		MB_YESNOCANCEL | MB_ICONINFORMATION | MB_SYSTEMMODAL | MB_HELP | MB_DEFBUTTON2 | MB_RIGHT |
		MB_SETFOREGROUND);
#endif // MESAGE_BOX

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:MessageBox(NULL, L"Была нажата кнопка ОК", L"Info", MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
	}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}