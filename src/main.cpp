#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct Point
{
	float x, y;
	int index;
	std::string dir;
};

std::vector<Point> VisiblePoints(const std::vector<Point>& points, int index,
	float max_angle, float max_dis)
{	
	const float max_cos = cos((max_angle/2) * (M_PI/180));

	const std::string dir  = points[index - 1].dir;
	std::vector<Point> result;

	for (const Point& point : points)
	{
		if (point.index == index) continue;
		
		float dir_vec[2];
		dir_vec[0] = point.x - points[index - 1].x;
		dir_vec[1] = point.y - points[index - 1].y;

		//normalise direction vector
		float norm = sqrt(dir_vec[0]*dir_vec[0] + dir_vec[1]*dir_vec[1]);
		float norm_dir_vec[2];
		norm_dir_vec[0] = dir_vec[0]/norm;
		norm_dir_vec[1] = dir_vec[1]/norm;

		float dot;
		
		//dot product normalised direction vector with cartesian unit vector
		if (dir == "North") dot = norm_dir_vec[1];
		else if (dir == "South") dot = -norm_dir_vec[1];
		else if (dir == "East") dot = norm_dir_vec[0];
		else if (dir == "West") dot = -norm_dir_vec[0];

		if ((dot >= max_cos) && (norm <= max_dis))
		{
			result.push_back(point);
		}
	}
	return result;
}

int main()
{
	std::ifstream file("points.txt"); //read data from file
	std::vector<Point> points;

	while (!file.eof()) //add data to array
	{
		Point temp_point;
		file >> temp_point.x >> temp_point.y >> temp_point.index >> temp_point.dir;
		points.push_back(temp_point);
	}

	//tests
	std::vector<Point> test1 = VisiblePoints(points, 1, 45, 20);
	std::cout << "test1(1, 45, 20): ";
	for (const Point& point : test1) {
		std::cout << "(" << point.x << "," << point.y << "," <<
			point.index << "," << point.dir << ") ";
	}
	std::cout << std::endl << std::endl;

	std::vector<Point> test2 = VisiblePoints(points, 4, 30, 60);
	std::cout << "test2(4, 30, 40): ";
	for (const Point& point : test2) {
		std::cout << "(" << point.x << "," << point.y << "," <<
			point.index << "," << point.dir << ") ";
	}
	std::cout << std::endl << std::endl;
}