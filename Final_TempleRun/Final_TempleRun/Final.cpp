#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "Header.h"
#include "file_read.h"
#include "Human.h"
#include "stb_image.h"
#include "map.h"
#include "inc/fmod.hpp"
#include "inc/fmod_errors.h"
#pragma comment(lib, "fmod_vc.lib")

FMOD::System* ssystem;
FMOD::Sound* sound1, * sound2;
FMOD::Channel* channel = 0;
FMOD_RESULT result;
void* extradriverdata = 0;

random_device rd;
std::mt19937 dre(rd());
std::uniform_int_distribution<int> uid{ 0, 1 };

unsigned int head_vao, head_vbo[3];
unsigned int body_vao, body_vbo[3];
unsigned int left_arm_vao, left_arm_vbo[3];
unsigned int right_arm_vao, right_arm_vbo[3];
unsigned int left_leg_vao, left_leg_vbo[3];
unsigned int right_leg_vao, right_leg_vbo[3];

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
GLuint leg_texture;
GLuint road_texture[2];

/*OPGL관렴 함수*/
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Timer_event(int value);
void SpecialKeyboard(int key, int x, int y);
void specialKeyUpCallback(int key, int x, int y);

/*셰이더 관련 함수*/
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();

/*vao, vbo 관련 함수*/
void Initvbovao();
void InitTexture();
void Draw();

// player객체
Human player;
void turn_camera();

// map객체
Road road;
int delete_num = 0;
int map_dir = 0;

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
float ambient_amount = 0.5;

// 임시배경 큐브
GLuint vao, vbo[3];

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
	//glUniform3f(lightPosLocation, -move_character[0], 1, -1 - move_character[2]);
	glUniform3f(lightPosLocation, -1 - move_character[0], 1, -1 - move_character[2]);
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
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -5.0));
	projection = glm::rotate(projection, glm::radians(y_rad), glm::vec3(0.0, 1.0, 0.0));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	// 대략적인 조명 위치
	TR = glm::translate(TR, glm::vec3(-2 -move_character[0], 1, 1 -move_character[2]));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변환 값 적용하기
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// 맵 그리기
	glBindTexture(GL_TEXTURE_2D, road_texture[0]);
	for (int i = 0; i < roads.size(); ++i) {
		if(roads.at(i).return_dir() == 0 || roads.at(i).return_dir() == 2)
			glBindTexture(GL_TEXTURE_2D, road_texture[0]);
		else
			glBindTexture(GL_TEXTURE_2D, road_texture[1]);
		roads.at(i).draw(vao, modelLocation);
	}


	/*그리기*/
	glBindTexture(GL_TEXTURE_2D, leg_texture);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);

	Draw();
	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Timer_event(int value) {
	player.move(move_character, rad, is_slide);
	turn_camera();

	// 임시적으로 맵 생성
	if (roads.size() == 0) {
		for (int i = 0; i < 40; ++i) {
			roads.push_back(road);
			roads.at(i).select_pos(0, -i);
		}
	}

	if (delete_num >= 40) {
		if (uid(dre) == 0)
			map_dir += 1;
		else
			map_dir -= 1;
		if (map_dir == -1)
			map_dir = 3;
		else if (map_dir == 4)
			map_dir = 0;
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
					road.select_pos((roads.at(roads.size() - 1).return_pos())[0], (roads.at(roads.size() - 1).return_pos())[2] - 1); // 앞으로 생성
				else if (road.return_dir() == 2)
					road.select_pos((roads.at(roads.size() - 1).return_pos())[0], (roads.at(roads.size() - 1).return_pos())[2] + 1); // 앞으로 생성
				else if (road.return_dir() == 1)
					road.select_pos((roads.at(roads.size() - 1).return_pos())[0] + 1, (roads.at(roads.size() - 1).return_pos())[2]); // 오른쪽으로 생성
				else if (road.return_dir() == 3)
					road.select_pos((roads.at(roads.size() - 1).return_pos())[0] - 1, (roads.at(roads.size() - 1).return_pos())[2]); // 왼쪽으로 생성

				roads.push_back(road);
				roads.erase(roads.begin() + i);
			}
		}
	}

	// 게임 시작시 자동으로 이동
	if (game_start) {
		if (rad[0] >= 40)
			flip = true;
		else if (rad[0] <= -40)
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
			rad[0] -= 10;
		else if(!flip && !is_jump && !is_slide)
			rad[0] += 10;
		cout << "x: " << move_character[0] << '\n';
		cout << "z: " << move_character[2] << '\n';
	}

	// 점프
	if (is_jump) {
		if (jump_flip) {
			move_character[1] -= 0.2;
			if (move_character[1] <= 0) {
				move_character[1] = 0;
				jump_flip = false;
				is_jump = false;
				rad[0] = 40;
			}
		}
		else {
			move_character[1] += 0.2;
			if (move_character[1] >= 1)
				jump_flip = true;
			rad[0] = 80;
		}
	}
	move_character[1] -= 0.05;
	player.road_check(move_character);

	cameraPos.x = -move_character[0] + camera_dir[0];
	cameraPos.y = 1.5;
	cameraPos.z = -move_character[2] + camera_dir[2];
	cameraDirection.x = -move_character[0];
	cameraDirection.z = -move_character[2];
	glutPostRedisplay(); //--- 배경색이 바뀔 때마다 출력 콜백 함수를 호출하여 화면을 refresh 한다
	glutTimerFunc(100, Timer_event, 4);
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
				move_character[2] += 0.1;
				break;
			case -1:
			case 3:
				move_character[0] += 0.1;
				break;
			case 1: 
			case -3:
				move_character[0] -= 0.1;
				break;
			case 2:
			case -2:
				move_character[2] -= 0.1;
				break;
			}
			if (flip)
				rad[0] -= 5;
			else
				rad[0] += 5;
			cout << "z: " << move_character_z << '\n';
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
		}
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
		is_slide = true;
		rad[0] = -90;
	}
	else if (key == GLUT_KEY_UP) {
		if (is_jump == false)
			is_jump = true;
	}
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
	player.draw(head_vao, body_vao, right_arm_vao, left_arm_vao, right_leg_vao, left_leg_vao, modelLocation, leg_texture);
}

