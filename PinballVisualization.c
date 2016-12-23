#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>

#define DEG_TO_RAD_CONV 0.017453293f
#define MOVEMENT_FACTOR 2.5f;
#define TIME_STEP 0.01;
// Global viewpoint/camera variables 
GLfloat latitude, longitude;
GLfloat eyeX, eyeY, eyeZ;
GLfloat centerX, centerY, centerZ;
GLfloat upX, upY, upZ;
GLfloat xRotation, yRotation = 0.0;
GLint mouseX, mouseY;
// Display list for coordinate axis 
GLuint axisList;
int AXIS_SIZE = 200;
int axisEnabled = 1;

GLfloat TIME;
typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
}vec3D;
typedef struct {
	GLfloat width;
	GLfloat height;
}Table;
typedef struct {
	vec3D* positions[10];
	vec3D* velocities[10];
	vec3D* accelerations[10];
}Pinball;
Table* table;
Pinball* pinball;
void calculateLookpoint() {
	GLfloat deltaX = cosf(DEG_TO_RAD_CONV*latitude)*sinf(DEG_TO_RAD_CONV*longitude);
	GLfloat deltaY = sinf(DEG_TO_RAD_CONV*-latitude);
	GLfloat deltaZ = cosf(DEG_TO_RAD_CONV*latitude)*cosf(DEG_TO_RAD_CONV*longitude);

	centerX = eyeX + deltaX;
	centerY = eyeY + deltaY;
	centerZ = eyeZ + deltaZ;
}

void mouseMotion(int x, int y) {
	// Called when mouse moves
	xRotation += (y - mouseY);	mouseY = y;
	yRotation += (x - mouseX);	mouseX = x;
	// keep all rotations between 0 and 360.
	if (xRotation > 360.0) xRotation -= 360.0;
	if (xRotation < 0.0)   xRotation += 360.0;
	if (yRotation > 360.0) yRotation -= 360.0;
	if (yRotation < 0.0)   yRotation += 360.0;
	// ask for redisplay
	glutPostRedisplay();
}


void mousePress(int button, int state, int x, int y) {
	// When left mouse button is pressed, save the mouse(x,y)
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		mouseX = x;
		mouseY = y;
	}
}

