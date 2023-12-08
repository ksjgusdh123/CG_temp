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
	void draw(GLuint, unsigned int, bool);
	void transform(bool);
	void get_move(float*, float*, bool);
};	

class Arm : public Part {
	bool is_right;
public:
	void draw(GLuint, unsigned int, bool);
	void check_right(int i);
	void transform(bool);
	void get_move(float*, float*, bool);
};

class Leg : public Part {
	bool is_right;
public:
	void draw(GLuint, unsigned int, GLuint, bool);
	void check_right(int i);
	void transform(bool);
	void get_move(float*, float*, bool);
};

class Body : public Part {
public:
	void draw(GLuint, unsigned int, bool);
	void transform(bool);
	void get_move(float*, float*, bool);
};


class Human {
	Head head;
	Body body;
	Arm left_arm;
	Arm right_arm;
	Leg left_leg;
	Leg right_leg;	
	Road last;
	int dir;
	float speed{ 0.15 };
	float rad[3];
	bool slide;
	bool jump;
	bool cross = false;
	float light = 100;
public:
	Human();
	void draw(GLuint head_vao, GLuint body_vao, GLuint right_arm_vao, GLuint left_arm_vao, GLuint right_leg_vao, GLuint left_leg_vao, unsigned int modelLocation, 
		GLuint head_texture, GLuint body_texture, GLuint right_arm_texture, GLuint left_arm_texture, GLuint right_leg_texture, GLuint left_leg_texture);
	void move(float* move_amount, float* rad, bool slide);
	void turn(int i);
	int return_dir();
	float get_speed();
	bool road_check(float* move_amount);
	bool return_slide();
	bool return_jump();
	void set_jump(bool a);
	void set_speed(float a);	
	void set_light(float num);
	float return_light();
	void set_road(Road&);
	void position_setting(float*);
	Road& return_last();
	float return_speed();
	void recover_speed(float);
};

class Police {
	Head head;
	Body body;
	Arm left_arm;
	Arm right_arm;
	Leg left_leg;
	Leg right_leg;
	float speed{ 0.15 };
	int now_dir;
	int next_dir;
	float pos[3];
	float rad[3]{ 0, 540, 0 };
	float turn_point[3];
	bool is_police = true;
	bool flip = false;
public:
	Police();
	void draw(GLuint head_vao, GLuint body_vao, GLuint right_arm_vao, GLuint left_arm_vao, GLuint right_leg_vao, GLuint left_leg_vao, unsigned int modelLocation,
		GLuint head_texture, GLuint body_texture, GLuint right_arm_texture, GLuint left_arm_texture, GLuint right_leg_texture, GLuint left_leg_texture);
	void move(Human& player);
	float get_speed();
	void get_rad(float* rad);
	void set_turn_point(Human& player);
	void set_speed(float a);
};
