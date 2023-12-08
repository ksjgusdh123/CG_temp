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

void Truck::set_pos(float x, float z, int num) {
	pos[0] = x;
	pos[1] = 0.13;
	pos[2] = z;
	flip = num;
}

void Truck::transform() {
	TR = glm::mat4(1.0f);
	TR = glm::translate(TR, glm::vec3(pos[0], pos[1], pos[2])); //--- xÃàÀ¸·Î ÀÌµ¿ Çà·Ä
	if (dir == 0) {
		if(flip)
			TR = glm::rotate(TR, glm::radians(0.f), glm::vec3(0, 1, 0));
		else
			TR = glm::rotate(TR, glm::radians(180.f), glm::vec3(0, 1, 0));
	}
	else if (dir == 1) {
		if(flip)
			TR = glm::rotate(TR, glm::radians(270.f), glm::vec3(0, 1, 0));
		else
			TR = glm::rotate(TR, glm::radians(90.f), glm::vec3(0, 1, 0));
	}
	else if (dir == 2) {
		if(flip)
			TR = glm::rotate(TR, glm::radians(180.f), glm::vec3(0, 1, 0));
		else
			TR = glm::rotate(TR, glm::radians(0.f), glm::vec3(0, 1, 0));
	}
	else if (dir == 3) {
		if(flip)
			TR = glm::rotate(TR, glm::radians(90.f), glm::vec3(0, 1, 0));
		else
			TR = glm::rotate(TR, glm::radians(270.f), glm::vec3(0, 1, 0));
	}

	TR = glm::scale(TR, glm::vec3(0.13, 0.12, 0.1));
}


void Truck::draw(GLuint vao, unsigned int modelLocation, GLuint texture) {
	Truck::transform();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform º¯¼ö¿¡ º¯È¯ °ª Àû¿ëÇÏ±â
	glDrawArrays(GL_TRIANGLES, 0, 3312);
}

