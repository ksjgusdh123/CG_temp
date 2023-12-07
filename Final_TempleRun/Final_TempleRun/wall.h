#pragma once
#include "Header.h"

class Apart {
	glm::mat4 TR{ glm::mat4(1.0f) };
	float pos[3];
	int dir = 0;
	bool is_delete = false;
	bool is_right;
public:
	void select_pos(float, float, int);
	void transform();
	void draw(GLuint, unsigned int);
	void player_distance(float*);
	bool return_delete();
	float* return_pos();
	void select_dir(int map_dir);
	int return_dir();
};

extern std::vector<Apart*> building;