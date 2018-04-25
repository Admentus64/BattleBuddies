#ifndef PRELOAD_H
#define PRELOAD_H

////////////////////////////////////////////////
/// Function to prepare starting the program ///
////////////////////////////////////////////////
void startgame()
{
     //Initialization
     allegro_init();
     reading_all_setting_files();
     reading_highscore_file();
     
     //Setting up the graphics engines bases on the values from above
     set_color_depth(COLOR_DEPTH);
     request_refresh_rate(REFRESH_RATE);
     if (PLAY_MOVIE == 0)
     {
          set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
          set_display_switch_mode(SWITCH_MODE);
     }
     
     install_keyboard();
     install_timer();
     install_mouse();
     
     //Timer and randomness setup
     srand(time(0));
     LOCK_VARIABLE(time);
	 LOCK_FUNCTION(timer);
	 install_int_ex(timer, BPS_TO_TIMER(updates_per_second));
     
     //Install the sound driver
     if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0)
     { allegro_message("Error initializing sound system\n%s\n", allegro_error); return; }
	      
     //Setup mouse
     if (HARDWARE_CURSOR == 1)
          enable_hardware_cursor();
     set_mouse_speed(SPEED_CURSOR, SPEED_CURSOR);
     
     //Set sound and music volume
	 set_volume(VOLUME_SND,VOLUME_MID);
	 
	 //Functions to load all resources + back buffer
     check_resources();
     buffer = create_bitmap(WIDTH, HEIGHT);
     
     //start_intro_movie();
     
     if (file_is_missing == 1)
     {
          set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
          set_display_switch_mode(SWITCH_PAUSE);
          show_os_cursor(MOUSE_CURSOR_ALLEGRO);
          return;
     }
	 load_resources1();
	 play_midi(mid_main, 1); //Start menu theme
	 start_intro_movie();
	 load_resources2();
}

//////////////////////////////////////////////////
/// Function to check all resources on startup ///
//////////////////////////////////////////////////
void check_resources()
{
      for (int i=0; i<TOTAL_FILES; i++)
           for (int j=0; j<TYPE_FILES; j++)
                file_missing[i][j] = 0;
     
      //Image files
      if (!exists("data/images/core.dat"))
	       file_missing[0][0] = 1;
      if (!exists("data/images/setting.dat"))
	       file_missing[1][0] = 1;
      if (!exists("data/images/guide.dat"))
	       file_missing[2][0] = 1;
      
      //Sound files
      if (!exists("data/sounds/button.dat"))
	       file_missing[0][1] = 1;
      if (!exists("data/sounds/fight.dat"))
	       file_missing[1][1] = 1;
      if (!exists("data/sounds/game.dat"))
	       file_missing[2][1] = 1;
      
      //Music files
      if (!exists("data/music/aftermatch.dat"))
	       file_missing[0][2] = 1;
      if (!exists("data/music/menu.dat"))
	       file_missing[1][2] = 1;
      if (!exists("data/music/preparation.dat"))
	       file_missing[2][2] = 1;
      if (!exists("data/music/theme.dat"))
	       file_missing[3][2] = 1;
      if (!exists("data/music/theme.ini"))
	       file_missing[4][2] = 1;
     if (!exists("data/music/preparation.ini"))
	       file_missing[5][2] = 1;
	       
      //Font files
      if (!exists("data/fonts/fonts.dat"))
	       file_missing[0][3] = 1;
     
     //Background files
      if (!exists("data/backgrounds/images - grass.dat"))
	       file_missing[0][4] = 1;
      if (!exists("data/backgrounds/images - sand.dat"))
	       file_missing[1][4] = 1;
	  if (!exists("data/backgrounds/images - snow.dat"))
	       file_missing[2][4] = 1;
     
     //Button files
     if (!exists("data/buttons/images - button.dat"))
	       file_missing[0][5] = 1;
     if (!exists("data/buttons/images - arrow.dat"))
	       file_missing[1][5] = 1;
     if (!exists("data/buttons/fonts - button.dat"))
	       file_missing[2][5] = 1;
     
     //Misc files
     if (!exists("data/misc/images - pointer.dat"))
	       file_missing[0][6] = 1;
     if (!exists("data/misc/images - explosion.dat"))
	       file_missing[1][6] = 1;
     
     //FLIC files
     if (!exists("data/FLIC/octahedron.fli"))
	       file_missing[0][7] = 1;
     if (!exists("data/FLIC/particles.fli"))
	       file_missing[1][7] = 1;
     
     //Unit files
     if (!exists("data/units/images - bullet.dat"))
	       file_missing[0][8] = 1;
     if (!exists("data/units/images - chopper.dat"))
	       file_missing[1][8] = 1;
     if (!exists("data/units/images - fighter.dat"))
	       file_missing[2][8] = 1;
     if (!exists("data/units/images - mec.dat"))
	       file_missing[3][8] = 1;
     if (!exists("data/units/images - odin.dat"))
	       file_missing[4][8] = 1;
     if (!exists("data/units/images - tank.dat"))
	       file_missing[5][8] = 1;
     if (!exists("data/units/sounds - chopper.dat"))
	       file_missing[6][8] = 1;
     if (!exists("data/units/sounds - fighter.dat"))
	       file_missing[7][8] = 1;
     if (!exists("data/units/sounds - mec.dat"))
           file_missing[8][8] = 1;
     if (!exists("data/units/sounds - odin.dat"))
	       file_missing[9][8] = 1;
     if (!exists("data/units/sounds - tank.dat"))
	       file_missing[10][8] = 1;

      for (int i=0; i<TOTAL_FILES; i++)
           for (int j=0; j<TYPE_FILES; j++)
                if (file_missing[i][j] == 1)
                     file_is_missing = 1;
}

