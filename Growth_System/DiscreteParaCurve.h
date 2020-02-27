#pragma once
#define _USE_MATH_DEFINES

#include <vector>
#include"glm/glm.hpp"


class DiscreteParaCurve
{
public:
	DiscreteParaCurve(glm::dvec3 func(double), double coord_min, double coord_max, double delta = 0.01 * M_PI);
	DiscreteParaCurve(std::vector<double> coordinates, std::vector<glm::dvec3> points);
	~DiscreteParaCurve();

	//glm::dvec3 getPoint(double u);
	double getCoordinate(int index);
	glm::dvec3 getPoint(int index);
	std::vector<glm::dvec3> getPoints();

private:
	std::vector<double> coordinates;
	std::vector<glm::dvec3> points;
	double coord_min;
	double coord_max;
	double delta;
};

