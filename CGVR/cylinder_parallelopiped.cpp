#include <GL/glut.h>


void plotpixels(int h, int k, int x, int y)
{
	glBegin(GL_POINTS);
	glColor3f(0, 1, 0);
	glVertex2f(h + x, k + y);
	glVertex2f(h - x, k + y);
	glVertex2f(h + x, k - y);
	glVertex2f(h - x, k - y);
	glVertex2f(h + y, k + x);
	glVertex2f(h - y, k + x);
	glVertex2f(h + y, k - x);
	glVertex2f(h - y, k - x);
	glEnd();
}

void Circle_draw(int h, int k, int r)  // Midpoint Circle Drawing Algorithm
{
	int d = 3 - 2 * r, x = 0, y = r;
	while (x <= y)
	{
		plotpixels(h, k, x, y);
		if (d < 0)
			d += 4 * x + 6;
		else
		{
			y--;
			d += 4 * (x - y) + 10;
		}
		++x;
		plotpixels(h, k, x, y);
	}
}

void Cylinder_draw()
{
	int xc = 100, yc = 100, r = 50, i, n = 50;

	for (i = 0; i < n; i += 2)
		Circle_draw(xc, yc + i, r);
}

void parallelepiped(int x1, int x2, int y1, int y2)
{
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x1, y1);
	glVertex2i(x2, y1);
	glVertex2i(x2, y2);
	glVertex2i(x1, y2);
	glEnd();
}

void parallelepiped_draw()
{
	int x1 = 200, x2 = 300, y1 = 100, y2 = 175, i, n = 40;
	for (i = 0; i < n; i += 2)
		parallelepiped(x1 + i, x2 + i, y1 + i, y2 + i);
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 400.0, 0, 300.0);
}

void display1(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	// Cylinder_draw();
	parallelepiped_draw();
	glFlush();
}

void display2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Cylinder_draw();
	// parallelepiped_draw();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 300);

	int id1 = glutCreateWindow("Cylinder");
	glutSetWindow(id1);
	glutDisplayFunc(display2);
	init();

	int id2 = glutCreateWindow("Parallelopiped");
	glutSetWindow(id2);
	glutDisplayFunc(display1);
	init();
	glutMainLoop();
}
