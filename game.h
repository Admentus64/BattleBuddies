#ifndef GAME_H
#define GAME_H

//////////////////////////////////
/// Function to select an unit ///
//////////////////////////////////
void press_select_unit(sprite *spr)
{
     if (spr->alive == 0 || spr->player != turn || spr->squares == 0)
          return;
     
     if (spr->select == 1)
          if (mx > spr->x   &&   mx < spr->x+spr->width   &&   my > spr->y   &&   my < spr->y+spr->height)
               return;
       
     if (counter == 0 && mb1 && mb1_hold == 0)
          if (mx > spr->x   &&   mx < spr->x+spr->width   &&   my > spr->y   &&   my < spr->y+spr->height)
          {
               curn = n;
               mb1_hold = 1;
               nameN = spr->name;
               
               for (unsigned char i=0; i<NUM; i++)
                    if (units->get(i)->select == 1)
                    {
                         units->get(i)->select = 0;
                         selected = 0;
                    }
          }
}

void release_select_unit(sprite *spr)
{
     if (spr->select == 1)
          return;
     
          if (!mb1 && inside == 1)
          {
               if (units->get(curn)->select == 1)
                    units->get(curn)->select = 0;
               
               typeN = spr->type;
               selected = 1;
               spr->select = 1;
               play_sample(snd_unit_select, 255, 128, 1000, FALSE);             //Each unit has his own sounds within the spritehandler
               selx = spr->x;
               sely = spr->y;
               fight = 0;
               if (confirm_stop == 1)
                    confirm_stop = 0;
          
               for (unsigned char i=0; i<4; i++)
                    for (unsigned char j=0; j<3; j++)
                         blockmove[i][j] = 0;
          
               if (starttext != 3)
                    starttext = 3;
          
               for (unsigned char i=0; i<NUM; i++)
                    checkmove(units->get(i));
               for (unsigned char i=0; i<NUM_BG; i++)
                    checkmove(bg_mains->get(i));
               
               for (unsigned char i=1; i<6; i++)
                    nonunits->get(i)->alive = 0;
               
               if (nameN == "Chopper")
               {
                     nonunits->get(4)->x = 500; nonunits->get(4)->y = 195; nonunits->get(4)->alive = 1;
                     
                     nonunits->get(3)->x = 500; nonunits->get(3)->y = 255; nonunits->get(3)->alive = 1;
                     nonunits->get(5)->x = 550; nonunits->get(5)->y = 255; nonunits->get(5)->alive = 1;
               }
               if (nameN == "Light Tank")
               {
                     nonunits->get(4)->x = 500; nonunits->get(4)->y = 195; nonunits->get(4)->alive = 1;
                     
                     nonunits->get(3)->x = 500; nonunits->get(3)->y = 255; nonunits->get(3)->alive = 1;
                     nonunits->get(5)->x = 550; nonunits->get(5)->y = 255; nonunits->get(5)->alive = 1;
               }
               if (nameN == "MEC Hovercraft")
               {
                     nonunits->get(1)->x = 500; nonunits->get(1)->y = 195; nonunits->get(1)->alive = 1;
                     nonunits->get(2)->x = 550; nonunits->get(2)->y = 195; nonunits->get(2)->alive = 1;
                     
                     nonunits->get(4)->x = 500; nonunits->get(4)->y = 255; nonunits->get(4)->alive = 1;
               }
               if (nameN == "Odin")
               {
                     nonunits->get(3)->x = 500; nonunits->get(3)->y = 195; nonunits->get(3)->alive = 1;
                     nonunits->get(5)->x = 550; nonunits->get(5)->y = 195; nonunits->get(5)->alive = 1;
                     
                     nonunits->get(1)->x = 500; nonunits->get(1)->y = 255; nonunits->get(1)->alive = 1;
                     nonunits->get(2)->x = 550; nonunits->get(2)->y = 255; nonunits->get(2)->alive = 1;
               }
               if (nameN == "F9 Fighter")
               {
                     nonunits->get(1)->x = 500; nonunits->get(1)->y = 195; nonunits->get(1)->alive = 1;
                     nonunits->get(2)->x = 550; nonunits->get(2)->y = 195; nonunits->get(2)->alive = 1;
                     
                     nonunits->get(4)->x = 500; nonunits->get(4)->y = 255; nonunits->get(4)->alive = 1;
               }
               
          }
          
          if (!mb1)
          {
               inside = 0;
               mb1_hold = 0;
          }

          if (mb1_hold == 1)
          {
               if (mx > spr->x   ||   mx < spr->x+spr->width   ||   my > spr->y   ||   my < spr->y+spr->height)
                    inside = 1;
               if (mx < spr->x   ||   mx > spr->x+spr->width   ||   my < spr->y   ||   my > spr->y+spr->height)
                    inside = 0;
          }
}

