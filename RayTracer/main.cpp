#pragma once
#include "main.h"
#include <time.h>

/*The scene is now contained (and arranged) within its own class. This was done to help me 
build relationships between main, the scene, and the pixel artist.*/
void BuildScene() 
{
	scene.BuildScene();
}

/*cast a ray*/
vec3 castRay(vec3 o, vec3 d)
{
	vec3 ray(d.x() - o.x(), d.y() - o.y(), d.z() - o.z());
	ray.normalize();
	return ray;
}

/*Ray tracing happens here*/
void ScanImage()
{
	cout << "Ray tracing scene. This may take a while..." << endl;
	clock_t timeStart = clock();
	vec3 eye(0.0f, 0.0f, -2.0);  //if we assume image pane has origin at 0,0,0, then eye is 10 units in front of it, and 'd' = 10
	float dist = eye.z();

	//finding pixel coords
	float left, right, top, bottom;
	left = -(float(image.cols) / float(image.rows));
	bottom = -1;
	top = 1;
	right = (float(image.cols) / float(image.rows));

	for (int row = 0; row < image.rows; ++row) {
		for (int col = 0; col < image.cols; ++col) {
			//construct ray
			float u = (left + (right - left)*(col + 0.5f) / image.cols);
			float v = (bottom + (top - bottom)*(row + 0.5f) / image.rows);

			vec3 d(u, v, 0);
			vec3 r = castRay(eye, d);
			raysCast += 1;
			float tmin = 1000;//arbitrarily large instantiation for infinity.
			float t;
			bool intersection = false;
			
			/******GROUND DRAWING*********/
			//check for ground plane intersection
			vec3 p0(0, 1, 2);
			vec3 n(0, 1, 0); //normal vector to plane on the x-z plane
			Colour groundColour(50, 50, 50);

			if (r.dot(n) != 0 && row >= image.rows / 2) //the inequality is here until I can figure out why the plane appears in the sky.
			{

				t = ((p0 - eye).dot(n)) / r.dot(n);

				tmin = t;

				intersection = true;
				Colour colour(100, 100, 100);  //only one ground, so its colour is declared here
				vec3 p(eye.x() + t*r.x(), eye.y() + t*r.y(), eye.z() + t*r.z()); //point of intersection
				//TODO: lighting calculations go here.

				image(row, col) = colour;
			}
			/******END OF GROUND DRAWING******/

			//draw spheres
			vector<Sphere*> spheres = scene.GetSpheres();
				for (std::vector<Sphere*>::iterator itr = spheres.begin(); itr != spheres.end(); ++itr)
				{
					if ((*itr)->CheckBoundsIntersection(eye, r, -10.0f, 10.0f))
					{
						boundingBoxHits += 1;
						float b = (r.dot(eye - (*itr)->GetPos()));
						float c = (eye - (*itr)->GetPos()).dot(eye - (*itr)->GetPos()) - pow((*itr)->GetRad(), 2);
						float discriminant = sqrt(pow(b, 2) - c);
						if (discriminant >= 0) //don't waste computation time if no intersection
						{
							t = fmin(((-1)*b - discriminant), ((-1)*b + discriminant));
							intersection = true;
							sphereIntersections += 1;
							if (t < tmin)
							{
								vec3 p(eye.x() + t*r.x(), eye.y() + t*r.y(), eye.z() + t*r.z());
								tmin = t;
								image(row, col) = scene.artist.DrawSpherePixel(*itr);
							}
						}
					}

				}
			
			//just draw black if ray hit nothing
			if (!intersection)
			{
				image(row, col) = Colour(0, 0, 0);
			}

		}
	}//end of scan loop

	clock_t timeEnd = clock();
	cout << "Render time: " << float(timeEnd - timeStart)/1000.0f << " seconds" << endl;
	cout << "Rays cast: " << raysCast << endl;
	cout << "Rays that hit spheres: " << sphereIntersections << endl;
	cout << "Bounding box hits: " << boundingBoxHits << endl;
}

int main()
{
	raysCast = sphereIntersections = boundingBoxHits = 0;
	BuildScene();
	ScanImage();
	image.show();
	// image.save("output.png"); ///< Does not work on Windows!
 
	return EXIT_SUCCESS;
}
