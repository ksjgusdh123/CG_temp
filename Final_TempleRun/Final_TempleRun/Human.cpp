#define _CRT_SECURE_NO_WARNINGS
#include "Human.h"

float HUMAN_SIZE = 0.025;

float GAP = 1.45;

void Head::transform(bool is_police) {
	TR = glm::mat4(1.0f);
	if (is_police) {
		TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
		TR = glm::rotate(TR, glm::radians(rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR = glm::translate(TR, glm::vec3(0, 0.08, -0.075)); //--- x축으로 이동 행렬
		TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
	}
	else {
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
}

void Head::draw(GLuint vao, unsigned int modelLocation, bool is_police) {
	Head::transform(is_police);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	glBindVertexArray(vao);
	if(is_police)
		glDrawArrays(GL_TRIANGLES, 0, 3960);
	else
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

void Body::transform(bool is_police) {
	TR = glm::mat4(1.0f);
	if (is_police) {
		TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
		TR = glm::rotate(TR, glm::radians(0.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR = glm::translate(TR, glm::vec3(0, -0.26, -0.075)); //--- x축으로 이동 행렬
		TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
	}
	else {
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
	
}

void Body::draw(GLuint vao, unsigned int modelLocation, bool is_police) {
	Body::transform(is_police);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	glBindVertexArray(vao);
	if(is_police)
		glDrawArrays(GL_TRIANGLES, 0, 1464);
	else
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

void Arm::transform(bool is_police) {
	TR = glm::mat4(1.0f);
	if (is_police) {
		if (is_right) {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(-10.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
			TR = glm::translate(TR, glm::vec3(-0.08, -0.15, -0.08)); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(-rad[0] + 30), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
			TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
		}
		else{
			TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(0.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
			TR = glm::translate(TR, glm::vec3(0.08, -0.15, -0.1)); //--- x축으로 이동 행렬
			TR = glm::rotate(TR, glm::radians(rad[0]), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
			TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
		}
	}
	else {
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
				TR = glm::rotate(TR, glm::radians(rad[0] / 10 + 60), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
				TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
			}
		}
	}
}

void Arm::draw(GLuint vao, unsigned int modelLocation, bool is_police) {
	Arm::transform(is_police);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	glBindVertexArray(vao);
	if (is_police) {
		if (is_right)
			glDrawArrays(GL_TRIANGLES, 0, 3036);
		else
			glDrawArrays(GL_TRIANGLES, 0, 2484);
	}
	else {
		if (is_right)
			glDrawArrays(GL_TRIANGLES, 0, 1848);
		else
			glDrawArrays(GL_TRIANGLES, 0, 3888);
	}
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

void Leg::transform(bool is_police) {
	TR = glm::mat4(1.0f);
	if (is_police) {
		if (is_right) {
				TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x축으로 이동 행렬
				TR = glm::rotate(TR, glm::radians(10.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
				TR = glm::translate(TR, glm::vec3(-0.035, -0.32, -0.075)); //--- x축으로 이동 행렬
				//TR = glm::rotate(TR, glm::radians(6.f), glm::vec3(0.0, 0.0, 1.0)); //--- x축에 대하여 회전 행렬
				TR = glm::rotate(TR, glm::radians(rad[0] + 20), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
				TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, 0.018));
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
	else {
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
}

void Leg::draw(GLuint vao, unsigned int modelLocation, GLuint leg_texture, bool is_police) {
	Leg::transform(is_police);
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

void Human::draw(GLuint head_vao, GLuint body_vao, GLuint right_arm_vao, GLuint left_arm_vao, GLuint right_leg_vao, GLuint left_leg_vao, unsigned int modelLocation,
	GLuint head_texture, GLuint body_texture, GLuint right_arm_texture, GLuint left_arm_texture, GLuint right_leg_texture, GLuint left_leg_texture){

	glBindTexture(GL_TEXTURE_2D, head_texture);
	head.draw(head_vao, modelLocation, false);
	glBindTexture(GL_TEXTURE_2D, body_texture);
	body.draw(body_vao, modelLocation, false);
	glBindTexture(GL_TEXTURE_2D, right_arm_texture);
	right_arm.draw(right_arm_vao, modelLocation, false);
	glBindTexture(GL_TEXTURE_2D, left_arm_texture);
	left_arm.draw(left_arm_vao, modelLocation, false);
	glBindTexture(GL_TEXTURE_2D, right_leg_texture);
	right_leg.draw(right_leg_vao, modelLocation, right_leg_texture, false);
	left_leg.draw(left_leg_vao, modelLocation, 0, false);
	glBindTexture(GL_TEXTURE_2D, left_leg_texture);
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

bool Human::road_check(float* move_amount) {
	for (int i = 0; i < roads.size(); ++i) {
		if (-(roads.at(i).return_pos())[0] - 3 < move_amount[0] && -(roads.at(i).return_pos())[0] + 3 > move_amount[0]
			&& -(roads.at(i).return_pos())[2] - 3 < move_amount[2] && -(roads.at(i).return_pos())[2] + 3 > move_amount[2]){
			set_road(roads.at(i));
			if (move_amount[1] <= -0.1) {
				move_amount[1] = -0.1;
				return true;
			}
		}
	}
	return false;
}

bool Human::return_slide() { return slide; }

bool Human::return_jump() { return jump; }

void Human::set_jump(bool a) { jump = a;}

void Human::set_speed(float a) { speed += a;}

void Human::set_light(float a) { light += a; }

float Human::return_light() { return light; }

void Human::set_road(Road& ro) {
	last = ro;
}

void Human::recover_speed(float sp) { speed = sp; }

void Human::position_setting(float* move_amount) {
	float* temp = last.return_pos();
	int num = 0;
	if (last.return_cross() == 0) {
		if (last.return_dir() == 1) {
			if (move_amount[2] <= -(temp[2] + GAP)) //2
				move_amount[2] = -(temp[2] + GAP);
			if (move_amount[0] <= -(temp[0] + GAP))  // 1
				move_amount[0] = -(temp[0] + GAP);
		}
		else if (last.return_dir() == 3) {
			if (move_amount[2] <= -(temp[2] + GAP)) //2
				move_amount[2] = -(temp[2] + GAP);
			if (move_amount[0] >= -(temp[0] - GAP))  // 3
				move_amount[0] = -(temp[0] - GAP);
		}
	}
	else if (last.return_cross() == 1) {
		if (last.return_dir() == 0) {
			if (move_amount[0] >= -(temp[0] - GAP))  // 3
				move_amount[0] = -(temp[0] - GAP);
			if (move_amount[2] >= -(temp[2] - GAP)) // 0
				move_amount[2] = -(temp[2] - GAP);
		}
		else if (last.return_dir() == 2) {
			if (move_amount[0] >= -(temp[0] - GAP))  // 3
				move_amount[0] = -(temp[0] - GAP);
			if (move_amount[2] <= -(temp[2] + GAP)) //2
				move_amount[2] = -(temp[2] + GAP);
		}
	}
	else if (last.return_cross() == 2) {
		if (last.return_dir() == 1) {
			if (move_amount[0] <= -(temp[0] + GAP))  // 1
				move_amount[0] = -(temp[0] + GAP);
			if (move_amount[2] >= -(temp[2] - GAP)) // 0
				move_amount[2] = -(temp[2] - GAP);
		}
		else if (last.return_dir() == 3) {
			if (move_amount[0] >= -(temp[0] - GAP))  // 3
				move_amount[0] = -(temp[0] - GAP);
			if (move_amount[2] >= -(temp[2] - GAP)) // 0
				move_amount[2] = -(temp[2] - GAP);
		}
	}
	else if (last.return_cross() == 3) {
		if (last.return_dir() == 0) {
			if (move_amount[0] <= -(temp[0] + GAP))  // 1
				move_amount[0] = -(temp[0] + GAP);
			if (move_amount[2] >= -(temp[2] - GAP)) // 0
				move_amount[2] = -(temp[2] - GAP);
		}
		else if (last.return_dir() == 2) {
			if (move_amount[0] <= -(temp[0] + GAP))  // 1
				move_amount[0] = -(temp[0] + GAP);
			if (move_amount[2] <= -(temp[2] + GAP)) //2
				move_amount[2] = -(temp[2] + GAP);
		}
	}
	else {
		if (last.return_dir() == 0) {
			if (move_amount[0] <= -(temp[0] + GAP))  // 1
				move_amount[0] = -(temp[0] + GAP);
			else if (move_amount[0] >= -(temp[0] - GAP)) // 3
				move_amount[0] = -(temp[0] - GAP);
		}
		else if (last.return_dir() == 1) {
			if (move_amount[2] >= -(temp[2] - GAP)) // 0
				move_amount[2] = -(temp[2] - GAP);
			else if (move_amount[2] <= -(temp[2] + GAP)) //2
				move_amount[2] = -(temp[2] + GAP);
		}
		else if (last.return_dir() == 2) {
			if (move_amount[0] <= -(temp[0] + GAP))  // 1
				move_amount[0] = -(temp[0] + GAP);
			else if (move_amount[0] >= -(temp[0] - GAP)) // 3
				move_amount[0] = -(temp[0] - GAP);
		}
		else if (last.return_dir() == 3) {
			if (move_amount[2] >= -(temp[2] - GAP)) // 0
				move_amount[2] = -(temp[2] - GAP);
			else if (move_amount[2] <= -(temp[2] + GAP)) //2
				move_amount[2] = -(temp[2] + GAP);
		}
	}
}

Road& Human::return_last() { return last; }

float Human::return_speed() { return speed; }

void Human::reset_player() {
	dir = 0;
	speed = 0.15;
	for (int i = 0; i < 3; ++i)
		rad[i] = 0;
	slide = false;
	jump = false;
	cross = false;
	light = 100;
}

Police::Police() {
	right_arm.check_right(0);
	left_arm.check_right(1);
	right_leg.check_right(0);
	left_leg.check_right(1);
	pos[2] = -3;
	for (int i = 0; i < 3; ++i)
		turn_point[i] = 100;
}

void Police::draw(GLuint head_vao, GLuint body_vao, GLuint right_arm_vao, GLuint left_arm_vao, GLuint right_leg_vao, GLuint left_leg_vao, unsigned int modelLocation,
	GLuint head_texture, GLuint body_texture, GLuint right_arm_texture, GLuint left_arm_texture, GLuint right_leg_texture, GLuint left_leg_texture){
	glBindTexture(GL_TEXTURE_2D, head_texture);
	head.draw(head_vao, modelLocation, true);
	glBindTexture(GL_TEXTURE_2D, body_texture);
	body.draw(body_vao, modelLocation, true);
	glBindTexture(GL_TEXTURE_2D, right_arm_texture);
	right_arm.draw(right_arm_vao, modelLocation, true);
	glBindTexture(GL_TEXTURE_2D, left_arm_texture);
	left_arm.draw(left_arm_vao, modelLocation, true);
	glBindTexture(GL_TEXTURE_2D, right_leg_texture);
	right_leg.draw(right_leg_vao, modelLocation, right_leg_texture, true);
	glBindTexture(GL_TEXTURE_2D, left_leg_texture);
	left_leg.draw(left_leg_vao, modelLocation, 0, true);
}

void Police::set_turn_point(Human& player) {
	Road temp = player.return_last();
	float* temp_pos = temp.return_pos();
	
	if (next_dir == now_dir) {
		if (temp.return_cross() != 100) {
			next_dir = temp.return_cross();
			for (int i = 0; i < 3; ++i) {
				turn_point[i] = temp_pos[i];
			}
		}
	}
	else {
		if (now_dir == 0) {
			if (next_dir == 1 && pos[2] >= -turn_point[2]) {
				rad[1] -= 90;
				now_dir = 1;
				turn_point[2] = INT_MAX;
			}
			else if (next_dir == 3 && pos[2] >= -turn_point[2]) {
				rad[1] += 90;
				now_dir = 3;
				turn_point[2] = INT_MAX;
			}
		}
		else if (now_dir == 1) {
			if (next_dir == 0 && -pos[0] >= turn_point[0]) {
				rad[1] += 90;
				now_dir = 0;
				turn_point[2] = INT_MAX;
			}
			else if (next_dir == 2 && -pos[0] >= turn_point[0]) {
				rad[1] -= 90;
				now_dir = 2;
				turn_point[2] = INT_MAX;
			}
		}
		else if (now_dir == 2) {
			if (next_dir == 1 && -pos[2] >= turn_point[2]) {
				rad[1] += 90;
				now_dir = 1;
				turn_point[2] = INT_MAX;
			}
			else if (next_dir == 3 && -pos[2] >= turn_point[2]) {
				rad[1] -= 90;
				now_dir = 3;
				turn_point[2] = INT_MAX;
			}
		}
		else if (now_dir == 3) {
			if (next_dir == 0 && pos[0] >= -turn_point[0]) {
				rad[1] -= 90;
				now_dir = 0;
				turn_point[2] = INT_MAX;
			}
			else if (next_dir == 2 && pos[0] >= -turn_point[0]) {
				rad[1] += 90;
				now_dir = 2;
				turn_point[2] = INT_MAX;
			}
		}
	}
}

void Police::move(Human& player) {
	set_turn_point(player);
	if (now_dir == 0) {
		pos[2] += speed;
	}
	else if(now_dir == 1) {
		pos[0] -= speed;
	}
	else if (now_dir == 2) {
		pos[2] -= speed;
	}
	else if (now_dir == 3) {
		pos[0] += speed;
	}

	

	if (flip)
		rad[0] -= 5;
	else
		rad[0] += 5;

	if (rad[0] >= 50)
		flip = true;
	else if (rad[0] <= -50)
		flip = false;

	police_re();
}

void Police::police_re() {
	head.get_move(pos, rad, false);
	body.get_move(pos, rad, false);
	right_arm.get_move(pos, rad, false);
	left_arm.get_move(pos, rad, false);
	right_leg.get_move(pos, rad, false);
	left_leg.get_move(pos, rad, false);
}


float Police::get_speed() {
	return speed;
}

void Police::set_speed(float a) { speed += a; }

void Police::get_rad(float* other_rad) {
	for (int i = 0; i < 3; ++i)
		rad[i] = other_rad[i];
}

void Police::police_reset() {
	speed = 0.15;
	now_dir = 0;
	next_dir = 0;
	for (int i = 0; i < 3; ++i) {
		turn_point[i] = 100;
		pos[i] = 0;
	}
	pos[2] = -3;
	rad[0] = 0; rad[1] = 540; rad[2] = 0;
	is_police = true;
	flip = false;
}

float* Police::return_pos() { return pos; }

bool Police::catch_thief(Human& player, float* move_amount) {
	if (now_dir == player.return_last().return_dir()) {
		switch (now_dir) {
		case 0:
			if (pos[2] >= move_amount[2]) {
				std::cout << "잡았다" << std::endl;
				return true;
			}
			break;
		case 1:
			if (pos[0] <= move_amount[0]) {
				std::cout << "잡았다" << std::endl;
				return true;
			}
			break;
		case 2:
			if (pos[2] <= move_amount[2]) {
				std::cout << "잡았다" << std::endl;
				return true;
			}
			break;
		case 3:
			if (pos[0] >= move_amount[0]) {
				std::cout << "잡았다" << std::endl;
				return true;
			}
			break;
		}
	}
	else if (now_dir == player.return_last().return_cross() && player.return_dir() != player.return_last().return_cross())
		return true;
	return false;
}