#define _CRT_SECURE_NO_WARNINGS
#include "map.h"

std::vector<Road> roads;

void Road::select_pos(float x, float z) {
	pos[0] = x;
	pos[2] = z;
	pos[1] = -1.7;
}

void Road::transform() {
	TR = glm::mat4(1.0f);
	TR = glm::translate(TR, glm::vec3(pos[0], pos[1], pos[2]));
	TR = glm::scale(TR, glm::vec3(1.5, 1.0, 1.5));
}

void Road::draw(GLuint vao, unsigned int modelLocation) {
	Road::transform();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Road::player_distance(float* player_pos, int* camera_dir) {
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