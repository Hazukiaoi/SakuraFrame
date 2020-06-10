#pragma once
#include <glm/glm.hpp>
#include "Type.h"
#include "ECS.h"
#include "Transform.h"

class Camera : public Component
{
private:
	Transform *transform;
public:
	Matrix4x4 WorldToViewMatrix;
	Matrix4x4 ViewToProjMatrix;

	Matrix4x4 Inv_WorldToViewMatrix;
	Matrix4x4 Inv_ViewToProjMatrix;

	void Init()
	{
		transform = entity->GetComponent<Transform>();
	}

	Camera()
	{

	}
};