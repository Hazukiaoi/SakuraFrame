#pragma once


#include "Ecs.h"
#include "Type.h"

class Transform : public Component
{
public:

	Vector3 Position =	Vector3(0, 0, 0);
	Vector3 Euler =		Vector3(0, 0, 0);
	Vector3 Scale =		Vector3(1, 1, 1);
	Transform(){}
	Transform(Vector3 pos, Vector3 euler, Vector3 scale) : Position(pos), Euler(euler), Scale(scale) {}
};
