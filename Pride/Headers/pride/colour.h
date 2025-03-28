#pragma once

#include <SDL3/SDL.h>

namespace Pride
{
	/// <summary>
	/// Represents a RGBA colour struct.
	/// </summary>
	struct Colour
	{
		Uint8 r, g, b, a;

		Colour(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255) 
			: r(red), g(green), b(blue), a(alpha) {}
	};
}