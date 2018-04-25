#include <allegro.h>
#include "sprite.h"

sprite::sprite()
{
    for (int i=0; i<DATA_SPR_SIZE; i++)
         data[i] = NULL;
    for (int i=0; i<IMG_SPR_SIZE; i++)
         image[i] = NULL;    
    for (int i=0; i<SND_SPR_SIZE; i++)
         sound[i] = NULL;
    for (int i=0; i<STYLE_SPR_SIZE; i++)
         style[i] = NULL;
    alive = 0;
    dir = 0;
    animcolumns = 8;
    animstartx = 0; 
    animstarty = 0;
    x = 0;
    y = 0;
    width = 0; 
    height = 0;
    xdelay = 0; 
    ydelay = 0;
    xcount = 0; 
    ycount = 0;
    velx = 0 ;
    vely = 0;
    curframe = 0; 
    havestopframe = 0;
    totalframes = 1;
    framecount = 0; 
    framedelay = 10;
    animdir = 1;
    select = 0;
    player = 0;
    startsquares = 2;
    squares = startsquares;
    xcorrect = 0;
    ycorrect = 0;
    type = "";
    name = "";
    text = "";
    c_color = 0;
    fill = 0;
    have_onoff = 0;
    y1 = 0, y2 = 0; 
}

sprite::~sprite()
{
    for (int i=0; i<DATA_SPR_SIZE; i++)
         if (data[i] != NULL)
              unload_datafile(data[i]);
}

int sprite::load_data_img(char *filename, int files) //Loading images from *dat files, one function can call all files at once
{
     data[img] = load_datafile(filename);
    
     for (int i=0; i<files; i++)
          if (image[i] == NULL)
          {
               image[i] = (BITMAP *)data[img][i].dat;
               if (image[i] == NULL)
                    return 0;
               width = image[i]->w;
               height = image[i]->h;
          }
          return 1;
}

int sprite::load_data_snd(char *filename, int files) //Loading sounds from *dat files, one function can call all files at once
{
     data[snd] = load_datafile(filename);
    
     for (int i=0; i<files; i++)
          if (sound[i] == NULL)
          {
               sound[i] = (SAMPLE *)data[snd][i].dat;
               if (sound[i] == NULL)
                    return 0;
          }
          return 1;
}

int sprite::load_data_style(char *filename, int files) //Loading fonts (styles) from *dat files, one function can call all files at once
{
     data[stl] = load_datafile(filename);
    
     for (int i=0; i<files; i++)
          if (style[i] == NULL)
          {
               style[i] = (FONT *)data[stl][i].dat;
               if (style[i] == NULL)
                    return 0;
          }
          return 1;
}

void sprite::drawframe(BITMAP *dest)
{
     if (alive == 0)
          return;

     if (name == "Arrow")
     {
          int fxx = animstartx + (totalframes % animcolumns) * width;
          int fyy = animstarty + (totalframes / animcolumns) * height;
          masked_blit(image[dir],dest,fxx,fyy,(int)x,(int)y,width,height);
     }

     int fx = animstartx + (curframe % animcolumns) * width;
     int fy = animstarty + (curframe / animcolumns) * height;
    
     masked_blit(image[dir],dest,fx,fy,(int)x,(int)y,width,height);

     //Drawing text for buttons
     if (text != "" && name == "Button")
          if (style[0] != NULL)
               textprintf_centre_ex(dest, stl_button, x+width/2, y+2, C_BLACK ,-1, text.c_str());
}

void sprite::drawframe_unit(BITMAP *dest, int col)
{
     if (alive == 0)
          return;
     
     int fx = animstartx + (curframe % animcolumns) * width;
     int fy = animstarty + (curframe / animcolumns) * height;
    
     masked_blit(image[dir],dest,fx,fy,(int)x,(int)y,width,height);
     
     if (name == "Bullet")
          return;
     
     //Drawing the circle around the selected unit
     if (select == 1)
          circle(dest, x+width/2, y+height/2, 25, C_RED);
     
     if (col == 0 || col == 1)
          c_color = makecol(255, 255, 255);
     if (col == 2)
          c_color = makecol(0, 0, 0);
     
     //Drawing player numbers at all units
     if (player == 1 || player == 2)
          textprintf_ex(dest, font, x-xcorrect+2, y-ycorrect+30, c_color ,-1, "%d", squares);
          
     //Drawing player colors at all units
     if (player == 1)
          circlefill(dest, x-xcorrect+3, y-ycorrect+3, 3, C_BLUE);
     if (player == 2)
          circlefill(dest, x-xcorrect+4, y-ycorrect+4, 3, C_RED);
}

void sprite::drawBG(BITMAP *dest)
{
     if (alive == 0)
          return;

     int fx = animstartx + (curframe % animcolumns) * width;
     int fy = animstarty + (curframe / animcolumns) * height;
     
     unsigned char hor = 0, ver = 1;
     
     for (int i=0; i<100; i++)
     {
          hor++;
          if (hor == 11)
          {
               hor = 1;
               ver++;
          }

          masked_blit(image[dir],dest,fx,fy,hor*41,ver*41,width,height);
     }
}


void sprite::updatePosition()
{
     //update x position
     if (++xcount > xdelay)
     {
         xcount = 0;
         x += velx;
     }

    //update y position
     if (++ycount > ydelay)
     {
         ycount = 0;
         y += vely;
     }
}

void sprite::updateAnimation() 
{
     //update frame based on animdir

     if (name == "Light Tank")
          if (velx == 0 && vely == 0)
               return;

     if (havestopframe == 1 && (velx == 0 && vely == 0)   )
          { curframe = 0; return; }
    
     if (++framecount > framedelay)
     {
          framecount = 0;
          curframe += animdir;

          if (curframe < 0)
               curframe = totalframes;
		  if (curframe > totalframes)
               curframe = 0;
        
          if (curframe == 0 && havestopframe == 1)
               curframe += 1;
     }
}
