#ifndef SETUP_H
#define SETUP_H

//Include lib files
#include "allegro.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

//Define some constants
#define NUM 41 //units
#define NUM_B 9
#define NUM_MENU_B 23
#define O_WIDTH 640
#define O_HEIGHT 480

//Define colours
#define C_BLACK makecol(0,0,0)
#define C_WHITE makecol(255,255,255)
#define C_RED makecol(255,0,0)
#define C_BLUE makecol(0,0,255)
#define C_PINK makecol(255,0,255)
#define C_YELLOW makecol(255,255,0)
#define C_LIGHTBLUE makecol(0,255,255)
#define C_BROWN makecol(80,25,25)
#define C_GRAY makecol(125,125,125)
#define C_GREEN makecol(0,255,0)
#define C_PURPLE makecol(150,60,220)

//Include project c++ files
#include "defines.h"
#include "sprite.h"
#include "spritehandler.h"

//Defines Rescources size
const unsigned char TOTAL_FILES = 11;
const unsigned char TYPE_FILES = 9;
const unsigned char DATA_SIZE = 11;

const unsigned char TEMP_SIZE = 6;

const unsigned char IMG_CORE_SIZE = 7;
const unsigned char IMG_SETTING_SIZE = 3;
const unsigned char IMG_GUIDE_SIZE = 1;

const unsigned char SND_BUTTON_SIZE = 5;
const unsigned char SND_FIGHT_SIZE = 4;
const unsigned char SND_GAME_SIZE = 7;

const unsigned char MID_AFTERMATCH_SIZE = 4;
const unsigned char MID_MENU_SIZE = 5;
const unsigned char MID_PREPARATION_SIZE = 5;
const unsigned char MID_THEME_SIZE = 10;

const unsigned char FONT_SIZE = 6;

//Rescources
DATAFILE *datafiles[DATA_SIZE];

DATAFILE *temp_data[TEMP_SIZE];
BITMAP *temp_sprite[TEMP_SIZE];

BITMAP *img_core[IMG_CORE_SIZE];
BITMAP *img_setting[IMG_SETTING_SIZE];
BITMAP *img_guide[IMG_GUIDE_SIZE];

SAMPLE *snd_button[SND_BUTTON_SIZE];
SAMPLE *snd_fight[SND_FIGHT_SIZE];
SAMPLE *snd_game[SND_GAME_SIZE];

MIDI *mid_aftermatch[MID_AFTERMATCH_SIZE];
MIDI *mid_menu[MID_MENU_SIZE];
MIDI *mid_preparation[MID_PREPARATION_SIZE];
MIDI *mid_theme[MID_THEME_SIZE];

FONT *fonts[FONT_SIZE];

BITMAP *buffer;
unsigned char file_missing[TOTAL_FILES][TYPE_FILES];
unsigned char file_is_missing = 0;

//Init sprite objects
sprite *button;               spritehandler *buttons;
sprite *bg_main;              spritehandler *bg_mains;
sprite *unit;                 spritehandler *units;
sprite *nonunit;              spritehandler *nonunits;

//Declare score struct
struct score
{
     int points;
     string player;
};

//Function prototypes for startup & shutdown & error of startup
void startgame();
void reading_all_setting_files();
void reading_highscore_file();
void files_not_found();
void setup_coords();
void check_resources();
void load_resources1();
void load_resources2();
void endgame();
void reset_variables();
void startpos();
void erase_sprites();
void init_sprites();
void place_units();
void start_intro_movie();

//Function prototypes for menu
void init_menu_sprites();
void edit_menu_sprites();
void loop_submenu1();
void loop_submenu2();
void loop_submenu3();
string input_change_name(string temp_name);
void check_for_change_settings();

