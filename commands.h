#ifndef COMMANDS_H
#define COMMANDS_H

/////////////////////////////////////////////
/// Function to load data from text files ///
/////////////////////////////////////////////
int read_data(char *filename, char row, short int reset, short int min, short int max)
{
     //Declare some local variables
     short int value;
     string textstr;
     ifstream infil;
     
     //Returns default value if file doesn't exist
     if (!exists(filename))
     {
          error_reading = 1;
          error_reading_file = 1;
          return reset;
     }
     
     //Files is opened, checking for input and stops at the given row
     infil.open(filename);
     for (int i=0; i<row; i++)
     {
          getline(infil,textstr);
          stringstream sstr(textstr);
          sstr>>value;
     }
     infil.close();

     //Returns default value if value is lower than min or higher than max given by the call of this function
     //Or if no value was give in the file (which means a reset value too)
     //These reset values will be also written in the file
     if (textstr.size() < 1 || value < min || value > max)
     {
          error_reading = 1;
          error_reading_file = 1;
          return reset;
     }
     
     //If no errors, than the value will be given to the game
     return value;
}

string read_string_data(char *filename, char row)
{
     //Declare some local variables
     string textstr;
     ifstream infil;
     
     //Returns default value if file doesn't exist
     if (!exists(filename))
     {
          error_reading = 1;
          error_reading_file = 1;
          if (row == 1)
               return textstr = "Error 1";
          else
               return textstr = "Error 2";
     }
     
     //Files is opened, checking for input and stops at the given row
     infil.open(filename);
     for (int i=0; i<row; i++)
          getline(infil,textstr);
     infil.close();
     
     if (textstr.size() < 1)
     {
          error_reading_file = 1;
          error_reading = 1;
     }
     
     if (textstr.size() > 15 && row == 1)
          textstr = "Too Long 1";
     if (textstr.size() > 15 && row == 2)
          textstr = "Too Long 2";
     return textstr;
}

void write_data(char *filename, short int row1, short int row2)
{
     if (error_reading_file == 1)
          error_reading_file = 0;
     
     ofstream utfil;
     utfil.open(filename);
     utfil<<row1<<endl;
     utfil<<row2<<endl;
     utfil.close();
}
void write_string_data(char *filename, string row1, string row2)
{
     if (error_reading_file == 1)
          error_reading_file = 0;
     
     ofstream utfil;
     utfil.open(filename);
     utfil<<row1<<endl;
     utfil<<row2<<endl;
     utfil.close();
}

void read_music_data(char *filename)
{
     if (!exists(filename))
          return;
     
     string textstr;
     ifstream infil;
     song_name_prep.clear();

     infil.open(filename);
     while(infil.peek()!=EOF)
     {
          getline(infil,textstr);
          song_name_prep.push_back(textstr);
     }
     infil.close();
}

void read_credits_data(char *filename)
{ 
     int text_y, text_x1, text_x2;
     string textstr;
     ifstream infil;
     unsigned char row = 1;
     unsigned char skip_rows = 5;
     int value;
     
     if (!exists(filename))
          return;
     
     infil.open(filename);
     while(infil.peek()!=EOF)
     {
          getline(infil,textstr);
          if (skip_rows > 0)
          {
               if (skip_rows > 2)
               {
                    stringstream sstr(textstr);
                    sstr>>value;
               }
               if (skip_rows == 5)
                    text_y = value;
               if (skip_rows == 4)
                    text_x1 = value;
               if (skip_rows == 3)
                    text_x2 = value;
               if (skip_rows == 2)
               {
                    textprintf_ex(buffer, f_button, text_x1, text_y-25, C_WHITE ,-1, textstr.c_str());
                    textprintf_ex(buffer, f_button, text_x1, text_y-20, C_WHITE ,-1, "--------------------------------------");
               }
               skip_rows--;
          }
          
          if (skip_rows == 0)
          {
               if (row == 1)
               {
                    textprintf_ex(buffer, f_credits, text_x1, text_y, C_WHITE ,-1, textstr.c_str());
                    row = 0;
               }
               else
               {
                    textprintf_ex(buffer, f_credits, text_x2, text_y, C_WHITE ,-1, textstr.c_str());
                    row = 1;
                    text_y += 15;
               }
          }
     }
     infil.close();
}

