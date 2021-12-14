#include<stdlib.h>
#include<gl/glut.h>
#include<iostream>

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 600 

typedef GLfloat point[3];

int iter;
//point tetra[4] = { {0,0,250},{0,250,-250},{250,-250,-250},{-250,-250,-250} };
point tetra[4] = { {0,0,250}, {0,250,-250},{250,-250,-250},{-250,-250,-250} };
void myInit();
void tetrahedron();
void drawTriangle(point p1, point p2, point p3);
void drawTetrahedron(point p1, point p2, point p3, point p4);

void drawTriangle(point p1, point p2, point p3) {
	glBegin(GL_TRIANGLES);
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p3);
	glEnd();
}

void drawTetrahedron(point p1, point p2, point p3, point p4) {
	glColor3f(1.0, 1.0, 0.0);
	drawTriangle(p1, p2, p3);
	glColor3f(0.0, 1.0, 0.0);
	drawTriangle(p1, p3, p4);
	glColor3f(1.0, 0.0, 0.0);
	drawTriangle(p1, p4, p2);
	glColor3f(0.0, 0.0, 1.0);
	drawTriangle(p2, p3, p4);
}

void divideTetrahedron(point p1, point p2, point p3, point p4, int iter) {
	point mid[6];
	int j;

	if (iter > 0) {
		for (j = 0; j < 3; j++)mid[0][j] = (p1[j] + p2[j]) / 2;
		for (j = 0; j < 3; j++)mid[1][j] = (p1[j] + p3[j]) / 2;
		for (j = 0; j < 3; j++)mid[2][j] = (p1[j] + p4[j]) / 2;
		for (j = 0; j < 3; j++)mid[3][j] = (p2[j] + p3[j]) / 2;
		for (j = 0; j < 3; j++)mid[4][j] = (p3[j] + p4[j]) / 2;
		for (j = 0; j < 3; j++)mid[5][j] = (p2[j] + p4[j]) / 2;
		// the mid point between edges are found and then four tetra hedrons are formed
		divideTetrahedron(p1, mid[0], mid[1], mid[2], iter - 1);
		divideTetrahedron(p2, mid[3], mid[0], mid[5], iter - 1);
		divideTetrahedron(p3, mid[1], mid[3], mid[4], iter - 1);
		divideTetrahedron(p4, mid[2], mid[5], mid[4], iter - 1);
	}
	else
		drawTetrahedron(p1, p2, p3, p4);
}

void tetrahedron() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	divideTetrahedron(tetra[0], tetra[1], tetra[2], tetra[3], iter);
	glFlush();
}

void myInit() {
	glClearColor(1, 1, 1, 1);
	glOrtho(-300.0, 300.0, -300.0, 300.0, -300.0, 300.0);
}

void main(int argc, char* argv[]) {
	printf("Ënter the number of Subdivisions\n");
	std::cin >> iter;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Sierpenski Gasket");
	glutDisplayFunc(tetrahedron);
	glEnable(GL_DEPTH_TEST);
	myInit();
	glutMainLoop();
}
