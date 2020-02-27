#pragma once

#include <vector>
#include "glm/glm.hpp"

struct orthogonal_basis
{
	glm::dvec3 d1;
	glm::dvec3 d2;
	glm::dvec3 d3;
};

struct three_coordinates
{
	double q1;
	double q2;
	double q3;
};

class CoordinateSystem
{
public:
	void set_local_basis(glm::dvec3 d1, glm::dvec3 d2, glm::dvec3 d3);
	void set_local_coordinates(double q1, double q2, double q3);
	glm::dvec3 get_global_coordinates();

private:
	orthogonal_basis local_basis;
	three_coordinates local_coordinates;
};

