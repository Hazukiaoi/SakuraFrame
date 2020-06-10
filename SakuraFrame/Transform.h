#pragma once


#include "ECS.h"
#include "Type.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform : public Component
{
public:

	Vector3 Right		= Vector3(1, 0, 0);
	Vector3 Up			= Vector3(0, 1, 0);
	Vector3 Forward		= Vector3(0, 0, 1);

	Matrix4x4 WorldToObject;
	Matrix4x4 ObjectToWorld;

	Vector3 Position	= Vector3(0, 0, 0);
	Vector3 Euler		= Vector3(0, 0, 0);
	Vector3 Scale		= Vector3(1, 1, 1);

	Transform()
	{
		ObjectToWorld = glm::mat4(1.0f);
		//���û�������
		ObjectToWorld[0] = Vector4(Right.x,   Right.y,   Right.z,   0.0f);
		ObjectToWorld[1] = Vector4(Up.x,	  Up.y,	     Up.z,      0.0f);
		ObjectToWorld[2] = Vector4(Forward.x, Forward.y, Forward.z, 0.0f);
		//ObjectToWorld = glm::rotate(ObjectToWorld, Euler);
		ObjectToWorld = glm::scale(ObjectToWorld, Scale);
		ObjectToWorld = glm::translate(ObjectToWorld, Position);

		//����������
		WorldToObject = glm::inverse(ObjectToWorld);
	}

	Transform(Vector3 pos, Vector3 euler, Vector3 scale) : Position(pos), Euler(euler), Scale(scale) 
	{
		Transform();
	}
};
