#define _CRT_SECURE_NO_WARNINGS
#include "map.h"

std::vector<Road> roads;

void Road::select_pos(float x, float z) {
	pos[0] = x;
	pos[1] = -1.7;
	pos[2] = z;
}

void Road::transform() {
	TR = glm::mat4(1.0f);
	TR = glm::translate(TR, glm::vec3(pos[0], pos[1], pos[2]));
	if (cross != 100) {
		if (dir == 0) {
			if(cross == 1)
				TR = glm::rotate(TR, glm::radians(90.f), glm::vec3(0, 1, 0));
			else if(cross == 3)
				TR = glm::rotate(TR, glm::radians(0.f), glm::vec3(0, 1, 0));
		}
		else if (dir == 1) {
			if (cross == 0) {
				TR = glm::rotate(TR, glm::radians(-90.f), glm::vec3(0, 1, 0));
			}
			if (cross == 2) {
				TR = glm::rotate(TR, glm::radians(0.f), glm::vec3(0, 1, 0));
			}
		}
		else if (dir == 2) {
			if (cross == 1)
				TR = glm::rotate(TR, glm::radians(180.f), glm::vec3(0, 1, 0));
			else if (cross == 3)
				TR = glm::rotate(TR, glm::radians(-90.f), glm::vec3(0, 1, 0));
		}
		else if (dir == 3) {
			if (cross == 0) {
				TR = glm::rotate(TR, glm::radians(180.f), glm::vec3(0, 1, 0));
			}
			if (cross == 2) {
				TR = glm::rotate(TR, glm::radians(90.f), glm::vec3(0, 1, 0));
			}
		}
	}
	else {
		if (dir % 2 == 1)
			TR = glm::rotate(TR, glm::radians(90.f), glm::vec3(0, 1, 0));
	}
	TR = glm::scale(TR, glm::vec3(3, 1.0, 3));
}

void Road::draw(GLuint vao, unsigned int modelLocation) {
	Road::transform();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	if(cross != 100)
		glDrawArrays(GL_TRIANGLES, 0, 540);
	else
		glDrawArrays(GL_TRIANGLES, 0, 264);
}

void Road::player_distance(float* player_pos, float* camera_dir) {
	if (pow((player_pos[2] + pos[2]), 2) + pow((player_pos[0] + pos[0]), 2) >= 100) {
		if (dir == 0) {
			if(player_pos[2] > -pos[2])
				is_delete = true;
		}
		else if (dir == 1) {
			if (-player_pos[0] > pos[0])
				is_delete = true;
		}
		else if (dir == 2) {
			if (player_pos[2] < -pos[2])
				is_delete = true;
		}
		else if (dir == 3) {
			if (-player_pos[0] < pos[0])
				is_delete = true;
		}
	}
}

bool Road::return_is_delete() {
	return is_delete;
}

float* Road::return_pos() {
	return pos;
}

void Road::select_dir(int map_dir) {
	dir = map_dir;
}

int Road::return_dir() { return dir; }

void Road::set_cross(int num) { cross = num; }

int Road::return_cross() { return cross; }