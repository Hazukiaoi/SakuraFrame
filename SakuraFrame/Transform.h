#pragma once


#include "Ecs.h"
#include "Type.h"

class Transform : public Component
{
public:
	Vector3 position =	Vector3(0, 0, 0);
	Vector3 euler =		Vector3(0, 0, 0);
	Vector3 Scale =		Vector3(1, 1, 1);
};
