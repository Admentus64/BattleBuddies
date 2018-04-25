#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <iostream>
#include <string>
using namespace std;

void loop()
{
     //game loop
     while (gamestop != 2)
     {
          //Grab the current mouse values
          mx = mouse_x; my = mouse_y; mb1 = (mouse_b & 1); mb2 = (mouse_b & 2);
          
          //Draw the background && grid
		  draw_sprite(buffer, bg, 0, 0);
		  draw_sprite(buffer, grid, 40, 40);
		  draw_sprite(buffer, hud, 460, 40);

		  if (temp_disable_bg == 0) //In preparation mode the bg can be repositioned, therefore a check if this isn't happening
		  {
               //Draw the frist bg_main sprite as the background and all other bg_main sprites as debris
		       bg_mains->get(0)->drawBG(buffer);
		       if (NUM_BG > 1)
	           {
		            for (n=1; n<NUM_BG; n++)
		                 bg_mains->get(n)->drawframe(buffer);
               }
          }

          //Drawing the buttons with their text, and checking for button presses
          for (n=0; n<NUM_B; n++)
          {
               buttons->get(n)->drawframe(buffer);
               if (choice_menu == "Paused" && mx > 440)
                    for (int i=0; i<NUM_B; i++)
                    {
                         if (buttons->get(i)->text == "Unpause")
                              press_button(buttons->get(i));
                    }
               else if (mx > 440)
                    press_button(buttons->get(n));
               if (mb1_hold == 1 && mx > 440)
                    release_button(buttons->get(curnb));
          }
          
          if (starttext == 0)
               place_units();
          
          if (starttext != 0)
          {
               for (n=0; n<NUM; n++) //Goes through all existing units to execute commands
               {
                    //update positions, update animations, draw the sprites & draw the info for the hud
                    if (units->get(n)->select == 0)
                    {
                         units->get(n)->updatePosition();
                         units->get(n)->updateAnimation();
                         units->get(n)->drawframe_unit(buffer, bg_scenery);
                    }
                    draw_hud(units->get(n));
               
                    //If hovering with mouse on unit then a different cursor will show, otherwise that cursor is off
                    if (mb1_hold == 0 && mb2_hold == 0)
                         if (mx > units->get(n)->x && mx < units->get(n)->x+units->get(n)->width && my > units->get(n)->y && my < units->get(n)->y+units->get(n)->height)
                         {
                              mouse_over = 1;
                              cur_unit = n;
                         }
                    if (n == cur_unit && mouse_over == 1)
                    {
                         if (mx < units->get(n)->x || mx > units->get(n)->x+units->get(n)->width || my < units->get(n)->y || my > units->get(n)->y+units->get(n)->height)
                              mouse_over = 0;
                         if (mb1 || mb2)
                              mouse_over = 0;
                    }
               
                    //Only proceed with selecting units only if game is not paused, if not paused than gameplay functions proceed
                    //Also checking if the cursor is located inside the area of the current players units
                    //This function will neither proceed if the cursor is outside the playing board
                    if (choice_menu != "Paused" && mx > 40 && mx < 440 && my > 40 && my < 440 && move == 0 && n!= 41)
                         if (   (turn == 1 && n < 20) || (turn == 2 && n >= 20)   )
                              if (mx > units->get(n)->x && mx < units->get(n)->x+units->get(n)->width && my > units->get(n)->y && my < units->get(n)->y+units->get(n)->height)
                              {     
                                   press_select_unit(units->get(n));
                                   if (mb1_hold == 1)
                                        release_select_unit(units->get(curn));
                              }
                    if (mb1_hold == 1 && !mb1 && selected == 0)
                        if (mx < units->get(curn)->x || mx > units->get(curn)->x+units->get(curn)->width || my < units->get(curn)->y || my > units->get(curn)->y+units->get(curn)->height)
                        {
                             mb1_hold = 0;
                        }
                    
                    
               
                    if (move == 1 || bullet_shooting == 1)
                         init_fight(units->get(n));         
               } //Unit commands ends here
               
               if (selected == 1)
               {
                    units->get(curn)->updatePosition();
                    units->get(curn)->updateAnimation();
                    units->get(curn)->drawframe_unit(buffer, bg_scenery);
               }
               
               if (mb1 && move == 0 && selected == 1 && counter == 0)
                    mb1_hold = 1;
               if (!mb1 && mb1_hold == 1)
                    release_move_unit(units->get(curn));
               
               if (move == 1)
                    resetunit_arrive(units->get(curn));
                    
               if (mb2 && selected == 1)
                    mb2_hold = 1;
               if (!mb2 && mb2_hold == 1)
                    release_deselect_unit(units->get(curn));
               
               //Is an explosion is alive (showing on screen), then draw it and remove it once it reaches the final frame
               if (explosion->alive == 1 && starttext != 0)
               {
                    explosion->updatePosition();
                    explosion->updateAnimation();
                    explosion->drawframe(buffer);
                    if (explosion->curframe == explosion->totalframes)
                         explosion->alive = 0;
               }
               
               if (starttext == 1 && counter != 4)
                    textprintf_ex(buffer, f_starttext, 60, 210, C_COLOR ,-1, "The game starts in... %d", counter);
               if (starttext == 2)
                    textprintf_ex(buffer, f_starttext, 60, 210, C_COLOR ,-1, "The game has started");
          }
          
          if (confirm_stop == 1)
               textprintf_ex(buffer, f_starttext, 60, 210, C_COLOR ,-1, "Are you sure to quit?");
          
          control_music(); //Function to check the music status
          check_game_buttons();
          
          //When pressing ESCAPE
          if (key[KEY_ESC] && keyboard_pressed == 1)
          {
               keyboard_pressed = 0;
               play_sample(snd_button_click, 255, 128, 1000, FALSE);
          
               if (starttext == 2) //First, if the text "The Game Has Started" is shown on screen, ESCAPE will remove that text, end of function
                    starttext = 3;
               else if (selected == 1) //Secondly, if an unit is selected, it will be deselected with ESCAPE, end of function
               {
                    units->get(curn)->select = 0;
                    selected = 0;
               }
               else //Thirdly, ESCAPE will resume game when paused, calls for a confirm to resign of resign the match when there is a conform to resign
               {
                    if (choice_menu == "Paused") //When pressing ESC while paused, the game will unpause
                         choice_menu = "Unpause";
                    if (choice_menu == "None") //When pressing ESC without any menu open, the game will init exit mode
                         choice_menu = "Resign";
               }
          }
          //DELETE for deleting your current selected unit when standing idle
          if (key[KEY_DEL] && keyboard_pressed == 1)
          {
               keyboard_pressed = 0;
               if (selected == 1 && move == 0)
               {
                    erase_unit(units->get(curn));
                    activate_explosion(units->get(curn), 0);
                    play_sample(snd_fight_lose, 255, 128, 1000, FALSE);
                    check_outcome();
               }
               else
                    play_sample(snd_button_click, 255, 128, 1000, FALSE);
               
               if (starttext == 2)
                    starttext = 3;
          }

          update_screen(); //Function to refresh the screen properly without flickering
    }
}

#endif
