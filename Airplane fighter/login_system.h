#ifndef LOGIN_H
# define LOGGIN_H
struct player {
	char username[100];
	char password[100];
	int score;
	int nr_of_games;
};
void drow_loggin_form();
#endif
