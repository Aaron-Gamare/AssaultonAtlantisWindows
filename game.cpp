#include "settings.h"

#define is_down(b) input->buttons[b].is_down 
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

//score of game
global_variable int score = 0;
global_variable int onesdigit = 0;
global_variable int seconddigit = 0;
global_variable int thirddigit = 0;
//dead = 0, alive = 1
typedef enum { dead, alive } status_t;

//struct for all sprites
struct sprite {
	float x;
	float y;
	float vx;
	float vy;
	int frame;
	int NumFrame;
	int counter_frame;
	int counter_y;
	int NumFrame_y;
	int current_frame_y;
	float frame_y[4];
	const unsigned char* image[5];
	status_t life;
};
typedef struct sprite sprite_t;

//create sprites of type sprite_t
sprite_t player;
sprite_t tridents[10];
sprite_t bigships[2];
sprite_t mediumships[3];
sprite_t smallships[2];
sprite_t sharks[8];
sprite_t turtles[8];

int NeedtoDraw = 1;
int leftpressed = 0;
int rightpressed = 0;
int gap_counter_bigship = 0;
int gap_counter_mediumship = 0;
int gap_counter_smallship = 0;
int gap_counter_shark = 0;
int gap_counter_turtle = 0;
int trident50counter = 50;

enum Gamemode {
	GM_MENU,
	GM_GAMEPLAY,
	GM_50TRIDENTS,
	GM_50SECONDS,
	GM_GAMEOVER
};
Gamemode current_gamemode;
Gamemode current_mode;

//Initialize all sprites
internal void Init(void) {

	//Initialize shot tridents
	for (int i = 0; i < 10; i++) {
		tridents[i].frame = 0;
		tridents[i].NumFrame = 5;
		tridents[i].image[0] = tridentsmall1;
		tridents[i].image[1] = tridentsmall2;
		tridents[i].image[2] = tridentsmall3;
		tridents[i].image[3] = tridentsmall4;
		tridents[i].image[4] = tridentsmall5;
		tridents[i].life = dead;
	}

	//Initialize bigships
	for (int i = 0; i < 2; i++) {
		bigships[i].frame = 0;
		bigships[i].NumFrame = 4;
		bigships[i].current_frame_y = 0;
		bigships[i].NumFrame_y = 4;
		bigships[i].frame_y[0] = 90;
		bigships[i].frame_y[1] = 94;
		bigships[i].frame_y[2] = 86;
		bigships[i].frame_y[3] = 94;
		bigships[i].image[0] = bigship1;
		bigships[i].image[1] = bigship2;
		bigships[i].image[2] = bigship3;
		bigships[i].image[3] = bigship2;
		bigships[i].life = dead;
	}

	//Initialize mediumships
	for (int i = 0; i < 3; i++) {
		mediumships[i].frame = 0;
		mediumships[i].NumFrame = 4;
		mediumships[i].current_frame_y = 0;
		mediumships[i].NumFrame_y = 4;
		mediumships[i].frame_y[0] = -40;
		mediumships[i].frame_y[1] = -35;
		mediumships[i].frame_y[2] = -32;
		mediumships[i].frame_y[3] = -35;
		mediumships[i].image[0] = mediumship1;
		mediumships[i].image[1] = mediumship2;
		mediumships[i].image[2] = mediumship3;
		mediumships[i].image[3] = mediumship2;
		mediumships[i].life = dead;
	}

	//Initialize smallships
	for (int i = 0; i < 2; i++) {
		smallships[i].frame = 0;
		smallships[i].NumFrame = 4;
		smallships[i].current_frame_y = 0;
		smallships[i].NumFrame_y = 4;
		smallships[i].frame_y[0] = -100;
		smallships[i].frame_y[1] = -95;
		smallships[i].frame_y[2] = -90;
		smallships[i].frame_y[3] = -95;
		smallships[i].image[0] = smallship1;
		smallships[i].image[1] = smallship2;
		smallships[i].image[2] = smallship3;
		smallships[i].image[3] = smallship2;
		smallships[i].life = dead;
	}

	//Initialize sharks
	for (int i = 0; i < 8; i++) {
		sharks[i].frame = 0;
		sharks[i].NumFrame = 3;
		sharks[i].current_frame_y = 0;
		sharks[i].NumFrame_y = 4;
		sharks[i].frame_y[0] = -172;
		sharks[i].frame_y[1] = -170;
		sharks[i].frame_y[2] = -168;
		sharks[i].frame_y[3] = -170;
		sharks[i].image[0] = shark1;
		sharks[i].image[1] = shark2;
		sharks[i].image[2] = shark3;
		sharks[i].life = dead;
	}

	//Initialize turtles
	for (int i = 0; i < 8; i++) {
		turtles[i].frame = 0;
		turtles[i].NumFrame = 2;
		turtles[i].current_frame_y = 0;
		turtles[i].NumFrame_y = 4;
		turtles[i].frame_y[0] = -247;
		turtles[i].frame_y[1] = -245;
		turtles[i].frame_y[2] = -243;
		turtles[i].frame_y[3] = -245;
		turtles[i].image[0] = turtle1;
		turtles[i].image[1] = turtle2;
		turtles[i].life = dead;
	}
}

