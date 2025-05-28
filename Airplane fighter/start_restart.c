#include <windows.h> // nu se copiaza pe linux
#include <GL/glut.h>
#include <GL\freeglut.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "meteorites.h"
#include "login_system.h"

#include "plane.h"
extern bool start_game;
extern bool restart_game;
extern struct plane my_plane;
extern int time_since_last_meteorite_draw, current_score;
extern struct player my_player;
bool reset_called = false;
void draw_start_button() {
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	char start_indication[] = "Press \"Enter\" to start the game!";

	int len, i;


	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-0.4f, 0.25f);
	glVertex2f(-0.4f, -0.25f);
	glVertex2f(0.4f, -0.25f);
	glVertex2f(0.4f, 0.25f);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	len = (int) strlen(start_indication);
	glRasterPos2f(-0.35f, 0.0f); // pozitionare raster

	for (i = 0; i < len; i++) { // bucla pentru afisare litere
		// afisare litera i
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, start_indication[i]);
	}
}

void draw_restart_button() {
	char start_indication[] = "Press \"Enter\" to restart the game!";
	int len, i;
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-0.4f, 0.25f);
	glVertex2f(-0.4f, -0.25f);
	glVertex2f(0.4f, -0.25f);
	glVertex2f(0.4f, 0.25f);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);

	len = (int) strlen(start_indication);
	glRasterPos2f(-0.38f, 0.0f); // pozitionare raster

	for (i = 0; i < len; i++) { // bucla pentru afisare litere
		// afisare litera i
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, start_indication[i]);
	}
}
void reset() {
	restart_game = false;
	create_meteorites();
	my_plane.plane_x = 0;
	my_plane.plane_y = -0.7;
	my_plane.plane_green = 1.0;
	my_plane.plane_red = 0;
	my_plane.distroid = 0;
	time_since_last_meteorite_draw = -1;
	current_score = 0;
	my_player.nr_of_games++;


}
void start_key(int key, int x, int y) {
	if (key == 13 && !start_game) {
		start_game = true;
	} else if (key == 13 && start_game && restart_game) {

	reset();

	}

}
