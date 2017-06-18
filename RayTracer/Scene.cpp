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
}

void Scene::BuildScene()
{
	Sphere* sphere1 = new Sphere(vec3(0.85f, 0.0f, 1.0f), 0.25f, Colour(255, 0, 0), 50);
	Spheres.push_back(sphere1);

	//Sphere sphere4(vec3(-0.4f, -0.75f, 0.5f), 0.04f, Colour(150, 0, 150), 10000);
	//Spheres.push_back(sphere4);
	Sphere* sphere5 = new Sphere(vec3(-0.5f, -1.0f, 0.5f), 0.4f, Colour(150, 155, 150), 10000);
	Spheres.push_back(sphere5);

	LightSource light1(vec3(-0.5f, -1.7f, 1.75f), Colour(150, 150, 150), 10);
	LightSources.push_back(&light1);
}
