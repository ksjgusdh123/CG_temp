#include "wall.h"

std::vector<Apart*> building;

void Apart::draw(GLuint vao, unsigned int modelLocation) {
	Apart::transform();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 9360);
}

void Apart::transform() {
	TR = glm::mat4(1.0f);
	if (is_right) {
		TR = glm::translate(TR, glm::vec3(pos[0] + 2, pos[1], pos[2]));
		TR = glm::rotate(TR, glm::radians(-90.f), glm::vec3(0, 1.0, 0));
	}
	else {
		TR = glm::translate(TR, glm::vec3(pos[0] - 2, pos[1], pos[2]));
		TR = glm::rotate(TR, glm::radians(90.f), glm::vec3(0, 1.0, 0));
	}
	TR = glm::scale(TR, glm::vec3(0.07, 0.05, 0.05));
}

void Apart::select_pos(float x, float z, int num) {
	pos[0] = x;
	pos[1] = -0.7;
	pos[2] = z;
	if (num % 2 == 0)
		is_right = true;
	else
		is_right = false;
}


bool Apart::return_is_delete() {
	return is_delete;
}

float* Apart::return_pos() {
	return pos;
}

void Apart::select_dir(int map_dir) {
	dir = map_dir;
}

int Apart::return_dir() { return dir; }