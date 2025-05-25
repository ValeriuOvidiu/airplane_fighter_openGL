#include <windows.h> // nu se copiaza pe linux
#include <GL/glut.h>
#include <GL\freeglut.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "meteorites.h"
#include "plane.h"
#include "start_restart.h"
#include "login_system.h"
struct player my_player;

void draw_sign_up_button() {
	int len, i;

	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-0.2f, 0.55f);
	glVertex2f(-0.2f, 0.4f);
	glVertex2f(0.2f, 0.4f);
	glVertex2f(0.2f, 0.55f);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	char sign_up_text[] = "Sign up";
	len = (int) strlen(sign_up_text);
	glRasterPos2f(-0.1f, 0.48f); // pozitionare raster

	for (i = 0; i < len; i++) { // bucla pentru afisare litere
		// afisare litera i
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, sign_up_text[i]);
	}
}
void drow_loggin_form() {
	char loggin_indications_line1[] =
			"Introduce your username and password to loggin or ";
	char loggin_indications_line2[] =
			"click the \"Sign up\"button to create a new accound";
	char username[] = "Username";
	char password[] = "Password";
	int len, i;
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 0.0f);
	len = (int) strlen(loggin_indications_line1);
	glRasterPos2f(-0.6f, 0.7f); // pozitionare raster

	for (i = 0; i < len; i++) { // bucla pentru afisare litere
		// afisare litera i
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, loggin_indications_line1[i]);
	}
	len = (int) strlen(loggin_indications_line2);
	glRasterPos2f(-0.6f, 0.6f); // pozitionare raster

	for (i = 0; i < len; i++) { // bucla pentru afisare litere
		// afisare litera i
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, loggin_indications_line2[i]);
	}

	draw_sign_up_button();

	glColor3f(0.0f, 1.0f, 0.0f);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.2f, 0.15f);
	glVertex2f(-0.2f, 0.0f);
	glVertex2f(0.6f, 0.0f);
	glVertex2f(0.6f, 0.15f);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);

	len = (int) strlen(username);
	glRasterPos2f(-0.6f, 0.07f); // pozitionare raster

	for (i = 0; i < len; i++) { // bucla pentru afisare litere
		// afisare litera i
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, username[i]);
	}

	glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.2f, -0.05f);
	glVertex2f(-0.2f, -0.2f);
	glVertex2f(0.6f, -0.2f);
	glVertex2f(0.6f, -0.05f);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);

	len = (int) strlen(password);
	glRasterPos2f(-0.6f, -0.12f); // pozitionare raster

	for (i = 0; i < len; i++) { // bucla pentru afisare litere
		// afisare litera i
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, password[i]);
	}


}
void void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (x >= -0.2 && x < 0.2 && y <= 0.55 && y >= 0.4) {

		} else if (x >= -0.2 && x <= 0.6 && y <= 0.15 && y >= 0.0) {

		} else if (x >= -0.2 && x <= 0.6 && y <= -0.05 && y >= -0.2) {

		}
	}
}
