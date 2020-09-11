#pragma once

#include "ECS.h"
#include "Mesh.h"

namespace Render
{
	class MeshFilter : public Component
	{
	public:
		Mesh* mesh;
		static std::string ComponentName() { return "MESH_FILTER"; };

		~MeshFilter()
		{
			cout << "Mesh Filter Destroy" << endl;
		}
	};
}