/////////////////////////////////////////////////
/// Function to load all resources on startup ///
/////////////////////////////////////////////////
void load_resources1()
{
     //Music - Menu
     datafiles[7] = load_datafile("data/music/menu.dat");
     for (int j=0; j<MID_MENU_SIZE; j++)
          mid_menu[j] = (MIDI *)datafiles[7][j].dat;
     
     //Fonts - Fonts
     datafiles[10] = load_datafile("data/fonts/fonts.dat");
     for (int j=0; j<FONT_SIZE; j++) //Load fonts from datafile
          fonts[j] = (FONT *)datafiles[10][j].dat;
}

void load_resources2()
{
     //Images - Core
     datafiles[0] = load_datafile("data/images/core.dat");
     for (int j=0; j<IMG_CORE_SIZE; j++)
          img_core[j] = (BITMAP *)datafiles[0][j].dat;

     //Images - Setting
     datafiles[1] = load_datafile("data/images/setting.dat");
     for (int j=0; j<IMG_SETTING_SIZE; j++)
          img_setting[j] = (BITMAP *)datafiles[1][j].dat;

     //Sounds - Button
     datafiles[3] = load_datafile("data/sounds/button.dat");
     for (int j=0; j<SND_BUTTON_SIZE; j++)
          snd_button[j] = (SAMPLE *)datafiles[3][j].dat;

     //Sounds - Fight
     datafiles[4] = load_datafile("data/sounds/fight.dat");
     for (int j=0; j<SND_FIGHT_SIZE; j++)
          snd_fight[j] = (SAMPLE *)datafiles[4][j].dat;

     //Sounds - Game
     datafiles[5] = load_datafile("data/sounds/game.dat");
     for (int j=0; j<SND_GAME_SIZE; j++)
          snd_game[j] = (SAMPLE *)datafiles[5][j].dat;
}