//Collision between tridents and other sprites
internal void Collision(void) {
	int x1, y1, x2, y2, x3, y3;
	
	for (int i = 0; i < 3; i++) {
		if (tridents[i].life == alive) {
			x1 = tridents[i].x + 16;
			y1 = tridents[i].y + 30;
			for (int j = 0; j < 2; j++) {
				if (bigships[j].life == alive) {
					x2 = bigships[j].x + 192;
					y2 = bigships[j].y + 104;
					if ((abs(x1 - x2) < 192) && (abs(y1 - y2) < 104)) {
						//bigships[j].frame++;
						bigships[j].life = dead;
						tridents[i].life = dead;
						score += 5;
						if (bigships[j].frame == bigships[j].NumFrame) {
							
							bigships[j].frame = 0;
							
							return;
						}

					}
				}
			}
			for (int j = 0; j < 3; j++) {
				if (mediumships[j].life == alive) {
					x2 = mediumships[j].x + 96;
					y2 = mediumships[j].y + 40;
					if ((abs(x1 - x2) < 96) && (abs(y1 - y2) < 40)) {
						//mediumships[j].frame++;
						tridents[i].life = dead;
						mediumships[j].life = dead;
						score += 3;
						if (mediumships[j].frame == mediumships[j].NumFrame) {
							
							mediumships[j].frame = 0;
							
							return;
						}

					}
				}
			}
			for (int j = 0; j < 2; j++) {
				if (smallships[j].life == alive) {
					x2 = smallships[j].x + 30;
					y2 = smallships[j].y + 20;
					if ((abs(x1 - x2) < 36) && (abs(y1 - y2) < 20)) {
						tridents[i].life = dead;
						smallships[j].life = dead;
						score += 8;
						return;
					}
				}
			}
			for (int j = 0; j < 8; j++) {
				if (sharks[j].life == alive) {
					x2 = sharks[j].x + 32;
					y2 = sharks[j].y + 16;
					if ((abs(x1 - x2) < 37) && (abs(y1 - y2) < 16)) {
						tridents[i].life = dead;
						sharks[j].life = dead;
						score -= 3;
						return;
					}
				}
			}
			for (int j = 0; j < 8; j++) {
				if (turtles[j].life == alive) {
					x2 = turtles[j].x + 32;
					y2 = turtles[j].y + 19;
					if ((abs(x1 - x2) < 32) && (abs(y1 - y2) < 19)) {
						tridents[i].life = dead;
						turtles[j].life = dead;
						score -= 2;
						return;
					}
				}
			}
		}
	}
}

