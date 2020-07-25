#include <windows.h>
#include <gl/glut.h>
#include <stdlib.h>

void init(void);
void tampil(void);
void keyboard(unsigned char, int, int);
void ukuran(int, int);
void idle();
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);
bool mouseDown = false;
int is_depth;
float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;

float xpos = 0.0f;
float ypos = 0.0f;
float zpos = 0.0f;


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(250, 80);
	glutCreateWindow("TUGAS AKHIR - GRAFIKA KOMPUTER");
	init();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutDisplayFunc(tampil);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(ukuran);
	glutMainLoop();
	return 0;
}
void init(void)
{
glClearColor(1.0, 1.0, 1.0, 0.0);
glEnable(GL_DEPTH_TEST);
//pencahayaan
glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
//set cahaya
GLfloat qaAmbientLight[] = { 0.2,0.2,0.2,1.0 };
GLfloat qaDiffuseLight[] = { 1,1,1,1 };
GLfloat qaSpecularLight[] = { 1,1,1,1 };
glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
//posisi cahaya
GLfloat posisilampu[] = { 0,160,200,1 };
glLightfv(GL_LIGHT0, GL_POSITION, posisilampu);
glEnable(GL_COLOR_MATERIAL);
glShadeModel(GL_SMOOTH);
glMatrixMode(GL_MODELVIEW);
glOrtho(-1, 1, -1, 1, -1, 1);
glPointSize(2.0);
glLineWidth(2.0);

}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
		case 'W':
		zpos += 3.0;
		glTranslatef(0.0, 0.0, 3.0);
		break;
		case 'd':
		case 'D':
		xpos += 3.0;
		glTranslatef(3.0, 0.0, 0.0);
		break;
		case 's':
		case 'S':
		zpos += -3.0;
		glTranslatef(0.0, 0.0, -3.0);
		break;
		case 'a':
		case 'A':
		xpos += -3.0;
		glTranslatef(-3.0, 0.0, 0.0);
		break;
		case '5':
		if (is_depth)
		{
			is_depth =0;
			glDisable(GL_DEPTH_TEST);
		} else
		{
			is_depth=1;
			glEnable(GL_DEPTH_TEST);
		}
		break;
	}
	tampil();
}

void idle()
{

	if (!mouseDown)
	{
		xrot += 0.3f;
		yrot += 0.4f;
	}
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseDown = true;
		xdiff = x - yrot;
		ydiff = -y + xrot;
	}
	else
	mouseDown = false;
}

void mouseMotion(int x, int y)
{

	if (mouseDown)
	{
		yrot = x - xdiff;
		xrot = y + ydiff;

	glutPostRedisplay();

	}
}

void ukuran(int lebar, int tinggi)
{
	if (tinggi == 0) tinggi = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, lebar / tinggi, 5.0, 500.0);
	glTranslatef(0.0, -5.0, -150.0);
	glMatrixMode(GL_MODELVIEW);
}
void tampil(void)
{
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gluLookAt(0,10,20,0,0,0,0,1,0);
	glRotatef(xrot,1,0,0);
	glRotatef(yrot,0,1,0);
	glColor3f(1,0,0);

	 //atap-depan
	glBegin(GL_POLYGON);
	glColor3f(105/255.0f,105/255.0f,105/255.0f);
	glVertex3f(-20.0, 20.0, 20.0);
	glVertex3f(20.0, 20.0, 20.0);
	glVertex3f(0.0, 45.0, 0.0);
	glEnd();
	//atap-kanan
	glBegin(GL_POLYGON);
	glColor3f(105/255.0f,105/255.0f,105/255.0f);
	glVertex3f(20.0, 20.0, 20.0);
	glVertex3f(20.0, 20.0, -20.0);
	glVertex3f(0.0, 45.0, 0.0);
	glEnd();

			//atap-kiri
	glBegin(GL_POLYGON);
	glColor3f(105/255.0f,105/255.0f,105/255.0f);
	glVertex3f(-20.0, 20.0, 20.0);
	glVertex3f(-20.0, 20.0, -20.0);
	glVertex3f(0.0, 45.0, 0.0);
	glEnd();

				//atap-kanan
	glBegin(GL_POLYGON);
	glColor3f(105/255.0f,105/255.0f,105/255.0f);
	glVertex3f(20.0, 20.0, -20.0);
	glVertex3f(-20.0, 20.0, -20.0);
	glVertex3f(0.0, 45.0, 0.0);
	glEnd();

}
