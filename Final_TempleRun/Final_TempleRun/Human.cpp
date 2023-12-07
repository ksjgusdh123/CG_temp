#define _CRT_SECURE_NO_WARNINGS
#include "Human.h"

float HUMAN_SIZE = 0.025;

void Head::transform() {
	TR = glm::mat4(1.0f);
	if (is_slide) {
		TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
		TR = glm::rotate(TR, glm::radians(rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR = glm::rotate(TR, glm::radians(-30.f), glm::vec3(1.0, 0.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR = glm::translate(TR, glm::vec3(0, -0.2, -0.4)); //--- x축으로 이동 행렬
		TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
	}
	else {
		TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
		TR = glm::rotate(TR, glm::radians(rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR = glm::translate(TR, glm::vec3(0, 0, -0.075)); //--- x축으로 이동 행렬
		TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
	}
}

void Head::draw(GLuint vao, unsigned int modelLocation) {
	Head::transform();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 4056);
}

void Head::get_move(float* move_amount, float* get_rad, bool slide) {
	for (int i = 0; i < 3; ++i) {
		move[i] = move_amount[i];
	}

	for (int i = 0; i < 3; ++i) {
		rad[i] = get_rad[i];
	}
	is_slide = slide;
		
}

void Body::transform() {
	TR = glm::mat4(1.0f);
	if (is_slide) {
		TR = glm::translate(TR, glm::vec3(-move[0], move[1] - 0.05, -move[2])); //--- x축으로 이동 행렬
		TR = glm::rotate(TR, glm::radians(rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR = glm::translate(TR, glm::vec3(0, -0.5, -0.075)); //--- x축으로 이동 행렬
		TR = glm::rotate(TR, glm::radians(rad[0]), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
	}
	else {
		TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
		TR = glm::rotate(TR, glm::radians(0.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR = glm::translate(TR, glm::vec3(0, -0.22, -0.075)); //--- x축으로 이동 행렬
		TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
	}
}

void Body::draw(GLuint vao, unsigned int modelLocation) {
	Body::transform();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 1464);

}

void Body::get_move(float* move_amount, float* get_rad, bool slide) {
	for (int i = 0; i < 3; ++i) {
		move[i] = move_amount[i];
	}

	for (int i = 0; i < 3; ++i) {
		rad[i] = get_rad[i];
	}
	is_slide = slide;

}
void Arm::check_right(int i) {
	if (i == 0)
		is_right = true;
	else
		is_right = false;
}

void Arm::transform() {
	TR = glm::mat4(1.0f);
	if (is_right) {
		if (is_slide) {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1] - 0.15, -move[2] - 0.02)); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
			TR = glm::translate(TR, glm::vec3(-0.08, -0.41, -0.1)); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(-90.f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
			TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
		}
		else {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(-10.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
			TR = glm::translate(TR, glm::vec3(-0.08, -0.15, -0.08)); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(-rad[0] + 10), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
			TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
		}
	}
	else {
		if (is_slide) {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1] - 0.15, -move[2] - 0.02)); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
			TR = glm::translate(TR, glm::vec3(0.08, -0.41, -0.1)); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(30.f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
			TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
		}
		else {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(0.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
			TR = glm::translate(TR, glm::vec3(0.08, -0.15, -0.1)); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(rad[0] + 60), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
			TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
		}
	}
}

void Arm::draw(GLuint vao, unsigned int modelLocation) {
	Arm::transform();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	glBindVertexArray(vao);
	if(is_right)
		glDrawArrays(GL_TRIANGLES, 0, 1848);
	else
		glDrawArrays(GL_TRIANGLES, 0, 3888);

}

void Arm::get_move(float* move_amount, float* get_rad, bool slide) {
	for (int i = 0; i < 3; ++i) {
		move[i] = move_amount[i];
	}
	for (int i = 0; i < 3; ++i) {
		rad[i] = get_rad[i];
	}
	is_slide = slide;
}

void Leg::check_right(int i) {
	if (i == 0)
		is_right = true;
	else
		is_right = false;
}

void Leg::transform() {
	TR = glm::mat4(1.0f);
	if (is_right) {
		if (is_slide) {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(-10.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
			TR = glm::translate(TR, glm::vec3(-0.05, -0.55, 0)); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(rad[0] + 10), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
			TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
		}
		else {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(10.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
			TR = glm::translate(TR, glm::vec3(-0.035, -0.32, -0.075)); //--- x축으로 이동 행렬
			//TR = glm::rotate(TR, glm::radians(6.f), glm::vec3(0.0, 0.0, 1.0)); //--- x축에 대하여 회전 행렬
			TR = glm::rotate(TR, glm::radians(rad[0] + 20), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
			TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, 0.018));
		}

	}
	else {
		if (is_slide) {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(-10.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
			TR = glm::translate(TR, glm::vec3(0.05, -0.55, 0)); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(rad[0] + 10), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
			TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
		}
		else {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(-10.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
			TR = glm::translate(TR, glm::vec3(0.035, -0.32, -0.075)); //--- x축으로 이동 행렬
			//TR = glm::rotate(TR, glm::radians(-6.f), glm::vec3(0.0, 0.0, 1.0)); //--- x축에 대하여 회전 행렬
			TR = glm::rotate(TR, glm::radians(-rad[0] + 20), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
			TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, 0.018));
		}
	}
}

void Leg::draw(GLuint vao, unsigned int modelLocation, GLuint leg_texture) {
	Leg::transform();
	if (is_right)
		glBindTexture(GL_TEXTURE_2D, leg_texture);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	glBindVertexArray(vao);
	if(is_right)
		glDrawArrays(GL_TRIANGLES, 0, 2484);
	else
		glDrawArrays(GL_TRIANGLES, 0, 1848);
}

void Leg::get_move(float* move_amount, float* get_rad, bool slide) {
	for (int i = 0; i < 3; ++i) {
		move[i] = move_amount[i];
	}
	for (int i = 0; i < 3; ++i) {
		rad[i] = get_rad[i];
	}
	is_slide = slide;

}

Human::Human() {
	right_arm.check_right(0);
	left_arm.check_right(1);
	right_leg.check_right(0);
	left_leg.check_right(1);
	slide = false;
}

void Human::draw(GLuint head_vao, GLuint body_vao, GLuint right_arm_vao, GLuint left_arm_vao, GLuint right_leg_vao, GLuint left_leg_vao, unsigned int modelLocation, GLuint leg_texture) {
	head.draw(head_vao, modelLocation);
	body.draw(body_vao, modelLocation);
	right_arm.draw(right_arm_vao, modelLocation);
	left_arm.draw(left_arm_vao, modelLocation);
	right_leg.draw(right_leg_vao, modelLocation, leg_texture);
	left_leg.draw(left_leg_vao, modelLocation, 0);
}

void Human::move(float* move_amount, float* rad, bool pslide) {
	head.get_move(move_amount, rad, pslide);
	body.get_move(move_amount, rad, pslide);
	right_arm.get_move(move_amount, rad, pslide);
	left_arm.get_move(move_amount, rad, pslide);
	right_leg.get_move(move_amount, rad, pslide);
	left_leg.get_move(move_amount, rad, pslide);
	slide = pslide;
}

void Human::turn(int i) {
	if (i == 0) {
		dir += 1;
	}
	else {
		dir -= 1;
	}
	dir = dir % 4;
}

int Human::return_dir() { return dir; }

float Human::get_speed() { return speed; }

void Human::road_check(float* move_amount) {
	for (int i = 0; i < roads.size(); ++i) {
		if (-(roads.at(i).return_pos())[0] - 1.5 < move_amount[0] && -(roads.at(i).return_pos())[0] + 1.5 > move_amount[0]
			&& -(roads.at(i).return_pos())[2] - 1.5 < move_amount[2] && -(roads.at(i).return_pos())[2] + 1.5 > move_amount[2]
			&& (1)){
			if(move_amount[1] <= -0.1)
				move_amount[1] = -0.1;
		}
	}
}

bool Human::return_slide() { return slide; }





































































































