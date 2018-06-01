#include "Kernel.h"
#include "SceneLoader.h"
#include "WindowManager.h"
#include "SceneManager.h"
#include "AssetManager.h"
#include "Timer.h"
#include "Input.h"
#include "DirectX9\Direct3D.h"
#include "DirectX9\DirectInput.h"

// MACROAGRESSION DETECTED (chill, it's a joke).
#define PI 3.141592

// Example of manually adding and expanding on an Entity.
class Tiny : public se::Entity {
public:
	Tiny(se::AbstractInput *input);
	void Update(float delta) override;
	void Render(se::AbstractRenderer *renderer) override;
private:
	se::Timer m_timer;
	se::AbstractInput *m_input;
	float m_speed;
};

Tiny::Tiny(se::AbstractInput *input) {
	m_input = input;
	m_assetName = "tiny";
	SetScale(1.0f / 50, 1.0f / 50, 1.0f / 50);
	SetPosition(5.0f, 0.0f, 0.0f);
	SetRotation(0.0f, -(PI / 2), 0.0f);
	m_timer.Start();
	m_speed = 100.0f;
}

void Tiny::Update(float delta) {
	unsigned int iTime = (int)m_timer.Milliseconds() / 10 % 1000;
	SetRotation(iTime * (2.0f * PI) / 1000.0f, -(PI / 2), 0.0f);
	if (m_input->IsPressed(se::SE_KEY_I)) {
		m_position.z += m_speed * delta;
	}
	if (m_input->IsPressed(se::SE_KEY_K)) {
		m_position.z -= m_speed * delta;
	}
	if (m_input->IsPressed(se::SE_KEY_L)) {
		m_position.x += m_speed * delta;
	}
	if (m_input->IsPressed(se::SE_KEY_J)) {
		m_position.x -= m_speed * delta;
	}
}

void Tiny::Render(se::AbstractRenderer *renderer) {
	renderer->SetFVF(true, false, false, true);
	renderer->SetStreamSource(0, m_assetName, 0);
	renderer->SetTexture(0, m_assetName, 0);
	renderer->Draw(m_assetName);
}

int main() {
	// Begin smallest setup possible.
	//se::Kernel kernel("GameEngine3D", true, 0, 0, 800, 500, new se::Direct3D(), new se::DirectInput());
	//kernel.EnterLoop();
	// End smallest setup possible.

	int width = 800;
	int height = 500;
	se::AbstractRenderer *renderer = new se::Direct3D();
	se::AbstractInput *input = new se::DirectInput();
	se::Kernel kernel("GameEngine3D", false, 0, 0, width, height, renderer, input);
	//se::WindowManager::GetInstance()->AddWindow(renderer, "2nd window", false, width, 0, width, height, input);

	// Automatically loading assets, scenes and entities with an xml file.
	se::SceneLoader loader(renderer, "Assets\\level1.xml", input);

	// Example for manually adding an entity to a scene.
	se::SceneManager::GetInstance()->GetScene("empty")->AddEntity(new Tiny(input));
	se::SceneManager::GetInstance()->GetScene("world")->AddEntity(new Tiny(input));
	se::SceneManager::GetInstance()->SetCurrentScene("world");

	kernel.EnterLoop();
	// This is unnecessary, when the loop quits all assets automatically release, but it's just to show you *can* do it.
	se::AssetManager::GetInstance()->ReleaseAsset("tiny");
	return 0;
}