////////////////////////////////////////////////////////////////
/// Function to deselect units when releasing mouse button 2 ///
////////////////////////////////////////////////////////////////
void release_deselect_unit(sprite *spr)
{ 
     selected = 0;
     spr->select = 0;
     mb2_hold = 0;
     
     for (unsigned char i=1; i<6; i++)
          nonunits->get(i)->alive = 0;
}

/////////////////////////////////////////
/// Function to move the unit around ///
////////////////////////////////////////
void release_move_unit(sprite *spr)
{
     if (spr->alive == 0 || spr->select == 0)
          return;
     
     //Don't allow moving outside the field
     if (mx > 439 || mx < 41 || my > 439 || my < 41)
          return;

     mb1_hold = 0;
     
     //Moving 1 square
     if (mx > spr->x   &&   my > spr->y-40   &&   mx < spr->x+spr->width   &&   my < spr->y+spr->height-40) //Up
          { if (blockmove[0][0] == 1 || spr->squares < 1)
               { play_sample(snd_move_error, 255, 128, 1000, FALSE); return; }
                    endpos = spr->y-41; spr->dir = 0; spr->vely = -1; spr->squares -= 1; }
     if (mx > spr->x+40   &&   my > spr->y   &&   mx < spr->x+spr->width+40   &&   my < spr->y+spr->height) //Right
          { if (blockmove[1][0] == 1 || spr->squares < 1)
               { play_sample(snd_move_error, 255, 128, 1000, FALSE); return; }
                    endpos = spr->x+41; spr->dir = 1; spr->velx = 1; spr->squares -= 1; }
     if (mx > spr->x   &&   my > spr->y+40   &&   mx < spr->x+spr->width   &&   my < spr->y+spr->height+40) //Down
          { if (blockmove[2][0] == 1 || spr->squares < 1)
               { play_sample(snd_move_error, 255, 128, 1000, FALSE); return; }
                    endpos = spr->y+41; spr->dir = 2; spr->vely = 1; spr->squares -= 1; }
     if (mx > spr->x-40   &&   my > spr->y   &&   mx < spr->x+spr->width-40   &&   my < spr->y+spr->height) //Left
          { if (blockmove[3][0] == 1 || spr->squares < 1)
               { play_sample(snd_move_error, 255, 128, 1000, FALSE); return; }
                    endpos = spr->x-41; spr->dir = 3; spr->velx = -1; spr->squares -= 1; }

     //Moving 2 squares
     if (mx > spr->x   &&   my > spr->y-80   &&   mx < spr->x+spr->width   &&   my < spr->y+spr->height-80) //Up
     {
          if (spr->name != "F9 Fighter" && (blockmove[0][0] == 1 || blockmove[0][1] == 1 || spr->squares < 2)   )
          {
               play_sample(snd_move_error, 255, 128, 1000, FALSE);
               return;
          }
          if (spr->name == "F9 Fighter" && (blockmove[0][1] == 1 || spr->squares < 2)   )
          {
               play_sample(snd_move_error, 255, 128, 1000, FALSE);
               return;
          }
          endpos = spr->y-82;
          spr->dir = 0;
          spr->vely = -1;
          spr->squares -= 2;
     }
     if (mx > spr->x+80   &&   my > spr->y   &&   mx < spr->x+spr->width+80   &&   my < spr->y+spr->height) //Right
     {
          if (spr->name != "F9 Fighter" && (blockmove[1][0] == 1 || blockmove[1][1] == 1 || spr->squares < 2)   )
          {
               play_sample(snd_move_error, 255, 128, 1000, FALSE);
               return;
          }
          if (spr->name == "F9 Fighter" && (blockmove[1][1] == 1 || spr->squares < 2)   )
          {
               play_sample(snd_move_error, 255, 128, 1000, FALSE);
               return;
          }
          endpos = spr->x+82;
          spr->dir = 1;
          spr->velx = 1;
          spr->squares -= 2;
     }
     if (mx > spr->x   &&   my > spr->y+80   &&   mx < spr->x+spr->width   &&   my < spr->y+spr->height+80) //Down
     {
          if (spr->name != "F9 Fighter" && (blockmove[2][0] == 1 || blockmove[2][1] == 1 || spr->squares < 2)   )
          {
               play_sample(snd_move_error, 255, 128, 1000, FALSE);
               return;
          }
          if (spr->name == "F9 Fighter" && (blockmove[2][1] == 1 || spr->squares < 2)   )
          {
               play_sample(snd_move_error, 255, 128, 1000, FALSE);
               return;
          }
          endpos = spr->y+82;
          spr->dir = 2;
          spr->vely = 1;
          spr->squares -= 2;
     }
     if (mx > spr->x-80   &&   my > spr->y   &&   mx < spr->x+spr->width-80   &&   my < spr->y+spr->height) //Left
     {
          if (spr->name != "F9 Fighter" && (blockmove[3][0] == 1 || blockmove[3][1] == 1 || spr->squares < 2)   )
          {
               play_sample(snd_move_error, 255, 128, 1000, FALSE);
               return;
          }
          if (spr->name == "F9 Fighter" && (blockmove[3][1] == 1 || spr->squares < 2)   )
          {
               play_sample(snd_move_error, 255, 128, 1000, FALSE);
               return;
          }
          endpos = spr->x-82;
          spr->dir = 3;
          spr->velx = -1;
          spr->squares -= 2;
     }
     
     //Moving 3 squares
     if (mx > spr->x   &&   my > spr->y-120   &&   mx < spr->x+spr->width   &&   my < spr->y+spr->height-120) //Up
          { if (blockmove[0][0] == 1 || blockmove[0][1] == 1 || blockmove[0][2] == 1 || spr->squares < 3)
               { play_sample(snd_move_error, 255, 128, 1000, FALSE); return; }
               endpos = spr->y-123; spr->dir = 0; spr->vely = -1; spr->squares -= 3; }
     if (mx > spr->x+120   &&   my > spr->y   &&   mx < spr->x+spr->width+120   &&   my < spr->y+spr->height) //Right
          { if (blockmove[1][0] == 1 || blockmove[1][1] == 1 || blockmove[1][2] == 1 || spr->squares < 3)
               { play_sample(snd_move_error, 255, 128, 1000, FALSE); return; }
               endpos = spr->x+123; spr->dir = 1; spr->velx = 1; spr->squares -= 3; }
     if (mx > spr->x   &&   my > spr->y+120   &&   mx < spr->x+spr->width   &&   my < spr->y+spr->height+120) //Down
          { if (blockmove[2][0] == 1 || blockmove[2][1] == 1 || blockmove[2][2] == 1 || spr->squares < 3)
               { play_sample(snd_move_error, 255, 128, 1000, FALSE); return; }
               endpos = spr->y+123; spr->dir = 2; spr->vely = 1; spr->squares -= 3; }
     if (mx > spr->x-120   &&   my > spr->y   &&   mx < spr->x+spr->width-120   &&   my < spr->y+spr->height) //Left
          { if (blockmove[3][0] == 1 || blockmove[3][1] == 1 || blockmove[3][2] == 1 || spr->squares < 3)
               { play_sample(snd_move_error, 255, 128, 1000, FALSE); return; }
               endpos = spr->x-123; spr->dir = 3; spr->velx = -1; spr->squares -= 3; }
          
     //Executing the move if the sprite's speed is not 0
     if (spr->vely != 0 || spr->velx != 0)
     {
          move = 1;
          counter = 2;
          play_sample(snd_unit_move, 255, 128, 1000, FALSE);
     }
}

