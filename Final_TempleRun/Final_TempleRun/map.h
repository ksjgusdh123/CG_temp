#pragma once
#include "Header.h"
class Road {
	glm::mat4 TR{ glm::mat4(1.0f) };
	float pos[3];
	int dir = 0;
	bool is_delete;
	int cross = 100;
public:
	void select_pos(float, float);
	void transform();
	void draw(GLuint, unsigned int);
	void player_distance(float*, int*);
	bool return_is_delete();
	float* return_pos();
	void select_dir(int map_dir);
	int return_dir();
	int return_cross();
	void set_cross(int);
};

extern std::vector<Road> roads;
