#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "Header.h"
#include "file_read.h"
#include "Human.h"
#include "stb_image.h"
#include "map.h"
#include "obstacle.h"
#include "wall.h"
#include "inc/fmod.hpp"
#include "inc/fmod_errors.h"
#pragma comment(lib, "fmod_vc.lib")

// FMOD
FMOD::System* ssystem;
FMOD::Sound* sound1, * sound2;
FMOD::Channel* channel = 0;
FMOD_RESULT result;
void* extradriverdata = 0;

// random 엔진
random_device rd;
std::mt19937 dre(rd());
std::uniform_int_distribution<int> uid{ 0, 1 };
std::uniform_int_distribution<int> rand_ob{ 10, 70 };

unsigned int head_vao, head_vbo[3];
unsigned int truck_vao, truck_vbo[3];
unsigned int hurdle_vao, hurdle_vbo[3];
unsigned int body_vao, body_vbo[3];
unsigned int left_arm_vao, left_arm_vbo[3];
unsigned int right_arm_vao, right_arm_vbo[3];
unsigned int left_leg_vao, left_leg_vbo[3];
unsigned int right_leg_vao, right_leg_vbo[3];
unsigned int apart_vao, apart_vbo[3];
unsigned int road_vao, road_vbo[3];
unsigned int police_head_vao, police_head_vbo[3];
unsigned int police_body_vao, police_body_vbo[3];
unsigned int police_left_arm_vao, police_left_arm_vbo[3];
unsigned int police_right_arm_vao, police_right_arm_vbo[3];
unsigned int police_left_leg_vao, police_left_leg_vbo[3];
unsigned int police_right_leg_vao, police_right_leg_vbo[3];

std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

std::vector< glm::vec3 > vertices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals;

std::vector< glm::vec3 > temp_vertices;
std::vector< glm::vec2 > temp_uvs;
std::vector< glm::vec3 > temp_normals;


glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 2.0f); //--- 카메라 위치
glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향

GLfloat radius = 0.1f;
GLfloat rColor = 10, gColor = 10, bColor = 10;

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;
GLchar* vertexSource, * fragmentSource;
GLuint texture;
GLuint thief_texture;
GLuint road_texture;
GLuint road_texture_horizon;
GLuint apart_horizon;

/*OPGL관렴 함수*/
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Timer_event(int value);
void SpecialKeyboard(int key, int x, int y);
void specialKeyUpCallback(int key, int x, int y);
void KeyUpCallback(unsigned char key, int x, int y);

// 텍스처 관련 함수
void init_texture_file(GLuint& texture, const char* file);
void InitTexture();


/*셰이더 관련 함수*/
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();

/*vao, vbo 관련 함수*/
void Initvbovao();
void Draw();
void gen_vao(GLuint& vao, GLuint* vbo);

// player객체
Human player;
void turn_camera();

// police 객체
Police police;

// map객체
Road road;
int delete_num = 0;
int map_dir = 0;
float MAP_SIZE = 40;

// 사운드
void sound_init();


// 키입력 객체
float y_rad = 0;
float move_character[3] = { 0 };
float move_character_z = 0;
float move_character_x = 0;
float rad[3]{ 0, 540, 0 };
int camera_dir[3]{0, 0, 5};
bool flip = false;
bool interupt = false;
int temp_rad = 0;
bool is_a_button = false;
bool is_jump = false;
bool jump_flip = false;
bool game_start = false;
bool is_slide = false;
float ambient_amount = 1;
bool space = false;

// 임시배경 큐브
GLuint vao, vbo[3];

// 카메라 각도 임시 조작
float camera[3]{ 0 };



int main(int argc, char** argv) {
	srand(time(NULL));
	result = FMOD::System_Create(&ssystem);
	glutInit(&argc, argv);
	width = 800, height = 600;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Cube");
	glewExperimental = GL_TRUE;
	glewInit();

	/*초기화 함수*/
	make_shaderProgram();
	sound_init();
	Initvbovao();
	InitTexture();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutSpecialUpFunc(specialKeyUpCallback);
	glutKeyboardUpFunc(KeyUpCallback);

	channel->stop();
	channel->setVolume(1.0);
	ssystem->update();
	//ssystem->playSound(sound1, 0, false, &channel);
	glutTimerFunc(100, Timer_event, 4);
	glutMainLoop();

	return 0;
}

