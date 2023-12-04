#define _CRT_SECURE_NO_WARNINGS
#include "map.h"


void Road::select_pos(int n) {
	for (int i = 0; i < n; ++i) {
		pos[2] = -n * 2;
		pos[1] = -1.7;
	}
}

void Road::transform() {
	TR = glm::mat4(1.0f);
	TR = glm::translate(TR, glm::vec3(pos[0], pos[1], pos[2]));
}

void Road::draw(GLuint vao, unsigned int modelLocation) {
	Road::transform();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
