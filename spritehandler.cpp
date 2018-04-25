#include "spritehandler.h"

spritehandler::spritehandler(void)
{
	count = 0;
}

spritehandler::~spritehandler(void)
{
    //delete the sprites
	for (unsigned char n = 0; n < count; n++)
		delete sprites[n];
}

void spritehandler::add(sprite *spr) 
{
	if (spr != NULL) {
		sprites[count] = spr;
		count++;
	}
}

void spritehandler::create() 
{
	sprites[count] = new sprite();
	count++;
}

sprite *spritehandler::get(unsigned char index)
{
	return sprites[index];
}