void sound_init() {
	ssystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	ssystem->createSound("sound\\main_bgm.mp3", FMOD_LOOP_NORMAL, 0, &sound1);
	ssystem->update();
}

GLvoid drawScene() {
	glClearColor(rColor, gColor, bColor, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);
	glUseProgram(shaderProgramID);

	unsigned int lightPosLocation = glGetUniformLocation(shaderProgramID, "lightPos");
	
	switch (player.return_dir()) {
	case 0:
		glUniform3f(lightPosLocation, -move_character[0], 0, -2 - move_character[2]);
		break;
	case 1:
	case -3:
		glUniform3f(lightPosLocation, 2 -move_character[0], 0, - move_character[2]);
		break;
	case 2:
	case -2:
		glUniform3f(lightPosLocation, -move_character[0], 0, 2 - move_character[2]);
		break;
	case 3:
	case -1:
		glUniform3f(lightPosLocation, -2 - move_character[0], 0, -move_character[2]);
		break;
	}
	unsigned int lightColorLocation = glGetUniformLocation(shaderProgramID, "lightColor");
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);
	unsigned int objColorLocation = glGetUniformLocation(shaderProgramID, "objectColor");
	glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
	unsigned int viewPosLocation = glGetUniformLocation(shaderProgramID, "viewPos"); //--- viewPos 값 전달: 카메라 위치
	glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);
	unsigned int ambient = glGetUniformLocation(shaderProgramID, "ambientLight"); //--- viewPos 값 전달: 카메라 위치
	glUniform1f(ambient, ambient_amount);

	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 temp_back_ground = glm::mat4(1.0f);
	unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "viewTransform"); //--- 뷰잉 변환 설정
	unsigned int projectionLocation = glGetUniformLocation(shaderProgramID, "projectionTransform"); //--- 투영 변환 값 설정
	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "transform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	// 임시 배경
	glDisable(GL_DEPTH_TEST);
	temp_back_ground = glm::translate(temp_back_ground, glm::vec3(0, 0, -2));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(temp_back_ground)); //--- modelTransform 변수에 변환 값 적용하기
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 12, 6);

	glEnable(GL_DEPTH_TEST);

	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	projection = glm::perspective(glm::radians(30.0f), 1.0f, 0.1f, 50.0f);
	projection = glm::translate(projection, glm::vec3(0.0 + camera[0], 0.0 + camera[1], -5.0 + camera[2]));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	// 대략적인 조명 위치
	//TR = glm::translate(TR, glm::vec3(-2 -move_character[0], 1, 1 -move_character[2]));
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	//glBindVertexArray(vao);
	//glDrawArrays(GL_TRIANGLES, 0, 36);

	//TR = glm::mat4(1.0f);
	//TR = glm::translate(TR, glm::vec3(0, 2, -14));
	//TR = glm::scale(TR, glm::vec3(0.1, 0.1, 0.1));
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	//glBindVertexArray(truck_vao);
	//glDrawArrays(GL_TRIANGLES, 0, 3312);


	// 맵 그리기
	for (int i = 0; i < roads.size(); ++i) {
		if(roads.at(i).return_dir() == 0 || roads.at(i).return_dir() == 2)
			glBindTexture(GL_TEXTURE_2D, road_texture);
		else
			glBindTexture(GL_TEXTURE_2D, road_texture_horizon);
		roads.at(i).draw(road_vao, modelLocation);
	}

	//장애물 그리기
	for (int i = 0; i < ob.size(); ++i) {
		if(dynamic_cast<Hurdle*>(ob[i]))
			glBindVertexArray(hurdle_vao);
		else
			glBindVertexArray(truck_vao);
		ob.at(i)->draw(truck_vao, modelLocation, texture);
	}
	/* 사람 그리기 */
	glBindTexture(GL_TEXTURE_2D, thief_texture);
	Draw(); // 사람을 그리는 함수

	/* 아파트 그리기 */
	glBindTexture(GL_TEXTURE_2D, thief_texture);
	for (int i = 0; i < building.size(); ++i) {
		if (building.at(i)->return_dir() != player.return_dir()) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		building.at(i)->draw(apart_vao, modelLocation); // 아파트를 반투명하게 그림
	}

	glDisable(GL_BLEND);

	glutSwapBuffers(); //--- 화면에 출력하기

}

