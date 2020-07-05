#pragma once

#include "ECS.h"
#include "Type.h"


namespace Render
{
	enum class LightType
	{
		LIGHT_DIRECTTIONAL,
		LIGHT_POINT,
		LIGHT_SPOT,
	};

	class Light : public Component
	{

	public:
		float Intensity;
		float Range;
		LightType Type;
		Color LightColor;

		Light()
		{
			Intensity = 1.0f;
			Range = 10.f;
			Type = LightType::LIGHT_DIRECTTIONAL;
			LightColor = Color(1.0f, 1.0f, 1.0f, 1.0f);
		}

		Light(float intensity, float range, int type, Color color) : Intensity(intensity), Range(range), Type(LightType(type)), LightColor(color)
		{
		}

		~Light()
		{
			std::cout << "Light Destroy" << std::endl;
		}
	};
}