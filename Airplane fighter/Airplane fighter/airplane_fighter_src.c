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


bool meteorites_created=false;
bool start_game = false;
bool restart_game = false;
bool user_logged_in = false;
int time_since_last_meteorite_draw = -1;
struct plane my_plane = { 0, -0.7, 1.0, 0, 0 };
extern struct meteorite meteorites[10];
extern struct player my_player;
extern struct player players[100];
extern int player_id;
int current_score = 0, score_from_last_update = 0;


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
			current_score++;

		}

	}

	time_since_last_meteorite_draw = present_time;
}


int last;
int time_since_last_db_update;
void draw_score() {
	int len, i, all_time_score_value;
	if (current_score >= score_from_last_update) {
		all_time_score_value = players[player_id].score + current_score
			- score_from_last_update;
	} else {
		score_from_last_update = 0;
	}

	char current_score_str[100], all_time_score[100], total_nr_of_games[100];
	glColor3f(0.0f, 1.0f, 0.0f);
	sprintf(total_nr_of_games, "Total Games Played: %d",
			players[player_id].nr_of_games);

	sprintf(all_time_score, "All Time Score %d", all_time_score_value);
	sprintf(current_score_str, "Current Score %d", current_score);
	len = (int) strlen(current_score_str);
	glRasterPos2f(-0.9f, 0.8f);

	for (i = 0; i < len; i++) {

		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, current_score_str[i]);

	}
	len = (int) strlen(all_time_score);
	glRasterPos2f(-0.9f, 0.9f);

	for (i = 0; i < len; i++) {

		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, all_time_score[i]);

	}
	len = (int) strlen(total_nr_of_games);
	glRasterPos2f(0.4f, 0.9f);

	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, total_nr_of_games[i]);

	}

}
void display() {
	
	int present = glutGet(GLUT_ELAPSED_TIME);
	int delta = present - last;
	last = present;
	
	delta *= 1000;
	int update_db_timer = present - time_since_last_db_update;

	if (update_db_timer > 1000) {
		if (current_score >= score_from_last_update) {
			players[player_id].score += current_score - score_from_last_update;
		score_from_last_update = current_score;
		update_db();
		time_since_last_db_update = glutGet(GLUT_ELAPSED_TIME);
		} else {
			score_from_last_update = 0;
		}
	}
	if (delta < 15000) {
		
		int sleepp = 15000 - delta;
		usleep(sleepp);
		present = glutGet(GLUT_ELAPSED_TIME);
		delta = present - last;
	}
	last = glutGet(GLUT_ELAPSED_TIME);


	 if (start_game && !restart_game) {
		glClear(GL_COLOR_BUFFER_BIT);

		update_plane_position(&my_plane);
	animate_meteorite();
		draw_airplane(&my_plane);
		draw_score();

	} else if (!start_game) {
		draw_start_button();
	} else if (restart_game) {
		draw_restart_button();
		draw_airplane(&my_plane);


	}

	glFlush();
}



int main(int argc, char** argv) {
	account_menu();
	glutInit(&argc, argv);
	last = glutGet(GLUT_ELAPSED_TIME);
	update_db();
	time_since_last_db_update = glutGet(GLUT_ELAPSED_TIME);
	
	if(!meteorites_created){
		meteorites_created=true;
		create_meteorites();
	}
	int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
	    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

	    // Window dimensions
	    int windowWidth = 800;  // Example width
	    int windowHeight = screenHeight; // Example height

	    int windowX = (screenWidth - windowWidth) / 2;
	int windowY = 0;

	    
	    glutInitWindowPosition(windowX, windowY);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("OpenGL ovidiu Test");
	glutIdleFunc(update); 

	  glutSpecialFunc(special_key_down);
	glutSpecialUpFunc(special_key_up);
	glutKeyboardFunc(start_key);


	glutDisplayFunc(display);
	glutMainLoop();
	update_db();
	printf("Eroare la salvarea datelor!\n");

return 0;}

