#pragma once
#include "common.h"
#include "PixelArtist.h"

class Scene
{
public:
	Scene();
	~Scene();

public:
	void BuildScene();
	std::vector<Sphere*> GetSpheres() { return Spheres; }
	std::vector<LightSource*> GetLights() { return LightSources; }
	PixelArtist artist;

private:
	std::vector<Sphere*> Spheres;
	std::vector<LightSource*> LightSources;
};

