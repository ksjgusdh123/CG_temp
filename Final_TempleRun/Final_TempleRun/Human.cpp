#define _CRT_SECURE_NO_WARNINGS
#include "Human.h"

void Head::transform() {
	TR = glm::mat4(1.0f);
	TR = glm::translate(TR, glm::vec3(-move_amount_x, 0, -move_amount_z)); //--- x������ �̵� ���
	TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
	TR = glm::rotate(TR, glm::radians(0.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
	TR = glm::translate(TR, glm::vec3(0, -0.01, -0.075)); //--- x������ �̵� ���
	TR = glm::scale(TR, glm::vec3(0.01, 0.01, 0.01));
}

void Head::draw(GLuint vao, unsigned int modelLocation) {
	Head::transform();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��ȯ �� �����ϱ�
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 1000);
}

void Head::get_move(float amount_x, float amount_z, float* get_rad) {
	move_amount_x = amount_x;
	move_amount_z = amount_z;
	for (int i = 0; i < 3; ++i) {
		rad[i] = get_rad[i];
	}
}

void Body::transform() {
	TR = glm::mat4(1.0f);
	TR = glm::translate(TR, glm::vec3(-move_amount_x, 0, -move_amount_z)); //--- x������ �̵� ���
	TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
	TR = glm::rotate(TR, glm::radians(0.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
	TR = glm::translate(TR, glm::vec3(0, -0.24, -0.075)); //--- x������ �̵� ���
	TR = glm::scale(TR, glm::vec3(0.01, 0.01, 0.01));
}

void Body::draw(GLuint vao, unsigned int modelLocation) {
	Body::transform();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��ȯ �� �����ϱ�
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 1000);
}

void Body::get_move(float amount_x, float amount_z, float* get_rad) {
	move_amount_x = amount_x;
	move_amount_z = amount_z;
	for (int i = 0; i < 3; ++i) {
		rad[i] = get_rad[i];
	}
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
		TR = glm::translate(TR, glm::vec3(-move_amount_x, 0, -move_amount_z)); //--- x������ �̵� ���
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR = glm::rotate(TR, glm::radians(-10.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR = glm::translate(TR, glm::vec3(-0.05, -0.18, -0.05)); //--- x������ �̵� ���
		TR = glm::rotate(TR, glm::radians(-rad[0]), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR = glm::scale(TR, glm::vec3(0.01, 0.01, 0.01));

	}
	else {
		TR = glm::translate(TR, glm::vec3(-move_amount_x, 0, -move_amount_z)); //--- x������ �̵� ���
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR = glm::rotate(TR, glm::radians(0.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR = glm::translate(TR, glm::vec3(0.04, -0.18, -0.05)); //--- x������ �̵� ���
		TR = glm::rotate(TR, glm::radians(rad[0]), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR = glm::scale(TR, glm::vec3(0.01, 0.01, 0.01));
	}
}

void Arm::draw(GLuint vao, unsigned int modelLocation) {
	Arm::transform();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��ȯ �� �����ϱ�
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 1000);
}

void Arm::get_move(float amount_x, float amount_z, float* get_rad) {
	move_amount_x = amount_x;
	move_amount_z = amount_z;
	for (int i = 0; i < 3; ++i) {
		rad[i] = get_rad[i];
	}
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
		TR = glm::translate(TR, glm::vec3(-move_amount_x, 0, -move_amount_z)); //--- x������ �̵� ���
		TR = glm::rotate(TR, glm::radians(10.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR = glm::translate(TR, glm::vec3(-0.02, -0.32, -0.08)); //--- x������ �̵� ���
		TR = glm::rotate(TR, glm::radians(rad[0] + 20), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR = glm::scale(TR, glm::vec3(0.01, 0.01, 0.01));
	}
	else {
		TR = glm::translate(TR, glm::vec3(-move_amount_x, 0, -move_amount_z)); //--- x������ �̵� ���
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR = glm::rotate(TR, glm::radians(-10.0f + rad[1]), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR = glm::translate(TR, glm::vec3(0.02, -0.32, -0.08)); //--- x������ �̵� ���
		TR = glm::rotate(TR, glm::radians(-rad[0] + 20), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR = glm::scale(TR, glm::vec3(0.01, 0.01, 0.01));

	}
}

void Leg::draw(GLuint vao, unsigned int modelLocation) {
	Leg::transform();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��ȯ �� �����ϱ�
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 850);
}

void Leg::get_move(float amount_x, float amount_z, float* get_rad) {
	move_amount_x = amount_x;
	move_amount_z = amount_z;
	for (int i = 0; i < 3; ++i) {
		rad[i] = get_rad[i];
	}
}

Human::Human() {
	right_arm.check_right(0);
	left_arm.check_right(1);
	right_leg.check_right(0);
	left_leg.check_right(1);
}

void Human::draw(GLuint head_vao, GLuint body_vao, GLuint right_arm_vao, GLuint left_arm_vao, GLuint right_leg_vao, GLuint left_leg_vao, unsigned int modelLocation) {
	head.draw(head_vao, modelLocation);
	body.draw(body_vao, modelLocation);
	right_arm.draw(right_arm_vao, modelLocation);
	left_arm.draw(left_arm_vao, modelLocation);
	right_leg.draw(right_leg_vao, modelLocation);
	left_leg.draw(left_leg_vao, modelLocation);
}

void Human::move(float amount_x, float amount_z, float* rad) {
	head.get_move(amount_x, amount_z, rad);
	body.get_move(amount_x, amount_z, rad);
	right_arm.get_move(amount_x, amount_z, rad);
	left_arm.get_move(amount_x, amount_z, rad);
	right_leg.get_move(amount_x, amount_z, rad);
	left_leg.get_move(amount_x, amount_z, rad);
}
