#include "DiscreteParaCurve.h"



DiscreteParaCurve::DiscreteParaCurve(glm::dvec3 func(double), double coord_min, double coord_max, double delta)
{
	this->coord_min = coord_min;
	this->coord_max = coord_max;
	this->delta = delta;

	//unsigned int num_of_points = (coord_max - coord_min) / delta;
	for (double u = coord_min; u < coord_max - delta * 0.1 ; u += delta)
	{
		coordinates.push_back(u);
		points.push_back(func(u));
	}
}

DiscreteParaCurve::DiscreteParaCurve(std::vector<double> coordinates, std::vector<glm::dvec3> points):coordinates(coordinates), points(points)
{
	delta = 0.1f;
}


DiscreteParaCurve::~DiscreteParaCurve()
{
}

double DiscreteParaCurve::getCoordinate(int index)
{
	return coordinates[index];
}

glm::dvec3 DiscreteParaCurve::getPoint(int index)
{
	return points[index];
}

std::vector<glm::dvec3> DiscreteParaCurve::getPoints()
{
	return points;
}