//Function prototypes for commands
int read_data(char *filename, char row, short int reset, short int min, short int max);
string read_string_data(char *filename, char row);
void write_data(char *filename, short int row1, short int row2);
void write_string_data(char *filename, string row1, string row2);
void read_music_data(char *filename);
void read_credits_data(char *filename);
void read_guide_data(char *filename);
void draw_guide_data(char *filename, char file, char image, short int source_x, short int source_y, short int x, short int y, short int width, short int height);
void read_highscore_data(char *filename);
void sort_highscore(vector<score>& highscore);
void init_menuloop();
void update_screen_errormode();
void update_screen();
void erase_unit(sprite *spr);
void press_option(sprite *spr);
void press_button(sprite *spr);
void release_option(sprite *spr);
void release_button(sprite *spr);
void draw_bar(BITMAP *dest, unsigned char bar, float fill);
void keyboard_registering();
void timer();

//Function prototypes for main game
void check_outcome();
void check_game_buttons();
void checkmove(sprite *spr);
void checkwater(sprite *spr);
void release_deselect_unit(sprite *spr);
void init_fight(sprite *spr);
void resetunit(sprite *spr);
void release_move_unit(sprite *spr);
void draw_hud(sprite *spr);
void activate_bullet(unsigned char dir, signed char speedx, signed char speedy, unsigned short int x, unsigned short int y);
void press_select_unit(sprite *spr);
void release_select_unit(sprite *spr);
void activate_explosion(sprite *spr, unsigned char win_lose);

//Function prototypes for music
void start_music();
void control_music();

//Timer Variables
unsigned char counter;
const char updates_per_second = 1;

//Movement variables
unsigned char selected, move, fight;
unsigned short int selx, sely, endpos;

//Mouse variables
unsigned short int mx, my;
unsigned char mb1, mb2;
unsigned char mb1_hold = 0, mb2_hold = 0, inside = 0, cur_button;
unsigned char mouse_over = 0;
signed short int gmx, gmy;
unsigned char ACC = 1;
unsigned char cur_unit = 0;

//Gameplay variables
unsigned char turn, gamestop, round;
unsigned char game_outcome, resign;
unsigned char units_left[3];
unsigned int C_COLOR;
unsigned char bullet_shooting = 0;

//Gameplay Preparation variables
unsigned char temp_disable_bg = 0;
unsigned char restart = 0;
unsigned char unloaded_prep_music = 0;
unsigned char cur_placement, unit_is_placed;
unsigned char unit_place_i, unit_place_j;
unsigned char bg_scenery, last_bg_scenery = 10;

//Music variables
unsigned char song_pick;
volatile short int song_length;
unsigned short int song_length_copy;
signed char song_length_min, song_length_sec;
string song_name;

//Misc. variables
unsigned char n, curn, curnb;
string nameN, typeN;
unsigned short int radius;
unsigned char starttext;
signed char grid_number;
unsigned char reroll = 0;
unsigned char NUM_BG;
unsigned char key_is_pressed = 0, key_activated = 0;
unsigned char confirm_stop = 0;
unsigned char keyboard_pressed = 0;
unsigned char keyboard_is_pressed = 0;

//Menu variables
string choice_menu = "Back";
unsigned char allow_edit = 0;
unsigned char edit_name1 = 0, edit_name2 = 0;
unsigned char error_reading = 0;
unsigned char EDIT_RESOLUTION = 0;
unsigned char cur_slide = 0;

//Settings variables (with default worths)
unsigned char error_reading_file = 0;
unsigned char MODE;
unsigned char SWITCH_MODE;
unsigned char REFRESH_RATE;
unsigned short int WIDTH, NEW_WIDTH;
unsigned short int HEIGHT, NEW_HEIGHT;
unsigned char REST_DUR;
unsigned char COLOR_DEPTH;
unsigned char HARDWARE_CURSOR;
unsigned char SPEED_CURSOR;
unsigned char VOLUME_SND;
unsigned char VOLUME_MID;
unsigned char PLAY_MOVIE;
string PLAYER_NAME1, PLAYER_NAME2;
unsigned char MAX_SLIDE;

//Init lists & vectors
unsigned char blockmove[4][3];
unsigned short int coord_x[11], coord_y[11];
unsigned char temp_sprite_loaded[TEMP_SIZE];
unsigned char got_unit[1];
char s[40];
vector<string>song_name_prep;
score temp_score;
vector<score>highscore;

#endif