GLvoid Timer_event(int value) {
	player.move(move_character, rad, is_slide);
	police.move(move_character, rad, is_slide);
	turn_camera();
	police.move(player);
	// 임시적으로 맵 생성
	if (roads.size() == 0) {
		for (int i = 0; i < 40; ++i) {
			roads.push_back(road);
			roads.at(i).select_pos(0, -i * 4);
		}
		for (int i = 0; i < 5; ++i) {
			if (uid(dre) == 0)
				ob.push_back(new Truck);
			else
				ob.push_back(new Hurdle);
			ob.at(i)->set_pos(0, -10 + i * -20, uid(dre));
		}
		/*for (int i = 0; i < 189; ++i) {
			building.push_back(new Apart);
			if(i != 188)
				building.at(i)->select_pos(0, -i, i);
		}*/
	}

	if (delete_num >= MAP_SIZE) {
		if (uid(dre) == 0)
			map_dir += 1;
		else
			map_dir -= 1;
		if (map_dir == -1)
			map_dir = 3;
		else if (map_dir == 4)
			map_dir = 0;
		roads.at(roads.size() - 1).set_cross(map_dir);
		int temp_ob_num = ob.size();
		for (int i = temp_ob_num; i < 5 + temp_ob_num; ++i) {
			if (uid(dre) == 0)
				ob.push_back(new Truck);
			else
				ob.push_back(new Hurdle);

			ob.at(i)->select_dir(map_dir);
			if(map_dir == 0)
				ob.at(i)->set_pos((roads.at(roads.size() - 1).return_pos())[0], (roads.at(roads.size() - 1).return_pos())[2] - max(30 * (i - temp_ob_num), 20), uid(dre));
			else if(map_dir == 1)
				ob.at(i)->set_pos((roads.at(roads.size() - 1).return_pos())[0] + max(30 * (i - temp_ob_num), 20), (roads.at(roads.size() - 1).return_pos())[2], uid(dre));
			else if(map_dir == 2)
				ob.at(i)->set_pos((roads.at(roads.size() - 1).return_pos())[0], (roads.at(roads.size() - 1).return_pos())[2] + max(30 * (i - temp_ob_num), 20), uid(dre));
			else if(map_dir == 3)
				ob.at(i)->set_pos((roads.at(roads.size() - 1).return_pos())[0] - max(30 * (i - temp_ob_num), 20), (roads.at(roads.size() - 1).return_pos())[2], uid(dre));
		}
		delete_num = 0;
	}

	// 도로 삭제 검사
	if (roads.size() != 0) {
		for (int i = 0; i < roads.size(); ++i) {
			roads.at(i).player_distance(move_character, camera_dir);
		}
		for (int i = 0; i < roads.size(); ++i) {
			if (roads.at(i).return_is_delete()) {
				++delete_num;
				road.select_dir(map_dir);
				if(road.return_dir() == 0)
					road.select_pos((roads.at(roads.size() - 1).return_pos())[0], (roads.at(roads.size() - 1).return_pos())[2] - 4); // 앞으로 생성
				else if (road.return_dir() == 2)
					road.select_pos((roads.at(roads.size() - 1).return_pos())[0], (roads.at(roads.size() - 1).return_pos())[2] + 4); // 앞으로 생성
				else if (road.return_dir() == 1)
					road.select_pos((roads.at(roads.size() - 1).return_pos())[0] + 4, (roads.at(roads.size() - 1).return_pos())[2]); // 오른쪽으로 생성
				else if (road.return_dir() == 3)
					road.select_pos((roads.at(roads.size() - 1).return_pos())[0] - 4, (roads.at(roads.size() - 1).return_pos())[2]); // 왼쪽으로 생성

				roads.push_back(road);
				roads.erase(roads.begin() + i);
				--i;
				if (delete_num >= 40) break;
			}
		}
	}

	// 장애물 삭제 검사
	if (ob.size() != 0) {
		for (int i = 0; i < ob.size(); ++i) {
			ob.at(i)->player_distance(move_character);
		}
		for (int i = 0; i < ob.size(); ++i) {
			if (ob.at(i)->return_delete()) {
				delete ob[i];
				ob.erase(ob.begin() + i);
			}
		}
	}

	// 건물 삭제 검사
	/*for (int i = 0; i < building.size(); ++i) {
		building.at(i)->player_distance(move_character);
	}
	for (int i = 0; i < building.size(); ++i) {
		if (building.at(i)->return_delete()) {
			delete building[i];
			building.erase(building.begin() + i);
		}
	}*/

	// 충돌체크
	for (int i = 0; i < ob.size(); ++i) {
		ob.at(i)->collision(move_character, player);
	}

	// 게임 시작시 자동으로 이동
	if (game_start) {
		if (rad[0] >= 60)
			flip = true;
		else if (rad[0] <= -60)
			flip = false;
		switch (player.return_dir()) {
		case 0:
			move_character[2] += player.get_speed();
			break;
		case -1:
		case 3:
			move_character[0] += player.get_speed();
			break;
		case 1:
		case -3:
			move_character[0] -= player.get_speed();
			break;
		case 2:
		case -2:
			move_character[2] -= player.get_speed();
			break;
		}    
		 
		if (flip && !is_jump && !is_slide)
			rad[0] -= 2;
		else if(!flip && !is_jump && !is_slide)
			rad[0] += 2;
	}

	// 점프
	if (is_jump) {
		if (jump_flip) {
			if (player.road_check(move_character)) {
				move_character[1] = 0;
				player.set_jump(false);
				jump_flip = false;
				is_jump = false;
				rad[0] = 40;
			}
			move_character[1] += 0;
		}
		else {
			move_character[1] += 0.09;
			if (move_character[1] >= 1)
				jump_flip = true;
			rad[0] = 80;
		}
	}


	if (space) {
		if (player.return_light() > 0) {
			if (ambient_amount < 0.5)
				ambient_amount += 0.005;
			player.set_light(-0.05);
		}
		else {
			ambient_amount = 0;
			space = false;
		}
		std::cout << player.return_light() << std::endl;
	}
	else if (!space) {
		if (player.return_light() < 100) {
			player.set_light(0.01);
		}
	}
	move_character[1] -= 0.05;
	player.road_check(move_character);
	player.position_setting(move_character);
	cameraPos.x = -move_character[0] + camera_dir[0];
	cameraPos.y = 1.5;
	cameraPos.z = -move_character[2] + camera_dir[2];
	cameraDirection.x = -move_character[0];
	cameraDirection.z = -move_character[2];
	glutPostRedisplay(); //--- 배경색이 바뀔 때마다 출력 콜백 함수를 호출하여 화면을 refresh 한다
	glutTimerFunc(10, Timer_event, 4);
}