void read_guide_data(char *filename)
{ 
     short int y, x;
     string textstr;
     ifstream infil;
     unsigned char row = 1;
     unsigned char skip_rows = 5;
     unsigned char stop_reading;
     short int value;
     
     if (!exists(filename))
          return;
     
     infil.open(filename);
     while(infil.peek()!=EOF)
     {
          stop_reading = 0;
          getline(infil,textstr);
          {
               if (row == 1  && stop_reading == 0)
               {
                    stringstream sstr(textstr);
                    sstr>>x;
                       
                    row = 2;
                    stop_reading = 1;
               }
               if (row == 2 && stop_reading == 0)
               {
                    stringstream sstr(textstr);
                    sstr>>y;
                    
                    row = 3;
                    stop_reading = 1;
               }
               if (row == 3  && stop_reading == 0)
               { 
                    if (textstr == "draw_white_cursor")
                         draw_sprite(buffer, cursor1, x, y);
                    else if (textstr == "draw_red_cursor")
                         draw_sprite(buffer, cursor2, x, y);
                    else if (textstr == "draw_green_cursor")
                         draw_sprite(buffer, cursor3, x, y);
                    else if (textstr == "draw_pointer")
                         draw_guide_data("data/misc/images - pointer.dat", 0, 0, 32, 0, x, y, 32, 32);
                    else if (textstr == "draw_button")
                         draw_guide_data("data/buttons/images - button.dat", 1, 0, 0, 0, x, y, 128, 32);
                    else if (textstr == "draw_chopper")
                         draw_guide_data("data/units/images - chopper.dat", 0, 1, 0, 0, x, y, 40, 40);
                    else if (textstr == "draw_light_tank")
                         draw_guide_data("data/units/images - tank.dat", 1, 1, 0, 0, x, y, 32, 32);
                    else if (textstr == "draw_MEC")
                         draw_guide_data("data/units/images - mec.dat", 2, 1, 0, 0, x, y, 41, 41);
                    else if (textstr == "draw_odin")
                         draw_guide_data("data/units/images - odin.dat", 3, 1, 0, 0, x, y, 39, 39);
                    else if (textstr == "draw_f9_fighter")
                         draw_guide_data("data/units/images - fighter.dat", 4, 1, 0, 0, x, y, 32, 32);
                    else if (textstr == "draw_bullet")
                         draw_guide_data("data/units/images - bullet.dat", 0, 1, 0, 0, x, y, 32, 32);
                    else if (textstr == "draw_explosion")
                         draw_guide_data("data/misc/images - explosion.dat", 0, 0, 156, 0, x, y, 39, 39);
                    else if (textstr == "draw_grass")
                         draw_guide_data("data/backgrounds/images - grass.dat", 0, 0, 0, 0, x, y, 320, 40);
                    else if (textstr == "draw_sand")
                         draw_guide_data("data/backgrounds/images - sand.dat", 1, 0, 0, 0, x, y, 280, 40);
                    else if (textstr == "draw_snow")
                         draw_guide_data("data/backgrounds/images - snow.dat", 2, 0, 0, 0, x, y, 280, 40);
                    else if (textstr == "draw_on")
                         draw_guide_data("data/images/setting.dat", 5, 2, 0, 0, x, y, 32, 32);
                    else if (textstr == "draw_hud")
                         draw_guide_data("data/images/core.dat", 0, 6, 0, 0, x, y, 176, 240);
                    else if (textstr == "draw_water")
                         draw_guide_data("data/backgrounds/images - grass.dat", 1, 0, 280, 0, x, y, 40, 40);
                    else
                         textprintf_centre_ex(buffer, f_guide, x, y, C_WHITE ,-1, textstr.c_str());
                    
                    row = 1;
                    stop_reading = 1;
               }
          }
     }
     infil.close();
}

void draw_guide_data(char *filename, char file, char image, short int source_x, short int source_y, short int x, short int y, short int width, short int height)
{
     if (temp_sprite_loaded[file] == 0)
     {
          temp_data[file] = load_datafile(filename);
          temp_sprite[file] = (BITMAP *)temp_data[file][image].dat;
          temp_sprite_loaded[file] = 1;
     }
     if (temp_sprite_loaded[file] == 1)
          masked_blit(temp_sprite[file], buffer, source_x, source_y, x, y, width, height);
}

void read_highscore_data(char *filename)
{
     short int y = 180;
     string textstr;
     ifstream infil;
     unsigned char row = 1;
     unsigned char entre = 1;
     infil.open(filename);
     while(infil.peek()!=EOF)
     {
          getline(infil,textstr);
          if (row == 1)
          {
               textprintf_ex(buffer, f_button, 100, y, C_WHITE ,-1, "%i", entre);
               textprintf_centre_ex(buffer, f_button, O_WIDTH/2-100, y, C_WHITE ,-1, textstr.c_str());
               row = 0;
          }
          else
          {
               textprintf_centre_ex(buffer, f_button, O_WIDTH/2+100, y, C_WHITE ,-1, textstr.c_str());
               row = 1;
               y += 40;
               entre++;
          }
     }
     infil.close();
}

