#pragma once

namespace engine
{
	class Scene
	{
	public:
		virtual void OnStart() = 0;
		virtual void OnUpdate(float deltaTime) = 0;
		virtual void OnUIUpdate() = 0;
	};
}



