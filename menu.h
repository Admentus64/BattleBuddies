#ifndef MENU_H
#define MENU_H

void init_menu_sprites()
{
     buttons = new spritehandler();
     
     //Add sprites to the sprite handler
     for (n=0; n<NUM_MENU_B; n++) //create the button sprites
     {
          button = new sprite();
          
          if (n < 10 || n == 20 || n == 21 || n == 22) //Normal Button
          {
               button->load_data_img("data/buttons/images - button.dat", 1);
               button->load_data_style("data/buttons/fonts - button.dat", 1);
               button->name = "Button";
               button->width = 128; button->height = 32;
          }
          if (n >= 10 && n < 20) //Arrow
          {
               button->load_data_img("data/buttons/images - arrow.dat", 1);
               button->load_data_style("data/buttons/fonts - button.dat", 1);
               button->name = "Arrow";
               button->totalframes = 0;
               button->width = 32; button->height = 32;
          }
          button->alive = 0;
          button->x = 0;
          button->y = 0;
          buttons->add(button); //Add 1 button to the spritehandler
     } //End of button sprites
}

void edit_menu_sprites()
{
     mouse_over = 0;
     
     for (n=0; n<NUM_MENU_B; n++)
     {
          buttons->get(n)->alive = 0;
          buttons->get(n)->have_onoff = 0;
          buttons->get(n)->select = 0;
          buttons->get(n)->text = "";
          buttons->get(n)->curframe = 0;
          buttons->get(n)->x = 0;
          buttons->get(n)->y = 0;
     }
     
     if (choice_menu == "Back")
     {
          buttons->get(0)->text = "Start Game";
          buttons->get(1)->text = "Help";
          buttons->get(2)->text = "Settings";
          buttons->get(3)->text = "Highscore";
          buttons->get(4)->text = "Credits";
          buttons->get(5)->text = "Exit Game";

          for (n=0; n<6; n++)
          {
               buttons->get(n)->alive = 1;
               buttons->get(n)->x = O_WIDTH/2-buttons->get(n)->width/2;
               buttons->get(n)->y = 150+50*n;
          }
          return;
     }
     
     if (error_reading == 1)
          error_reading = 0;
     
     if (choice_menu == "Help")
     {
          buttons->get(0)->text = "Back";
          buttons->get(0)->x = O_WIDTH/2-buttons->get(0)->width/2; buttons->get(0)->y = 425;

          for (n=10; n<12; n++)
               buttons->get(n)->alive = 1;
          buttons->get(0)->alive = 1;
               
          buttons->get(10)->x = 25;                                             buttons->get(11)->x = O_WIDTH-buttons->get(11)->width-25;
          buttons->get(10)->y = 250;                                            buttons->get(11)->y = 250;
          buttons->get(10)->curframe = 2;                                       buttons->get(11)->curframe = 3;
          buttons->get(10)->text = "Slide Less";                                buttons->get(11)->text = "Slide More";
     }
     if (choice_menu == "Settings")
     {
          for (n=0; n<23; n++)
               buttons->get(n)->alive = 1;
     
          buttons->get(0)->text = "Back";                                       buttons->get(1)->text = "Apply"; buttons->get(1)->alive = 0;
          buttons->get(0)->x = 450;                                             buttons->get(1)->x = 450;
          buttons->get(0)->y = 375;                                             buttons->get(1)->y = 425;
          
          for (n=2; n<7; n++)
          {
               buttons->get(n)->y = 25+50*n;
               buttons->get(n)->x = 50;
          }
          for (n=7; n<10; n++)
          {
               buttons->get(n)->y = 50*n-175;
               buttons->get(n)->x = 450;
          }
          buttons->get(22)->y = 125; buttons->get(22)->x = 450;
               
          buttons->get(2)->text = "Sound";
          buttons->get(3)->text = "Music";
          buttons->get(4)->text = "Slowdown";
          buttons->get(5)->text = "Slow Mouse";
          buttons->get(6)->text = "Resolution";
          
          buttons->get(7)->text = "Fullscreen";
          buttons->get(8)->text = "Background";
          buttons->get(9)->text = "HW Cursor";
          buttons->get(22)->text = "Movie";
          
          buttons->get(20)->text = "Name 1"; buttons->get(20)->x = 50; buttons->get(20)->y = 375;
          buttons->get(21)->text = "Name 2"; buttons->get(21)->x = 50; buttons->get(21)->y = 425;
          
          buttons->get(10)->x = buttons->get(2)->x - 40;                        buttons->get(11)->x = buttons->get(2)->x + 136;
          buttons->get(10)->y = buttons->get(2)->y;                             buttons->get(11)->y = buttons->get(2)->y;
          buttons->get(10)->curframe = 2;                                       buttons->get(11)->curframe = 3;
          buttons->get(10)->text = "Sound Less";                                buttons->get(11)->text = "Sound More";
          
          buttons->get(12)->x = buttons->get(3)->x - 40;                        buttons->get(13)->x = buttons->get(3)->x + 136;  
          buttons->get(12)->y = buttons->get(3)->y;                             buttons->get(13)->y = buttons->get(3)->y;
          buttons->get(12)->curframe = 2;                                       buttons->get(13)->curframe = 3; 
          buttons->get(12)->text = "Music Less";                                buttons->get(13)->text = "Music More";
          
          buttons->get(14)->x = buttons->get(4)->x - 40;                        buttons->get(15)->x = buttons->get(4)->x + 136;
          buttons->get(14)->y = buttons->get(4)->y;                             buttons->get(15)->y = buttons->get(4)->y;
          buttons->get(14)->curframe = 2;                                       buttons->get(15)->curframe = 3;
          buttons->get(14)->text = "Slowdown Less";                             buttons->get(15)->text = "Slowdown More";
          
          buttons->get(16)->x = buttons->get(5)->x - 40;                        buttons->get(17)->x = buttons->get(5)->x + 136;
          buttons->get(16)->y = buttons->get(5)->y;                             buttons->get(17)->y = buttons->get(5)->y;
          buttons->get(16)->curframe = 2;                                       buttons->get(17)->curframe = 3;
          buttons->get(16)->text = "Slow Mouse Less";                           buttons->get(17)->text = "Slow Mouse More";
          
          buttons->get(18)->x = buttons->get(6)->x - 40;                        buttons->get(19)->x = buttons->get(6)->x + 136;
          buttons->get(18)->y = buttons->get(6)->y;                             buttons->get(19)->y = buttons->get(6)->y;
          buttons->get(18)->curframe = 2;                                       buttons->get(19)->curframe = 3;
          buttons->get(18)->text = "Resolution Less";                           buttons->get(19)->text = "Resolution More";
          
          buttons->get(7)->have_onoff = 1;
          buttons->get(8)->have_onoff = 1;
          buttons->get(9)->have_onoff = 1;
          buttons->get(22)->have_onoff = 1;
          if (MODE == GFX_AUTODETECT_FULLSCREEN)
               buttons->get(7)->select = 1;
          if (SWITCH_MODE == SWITCH_BACKGROUND)
               buttons->get(8)->select = 1;
          if (HARDWARE_CURSOR == 1)
               buttons->get(9)->select = 1;
          if (PLAY_MOVIE == 1)
               buttons->get(22)->select = 1;
     }
     if (choice_menu == "Highscore")
     {
          buttons->get(0)->text = "Back";
          buttons->get(1)->text = "Reset";
          buttons->get(0)->x = O_WIDTH/2-100-64; buttons->get(0)->y = 400;
          buttons->get(1)->x = O_WIDTH/2+100-64; buttons->get(1)->y = 400;
          buttons->get(0)->alive = 1;
          buttons->get(1)->alive = 1;
     }
     if (choice_menu == "Credits")
     {
          buttons->get(0)->alive = 1; 
          buttons->get(0)->text = "Back";
          buttons->get(0)->x = 60;
          buttons->get(0)->y = 430;
     }
}

