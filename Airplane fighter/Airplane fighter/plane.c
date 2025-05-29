#include <windows.h>
#include <GL/glut.h>
#include <GL\freeglut.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "meteorites.h"
#include "plane.h"
#include "meteorites.h"
bool key_left_pressed = false;
bool key_right_pressed = false;
int time_since_last_plane_drow = -1;
extern bool restart_game;

void draw_airplane(struct plane *my_plane) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// draw triangle (airplane nose)
	glBegin(GL_TRIANGLES);
	glColor3f(my_plane->plane_red, my_plane->plane_green, 0.0f);
	glVertex2f(my_plane->plane_x, my_plane->plane_y + 0.08f);
	glVertex2f(my_plane->plane_x - 0.03f, my_plane->plane_y + 0.03f);
	glVertex2f(my_plane->plane_x + 0.03f, my_plane->plane_y + 0.03f);
	glEnd();

	// draw body (top quad)
	glBegin(GL_QUADS);
	glVertex2f(my_plane->plane_x - 0.06f, my_plane->plane_y + 0.03f);
	glVertex2f(my_plane->plane_x - 0.06f, my_plane->plane_y);
	glVertex2f(my_plane->plane_x + 0.06f, my_plane->plane_y);
	glVertex2f(my_plane->plane_x + 0.06f, my_plane->plane_y + 0.03f);
	glEnd();

	// draw tail or lower part
	glBegin(GL_QUADS);
	glVertex2f(my_plane->plane_x - 0.03f, my_plane->plane_y);
	glVertex2f(my_plane->plane_x - 0.03f, my_plane->plane_y - 0.06f);
	glVertex2f(my_plane->plane_x + 0.03f, my_plane->plane_y - 0.06f);
	glVertex2f(my_plane->plane_x + 0.03f, my_plane->plane_y);
	glEnd();

}
// Când o tastă specială este apasata
void special_key_down(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT)
		key_left_pressed = true;
	if (key == GLUT_KEY_RIGHT)
		key_right_pressed = true;
}

// Când o tastă specială este eliberata
void special_key_up(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		key_left_pressed = false;
	}
	if (key == GLUT_KEY_RIGHT)
		key_right_pressed = false;
}
void update_plane_position(struct plane *my_plane) {
	if (time_since_last_plane_drow == -1) {
		time_since_last_plane_drow = glutGet(GLUT_ELAPSED_TIME);

	}
	float speed;
	int present_time = glutGet(GLUT_ELAPSED_TIME);
	int delta_time = present_time - time_since_last_plane_drow;
	speed = (float) 0.002 * delta_time;
	if (key_left_pressed && my_plane->plane_x > -1
			&& my_plane->plane_red == 0) {
		my_plane->plane_x -= speed;
	}

	if (key_right_pressed && my_plane->plane_x < 1
			&& my_plane->plane_red == 0) {
		my_plane->plane_x += speed;
	}
	time_since_last_plane_drow = present_time;
}
void colizion(struct plane *my_plane, struct meteorite *meteorites) {
	float x_axis = my_plane->plane_x - meteorites->meteorite_x;
	float y_axis = my_plane->plane_y - meteorites->meteorite_y;
	float distance = sqrt(x_axis * x_axis + y_axis * y_axis);
	if (distance < meteorites->meteorite_r + 0.06) {
		my_plane->plane_red = 1.0;
		my_plane->plane_green = 0;
		restart_game = true;
	}
}
