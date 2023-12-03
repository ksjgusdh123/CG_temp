#pragma once
#include "Header.h"

class Head {
	glm::mat4 TR{ glm::mat4(1.0f) };
	float move_amount_x;
	float move_amount_z;
	float rad[3];
public:
	void draw(GLuint, unsigned int);
	void transform();
	void get_move(float, float, float*);
};	

class Arm {
	glm::mat4 TR{ glm::mat4(1.0f) };
	bool is_right;
	float move_amount_x;
	float move_amount_z;
	float rad[3];
public:
	void draw(GLuint, unsigned int);
	void check_right(int i);
	void transform();
	void get_move(float, float, float*);
};

class Leg {
	glm::mat4 TR{ glm::mat4(1.0f) };
	bool is_right;
	float move_amount_x;
	float move_amount_z;
	float rad[3];
public:
	void draw(GLuint, unsigned int);
	void check_right(int i);
	void transform();
	void get_move(float, float, float*);
};

class Body {
	glm::mat4 TR{ glm::mat4(1.0f) };
	float move_amount_x;
	float move_amount_z;
	float rad[3];
public:
	void draw(GLuint, unsigned int);
	void transform();
	void get_move(float, float, float*);
};

class Human {
	Head head;
	Body body;
	Arm left_arm;
	Arm right_arm;
	Leg left_leg;
	Leg right_leg;	
	float move_amount_x;
	float move_amount_z;
	float rad[3];
public:
	Human();
	void draw(GLuint head_vao, GLuint body_vao, GLuint right_arm_vao, GLuint left_arm_vao, GLuint right_leg_vao, GLuint left_leg_vao, unsigned int modelLocation);
	void move(float amount_x, float amount_z, float* rad);
};