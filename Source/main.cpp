#include "Kernel.h"
#include "SceneManager.h"
#include "Timer.h"
#include "AssetManager.h"
#include "Transform.h"
#include "Input.h"
#include "CameraController.h"
#include "DirectX9/DirectXTerrain.h"
#include "DirectX9/DirectXMesh.h"
#include "DirectX9/DirectXCamera.h"
#include "DirectX9/DirectXSkybox.h"

//MACROAGRESSION DETECTED (chill, it's a joke)
#define PI 3.141592

class Tiny : public se::Entity {
public:
	Tiny();
	void Update(float delta);
private:
	se::Timer m_timer;
};

Tiny::Tiny() {
	m_assetName = "tiny";
	SetScale(1.0f / 50, 1.0f / 50, 1.0f / 50);
	SetPosition(-2.0f, 0.0f, 0.0f);
	//SetRotation(0.0f, -(PI / 2), 0.0f);
	m_timer.Start();
}

void Tiny::Update(float delta) {
	unsigned int iTime = (int)m_timer.Milliseconds() / 10 % 1000;
	SetRotation(iTime * (2.0f * PI) / 1000.0f, -(PI / 2), 0.0f);
}

class Airplane : public se::Entity {
public:
	Airplane();
};

Airplane::Airplane() {
	m_assetName = "airplane";
	SetScale(1.0f, 1.0f, 1.0f);
	SetPosition(20.0f, 0.0f, 0.0f);
}

int main() {
	//Begin smallest setup possible
	//se::Kernel kernel("GameEngine3D", 800, 500, new se::Direct3D(), new se::Input);
	//kernel.EnterLoop();
	//End smallest setup possible

	int width = 800;
	int height = 500;
	se::Direct3D *renderer = new se::Direct3D();
	se::Input input;
	se::Kernel kernel("GameEngine3D", width, height, renderer, &input);
	kernel.AddWindow("test", 0, 0, 1920, 1080);
	
	se::CameraController controller(new se::DirectXCamera(renderer->GetDevice(), width, height), &input);
	kernel.SetCameraController(&controller);
	//se::Transform3f target;
	//target.posZ = -15.0f;
	//controller.SetTarget(&target);

	se::Mesh *tinyMesh = new se::Mesh(renderer->GetDevice(), "Assets\\tiny.x");
	Tiny *tiny = new Tiny();
	se::Mesh *airplaneMesh = new se::Mesh(renderer->GetDevice(), "Assets\\airplane.x");
	Airplane *airplane = new Airplane();

	se::AssetManager::GetInstance()->AddAsset("tiny", tinyMesh);
	se::AssetManager::GetInstance()->AddAsset("airplane", airplaneMesh);

	se::Terrain *terrain = new se::Terrain(renderer->GetDevice());
	terrain->Create("Heightmap2.bmp", "texture.jpg");
	se::Skybox *skybox = new se::Skybox(renderer->GetDevice());
	se::Transform3f transformSkybox;
	transformSkybox.posX = -250.0f;
	transformSkybox.posY = 250.0f;
	transformSkybox.posZ = 250.0f;
	transformSkybox.scaleX = 500.0f;
	transformSkybox.scaleY = 500.0f;
	transformSkybox.scaleZ = 500.0f;
	skybox->Create(transformSkybox, "Assets\\yokohama.jpg");
	//skybox->Create(transformSkybox, "Assets\\faulty_skybox_texture.jpg"); //use this when you want it to load quickly since the good one is a bit big, although this will have black borders on top and bottom except in front


	se::SceneManager::GetInstance()->AddScene("world");
	se::SceneManager::GetInstance()->GetScene("world")->SetTerrain(terrain);
	se::SceneManager::GetInstance()->GetScene("world")->SetSkybox(skybox);
	se::SceneManager::GetInstance()->GetScene("world")->AddEntity(tiny);
	se::SceneManager::GetInstance()->GetScene("world")->AddEntity(airplane);
	se::SceneManager::GetInstance()->SetCurrentScene("world");

	kernel.EnterLoop();

	se::AssetManager::GetInstance()->ReleaseAsset("tiny");
	return 0;
}