//////////////////////////////////////////////////////////////////////
/// Function to stop moving the unit when reaching its destination ///
//////////////////////////////////////////////////////////////////////
void resetunit_arrive(sprite *spr)
{
     if (spr->alive == 0 || spr->select == 0)
          return;
     
     selx = spr->x;
     sely = spr->y;
     
     if ( (spr->y == endpos && (spr->dir == 0 || spr->dir == 2)) || (spr->x == endpos && (spr->dir == 1 || spr->dir == 3))   ) //|| fight == 2)
     {
          spr->select = 0;
          spr->vely = 0;
          spr->velx = 0;
          move = 0;
          selected = 0;
          counter = 0;
          fight = 0;
          
          //Checking is the Light Tank is in range for firing a bullet against the enemy
          if (spr->name == "Light Tank")
          {
               for (n=1; n<41; n++)
               {
                    if (units->get(n)->alive == 1 && units->get(n)->player != turn)
                    {
                         if (spr->dir == 0)
                              if (spr->y-20 > units->get(n)->y   &&   spr->y-60 < units->get(n)->y)
                                   if (spr->x+20 > units->get(n)->x   &&   spr->x-20 < units->get(n)->x)
                                        activate_bullet(0, 0, -1, spr->x, spr->y);
                         if (spr->dir == 1)
                              if (spr->x+60 > units->get(n)->x   &&   spr->x+20 < units->get(n)->x)
                                   if (spr->y+20 > units->get(n)->y   &&   spr->y-20 < units->get(n)->y)
                                        activate_bullet(1, 1, 0, spr->x, spr->y);
                         if (spr->dir == 2)
                              if (spr->y+60 > units->get(n)->y   &&   spr->y+20 < units->get(n)->y)
                                   if (spr->x+20 > units->get(n)->x   &&   spr->x-20 < units->get(n)->x)
                                        activate_bullet(2, 0, 1, spr->x, spr->y);
                         if (spr->dir == 3)
                              if (spr->x-20 > units->get(n)->x   &&   spr->x-60 < units->get(n)->x)
                                   if (spr->y+20 > units->get(n)->y   &&   spr->y-20 < units->get(n)->y)
                                        activate_bullet(3, -1, 0, spr->x, spr->y);
                    }
               }
          }
     }
}