void loop_submenu1() //Help submenu
{
     play_midi(mid_help, 1); //Start help theme
     
     //A fast reset every time the player enters the help menu
     cur_slide = 0;
     buttons->get(10)->alive = 0;
          
     //Load the slide images
     datafiles[image_guide] = load_datafile("data/images/guide.dat");
     for (unsigned char j=0; j<IMG_GUIDE_SIZE; j++)
          img_guide[j] = (BITMAP *)datafiles[image_guide][j].dat;
     
     //submenu 1 loop (Help)
     while (choice_menu != "Back")
     {
          init_menuloop(); //game.h
          
          //Basic button stuff
          for (n=0; n<NUM_MENU_B; n++)
          {
               buttons->get(n)->drawframe(buffer);
               press_button(buttons->get(n));
               if (mb1_hold == 1)
                    release_button(buttons->get(curnb));
          }
          
          //Draw the current slide of the guide system
          draw_sprite(buffer, img_guide[0], (O_WIDTH/2)-250, 120); 
          
          //Display info from an ini based based on current slide
          sprintf(s, "guide/slide%d.ini", cur_slide);
          read_guide_data(s); 
          
          //Actions to switch between slides when pressing the arrow buttons
          //Also releases temp data which certain slides require
          if (allow_edit == 1)
          {
               for (unsigned char i=0; i<TEMP_SIZE; i++)
                    if (temp_sprite_loaded[i] == 1)
                    {
                         unload_datafile(temp_data[i]);
                         temp_sprite_loaded[i] = 0;
                    }
          }
          if (choice_menu == "Slide More" && allow_edit == 1)
          {
               cur_slide++;
               if (cur_slide == MAX_SLIDE-1)
                    buttons->get(11)->alive = 0;
               if (cur_slide == 1)
                    buttons->get(10)->alive = 1;
          }
          if (choice_menu == "Slide Less" && allow_edit == 1)
          {
               cur_slide--;
               if (cur_slide == 0)
                    buttons->get(10)->alive = 0;
               if (cur_slide == MAX_SLIDE-2)
                    buttons->get(11)->alive = 1;
          }
          if (allow_edit == 1)
               allow_edit = 0;
          
          update_screen();
     }
     play_midi(mid_main, 0); //Start menu theme
     edit_menu_sprites();
     
     //Remove the slide images from memory
     unload_datafile(datafiles[image_guide]);
     for (unsigned char i=0; i<TEMP_SIZE; i++)
     {
          if (temp_sprite_loaded[i] == 1)
               unload_datafile(temp_data[i]);
          temp_sprite_loaded[i] = 0;
     }
}

