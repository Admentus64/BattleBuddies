#ifndef GAMERESOLUTION_H
#define GAMERESOLUTION_H

void loop_outcome()
{
     unsigned char written_score = 0;
     
     datafiles[music_aftermatch] = load_datafile("data/music/aftermatch.dat");
     for (unsigned char j=0; j<MID_AFTERMATCH_SIZE; j++)
          mid_aftermatch[j] = (MIDI *)datafiles[music_aftermatch][j].dat;
     if (starttext != 0 && resign == 0 && game_outcome != 3)
     {
          play_midi(mid_aftermatch_win, 1);
          unload_datafile(datafiles[music_main]);
     }
     if (starttext != 0 && resign == 0 && game_outcome == 3)
     {
          play_midi(mid_aftermatch_equal, 1);
          unload_datafile(datafiles[music_main]);
     }
     if (starttext != 0 && resign != 0)
     {
          play_midi(mid_aftermatch_lose, 1);
          unload_datafile(datafiles[music_main]);
     }
     if (starttext == 0)
     {
          play_midi(mid_aftermatch_not_started, 1);
          unload_datafile(datafiles[music_preparation]);
     }
     
     buttons->get(0)->x = O_WIDTH/2-buttons->get(0)->width/2;
     buttons->get(0)->y = O_HEIGHT-100;
     buttons->get(0)->alive = 1;
     buttons->get(0)->text = "Continue";
     
     while (choice_menu != "Continue")
     {
          //Grab the current mouse values
          mx = mouse_x; my = mouse_y; mb1 = (mouse_b & 1); mb2 = (mouse_b & 2);
          
          draw_sprite(buffer, bg, 0, 0); //Redraws the background
          
          if (game_outcome != 0 && resign == 0 && game_outcome < 3) //When a player wins the match
          {
               textprintf_centre_ex(buffer, f_starttext, O_WIDTH/2, O_HEIGHT/2-100, C_WHITE ,-1, "Congratulations");
               if (game_outcome == 1)
                    textprintf_centre_ex(buffer, f_starttext, O_WIDTH/2, O_HEIGHT/2-60, C_WHITE ,-1, "%s won the match", PLAYER_NAME1.c_str());
               if (game_outcome == 2)
                    textprintf_centre_ex(buffer, f_starttext, O_WIDTH/2, O_HEIGHT/2-60, C_WHITE ,-1, "%s won the match", PLAYER_NAME2.c_str());
               
               //If an players wins, their score will be written into the highscore list if it makes the top 5
               if (written_score == 0)
               {
                    //The score of this match is added
                    temp_score.points = round;
                    if (game_outcome == 1)
                         temp_score.player = PLAYER_NAME1.c_str();
                    if (game_outcome == 2)
                         temp_score.player = PLAYER_NAME2.c_str();
                    highscore.push_back(temp_score);
                    //Scores are sorted, currently there are 6 score, 1 needs to be removed from the vector
                    sort_highscore(highscore);
                    ofstream utfil;
                    utfil.open("data/highscore.ini");
                    //Only the first 5 scores from the vector are written into the highscore list (they were sorted, remember?)
                    for (unsigned char i=0; i<5; i++)
                    {
                         utfil<<highscore.at(i).points<<endl;
                         utfil<<highscore.at(i).player.c_str()<<endl;
                    }
                    utfil.close();
                    //The score vector is made empty
                    highscore.clear();
                    //The score vector is refilling itself again, based on the highscore.ini file which has only 5 scores
                    reading_highscore_file();
                    written_score = 1;
               }
          }
          if (game_outcome == 3 && resign == 0)
          {
               textprintf_centre_ex(buffer, f_starttext, O_WIDTH/2, O_HEIGHT/2-100, C_WHITE ,-1, "Wow... How did you do it...?");
               textprintf_centre_ex(buffer, f_starttext, O_WIDTH/2, O_HEIGHT/2-60, C_WHITE ,-1, "Both of you lost at the same time");
               textprintf_centre_ex(buffer, f_starttext, O_WIDTH/2, O_HEIGHT/2+20, C_WHITE ,-1, "%s", PLAYER_NAME1.c_str());
               textprintf_centre_ex(buffer, f_starttext, O_WIDTH/2, O_HEIGHT/2+60, C_WHITE ,-1, "%s", PLAYER_NAME2.c_str());
          }
          
          if (resign != 0) //When someone did resign the match
          {
               textprintf_centre_ex(buffer, f_starttext, O_WIDTH/2, O_HEIGHT/2-100, C_WHITE ,-1, "Alas, none did win the match");
               if (game_outcome == 1)
                    textprintf_centre_ex(buffer, f_starttext, O_WIDTH/2, O_HEIGHT/2-60, C_WHITE ,-1, "%s resigned the match", PLAYER_NAME1.c_str());
               if (game_outcome == 2)
                    textprintf_centre_ex(buffer, f_starttext, O_WIDTH/2, O_HEIGHT/2-60, C_WHITE ,-1, "%s resigned the match", PLAYER_NAME2.c_str());
          }
          if (starttext == 0) //When someone did resign the matched while not started
          {
               textprintf_centre_ex(buffer, f_starttext, O_WIDTH/2, O_HEIGHT/2+20, C_WHITE ,-1, "Besides...");
               textprintf_centre_ex(buffer, f_starttext, O_WIDTH/2, O_HEIGHT/2+60, C_WHITE ,-1, "The match didn't start yet...");
          }
           
          for (n=0; n<NUM_MENU_B; n++)
          {
               buttons->get(n)->drawframe(buffer);
               press_button(buttons->get(n));
               if (mb1_hold == 1)
                    release_button(buttons->get(curnb));
          }
          
          if (key[KEY_ESC])
               choice_menu = "Continue";
          
          update_screen();
     }
     datafiles[music_menu] = load_datafile("data/music/menu.dat");
     for (unsigned char j=0; j<MID_MENU_SIZE; j++)
          mid_menu[j] = (MIDI *)datafiles[music_menu][j].dat;         
     play_midi(mid_main, 1); //Start menu theme
     unload_datafile(datafiles[music_aftermatch]);
}

#endif
