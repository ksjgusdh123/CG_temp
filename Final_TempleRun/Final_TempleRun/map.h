#pragma once
#include "Header.h"
class Road {
	glm::mat4 TR{ glm::mat4(1.0f) };
	float pos[3];
	int dir;
	bool is_delete;
public:
	void select_pos(float, float);
	void transform();
	void draw(GLuint, unsigned int);
	void player_distance(float*);
	bool return_is_delete();
	float* return_pos();
	void select_dir();
	int return_dir();
};

extern std::vector<Road> roads;