void InitTexture()
{
	int widthImage, heightImage, numberOfChannel;
	glGenTextures(1, &texture); //--- 텍스처 생성
	glBindTexture(GL_TEXTURE_2D, texture); //--- 텍스처 바인딩
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- 현재 바인딩된 텍스처의 파라미터 설정하기
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("image\\temp_city.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //---텍스처 이미지 정의

	glGenTextures(1, &leg_texture); //--- 텍스처 생성
	glBindTexture(GL_TEXTURE_2D, leg_texture); //--- 텍스처 바인딩
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- 현재 바인딩된 텍스처의 파라미터 설정하기
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("resource\\character\\leftleg.png", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //---텍스처 이미지 정의

	glGenTextures(2, road_texture); //--- 텍스처 생성
	glBindTexture(GL_TEXTURE_2D, road_texture[0]); //--- 텍스처 바인딩
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- 현재 바인딩된 텍스처의 파라미터 설정하기
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("image\\temp_road3.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //---텍스처 이미지 정의

	glBindTexture(GL_TEXTURE_2D, road_texture[1]); //--- 텍스처 바인딩
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- 현재 바인딩된 텍스처의 파라미터 설정하기
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("image\\temp_road3_horizon.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //---텍스처 이미지 정의
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
	Load_Object("resource\\character\\head.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);

	glGenVertexArrays(1, &head_vao);
	glGenBuffers(3, head_vbo);
	glBindVertexArray(head_vao);

	glBindBuffer(GL_ARRAY_BUFFER, head_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, head_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, head_vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	Load_Object("resource\\character\\body.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);

	glGenVertexArrays(1, &body_vao);
	glGenBuffers(3, body_vbo);
	glBindVertexArray(body_vao);

	glBindBuffer(GL_ARRAY_BUFFER, body_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, body_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, body_vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	Load_Object("resource\\character\\rightleg.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);

	glGenVertexArrays(1, &right_leg_vao);
	glGenBuffers(3, right_leg_vbo);
	glBindVertexArray(right_leg_vao);

	glBindBuffer(GL_ARRAY_BUFFER, right_leg_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, right_leg_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, right_leg_vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	Load_Object("resource\\character\\leftleg.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);

	glGenVertexArrays(1, &left_leg_vao);
	glGenBuffers(3, left_leg_vbo);
	glBindVertexArray(left_leg_vao);

	glBindBuffer(GL_ARRAY_BUFFER, left_leg_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, left_leg_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, left_leg_vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	Load_Object("resource\\character\\rightarm.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);

	glGenVertexArrays(1, &right_arm_vao);
	glGenBuffers(3, right_arm_vbo);
	glBindVertexArray(right_arm_vao);

	glBindBuffer(GL_ARRAY_BUFFER, right_arm_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, right_arm_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, right_arm_vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	Load_Object("resource\\character\\leftarm.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);

	glGenVertexArrays(1, &left_arm_vao);
	glGenBuffers(3, left_arm_vbo);
	glBindVertexArray(left_arm_vao);

	glBindBuffer(GL_ARRAY_BUFFER, left_arm_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, left_arm_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, left_arm_vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	Load_Object("resource\\cube.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	glGenVertexArrays(1, &vao);
	glGenBuffers(3, vbo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

}

                                                                                                        