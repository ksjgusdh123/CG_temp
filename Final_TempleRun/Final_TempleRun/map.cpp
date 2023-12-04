#define _CRT_SECURE_NO_WARNINGS
#include "map.h"

std::vector<Road> roads;

void Road::select_pos(int n) {
	pos[2] = n;
	pos[1] = -1.7;
}

void Road::transform() {
	TR = glm::mat4(1.0f);
	TR = glm::translate(TR, glm::vec3(pos[0], pos[1], pos[2]));
	TR = glm::scale(TR, glm::vec3(1.5, 1.0, 1.0));
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
