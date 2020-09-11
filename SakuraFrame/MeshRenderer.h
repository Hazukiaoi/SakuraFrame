#pragma once

#include "ECS.h"
#include "Mesh.h"
#include "Material.h"

namespace Render
{
	class MeshRenderer : public Component
	{
	public:
		DEF_COMPONENT(MESH_RENDERER)

		Material* material;

		~MeshRenderer()
		{
			cout << "Mesh Renderer Destroy" << endl;
		}
	};
}