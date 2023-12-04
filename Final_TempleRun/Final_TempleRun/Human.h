#pragma once
#include "Header.h"
#include "map.h"
class Part {
protected:
	glm::mat4 TR{ glm::mat4(1.0f) };
	float move[3];
	float rad[3];
	bool is_slide;
};

class Head : public Part {
public:
	void draw(GLuint, unsigned int);
	void transform();
	void get_move(float*, float*, bool);
};	

class Arm : public Part {
	bool is_right;
public:
	void draw(GLuint, unsigned int);
	void check_right(int i);
	void transform();
	void get_move(float*, float*, bool);
};

class Leg : public Part {
	bool is_right;
public:
	void draw(GLuint, unsigned int, GLuint);
	void check_right(int i);
	void transform();
	void get_move(float*, float*, bool);
};

class Body : public Part {
public:
	void draw(GLuint, unsigned int);
	void transform();
	void get_move(float*, float*, bool);
};

class Human {
	Head head;
	Body body;
	Arm left_arm;
	Arm right_arm;
	Leg left_leg;
	Leg right_leg;	
	int dir;
	float speed{ 0.3 };
	float rad[3];
	bool slide;
public:
	Human();
	void draw(GLuint head_vao, GLuint body_vao, GLuint right_arm_vao, GLuint left_arm_vao, GLuint right_leg_vao, GLuint left_leg_vao, unsigned int modelLocation, GLuint leg_texture);
	void move(float* move_amount, float* rad, bool slide);
	void turn(int i);
	int return_dir();
	float get_speed();
	void road_check(float* move_amount);
};