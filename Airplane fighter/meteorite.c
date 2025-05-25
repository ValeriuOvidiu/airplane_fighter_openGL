#include <windows.h> // nu se copiaza pe linux
#include <GL/glut.h>
#include <GL\freeglut.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "meteorites.h"
struct meteorite meteorites[10];


void create_meteorites() {
	int meteorite_index = 0;
	meteorites[meteorite_index].meteorite_r = (float) randf(1, 3) / 10;
	meteorites[meteorite_index].meteorite_x = randf(1, 3) - 2;
	meteorites[meteorite_index].meteorite_y = 1.2;
	meteorites[meteorite_index].meteorite_begin =
			meteorites[meteorite_index].meteorite_y;
	for (meteorite_index = 1; meteorite_index < 100; ++meteorite_index) {
		meteorites[meteorite_index].meteorite_r = (float) randf(1, 3) / 10;
		meteorites[meteorite_index].meteorite_x = randf(1, 3) - 2;
		meteorites[meteorite_index].meteorite_y =
				meteorites[meteorite_index - 1].meteorite_y
						+ meteorites[meteorite_index - 1].meteorite_r
						+ meteorites[meteorite_index].meteorite_r;
		meteorites[meteorite_index].meteorite_begin =
				meteorites[meteorite_index].meteorite_y;

	}
}

void draw_meteorite(float x, float y, float radius) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, 0.0f);
	static const int circle_points = 100;
	float angle = 2.0f * 3.1416f / circle_points;

	// this code (mostly) copied from question:
	glBegin(GL_POLYGON);
	double angle1 = 0.0;
	glVertex2d(radius * cos(0.0), radius * sin(0.0));
	int i;
	for (i = 0; i < circle_points; i++) {
		glVertex2d(radius * cos(angle1), radius * sin(angle1));
		angle1 += angle;
	}
	glEnd();
	glPopMatrix();
	// glFlush();
}
float randf(float min, float max) {
	return min + ((float) rand() / (float) RAND_MAX) * (max - min);
}