///////////////////////////////////////////////////////////
/// Function to create the bullet when in firing range ///
//////////////////////////////////////////////////////////
void activate_bullet(unsigned char dir, signed char speedx, signed char speedy, unsigned short int x, unsigned short int y)
{
     bullet->alive = 1;
     bullet->player = turn;
     bullet->x = x;
     bullet->y = y;
     curn = 40;
     bullet->velx = speedx;
     bullet->vely = speedy;
     bullet->dir = dir;
     bullet_shooting = 1;
     play_sample(snd_bullet_shot, 255, 128, 1000, FALSE);
     counter = 2;
}

//////////////////////////////////////////////
/// Function to decide outcomes of battles ///
//////////////////////////////////////////////
void init_fight(sprite *spr)
{
     if (spr->alive == 0)
          return;
     
     if (bullet_shooting == 1)
     {
          selx = bullet->x;
          sely = bullet->y;
     }
     
     if ((spr->player == 2 && turn == 1) || (spr->player == 1 && turn == 2))
          if ((spr->x > selx-10)   &&   spr->x < selx+10)
               if ((spr->y > sely-10)   &&   spr->y < sely+10)
                    fight = 1;
     
     if (fight == 0)
          return;

     units->get(curn)->squares = 0;

     if (fight == 1) //All possible win scenarios between the 3 types of units
     {
          if (typeN == "Light") //When Light is attacking
          {
               if (spr->type == "Assault") //Against Assault = Win
               {
                    spr->alive = 0;
                    play_sample(snd_fight_win, 255, 128, 1000, FALSE);
                    activate_explosion(spr, 1);
               }
               if (spr->type == "Light") //Against same = both lose
               {
                    spr->alive = 0;
                    erase_unit(units->get(curn));
                    play_sample(snd_fight_draw, 255, 128, 1000, FALSE);
                    activate_explosion(spr, 2);
               }
               if (spr->type == "Heavy") //Against Heavy = Lose
               {
                    erase_unit(units->get(curn));
                    play_sample(snd_fight_lose, 255, 128, 1000, FALSE);
                    activate_explosion(spr, 0);
               }
          }
          if (typeN == "Assault") //When Assault is attacking
          {
               if (spr->type == "Assault") //Against same = both lose
               {
                    spr->alive = 0;
                    erase_unit(units->get(curn));
                    play_sample(snd_fight_draw, 255, 128, 1000, FALSE);
                    activate_explosion(spr, 2);
               }
               if (spr->type == "Light") //Against Light = Lose
               {
                    erase_unit(units->get(curn));
                    play_sample(snd_fight_lose, 255, 128, 1000, FALSE);
                    activate_explosion(spr, 0);
               }
               if (spr->type == "Heavy") //Against Heavy = Win
               {
                    spr->alive = 0;
                    play_sample(snd_fight_win, 255, 128, 1000, FALSE);     
                    activate_explosion(spr, 1);
               }
          }
          if (typeN == "Heavy") //When Heavy is attacking
          {
               if (spr->type == "Assault") //Against Assault = Lose
               {
                    erase_unit(units->get(curn));
                    play_sample(snd_fight_lose, 255, 128, 1000, FALSE);
                    activate_explosion(spr, 0);
               }
               if (spr->type == "Light") //Against Light = Win
               {
                    spr->alive = 0;
                    play_sample(snd_fight_win, 255, 128, 1000, FALSE);
                    activate_explosion(spr, 1);
               }
               if (spr->type == "Heavy") //Against same = both lose
               {
                    spr->alive = 0;
                    erase_unit(units->get(curn));
                    play_sample(snd_fight_draw, 255, 128, 1000, FALSE);
                    activate_explosion(spr, 2);
               }
          }
          if (bullet->alive == 1)
          {
               bullet->alive = 0;
               bullet->velx = 0;
               bullet->vely = 0;
          }
          
          bullet_shooting = 0;
          fight = 2;
          check_outcome();
     }
}

