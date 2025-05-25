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

bool meteorites_created=false;
bool start_game = false;
bool restart_game = false;
bool user_logged_in = false;
int time_since_last_meteorite_draw = -1;
struct plane my_plane = { 0, -0.7, 1.0, 0, 0 };
extern struct meteorite meteorites[10];



void update() {
	glutPostRedisplay();
}



void animate_meteorite(){
	if (time_since_last_meteorite_draw == -1) {
		time_since_last_meteorite_draw = glutGet(GLUT_ELAPSED_TIME);
	}
	int meteorites_index;
	float present_time=glutGet(GLUT_ELAPSED_TIME);
	float delta_time = present_time - time_since_last_meteorite_draw;

	for (meteorites_index = 0; meteorites_index < 10; ++meteorites_index) {
			if (my_plane.plane_green == 1) {
		meteorites[meteorites_index].meteorite_y -= 0.001 * delta_time;
			}
		draw_meteorite(meteorites[meteorites_index].meteorite_x,
				meteorites[meteorites_index].meteorite_y,
				meteorites[meteorites_index].meteorite_r);
		colizion(&my_plane, &meteorites[meteorites_index]);
		if (meteorites[meteorites_index].meteorite_y
				< -1 - meteorites[meteorites_index].meteorite_r) {
			meteorites[meteorites_index].meteorite_y =
					meteorites[9].meteorite_begin - 2;
			meteorites[meteorites_index].meteorite_r = (float) randf(1, 3) / 10;
			meteorites[meteorites_index].meteorite_x = randf(1, 3) - 2;
		}

	}
    //printf("%f  %f  %f     ",meteorites[1].meteorite_x,meteorites[1].meteorite_y,meteorites[1].meteorite_r);

	time_since_last_meteorite_draw = present_time;
}


int last;
void display() {
	
	int present = glutGet(GLUT_ELAPSED_TIME);
	int delta = present - last;
	last = present;
	
	delta *= 1000;
	if (delta < 15000) {

		int sleepp = 15000 - delta;
		usleep(sleepp);
		present = glutGet(GLUT_ELAPSED_TIME);
		delta = present - last;
	}
	last = glutGet(GLUT_ELAPSED_TIME);


	if (!user_logged_in) {
		drow_loggin_form();
	} else if (start_game && !restart_game) {
		glClear(GL_COLOR_BUFFER_BIT);

		update_plane_position(&my_plane);
	animate_meteorite();
		draw_airplane(&my_plane);

	} else if (!start_game) {
		draw_start_button();
	} else if (restart_game) {
		draw_restart_button();
		draw_airplane(&my_plane);


	}

	glFlush();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	//time_since_last_plane_drow = glutGet(GLUT_ELAPSED_TIME);
	last = glutGet(GLUT_ELAPSED_TIME);
	if(!meteorites_created){
		meteorites_created=true;
		create_meteorites();
	}
	int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
	    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

	    // Window dimensions
	    int windowWidth = 800;  // Example width
	    int windowHeight = screenHeight; // Example height

	    // Calculate X position for centering on the X-axis
	    int windowX = (screenWidth - windowWidth) / 2;
	    int windowY = 0; // Example Y position (not centered vertically)

	    // Initialize window position
	    glutInitWindowPosition(windowX, windowY);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("OpenGL ovidiu Test");
    glutIdleFunc(update); // apelat constant pentru miscare lina

	  glutSpecialFunc(specialKeyDown); // cand apesi
	    glutSpecialUpFunc(specialKeyUp); // cand eliberezi
	glutKeyboardFunc(start_key);
	//glutKeyboardFunc(restart_key);

	glutDisplayFunc(display);
	glutMainLoop();
	glutMouseFunc(mouse);

return 0;}

