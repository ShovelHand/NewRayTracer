#pragma once
#include "common.h"

/*My intention here is to have a class that encapsulates recursive ray casting to check for reflections, shadows, etc, and ultimately 
tells main what colour the pixel should be.*/

class PixelArtist
{
public:
	PixelArtist();
	~PixelArtist();

	Colour DrawGroundPixel();
	Colour DrawSpherePixel(Sphere* sphere);

};

