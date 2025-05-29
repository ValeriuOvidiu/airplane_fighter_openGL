#include <windows.h>
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
#include <string.h>
int players_iteretor = 0;
struct player players[100];
int player_id = -1;
void update_db() {
	int i = 0;
	FILE *db;
	db = fopen("players_db.txt", "w");

	if (!db) {
		printf("Eroare la deschiderea fișierului (va fi creat)\n");
	} else {

		for (i = 0; i < players_iteretor; i++) {
			fprintf(db, "%s %s %d %d\n", players[i].username,
					players[i].password, players[i].nr_of_games,
					players[i].score);
		}
		fclose(db);
	}


}
int login_user(char username[], char password[]) {
	players_iteretor = 0;
	FILE *db = fopen("players_db.txt", "r");

	if (!db) {
		printf("Eroare la deschiderea fișierului (va fi creat)\n");
	} else {
		while (fscanf(db, "%s %s %d %d", players[players_iteretor].username,
				players[players_iteretor].password,
				&players[players_iteretor].nr_of_games,
				&players[players_iteretor].score) != EOF) {
			if (strcmp(username, players[players_iteretor].username) == 0
					&& strcmp(password, players[players_iteretor].password)
							== 0) {

				player_id = players_iteretor;
				players[player_id].nr_of_games += 1;
			}
			players_iteretor++;
		}
		fclose(db);
	}
	if (player_id != -1) {
		return 1;
	}
	for (int i = 0; i < players_iteretor; i++) {
		strcpy(players[i].username, "");
		strcpy(players[i].password, "");
		players[i].score = 0;
		players[i].nr_of_games = 0;
	}

	return 2;
}

int sign_up_user(char username[], char password[]) {
	FILE *db = fopen("players_db.txt", "r");

	if (!db) {
		printf("Eroare la deschiderea fișierului (va fi creat)\n");
	} else {
		while (fscanf(db, "%s %s %d %d", players[players_iteretor].username,
				players[players_iteretor].password,
				&players[players_iteretor].nr_of_games,
				&players[players_iteretor].score) != EOF) {
			if (strcmp(username, players[players_iteretor].username) == 0) {
				fclose(db);
				players_iteretor = 0;
				return 1;  // Username deja folosit
			}
			players_iteretor++;
		}
		fclose(db);
	}

	// Adaugă jucătorul nou
	strcpy(players[players_iteretor].username, username);
	strcpy(players[players_iteretor].password, password);
	players[players_iteretor].nr_of_games = 1;
	players[players_iteretor].score = 0;
	player_id = players_iteretor;

	// Scrie în fișier toți jucătorii, inclusiv cel nou
	db = fopen("players_db.txt", "w");
	if (!db) {
		printf("Eroare la salvarea datelor!\n");
		return 0;
	}
	++players_iteretor;

	for (int i = 0; i < players_iteretor; i++) {
		fprintf(db, "%s %s %d %d\n", players[i].username, players[i].password,
				players[i].nr_of_games, players[i].score);
	}

	fclose(db);
	return 2;  // Înregistrare cu succes
}

void login_menu() {
	char username[100], password[100];
	int check;

	while (1) {

		printf("Enter your username: ");
		fflush(stdout);
		scanf("%99s", username); // %99s pentru a evita buffer overflow

		printf("Enter your password: ");
		fflush(stdout);
		scanf("%99s", password);

		check = login_user(username, password);

		if (check == 1) {
			break;

		} else if (check == 2) {
			printf("Username or password incorect %s %s\n", username, password);
			fflush(stdout);
		} else {
			printf("An unknown error occurred.\n");
			fflush(stdout);
		}
	}
}




void sign_up_menu() {
	char username[100], password[100];
	int check;

	while (1) {
		printf(
				"Choose your username (without spaces, use \"_\" instead, e.g., ovidiu_dumitru,and maximum of 100 char):\n");
		printf("Enter your username: ");
		fflush(stdout);
		scanf("%99s", username);

		printf(
				"Choose your password (without spaces, use \"_\" instead, e.g., correct_password):\n");
		printf("Enter your password: ");
		fflush(stdout);
		scanf("%99s", password);

		check = sign_up_user(username, password);

		if (check == 1) {
			printf("This username is unavailable.\n");
			fflush(stdout);
		} else if (check == 2) {
			printf("Sign-up successful!\n");
			fflush(stdout);
			break;
		} else {
			printf("An unknown error occurred.\n");
			fflush(stdout);
		}
	}
}




void account_menu() {
	char option;

	while (1) {
		printf(
				"Press letter \"l\" to access the login form, or letter \"s\" to access the sign-up form.\n");
		printf("Enter your choice: ");
		fflush(stdout);

		scanf(" %c", &option); // Spațiul înainte de %c elimină newline-ul rămas în buffer

		if (option == 'l') {
			login_menu();
			break;
		} else if (option == 's') {
			sign_up_menu();
			break;
		} else {
			printf("!!! You chose a wrong option !!! Try again.\n");
		}
	}
}