/////////////////////////////////////////////////////////
/// Function load all variables bases on loaded files ///
/////////////////////////////////////////////////////////
void reading_all_setting_files()
{
     //Game starts with reading saved data, if not readable or wrong data the game uses default worths
     //The returned values will be used for setup later in this function
     
     MODE = read_data("settings/display.ini", 1, 2, 1, 2);
     if (MODE == 1)
          MODE = GFX_AUTODETECT_FULLSCREEN;
     if (MODE != 1)
          MODE = GFX_AUTODETECT_WINDOWED;
     SWITCH_MODE = read_data("settings/display.ini", 2, 1, 1, 2);
     if (SWITCH_MODE == 1)
          SWITCH_MODE = SWITCH_PAUSE;
     if (SWITCH_MODE != 1)
          SWITCH_MODE = SWITCH_BACKGROUND;
     if (error_reading_file == 1)
          write_data("settings/display.ini", 2, 1);
     
     COLOR_DEPTH = read_data("settings/editable/color depth.ini", 1, 32, 8, 32);  
     if (COLOR_DEPTH != 8 && COLOR_DEPTH != 15 && COLOR_DEPTH != 16 && COLOR_DEPTH != 24 && COLOR_DEPTH != 32)
          error_reading_file = 1;
     if (error_reading_file == 1) 
     {   
          write_data("settings/editable/color depth.ini", 32, 0);
          COLOR_DEPTH = 32;
     }
             
     REFRESH_RATE = read_data("settings/editable/refresh rate.ini", 1, 60, 25, 75);
     if (REFRESH_RATE != 25 && REFRESH_RATE != 29 && REFRESH_RATE != 30 && REFRESH_RATE != 50 && REFRESH_RATE != 56 && REFRESH_RATE != 59 && REFRESH_RATE != 60 && REFRESH_RATE != 67 && REFRESH_RATE != 70 && REFRESH_RATE != 72 && REFRESH_RATE != 75)
          error_reading_file = 1;
     if (error_reading_file == 1) 
     {   
          write_data("settings/editable/refresh rate.ini", 60, 0);
          REFRESH_RATE = 60;
     }
     
     WIDTH = read_data("settings/resolution.ini", 1, 640, 100, 1000);
     HEIGHT = read_data("settings/resolution.ini", 2, 480, 100, 1000);
     NEW_WIDTH = read_data("settings/resolution.ini", 1, 640, 100, 1000);
     NEW_HEIGHT = read_data("settings/resolution.ini", 2, 480, 100, 1000);
     
     if (MODE == GFX_AUTODETECT_WINDOWED)
     {
          if (WIDTH != 640 && WIDTH != 720 && WIDTH != 800 && WIDTH != 880 && WIDTH != 960)
               error_reading_file = 1;
          if (HEIGHT != 480 && HEIGHT != 540 && HEIGHT != 600 && HEIGHT != 660 && HEIGHT != 720)
               error_reading_file = 1;
     }
     if (MODE == GFX_AUTODETECT_FULLSCREEN)
     {
          if (WIDTH != 640 && WIDTH != 800)
               error_reading_file = 1;
          if (HEIGHT != 480 && HEIGHT != 600)
               error_reading_file = 1;
     }
     if (error_reading_file == 1)
     {
          write_data("settings/resolution.ini", 640, 480);
          WIDTH = 640; NEW_WIDTH = 640;
          HEIGHT = 480; NEW_HEIGHT = 640;
     }
     
     HARDWARE_CURSOR = read_data("settings/mouse.ini", 1, 0, 0, 1);
     SPEED_CURSOR = read_data("settings/mouse.ini", 2, 2, 1, 10);
     if (error_reading_file == 1)
          write_data("settings/mouse.ini", 0, 1);
     
     REST_DUR = read_data("settings/gameplay.ini", 1, 10, 0, 20);
     PLAY_MOVIE = read_data("settings/gameplay.ini", 2, 1, 0, 1);
     if (error_reading_file == 1)
          write_data("settings/gameplay.ini", 10, 1);
     
     VOLUME_SND = read_data("settings/sound.ini", 1, 255, 0, 255);
     VOLUME_MID = read_data("settings/sound.ini", 2, 175, 0, 255);
     if (error_reading_file == 1)
          write_data("settings/sound.ini", 255, 175);
     
     PLAYER_NAME1 = read_string_data("settings/player.ini", 1);
     PLAYER_NAME2 = read_string_data("settings/player.ini", 2);
     if (error_reading_file == 1)
          write_string_data("settings/player.ini", "Error 1", "Error 2");
     
     MAX_SLIDE = read_data("guide/slides.ini", 1, 15, 1, 100);
     if (error_reading_file == 1)
          write_data("guide/slides.ini", 15, 0);
     
     if (error_reading_file == 1)
          error_reading_file = 0;
}

