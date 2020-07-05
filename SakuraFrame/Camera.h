#pragma once
#include <glm/glm.hpp>
#include "Type.h"
#include "ECS.h"
#include "Transform.h"

namespace Render
{
	enum class CameraProjection
	{
		PRESPECTIVE,
		ORTHOGRAPHIC
	};

	class Camera : public Component
	{
	private:
		GameCore::Transform* transform;
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

		int Layer = 0;

		void SetMatrix()
		{
			WorldToViewMatrix = transform->WorldToObject;
			ViewToProjMatrix = transform->ObjectToWorld;
			ViewToProjMatrix = glm::perspective(glm::radians(FOV), Aspect, NearPlane, FarPlane);
			Inv_ViewToProjMatrix = glm::inverse(ViewToProjMatrix);
		}

		void Init()
		{
			transform = entity->GetComponent<GameCore::Transform>();
			if (transform) SetMatrix();
		}

		void Update()
		{
			if (transform) SetMatrix();
		}

		Camera()
		{
			Size = 5.0f;
			FOV = 60.0f;
			FarPlane = 1000.0f;
			NearPlane = 0.3f;
			Aspect = 1.778f;
			Layer = 0;
		}

		Camera(float size, float fov, float fPlane, float nPlane, float aspect, int layer) :
			Size(size),
			FOV(fov),
			FarPlane(fPlane),
			NearPlane(nPlane),
			Aspect(aspect),
			Layer(layer)
		{

		}

		//Camera()
		//{
		//	ViewToProjMatrix = glm::perspective(glm::radians(FOV), Aspect, NearPlane, FarPlane);
		//	Inv_ViewToProjMatrix = glm::inverse(ViewToProjMatrix);
		//}
		~Camera()
		{
			std::cout << "Camera Destroy" << std::endl;
		}
	};
}