#include "Kernel.h"
#include "SceneLoader.h"
#include "Timer.h"
#include "AssetLoader.h"

//MACROAGRESSION DETECTED
#define PI 3.141592

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
	Init("tiny.x");
	SetScale(1.0f / 50);
	SetPosition(-2.0f, 0.0f, 0.0f);
	SetRotation(0.0f, -(PI / 2), 0.0f);
	m_timer.Start();
}

void Tiger::Update(float delta) {
	//unsigned int iTime = (int)m_timer.Milliseconds() / 10 % 1000;
	//SetRotation(iTime * (2.0f * PI) / 1000.0f, 0.0f, 0.0f);
}

int main(int argc, char **argv) {
	se::Kernel kernel("GameEngine3D");
	se::Debug logger("project.log");
	logger.Log(0, __FILE__, __LINE__, "teststart");

	se::AssetLoader::GetInstance()->AddMesh("airplane.x");
	se::AssetLoader::GetInstance()->AddMesh("tiny.x");

	Airplane *airplane = new Airplane();
	Tiger *tiger = new Tiger();

	se::SceneLoader::GetInstance()->AddScene("terrain");
	se::SceneLoader::GetInstance()->AddScene("rotatingobjects");
	se::SceneLoader::GetInstance()->GetScene("rotatingobjects")->AddEntity(airplane);
	se::SceneLoader::GetInstance()->GetScene("rotatingobjects")->AddEntity(tiger);
	se::SceneLoader::GetInstance()->SetCurrentScene("rotatingobjects");

	kernel.EnterLoop();

	se::Debug logger2("engine.log");
	logger2.Log(0, __FILE__, __LINE__, "engine stopped");

	logger.Log(0, __FILE__, __LINE__, "teststop");
	se::AssetLoader::GetInstance()->ReleaseMesh("airplane.x");
	se::AssetLoader::GetInstance()->ReleaseMesh("tiny.x");
	return 0;
}