/////////////////////////////////////////////////////////
/// Function load highscores into the game ///
/////////////////////////////////////////////////////////
void reading_highscore_file()
{
     string textstr;
     int value;
     ifstream infil;
     unsigned char row = 1;
     //highscore.clear();
     
     if (!exists("data/highscore.ini"))
          return;
     
     infil.open("data/highscore.ini");
     while(infil.peek()!=EOF)
     {
          getline(infil,textstr);
          if (row == 1)
          {
               stringstream sstr(textstr);
               sstr>>value;
               temp_score.points = value;
               row = 0;
          }
          else
          {
               temp_score.player = textstr;
               highscore.push_back(temp_score);
               row = 1;
          }
     }
     infil.close();
     sort_highscore(highscore);
}

////////////////////////////////////////////////////////
/// Function to setup a list with x- & y-coordinates ///
////////////////////////////////////////////////////////
void setup_coords()
{
     coord_x[0] = 0;                     coord_y[0] = 0;
     coord_x[1] = 41;                    coord_y[1] = 410;
     coord_x[2] = 82;                    coord_y[2] = 369;
     coord_x[3] = 123;                   coord_y[3] = 328;
     coord_x[4] = 164;                   coord_y[4] = 287;
     coord_x[5] = 205;                   coord_y[5] = 246;
     coord_x[6] = 246;                   coord_y[6] = 205;
     coord_x[7] = 287;                   coord_y[7] = 164;
     coord_x[8] = 328;                   coord_y[8] = 123;
     coord_x[9] = 369;                   coord_y[9] = 82;
     coord_x[10] = 410;                  coord_y[10] = 41;
}

