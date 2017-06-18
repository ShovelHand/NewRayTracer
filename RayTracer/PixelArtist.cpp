#include "PixelArtist.h"



PixelArtist::PixelArtist()
{
}


PixelArtist::~PixelArtist()
{
}

Colour PixelArtist::DrawGroundPixel()
{
	return Colour(100, 100, 100);
}

Colour PixelArtist::DrawSpherePixel(Sphere* sphere)
{
	return (sphere)->GetColour();
}