void activate_explosion(sprite *spr, unsigned char win_lose)
{
     //Lose = 0
     //Win = 1
     //Both lose = 2

     if (win_lose == 0 || win_lose == 2)
     {
          explosion->x = spr->x;
          explosion->y = spr->y;
     }
     if (win_lose == 1)
     {
          explosion->x = units->get(curn)->x;
          explosion->y = units->get(curn)->y;
     }
     
     explosion->curframe = 0;
     explosion->alive = 1;
}

//////////////////////////////////////////
/// Function to draw the hud on-screen ///
//////////////////////////////////////////
void draw_hud(sprite *spr)
{
     //Grid part
     for (grid_number = 10; grid_number > 0; grid_number--)
     {
          textprintf_ex(buffer, f_hud, 15, coord_y[grid_number]+10, C_WHITE ,-1, "%i", grid_number);
          textprintf_ex(buffer, f_hud, coord_x[grid_number]+15, 455, C_WHITE ,-1, "%i", grid_number);
     }
     
     if (turn == 1)
          textprintf_ex(buffer, f_hud, 470, 50, C_WHITE ,-1, "Turn: %s", PLAYER_NAME1.c_str());
     if (turn == 2)
          textprintf_ex(buffer, f_hud, 470, 50, C_WHITE ,-1, "Turn: %s", PLAYER_NAME2.c_str());
     textprintf_ex(buffer, f_hud, 470, 70, C_WHITE ,-1, "Round: %i", round);
     
     if (spr->select == 0)
          return;
     
     textprintf_ex(buffer, f_hud, 470, 90, C_WHITE ,-1, "Type: %s", spr->type.c_str());
     textprintf_ex(buffer, f_hud, 470, 110, C_WHITE ,-1, "Moves left: %i", spr->squares);
     textprintf_ex(buffer, f_hud, 470, 130, C_WHITE ,-1, "- Name -");
     textprintf_ex(buffer, f_hud, 470, 150, C_WHITE ,-1, "%s", spr->name.c_str());
     textprintf_ex(buffer, f_hud, 470, 170, C_WHITE ,-1, "Use against: ");
     textprintf_ex(buffer, f_hud, 470, 230, C_WHITE ,-1, "Bad against: ");
     
     for (unsigned char i=1; i<6; i++)
     {
          nonunits->get(i)->drawframe(buffer);
          nonunits->get(i)->updatePosition();
     }
}

