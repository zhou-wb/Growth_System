#include "DiscreteParaCurve.h"



DiscreteParaCurve::DiscreteParaCurve(glm::vec3 func(float), float coord_min, float coord_max, float delta)
{
	this->coord_min = coord_min;
	this->coord_max = coord_max;
	this->delta = delta;

	//unsigned int num_of_points = (coord_max - coord_min) / delta;
	for (float u = coord_min; u < coord_max; u += delta)
	{
		coordinates.push_back(u);
		points.push_back(func(u));
	}
}

DiscreteParaCurve::DiscreteParaCurve(std::vector<float> coordinates, std::vector<glm::vec3> points):coordinates(coordinates), points(points)
{
	delta = 0.1f;
}


DiscreteParaCurve::~DiscreteParaCurve()
{
}

float DiscreteParaCurve::getCoordinate(int index)
{
	return coordinates[index];
}

glm::vec3 DiscreteParaCurve::getPoint(int index)
{
	return points[index];
}

std::vector<glm::vec3> DiscreteParaCurve::getPoints()
{
	return points;
}
