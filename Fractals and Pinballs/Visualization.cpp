#include "Visualization.h"

Visualization::Visualization(){};

void keyboard(unsigned char key, int x, int y)
{
	if (key == '27') { exit(0); }
}

void display(void)
{
	glPushMatrix();
	glTranslatef(18, 2, 0);
	glRotatef(5.0f, 0, 0, 0.7f);
	glColor3ub(0, 255, 255);
	glutWireSphere(3, 10, 10);
	glPopMatrix();
}
void reshape(int width, int height)
{}
void Visualization::initGraphics(int argc, char *argv[])
{
	/*INITIAL NAVIGATIONAL VARIABLES
	eyeX = 50.0;
	eyeY = 5.0;
	eyeZ = -500.0;
	upX = 0.0;
	upY = -1.0;
	upZ = 0.0;
	latitude = 0.0;
	longitude = 0.0;
	*/
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutCreateWindow("COMP37111 Particles");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glEnable(GL_POINT_SMOOTH);
	glutMainLoop();
}