//////////////////////////////////////////////////
/// Function to check if buttons where pressed ///
//////////////////////////////////////////////////
void check_game_buttons()
{
     if (choice_menu == "Pause")
     {
          if (confirm_stop == 1)
               confirm_stop = 0;
          midi_pause();
          set_volume(VOLUME_MID,VOLUME_MID);
          play_sample(snd_game_paused, 255, 128, 1000, TRUE);
          
          for (n=0; n<NUM_B; n++)
               if (buttons->get(n)->text == "Pause")
                    buttons->get(n)->text = "Unpause";
          
          if (units->get(curn)->select == 1)
          {
               units->get(curn)->select = 0;
               selected = 0;
          }
          
          if (starttext != 3)
               starttext = 3;

          choice_menu = "Paused";
     }
     if (choice_menu == "Paused")
     {
          rectfill(buffer, 95, 45, 390, 75, C_COLOR);
          rectfill(buffer, 95, 415, 390, 445, C_COLOR);                

          if (bg_scenery == 2)
          {
               textprintf_centre_ex(buffer, f_paused, 400/2+40, 40, C_WHITE ,-1, "The game is paused");
               textprintf_centre_ex(buffer, f_paused, 400/2+40, 410, C_WHITE ,-1, "The game is paused");
          }
          else
          {
               textprintf_centre_ex(buffer, f_paused, 400/2+40, 40, C_BLACK ,-1, "The game is paused");
               textprintf_centre_ex(buffer, f_paused, 400/2+40, 410, C_BLACK ,-1, "The game is paused");
          }
          
          draw_sprite(buffer, spr_pause, 95, 100);
     }
     if (choice_menu == "Unpause")
     {
          stop_sample(snd_game_paused);
          set_volume(VOLUME_SND,VOLUME_MID);
          midi_resume();
          choice_menu = "None";
          
          for (unsigned char i=0; i<NUM_B; i++)
          {
               if ( buttons->get(i)->text == "Unpause")
                    buttons->get(i)->text = "Pause";
          }
     }
     if (choice_menu == "Next Song")
     {
          if (confirm_stop == 1)
               confirm_stop = 0;
          song_length = 1;
          song_length_sec = 1;
          song_length_min = 0;
          choice_menu = "None";
     }
     if (choice_menu == "End Turn")
     {
          choice_menu = "None";
          if (confirm_stop == 1)
               confirm_stop = 0;
          if (turn == 1)
               turn = 2;
          else
          {
               turn = 1;
               round += 1;
               
               if (round == 4 || round == 7 || round == 10)
                    for (n=0; n<NUM; n++)
                         if (units->get(n)->name == "Chopper")
                              units->get(n)->startsquares += 1;
               
               for (n=0; n<NUM; n++) //Reseting the squares units are allowed to move on new turn
                    units->get(n)->squares = units->get(n)->startsquares;
          }
          
          selected = 0;
          for (n=0; n<NUM; n++)
               units->get(n)->select = 0;
          
          if (starttext == 2)
               starttext = 3;
     }
     
     if (choice_menu == "Background")
     {
          choice_menu = "None";
          if (confirm_stop == 1)
               confirm_stop = 0;

          for (n=1; n<NUM_BG; n++)
               bg_mains->get(n)->alive = 0;

          n = 1;
          while (n != NUM_BG)
          {
                    reroll = 0;
                    
                    //Giving random positions to debris backgrounds, except for the first 2 and last 2 rows
                    bg_mains->get(n)->x = coord_x[rand() %10 + 1];
                    bg_mains->get(n)->y = coord_y[rand() %6 + 3];
           
                    //Checking if the debris background does not collide with other existing backgrounds
                    for (unsigned char i=1; i<NUM_BG; i++)
                         if (bg_mains->get(i)->alive == 1)
                              if (bg_mains->get(n)->x == bg_mains->get(i)->x)
                                   if (bg_mains->get(n)->y == bg_mains->get(i)->y)
                                        reroll = 1;
                    
                    if (reroll == 0) //If the background does not collide, the debris background will be added
                    {
                         bg_mains->get(n)->curframe = rand() %bg_mains->get(n)->totalframes + 1;
                         bg_mains->get(n)->alive = 1;
                         bg_mains->get(n)->player = 10;
                         n++;
                    }
          }
     }
     
     if (choice_menu == "Restart")
     {
          choice_menu = "None";
          if (confirm_stop == 1)
               confirm_stop = 0;
          
          gamestop = 2;
          restart = 1;
     }
     
     if (confirm_stop == 2)
     {
          if (radius == 0)
               play_sample(snd_game_resign, 255, 128, 1000, FALSE);
          radius += 2;
          circlefill(buffer, O_WIDTH/2, O_HEIGHT/2, 200+radius, C_RED);
          circlefill(buffer, O_WIDTH/2, O_HEIGHT/2, 180+radius, C_GREEN);
          circlefill(buffer, O_WIDTH/2, O_HEIGHT/2, 160+radius, C_BLUE);
          circlefill(buffer, O_WIDTH/2, O_HEIGHT/2, 140+radius, C_YELLOW);
          circlefill(buffer, O_WIDTH/2, O_HEIGHT/2, 120+radius, C_PINK);
          circlefill(buffer, O_WIDTH/2, O_HEIGHT/2, 100+radius, C_GRAY);
          circlefill(buffer, O_WIDTH/2, O_HEIGHT/2, 80+radius, C_PURPLE);
          circlefill(buffer, O_WIDTH/2, O_HEIGHT/2, 60+radius, C_LIGHTBLUE);
          circlefill(buffer, O_WIDTH/2, O_HEIGHT/2, 40+radius, C_WHITE);
          circlefill(buffer, O_WIDTH/2, O_HEIGHT/2, 5+radius, C_BLACK);
          
          if (radius > 450)
          {
               resign = 1;
               game_outcome = turn;
               gamestop = 2;
          }
          
          if (starttext == 2)
               starttext = 3;
     }
     
     if (choice_menu == "Resign") //Init action to exit the game
     {
          choice_menu = "None";
          if (starttext == 2)
               starttext = 3;
          if (confirm_stop == 0)
               confirm_stop = 1;
          else
               confirm_stop = 2;
     }
}