///////////////////////////////////////////////
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 97: {
		eyeX += MOVEMENT_FACTOR;
		calculateLookpoint();
		break;
	}
	case 100: {
		eyeX -= MOVEMENT_FACTOR;
		calculateLookpoint();
		break;
	}
	case 119: {
		eyeY += MOVEMENT_FACTOR;
		calculateLookpoint();
		break;
	}
	case 115: {
		eyeY -= MOVEMENT_FACTOR;
		calculateLookpoint();
	}
			  break;
	case 120:
	{
		eyeZ -= MOVEMENT_FACTOR;
		calculateLookpoint();
		break;
	}
	case 122:
	{
		eyeZ += MOVEMENT_FACTOR;
		calculateLookpoint();
		break;
	}
	case 32:
	{
		centerX = 0.5;
		centerY = .5;
		centerZ = 0.0;
		eyeX = .5;
		eyeY = 0.5;
		eyeZ = -1.5;
		upX = 0.0;
		upY = 1.0;
		upZ = 0.0;
		latitude = 0.0;
		longitude = 0.0; 
		break;
	}
	}
	printf("EYE[X,Y,Z]=[%f,%f,%f] \t CENTER[X,Y,Z]=[%f,%f,%f]\n ", eyeX, eyeY, eyeZ, centerX, centerY, centerZ);
	glutPostRedisplay();
}
void reshape(int width, int height)
{
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 10000.0);
	glMatrixMode(GL_MODELVIEW);
}
void makeAxes() {
	// Create a display list for drawing coord axis
	axisList = glGenLists(1);
	glNewList(axisList, GL_COMPILE);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glColor4f(1.0, 0.0, 0.0, 1.0);       // X axis - red
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f((float)AXIS_SIZE, 0.0, 0.0);
	glColor4f(0.0, 1.0, 0.0, 1.0);       // Y axis - green
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, (float)AXIS_SIZE, 0.0);
	glColor4f(0.0, 0.0, 1.0, 1.0);       // Z axis - blue
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, (float)AXIS_SIZE);
	glEnd();
	glEndList();
}
int i = 0;
void display(void) {
	glLoadIdentity();
	glRotatef(xRotation, 1.0, 0.0, 0.0);
	glRotatef(yRotation, 0.0, 1.0, 0.0);
	glPushMatrix();
	calculateLookpoint();
	gluLookAt(eyeX, eyeY, eyeZ,
		centerX, centerY, centerZ,
		upX, upY, upZ);
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(table->width, table->height,0.0);
	glVertex3f(0.0, table->height,0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(table->width, 0.0,0.0);
	glEnd();
	if (axisEnabled) glCallList(axisList);
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	if (TIME > 1) {
		i++;
		TIME = 0;
	}
	else
	{
		TIME += TIME_STEP;
	}
	if (i < 10) {
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(pinball->positions[i]->x, pinball->positions[i]->y, 0.0);
		glEnd();
		glPopMatrix();
		glutSwapBuffers();
		glutPostRedisplay();
	}
	else
	{
		glColor3f(1.0, 1.0, 1.0);
		glPointSize(3.0f);
		glVertex3f(pinball->positions[9]->x, pinball->positions[9]->y, 0.0);
		glEnd();
		glPopMatrix();
		glutSwapBuffers();
		glutPostRedisplay();
	}
}

void initGraphics(int argc, char* argv) {
	/*INITIAL NAVIGATIONAL VARIABLES*/
	centerX = 0.5;
	centerY = 1.5;
	centerZ = 0.0;
	eyeX = 0.5;
	eyeY = 1.0;
	eyeZ = -6.0;
	upX = 0.0;
	upY = 1.0;
	upZ = 0.0;
	latitude = 0.0;
	longitude = 0.0;
	glutInit(&argc, &argv);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutCreateWindow("Pinball Machine OpenGL Visualization");
	//Enable alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mousePress);
	glutMotionFunc(mouseMotion);
	glutReshapeFunc(reshape);
	makeAxes();
}
//Pinball table variables
float val1;
float val2;
int setValuesFromTextFile(char* filename) {
	FILE *inputFile;
	char buffer[100];
	int line = 0;
	inputFile = fopen(filename, "r");
	char objectName[16];
	if (!inputFile)
	{
		printf("Could not open file: %s \n", filename);
		return 1;
	}
	int arrayPos = 0;
	while (fgets(buffer, sizeof(buffer), inputFile)) {
		line++;
		sscanf(buffer,"%s\t%f\t%f\n",&objectName, &val1, &val2);
		if (strcmp(objectName, "TABLE") == 0)
		{
			table->width = val1;
			table->height = val2;
		}
		else if (strcmp(objectName, "BALLPOS") == 0)
		{
			pinball->positions[arrayPos]->x = val1;
			pinball->positions[arrayPos]->y = val2;
			arrayPos++;
		}
	}
	fclose(inputFile);
	return 0;
}
int main(int argc, char *argv)
{
	double f;
	srand(time(NULL));
	table = (Table*)malloc(sizeof(Table));
	pinball = (Pinball*)malloc(sizeof(Pinball));
	int i;
	for (i = 0; i < 10; i++) {
		pinball->positions[i] = (vec3D*)malloc(sizeof(vec3D));
		pinball->velocities[i] = (vec3D*)malloc(sizeof(vec3D));
		pinball->accelerations[i] = (vec3D*)malloc(sizeof(vec3D));
	}
	setValuesFromTextFile("test1.txt");
	printf("Last X Pos: %f \t Last Y Pos: %f \n", pinball->positions[9]->x, pinball->positions[9]->y);
	initGraphics(argc, argv);
	glEnable(GL_POINT_SMOOTH);
	glutMainLoop();
}