bool Truck::collision(float* player_pos, Human& player) {

	float DOWN_SPEED = -0.0005 * player.get_speed() * 50;

	float temp_player_pos_x = round(player_pos[0] * -100) / 100;
	float temp_player_pos_z = round(player_pos[2] * -100) / 100;

	// Æ®·° ¹× ¹ÙÄû pos[0] - 1.2ºÎÅÍ Æ®·° Áß½É 0.5 Á¤µµ
	if (!is_collide) {
		if (dir == 0 && player.return_dir() == 0) {
			if (flip) {
				if ((temp_player_pos_z >= pos[2] - 0.5 && temp_player_pos_z <= pos[2] + 0.5) && ((temp_player_pos_x >= pos[0] - 1.2 && temp_player_pos_x <= pos[0] && !player.return_slide())
					|| (temp_player_pos_x < pos[0] - 1.2 || temp_player_pos_x > pos[0]))) {
					std::cout << "Á¢ÃË" << std::endl;
					is_collide = true;
					player.set_speed(DOWN_SPEED);
				}
			}
			else {
				if ((temp_player_pos_z >= pos[2] - 0.5 && temp_player_pos_z <= pos[2] + 0.5) && ((temp_player_pos_x <= pos[0] + 1.2 && temp_player_pos_x >= pos[0] && !player.return_slide())
					|| (temp_player_pos_x > pos[0] + 1.2 || temp_player_pos_x < pos[0]))) {
					std::cout << "Á¢ÃË" << std::endl;
					is_collide = true;
					player.set_speed(DOWN_SPEED);
				}
			}
		}
		else if (dir == 1 && (player.return_dir() == 1 || player.return_dir() == -3)) {
			if (flip) {
				if ((temp_player_pos_x >= pos[0] - 0.5 && temp_player_pos_x <= pos[0] + 0.5) && ((temp_player_pos_z >= pos[2] - 1.2 && temp_player_pos_z <= pos[2] && !player.return_slide())
					|| (temp_player_pos_z < pos[2] - 1.2 || temp_player_pos_z > pos[2]))) {
					std::cout << "Á¢ÃË2" << std::endl;
					is_collide = true;
					player.set_speed(DOWN_SPEED);
				}
			}
			else {
				if ((temp_player_pos_x >= pos[0] - 0.5 && temp_player_pos_x <= pos[0] + 0.5) && ((temp_player_pos_z <= pos[2] + 1.2 && temp_player_pos_z >= pos[2] && !player.return_slide())
					|| (temp_player_pos_z > pos[2] + 1.2 || temp_player_pos_z < pos[2]))) {
					std::cout << "Á¢ÃË2" << std::endl;
					is_collide = true;
					player.set_speed(DOWN_SPEED);
				}
			}
		}
		else if (dir == 2 && (player.return_dir() == 2 || player.return_dir() == -2)) {
			if (flip) {
				if ((temp_player_pos_z >= pos[2] - 0.5 && temp_player_pos_z <= pos[2] + 0.5) && ((temp_player_pos_x <= pos[0] + 1.2 && temp_player_pos_x >= pos[0] && !player.return_slide())
					|| (temp_player_pos_x > pos[0] + 1.2 || temp_player_pos_x < pos[0]))) {
					std::cout << "Á¢ÃË3" << std::endl;
					is_collide = true;
					player.set_speed(DOWN_SPEED);
				}
			}
			else {
				if ((temp_player_pos_z >= pos[2] - 0.5 && temp_player_pos_z <= pos[2] + 0.5) && ((temp_player_pos_x >= pos[0] - 1.2 && temp_player_pos_x <= pos[0] && !player.return_slide())
					|| (temp_player_pos_x < pos[0] - 1.2 || temp_player_pos_x > pos[0]))) {
					std::cout << "Á¢ÃË3" << std::endl;
					is_collide = true;
					player.set_speed(DOWN_SPEED);
				}
			}
		}
		else if (dir == 3 && (player.return_dir() == -1 || player.return_dir() == 3)) {
			if (flip) {
				if ((temp_player_pos_x >= pos[0] - 0.5 && temp_player_pos_x <= pos[0] + 0.5) && ((temp_player_pos_z <= pos[2] + 1.2 && temp_player_pos_z >= pos[2] && !player.return_slide())
					|| (temp_player_pos_z > pos[2] + 1.2 || temp_player_pos_z < pos[2]))) {
					std::cout << "Á¢ÃË4" << std::endl;
					is_collide = true;
					player.set_speed(DOWN_SPEED);
				}
			}
			else {
				if ((temp_player_pos_x >= pos[0] - 0.5 && temp_player_pos_x <= pos[0] + 0.5) && ((temp_player_pos_z >= pos[2] - 1.2 && temp_player_pos_z <= pos[2] && !player.return_slide())
					|| (temp_player_pos_z < pos[2] - 1.2 || temp_player_pos_z > pos[2]))) {
					std::cout << "Á¢ÃË4" << std::endl;
					is_collide = true;
					player.set_speed(DOWN_SPEED);
				}
			}
		}
		return is_collide;
	}
	return false;
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

void Hurdle::set_pos(float x, float z, int num) {
	flip = num;
	if (dir == 0 || dir == 2) {
		if (num)
			pos[0] = x + 0.75;
		else
			pos[0] = x - 0.75;
	}
	else
		pos[0] = x;
	pos[1] = -0.70;
	if (dir == 1 || dir == 3) {
		if (num)
			pos[2] = z + 0.75;
		else
			pos[2] = z - 0.75;
	}
	else 
		pos[2] = z;
}

void Hurdle::transform() {
	TR = glm::mat4(1.0f);
	TR = glm::translate(TR, glm::vec3(pos[0], pos[1], pos[2])); //--- xÃàÀ¸·Î ÀÌµ¿ Çà·Ä
	if (dir == 0)
		TR = glm::rotate(TR, glm::radians(180.f), glm::vec3(0, 1, 0));
	else if (dir == 1)
		TR = glm::rotate(TR, glm::radians(450.f), glm::vec3(0, 1, 0));
	else if (dir == 2)
		TR = glm::rotate(TR, glm::radians(360.f), glm::vec3(0, 1, 0));
	else if (dir == 3)
		TR = glm::rotate(TR, glm::radians(270.f), glm::vec3(0, 1, 0));
	TR = glm::scale(TR, glm::vec3(0.1, 0.05, 0.2));

}

bool Hurdle::collision(float* player_pos, Human& player) {
	float temp_player_pos_x = round(player_pos[0] * -100) / 100;
	float temp_player_pos_z = round(player_pos[2] * -100) / 100;

	float DOWN_SPEED = -0.0005 * player.get_speed() * 20;


	if (!is_collide) {
		if (dir == 0 && player.return_dir() == 0) {
			if (flip) {
				if ((temp_player_pos_z >= pos[2] - 0.5 && temp_player_pos_z <= pos[2] + 0.5) && (player_pos[0] < pos[0] - 0.75 && !player.return_jump())) {
					std::cout << "Á¢ÃËhurdle" << std::endl;
					is_collide = true;
					player.set_speed(DOWN_SPEED);
				}
			}
			else {
				if ((temp_player_pos_z >= pos[2] - 0.5 && temp_player_pos_z <= pos[2] + 0.5) && (player_pos[0] > pos[0] + 0.75 && !player.return_jump())) {
					std::cout << "Á¢ÃËhurdle" << std::endl;
					is_collide = true;
					player.set_speed(DOWN_SPEED);
				}
			}
		}
		else if (dir == 1 && (player.return_dir() == 1 || player.return_dir() == -3)) {
			if (flip) {
				if ((temp_player_pos_x >= pos[0] - 0.5 && temp_player_pos_x <= pos[0] + 0.5) && (temp_player_pos_z > pos[2] - 0.75 && !player.return_jump())) {
					std::cout << "Á¢ÃË2hurdlef" << std::endl;
					is_collide = true;
					player.set_speed(DOWN_SPEED);
				}
			}
			else {
				if ((temp_player_pos_x >= pos[0] - 0.5 && temp_player_pos_x <= pos[0] + 0.5) && (temp_player_pos_z < pos[2] + 0.75 && !player.return_jump())) {
					std::cout << "Á¢ÃË2hurdle" << std::endl;
					is_collide = true;
					player.set_speed(DOWN_SPEED);
				}
			}
		}
		else if (dir == 2 && (player.return_dir() == 2 || player.return_dir() == -2)) {
			if (flip) {
				if ((temp_player_pos_z >= pos[2] - 0.5 && temp_player_pos_z <= pos[2] + 0.5) && (temp_player_pos_x > pos[0] - 0.75 && !player.return_jump())) {
					std::cout << "Á¢ÃË3hurdle" << std::endl;
					is_collide = true;
					player.set_speed(DOWN_SPEED);
				}
			}
			else {
				if ((temp_player_pos_z >= pos[2] - 0.5 && temp_player_pos_z <= pos[2] + 0.5) && (temp_player_pos_x < pos[0] + 0.75 && !player.return_jump())) {
					std::cout << "Á¢ÃË3hurdlef" << std::endl;
					is_collide = true;
					player.set_speed(DOWN_SPEED);
				}
			}
		}
		else if (dir == 3 && (player.return_dir() == -1 || player.return_dir() == 3)) {
			if (flip) {
				if ((temp_player_pos_x >= pos[0] - 0.5 && temp_player_pos_x <= pos[0] + 0.5) && (temp_player_pos_z > pos[2] - 0.75 && !player.return_jump())) {
					std::cout << "Á¢ÃË4hurdlef" << std::endl;
					is_collide = true;
					player.set_speed(DOWN_SPEED);
				}
			}
			else {
				if ((temp_player_pos_x >= pos[0] - 0.5 && temp_player_pos_x <= pos[0] + 0.5) && (temp_player_pos_z < pos[2] + 0.75 && !player.return_jump())) {
					std::cout << "Á¢ÃË4hurdle" << std::endl;
					is_collide = true;
					player.set_speed(DOWN_SPEED);
				}
			}
		}
		return is_collide;
	}
	return false;
}

void Hurdle::draw(GLuint vao, unsigned int modelLocation, GLuint texture) {
	Hurdle::transform();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform º¯¼ö¿¡ º¯È¯ °ª Àû¿ëÇÏ±â
	glDrawArrays(GL_TRIANGLES, 0, 2568);
}