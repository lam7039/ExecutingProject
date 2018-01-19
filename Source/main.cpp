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
	Tiny(se::Input *input);
	void Update(float delta);
private:
	se::Timer m_timer;
	se::Input *m_input;
	float m_speed;
};

Tiny::Tiny(se::Input *input) {
	m_input = input;
	m_assetName = "tiny";
	SetScale(1.0f / 50, 1.0f / 50, 1.0f / 50);
	SetPosition(-2.0f, 0.0f, 0.0f);
	//SetRotation(0.0f, -(PI / 2), 0.0f);
	m_timer.Start();
	m_speed = 100.0f;
}

void Tiny::Update(float delta) {
	unsigned int iTime = (int)m_timer.Milliseconds() / 10 % 1000;
	SetRotation(iTime * (2.0f * PI) / 1000.0f, -(PI / 2), 0.0f);
	if (m_input->IsPressed(DIK_I)) {
		m_transform.posZ += m_speed * delta;
	}
	if (m_input->IsPressed(DIK_K)) {
		m_transform.posZ -= m_speed * delta;
	}
	if (m_input->IsPressed(DIK_L)) {
		m_transform.posX += m_speed * delta;
	}
	if (m_input->IsPressed(DIK_J)) {
		m_transform.posX -= m_speed * delta;
	}
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
	//se::Kernel kernel("GameEngine3D", true, 0, 0, 800, 500, new se::Direct3D(), new se::Input);
	//kernel.EnterLoop();
	//End smallest setup possible

	int width = 800;
	int height = 500;
	se::Direct3D *renderer = new se::Direct3D();
	se::Input input;
	se::Kernel kernel("GameEngine3D", false, 0, 0, width, height, renderer, &input);
	kernel.AddWindow("test", width, 0, 800, 500);

	se::CameraController controller(new se::Camera(renderer->GetDevice(), width, height), &input);
	kernel.SetCameraController(&controller);
	//se::Transform3f target;
	//target.posZ = -15.0f;
	//controller.SetTarget(&target);

	se::Mesh *tinyMesh = new se::Mesh(renderer->GetDevice(), "Assets\\tiny.x");
	Tiny *tiny = new Tiny(&input);

	se::Mesh *airplaneMesh = new se::Mesh(renderer->GetDevice(), "Assets\\airplane.x");
	Airplane *airplane = new Airplane();

	se::AssetManager::GetInstance()->AddAsset("tiny", tinyMesh);
	se::AssetManager::GetInstance()->AddAsset("airplane", airplaneMesh);

	se::Transform3f transformTerrain;
	transformTerrain.posX = 0.0f;
	transformTerrain.posY = -20.0f;
	transformTerrain.posZ = 10.0f;
	transformTerrain.rotX = 0.0f;
	transformTerrain.rotY = 0.0f;
	transformTerrain.rotZ = 0.0f;
	se::Terrain *terrain = new se::Terrain(renderer->GetDevice());
	terrain->Create("Heightmap2.bmp", "texture.jpg", transformTerrain);

	se::Skybox *skybox = new se::Skybox(renderer->GetDevice());
	se::Transform3f transformSkybox;
	transformSkybox.posX = -250.0f;
	transformSkybox.posY = 250.0f;
	transformSkybox.posZ = 250.0f;
	transformSkybox.scaleX = 500.0f;
	transformSkybox.scaleY = 500.0f;
	transformSkybox.scaleZ = 500.0f;
	//skybox->Create(transformSkybox, "Assets\\yokohama.jpg");
	skybox->Create(transformSkybox, "Assets\\faulty_skybox_texture.jpg"); //use this when you want it to load quickly since the good one is a bit big, although this will have black borders on top and bottom except in front

	se::SceneManager::GetInstance()->AddScene("empty");
	se::SceneManager::GetInstance()->AddScene("world");
	se::SceneManager::GetInstance()->GetScene("world")->SetTerrain(terrain);
	se::SceneManager::GetInstance()->GetScene("world")->SetSkybox(skybox);
	se::SceneManager::GetInstance()->GetScene("world")->AddEntity(tiny);
	se::SceneManager::GetInstance()->GetScene("world")->AddEntity(airplane);
	se::SceneManager::GetInstance()->SetCurrentScene("world");

	kernel.EnterLoop();
	//this is unecessary, when the loop quits all assets automatically release, but it's just to show you *can* do it
	se::AssetManager::GetInstance()->ReleaseAsset("tiny");
	return 0;
}