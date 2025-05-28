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
#include <string.h>

struct player my_player;
struct player players[100];
void update_db() {
	int players_iteretor = 0, i = 0;
	FILE *db = fopen("players_db.txt", "r");

	if (!db) {
		printf("Eroare la deschiderea fișierului (va fi creat)\n");
		// Dacă fișierul nu există, e OK - continuăm fără citire
	} else {
		while (fscanf(db, "%s %s %d %d", players[players_iteretor].username,
				players[players_iteretor].password,
				&players[players_iteretor].nr_of_games,
				&players[players_iteretor].score) != EOF) {

			players_iteretor++;
		}
		fclose(db);
	}
	for (i = 0; i < players_iteretor; i++) {
		if (strcmp(my_player.username, players[i].username) == 0
				&& strcmp(my_player.password, players[i].password) == 0) {

			players[i] = my_player;

		}
	}
	db = fopen("players_db.txt", "w");
	for (i = 0; i < players_iteretor; i++) {
		fprintf(db, "%s %s %d %d\n", players[i].username, players[i].password,
				players[i].nr_of_games, players[i].score);
	}
	fclose(db);
}
int login_user(char username[], char password[]) {
	int players_iteretor = 0;
	FILE *db = fopen("players_db.txt", "r");

	if (!db) {
		printf("Eroare la deschiderea fișierului (va fi creat)\n");
		// Dacă fișierul nu există, e OK - continuăm fără citire
	} else {
		while (fscanf(db, "%s %s %d %d", players[players_iteretor].username,
				players[players_iteretor].password,
				&players[players_iteretor].nr_of_games,
				&players[players_iteretor].score) != EOF) {

			players_iteretor++;
		}
		fclose(db);
	}
	for (int i = 0; i < players_iteretor; i++) {
		if (strcmp(username, players[i].username) == 0
				&& strcmp(password, players[i].password) == 0) {

			my_player = players[i];
			my_player.nr_of_games += 1;
			return 1;  // Username deja folosit
		}
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
	int players_iteretor = 0;
	FILE *db = fopen("players_db.txt", "r");

	if (!db) {
		printf("Eroare la deschiderea fișierului (va fi creat)\n");
		// Dacă fișierul nu există, e OK - continuăm fără citire
	} else {
		while (fscanf(db, "%s %s %d %d", players[players_iteretor].username,
				players[players_iteretor].password,
				&players[players_iteretor].nr_of_games,
				&players[players_iteretor].score) != EOF) {
			if (strcmp(username, players[players_iteretor].username) == 0) {
				fclose(db);
				return 1;  // Username deja folosit
			}
			players_iteretor++;
		}
		fclose(db);
	}

	// Adaugă jucătorul nou
	strcpy(players[players_iteretor].username, username);
	strcpy(players[players_iteretor].password, password);
	players[players_iteretor].nr_of_games = 0;
	players[players_iteretor].score = 0;
	my_player = players[players_iteretor];

	// Scrie în fișier toți jucătorii, inclusiv cel nou
	db = fopen("players_db.txt", "w");
	if (!db) {
		printf("Eroare la salvarea datelor!\n");
		return 0;
	}

	for (int i = 0; i <= players_iteretor; i++) {
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
		scanf("%99s", username); // %99s pentru a evita buffer overflow

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