void sort_highscore(vector<score>& highscore)
{
     //Declare variables
     unsigned char temp_points1, temp_points2;
     string temp_player1, temp_player2;
     
     //Goes through each score (their are only 5 scores or 6 after a won match)
     for (unsigned char i=0; i<highscore.size(); i++)
          //The current score will be checked for swapping with the score beneath for 4 times or 5 after a won match
          for (unsigned char i=0; i<highscore.size()-1; i++)
          {
               //Making temp values
               temp_points1 = highscore.at(i).points;
               temp_points2 = highscore.at(i+1).points;
               temp_player1 = highscore.at(i).player;
               temp_player2 = highscore.at(i+1).player;
     
               //If the current score is higher than the score beneath, then the current score and the score beneath swap placed
               if (highscore.at(i).points > highscore.at(i+1).points)
               {
                    highscore.at(i).points = temp_points2;
                    highscore.at(i).player = temp_player2;
                    highscore.at(i+1).points = temp_points1;
                    highscore.at(i+1).player = temp_player1;
               }
          }
}

void init_menuloop()
{
     //Grab the current mouse values
     mx = mouse_x; my = mouse_y; mb1 = (mouse_b & 1); mb2 = (mouse_b & 2);

     draw_sprite(buffer, bg, 0, 0); //Redraws the background
     
     //Print Menu Title
     if (choice_menu != "Credits")
     {
          textprintf_centre_ex(buffer, f_starttext, O_WIDTH/2, 50, C_RED ,-1, "--- Welcome to ---");
          textprintf_centre_ex(buffer, f_starttext, O_WIDTH/2, 80, C_GREEN ,-1, "BattleBuddies");
     }
     
     //Pressing ESCAPE will return you to the main menu (this does not work when in main menu)
     if (choice_menu != "Back" && choice_menu != "Exit Game" && choice_menu != "Sure?" && choice_menu != "Game Ended")
          if (key[KEY_ESC] && keyboard_pressed == 1)
          {
               keyboard_pressed = 0;
               play_sample(snd_button_click, 255, 128, 1000, FALSE);
               choice_menu = "Back";
          }
}

void update_screen_errormode()
{
     //update the screen when game got error with loading data files
     acquire_screen();
     stretch_blit(buffer, screen, 0, 0, O_WIDTH, O_HEIGHT, 0, 0, WIDTH, HEIGHT);
     release_screen();
}

void update_screen()
{
     //Allows also keyboard input, but does not do tasks (it only registers if a keyboard key was pressed or released)
     keyboard_registering();
     
     //Repositioning the mouse
     short int x, y;
     
     //update the screen and redrawing the mouse
     acquire_screen();
     
     if (mb1_hold == 0 && mb2_hold == 0 && mouse_over == 0)
          draw_sprite(buffer, cursor1, mouse_x-5, mouse_y-7);
     if (   (mb1_hold == 1 || mb2_hold == 1) && mouse_over == 0)
          draw_sprite(buffer, cursor2, mouse_x-5, mouse_y-7);
     if (mb1_hold == 0 && mb2_hold == 0 && mouse_over == 1)
          draw_sprite(buffer, cursor3, mouse_x-5, mouse_y-7);
     
     stretch_blit(buffer, screen, 0, 0, O_WIDTH, O_HEIGHT, 0, 0, WIDTH, HEIGHT);
     release_screen();
     rest(REST_DUR);
}

void press_button(sprite *spr)
{
     if (spr->alive == 0)
          return;
      
     if (mb1_hold == 0)
          if (mx > spr->x   &&   mx < spr->x+spr->width   &&   my > spr->y   &&   my < spr->y+spr->height)
          {
               mouse_over = 1;
               cur_button = n;
          }
     if (cur_button == n && mb1_hold == 0)
          if (mx < spr->x   ||   mx > spr->x+spr->width   ||   my < spr->y   ||   my > spr->y+spr->height)
               mouse_over = 0;
       
     if (counter == 0 && mb1 && mb1_hold == 0)
          if (mx > spr->x   &&   mx < spr->x+spr->width   &&   my > spr->y   &&   my < spr->y+spr->height)
          {
               mouse_over = 0;
               curnb = n;
               mb1_hold = 1;
               nameN = spr->name;
               if (spr->name == "Button")
                    spr->curframe = 1;
               if (spr->name == "Arrow")
                    spr->totalframes = 1;
          }
}

