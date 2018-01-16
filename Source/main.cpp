#include "Kernel.h"
#include "Window.h"
#include "SceneManager.h"
#include "Timer.h"
#include "AssetLoader.h"
#include "Input.h"
#include "CameraController.h"
#include "DirectX9/DirectXTerrain.h"
#include "DirectX9/DirectXMesh.h"
#include "DirectX9/DirectXCamera.h"

//MACROAGRESSION DETECTED
#define PI 3.141592

//Cloaked an entity as a temporary skybox
//class Skybox : public se::Entity {
//public:
//	Skybox();
//	void Render();
//};
//
//Skybox::Skybox() {
//	m_entityName = "skybox2.x";
//	SetPosition(2.0f, 0.0f, -5.0f);
//	SetRotation(PI, -(PI / 2), 0.0f);
//	SetScale(2.0f);
//}
//
//void Skybox::Render() {
//
//}

class Tiny : public se::Entity {
public:
	Tiny();
	void Update(float delta);
private:
	se::Timer m_timer;
};

Tiny::Tiny() {
	m_entityName = "asdf";
	m_assetName = "tiny";
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
	se::Input input;
	se::Kernel kernel("GameEngine3D", 800, 500, new se::Direct3D(), &input);
	//kernel.AddWindow("test", 1920, 1080);
	se::Debug logger("project.log");
	logger.Log(0, __FILE__, __LINE__, "project started");

	
	se::CameraController controller(new se::DirectXCamera(), &input);


	se::Mesh *tinyMesh = new se::Mesh("Assets\\tiny.x");

	//se::AssetLoader::GetInstance()->AddMesh("skybox2.x");
	se::AssetLoader::GetInstance()->AddAsset("tiny", tinyMesh);

	se::Terrain *terrain = new se::Terrain();
	terrain->Create("Heightmap2.bmp", "texture.jpg");
	//Skybox *skybox = new Skybox();
	Tiny *tiny = new Tiny();

	se::SceneManager::GetInstance()->AddScene("world");
	se::SceneManager::GetInstance()->GetScene("world")->SetTerrain(terrain);
	//se::SceneManager::GetInstance()->GetScene("world")->AddEntity(skybox);
	se::SceneManager::GetInstance()->GetScene("world")->AddEntity(tiny);
	se::SceneManager::GetInstance()->SetCurrentScene("world");

	kernel.EnterLoop();

	//se::AssetLoader::GetInstance()->ReleaseAsset("skybox2.x");
	se::AssetLoader::GetInstance()->ReleaseAsset("tiny");
	return 0;
}