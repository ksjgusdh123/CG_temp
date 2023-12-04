#define _CRT_SECURE_NO_WARNINGS
#include "map.h"

std::vector<Road> roads;
random_device rd;
std::mt19937 dre(rd());
std::uniform_int_distribution<int> uid{ 0, 1 };

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

void Road::player_distance(float* player_pos) {
	if (std::abs(player_pos[2] + pos[2]) >= 10 && -player_pos[2] < pos[2])
		is_delete = true;
}

bool Road::return_is_delete() {
	return is_delete;
}

float* Road::return_pos() {
	return pos;
}

void Road::select_dir() {
	if (uid(dre) == 0) {
		dir += 1;
	}
	else {
		dir -= 1;
	}

	if (dir == -1)
		dir = 3;
	dir = dir % 4;
}

int Road::return_dir() { return dir; }