void loop_submenu2()
{
     play_midi(mid_settings, 1); //Start settings theme
     
     //submenu 2 loop (Settings)
     while (choice_menu != "Back")
     {
          init_menuloop(); //game.h
          
          for (n=0; n<NUM_MENU_B; n++)
          {
               buttons->get(n)->drawframe(buffer);
               press_button(buttons->get(n));
               if (mb1_hold == 1)
                         release_button(buttons->get(curnb));
               
               if (buttons->get(n)->have_onoff == 1 && buttons->get(n)->select == 0)
                    draw_sprite(buffer, spr_off, buttons->get(n)->x+136, buttons->get(n)->y); 
               if (buttons->get(n)->have_onoff == 1 && buttons->get(n)->select == 1)
                    draw_sprite(buffer, spr_on, buttons->get(n)->x+136, buttons->get(n)->y);
          }
          
          //Drawing filling bars for some buttons
          draw_bar(buffer, 11, VOLUME_SND);
          draw_bar(buffer, 13, VOLUME_MID);
          draw_bar(buffer, 15, REST_DUR*12.75);
          draw_bar(buffer, 17, SPEED_CURSOR*25+5);
          
          //Some more bars for resolutions
          if (is_windowed_mode())
          {
               if (NEW_WIDTH == 640 && NEW_HEIGHT == 480)
                    draw_bar(buffer, 19, 51);
               if (NEW_WIDTH == 720 && NEW_HEIGHT == 540)
                    draw_bar(buffer, 19, 102);
               if (NEW_WIDTH == 800 && NEW_HEIGHT == 600)
                    draw_bar(buffer, 19, 153);
               if (NEW_WIDTH == 880 && NEW_HEIGHT == 660)
                    draw_bar(buffer, 19, 204);
               if (NEW_WIDTH == 960 && NEW_HEIGHT == 720)
                    draw_bar(buffer, 19, 255);
          }
          if (!is_windowed_mode())
          {
               if (NEW_WIDTH == 640 && NEW_HEIGHT == 480)
                    draw_bar(buffer, 19, 51);
               if (NEW_WIDTH == 800 && NEW_HEIGHT == 600)
                    draw_bar(buffer, 19, 255);
          }
          textprintf_centre_ex(buffer, f_hud, buttons->get(19)->x+250, buttons->get(19)->y+5, C_WHITE ,-1, "%i x %i", NEW_WIDTH, NEW_HEIGHT);
          
          //All required for editing names, starts of with checking for keypresses
          if (keypressed())
               key_is_pressed = 1;
          
          //Is a key is pressed and the change name button is activated, players can edit the name
          if (edit_name1 == 1 && key_activated == 0 && key_is_pressed == 1)
          {
               key_activated = 1;
               PLAYER_NAME1 = input_change_name(PLAYER_NAME1);
          }
          if (edit_name2 == 1 && key_activated == 0  && key_is_pressed == 1)
          {
               key_activated = 1;
               PLAYER_NAME2 = input_change_name(PLAYER_NAME2);
          }
     
          //Checking when the key is released, so that another keypress can give another 1 letter
          if (key_is_pressed == 1)
               if (!key[KEY_BACKSPACE] && !key[KEY_SPACE])
                    if (!key[KEY_A]  && !key[KEY_B] && !key[KEY_C] && !key[KEY_D] && !key[KEY_E] && !key[KEY_F] && !key[KEY_G] && !key[KEY_H])
                         if (!key[KEY_I] && !key[KEY_J] && !key[KEY_K] && !key[KEY_L] && !key[KEY_M] && !key[KEY_N] && !key[KEY_O] && !key[KEY_P])
                              if (!key[KEY_Q] && !key[KEY_R] && !key[KEY_S] && !key[KEY_T] && !key[KEY_U] && !key[KEY_V] && !key[KEY_W])
                                   if (!key[KEY_X] && !key[KEY_Y] && !key[KEY_Z])
                                   {
                                        key_is_pressed = 0;
                                        key_activated = 0;
                                   }

          //Drawing some HUD info in the options menu for changing names
          if (edit_name1 == 0)
               rectfill(buffer, buttons->get(20)->x+150, buttons->get(20)->y, buttons->get(20)->x+350, buttons->get(20)->y+32, C_BLACK);
          if (edit_name1 == 1)
               rectfill(buffer, buttons->get(20)->x+150, buttons->get(20)->y, buttons->get(20)->x+350, buttons->get(20)->y+32, C_RED);
          if (edit_name2 == 0)
               rectfill(buffer, buttons->get(21)->x+150, buttons->get(21)->y, buttons->get(21)->x+350, buttons->get(21)->y+32, C_BLACK);
          if (edit_name2 == 1)
               rectfill(buffer, buttons->get(21)->x+150, buttons->get(21)->y, buttons->get(21)->x+350, buttons->get(21)->y+32, C_RED);
          textprintf_centre_ex(buffer, f_hud, buttons->get(20)->x+250, buttons->get(20)->y+5, C_WHITE ,-1, "%s", PLAYER_NAME1.c_str());
          textprintf_centre_ex(buffer, f_hud, buttons->get(21)->x+250, buttons->get(21)->y+5, C_WHITE ,-1, "%s", PLAYER_NAME2.c_str());

          //This function will activate button presses
          check_for_change_settings();

          //If an button was pressed
          if (allow_edit == 1)
          {
               if (choice_menu == "Apply")
               {
                    if (MODE == GFX_AUTODETECT_FULLSCREEN && SWITCH_MODE == SWITCH_PAUSE)
                         write_data("settings/display.ini", 1, 1);
                    if (MODE == GFX_AUTODETECT_WINDOWED && SWITCH_MODE == SWITCH_BACKGROUND)
                         write_data("settings/display.ini", 2, 2);
                    if (MODE == GFX_AUTODETECT_FULLSCREEN && SWITCH_MODE == SWITCH_BACKGROUND)
                         write_data("settings/display.ini", 1, 2);
                    if (MODE == GFX_AUTODETECT_WINDOWED && SWITCH_MODE == SWITCH_PAUSE)
                         write_data("settings/display.ini", 2, 1);

                    write_data("settings/sound.ini", VOLUME_SND, VOLUME_MID);
                    write_data("settings/gameplay.ini", REST_DUR, PLAY_MOVIE);
                    write_data("settings/mouse.ini", HARDWARE_CURSOR, SPEED_CURSOR);
                    write_string_data("settings/player.ini", PLAYER_NAME1, PLAYER_NAME2);
                    
                    set_volume(VOLUME_SND,VOLUME_MID);    
                    if (HARDWARE_CURSOR == 1)
                         enable_hardware_cursor();
                    else
                         disable_hardware_cursor();
                    set_mouse_speed(SPEED_CURSOR, SPEED_CURSOR);
                    
                    if (is_windowed_mode() && MODE == GFX_AUTODETECT_FULLSCREEN)
                    {
                         if (NEW_WIDTH != 800 && NEW_HEIGHT != 640)
                         {
                              WIDTH = 640; NEW_WIDTH = 640;
                              HEIGHT = 480; NEW_HEIGHT = 480;
                         }
                         write_data("settings/resolution.ini", WIDTH, HEIGHT);
                         set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
                         EDIT_RESOLUTION = 0;
                    }
                    if (!is_windowed_mode() && MODE == GFX_AUTODETECT_WINDOWED)
                    {
                         WIDTH = NEW_WIDTH;
                         HEIGHT = NEW_HEIGHT;
                         write_data("settings/resolution.ini", WIDTH, HEIGHT);
                         set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
                         EDIT_RESOLUTION = 0;
                    }
                    if (EDIT_RESOLUTION == 1)
                    {
                         WIDTH = NEW_WIDTH;
                         HEIGHT = NEW_HEIGHT;
                         write_data("settings/resolution.ini", WIDTH, HEIGHT);
                         set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
                         EDIT_RESOLUTION = 0;
                    }
                    set_display_switch_mode(SWITCH_MODE);
                    buttons->get(1)->alive = 0;
               }
               allow_edit = 0;
          }
          update_screen();
     }

     play_midi(mid_main, 0); //Start menu theme
     edit_name1 = 0;
     edit_name2 = 0;
     reading_all_setting_files();
     edit_menu_sprites();
}

