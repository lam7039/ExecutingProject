#include <Windows.h>
#include "Kernel.h"
#include "SceneLoader.h"
#include "Timer.h"

//MACROAGRESSION DETECTED
#define PI 3.1415

//Ignore this, it's only for a basic logger and that's currently being improved by Eimantas
se::Kernel kernel;

class Airplane : public se::Entity {
public:
	Airplane();
	void Render();
};

Airplane::Airplane() {
	Init("airplane.x");
	SetPosition(2.0f, 0.0f, -5.0f);
	SetRotation(PI, 0.0f, 0.0f);
}

void Airplane::Render() {
	kernel.LogDebug("testairplane");
}

class Tiger : public se::Entity {
public:
	Tiger();
	void Update(float delta);
private:
	se::Timer m_timer;
};

Tiger::Tiger() {
	Init("tiger.x");
	SetPosition(-2.0f, 0.0f, 0.0f);
	m_timer.Start();
}

void Tiger::Update(float delta) {
	unsigned int iTime = (int)m_timer.Milliseconds() / 10 % 1000;
	SetRotation(iTime * (2.0f * PI) / 1000.0f, 0.0f, 0.0f);
}

void Start() {
	Airplane *airplane = new Airplane();
	Tiger *tiger = new Tiger();

	se::SceneLoader::GetInstance()->AddScene("rotatingobjects");
	se::SceneLoader::GetInstance()->GetScene("rotatingobjects")->AddEntity(airplane);
	se::SceneLoader::GetInstance()->GetScene("rotatingobjects")->AddEntity(tiger);
	se::SceneLoader::GetInstance()->SetCurrentScene("heightmap");
	kernel.LogDebug("teststart");
	//se::SceneLoader::GetInstance()->GetScene("rotatingobjects")->RemoveObject(tiger);
}

void Stop() {
	kernel.LogDebug("teststop");
}

int main(int argc, char **argv) {

	kernel.StartEngine("GameEngine3D");
	kernel.EnterLoop(Start, Stop);
	return 0;
}