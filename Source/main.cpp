#include <Windows.h>
#include "Engine.h"

void Start() {
	se::LogDebug("teststart");
}

void Stop() {
	se::LogDebug("teststop");
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	se::StartEngine(hInstance, nCmdShow, "GameEngine3D");
	se::EnterLoop(Start, Stop);
	return 0;
}