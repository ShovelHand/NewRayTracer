#pragma once
#include "common.h"
#include "Scene.h"

Colour red() { return Colour(0, 0, 255); }
Colour white() { return Colour(255, 255, 255); }
Colour black() { return Colour(0, 0, 0); }

//std::vector<Bounds> BoundingVolumes;

//screen size. We'll need the ratio to display things properly.
int height = 480;
int width = 600;

struct MyImage {
	/// Data (not private for convenience)
	int cols = width;
	int rows = height;
	///  Channel with [0..255] range image (aka uchar)
	cv::Mat image = cv::Mat(rows, cols, CV_8UC3, cv::Scalar(255, 255, 255));

	Colour& operator()(int row, int col)
	{
		assert(row >= 0 && row < rows);
		assert(col >= 0 && col < cols);
		return image.at<cv::Vec3b>(cv::Point(col, row));
	}

	/// Displays the image and pauses program execution (until key pressed)
	void show() {
		/// Display the image
		cv::imshow("image", image);
		cv::waitKey(0);
	}

	/// Use files with "*.png" extension
	void save(std::string filename) {
		cv::imwrite(filename, image);
	}
};

MyImage image;
Scene scene;

const vec3 eye(0.0f, 0.0f, -2.0);  //if we assume image pane has origin at 0,0,0, then eye is 10 units in front of it, and 'd' = 10
uint raysCast;
uint sphereIntersections;
uint boundingBoxHits;
std::vector<std::pair<int, int> > pixelRows;

//thread semaphore
HANDLE threadMutex;
HANDLE imageWriteMutex;