void loop_submenu3()
{
     play_midi(mid_highscore, 1); //Start highscore theme
     //reading_highscore_file();
     
     //submenu 2 loop (Highscore)
     while (choice_menu != "Back")
     {
          init_menuloop(); //game.h
          
          for (n=0; n<2; n++)
          {
               buttons->get(n)->drawframe(buffer);
               press_button(buttons->get(n));
               if (mb1_hold == 1)
                    release_button(buttons->get(curnb));
          }
          
          //Display the highscore on screen
          textprintf_centre_ex(buffer, f_starttext, O_WIDTH/2, 110, C_YELLOW ,-1, "Best Highscores");
          
          if (highscore.size() == 0)
          {
               textprintf_centre_ex(buffer, f_button, O_WIDTH/2, 200, C_WHITE ,-1, "There is no available highscore to read");
               textprintf_centre_ex(buffer, f_button, O_WIDTH/2, 240, C_WHITE ,-1, "Play a game to add highscore to this list");
          }
          if (highscore.size() != 0)
               for (unsigned char i=0; i<highscore.size(); i++)
               {
                    textprintf_ex(buffer, f_button, 100, 180+i*40, C_WHITE ,-1, "%i", i+1);
                    textprintf_centre_ex(buffer, f_button, O_WIDTH/2-100, 180+i*40, C_WHITE ,-1, "Rounds: %i", highscore.at(i).points);
                    textprintf_centre_ex(buffer, f_button, O_WIDTH/2+100, 180+i*40, C_WHITE ,-1, "Player: %s", highscore.at(i).player.c_str());
               }
          
          //Pressing the reset button resets all highscore
          if (choice_menu == "Reset" && allow_edit == 1)
          {
               ofstream utfil;
               utfil.open("data/highscore.ini");
               utfil.close();
               allow_edit = 0;
               highscore.clear();
          }
          
          update_screen();
     }
     play_midi(mid_main, 0); //Start menu theme
     edit_menu_sprites();
}

