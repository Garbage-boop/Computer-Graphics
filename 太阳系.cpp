#include <Windows.h>
#include <GL/freeglut.h>
#include <math.h>

#define pi 3.1475926
//摄像机离物体的距离
GLfloat G_fDistance = 10.0f;
//物体的旋转角度 
GLfloat G_fAngle_horizon = 0.0f;
GLfloat G_fAngle_vertical = 0.0f;
GLfloat angle = 0.0f;//每次转动角度
GLfloat R_sun = 1.0f;
GLfloat R_earth = 0.3f;
GLfloat R_moon = 0.15;

void myinit(void);
void myReshape(GLsizei w, GLsizei h);//回调函数 重绘窗口
void display(void);//回调函数 绘制画面
void timer(int t);

//响应键盘输入, 从而设定物体移近移远以及旋转的回调函数
void processSpecialKeys(int key, int x, int y);
void processNormalKeys(unsigned char key, int x, int y);

//主函数
int main(int argc, char* argv[])
{
	glutInit(&argc, argv); 
	//初始化OPENGL显示方式
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//设定OPENGL窗口位置和大小
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	//打开窗口
	glutCreateWindow("太阳系");

	//调用初始化函数
	myinit();

	//设定窗口大小变化的回调函数
	glutReshapeFunc(myReshape); 

	//设定键盘控制的回调函数 
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(processNormalKeys);

	glutDisplayFunc(display); 

	glutTimerFunc(100, timer, 0);//1s呼叫一次timer

	glutMainLoop();

	return 0;
}

//用户初始化函数
void myinit(void)
{
	glEnable(GL_DEPTH_TEST);
}

//窗口大小变化时的回调函数
//定义投影
void myReshape(GLsizei w, GLsizei h)
{
	//设定视区
	glViewport(0, 0, w, h);
	//设定透视方式
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0 * (GLfloat)w / (GLfloat)h, 1.0, 30.0);//完成透视投影
}

void timer(int t)
{
	glutTimerFunc(100, timer, 0);
	angle += 5;
	glutPostRedisplay();
}

void display(void)
{
	//设置清除屏幕的颜色，并清除屏幕和深度缓冲
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//黑色
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//设置成模型矩阵模式
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -G_fDistance);
	glRotatef(G_fAngle_horizon, 0.0f, 1.0f, 0.0f);
	glRotatef(G_fAngle_vertical, 1.0f, 0.0f, 0.0f);

	//画一个太阳
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
	glutWireSphere(R_sun, 20, 16);
	//画一个地球并绕太阳旋转
	glPushMatrix();
		//画地球公转轨道
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
			glPushMatrix();//画一个月亮并绕地球旋转
				//画月球公转轨道
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