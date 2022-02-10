#include<Windows.h>

CONST CHAR g_szCLASS_NAME[] = "MyWindowClass";
CONST CHAR g_szTitle[] = "こんにちは";


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
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
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
	HWND hwnd = CreateWindowEx
	(
		WS_EX_CLIENTEDGE,     //exStyle
		g_szCLASS_NAME,       //имя окна
		g_szTitle,       //Заголовок окна
		WS_OVERLAPPEDWINDOW,  //Стиль окна OVERLAPPED всегда задаётся для главного окна программы
		CW_USEDEFAULT, CW_USEDEFAULT, //Позиция окна
		CW_USEDEFAULT, CW_USEDEFAULT, //Размер окна
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
		break;
	case WM_COMMAND: //Обработка команд нажатия кнопок, и других элементов окна
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