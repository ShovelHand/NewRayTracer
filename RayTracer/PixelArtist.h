#pragma once
#include "common.h"

/*My intention here is to have a class that encapsulates recursive ray casting to check for reflections, shadows, etc, and ultimately 
tells main what colour the pixel should be.*/

class PixelArtist
{
public:
	PixelArtist();
	~PixelArtist();

	Colour DrawGroundPixel(vec3 p);
	Colour DrawSpherePixel(Sphere* sphere, vec3 p);
	void SetLights(vector<LightSource*> lights) { LightSources = lights; }
	void SetSpheres(vector<Sphere*> sp) { Spheres = sp; }
	void SetEye(vec3 o) { v = o; }

private:
	Colour AddLight(Colour colour, vec3 n, vec3 p, float gloss);
	std::vector<LightSource*> LightSources;
	std::vector<Sphere*> Spheres;
	vec3 v;

};

