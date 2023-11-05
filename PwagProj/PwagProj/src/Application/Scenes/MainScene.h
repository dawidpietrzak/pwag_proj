#pragma once

#include <Engine/Scenes/Scene.h>
#include <Engine/Rendering/Entity.h>
#include <Engine/Rendering/Camera.h>

#include <Application/Tools/CylinderGenerator.h>

#include <memory>

class MainScene : public engine::Scene
{
public:
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnUIUpdate() override;

private:
	std::shared_ptr<engine::Camera> m_camera;
	std::unique_ptr<engine::Entity> m_terrain;
	std::unique_ptr<engine::Entity> m_cylinder;

	CylinderGenerator m_cylinderGen;
	float m_topScale = 1.0f, m_bottomScale = 1.0f;
};

