#pragma once


#include "ECS.h"
#include "Type.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



namespace GameCore {

	class Transform : public Component
	{
	public:
		DEF_COMPONENT(TRANSFORM)

		Vector3 Right = Vector3(1, 0, 0);
		Vector3 Up = Vector3(0, 1, 0);
		Vector3 Forward = Vector3(0, 0, 1);

		Matrix4x4 WorldToObject;
		Matrix4x4 ObjectToWorld;


		Vector3 Position = Vector3(0, 0, 0);
		Vector3 Euler = Vector3(0, 0, 0);
		Vector3 Scale = Vector3(1, 1, 1);

		Quaternion Rotation;

		Transform* parent = nullptr;

		Transform();
		Transform(Vector3 pos, Quaternion rotation, Vector3 scale);
		Transform(Vector3 pos, Vector3 euler, Vector3 scale);

	};
}