void loop_submenu4()
{
     play_midi(mid_credits, 1); //Start credits theme
     
     //submenu 4 loop (Credits)
     while (choice_menu != "Back")
     {
          init_menuloop(); //game.h
          
          for (n=0; n<NUM_MENU_B; n++)
          {
               buttons->get(n)->drawframe(buffer);
               press_button(buttons->get(n));
               if (mb1_hold == 1)
                    release_button(buttons->get(curnb));
          }
          
          textprintf_centre_ex(buffer, f_starttext, O_WIDTH/2, 20, C_RED ,-1, "Rainbow Productions & O.P.I.G.");
          textprintf_centre_ex(buffer, f_starttext, O_WIDTH/2, 50, C_RED ,-1, "Made by Robin");
          textprintf_centre_ex(buffer, f_starttext, O_WIDTH/2, 80, C_GREEN ,-1, "BattleBuddies");
          
          
          read_credits_data("credits/menu music.ini");
          read_credits_data("credits/preparation music.ini");
          read_credits_data("credits/aftermatch music.ini");
          read_credits_data("credits/main music.ini");
          read_credits_data("credits/graphics.ini");

          update_screen();
     }

     play_midi(mid_main, 0); //Start menu theme
     edit_menu_sprites();
}

string input_change_name(string temp_name)
{    
     //Backspace, Escape Space key pressed, and a check for max. string length
     if (key[KEY_BACKSPACE] && temp_name.size() != 0)
          temp_name.erase(temp_name.end()-1, temp_name.end());
     if (key[KEY_ESC])
          temp_name = "";
     
     if (temp_name.size() > 7)
          return temp_name;     
     
     if (key[KEY_SPACE] && temp_name.size() != 0)
          temp_name += " ";

     //Letter keys pressed
     if (key[KEY_A]) { if (temp_name.size() != 0) temp_name += "a"; else temp_name += "A"; }
     if (key[KEY_B]) { if (temp_name.size() != 0) temp_name += "b"; else temp_name += "B"; }
     if (key[KEY_C]) { if (temp_name.size() != 0) temp_name += "c"; else temp_name += "C"; }
     if (key[KEY_D]) { if (temp_name.size() != 0) temp_name += "d"; else temp_name += "D"; }
     if (key[KEY_E]) { if (temp_name.size() != 0) temp_name += "e"; else temp_name += "E"; }
     if (key[KEY_F]) { if (temp_name.size() != 0) temp_name += "f"; else temp_name += "F"; }
     if (key[KEY_G]) { if (temp_name.size() != 0) temp_name += "g"; else temp_name += "G"; }
     if (key[KEY_H]) { if (temp_name.size() != 0) temp_name += "h"; else temp_name += "H"; }
     if (key[KEY_I]) { if (temp_name.size() != 0) temp_name += "i"; else temp_name += "I"; }
     if (key[KEY_J]) { if (temp_name.size() != 0) temp_name += "j"; else temp_name += "J"; }
     if (key[KEY_K]) { if (temp_name.size() != 0) temp_name += "k"; else temp_name += "K"; }
     if (key[KEY_L]) { if (temp_name.size() != 0) temp_name += "l"; else temp_name += "L"; }
     if (key[KEY_M]) { if (temp_name.size() != 0) temp_name += "m"; else temp_name += "M"; }
     if (key[KEY_N]) { if (temp_name.size() != 0) temp_name += "n"; else temp_name += "N"; }
     if (key[KEY_O]) { if (temp_name.size() != 0) temp_name += "o"; else temp_name += "O"; }
     if (key[KEY_P]) { if (temp_name.size() != 0) temp_name += "p"; else temp_name += "P"; }
     if (key[KEY_Q]) { if (temp_name.size() != 0) temp_name += "q"; else temp_name += "Q"; }
     if (key[KEY_R]) { if (temp_name.size() != 0) temp_name += "r"; else temp_name += "R"; }
     if (key[KEY_S]) { if (temp_name.size() != 0) temp_name += "s"; else temp_name += "S"; }
     if (key[KEY_T]) { if (temp_name.size() != 0) temp_name += "t"; else temp_name += "T"; }
     if (key[KEY_U]) { if (temp_name.size() != 0) temp_name += "u"; else temp_name += "U"; }
     if (key[KEY_V]) { if (temp_name.size() != 0) temp_name += "v"; else temp_name += "V"; }
     if (key[KEY_W]) { if (temp_name.size() != 0) temp_name += "w"; else temp_name += "W"; }
     if (key[KEY_X]) { if (temp_name.size() != 0) temp_name += "x"; else temp_name += "X"; }
     if (key[KEY_Y]) { if (temp_name.size() != 0) temp_name += "y"; else temp_name += "Y"; }
     if (key[KEY_Z]) { if (temp_name.size() != 0) temp_name += "z"; else temp_name += "Z"; }
     //End of all leter keys

     return temp_name;
}

