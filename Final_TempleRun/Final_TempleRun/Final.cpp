#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include "file_read.h"
#include "Human.h"

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


glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 2.0f); //--- ī�޶� ��ġ
glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- ī�޶� �ٶ󺸴� ����
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����

GLfloat radius = 0.1f;
GLfloat rColor = 10, gColor = 10, bColor = 10;

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;
GLchar* vertexSource, * fragmentSource;

/*OPGL���� �Լ�*/
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Timer_event(int value);

/*���̴� ���� �Լ�*/
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();

/*vao, vbo ���� �Լ�*/
void Initvbovao();
void Draw();

// player��ü
Human player;

// Ű�Է� ��ü
float y_rad = 0;
float move_character_z = 0;
float move_character_x = 0;
float rad[3]{ 0 };
bool flip = false;

int main(int argc, char** argv) {

	srand(time(NULL));

	glutInit(&argc, argv);
	width = 800, height = 600;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Cube");
	glewExperimental = GL_TRUE;
	glewInit();

	/*�ʱ�ȭ �Լ�*/
	make_shaderProgram();
	Initvbovao();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, Timer_event, 4);
	glutMainLoop();

	return 0;
}

GLvoid drawScene() {
	glClearColor(rColor, gColor, bColor, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glUseProgram(shaderProgramID);

	unsigned int lightPosLocation = glGetUniformLocation(shaderProgramID, "lightPos");
	glUniform3f(lightPosLocation, 10, 0, 0);
	unsigned int lightColorLocation = glGetUniformLocation(shaderProgramID, "lightColor");
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);
	unsigned int objColorLocation = glGetUniformLocation(shaderProgramID, "objectColor");
	glUniform3f(objColorLocation, 1.0, 0.0, 1.0);
	unsigned int viewPosLocation = glGetUniformLocation(shaderProgramID, "viewPos"); //--- viewPos �� ����: ī�޶� ��ġ
	glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);
	unsigned int ambient = glGetUniformLocation(shaderProgramID, "ambientLight"); //--- viewPos �� ����: ī�޶� ��ġ
	glUniform1f(ambient, 1);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "viewTransform"); //--- ���� ��ȯ ����
	unsigned int projectionLocation = glGetUniformLocation(shaderProgramID, "projectionTransform"); //--- ���� ��ȯ �� ����

	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	projection = glm::perspective(glm::radians(30.0f), 1.0f, 0.1f, 50.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -2.0));
	projection = glm::rotate(projection, glm::radians(y_rad), glm::vec3(0.0, 1.0, 0.0));
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, 1.0));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	/*�׸���*/
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Draw();
	glDisable(GL_BLEND);
	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}

GLvoid Timer_event(int value) {
	player.move(move_character_x, move_character_z, rad);
	glutPostRedisplay(); //--- ������ �ٲ� ������ ��� �ݹ� �Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
	glutTimerFunc(100, Timer_event, 4);
}

GLvoid Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		if (rad[0] >= 40) 
			flip = true;
		else if (rad[0] <= -40)
			flip = false;
		move_character_z += 0.1;
		if (flip) 
			rad[0] -= 5;
		else
			rad[0] += 5;
		break;
	case 's':
		move_character_z -= 0.1;
		break;
	case 'a':
		move_character_x += 0.1;
		break;
	case 'd':
		move_character_x -= 0.1;
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
	glutPostRedisplay(); //--- ������ �ٲ� ������ ��� �ݹ� �Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�

}

void Draw() {
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "transform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	player.draw(head_vao, body_vao, right_arm_vao, left_arm_vao, right_leg_vao, left_leg_vao, modelLocation);
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void make_shaderProgram()
{
	make_vertexShaders(); //--- ���ؽ� ���̴� �����
	make_fragmentShaders(); //--- �����׸�Ʈ ���̴� �����
	//-- shader Program
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);
	//--- ���̴� �����ϱ�
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program ����ϱ�
	glUseProgram(shaderProgramID);
}

void make_vertexShaders()
{
	vertexSource = filetobuf("vertex.glsl");
	//--- ���ؽ� ���̴� ��ü �����
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	//--- ���ؽ� ���̴� �������ϱ�
	glCompileShader(vertexShader);
	//--- �������� ����� ���� ���� ���: ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}

void make_fragmentShaders()
{
	fragmentSource = filetobuf("fragment.glsl");
	//--- �����׸�Ʈ ���̴� ��ü �����
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	//--- �����׸�Ʈ ���̴� ������
	glCompileShader(fragmentShader);
	//--- �������� ����� ���� ���� ���: ������ ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}


void Initvbovao()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	//�Ӹ�
	Load_Object("head.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);

	glGenVertexArrays(1, &head_vao);
	glGenBuffers(3, head_vbo);
	glBindVertexArray(head_vao);

	glBindBuffer(GL_ARRAY_BUFFER, head_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, head_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	Load_Object("body.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);

	glGenVertexArrays(1, &body_vao);
	glGenBuffers(3, body_vbo);
	glBindVertexArray(body_vao);

	glBindBuffer(GL_ARRAY_BUFFER, body_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, body_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	Load_Object("rightleg.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);

	glGenVertexArrays(1, &right_leg_vao);
	glGenBuffers(3, right_leg_vbo);
	glBindVertexArray(right_leg_vao);

	glBindBuffer(GL_ARRAY_BUFFER, right_leg_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, right_leg_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	Load_Object("leftleg.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);

	glGenVertexArrays(1, &left_leg_vao);
	glGenBuffers(3, left_leg_vbo);
	glBindVertexArray(left_leg_vao);

	glBindBuffer(GL_ARRAY_BUFFER, left_leg_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, left_leg_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	Load_Object("rightarm.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);

	glGenVertexArrays(1, &right_arm_vao);
	glGenBuffers(3, right_arm_vbo);
	glBindVertexArray(right_arm_vao);

	glBindBuffer(GL_ARRAY_BUFFER, right_arm_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, right_arm_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	Load_Object("leftarm.obj", temp_vertices, temp_uvs, temp_normals, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);

	glGenVertexArrays(1, &left_arm_vao);
	glGenBuffers(3, left_arm_vbo);
	glBindVertexArray(left_arm_vao);

	glBindBuffer(GL_ARRAY_BUFFER, left_arm_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, left_arm_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

}
