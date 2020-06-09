#pragma once

#include "ECS.h"

enum class LightType
{
	LIGHT_DIRECTTIONAL,
	LIGHT_POINT,
	LIGHT_SPOT,
};

class Light : public Component
{

public:
	float intensity;
	LightType type;

	Light()
	{
		intensity = 1.0f;
		type = LightType::LIGHT_DIRECTTIONAL;
	}
};