#pragma once

#include "ECS.h"
#include "Mesh.h"
#include "Material.h"

namespace Render
{
	class MeshRenderer : public Component
	{
	public:
		Material* material;
		static std::string ComponentName() { return "MESH_RENDERER"; };

		~MeshRenderer()
		{
			cout << "Mesh Renderer Destroy" << endl;
		}
	};
}