void check_for_change_settings()
{
     //Sound check
     if (choice_menu == "Sound" && allow_edit == 1) { if (VOLUME_SND != 0) VOLUME_SND = 0; else VOLUME_SND = 255; }
     if (choice_menu == "Sound More" && allow_edit == 1) { if (VOLUME_SND < 241) VOLUME_SND += 15; else VOLUME_SND = 255; }
     if (choice_menu == "Sound Less" && allow_edit == 1) { if (VOLUME_SND > 14) VOLUME_SND -= 15;  else VOLUME_SND = 0; }
     
     //Music check
     if (choice_menu == "Music" && allow_edit == 1) {  if (VOLUME_MID != 0) VOLUME_MID = 0; else VOLUME_MID = 255; }
     if (choice_menu == "Music More" && allow_edit == 1) { if (VOLUME_MID < 241) VOLUME_MID += 15; else VOLUME_MID = 255; }
     if (choice_menu == "Music Less" && allow_edit == 1) { if (VOLUME_MID > 14) VOLUME_MID -= 15; else VOLUME_MID = 0; }
     
     //Slowdown check
     if (choice_menu == "Slowdown" && allow_edit == 1) { if (REST_DUR != 20) REST_DUR = 20; else REST_DUR = 0; }
     if (choice_menu == "Slowdown More" && allow_edit == 1) { if (REST_DUR < 20) REST_DUR ++; }
     if (choice_menu == "Slowdown Less" && allow_edit == 1) { if (REST_DUR > 0) REST_DUR --; }
     
     //Mouse Speed Check
     if (choice_menu == "Mouse Speed" && allow_edit == 1) { if (SPEED_CURSOR != 1) SPEED_CURSOR = 1; else SPEED_CURSOR = 10; }
     if (choice_menu == "Slow Mouse More" && allow_edit == 1) { if (SPEED_CURSOR < 10) SPEED_CURSOR ++; }
     if (choice_menu == "Slow Mouse Less" && allow_edit == 1) { if (SPEED_CURSOR > 1) SPEED_CURSOR --; }
     
     //Change name check
     if (choice_menu == "Name 1" && allow_edit == 1) { buttons->get(20)->text = "Save Name 1"; buttons->get(21)->text = "Name 2"; edit_name1 = 1; edit_name2 = 0; }
     if (choice_menu == "Save Name 1" && allow_edit == 1) { buttons->get(20)->text = "Name 1"; edit_name1 = 0; if (PLAYER_NAME1 == "") PLAYER_NAME1 = "Player 1"; }
     if (choice_menu == "Name 2" && allow_edit == 1) { buttons->get(20)->text = "Name 1"; buttons->get(21)->text = "Save Name 2"; edit_name1 = 0; edit_name2 = 1; }
     if (choice_menu == "Save Name 2" && allow_edit == 1) { buttons->get(21)->text = "Name 2"; edit_name2 = 0; if (PLAYER_NAME2 == "") PLAYER_NAME2 = "Player 2"; }
          
     //Resolution check
     if (choice_menu == "Resolution" && allow_edit == 1)
     {
          if (NEW_WIDTH != 640 && NEW_HEIGHT != 480)
          {
               NEW_WIDTH = 640;
               NEW_HEIGHT = 480;
          }
          else if (GFX_AUTODETECT_WINDOWED)
          {
              NEW_WIDTH = 960;
              NEW_HEIGHT = 720;
          }
          else if (GFX_AUTODETECT_FULLSCREEN)
          {
              NEW_WIDTH = 800;
              NEW_HEIGHT = 600;
          }
          EDIT_RESOLUTION = 1;
     }
     if (choice_menu == "Resolution More" && allow_edit == 1)
     {
          if (NEW_WIDTH < 960 && NEW_HEIGHT < 720 && is_windowed_mode())
          {
               NEW_WIDTH += 80;
               NEW_HEIGHT += 60;
               EDIT_RESOLUTION = 1;
          }
          if (NEW_WIDTH < 800 && NEW_HEIGHT < 600 && !is_windowed_mode())
          {
               NEW_WIDTH += 160;
               NEW_HEIGHT += 120;
               EDIT_RESOLUTION = 1;
          }
     }
     if (choice_menu == "Resolution Less" && allow_edit == 1)
     {
          if (NEW_WIDTH > 640 && NEW_HEIGHT > 480 && is_windowed_mode())
          {
               NEW_WIDTH -= 80;
               NEW_HEIGHT -= 60;
               EDIT_RESOLUTION = 1;
          }
          if (NEW_WIDTH > 640 && NEW_HEIGHT > 480 && !is_windowed_mode())
          {
               NEW_WIDTH -= 160;
               NEW_HEIGHT -= 120;
               EDIT_RESOLUTION = 1;
          }
     }
     
     //Fullscreen Check
     if (choice_menu == "Fullscreen" && allow_edit == 1) { if (MODE == GFX_AUTODETECT_WINDOWED) { buttons->get(7)->select = 1; MODE = GFX_AUTODETECT_FULLSCREEN; } else { buttons->get(7)->select = 0; MODE = GFX_AUTODETECT_WINDOWED; } }
          
     //Background Switch Check
     if (choice_menu == "Background" && allow_edit == 1) { if (SWITCH_MODE == SWITCH_BACKGROUND) { buttons->get(8)->select = 0; SWITCH_MODE = SWITCH_PAUSE; } else { buttons->get(8)->select = 1; SWITCH_MODE = SWITCH_BACKGROUND; }}
     
     //Hardware Cursor Check
     if (choice_menu == "HW Cursor" && allow_edit == 1) { if (HARDWARE_CURSOR == 1) { buttons->get(9)->select = 0; HARDWARE_CURSOR = 0; } else { buttons->get(9)->select = 1; HARDWARE_CURSOR = 1; } }
     
     //Movie Check
     if (choice_menu == "Movie" && allow_edit == 1) { if (PLAY_MOVIE == 1) { buttons->get(22)->select = 0; PLAY_MOVIE = 0; } else { buttons->get(22)->select = 1; PLAY_MOVIE = 1; } }
     
     if (choice_menu != "Settings" && choice_menu != "Apply" && choice_menu != "Name 1" && choice_menu != "Name 2")
     {
          if (buttons->get(1)->alive == 0)
               buttons->get(1)->alive = 1;
          edit_name1 = 0;
          edit_name2 = 0;
          buttons->get(20)->text = "Name 1";
          buttons->get(21)->text = "Name 2";
     }
}



#endif
