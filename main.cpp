///////////////////////////////////////////////////////////
/// Game Title: BattleBuddies                           ///
/// A game made by Robin Hallink - TE10 - Programming C ///
/// Made with Allegro and C++                           ///
/// Made with the lalleg linker                         ///
///////////////////////////////////////////////////////////

//Includes all programming files of the project to be able to start the game (more are loaded in the setup.h files)
#include "setup.h"
#include "preload.h"
#include "addsprites.h"
#include "preparegame.h"
#include "menu.h"
#include "game.h"
#include "checkmove.h"
#include "gameloop.h"
#include "commands.h"
#include "exitprogram.h"
#include "gameresolution.h"

//////////////////////////////////////
/// Function the game starts with ///
/////////////////////////////////////
int main(void)
{   
     //Alle required functions are in different files, to make this main function short and clean
     startgame(); //preload.h

     if (file_is_missing == 1)
          while (!key[KEY_ESC])
          {
               files_not_found();
               update_screen_errormode();
               if (key[KEY_ESC])
                    return 0;
          }

     setup_coords(); //preload.h
     
     //Reset timer
     rest(50), counter = 1, mb1_hold = 0;
     starttext = 3;
     
     init_menu_sprites();
     edit_menu_sprites();

     while (choice_menu != "Game Ended") //The main menu loop
     {
          if (restart == 0) //Start section 1
          {
               init_menuloop(); //game.h

               if (error_reading == 1) //Write out a error message on the screen if data was not loaded correctly
               {
                    textprintf_ex(buffer, font, 10, 10, C_WHITE ,-1, "Error loading data from ini files located in: 'settings' dir");
                    textprintf_ex(buffer, font, 10, 20, C_WHITE ,-1, "These *ini files have now been restored, the game uses default values now");
                    //textprintf_ex(buffer, font, 10, 30, C_WHITE ,-1, "Restart the game please to disable this error");
               }

               for (n=0; n<NUM_MENU_B; n++)
               {
                    buttons->get(n)->drawframe(buffer);
                    press_button(buttons->get(n));
                    if (mb1_hold == 1)
                         release_button(buttons->get(curnb));
               }

               if (   (choice_menu == "Sure?" || choice_menu == "Start Game")   && counter == 0) //Init the counter when exiting game
               {     
                    counter = 2;
                    if (choice_menu == "Start Game")
                         play_sample(snd_button_gamestart, 255, 128, 1000, FALSE);
               }
          
               if (key[KEY_ESC] && keyboard_pressed == 1) //Exiting game by pressing ESC
               {
                    keyboard_pressed = 0;
                    play_sample(snd_button_back, 255, 128, 1000, FALSE);
                    if (choice_menu != "Exit Game" && choice_menu != "Sure?")
                         choice_menu = "Exit Game";
                    else
                    {
                         choice_menu = "Sure?";
                         counter = 2;
                    }
               }

               if (choice_menu == "Exit Game" || choice_menu == "Sure?")
                    buttons->get(5)->text = "Sure?";
               else
                    buttons->get(5)->text = "Exit Game";
                    
               //When pressing buttons for submenus
               if (choice_menu == "Help") //How to Play submenu (currently no menu yet)
               {
                    edit_menu_sprites();
                    loop_submenu1();
               }
               if (choice_menu == "Settings") //Settings submenu
               {
                    edit_menu_sprites();
                    loop_submenu2();
               }
               if (choice_menu == "Highscore") //Highscore submenu (currently no menu yet)
               {
                    edit_menu_sprites();
                    loop_submenu3();
               }
               if (choice_menu == "Credits") //Highscore submenu (currently no menu yet)
               {
                    edit_menu_sprites();
                    loop_submenu4();
               }
          }

          //All following code is concering setting up the main game and it's preparation mode
          if (choice_menu == "Game Started") //Starts main game
          {
               reset_variables(); // preload.h
               if (restart == 0)
               {
                    delete buttons; //Delete previous menu sprites when not forcing a restart
                    song_pick = 100;
                    start_music();
                    unload_datafile(datafiles[music_menu]);
               }
               init_sprites(); //addsprites.h
               startpos(); //preload.h
               restart = 0;
               loop(); //Main gameloop from the gameloop.h file within the menu loop
               erase_sprites(); //preload.h
               if (restart == 0) //If forcing a restart, the game will skip loading menu graphics, but will reset main game graphics
               {
                    init_menu_sprites();
                    counter = 1;
                    loop_outcome(); //Someone did win, resign the match or resigned before the match started? Therefore the outcome menu
                    choice_menu = "Back";
                    edit_menu_sprites();
                    unloaded_prep_music = 0;
               }
               if (restart == 1) //This section will restart the main game function
                    choice_menu = "Game Started";
          }
          
          if (restart == 0) //Refreshing the screen when not restarting a preparation match
               update_screen();
     } //End of program

	 endgame(); //preload.h
     return 0;
}
END_OF_MAIN()
