#include <Windows.h>
#include "Engine.h"
#include "SceneLoader.h"
#include "Timer.h"

#define PI 3.1415

class Airplane : public se::Object {
public:
	Airplane();
	virtual void Render();
};

Airplane::Airplane() {
	Init("airplane.x");
	SetPosition(2.0f, 0.0f, -5.0f);
	SetRotation(PI, 0.0f, 0.0f);
}

void Airplane::Render() {
	se::LogDebug("testairplane");
}

class Tiger : public se::Object {
public:
	Tiger();
	virtual void Update(float delta);
};

Tiger::Tiger() {
	Init("tiger.x");
	SetPosition(-2.0f, 0.0f, 0.0f);
}

void Tiger::Update(float delta) {
	unsigned int iTime = (int)delta / 10 % 1000;
	SetRotation(iTime * (2.0f * PI) / 1000.0f, 0.0f, 0.0f);
}

void Start() {
	Airplane *airplane = new Airplane();
	Tiger *tiger = new Tiger();

	se::SceneLoader::GetInstance()->AddScene("rotatingobjects");
	se::SceneLoader::GetInstance()->GetScene("rotatingobjects")->AddObject(airplane);
	se::SceneLoader::GetInstance()->GetScene("rotatingobjects")->AddObject(tiger);
	se::SceneLoader::GetInstance()->AddScene("heightmap");
	se::SceneLoader::GetInstance()->GetScene("heightmap")->AddObject(tiger);
	se::SceneLoader::GetInstance()->SetCurrentScene("rotatingobjects");
	se::LogDebug("teststart");
	//se::SceneLoader::GetInstance()->GetScene("rotatingobjects")->RemoveObject(tiger);
}

void Stop() {
	se::LogDebug("teststop");
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	se::StartEngine(hInstance, nCmdShow, "GameEngine3D");
	se::EnterLoop(Start, Stop);
	return 0;
}