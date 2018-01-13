#include "Kernel.h"
#include "SceneManager.h"
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
	m_entityName = "skybox2.x";
	SetPosition(2.0f, 0.0f, -5.0f);
	SetRotation(PI, -(PI / 2), 0.0f);
	SetScale(2.0f);
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
	m_entityName = "tiny.x";
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
	logger.Log(0, __FILE__, __LINE__, "project started");

	se::AssetLoader::GetInstance()->AddMesh("skybox2.x");
	//se::AssetLoader::GetInstance()->AddMesh("tiny.x");
	se::AssetLoader::GetInstance()->AddTerrain("Heightmap.bmp", "texture.jpg");

	Skybox *skybox = new Skybox();
	//Tiny *tiny = new Tiny();

	se::SceneManager::GetInstance()->AddScene("world");
	se::SceneManager::GetInstance()->GetScene("world")->AddEntity(skybox);
	//se::SceneManager::GetInstance()->GetScene("world")->AddEntity(tiny);
	se::SceneManager::GetInstance()->SetCurrentScene("world");

	kernel.EnterLoop();

	se::AssetLoader::GetInstance()->ReleaseMesh("skybox2.x");
	//se::AssetLoader::GetInstance()->ReleaseMesh("tiny.x");
	return 0;
}