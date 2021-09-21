#pragma once
float player_p, player_dp;
float player_half_size_x = 32;

float bigship_p = 550;
float bigship_dp = 0.1;

float mediumship_p = -1000;
float mediumship_dp = 0.3;

float smallship_p = 400;
float smallship_dp = 0.6;

float shark_p = -1000;
float shark_dp = 0.2;

float turtle_p = 900;
float turtle_dp = 0.2;

float screen_half_size_x = 960;
float screen_half_size_y = 540;

const unsigned char* bigships_images[] = { bigship1, bigship2, bigship3, bigship2 };
const unsigned char* mediumships_images[] = { mediumship1, mediumship2, mediumship3, mediumship2 };
const unsigned char* smallships_images[] = { smallship1, smallship2, smallship3, smallship2 };
const unsigned char* sharks_images[] = { shark1, shark2, shark3, shark2};
const unsigned char* turtle_images[] = { turtle2, turtle1 };

float bigship_y[] = { 145, 150, 155, 150 };
float mediumship_y[] = { -5, 0, 5, 0 };
float smallship_y[] = { -100, -95, -90, -95 };
float shark_y[] = { -172, -170, -168, -170 };
float turtle_y[] = { -247, -245, -243, -245 };

int counter = 0;
int counter_y = 0;
int framecount = 0;
int framecount_y = 0;

int frame_medium_count_y = 0;
int frame_medium_count = 0;
int counter_medium_ship = 0;
int counter_mediumship_y = 0;

int counter_small_ship = 0;
int frame_small_count = 0;
int counter_smallship_y = 0;
int frame_small_count_y = 0;

int counter_shark = 0;
int frame_shark_count = 0;
int counter_shark_y = 0;
int frame_shark_count_y = 0;

int counter_turtle = 0;
int frame_turtle_count = 0;
int counter_turtle_y = 0;
int frame_turtle_count_y = 0;