GLvoid Keyboard(unsigned char key, int x, int y) {
	if (!interupt) {
		switch (key) {
		case '-':
			if (ambient_amount > 0.1)
				ambient_amount -= 0.1;
			break;
		case '+':
			if (ambient_amount < 1)
				ambient_amount += 0.1;
			break;
		case 'p':
			game_start = true;
			break;
		case 'w':
			if (rad[0] >= 90)
				flip = true;
			else if (rad[0] <= -90)
				flip = false;
			switch (player.return_dir()) {
			case 0:
				move_character[2] += 0.8;
				break;
			case -1:
			case 3:
				move_character[0] += 0.8;
				break;
			case 1: 
			case -3:
				move_character[0] -= 0.8;
				break;
			case 2:
			case -2:
				move_character[2] -= 0.8;
				break;
			}
			if (flip)
				rad[0] -= 5;
			else
				rad[0] += 5;
			break;
		case 'W':
			if (rad[0] >= 90)
				flip = true;
			else if (rad[0] <= -90)
				flip = false;
			switch (player.return_dir()) {
			case 0:
				move_character[2] += 8;
				break;
			case -1:
			case 3:
				move_character[0] += 8;
				break;
			case 1:
			case -3:
				move_character[0] -= 8;
				break;
			case 2:
			case -2:
				move_character[2] -= 8;
				break;
			}
			if (flip)
				rad[0] -= 5;
			else
				rad[0] += 5;
			break;
		case 's':
			move_character[2] -= 0.1;
			move_character_z -= 0.1;
			break;
		case 'a':
			player.turn(1);
			temp_rad = rad[1];
			is_a_button = true;
			interupt = true;
			break;
		case 'd':
			player.turn(0);
			temp_rad = rad[1];
			is_a_button = false;
			interupt = true;
			break;
		case 'y':
			rad[1] += 10;
			break;
		case 'Y':
			rad[1] -= 10;
			break;
		case 'z':
			y_rad += 10;
			break;
		case 'Z':
			y_rad -= 10;
			break;
		case 't':
			camera[1] += 0.1;
			break;
		case 'T':
			camera[1] -= 0.1;
			break;
		case 'k':
			player.set_speed(0.01);
			police.set_speed(0.01);
			break;
		case ' ':
			if(player.return_light() > 0)
				space = true;
			break;
		}
	}

}

