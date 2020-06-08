#pragma once

enum class LightType
{
	LIGHT_DIRECTTIONAL,
	LIGHT_POINT,
	LIGHT_SPOT,
};

struct Light
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