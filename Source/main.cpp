#include "Kernel.h"
#include "SceneLoader.h"
#include "Timer.h"
#include "AssetLoader.h"

//MACROAGRESSION DETECTED
#define PI 3.141592

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

int main(int argc, char **argv) {
	kernel.StartEngine("GameEngine3D");
	kernel.LogDebug("teststart");

	se::AssetLoader::GetInstance()->AddMesh("airplane.x");
	se::AssetLoader::GetInstance()->AddMesh("tiger.x");

	Airplane *airplane = new Airplane();
	Tiger *tiger = new Tiger();

	se::SceneLoader::GetInstance()->AddScene("rotatingobjects");
	se::SceneLoader::GetInstance()->GetScene("rotatingobjects")->AddEntity(airplane);
	se::SceneLoader::GetInstance()->GetScene("rotatingobjects")->AddEntity(tiger);
	se::SceneLoader::GetInstance()->SetCurrentScene("rotatingobjects");

	kernel.EnterLoop();

	kernel.LogDebug("teststop");
	se::AssetLoader::GetInstance()->ReleaseMesh("airplane.x");
	se::AssetLoader::GetInstance()->ReleaseMesh("tiger.x");
	return 0;
}