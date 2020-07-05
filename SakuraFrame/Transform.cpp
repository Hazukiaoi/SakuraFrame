#include "Transform.h"


GameCore::Transform::Transform()
{

	ObjectToWorld = glm::mat4(1.0f);

	//http://www.opengl-tutorial.org/jp/intermediate-tutorials/tutorial-17-quaternions/
	Rotation = Quaternion(Euler);

	////���û�������
	//ObjectToWorld[0] = Vector4(Right.x,   Right.y,   Right.z,   0.0f);
	//ObjectToWorld[1] = Vector4(Up.x,	  Up.y,	     Up.z,      0.0f);
	//ObjectToWorld[2] = Vector4(Forward.x, Forward.y, Forward.z, 0.0f);

	Right = Rotation * Vector3(1.0f, 0.0f, 0.0f);
	Up = Rotation * Vector3(0.0f, 1.0f, 0.0f);
	Forward = Rotation * Vector3(0.0f, 0.0f, 1.0f);

	//����Ԫ���Ƕ����û�������
	ObjectToWorld = glm::toMat4(Rotation);

	//ObjectToWorld = glm::rotate(ObjectToWorld, Euler);
	ObjectToWorld = glm::scale(ObjectToWorld, Scale);
	ObjectToWorld = glm::translate(ObjectToWorld, Position);

	//����������
	WorldToObject = glm::inverse(ObjectToWorld);
}

GameCore::Transform::Transform(Vector3 pos, Quaternion rotation, Vector3 scale) : Position(pos), Rotation(rotation), Scale(scale)
{
	ObjectToWorld = glm::mat4(1.0f);

	//Rotation = Quaternion(Euler);
	//https://stackoverflow.com/questions/12048046/quaternions-euler-angles-rotation-matrix-trouble-glm
	Euler = glm::eulerAngles(Rotation) * PI / 180.0f;

	////���û�������
	//ObjectToWorld[0] = Vector4(Right.x,   Right.y,   Right.z,   0.0f);
	//ObjectToWorld[1] = Vector4(Up.x,	  Up.y,	     Up.z,      0.0f);
	//ObjectToWorld[2] = Vector4(Forward.x, Forward.y, Forward.z, 0.0f);

	Right = Rotation * Vector3(1.0f, 0.0f, 0.0f);
	Up = Rotation * Vector3(0.0f, 1.0f, 0.0f);
	Forward = Rotation * Vector3(0.0f, 0.0f, 1.0f);

	//����Ԫ���Ƕ����û�������
	ObjectToWorld = glm::toMat4(Rotation);

	//ObjectToWorld = glm::rotate(ObjectToWorld, Euler);
	ObjectToWorld = glm::scale(ObjectToWorld, Scale);
	ObjectToWorld = glm::translate(ObjectToWorld, Position);

	//����������
	WorldToObject = glm::inverse(ObjectToWorld);
}

GameCore::Transform::Transform(Vector3 pos, Vector3 euler, Vector3 scale) : Position(pos), Euler(euler), Scale(scale)
{
	ObjectToWorld = glm::mat4(1.0f);

	Rotation = Quaternion(Euler);

	////���û�������
	//ObjectToWorld[0] = Vector4(Right.x,   Right.y,   Right.z,   0.0f);
	//ObjectToWorld[1] = Vector4(Up.x,	  Up.y,	     Up.z,      0.0f);
	//ObjectToWorld[2] = Vector4(Forward.x, Forward.y, Forward.z, 0.0f);

	Right = Rotation * Vector3(1.0f, 0.0f, 0.0f);
	Up = Rotation * Vector3(0.0f, 1.0f, 0.0f);
	Forward = Rotation * Vector3(0.0f, 0.0f, 1.0f);

	//����Ԫ���Ƕ����û�������
	ObjectToWorld = glm::toMat4(Rotation);

	//ObjectToWorld = glm::rotate(ObjectToWorld, Euler);
	ObjectToWorld = glm::scale(ObjectToWorld, Scale);
	ObjectToWorld = glm::translate(ObjectToWorld, Position);

	//����������
	WorldToObject = glm::inverse(ObjectToWorld);
}