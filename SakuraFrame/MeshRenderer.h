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

		~MeshRenderer()
		{
			cout << "Mesh Renderer Destroy" << endl;
		}
	};
}