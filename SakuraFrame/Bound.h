#pragma once

#include "MathLib.h"

namespace Render
{
	struct Bound
	{
	public:
		Vector3 center;
		Vector3 size;
		Vector3 min, max;
	};
}
