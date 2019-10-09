#include "CoreWindow.h"



CoreWindow::CoreWindow()
{
}


CoreWindow::~CoreWindow()
{
}

bool CoreWindow::isRunning()
{
	return bRuns;
}

void CoreWindow::broadcast()
{
	MSG msg;
	while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	this->onUpdate();
	Sleep(1);
}

void CoreWindow::onCreate()
{

}

void CoreWindow::onDestroy()
{
	bRuns = false;
}

void CoreWindow::setHWND(HWND hwnd)
{
	hWnd = hwnd;
}

bool CoreWindow::init(LPCSTR _windowName, LPCSTR _windowClassName, LRESULT (CALLBACK * _WndProc)(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam))
{
	WNDCLASSEX wclass{};
	wclass.cbClsExtra = NULL;
	wclass.cbSize = sizeof(WNDCLASSEX);
	wclass.cbWndExtra = NULL;
	wclass.hbrBackground = HBRUSH(COLOR_WINDOW);
	wclass.hCursor = LoadCursor(NULL, IDC_CROSS);
	wclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wclass.hInstance = NULL;
	wclass.lpfnWndProc = _WndProc;
	wclass.lpszClassName = _windowClassName;
	wclass.lpszMenuName = "";
	wclass.style = NULL;

	if (!RegisterClassEx(&wclass))
		return false;

	hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, _windowClassName, _windowName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, NULL, NULL);

	if (!hWnd)
		return false;

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	bRuns = true;
	return true;
}
