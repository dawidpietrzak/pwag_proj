#include "Application.h"

#include <Application/Scenes/MainScene.h>

Application* Application::s_app = nullptr;

void Application::OnInitialize()
{
	engine::AppSpec appSpec = {};
	appSpec.WindowWidth = 1600;
	appSpec.WindowHeight = 900;
	appSpec.WindowTitle = "LSystem Presentation App";
	Initialize(appSpec);
}

void Application::OnStart()
{
	m_assetManager = GetAssetManager();
	LoadResources();
}

void Application::LoadResources()
{
	engine::Texture terrainTexture = m_assetManager->LoadTextureFromFile("assets/ground.png", "ground");
	engine::Texture blobTexture = m_assetManager->LoadTextureFromFile("assets/blob.png", "blob");
    engine::Texture logTexture = m_assetManager->LoadTextureFromFile("assets/log.png", "log");

    std::vector<std::string> skyboxFilenames = { "assets/posx.jpg", "assets/negx.jpg", "assets/posy.jpg", "assets/negy.jpg", "assets/posz.jpg", "assets/negz.jpg" };
    engine::Texture skyboxTexture = m_assetManager->LoadCubeMapFromFiles(skyboxFilenames, "skybox");

	engine::Material& terrainMaterial = m_assetManager->CreateMaterial("default", "terrain_mat");
	terrainMaterial.SetTexture(terrainTexture);

	engine::Material& defaultMaterial = m_assetManager->CreateMaterial("default", "default_mat");
	defaultMaterial.SetTexture(blobTexture);

	engine::Material& plantMaterial = m_assetManager->CreateMaterial("plant", "plant_mat");
	plantMaterial.SetTexture(logTexture);

    engine::Material& skyboxMaterial = m_assetManager->CreateMaterial("skybox", "skybox_mat");
    skyboxMaterial.SetTexture(skyboxTexture);

	m_assetManager->LoadMeshFromFile("assets/terrain.obj", "terrain");
	m_assetManager->LoadMeshFromFile("assets/cube.obj", "cube");

	CreateSkyboxMesh();

	AddScene("main_scene", new MainScene());
	SetCurrentScene("main_scene");
}

void Application::CreateSkyboxMesh()
{
    std::vector<GLfloat> vertices = {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    engine::VertexAttrib vertexAttrib;
    vertexAttrib.Create({
        { 0, 3 }	// Position 3d
    });

    engine::VertexBuffer vertexBuffer;
    vertexBuffer.Create(vertices, vertexAttrib);

    engine::Mesh mesh;
    mesh.Create(vertexBuffer);

    m_assetManager->LoadMesh(mesh, "skybox");
}