internal void Move(void) {
	for (int i = 0; i < 3; i++) {
		if (tridents[i].life == alive) {
			NeedtoDraw = 1;
			if ((tridents[i].y < 300) && (tridents[i].y > -1000)) {
				tridents[i].x += tridents[i].vx;
				tridents[i].y += tridents[i].vy;
				if (tridents[i].y > -500) {
					tridents[i].frame = 0;
				}
				if (tridents[i].y > -400) {
					tridents[i].frame = 1;
				}
				if (tridents[i].y > -170) {
					tridents[i].frame = 2;
				}
				if (tridents[i].y > -110) {
					tridents[i].frame = 3;
				}
				if (tridents[i].y > 100) {
					tridents[i].frame = 4;
				}
			}
			else {
				tridents[i].life = dead;
			}
		}
	}

	for (int i = 0; i < 2; i++) {
		if (bigships[i].life == alive) {
			NeedtoDraw = 1;
			if (bigships[i].x < -960) {
				bigships[i].life = dead;
				bigships[i].frame = 0;
			}
			if ((bigships[i].y < 500) && (bigships[i].y > -500)) {
				bigships[i].x -= bigships[i].vx;
				bigships[i].y += bigships[i].vy;
				if ((bigships[i].counter_frame % 500) == 0) {
					bigships[i].frame++;
					if (bigships[i].frame == bigships[i].NumFrame) {
						bigships[i].frame = 0;
					}
				}
				bigships[i].counter_frame++;

				if ((bigships[i].counter_y % 300) == 0) {
					bigships[i].current_frame_y++;
					if (bigships[i].current_frame_y == bigships[i].NumFrame_y) {
						bigships[i].current_frame_y = 0;
					}
					bigships[i].y = bigships[i].frame_y[bigships[i].current_frame_y];
				}
				bigships[i].counter_y++;
			}
			else {
				bigships[i].life = dead;
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		if (mediumships[i].life == alive) {
			NeedtoDraw = 1;
			if (mediumships[i].x > 768) {
				mediumships[i].life = dead;
				mediumships[i].frame = 0;
			}
			if ((mediumships[i].y < 500) && (mediumships[i].y > -500)) {
				mediumships[i].x += mediumships[i].vx;
				mediumships[i].y += mediumships[i].vy;
				if ((mediumships[i].counter_frame % 200) == 0) {
					mediumships[i].frame++;
					if (mediumships[i].frame == mediumships[i].NumFrame) {
						mediumships[i].frame = 0;
					}
				}
				mediumships[i].counter_frame++;

				if ((mediumships[i].counter_y % 250) == 0) {
					mediumships[i].current_frame_y++;
					if (mediumships[i].current_frame_y == mediumships[i].NumFrame_y) {
						mediumships[i].current_frame_y = 0;
					}
					mediumships[i].y = mediumships[i].frame_y[mediumships[i].current_frame_y];
				}
				mediumships[i].counter_y++;
			}
			else {
				mediumships[i].life = dead;
			}
		}
	}

	for (int i = 0; i < 2; i++) {
		if (smallships[i].life == alive) {
			NeedtoDraw = 1;
			if (smallships[i].x < -960) {
				smallships[i].life = dead;
			}
			if ((smallships[i].y < 500) && (smallships[i].y > -500)) {
				smallships[i].x -= (smallships[i].vx);
				smallships[i].y += (smallships[i].vy);
				if ((smallships[i].counter_frame % 80) == 0) {
					smallships[i].frame++;
					if (smallships[i].frame == smallships[i].NumFrame) {
						smallships[i].frame = 0;
					}
				}
				smallships[i].counter_frame++;

				if ((smallships[i].counter_y % 200) == 0) {
					smallships[i].current_frame_y++;
					if (smallships[i].current_frame_y == smallships[i].NumFrame_y) {
						smallships[i].current_frame_y = 0;
					}
					smallships[i].y = smallships[i].frame_y[smallships[i].current_frame_y];
				}
				smallships[i].counter_y++;
			}
			else {
				smallships[i].life = dead;
			}
		}
	}
	for (int i = 0; i < 8; i++) {
		if (sharks[i].life == alive) {
			NeedtoDraw = 1;
			if (sharks[i].x > 486) {
				sharks[i].life = dead;
			}
			if ((sharks[i].y < 500) && (sharks[i].y > -500)) {
				sharks[i].x += sharks[i].vx;
				sharks[i].y += sharks[i].vy;
				if ((sharks[i].counter_frame % 500) == 0) {
					sharks[i].frame++;
					if (sharks[i].frame == sharks[i].NumFrame) {
						sharks[i].frame = 0;
					}
				}
				sharks[i].counter_frame++;

				if ((sharks[i].counter_y % 500) == 0) {
					sharks[i].current_frame_y++;
					if (sharks[i].current_frame_y == sharks[i].NumFrame_y) {
						sharks[i].current_frame_y = 0;
					}
					sharks[i].y = sharks[i].frame_y[sharks[i].current_frame_y];
				}
				sharks[i].counter_y++;
			}
			else {
				sharks[i].life = dead;
			}
		}
	}
	for (int i = 0; i < 8; i++) {
		if (turtles[i].life == alive) {
			NeedtoDraw = 1;
			if (turtles[i].x < -960) {
				turtles[i].life = dead;
			}
			if ((turtles[i].y < 500) && (turtles[i].y > -500)) {
				turtles[i].x -= turtles[i].vx;
				turtles[i].y += turtles[i].vy;
				if ((turtles[i].counter_frame % 1000) == 0) {
					turtles[i].frame++;
					if (turtles[i].frame == turtles[i].NumFrame) {
						turtles[i].frame = 0;
					}
					if (turtles[i].vx < 0.2) {
						turtles[i].vx = 0.2;
					}
					else {
						turtles[i].vx = 0.1;
					}
				}
				turtles[i].counter_frame++;

				if ((turtles[i].counter_y % 300) == 0) {
					turtles[i].current_frame_y++;
					if (turtles[i].current_frame_y == turtles[i].NumFrame_y) {
						turtles[i].current_frame_y = 0;
					}
					turtles[i].y = turtles[i].frame_y[turtles[i].current_frame_y];
				}
				turtles[i].counter_y++;
			}
			else {
				turtles[i].life = dead;
			}
		}
	}
}

internal void Fire(void) {
	int i = 0;
	while (tridents[i].life == alive) {
		i++;
		if (i == 3) {
			return;
		}
	}
	tridents[i].x = player_p;
	tridents[i].y = -480;
	tridents[i].vx = 0;
	tridents[i].vy = 0.5;
	tridents[i].image[0] = tridentsmall1;
	tridents[i].life = alive;
	trident50counter--;
}

internal void newspawnbigship() {
	int i = 0;
	while (bigships[i].life == alive) {
		i++;
		if (i == 2) return;
	}
	bigships[i].x = 550;
	bigships[i].vx = 0.2;
	bigships[i].vy = 0;
	//bigships[i].image[0] = im;
	bigships[i].life = alive;
}

internal void newspawnmediumship() {
	int i = 0;
	while (mediumships[i].life == alive) {
		i++;
		if (i == 3) return;
	}
	mediumships[i].x = -960;
	//mediumships[i].y = 0;
	mediumships[i].vx = 0.3;
	mediumships[i].vy = 0;
	//mediumships[i].image[0] = im;
	mediumships[i].life = alive;
}

internal void newspawnsmallship() {
	int i = 0;
	while (smallships[i].life == alive) {
		i++;
		if (i == 2) return;
	}
	smallships[i].x = 900;
	//smallships[i].y = -95;
	smallships[i].vx = 0.5;
	smallships[i].vy = 0;
	//smallships[i].image[0] = im;
	smallships[i].life = alive;
}

internal void newspawnshark() {
	int i = 0;
	while (sharks[i].life == alive) {
		i++;
		if (i == 8) return;
	}
	sharks[i].x = -960;
	//sharks[i].y = -170;
	sharks[i].vx = 0.1;
	sharks[i].vy = 0;
	//sharks[i].image[0] = im;
	sharks[i].life = alive;
}

internal void newspawnturtle() {
	int i = 0;
	while (turtles[i].life == alive) {
		i++;
		if (i == 8) return;
	}
	turtles[i].x = 896;
	//turtles[i].y = -245;
	turtles[i].vx = 0.15;
	turtles[i].vy = 0;
	//turtles[i].image[0] = im;
	turtles[i].life = alive;
}

internal void simulate_player(float *p, float *dp, float ddp, float dt) {
	ddp -= *dp * 10.f;

	//Simulate velocity and acceleration for smoother movement
	*p = *p + *dp * dt + ddp * dt * dt * 0.5f;
	*dp = *dp + ddp * dt;

	//Collision Detection (Player with right side of screen)
	if (*p + player_half_size_x > screen_half_size_x) {
		*p = screen_half_size_x - player_half_size_x;
		*dp = 0;
	}

	//Collision Detection (Player with left side of screen)
	else if (*p + player_half_size_x < -screen_half_size_x) {
		*p = -screen_half_size_x;// +player_half_size_x;
		*dp = 0;
	}
}

internal void spawnhandler(void) {
	
	gap_counter_bigship++;															//To fix overlapping between spawned images
	if (rand() < 15) {
		if (gap_counter_bigship > 2000) {
			gap_counter_bigship = 0;
			newspawnbigship();
		}
	}

	gap_counter_mediumship++;
	if (rand() < 20) {
		if (gap_counter_mediumship > 800) {
			gap_counter_mediumship = 0;
			newspawnmediumship();
		}
	}

	gap_counter_smallship++;
	if (rand() < 10) {
		if (gap_counter_smallship > 200) {
			gap_counter_smallship = 0;
			newspawnsmallship();
		}
	}

	gap_counter_shark++;
	if (rand() < 20) {
		if (gap_counter_shark > 700) {
			gap_counter_shark = 0;
			newspawnshark();
		}
	}

	gap_counter_turtle++;
	if (rand() < 25) {
		if (gap_counter_turtle > 700) {
			gap_counter_turtle = 0;
			newspawnturtle();
		}
	}

	Move();
}
internal void Score(int score) {
	draw_image(780, 420, blackbox, 0);
	if (score < 0) {
		draw_image(815, 420, blackbox, 0);
		draw_image(880, 420, zero, 0);
		draw_image(815, 420, zero, 0);
		draw_image(750, 420, zero, 0);
		score = 0;
	}
	else {
		onesdigit = score % 10;
		seconddigit = (score / 10) % 10;
		thirddigit = (score / 100) % 10;

		//clear score screen
		
		switch (onesdigit) {
			case 0:
				draw_image(880, 420, zero, 0);
				break;
			case 1:
				draw_image(880, 420, one, 0);
				break;
			case 2:
				draw_image(880, 420, two, 0);
				break;
			case 3:
				draw_image(880, 420, three, 0);
				break;
			case 4:
				draw_image(880, 420, four, 0);
				break;
			case 5:
				draw_image(880, 420, five, 0);
				break;
			case 6:
				draw_image(880, 420, six, 0);
				break;
			case 7:
				draw_image(880, 420, seven, 0);
				break;
			case 8:
				draw_image(880, 420, eight, 0);
				break;
			case 9:
				draw_image(880, 420, nine, 0);
				break;
			default:
				return;
		}

		switch (seconddigit) {
			case 0:
				draw_image(815, 420, zero, 0);
				break;
			case 1:
				draw_image(820, 420, one, 0);
				break;
			case 2:
				draw_image(820, 420, two, 0);
				break;
			case 3:
				draw_image(820, 420, three, 0);
				break;
			case 4:
				draw_image(820, 420, four, 0);
				break;
			case 5:
				draw_image(820, 420, five, 0);
				break;
			case 6:
				draw_image(820, 420, six, 0);
				break;
			case 7:
				draw_image(820, 420, seven, 0);
				break;
			case 8:
				draw_image(820, 420, eight, 0);
				break;
			case 9:
				draw_image(820, 420, nine, 0);
				break;
			default:
				return;
		}

		switch (thirddigit) {
			case 0:
				draw_image(755, 420, zero, 0);
				break;
			case 1:
				draw_image(760, 420, one, 0);
				break;
			case 2:
				draw_image(760, 420, two, 0);
				break;
			case 3:
				draw_image(760, 420, three, 0);
				break;
			case 4:
				draw_image(760, 420, four, 0);
				break;
			case 5:
				draw_image(760, 420, five, 0);
				break;
			case 6:
				draw_image(760, 420, six, 0);
				break;
			case 7:
				draw_image(760, 420, seven, 0);
				break;
			case 8:
				draw_image(760, 420, eight, 0);
				break;
			case 9:
				draw_image(760, 420, nine, 0);
				break;
		}
	}
}

internal void draw(void) {
	for (int i = 0; i < 3; i++) {
		if (tridents[i].life) {
			draw_image(tridents[i].x, tridents[i].y, tridents[i].image[tridents[i].frame], 0);
		}
	}
	for (int i = 0; i < 2; i++) {
		if (bigships[i].life) {
			draw_image(bigships[i].x, bigships[i].y, bigships[i].image[bigships[i].frame], 0);
		}
	}
	for (int i = 0; i < 3; i++) {
		if (mediumships[i].life) {
			draw_image(mediumships[i].x, mediumships[i].y, mediumships[i].image[mediumships[i].frame], 0);
		}
	}
	for (int i = 0; i < 2; i++) {
		if (smallships[i].life) {
			draw_image(smallships[i].x, smallships[i].y, smallships[i].image[smallships[i].frame], 0);
		}
	}
	for (int i = 0; i < 8; i++) {
		if (sharks[i].life) {
			draw_image(sharks[i].x, sharks[i].y, sharks[i].image[sharks[i].frame], 0);
		}
	}
	for (int i = 0; i < 8; i++) {
		if (turtles[i].life) {
			draw_image(turtles[i].x, turtles[i].y, turtles[i].image[turtles[i].frame], 0);
		}
	}
	NeedtoDraw = 0;
}

internal void displaycounttrident(int trident50counter) {
	draw_image(-850, 420, blackbox, 0);
	onesdigit = trident50counter % 10;
	seconddigit = (trident50counter / 10) % 10;

	switch (onesdigit) {
	case 0:
		draw_image(-815, 420, zero, 0);
		break;
	case 1:
		draw_image(-820, 420, one, 0);
		break;
	case 2:
		draw_image(-820, 420, two, 0);
		break;
	case 3:
		draw_image(-820, 420, three, 0);
		break;
	case 4:
		draw_image(-820, 420, four, 0);
		break;
	case 5:
		draw_image(-820, 420, five, 0);
		break;
	case 6:
		draw_image(-820, 420, six, 0);
		break;
	case 7:
		draw_image(-820, 420, seven, 0);
		break;
	case 8:
		draw_image(-820, 420, eight, 0);
		break;
	case 9:
		draw_image(-820, 420, nine, 0);
		break;
	default:
		return;
	}

	switch (seconddigit) {
	case 0:
		draw_image(-880, 420, zero, 0);
		break;
	case 1:
		draw_image(-880, 420, one, 0);
		break;
	case 2:
		draw_image(-880, 420, two, 0);
		break;
	case 3:
		draw_image(-880, 420, three, 0);
		break;
	case 4:
		draw_image(-880, 420, four, 0);
		break;
	case 5:
		draw_image(-880, 420, five, 0);
		break;
	case 6:
		draw_image(-880, 420, six, 0);
		break;
	case 7:
		draw_image(-880, 420, seven, 0);
		break;
	case 8:
		draw_image(-880, 420, eight, 0);
		break;
	case 9:
		draw_image(-880, 420, nine, 0);
		break;
	default:
		return;
	}

}

internal void displaytimeleft(int displaytime) {
	draw_image(-850, 420, blackbox, 0);
	onesdigit = displaytime % 10;
	seconddigit = (displaytime / 10) % 10;

	switch (onesdigit) {
	case 0:
		draw_image(-815, 420, zero, 0);
		break;
	case 1:
		draw_image(-820, 420, one, 0);
		break;
	case 2:
		draw_image(-820, 420, two, 0);
		break;
	case 3:
		draw_image(-820, 420, three, 0);
		break;
	case 4:
		draw_image(-820, 420, four, 0);
		break;
	case 5:
		draw_image(-820, 420, five, 0);
		break;
	case 6:
		draw_image(-820, 420, six, 0);
		break;
	case 7:
		draw_image(-820, 420, seven, 0);
		break;
	case 8:
		draw_image(-820, 420, eight, 0);
		break;
	case 9:
		draw_image(-820, 420, nine, 0);
		break;
	default:
		return;
	}

	switch (seconddigit) {
	case 0:
		draw_image(-880, 420, zero, 0);
		break;
	case 1:
		draw_image(-880, 420, one, 0);
		break;
	case 2:
		draw_image(-880, 420, two, 0);
		break;
	case 3:
		draw_image(-880, 420, three, 0);
		break;
	case 4:
		draw_image(-880, 420, four, 0);
		break;
	case 5:
		draw_image(-880, 420, five, 0);
		break;
	case 6:
		draw_image(-880, 420, six, 0);
		break;
	case 7:
		draw_image(-880, 420, seven, 0);
		break;
	case 8:
		draw_image(-880, 420, eight, 0);
		break;
	case 9:
		draw_image(-880, 420, nine, 0);
		break;
	default:
		return;
	}
}

float currenttime = 0.0;
float difference = 0.0;
int gothroughonce = 1;
float timeleft = 740;
int i = 0;
float starttime = 0;
float interval = 0;
int interval_counter = 0;
int my_counter = 0;

internal void simulate_game(Input* input, float dt) {

	make_background();
	if (current_gamemode == GM_GAMEPLAY) {
		draw_image(-880, 420, blackbox, 0);
		if (current_mode == GM_50TRIDENTS) {
			float player_ddp = 0.f;
			//Button Control
			if (is_down(BUTTON_LEFT)) {
				player_ddp -= 10000;
			}
			if (is_down(BUTTON_RIGHT)) {
				player_ddp += 10000;
			}
			if (pressed(BUTTON_SPACE)) {
				Fire();
			}
			if (trident50counter == 0) {
				current_gamemode = GM_GAMEOVER;
			}
			spawnhandler();

			displaycounttrident(trident50counter);
			draw_image(-720, 430, tridentblacksmall, 0);
			Collision();

			if (NeedtoDraw) {
				draw();
			}

			Score(score);

			simulate_player(&player_p, &player_dp, player_ddp, dt);

			draw_image(player_p, -480, tridentsmall1, 0);
		}
		else if (current_mode == GM_50SECONDS) {
			if (gothroughonce == 1) {
				starttime = GetCounter();
				gothroughonce = 0;
			}
			currenttime = GetCounter();
			currenttime = currenttime - starttime;
			
			timeleft = timeleft - currenttime;
			
			if (timeleft < 0) {
				current_gamemode = GM_GAMEOVER;
			}
			/*interval_counter++;
			if (interval_counter == 2000) {
				interval = interval + 14.8;
				interval_counter = 0;
				i++;
				
			}
			my_counter++;
			if (my_counter == 5000) {
				displaytimeleft(50 - i);
				my_counter = 0;
			}*/
			
			for (; i < 50; i++) {
				if (timeleft > (740 - (14.8 * i))) {
					displaytimeleft(50 - i);
					break;
				}
			}

			float player_ddp = 0.f;
			//Button Control
			if (is_down(BUTTON_LEFT)) {
				player_ddp -= 10000;
			}
			if (is_down(BUTTON_RIGHT)) {
				player_ddp += 10000;
			}
			if (pressed(BUTTON_SPACE)) {
				Fire();
			}

			spawnhandler();
			
			Collision();

			if (NeedtoDraw) {
				draw();
			}

			Score(score);

			simulate_player(&player_p, &player_dp, player_ddp, dt);

			draw_image(player_p, -480, tridentsmall1, 0);
		}
		
	}
	else if (current_gamemode == GM_GAMEOVER) {
		for (int y = 250; y < 700; y++) {														//game over background
			u32* pixel = (u32*)render_state.memory + 625 + y * render_state.width;
			for (int x = 0; x < 700; x++) {
				*pixel++ = 0x000000;
			}
		}
		draw_image(-150, 50, gameovertext, 0);
		draw_image(-250, -50, entertostartovertext, 0);

		if (released(BUTTON_ENTER)) {
			current_gamemode = GM_MENU;
			trident50counter = 50;
		}
	}
	else if (current_gamemode == GM_MENU) {
		for (int y = 250; y < 700; y++) {														//menu background
			u32* pixel = (u32*)render_state.memory + 625 + y * render_state.width;
			for (int x = 0; x < 725; x++) {
				*pixel++ = 0x000000;
			}
		}

		draw_image(-225, 100, gamemodetext, 0);
		
		if (is_down(BUTTON_LEFT) || (leftpressed == 1)) {
			leftpressed = 1;
			rightpressed = 0;
			for (int y = 343; y < 558; y++) {
				u32* pixel = (u32*)render_state.memory + 666 + y * render_state.width;
				for (int x = 250; x < 568; x++) {
					*pixel++ = 0xFFFFFF;
				}
			}
		}
		if (is_down(BUTTON_RIGHT) || (rightpressed == 1)) {
			rightpressed = 1;
			leftpressed = 0;
			for (int y = 343; y < 558; y++) {
				u32* pixel = (u32*)render_state.memory + 990 + y * render_state.width;
				for (int x = 250; x < 568; x++) {
					*pixel++ = 0xFFFFFF;
				}
			}
		}

		for (int y = 350; y < 550; y++) {														
			u32* pixel = (u32*)render_state.memory + 675 + y * render_state.width;
			for (int x = 0; x < 300; x++) {
				*pixel++ = 0x255A68;
			}
		}
		
		draw_image(-240, -20, maxoftext, 0);
		draw_image(-250 , -125, fiveblue, 0);
		draw_image(-200, -125, zeroblue, 0);
		draw_image(-100, -150, tridentdark, 0);

		for (int y = 350; y < 550; y++) {
			u32* pixel = (u32*)render_state.memory + 1000 + y * render_state.width;
			for (int x = 0; x < 300; x++) {
				*pixel++ = 0x255A68;
			}
		}

		draw_image(95, -20, maxoftext, 0);
		draw_image(55, -125, fiveblue, 0);
		draw_image(105, -125, zeroblue, 0);
		draw_image(180, -110, secstext, 0);

		if (is_down(BUTTON_SPACE)) {
			current_gamemode = GM_GAMEPLAY;
			if (leftpressed == 1) {
				current_mode = GM_50TRIDENTS;
			}
			else if(rightpressed == 1) {
				current_mode = GM_50SECONDS;
				gothroughonce = 1;
				currenttime = 0;
			}
		}
		/*for (int y = 255; y < 320; y++) {
			u32* pixel = (u32*)render_state.memory + 800 + y * render_state.width;
			for (int x = 0; x < 400; x++) {
				*pixel++ = 0x255A68;
			}
		}*/
		//draw_image(-110, -250, highscoresbluetext, 0);
	}
}