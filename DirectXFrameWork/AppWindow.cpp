#include "AppWindow.h"

AppWindow* gWindow;
LRESULT CALLBACK WndProcToPass(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	CoreWindow::onCreate();
	GEngine::Get()->init(hWnd);

}

void AppWindow::onDestroy()
{
	CoreWindow::onDestroy();
	GEngine::Get()->release();
}

void AppWindow::onUpdate()
{	

}

bool AppWindow::initialize(LPCSTR _windowName)
{
	gWindow = this;
	return CoreWindow::init(_windowName, "AppWindowClass", WndProcToPass);
}

LRESULT CALLBACK WndProcToPass(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

	switch (msg) {
	case WM_CREATE: {
		gWindow->setHWND(hwnd);
		gWindow->onCreate();
	} break;
	case WM_DESTROY: {
		gWindow->onDestroy();
		PostQuitMessage(0);
	} break;
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
}