/////////////////////////////////////
/// Function to active error mode ///
/////////////////////////////////////
void files_not_found()
{
     int i=0;
     
     textprintf_centre_ex(buffer, font, 320, 10, C_WHITE ,-1, "Files are missing, please restore them");
     textprintf_centre_ex(buffer, font, 320, 20, C_WHITE ,-1, "Press ESC to Exit");
     textprintf_ex(buffer, font, 200, 40, C_WHITE ,-1, "The Following Files are missing:");
     textprintf_ex(buffer, font, 200, 50, C_WHITE ,-1, "--------------------------------");
     
     //Images files are missing
     for (i=0; i<TOTAL_FILES; i++)
          if (file_missing[i][0] == 1)
          {
               textprintf_ex(buffer, font, 220, 70, C_WHITE ,-1, "Images files");
               textprintf_ex(buffer, font, 220, 80, C_WHITE ,-1, "are missing:");
               textprintf_ex(buffer, font, 220, 90, C_WHITE ,-1, "data/images");
               textprintf_ex(buffer, font, 220, 100, C_WHITE ,-1, "------------");
          }
     i=0;
     if (file_missing[i][0] == 1)                                               { textprintf_ex(buffer, font, 220, 110+i*10, C_WHITE ,-1, "core.dat"); i++; }
     if (file_missing[i][0] == 1)                                               { textprintf_ex(buffer, font, 220, 110+i*10, C_WHITE ,-1, "setting.dat"); i++; }
     if (file_missing[i][0] == 1)                                               textprintf_ex(buffer, font, 220, 110+i*10, C_WHITE ,-1, "guide.dat");
     
     //Sound files are missing
     for (i=0; i<TOTAL_FILES; i++)
          if (file_missing[i][1] == 1)
          {
               textprintf_ex(buffer, font, 220, 160, C_WHITE ,-1, "Sound files");
               textprintf_ex(buffer, font, 220, 170, C_WHITE ,-1, "are missing:");
               textprintf_ex(buffer, font, 220, 180, C_WHITE ,-1, "data/sounds");
               textprintf_ex(buffer, font, 220, 190, C_WHITE ,-1, "------------");
          }
     i=0;
     if (file_missing[i][1] == 1)                                               { textprintf_ex(buffer, font, 220, 200+i*10, C_WHITE ,-1, "button.dat"); i++; }
     if (file_missing[i][1] == 1)                                               { textprintf_ex(buffer, font, 220, 200+i*10, C_WHITE ,-1, "fight.dat"); i++; }
     if (file_missing[i][1] == 1)                                               textprintf_ex(buffer, font, 220, 200+i*10, C_WHITE ,-1, "game.dat");
     
     //Music files are missing
     for (i=0; i<TOTAL_FILES; i++)
          if (file_missing[i][2] == 1)
          {
               textprintf_ex(buffer, font, 220, 250, C_WHITE ,-1, "Music files");
               textprintf_ex(buffer, font, 220, 260, C_WHITE ,-1, "are missing:");
               textprintf_ex(buffer, font, 220, 270, C_WHITE ,-1, "data/music");
               textprintf_ex(buffer, font, 220, 280, C_WHITE ,-1, "------------");
          }
     i=0;
     if (file_missing[i][2] == 1)                                               { textprintf_ex(buffer, font, 220, 290+i*10, C_WHITE ,-1, "aftermatch.dat"); i++; }
     if (file_missing[i][2] == 1)                                               { textprintf_ex(buffer, font, 220, 290+i*10, C_WHITE ,-1, "menu.dat"); i++; }
     if (file_missing[i][2] == 1)                                               { textprintf_ex(buffer, font, 220, 290+i*10, C_WHITE ,-1, "preparation.dat"); i++; }
     if (file_missing[i][2] == 1)                                               { textprintf_ex(buffer, font, 220, 290+i*10, C_WHITE ,-1, "theme.dat"); i++; }
     if (file_missing[i][2] == 1)                                               { textprintf_ex(buffer, font, 220, 290+i*10, C_WHITE ,-1, "theme.ini"); i++; }
     if (file_missing[i][2] == 1)                                               textprintf_ex(buffer, font, 220, 290+i*10, C_WHITE ,-1, "preparation.ini");
     
     //Font files are missing
     for (i=0; i<TOTAL_FILES; i++)
          if (file_missing[i][3] == 1)
          {
               textprintf_ex(buffer, font, 220, 370, C_WHITE ,-1, "Font files");
               textprintf_ex(buffer, font, 220, 380, C_WHITE ,-1, "are missing:");
               textprintf_ex(buffer, font, 220, 390, C_WHITE ,-1, "data/fonts");
               textprintf_ex(buffer, font, 220, 400, C_WHITE ,-1, "------------");
          }
     i=0;
     if (file_missing[i][3] == 1)                                               textprintf_ex(buffer, font, 220, 410+i*10, C_WHITE ,-1, "fonts.dat");
     
     //Background files are missing
     for (int i=0; i<TOTAL_FILES; i++)
          if (file_missing[i][4] == 1)
          {
               textprintf_ex(buffer, font, 400, 70, C_WHITE ,-1, "Background files");
               textprintf_ex(buffer, font, 400, 80, C_WHITE ,-1, "are missing:");
               textprintf_ex(buffer, font, 400, 90, C_WHITE ,-1, "data/backgrounds/");
               textprintf_ex(buffer, font, 400, 100, C_WHITE ,-1, "-----------------");
          }
     i=0;
     if (file_missing[i][4] == 1)                                               { textprintf_ex(buffer, font, 400, 110+i*10, C_WHITE ,-1, "images - grass.dat"); i++; }
     if (file_missing[i][4] == 1)                                               { textprintf_ex(buffer, font, 400, 110+i*10, C_WHITE ,-1, "images - sand.dat"); i++; }
     if (file_missing[i][4] == 1)                                               textprintf_ex(buffer, font, 400, 110+i*10, C_WHITE ,-1, "images - snow.dat");
     
     //Button files are missing
     for (int i=0; i<TOTAL_FILES; i++)
          if (file_missing[i][5] == 1)
          {
               textprintf_ex(buffer, font, 400, 160, C_WHITE ,-1, "Button files");
               textprintf_ex(buffer, font, 400, 170, C_WHITE ,-1, "are missing:");
               textprintf_ex(buffer, font, 400, 180, C_WHITE ,-1, "data/buttons/");
               textprintf_ex(buffer, font, 400, 190, C_WHITE ,-1, "-------------");
          }
     i=0;
     if (file_missing[i][5] == 1)                                               { textprintf_ex(buffer, font, 400, 200+i*10, C_WHITE ,-1, "images - button.dat"); i++; }
     if (file_missing[i][5] == 1)                                               { textprintf_ex(buffer, font, 400, 200+i*10, C_WHITE ,-1, "images - arrow.dat"); i++; }
     if (file_missing[i][5] == 1)                                               textprintf_ex(buffer, font, 400, 200+i*10, C_WHITE ,-1, "fonts - buttons.dat");
     
     //Button files are missing
     for (int i=0; i<TOTAL_FILES; i++)
          if (file_missing[i][6] == 1)
          {
               textprintf_ex(buffer, font, 400, 250, C_WHITE ,-1, "Misc files");
               textprintf_ex(buffer, font, 400, 260, C_WHITE ,-1, "are missing:");
               textprintf_ex(buffer, font, 400, 270, C_WHITE ,-1, "data/misc/");
               textprintf_ex(buffer, font, 400, 280, C_WHITE ,-1, "------------");
          }
     i=0;
     if (file_missing[i][6] == 1)                                               { textprintf_ex(buffer, font, 400, 290+i*10, C_WHITE ,-1, "images - pointer.dat"); i++; }
     if (file_missing[i][6] == 1)                                               textprintf_ex(buffer, font, 400, 290+i*10, C_WHITE ,-1, "images - explosion.dat");
     
     //FLIC files are missing
     for (int i=0; i<TOTAL_FILES; i++)
          if (file_missing[i][7] == 1)
          {
               textprintf_ex(buffer, font, 400, 330, C_WHITE ,-1, "FLIC files");
               textprintf_ex(buffer, font, 400, 340, C_WHITE ,-1, "are missing:");
               textprintf_ex(buffer, font, 400, 350, C_WHITE ,-1, "data/FLIC/");
               textprintf_ex(buffer, font, 400, 360, C_WHITE ,-1, "------------");
          }
     i=0;
     if (file_missing[i][7] == 1)                                               { textprintf_ex(buffer, font, 400, 370+i*10, C_WHITE ,-1, "octahedron.fli"); i++; }
     if (file_missing[i][7] == 1)                                               textprintf_ex(buffer, font, 400, 370+i*10, C_WHITE ,-1, "particles.fli");
     
     //Unit files are missing
     for (int i=0; i<TOTAL_FILES; i++)
          if (file_missing[i][8] == 1)
          {
               textprintf_ex(buffer, font, 10, 70, C_WHITE ,-1, "Unit files");
               textprintf_ex(buffer, font, 10, 80, C_WHITE ,-1, "are missing:");
               textprintf_ex(buffer, font, 10, 90, C_WHITE ,-1, "data/units/");
               textprintf_ex(buffer, font, 10, 100, C_WHITE ,-1, "------------");
          }
     i=0;
     if (file_missing[i][8] == 1)                                               { textprintf_ex(buffer, font, 10, 110+i*10, C_WHITE ,-1, "images - bullet.dat"); i++; }
     if (file_missing[i][8] == 1)                                               { textprintf_ex(buffer, font, 10, 110+i*10, C_WHITE ,-1, "images - chopper.dat"); i++; }
     if (file_missing[i][8] == 1)                                               { textprintf_ex(buffer, font, 10, 110+i*10, C_WHITE ,-1, "images - fighter.dat"); i++; }
     if (file_missing[i][8] == 1)                                               { textprintf_ex(buffer, font, 10, 110+i*10, C_WHITE ,-1, "images - mec.dat"); i++; }
     if (file_missing[i][8] == 1)                                               { textprintf_ex(buffer, font, 10, 110+i*10, C_WHITE ,-1, "images - odin.dat"); i++; }
     if (file_missing[i][8] == 1)                                               { textprintf_ex(buffer, font, 10, 110+i*10, C_WHITE ,-1, "images - tank.dat"); i++; }
     if (file_missing[i][8] == 1)                                               { textprintf_ex(buffer, font, 10, 110+i*10, C_WHITE ,-1, "sounds - chopper.dat"); i++; }
     if (file_missing[i][8] == 1)                                               { textprintf_ex(buffer, font, 10, 110+i*10, C_WHITE ,-1, "sounds - fighter.dat"); i++; }
     if (file_missing[i][8] == 1)                                               { textprintf_ex(buffer, font, 10, 110+i*10, C_WHITE ,-1, "sounds - mec.dat"); i++; }
     if (file_missing[i][8] == 1)                                               { textprintf_ex(buffer, font, 10, 110+i*10, C_WHITE ,-1, "sounds - odin.dat"); i++; }
     if (file_missing[i][8] == 1)                                               textprintf_ex(buffer, font, 10, 110+i*10, C_WHITE ,-1, "sounds - tank.dat");
}

