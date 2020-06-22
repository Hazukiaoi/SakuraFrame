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

	Quaternion Rotation;

	Transform()
	{
		ObjectToWorld = glm::mat4(1.0f);

		//http://www.opengl-tutorial.org/jp/intermediate-tutorials/tutorial-17-quaternions/
		Rotation = Quaternion(Euler);

		////设置基础向量
		//ObjectToWorld[0] = Vector4(Right.x,   Right.y,   Right.z,   0.0f);
		//ObjectToWorld[1] = Vector4(Up.x,	  Up.y,	     Up.z,      0.0f);
		//ObjectToWorld[2] = Vector4(Forward.x, Forward.y, Forward.z, 0.0f);

		Right =		Rotation * Vector3(1.0f, 0.0f, 0.0f);
		Up =		Rotation * Vector3(0.0f, 1.0f, 0.0f);
		Forward =	Rotation * Vector3(0.0f, 0.0f, 1.0f);

		//用四元数角度设置基础向量
		ObjectToWorld = glm::toMat4(Rotation);

		//ObjectToWorld = glm::rotate(ObjectToWorld, Euler);
		ObjectToWorld = glm::scale(ObjectToWorld, Scale);
		ObjectToWorld = glm::translate(ObjectToWorld, Position);

		//设置逆向量
		WorldToObject = glm::inverse(ObjectToWorld);
	}

	Transform(Vector3 pos, Quaternion rotation, Vector3 scale) : Position(pos), Rotation(rotation), Scale(scale)
	{
		ObjectToWorld = glm::mat4(1.0f);

		//Rotation = Quaternion(Euler);
		//https://stackoverflow.com/questions/12048046/quaternions-euler-angles-rotation-matrix-trouble-glm
		Euler = glm::eulerAngles(Rotation) * PI / 180.0f;

		////设置基础向量
		//ObjectToWorld[0] = Vector4(Right.x,   Right.y,   Right.z,   0.0f);
		//ObjectToWorld[1] = Vector4(Up.x,	  Up.y,	     Up.z,      0.0f);
		//ObjectToWorld[2] = Vector4(Forward.x, Forward.y, Forward.z, 0.0f);

		Right = Rotation * Vector3(1.0f, 0.0f, 0.0f);
		Up = Rotation * Vector3(0.0f, 1.0f, 0.0f);
		Forward = Rotation * Vector3(0.0f, 0.0f, 1.0f);

		//用四元数角度设置基础向量
		ObjectToWorld = glm::toMat4(Rotation);

		//ObjectToWorld = glm::rotate(ObjectToWorld, Euler);
		ObjectToWorld = glm::scale(ObjectToWorld, Scale);
		ObjectToWorld = glm::translate(ObjectToWorld, Position);

		//设置逆向量
		WorldToObject = glm::inverse(ObjectToWorld);
	}

	Transform(Vector3 pos, Vector3 euler, Vector3 scale) : Position(pos), Euler(euler), Scale(scale) 
	{
		ObjectToWorld = glm::mat4(1.0f);

		Rotation = Quaternion(Euler);

		////设置基础向量
		//ObjectToWorld[0] = Vector4(Right.x,   Right.y,   Right.z,   0.0f);
		//ObjectToWorld[1] = Vector4(Up.x,	  Up.y,	     Up.z,      0.0f);
		//ObjectToWorld[2] = Vector4(Forward.x, Forward.y, Forward.z, 0.0f);

		Right = Rotation * Vector3(1.0f, 0.0f, 0.0f);
		Up = Rotation * Vector3(0.0f, 1.0f, 0.0f);
		Forward = Rotation * Vector3(0.0f, 0.0f, 1.0f);

		//用四元数角度设置基础向量
		ObjectToWorld = glm::toMat4(Rotation);

		//ObjectToWorld = glm::rotate(ObjectToWorld, Euler);
		ObjectToWorld = glm::scale(ObjectToWorld, Scale);
		ObjectToWorld = glm::translate(ObjectToWorld, Position);

		//设置逆向量
		WorldToObject = glm::inverse(ObjectToWorld);
	}
};
