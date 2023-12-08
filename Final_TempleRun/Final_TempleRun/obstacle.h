#pragma once
#include "Header.h"
#include "Human.h"

class Obstacle {
protected:
	glm::mat4 TR{ glm::mat4(1.0f) };
	int dir = 0;
	float pos[3];
	float rad[3];
	bool is_delete = false;
	int flip;
	bool is_collide = false;

public:
	virtual void draw(GLuint vao, unsigned int modelLocation, GLuint leg_texture) = 0;
	virtual void set_pos(float, float, int) = 0;
	virtual bool return_delete() = 0;
	virtual void player_distance(float*) = 0;
	virtual void select_dir(int) = 0;
	virtual bool collision(float*, Human&) = 0;
};


class Truck : public Obstacle{
public:
	virtual void draw(GLuint vao, unsigned int modelLocation, GLuint texture) override;
	void transform();
	virtual void set_pos(float x, float z, int) override;
	virtual bool return_delete() override;
	virtual void player_distance(float*) override;
	virtual void select_dir(int) override;
	virtual bool collision(float*, Human&) override;
};

class Hurdle : public Obstacle{
	virtual void draw(GLuint vao, unsigned int modelLocation, GLuint texture) override;
	void transform();
	virtual void set_pos(float x, float z, int) override;
	virtual bool return_delete() override;
	virtual void player_distance(float*) override;
	virtual void select_dir(int) override;
	virtual bool collision(float*, Human&) override;
};

extern std::vector<Obstacle*> ob;
