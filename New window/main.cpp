#define _CRT_SECURE_NO_WARNING
#include<Windows.h>
#include<stdio.h>
#include"resource.h"


CONST CHAR g_szCLASS_NAME[] = "MyWindowClass";
CONST CHAR g_szTitle[] = "MY PROGRAMM";


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна
	WNDCLASSEX wc; //ws - Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;//Указатель на процедуру окна
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	//wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_DISCORD));
	//wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_YUOTUBE));
	wc.hIcon = (HICON)LoadImage(hInstance, "1.ico",IMAGE_ICON,0,0,LR_DEFAULTSIZE |LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "2.ico",IMAGE_ICON,0,0,LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = g_szCLASS_NAME;
	wc.lpszMenuName = NULL;
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed!", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) Создание окна

	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	int window_width = screen_width - screen_width / 4;
	int window_height = screen_height - screen_height / 4;
	int window_start_x = screen_width / 8;
	int window_start_y = screen_height / 8;


	HWND hwnd = CreateWindowEx
	(
		WS_EX_CLIENTEDGE | WS_EX_APPWINDOW,     //exStyle
		g_szCLASS_NAME,       //имя окна
		g_szCLASS_NAME,       //Заголовок окна
		WS_OVERLAPPEDWINDOW,  //Стиль окна OVERLAPPED всегда задаётся для главного окна программы
		window_start_x, window_start_y,
		window_width, window_height,/*CW_USEDEFAULT, CW_USEDEFAULT,*/ //Размер окна
		NULL,        //Родительское окно
		NULL,        //Меню отсутствует
		hInstance,   //*,exe файл окна
		NULL
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);// Задаём режим отображения окна
	UpdateWindow(hwnd); // Прорисовываем окно(отправляем сообщени WM_PAINT)

	//3) Запускаем цикл сообщений
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE: //Создаются элементы окна
	{
		//HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_DISCORD));
		//SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
	}
	break;
	case WM_COMMAND: //Обработка команд нажатия кнопок, и других элементов окна
		break;
	case WM_SIZE:
	case WM_MOVE:
	{
		RECT rect;
		GetWindowRect(hwnd, &rect);
		CONST INT SIZE = 256;
		CHAR buffer[SIZE]{};
		SendMessage(hwnd, WM_GETTEXT, SIZE, (LPARAM)buffer);
		sprintf
		(
			buffer, "%s Position: %dx%d, Size: %dx%d",
			g_szTitle, rect.left, rect.top, rect.right - rect.left,
			rect.bottom - rect.top
		);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)buffer);
	}
	break;
	case WM_CLOSE:
		switch (MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "А если подумать?", MB_YESNO | MB_ICONQUESTION))
		{
		case IDYES:
			MessageBox(hwnd, "Ну всё, я обиделся!!!!", "Info", MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd); break;
		case IDNO: MessageBox(hwnd, "Это хорошо", "Info", MB_OK | MB_ICONINFORMATION); break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}