#define _CRT_SECURE_NO_WARNINGS
#include "Human.h"

float HUMAN_SIZE = 0.025;

void Head::transform() {
	TR = glm::mat4(1.0f);
	if (is_slide) {
		TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x������ �̵� ���
		TR = glm::rotate(TR, glm::radians(rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR = glm::rotate(TR, glm::radians(-30.f), glm::vec3(1.0, 0.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR = glm::translate(TR, glm::vec3(0, -0.2, -0.4)); //--- x������ �̵� ���
		TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
	}
	else {
		TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x������ �̵� ���
		TR = glm::rotate(TR, glm::radians(rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR = glm::translate(TR, glm::vec3(0, 0, -0.075)); //--- x������ �̵� ���
		TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
	}
}

void Head::draw(GLuint vao, unsigned int modelLocation) {
	Head::transform();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��ȯ �� �����ϱ�
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
		TR = glm::translate(TR, glm::vec3(-move[0], move[1] - 0.05, -move[2])); //--- x������ �̵� ���
		TR = glm::rotate(TR, glm::radians(rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR = glm::translate(TR, glm::vec3(0, -0.5, -0.075)); //--- x������ �̵� ���
		TR = glm::rotate(TR, glm::radians(rad[0]), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
	}
	else {
		TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x������ �̵� ���
		TR = glm::rotate(TR, glm::radians(0.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR = glm::translate(TR, glm::vec3(0, -0.22, -0.075)); //--- x������ �̵� ���
		TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
	}
}

void Body::draw(GLuint vao, unsigned int modelLocation) {
	Body::transform();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��ȯ �� �����ϱ�
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
			TR = glm::translate(TR, glm::vec3(-move[0], move[1] - 0.15, -move[2] - 0.02)); //--- x������ �̵� ���
			TR = glm::rotate(TR, glm::radians(rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
			TR = glm::translate(TR, glm::vec3(-0.08, -0.41, -0.1)); //--- x������ �̵� ���
			TR = glm::rotate(TR, glm::radians(-90.f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
			TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
		}
		else {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x������ �̵� ���
			TR = glm::rotate(TR, glm::radians(-10.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
			TR = glm::translate(TR, glm::vec3(-0.08, -0.15, -0.08)); //--- x������ �̵� ���
			TR = glm::rotate(TR, glm::radians(-rad[0] + 10), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
			TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
		}
	}
	else {
		if (is_slide) {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1] - 0.15, -move[2] - 0.02)); //--- x������ �̵� ���
			TR = glm::rotate(TR, glm::radians(rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
			TR = glm::translate(TR, glm::vec3(0.08, -0.41, -0.1)); //--- x������ �̵� ���
			TR = glm::rotate(TR, glm::radians(30.f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
			TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
		}
		else {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x������ �̵� ���
			TR = glm::rotate(TR, glm::radians(0.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
			TR = glm::translate(TR, glm::vec3(0.08, -0.15, -0.1)); //--- x������ �̵� ���
			TR = glm::rotate(TR, glm::radians(rad[0] + 60), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
			TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
		}
	}
}

void Arm::draw(GLuint vao, unsigned int modelLocation) {
	Arm::transform();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��ȯ �� �����ϱ�
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
			TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x������ �̵� ���
			TR = glm::rotate(TR, glm::radians(-10.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
			TR = glm::translate(TR, glm::vec3(-0.05, -0.55, 0)); //--- x������ �̵� ���
			TR = glm::rotate(TR, glm::radians(rad[0] + 10), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
			TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
		}
		else {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x������ �̵� ���
			TR = glm::rotate(TR, glm::radians(10.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
			TR = glm::translate(TR, glm::vec3(-0.035, -0.32, -0.075)); //--- x������ �̵� ���
			//TR = glm::rotate(TR, glm::radians(6.f), glm::vec3(0.0, 0.0, 1.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
			TR = glm::rotate(TR, glm::radians(rad[0] + 20), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
			TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, 0.018));
		}

	}
	else {
		if (is_slide) {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x������ �̵� ���
			TR = glm::rotate(TR, glm::radians(-10.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
			TR = glm::translate(TR, glm::vec3(0.05, -0.55, 0)); //--- x������ �̵� ���
			TR = glm::rotate(TR, glm::radians(rad[0] + 10), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
			TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, HUMAN_SIZE));
		}
		else {
			TR = glm::translate(TR, glm::vec3(-move[0], move[1], -move[2])); //--- x������ �̵� ���
			TR = glm::rotate(TR, glm::radians(-10.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
			TR = glm::translate(TR, glm::vec3(0.035, -0.32, -0.075)); //--- x������ �̵� ���
			//TR = glm::rotate(TR, glm::radians(-6.f), glm::vec3(0.0, 0.0, 1.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
			TR = glm::rotate(TR, glm::radians(-rad[0] + 20), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
			TR = glm::scale(TR, glm::vec3(HUMAN_SIZE, HUMAN_SIZE, 0.018));
		}
	}
}

void Leg::draw(GLuint vao, unsigned int modelLocation, GLuint leg_texture) {
	Leg::transform();
	if (is_right)
		glBindTexture(GL_TEXTURE_2D, leg_texture);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��ȯ �� �����ϱ�
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

bool Human::road_check(float* move_amount) {
	for (int i = 0; i < roads.size(); ++i) {
		if (-(roads.at(i).return_pos())[0] - 2 < move_amount[0] && -(roads.at(i).return_pos())[0] + 2 > move_amount[0]
			&& -(roads.at(i).return_pos())[2] - 2 < move_amount[2] && -(roads.at(i).return_pos())[2] + 2 > move_amount[2]){
			if (move_amount[1] <= -0.1) {
				move_amount[1] = -0.1;
			}
			set_road(roads.at(i));
			return true;
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

void Human::position_setting(float* move_amount) {
	float* temp = last.return_pos();
	int num = 0;
	if (last.return_cross() == 0) {
		if (last.return_dir() == 1) {
			if (move_amount[2] <= -(temp[2] + 1.7)) //2
				move_amount[2] = -(temp[2] + 1.7);
			if (move_amount[0] <= -(temp[0] + 1.7))  // 1
				move_amount[0] = -(temp[0] + 1.7);
		}
		else if (last.return_dir() == 3) {
			if (move_amount[2] <= -(temp[2] + 1.7)) //2
				move_amount[2] = -(temp[2] + 1.7);
			if (move_amount[0] >= -(temp[0] - 1.7))  // 3
				move_amount[0] = -(temp[0] - 1.7);
		}
	}
	else if (last.return_cross() == 1) {
		if (last.return_dir() == 0) {
			if (move_amount[0] >= -(temp[0] - 1.7))  // 3
				move_amount[0] = -(temp[0] - 1.7);
			if (move_amount[2] >= -(temp[2] - 1.7)) // 0
				move_amount[2] = -(temp[2] - 1.7);
		}
		else if (last.return_dir() == 2) {
			if (move_amount[0] >= -(temp[0] - 1.7))  // 3
				move_amount[0] = -(temp[0] - 1.7);
			if (move_amount[2] <= -(temp[2] + 1.7)) //2
				move_amount[2] = -(temp[2] + 1.7);
		}
	}
	else if (last.return_cross() == 2) {
		if (last.return_dir() == 1) {
			if (move_amount[0] <= -(temp[0] + 1.7))  // 1
				move_amount[0] = -(temp[0] + 1.7);
			if (move_amount[2] >= -(temp[2] - 1.7)) // 0
				move_amount[2] = -(temp[2] - 1.7);
		}
		else if (last.return_dir() == 3) {
			if (move_amount[0] >= -(temp[0] - 1.7))  // 3
				move_amount[0] = -(temp[0] - 1.7);
			if (move_amount[2] >= -(temp[2] - 1.7)) // 0
				move_amount[2] = -(temp[2] - 1.7);
		}
	}
	else if (last.return_cross() == 3) {
		if (last.return_dir() == 0) {
			if (move_amount[0] <= -(temp[0] + 1.7))  // 1
				move_amount[0] = -(temp[0] + 1.7);
			if (move_amount[2] >= -(temp[2] - 1.7)) // 0
				move_amount[2] = -(temp[2] - 1.7);
		}
		else if (last.return_dir() == 2) {
			if (move_amount[0] <= -(temp[0] + 1.7))  // 1
				move_amount[0] = -(temp[0] + 1.7);
			if (move_amount[2] <= -(temp[2] + 1.7)) //2
				move_amount[2] = -(temp[2] + 1.7);
		}
	}
	else {
		if (last.return_dir() == 0) {
			if (move_amount[0] <= -(temp[0] + 1.7))  // 1
				move_amount[0] = -(temp[0] + 1.7);
			else if (move_amount[0] >= -(temp[0] - 1.7)) // 3
				move_amount[0] = -(temp[0] - 1.7);
		}
		else if (last.return_dir() == 1) {
			if (move_amount[2] >= -(temp[2] - 1.7)) // 0
				move_amount[2] = -(temp[2] - 1.7);
			else if (move_amount[2] <= -(temp[2] + 1.7)) //2
				move_amount[2] = -(temp[2] + 1.7);
		}
		else if (last.return_dir() == 2) {
			if (move_amount[0] <= -(temp[0] + 1.7))  // 1
				move_amount[0] = -(temp[0] + 1.7);
			else if (move_amount[0] >= -(temp[0] - 1.7)) // 3
				move_amount[0] = -(temp[0] - 1.7);
		}
		else if (last.return_dir() == 3) {
			if (move_amount[2] >= -(temp[2] - 1.7)) // 0
				move_amount[2] = -(temp[2] - 1.7);
			else if (move_amount[2] <= -(temp[2] + 1.7)) //2
				move_amount[2] = -(temp[2] + 1.7);
		}
	}
}






























































