////////////////////////////////////////
/// Function control the game themes ///
////////////////////////////////////////
void control_music()
{
     rectfill(buffer, 40, 5, 450, 35, C_BLACK);
     rectfill(buffer, 41, 6, 449, 34, C_WHITE);
     rectfill(buffer, 42, 7, 448, 33, C_RED);

     textprintf_ex(buffer, f_paused, 50, -1, C_WHITE ,-1, "%s:", song_name.c_str());
     if (song_length_sec < 10)
          textprintf_ex(buffer, f_paused, 350, -2, C_WHITE ,-1, "%i:0%i", song_length_min, song_length_sec);
     else
          textprintf_ex(buffer, f_paused, 350, -2, C_WHITE ,-1, "%i:%i", song_length_min, song_length_sec);
     
     if (song_length_sec < 0)
     {
          song_length_min--;
          song_length_sec = 59;
     }
     
     if (song_length == 0)
     {
          song_pick++;
          if (song_pick > MID_THEME_SIZE-1 && starttext != 0)
               song_pick = 0;
          if (song_pick > MID_PREPARATION_SIZE-1 && starttext == 0)
               song_pick = 0;
          
          start_music();
     }
}

//////////////////////////////////////
/// Function to start a game theme ///
//////////////////////////////////////
void start_music()
{
     if (song_pick == 100) //Picking a song while placing the units
          song_pick = rand() %MID_PREPARATION_SIZE; //Chooses randomly on of these songs
     
     if (starttext == 0)
     {
          if (restart == 0)  //When loading a preparation theme for the first time in a match (restart not included)
          {
               datafiles[music_preparation] = load_datafile("data/music/preparation.dat");
               for (unsigned char j=0; j<MID_PREPARATION_SIZE; j++)
                    mid_preparation[j] = (MIDI *)datafiles[music_preparation][j].dat;
               read_music_data("data/music/preparation.ini");
          }         
                        
          song_length = get_midi_length(mid_preparation[song_pick]) + 5;
          song_name = song_name_prep.at(song_pick);
          play_midi(mid_preparation[song_pick], 0);
     }
     if (starttext != 0)
     {
          if (unloaded_prep_music == 0) //When loading a main theme for the first time in a match
          {
               stop_midi();
               datafiles[music_main] = load_datafile("data/music/theme.dat");
               for (unsigned char j=0; j<MID_THEME_SIZE; j++)
                    mid_theme[j] = (MIDI *)datafiles[music_main][j].dat;
               read_music_data("data/music/theme.ini");
               unload_datafile(datafiles[music_preparation]); //Unload preparation music when main music is starting
               unloaded_prep_music = 1;
          }
                        
          song_length = get_midi_length(mid_theme[song_pick]) + 5;
          song_name = song_name_prep.at(song_pick);
          play_midi(mid_theme[song_pick], 0);
     }

     //Some display correction commands for song length
     song_length_copy = song_length;
     while (song_length_copy > 60)
     {
          song_length_copy -= 60;
          song_length_min++;
     }
     song_length_sec = song_length_copy;
}

//////////////////////////////////////////////////////////
/// Function to check if a player lost all their units ///
//////////////////////////////////////////////////////////
void check_outcome()
{
     //Checking for winner
     units_left[1] = 20;
     units_left[2] = 20;
     for (n=0; n<NUM; n++)
     {
          if (units->get(n)->player == 1 && units->get(n)->name != "Bullet" && units->get(n)->alive == 0)
               units_left[1]--;
          if (units->get(n)->player == 2 && units->get(n)->name != "Bullet" && units->get(n)->alive == 0)
               units_left[2]--;            
     }
               
     if (units_left[1] == 0)
     {
          game_outcome = 2;
          gamestop = 1;
          counter = 3;
     }
     if (units_left[2] == 0)
     {
          if (units_left[1] != 0)
               game_outcome = 1;
          else
               game_outcome = 3;
          gamestop = 1;
          counter = 3;
     }
}

#endif
