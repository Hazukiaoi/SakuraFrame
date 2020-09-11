#pragma once

#include "ECS.h"
#include "Mesh.h"

namespace Render
{
	class MeshFilter : public Component
	{
	public:
		DEF_COMPONENT(MESH_FILTER)

		Mesh* mesh;

		~MeshFilter()
		{
			cout << "Mesh Filter Destroy" << endl;
		}
	};
}