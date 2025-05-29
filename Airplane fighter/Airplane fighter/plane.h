#ifndef PLANE_H
#define PLANE_H
struct plane {
	float plane_x;
	float plane_y;
	float plane_green;
	float plane_red;
	int distroid;
};
void draw_airplane(struct plane *my_plane);
void special_key_down(int key, int x, int y);
void special_key_up(int key, int x, int y);
void update_plane_position(struct plane *my_plane);
void colizion(struct plane *my_plane, struct meteorite *meteorites);

#endif