void KeyUpCallback(unsigned char key, int x, int y) {
	if (key == ' ') {
		space = false;
		ambient_amount = 0;
	}
}

void SpecialKeyboard(int key, int x, int y) {
	if (key == GLUT_KEY_RIGHT) {
		switch (player.return_dir()) {
		case 0:
			move_character[0] -= 0.1;
			break;
		case -1:
		case 3:
			move_character[2] += 0.1;
			break;
		case 1:
		case -3:
			move_character[2] -= 0.1;
			break;
		case 2:
		case -2:
			move_character[0] += 0.1;
			break;
		}
	}
	else if (key == GLUT_KEY_LEFT) {
		switch (player.return_dir()) {
		case 0:
			move_character[0] += 0.1;
			break;
		case -1:
		case 3:
			move_character[2] -= 0.1;
			break;
		case 1:
		case -3:
			move_character[2] += 0.1;
			break;
		case 2:
		case -2:
			move_character[0] -= 0.1;
			break;
		}
	}
	else if (key == GLUT_KEY_DOWN) {
		if (!is_jump) {
			is_slide = true;
			rad[0] = -90;
		}
	}
	else if (key == GLUT_KEY_UP) {
		if (is_jump == false) {
			is_jump = true;
			player.set_jump(true);
		}
	}
	player.position_setting(move_character);
}

void specialKeyUpCallback(int key, int x, int y) {
	if (key == GLUT_KEY_DOWN) {
		is_slide = false;
		rad[0] = 0;
	}
}


void Draw() {
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "transform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	player.draw(head_vao, body_vao, right_arm_vao, left_arm_vao, right_leg_vao, left_leg_vao, modelLocation, thief_texture);
	glBindTexture(GL_TEXTURE_2D, texture); //--- 텍스처 바인딩
	police.draw(police_head_vao, police_body_vao, police_right_arm_vao, police_left_arm_vao, police_right_leg_vao, police_left_leg_vao, modelLocation, thief_texture);
	
}

void InitTexture()
{
	init_texture_file(texture, "image\\temp_city.jpg");
	init_texture_file(thief_texture, "resource\\texture\\thief\\thief_head.png");
	init_texture_file(road_texture, "image\\temp_road3.jpg");
	init_texture_file(road_texture_horizon, "image\\temp_road3_horizon.jpg");
}


GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void make_shaderProgram()
{
	make_vertexShaders(); //--- 버텍스 세이더 만들기
	make_fragmentShaders(); //--- 프래그먼트 세이더 만들기
	//-- shader Program
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);
	//--- 세이더 삭제하기
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program 사용하기
	glUseProgram(shaderProgramID);
}

