#pragma once
#include "Header.h"
class Road {
	glm::mat4 TR{ glm::mat4(1.0f) };
	float pos[3];
	bool is_delete;
public:
	void select_pos(int n);
	void transform();
	void draw(GLuint, unsigned int);
	void player_distance(float*);
	bool return_is_delete();
	float* return_pos();
};

extern std::vector<Road> roads;
