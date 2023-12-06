#include "obstacle.h"

std::vector<Obstacle*> ob;

bool Truck::return_delete() { return is_delete; }

void Truck::player_distance(float* player_pos) {
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

void Truck::select_dir(int map_dir) {
	dir = map_dir;
}

void Truck::set_pos(float x, float z) {
	pos[0] = x;
	pos[1] = 0.0;
	pos[2] = z;
}

void Truck::transform() {
	TR = glm::mat4(1.0f);
	TR = glm::translate(TR, glm::vec3(pos[0], pos[1], pos[2])); //--- x축으로 이동 행렬

	if(dir == 0)
		TR = glm::rotate(TR, glm::radians(0.f) , glm::vec3(0, 1, 0));
	else if (dir == 1)
		TR = glm::rotate(TR, glm::radians(270.f), glm::vec3(0, 1, 0));
	else if (dir == 2)
		TR = glm::rotate(TR, glm::radians(180.f), glm::vec3(0, 1, 0));
	else if (dir == 3)
		TR = glm::rotate(TR, glm::radians(90.f), glm::vec3(0, 1, 0));
	
	TR = glm::scale(TR, glm::vec3(0.1, 0.1, 0.1));
}


void Truck::draw(GLuint vao, unsigned int modelLocation, GLuint texture) {
	Truck::transform();
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	glDrawArrays(GL_TRIANGLES, 0, 3312);
}

bool Hurdle::return_delete() { return is_delete; }

void Hurdle::player_distance(float* player_pos) {
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

void Hurdle::select_dir(int map_dir) {
	dir = map_dir;
}

void Hurdle::set_pos(float x, float z) {
	pos[0] = x;
	pos[1] = 0.0;
	pos[2] = z;
}

void Hurdle::transform() {
	TR = glm::mat4(1.0f);
	TR = glm::translate(TR, glm::vec3(pos[0], pos[1], pos[2])); //--- x축으로 이동 행렬
	if (dir == 0)
		TR = glm::rotate(TR, glm::radians(0.f), glm::vec3(0, 1, 0));
	else if (dir == 1)
		TR = glm::rotate(TR, glm::radians(270.f), glm::vec3(0, 1, 0));
	else if (dir == 2)
		TR = glm::rotate(TR, glm::radians(180.f), glm::vec3(0, 1, 0));
	else if (dir == 3)
		TR = glm::rotate(TR, glm::radians(90.f), glm::vec3(0, 1, 0));
	TR = glm::scale(TR, glm::vec3(0.1, 0.1, 0.1));

}

void Hurdle::draw(GLuint vao, unsigned int modelLocation, GLuint texture) {
	Hurdle::transform();
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	glDrawArrays(GL_TRIANGLES, 0, 2568);
}