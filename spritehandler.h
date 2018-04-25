#pragma once
#include "sprite.h"

class spritehandler
{
private:
	unsigned char count;
	sprite *sprites[45];

public:
	spritehandler(void);
	~spritehandler(void);
	void add(sprite *spr);
	void create();
	sprite *get(unsigned char index);
	unsigned char size() { return count; }
};
