#include "wall.h"

std::vector<Apart*> building;

void Apart::draw(GLuint vao, unsigned int modelLocation) {
	Apart::transform();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	if(is_store)
		glDrawArrays(GL_TRIANGLES, 0, 2760);
	else
		glDrawArrays(GL_TRIANGLES, 0, 9360);
}

void Apart::transform() {
	TR = glm::mat4(1.0f);
	if (is_store) {
		if (is_right) {
			switch (dir) {
			case 0:
			case 2:
				TR = glm::translate(TR, glm::vec3(pos[0] + 3.3, pos[1], pos[2]));
				TR = glm::rotate(TR, glm::radians(-90.f), glm::vec3(0, 1.0, 0));
				break;
			case 1:
			case 3:
				TR = glm::translate(TR, glm::vec3(pos[0], pos[1], pos[2] + 3.3));
				TR = glm::rotate(TR, glm::radians(180.f), glm::vec3(0, 1.0, 0));
				break;
			}
		}
		else {
			switch (dir) {
			case 0:
			case 2:
				TR = glm::translate(TR, glm::vec3(pos[0] - 3.3, pos[1], pos[2]));
				TR = glm::rotate(TR, glm::radians(90.f), glm::vec3(0, 1.0, 0));
				break;
			case 1:
			case 3:
				TR = glm::translate(TR, glm::vec3(pos[0], pos[1], pos[2] - 3.3));
				TR = glm::rotate(TR, glm::radians(0.f), glm::vec3(0, 1.0, 0));
				break;
			}
		}
		TR = glm::scale(TR, glm::vec3(0.1, 0.1, 0.1));
	}
	else {
		if (is_right) {
			switch (dir) {
			case 0:
			case 2:
				TR = glm::translate(TR, glm::vec3(pos[0] + 3.2, pos[1], pos[2]));
				TR = glm::rotate(TR, glm::radians(-90.f), glm::vec3(0, 1.0, 0));
				break;
			case 1:
			case 3:
				TR = glm::translate(TR, glm::vec3(pos[0], pos[1], pos[2] + 3.2));
				TR = glm::rotate(TR, glm::radians(180.f), glm::vec3(0, 1.0, 0));
				break;
			}
		}
		else {
			switch (dir) {
			case 0:
			case 2:
				TR = glm::translate(TR, glm::vec3(pos[0] - 3.2, pos[1], pos[2]));
				TR = glm::rotate(TR, glm::radians(90.f), glm::vec3(0, 1.0, 0));
				break;
			case 1:
			case 3:
				TR = glm::translate(TR, glm::vec3(pos[0], pos[1], pos[2] - 3.2));
				TR = glm::rotate(TR, glm::radians(0.f), glm::vec3(0, 1.0, 0));
				break;
			}
		}
		TR = glm::scale(TR, glm::vec3(0.07, 0.05, 0.05));
	}
}

void Apart::select_pos(float x, float z, int num, int n) {
	if (n == 0)
		is_store = false;
	else
		is_store = true;
	
	z = floor(-z / 2) * 2;
	pos[0] = x;
	pos[1] = -0.7;
	pos[2] = -z;
	if (num % 2 == 0)
		is_right = true;
	else
		is_right = false;
}

void Apart::player_distance(float* player_pos) {
	if (pow((player_pos[2] + pos[2]), 2) + pow((player_pos[0] + pos[0]), 2) >= 100) {
		if (dir == 0) {
			if (player_pos[2] > -pos[2])
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

bool Apart::return_delete() {
	return is_delete;
}

float* Apart::return_pos() {
	return pos;
}

void Apart::select_dir(int map_dir) {
	dir = map_dir;
}

int Apart::return_dir() { return dir; }

bool Apart::return_what() { return is_store; }