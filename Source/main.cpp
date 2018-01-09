#include "Kernel.h"
#include "SceneLoader.h"
#include "Timer.h"
#include "AssetLoader.h"

//MACROAGRESSION DETECTED
#define PI 3.141592

//Cloaked an entity as a temporary skybox
class Skybox : public se::Entity {
public:
	Skybox();
	void Render();
};

Skybox::Skybox() {
	Init("skybox2.x");
	SetPosition(2.0f, 0.0f, -5.0f);
	SetRotation(PI, -(PI / 2), 0.0f);
}

void Skybox::Render() {

}

class Tiny : public se::Entity {
public:
	Tiny();
	void Update(float delta);
private:
	se::Timer m_timer;
};

Tiny::Tiny() {
	Init("tiny.x");
	SetScale(1.0f / 50);
	SetPosition(-2.0f, 0.0f, 0.0f);
	//SetRotation(0.0f, -(PI / 2), 0.0f);
	m_timer.Start();
}

void Tiny::Update(float delta) {
	unsigned int iTime = (int)m_timer.Milliseconds() / 10 % 1000;
	SetRotation(iTime * (2.0f * PI) / 1000.0f, -(PI / 2), 0.0f);
}

int main(int argc, char **argv) {
	se::Kernel kernel("GameEngine3D", 800, 500);
	se::Debug logger("project.log");
	logger.Log(0, __FILE__, __LINE__, "teststart");

	se::AssetLoader::GetInstance()->AddMesh("skybox2.x");
	se::AssetLoader::GetInstance()->AddMesh("tiny.x");

	Skybox *skybox = new Skybox();
	Tiny *tiny = new Tiny();

	se::SceneLoader::GetInstance()->AddScene("terrain");
	se::SceneLoader::GetInstance()->AddScene("world");
	se::SceneLoader::GetInstance()->GetScene("world")->AddEntity(skybox);
	se::SceneLoader::GetInstance()->GetScene("world")->AddEntity(tiny);
	se::SceneLoader::GetInstance()->SetCurrentScene("world");

	kernel.EnterLoop();

	se::Debug logger2("engine.log");
	logger2.Log(0, __FILE__, __LINE__, "engine stopped");

	logger.Log(0, __FILE__, __LINE__, "teststop");
	se::AssetLoader::GetInstance()->ReleaseMesh("skybox2.x");
	se::AssetLoader::GetInstance()->ReleaseMesh("tiny.x");
	return 0;
}