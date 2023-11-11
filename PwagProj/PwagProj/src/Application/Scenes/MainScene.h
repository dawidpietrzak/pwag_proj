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

private:
	std::shared_ptr<engine::Camera> m_camera;
	std::unique_ptr<engine::Entity> m_terrain;
	std::unique_ptr<engine::Entity> m_cylinder;

	engine::Material m_defaultMaterial;
	engine::Entity m_plantEntity;
	PlantInstancedMeshGen m_plantInstancedMeshGen;

	std::unique_ptr<ILSystemGrammar> m_lSystemGrammar;
};
