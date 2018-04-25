#ifndef _SPRITE_H
#define _SPRITE_H 1

#define C_BLACK makecol(0,0,0)
#define C_WHITE makecol(255,255,255)
#define C_RED makecol(255,0,0)
#define C_BLUE makecol(0,0,255)
#define C_GREEN makecol(0,255,0)
#define stl_button                                style[0]        /* FONT */

#include "allegro.h"
#include <string>
using namespace std;

//These constants variables are changeable
const unsigned char DATA_SPR_SIZE = 3; //Each sprite can contain max. 3 *dat files
const unsigned char IMG_SPR_SIZE = 4; //Each sprite can contain max. 4 images
const unsigned char SND_SPR_SIZE = 2; //Each sprite can contain max. 2 sounds
const unsigned char STYLE_SPR_SIZE = 1; //Each sprite can contain max. 1 font (style)

#define img    0
#define snd    1
#define stl    2

class sprite {
private:
public:
    DATAFILE *data[DATA_SPR_SIZE];
    BITMAP *image[IMG_SPR_SIZE];
    SAMPLE *sound[SND_SPR_SIZE];
    FONT *style[STYLE_SPR_SIZE];
    unsigned char alive;
	unsigned char dir;
    unsigned short int x,y;
    unsigned char width,height;
    signed char velx, vely;
    unsigned char xdelay,ydelay;
    unsigned char xcount,ycount;
    signed char curframe, animdir;
    unsigned char havestopframe,totalframes;
    unsigned char framecount,framedelay;
	unsigned char animcolumns;
	unsigned animstartx, animstarty;
	unsigned char select;
	unsigned char player;
	unsigned char squares, startsquares;
	signed char xcorrect, ycorrect;
	string type, name, text;
	int number;
	int c_color;
	int fill;
	char have_onoff;
	int y1, y2;

public:
	sprite();
	~sprite();
	int load_data_img(char *filename, int files);
	int load_data_snd(char *filename, int files);
	int load_data_style(char *filename, int files);
	void drawframe(BITMAP *dest);
	void drawframe_unit(BITMAP *dest, int col);
	void drawBG(BITMAP *dest);
	void updatePosition();
	void updateAnimation();
};

#endif
