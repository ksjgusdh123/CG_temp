#define _CRT_SECURE_NO_WARNINGS
#include "Human.h"

void Head::transform() {
	TR = glm::mat4(1.0f);
	if (is_slide) {
		TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
		TR = glm::rotate(TR, glm::radians(rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR = glm::translate(TR, glm::vec3(0, -0.34 - 0.2, -0.075 - 0.045)); //--- x축으로 이동 행렬
		TR = glm::scale(TR, glm::vec3(0.01, 0.01, 0.01));
	}
	else {
		TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
		TR = glm::rotate(TR, glm::radians(rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR = glm::translate(TR, glm::vec3(0, -0.34, -0.075)); //--- x축으로 이동 행렬
		TR = glm::scale(TR, glm::vec3(0.01, 0.01, 0.01));
	}
}

void Head::draw(GLuint vao, unsigned int modelLocation) {
	Head::transform();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 1750);
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
		TR = glm::translate(TR, glm::vec3(0, -0.24, -0.075)); //--- x축으로 이동 행렬
		TR = glm::rotate(TR, glm::radians(rad[0]), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR = glm::scale(TR, glm::vec3(0.01, 0.01, 0.01));
	}
	else {
		TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
		TR = glm::rotate(TR, glm::radians(0.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR = glm::translate(TR, glm::vec3(0, -0.24, -0.075)); //--- x축으로 이동 행렬
		TR = glm::scale(TR, glm::vec3(0.01, 0.01, 0.01));
	}
}

void Body::draw(GLuint vao, unsigned int modelLocation) {
	Body::transform();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 1000);

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
			TR = glm::translate(TR, glm::vec3(-0.08, -0.15, -0.1)); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(10.f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
			TR = glm::scale(TR, glm::vec3(0.01, 0.01, 0.01));
		}
		else {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(-10.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
			TR = glm::translate(TR, glm::vec3(-0.08, -0.15, -0.08)); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(-rad[0] + 10), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
			TR = glm::scale(TR, glm::vec3(0.01, 0.01, 0.01));
		}
	}
	else {
		if (is_slide) {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1] - 0.15, -move[2] - 0.02)); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
			TR = glm::translate(TR, glm::vec3(0.08, -0.15, -0.1)); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(10.f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
			TR = glm::scale(TR, glm::vec3(0.01, 0.01, 0.01));
		}
		else {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(0.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
			TR = glm::translate(TR, glm::vec3(0.08, -0.15, -0.1)); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(rad[0] + 60), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
			TR = glm::scale(TR, glm::vec3(0.01, 0.01, 0.01));
		}
	}
}

void Arm::draw(GLuint vao, unsigned int modelLocation) {
	Arm::transform();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	glBindVertexArray(vao);
	if(is_right)
		glDrawArrays(GL_TRIANGLES, 0, 1000);
	else
		glDrawArrays(GL_TRIANGLES, 0, 2000);

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
			TR = glm::translate(TR, glm::vec3(-0.07, -0.32, -0.1)); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(-6.f), glm::vec3(0.0, 0.0, 1.0)); //--- x축에 대하여 회전 행렬
			TR = glm::rotate(TR, glm::radians(rad[0] + 10), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
			TR = glm::scale(TR, glm::vec3(0.01, 0.01, 0.01));
		}
		else {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(10.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
			TR = glm::translate(TR, glm::vec3(-0.02, -0.32, -0.1)); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(6.f), glm::vec3(0.0, 0.0, 1.0)); //--- x축에 대하여 회전 행렬
			TR = glm::rotate(TR, glm::radians(rad[0] + 20), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
			TR = glm::scale(TR, glm::vec3(0.01, 0.01, 0.01));
		}
	
	}
	else {
		if (is_slide) {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(-10.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
			TR = glm::translate(TR, glm::vec3(0.02, -0.32, -0.1)); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(-6.f), glm::vec3(0.0, 0.0, 1.0)); //--- x축에 대하여 회전 행렬
			TR = glm::rotate(TR, glm::radians(rad[0] + 20), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
			TR = glm::scale(TR, glm::vec3(0.01, 0.01, 0.01));
		}
		else {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(-10.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
			TR = glm::translate(TR, glm::vec3(0.02, -0.32, -0.1)); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(-6.f), glm::vec3(0.0, 0.0, 1.0)); //--- x축에 대하여 회전 행렬
			TR = glm::rotate(TR, glm::radians(-rad[0] + 20), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
			TR = glm::scale(TR, glm::vec3(0.01, 0.01, 0.01));
		}
	}
}

void Leg::draw(GLuint vao, unsigned int modelLocation, GLuint leg_texture) {
	Leg::transform();
	if(is_right)
		glBindTexture(GL_TEXTURE_2D, leg_texture);	
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 850);
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

void Human::move(float* move_amount, float* rad, bool slide) {
	head.get_move(move_amount, rad, slide);
	body.get_move(move_amount, rad, slide);
	right_arm.get_move(move_amount, rad, slide);
	left_arm.get_move(move_amount, rad, slide);
	right_leg.get_move(move_amount, rad, slide);
	left_leg.get_move(move_amount, rad, slide);
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
