#include <windows.h> // nu se copiaza pe linux
#include <GL/glut.h>
#include <GL\freeglut.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "meteorites.h"
#include "plane.h"

//glutGet(GLUT_ELAPSED_TIME)
//https://stackoverflow.com/questions/8523346/how-to-control-finely-the-glut-inner-loop
bool meteorites_created=false;
bool start_game = false;
float time_since_last_meteorite_draw, time_since_last_plane_drow;

struct meteorite {
	float meteorite_x;
	float meteorite_y;
	float meteorite_begin;
	float meteorite_r;

};

struct plane my_plane = { 0, -0.7, 1.0, 0, 0 };
struct meteorite meteorites[100];



void create_meteorites() {
	int meteorite_index = 0;
	meteorites[meteorite_index].meteorite_r = randf(1, 2) - 1;
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








void update() {


  

    glutPostRedisplay();
}


void colizion(int index_meteorite) {
	float x_axis = my_plane.plane_x - meteorites[index_meteorite].meteorite_x;
	float y_axis = my_plane.plane_y - meteorites[index_meteorite].meteorite_y;
	float distance = sqrt(x_axis * x_axis + y_axis * y_axis);
	if (distance < meteorites[index_meteorite].meteorite_r + 0.06) {
		my_plane.plane_red = 1.0;
		my_plane.plane_green = 0;
	}
}
void animate_meteorite(){
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
		colizion(meteorites_index);
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

draw_start_button() {

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
		printf("%d  ", delta);
	}
	last = glutGet(GLUT_ELAPSED_TIME);


	if (start_game) {
		update_plane_position(&my_plane);
		draw_airplane(&my_plane);
	animate_meteorite();
	} else {
		update_plane_position(&my_plane);
		draw_airplane(&my_plane);

		animate_meteorite();
	}

	glFlush();
}
int main(int argc, char** argv) {
	int arg1=1;
	glutInit(&argc, argv);
	time_since_last_meteorite_draw = glutGet(GLUT_ELAPSED_TIME);
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

	glutDisplayFunc(display);
	glutMainLoop();

return 0;}

