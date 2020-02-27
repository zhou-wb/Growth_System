#pragma once

#include <vector>
#include"glm/glm.hpp"

class DiscreteParaCurve
{
public:
	DiscreteParaCurve(glm::vec3 func(float), float coord_min, float coord_max, float delta = 0.01f);
	DiscreteParaCurve(std::vector<float> coordinates, std::vector<glm::vec3> points);
	~DiscreteParaCurve();

	//glm::vec3 getPoint(float u);
	float getCoordinate(int index);
	glm::vec3 getPoint(int index);
	std::vector<glm::vec3> getPoints();

private:
	std::vector<float> coordinates;
	std::vector<glm::vec3> points;
	float coord_min;
	float coord_max;
	float delta;
};

