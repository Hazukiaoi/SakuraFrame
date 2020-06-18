#pragma once
#include <glm/glm.hpp>
#include "Type.h"
#include "ECS.h"
#include "Transform.h"

enum class CameraProjection
{
	PRESPECTIVE,
	ORTHOGRAPHIC
};

class Camera : public Component
{
private:
	Transform *transform;
public:
	Matrix4x4 WorldToViewMatrix;
	Matrix4x4 ViewToProjMatrix;

	Matrix4x4 Inv_WorldToViewMatrix;
	Matrix4x4 Inv_ViewToProjMatrix;

	CameraProjection ProjectionType = CameraProjection::PRESPECTIVE;

	//if ProjectionType = ORTHOGRAPHIC;
	float Size = 5.0f;
	//if ProjectionType = PRESPECTIVE;
	float FOV = 60.0f;

	float FarPlane = 1000.0f;
	float NearPlane = 0.3f;

	float Aspect = 1.778f;

	int layer = 0;

	void SetMatrix()
	{
		WorldToViewMatrix = transform->WorldToObject;
		ViewToProjMatrix = transform->ObjectToWorld;
		ViewToProjMatrix = glm::perspective(glm::radians(FOV), Aspect, NearPlane, FarPlane);
		Inv_ViewToProjMatrix = glm::inverse(ViewToProjMatrix);
	}

	void Init()
	{
		transform = entity->GetComponent<Transform>();
		if (transform) SetMatrix();
	}

	void Update()
	{
		if (transform) SetMatrix();
	}

	//Camera()
	//{
	//	ViewToProjMatrix = glm::perspective(glm::radians(FOV), Aspect, NearPlane, FarPlane);
	//	Inv_ViewToProjMatrix = glm::inverse(ViewToProjMatrix);
	//}
};