void make_vertexShaders()
{
	vertexSource = filetobuf("vertex.glsl");
	//--- 버텍스 세이더 객체 만들기
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	//--- 버텍스 세이더 컴파일하기
	glCompileShader(vertexShader);
	//--- 컴파일이 제대로 되지 않은 경우: 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

void make_fragmentShaders()
{
	fragmentSource = filetobuf("fragment.glsl");
	//--- 프래그먼트 세이더 객체 만들기
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	//--- 프래그먼트 세이더 컴파일
	glCompileShader(fragmentShader);
	//--- 컴파일이 제대로 되지 않은 경우: 컴파일 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

void turn_camera() {
	if (is_a_button) {
		switch (player.return_dir()) {
		case 0:
			if (rad[1] < temp_rad + 90 and interupt) {
				camera_dir[0] += 1;
				camera_dir[2] += 1;
				rad[1] += 18;
			}
			else {
				interupt = false;
				rad[1] = 540;
			}
			break;
		case -1:
			if (rad[1] < temp_rad + 90 and interupt) {
				camera_dir[0] += 1;
				camera_dir[2] -= 1;
				rad[1] += 18;
			}
			else {
				interupt = false;
			}
			break;
		case -2:
		case 2:
			if (rad[1] < temp_rad + 90 and interupt) {
				camera_dir[0] -= 1;
				camera_dir[2] -= 1;
				rad[1] += 18;
			}
			else {
				interupt = false;
			}
			break;
		case -3:
		case 1:
			if (rad[1] < temp_rad + 90 and interupt) {
				camera_dir[0] -= 1;
				camera_dir[2] += 1;
				rad[1] += 18;
			}
			else {
				interupt = false;
			}
			break;
		}
	}
	else {
		switch (player.return_dir()) {
		case 0:
			if (rad[1] > temp_rad - 90 and interupt) {
				camera_dir[0] -= 1;
				camera_dir[2] += 1;
				rad[1] -= 18;
			}
			else {
				interupt = false;
				rad[1] = 540;
			}
			break;
		case 1:
			if (rad[1] > temp_rad - 90 and interupt) {
				camera_dir[0] -= 1;
				camera_dir[2] -= 1;
				rad[1] -= 18;
			}
			else {
				interupt = false;
			}
			break;
		case 2:
		case -2:
			if (rad[1] > temp_rad - 90 and interupt) {
				camera_dir[0] += 1;
				camera_dir[2] -= 1;
				rad[1] -= 18;
			}
			else {
				interupt = false;
			}
			break;
		case 3:
		case -1:
			if (rad[1] > temp_rad - 90 and interupt) {
				camera_dir[0] += 1;
				camera_dir[2] += 1;
				rad[1] -= 18;
			}
			else {
				interupt = false;
			}
			break;
		}
	}
}

void Initvbovao()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	//머리
	Load_Object("resource\\character\\thief_head.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	gen_vao(head_vao, head_vbo);

	Load_Object("resource\\character\\thief_body.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	gen_vao(body_vao, body_vbo);

	Load_Object("resource\\character\\thief_rightleg.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	gen_vao(right_leg_vao, right_leg_vbo);

	Load_Object("resource\\character\\thief_leftleg.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	gen_vao(left_leg_vao, left_leg_vbo);

	Load_Object("resource\\character\\thief_rightarm.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	gen_vao(right_arm_vao, right_arm_vbo);

	Load_Object("resource\\character\\thief_leftarm.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	gen_vao(left_arm_vao, left_arm_vbo);

	Load_Object("resource\\ob\\road.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	gen_vao(road_vao, road_vbo);

	Load_Object("resource\\cube.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	gen_vao(vao, vbo);

	Load_Object("resource\\ob\\truck.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	gen_vao(truck_vao, truck_vbo);

	Load_Object("resource\\ob\\fence.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	gen_vao(hurdle_vao, hurdle_vbo);

	Load_Object("resource\\ob\\apart.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	gen_vao(apart_vao, apart_vbo);

	Load_Object("resource\\police\\police_head.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	gen_vao(police_head_vao, police_head_vbo);

	Load_Object("resource\\police\\police_body.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	gen_vao(police_body_vao, police_body_vbo);

	Load_Object("resource\\police\\police_rightleg.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	gen_vao(police_right_leg_vao, police_right_leg_vbo);

	Load_Object("resource\\police\\police_leftleg.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	gen_vao(police_left_leg_vao, police_left_leg_vbo);

	Load_Object("resource\\police\\police_rightarm.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	gen_vao(police_right_arm_vao, police_right_arm_vbo);

	Load_Object("resource\\police\\police_leftarm.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	gen_vao(police_left_arm_vao, police_left_arm_vbo);
}

// texture 파일 자동 읽기
void init_texture_file(GLuint& texture, const char* file) {
	int widthImage, heightImage, numberOfChannel;
	glGenTextures(1, &texture); //--- 텍스처 생성
	glBindTexture(GL_TEXTURE_2D, texture); //--- 텍스처 바인딩
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- 현재 바인딩된 텍스처의 파라미터 설정하기
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(file, &widthImage, &heightImage, &numberOfChannel, 0);
	if(numberOfChannel == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //---텍스처 이미지 정의
	else if(numberOfChannel == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, 4, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //---텍스처 이미지 정의
}

// vao 생성 자동화
void gen_vao(GLuint& fvao, GLuint* fvbo) {
	glGenVertexArrays(1, &fvao);
	glGenBuffers(3, fvbo);
	glBindVertexArray(fvao);

	glBindBuffer(GL_ARRAY_BUFFER, fvbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, fvbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, fvbo[2]);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

}

                                                                                                        