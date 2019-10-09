#pragma once
#include "Windows.h" 

class CoreWindow
{
public:
	CoreWindow();
	virtual ~CoreWindow();

	bool isRunning();
	void broadcast();

	virtual void onCreate();
	virtual void onDestroy();
	virtual void onUpdate() = 0;

	void setHWND(HWND whnd);

protected:

	bool bRuns = false;
	HWND hWnd;

	bool init(LPCSTR _windowName,
			  LPCSTR _windowClassName,
			  LRESULT (CALLBACK *_WndProc)(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam));
};

