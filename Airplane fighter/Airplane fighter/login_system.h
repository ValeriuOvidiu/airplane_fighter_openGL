#ifndef LOGGIN_H
#define LOGGIN_H
struct player {
	char username[100];
	char password[100];
	int score;
	int nr_of_games;
};
void update_db();
void account_menu();
#endif
