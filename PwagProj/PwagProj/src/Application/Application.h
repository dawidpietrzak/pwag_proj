#pragma once

#include <Engine/AppBase.h>

class Application : public engine::AppBase
{
public:
	static void Create() { if (!s_app) s_app = new Application(); }
	static void Destroy() { delete s_app; s_app = nullptr; }
	static Application* Get() { return s_app; }

	virtual void OnInitialize() override;
	virtual void OnStart() override;

private:
	static Application* s_app;

	std::shared_ptr<engine::AssetManager> m_assetManager;

private:
	void LoadResources();

};

