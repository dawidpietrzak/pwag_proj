#pragma once

#include <Engine/Scenes/Scene.h>
#include <Engine/Rendering/Entity.h>
#include <Engine/Rendering/Camera.h>

#include <Application/LSystem/PlantFactory.h>
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

private:
	std::shared_ptr<engine::Camera> m_camera;
	std::unique_ptr<engine::Entity> m_terrain;

	engine::Material m_plantMaterial;
	engine::Entity m_plantEntity;
	engine::Entity m_cubeEntity;
	PlantInstancedMeshGen m_plantInstancedMeshGen;

	int m_lastMouseX = -1;
	int m_lastMouseY = -1;

	std::unique_ptr<ILSystemGrammar> m_lSystemGrammar;
	float m_timer = 0.0f;
};
