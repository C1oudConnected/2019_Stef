#include "AppWindow.h"

int main() {

	AppWindow window;
	if (window.initialize("Recreated")) {
		while (window.isRunning()) {
			window.broadcast();
			GEngine::Get()->clearRT(1,0,0,1);
			GEngine::Get()->present(false);
		}
	}

}