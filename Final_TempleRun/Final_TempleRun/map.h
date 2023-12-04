#pragma once
#include "Header.h"

class Road {
	glm::mat4 TR{ glm::mat4(1.0f) };
	float pos[3];
public:
	void select_pos(int n);
	void transform();
	void draw(GLuint, unsigned int);
};