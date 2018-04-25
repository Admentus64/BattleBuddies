#ifndef CHECKMOVE_H
#define CHECKMOVE_H

//////////////////////////////////////////////////////////////////
/// Function to check where the selected unit may move towards ///
//////////////////////////////////////////////////////////////////
void checkmove(sprite *spr)
{     
      if (spr->alive == 0)
           return;
      
      unsigned char i;
      
      for (i=0; i<3; i++) //Up Check
           if (sely-20-40*i > spr->y && sely-60-40*i < spr->y)
                if (selx+20 > spr->x && selx-20 < spr->x)
                     if ((spr->player == turn || spr->player == 10) && spr->alive == 1)
                     {
                          if (nameN == "MEC Hovercraft" && (   spr->name == "Chopper" || spr->name == "Light Tank" || spr->name == "MEC Hovercraft" || spr->name == "Odin" || spr->name == "F9 Fighter" || (spr->name == "BG" && spr->curframe != spr->totalframes)   )   )
                               blockmove[0][i] = 1;
                          if (nameN != "MEC Hovercraft")
                               blockmove[0][i] = 1;
                     }
           
      for (i=0; i<3; i++) //Right Check
           if (selx+60+40*i > spr->x && selx+20+40*i < spr->x)
                if (sely+20 > spr->y && sely-20 < spr->y)
                     if ((spr->player == turn || spr->player == 10) && spr->alive == 1)
                     {
                          if (nameN == "MEC Hovercraft" && (   spr->name == "Chopper" || spr->name == "Light Tank" || spr->name == "MEC Hovercraft" || spr->name == "Odin" || spr->name == "F9 Fighter" || (spr->name == "BG" && spr->curframe != spr->totalframes)   )   )
                               blockmove[1][i] = 1;
                          if (nameN != "MEC Hovercraft")
                               blockmove[1][i] = 1;
                     }
           
      for (i=0; i<3; i++) //Down Check
           if (sely+60+40*i > spr->y && sely+20+40*i < spr->y)
                if (selx+20 > spr->x && selx-20 < spr->x)
                     if ((spr->player == turn || spr->player == 10) && spr->alive == 1)
                     {
                          if (nameN == "MEC Hovercraft" && (   spr->name == "Chopper" || spr->name == "Light Tank" || spr->name == "MEC Hovercraft" || spr->name == "Odin" || spr->name == "F9 Fighter" || (spr->name == "BG" && spr->curframe != spr->totalframes)   )   )
                               blockmove[2][i] = 1;
                          if (nameN != "MEC Hovercraft")
                               blockmove[2][i] = 1;
                     }
           
      for (i=0; i<3; i++) //Left Check
           if (selx-20-40*i > spr->x && selx-60-40*i < spr->x)
                if (sely+20 > spr->y && sely-20 < spr->y)
                     if ((spr->player == turn || spr->player == 10) && spr->alive == 1)
                     {
                          if (nameN == "MEC Hovercraft" && (   spr->name == "Chopper" || spr->name == "Light Tank" || spr->name == "MEC Hovercraft" || spr->name == "Odin" || spr->name == "F9 Fighter" || (spr->name == "BG" && spr->curframe != spr->totalframes)   )   )
                               blockmove[3][i] = 1;
                          if (nameN != "MEC Hovercraft")
                               blockmove[3][i] = 1;
                     }
}

#endif
