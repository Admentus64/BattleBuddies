#ifndef PREPAREGAME_H
#define PREPAREGAME_H

//////////////////////////////////////////////////////////////
/// Function to decide the starting positions of all units ///
//////////////////////////////////////////////////////////////
void startpos()
{
     //Init bg positions
     if (bg_scenery == 2)
          C_COLOR = makecol(0,0,0);
     if (bg_scenery != 2)
          C_COLOR = makecol(255,255,255);
          

     bg_mains->get(0)->alive = 1;
     bg_mains->get(0)->x = coord_x[1];
     bg_mains->get(0)->y = coord_y[1];
     
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
     
     //Init button positions
     for (n=0; n<4; n++)
     {
          buttons->get(n)->x = 480;
          buttons->get(n)->y = 310+40*n;
     }
     for (n=4; n<NUM_B; n++)
     {
          buttons->get(n)->x = 480;
          buttons->get(n)->y = -60+40*n;
     }
}

///////////////////////////////
/// Function to place units ///
///////////////////////////////
void place_units()
{
     for (grid_number = 10; grid_number > 0; grid_number--) //Grid part
     {
          textprintf_ex(buffer, f_hud, 15, coord_y[grid_number]+10, C_WHITE ,-1, "%i", grid_number);
          textprintf_ex(buffer, f_hud, coord_x[grid_number]+15, 455, C_WHITE ,-1, "%i", grid_number);
     }
     
     if (cur_placement <= 19)
          textprintf_ex(buffer, f_hud, 470, 50, C_WHITE ,-1, "%s's turn", PLAYER_NAME1.c_str());
     if (cur_placement > 19)
          textprintf_ex(buffer, f_hud, 470, 50, C_WHITE ,-1, "%s's turn", PLAYER_NAME2.c_str());
     textprintf_ex(buffer, f_hud, 470, 70, C_WHITE ,-1, "to place units");
     
     for (n=0; n<cur_placement; n++)
     {
          units->get(n)->updatePosition();
          units->get(n)->updateAnimation();
          units->get(n)->drawframe_unit(buffer, bg_scenery);
     }
     pointer->updatePosition();
     pointer->drawframe(buffer);
     
     if (pointer->y < nonunits->get(0)->y1)
          pointer->vely = 1;
     if (pointer->y > nonunits->get(0)->y2)
          pointer->vely = -1;
     
     if (cur_placement == 40 && starttext == 0) //When all units are placed on the field (40 pieces), the game starts preparations to the real match
     {
          //Add the bullet as an unit
          unit = new sprite(); //Add bullet
          unit->load_data_img("data/units/images - bullet.dat", 4);
          unit->width = 32; unit->height = 32;
          unit->name = "Bullet"; unit->type = "Assault";
          unit->totalframes = 0;
          units->add(unit);
          
          //Delete the pointer nonunit and replace it with an explosion nonunit
          delete nonunits;
          nonunits = new spritehandler();
          for (unsigned char i=0; i<6; i++)
          {
               nonunit = new sprite();
               if (i == 0) //Add explosion
               {
                    nonunit->load_data_img("data/misc/images - explosion.dat", 1);
                    nonunit->width = 40; nonunit->height = 39;
                    nonunit->totalframes = 10;
               }
               if (i == 1)
               {
                    nonunit->load_data_img("data/units/images - chopper.dat", 4);
                    nonunit->width = 40; nonunit->height = 40;
               }
               if (i == 2)
               {
                    nonunit->load_data_img("data/units/images - tank.dat", 4);
                    nonunit->width = 32; nonunit->height = 32;
               }
               if (i == 3)
               {
                    nonunit->load_data_img("data/units/images - mec.dat", 4);
                    nonunit->width = 41; nonunit->height = 41;
               }
               if (i == 4)
               {
                    nonunit->load_data_img("data/units/images - odin.dat", 4);
                    nonunit->width = 39; nonunit->height = 39;
               }
               if (i == 5)
               {
                    nonunit->load_data_img("data/units/images - fighter.dat", 4);
                    nonunit->width = 32; nonunit->height = 32;
               }
               nonunits->add(nonunit);
          }
          

          //Reset the button before main game starts
          for (n=4; n<NUM_B; n++)
               buttons->get(n)->alive = 0;
          buttons->get(0)->text = "Pause";
          buttons->get(2)->text = "End Turn";
          
          //Prepare main game music
          song_length = 1;
          song_length_sec = 1;
          song_length_min = 0;
          song_pick = rand() %MID_THEME_SIZE;
          
          //Last reset of values before main gmae
          mouse_over = 0;
          mb1_hold = 0;
          mb1_hold = 0;
          inside = 0;
          starttext = 1;
          counter = 4;
          
          //play_sample(snd_game_countdown, 255, 128, 1000, FALSE);
     }      

     if (choice_menu == "Chopper" || choice_menu == "Light Tank" || choice_menu == "MEC" || choice_menu == "Odin" || choice_menu == "F9 Fighter") //Each placed units contains this same section
     {
          unit = new sprite();
          confirm_stop = 0;
     }

     if (choice_menu == "Chopper") //When Chopper is selected
     {
          unit->load_data_img("data/units/images - chopper.dat", 4);
          unit->load_data_snd("data/units/sounds - chopper.dat", 2);
          unit->width = 40; unit->height = 40;
          unit->xcorrect = 0; unit->ycorrect = 4;
          unit->name = "Chopper"; unit->type = "Assault";
          unit->totalframes = 3;
          unit->startsquares = 1; unit->squares = 1;
     }
     if (choice_menu == "Light Tank") //When Light Tank is selected
     {
          unit->load_data_img("data/units/images - tank.dat", 4);
          unit->load_data_snd("data/units/sounds - tank.dat", 2);
          unit->width = 32; unit->height = 32;
          unit->xcorrect = 4; unit->ycorrect = 3;
          unit->name = "Light Tank"; unit->type = "Assault";
          unit->totalframes = 7;
          unit->startsquares = 1; unit->squares = 1;
     }
     if (choice_menu == "MEC") //When MEC Hovercraft is selected
     {
          unit->load_data_img("data/units/images - mec.dat", 4);
          unit->load_data_snd("data/units/sounds - mec.dat", 2);
          unit->width = 41; unit->height = 41;
          unit->xcorrect = -1; unit->ycorrect = -1;
          unit->totalframes = 4; unit->havestopframe = 1;
          unit->name = "MEC Hovercraft"; unit->type = "Light";
     }
     if (choice_menu == "Odin") //When Odin is selected
     {
          unit->load_data_img("data/units/images - odin.dat", 4);
          unit->load_data_snd("data/units/sounds - odin.dat", 2);
          unit->width = 39; unit->height = 39;
          unit->xcorrect = 1; unit->ycorrect = 2;
          unit->name = "Odin"; unit->type = "Heavy";
          unit->totalframes = 1; unit->havestopframe = 1;
          unit->startsquares = 3; unit->squares = 3;
     }
     if (choice_menu == "F9 Fighter") //When F9 Fighter is selected
     {
          unit->load_data_img("data/units/images - fighter.dat", 4);
          unit->load_data_snd("data/units/sounds - fighter.dat", 2);
          unit->width = 32; unit->height = 32;
          unit->xcorrect = 4; unit->ycorrect = 3;
          unit->name = "F9 Fighter"; unit->type = "Light";
          unit->totalframes = 2;
     }

     if (choice_menu == "Chopper" || choice_menu == "Light Tank" || choice_menu == "MEC" || choice_menu == "Odin" || choice_menu == "F9 Fighter") //Each placed units contains this same section
     {
          unit->alive = 1;
          if (cur_placement<=19)
               unit->player = 1;
          else
          {
               unit->player = 2;
               unit->dir = 2;
          }
          units->add(unit);
          unit_is_placed = 1;
     }
     
     if (unit_is_placed == 1)
     {
          //Init unit positions for all units (both players), and moving the pointer
          unit_place_i++;
          units->get(cur_placement)->x = coord_x[unit_place_i] + units->get(cur_placement)->xcorrect;
          units->get(cur_placement)->y = coord_y[unit_place_j] + units->get(cur_placement)->ycorrect;
          pointer->x += 41;
          if (cur_placement == 9)
          {
               unit_place_j = 1;
               pointer->y = coord_y[1]-30;
          }
          if (cur_placement == 19)
          {
               unit_place_j = 9;
               pointer->y = coord_y[9]+40;
               pointer->curframe = 1;
          }
          if (cur_placement == 29)
          {
               unit_place_j = 10;
               pointer->y = coord_y[10]+40;
          }
          if (cur_placement == 9 || cur_placement == 19 || cur_placement == 29)
          {
               unit_place_i = 0;
               pointer->y1 = pointer->y - 10;
               pointer->y2 = pointer->y + 10;
               pointer->x = coord_x[1]+4;
          }
          unit_is_placed = 0;
          cur_placement++;
          choice_menu = "None";
     }
}

//////////////////////////////////////////////////////////
/// Function to reset variables when starting new game ///
//////////////////////////////////////////////////////////
void reset_variables()
{
     //Resetting all variables before new game starts
     mouse_over = 0;
     counter = 0;
     starttext = 0;
     selected = 0;
     move = 0;
     fight = 0;
     turn = 1;
     gamestop = 0;
     round = 1;
     radius = 0;
     choice_menu = "None";
     game_outcome = 0;
     resign = 0;
     cur_placement = 0;
     allow_edit = 0;
     unit_place_i = 0, unit_place_j = 2;
     mb1_hold, mb2_hold = 0;
     cur_unit = 0;
     confirm_stop = 0;
}

#endif
