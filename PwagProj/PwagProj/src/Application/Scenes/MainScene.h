#pragma once

#include <Engine/Scenes/Scene.h>
#include <Engine/Rendering/Mesh.h>
#include <Engine/Rendering/Material.h>
#include <Engine/Rendering/Camera.h>

#include <memory>

class MainScene : public engine::Scene
{
public:
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;

private:
	engine::Material m_material;
	engine::Mesh m_testMesh;
	std::shared_ptr<engine::Camera> m_camera;
};

