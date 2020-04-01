#include <Windows.h>
#include <GL/freeglut.h>
#include <math.h>

#define pi 3.1475926
//�����������ľ���
GLfloat G_fDistance = 10.0f;
//�������ת�Ƕ� 
GLfloat G_fAngle_horizon = 0.0f;
GLfloat G_fAngle_vertical = 0.0f;
GLfloat angle = 0.0f;//ÿ��ת���Ƕ�
GLfloat R_sun = 1.0f;
GLfloat R_earth = 0.3f;
GLfloat R_moon = 0.15;

void myinit(void);
void myReshape(GLsizei w, GLsizei h);//�ص����� �ػ洰��
void display(void);//�ص����� ���ƻ���
void timer(int t);

//��Ӧ��������, �Ӷ��趨�����ƽ���Զ�Լ���ת�Ļص�����
void processSpecialKeys(int key, int x, int y);
void processNormalKeys(unsigned char key, int x, int y);

//������
int main(int argc, char* argv[])
{
	glutInit(&argc, argv); 
	//��ʼ��OPENGL��ʾ��ʽ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//�趨OPENGL����λ�úʹ�С
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	//�򿪴���
	glutCreateWindow("̫��ϵ");

	//���ó�ʼ������
	myinit();

	//�趨���ڴ�С�仯�Ļص�����
	glutReshapeFunc(myReshape); 

	//�趨���̿��ƵĻص����� 
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(processNormalKeys);

	glutDisplayFunc(display); 

	glutTimerFunc(100, timer, 0);//1s����һ��timer

	glutMainLoop();

	return 0;
}

//�û���ʼ������
void myinit(void)
{
	glEnable(GL_DEPTH_TEST);
}

//���ڴ�С�仯ʱ�Ļص�����
//����ͶӰ
void myReshape(GLsizei w, GLsizei h)
{
	//�趨����
	glViewport(0, 0, w, h);
	//�趨͸�ӷ�ʽ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0 * (GLfloat)w / (GLfloat)h, 1.0, 30.0);//���͸��ͶӰ
}

void timer(int t)
{
	glutTimerFunc(100, timer, 0);
	angle += 5;
	glutPostRedisplay();
}

void display(void)
{
	//���������Ļ����ɫ���������Ļ����Ȼ���
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//��ɫ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//���ó�ģ�;���ģʽ
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -G_fDistance);
	glRotatef(G_fAngle_horizon, 0.0f, 1.0f, 0.0f);
	glRotatef(G_fAngle_vertical, 1.0f, 0.0f, 0.0f);

	//��һ��̫��
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
	glutWireSphere(R_sun, 20, 16);
	//��һ��������̫����ת
	glPushMatrix();
		//������ת���
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 100; i++)
		{
			glVertex2f(3.0 * cos(2 * pi / 100 * i), 3.0 * sin(2 * pi / 100 * i));
		}
		glEnd();
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glTranslatef(3.0f, 0.0f, 0.0f);
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
		glutWireSphere(R_earth, 20, 16);
			glPushMatrix();//��һ���������Ƶ�����ת
				//������ת���
				glColor4f(0.5f, 0.5f, 0.0f, 0.0f);
				glBegin(GL_LINE_LOOP);
				for (int i = 0; i < 100; i++)
				{
					glVertex2f(1.0 * cos(2 * pi / 100 * i), 1.0 * sin(2 * pi / 100 * i));
				}
				glEnd();
				glRotatef(angle, 0.0f, 0.0f, 1.0f);
				glTranslatef(1.0f, 0.0f, 0.0f);
				glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
				glutWireSphere(R_moon, 20, 16);
			glPopMatrix();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void processSpecialKeys(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		G_fAngle_horizon -= 5.0f;
		break;
	case GLUT_KEY_RIGHT:
		G_fAngle_horizon += 5.0f;
		break;
	case GLUT_KEY_UP:
		G_fAngle_vertical -= 5.0f;
		break;
	case GLUT_KEY_DOWN:
		G_fAngle_vertical += 5.0f;
		break;
	}
	glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case 97:	//"a"
		G_fDistance -= 0.3f;
		break;
	case 65:		//"A"
		G_fDistance += 0.3f;
		break;
	case 27:	//"esc"
		exit(0);
	}
	glutPostRedisplay();
}