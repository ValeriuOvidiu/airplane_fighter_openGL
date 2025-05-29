#ifndef METEORITES_H
# define METEORITES_H
struct meteorite {
	float meteorite_x;
	float meteorite_y;
	float meteorite_begin;
	float meteorite_r;

};

void draw_meteorite(float x, float y, float radius);
float randf(float min, float max);
void create_meteorites();


#endif