////////////////////////////////////////////////
/// Function to start the intro movie (FLIC) ///
////////////////////////////////////////////////
void start_intro_movie()
{
     if (PLAY_MOVIE == 0)
          return;
          
     set_gfx_mode(MODE, 640, 480, 0, 0);
     set_display_switch_mode(SWITCH_MODE);
     
     open_fli("data/FLIC/octahedron.fli");
     while (fli_frame != 360)
     {
          if (fli_timer)
          {
               next_fli_frame(1);
               set_palette(fli_palette);
               blit(fli_bitmap, screen, 0, 0, 150, 130, fli_bitmap->w, fli_bitmap->h);
               textprintf_centre_ex(screen, f_starttext, O_WIDTH/2, 40, C_WHITE,0,"Rainbow Productions & O.P.I.G.");
               textprintf_centre_ex(screen, f_starttext, O_WIDTH/2, 80, C_WHITE,0,"Presents");
          }
          if (key[KEY_ENTER] || key[KEY_ESC])
          {
               fli_frame = 360;
               counter = 2;
          }
     }
     close_fli();
     open_fli("data/FLIC/particles.fli");
     while (fli_frame != 46)
     {
          if (fli_timer)
          {
               next_fli_frame(1);
               set_palette(fli_palette);
               blit(fli_bitmap, screen, 0, 0, 150, 130, fli_bitmap->w, fli_bitmap->h);
               textprintf_centre_ex(screen, f_starttext, O_WIDTH/2, 350, C_RED,0,"BattleBuddies");
          }
          if (key[KEY_ENTER] || key[KEY_ESC])
          {
               fli_frame = 46;
               counter = 2;
          }
     }
     close_fli();
     
     set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
     set_display_switch_mode(SWITCH_MODE);
}

#endif
