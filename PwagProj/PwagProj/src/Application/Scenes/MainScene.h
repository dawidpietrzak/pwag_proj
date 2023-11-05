#pragma once

#include <Engine/Scenes/Scene.h>
#include <Engine/Rendering/Mesh.h>
#include <Engine/Rendering/Material.h>
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
	engine::Material m_terrainMaterial;
	engine::Material m_defaultMaterial;

	engine::Mesh m_testMesh;
	engine::Mesh m_cylinderMesh;
	std::shared_ptr<engine::Camera> m_camera;

	CylinderGenerator m_cylinderGen;
	float m_topScale = 1.0f, m_bottomScale = 1.0f;
};

