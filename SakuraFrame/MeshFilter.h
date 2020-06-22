#pragma once

#include "ECS.h"
#include "Mesh.h"

class MeshFilter : public Component
{
public:
	Mesh* mesh;

	~MeshFilter()
	{
		cout << "Mesh Filter Destroy" << endl;
	}
};
