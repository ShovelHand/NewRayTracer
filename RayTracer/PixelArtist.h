#pragma once
#include "common.h"

/*My intention here is to have a class that encapsulates recursive ray casting to check for reflections, shadows, etc, and ultimately 
tells main what colour the pixel should be.*/

class PixelArtist
{
public:
	PixelArtist();
	~PixelArtist();

	Colour DrawGroundPixel(vec3 p, vec3 rayFromeye);
	Colour DrawSpherePixel(Sphere* sphere, vec3 p, vec3 rayFromeye);
	void SetLights(vector<LightSource*> lights) { LightSources = lights; }
	void SetSpheres(vector<Sphere*> sp) { Spheres = sp; }
	void SetEye(vec3 o) { v = o; }

private:
	Colour AddLight(Colour colour, vec3 n, vec3 p, float gloss, vec3 incomingRay);
	vec3 ArtistRay(vec3 o, vec3 d); //trying to move main's CastRay to Common.h causes compiler errors. I don't get it.
	std::vector<LightSource*> LightSources;
	std::vector<Sphere*> Spheres;
	Colour DoRecursiveRays(vec3 n, vec3 p, vec3 rayFromeye, int recursionDepth);
	vec3 v;
};

