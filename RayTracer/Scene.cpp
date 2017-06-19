#include "Scene.h"

Scene::Scene()
{

}


Scene::~Scene()
{
	while (!Spheres.empty())
	{
		delete Spheres.back();
		Spheres.pop_back();
	}

	while (!LightSources.empty())
	{
		delete LightSources.back();
		LightSources.pop_back();
	}
}

void Scene::BuildScene()
{
	Sphere* sphere1 = new Sphere(vec3(0.45f, 0.0f, 1.0f), 0.25f, Colour(255, 0, 0), 50);
	Spheres.push_back(sphere1);

	Sphere* sphere4 = new Sphere(vec3(0.25f, -0.25f, 0.70f), 0.1f, Colour(150, 0, 150), 10000);
	Spheres.push_back(sphere4);
	Sphere* sphere5 = new Sphere(vec3(-0.5f, -1.0f, 0.5f), 0.4f, Colour(150, 155, 150), 100);
	Spheres.push_back(sphere5);
	
	LightSource* light1 = new LightSource(vec3(1.9f, -0.1f, 0.5f), Colour(150, 150, 150), 5);
	LightSources.push_back(light1);
	/*LightSource* light2 = new LightSource(vec3(-1.0f, 0.0f, -0.5f), Colour(150, 150, 150), 5);
	LightSources.push_back(light2);
	LightSource* light3 = new LightSource(vec3(0.99f, 0.7f, 5.0f), Colour(255, 15, 15), 3.0f);
	LightSources.push_back(light3);*/
	
	//give the PixelArtist pointers to our spheres and lights
	artist.SetLights(LightSources);
	artist.SetSpheres(Spheres);
}
