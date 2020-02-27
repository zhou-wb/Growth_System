#include "CoordinateSystem.h"

void CoordinateSystem::set_local_basis(glm::dvec3 d1, glm::dvec3 d2, glm::dvec3 d3)
{
	local_basis.d1 = d1;
	local_basis.d2 = d2;
	local_basis.d3 = d3;

}

void CoordinateSystem::set_local_coordinates(double q1, double q2, double q3)
{
	local_coordinates.q1 = q1;
	local_coordinates.q2 = q2;
	local_coordinates.q3 = q3;
}

glm::dvec3 CoordinateSystem::get_global_coordinates()
{
	return local_basis.d1*local_coordinates.q1 + local_basis.d2*local_coordinates.q2 + local_basis.d3*local_coordinates.q3;
}