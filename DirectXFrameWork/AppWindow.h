#pragma once
#include "CoreWindow.h"
#include "GEngine.h"

class AppWindow : public CoreWindow
{
public:

	AppWindow();
	~AppWindow();

	void onCreate();
	void onDestroy();
	void onUpdate();

	bool initialize(LPCSTR _windowName);

private:
	SwapChain * pSwapChain;
};