void release_button(sprite *spr)
{
          if (!mb1 && inside == 1)
          {
                    choice_menu = spr->text;
                    allow_edit = 1;
                    
                    if (spr->name == "Button")
                    {
                         if (choice_menu == "Back" || choice_menu == "Exit Game" || choice_menu == "Sure?")
                              play_sample(snd_button_back, 255, 128, 1000, FALSE);
                         else
                              play_sample(snd_button_click, 255, 128, 1000, FALSE);
                    }
                    if (spr->name == "Arrow" && spr->curframe == 2)
                         play_sample(snd_button_less, 255, 128, 1000, FALSE);
                    if (spr->name == "Arrow" && spr->curframe == 3)
                         play_sample(snd_button_more, 255, 128, 1000, FALSE);
          }
          if (!mb1)
          {
               inside = 0;
               mb1_hold = 0;
               if (spr->name == "Button")
                    spr->curframe = 0;
               if (spr->name == "Arrow")
                    spr->totalframes = 0;
          }

          if (mb1_hold == 1)
          {
               if (mx > spr->x   ||   mx < spr->x+spr->width   ||   my > spr->y   ||   my < spr->y+spr->height)
               {
                    inside = 1;
                    if (spr->name == "Button")
                         spr->curframe = 1;
                    if (spr->name == "Arrow")
                         spr->totalframes = 1;
               }
               if (mx < spr->x   ||   mx > spr->x+spr->width   ||   my < spr->y   ||   my > spr->y+spr->height)
               {
                    inside = 0;
                    if (spr->name == "Button")
                         spr->curframe = 0;
                    if (spr->name == "Arrow")
                         spr->totalframes = 0;
               }
          }
}

void draw_bar(BITMAP *dest, unsigned char bar, float fill)
{
     draw_sprite(buffer, spr_bar, buttons->get(bar)->x+40, buttons->get(bar)->y);
     
     int c_color;
     if (fill <= 50)
          c_color = makecol(255, 0, 0);
     if (fill > 50 && fill <= 100)
          c_color = makecol(200, 50, 0);
     if (fill > 100 && fill <= 150)
          c_color = makecol(100, 100, 0);
     if (fill > 150 && fill <= 200)
          c_color = makecol(50, 200, 0);
     if (fill > 200 && fill <= 255)
          c_color = makecol(0, 255, 0);

     if (fill != 0)
     {
          fill = fill/1.7;
          unsigned char intfill = (unsigned char)fill;
          rectfill(dest, buttons->get(bar)->x+3+40, buttons->get(bar)->y+3, buttons->get(bar)->x+intfill+2+40, buttons->get(bar)->y+buttons->get(bar)->height-4, c_color);
     }
}

void erase_unit(sprite *spr)
{
     move = 0;
     selected = 0;
     counter = 0;
     fight = 0;
     spr->alive = 0;
     spr->select = 0;
     spr->vely = 0;
     spr->velx = 0;
     spr->select = 0;
}

void keyboard_registering()
{
     //A simple code allow the which allows keyboard buttons only to activate their command upon pressing the button 
     if (counter == 0)
     {
          if (keyboard_is_pressed == 0)
               if (keypressed())
               {
                    keyboard_is_pressed = 1;
                    keyboard_pressed = 1;
               }
          if (keyboard_is_pressed == 1)
               if (!key[KEY_ESC] && !key[KEY_DEL])
               {
                    keyboard_is_pressed = 0;
                    keyboard_pressed = 0;
               }
     }
}

void timer()
{
     if (choice_menu != "Paused")
     {
          song_length--;
          song_length_sec--;
     }

     //Init clock when counter is not zero, every sec the counter decreases with one until zero
     if (counter != 0)
     {
          counter--;
          
          if (gamestop == 1 && counter == 0)
               gamestop = 2;
          
          if (starttext == 1 && counter == 0)
          {
               starttext = 2;
               play_sample(snd_game_started, 255, 128, 1000, FALSE);
          }
          if (starttext == 1 && counter != 4)
               play_sample(snd_game_countdown, 255, 128, 1000, FALSE);
          
          if (choice_menu == "Sure?" && counter == 0)
               choice_menu = "Game Ended";
          if (choice_menu == "Start Game" && counter == 0)
               choice_menu = "Game Started";
     }
}
END_OF_FUNCTION(timer)

#endif
