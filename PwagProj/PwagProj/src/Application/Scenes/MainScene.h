#pragma once

#include <Engine/Scenes/Scene.h>
#include <Engine/Rendering/Entity.h>
#include <Engine/Rendering/Camera.h>
#include <Engine/Window/Window.h>

#include <Application/LSystem/PlantFactory.h>
#include <Application/LSystem/ForestGenerator.h>
#include <Application/Tools/PlantInstancedMeshGen.h>

#include <memory>


class MainScene : public engine::Scene
{
public:
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnUIUpdate() override;
	void OnLSystemUIUpdate();

	virtual void OnMouseMove(int posX, int posY) override;
	virtual void OnMouseButton(engine::KeyState keyState, int button) override;

private:
	std::shared_ptr<engine::Camera> m_camera;
	std::unique_ptr<engine::Entity> m_terrain;

	engine::Material m_plantMaterial;
	
	engine::Entity m_cubeEntity;
	engine::Entity m_skyboxEntity;

	ForestGenerator m_forestGenerator;

	int m_lastMouseX = -1;
	int m_lastMouseY = -1;

	std::shared_ptr<ILSystemGrammar> m_lSystemGrammar;
	float m_timer = 0.0f;
};
