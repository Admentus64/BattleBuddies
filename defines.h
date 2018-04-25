#ifndef DEFINES_H
#define DEFINES_H

////////////////////////
// Define *dat files ///
////////////////////////

//Define core.dat image files
#define bg                                      img_core[0]             /* BMP  */
#define cursor1                                 img_core[1]             /* BMP  */
#define cursor2                                 img_core[2]             /* BMP  */
#define cursor3                                 img_core[3]             /* BMP  */
#define grid                                    img_core[4]             /* BMP  */
#define spr_pause                               img_core[5]             /* BMP  */
#define hud                                     img_core[6]             /* BMP  */

//Define setting.dat image files
#define spr_bar                                 img_setting[0]          /* BMP  */
#define spr_off                                 img_setting[1]          /* BMP  */
#define spr_on                                  img_setting[2]          /* BMP  */

//Define button.dat sound files
#define snd_button_back                         snd_button[0]            /* SAMP */
#define snd_button_click                        snd_button[1]            /* SAMP */
#define snd_button_gamestart                    snd_button[2]            /* SAMP */
#define snd_button_less                         snd_button[3]            /* SAMP */
#define snd_button_more                         snd_button[4]            /* SAMP */

//Define fight.dat sound files
#define snd_bullet_shot                         snd_fight[0]             /* SAMP */
#define snd_fight_draw                          snd_fight[1]             /* SAMP */
#define snd_fight_lose                          snd_fight[2]             /* SAMP */
#define snd_fight_win                           snd_fight[3]             /* SAMP */

//Define game.dat sound files
#define snd_game_countdown                      snd_game[0]              /* SAMP */
#define snd_game_lose                           snd_game[1]              /* SAMP */
#define snd_game_paused                         snd_game[2]              /* SAMP */
#define snd_game_resign                         snd_game[3]              /* SAMP */
#define snd_game_started                        snd_game[4]              /* SAMP */
#define snd_game_win                            snd_game[5]              /* SAMP */
#define snd_move_error                          snd_game[6]              /* SAMP */

//Define menu.dat music files
#define mid_credits                             mid_menu[0]              /* MIDI */
#define mid_help                                mid_menu[1]              /* MIDI */
#define mid_highscore                           mid_menu[2]              /* MIDI */
#define mid_main                                mid_menu[3]              /* MIDI */
#define mid_settings                            mid_menu[4]              /* MIDI */

//Define aftermatch.dat music files
#define mid_aftermatch_equal                    mid_aftermatch[0]        /* MIDI */
#define mid_aftermatch_lose                     mid_aftermatch[1]        /* MIDI */
#define mid_aftermatch_not_started              mid_aftermatch[2]        /* MIDI */
#define mid_aftermatch_win                      mid_aftermatch[3]        /* MIDI */
//Define fonts.dat font files
#define f_button                                fonts[0]                 /* FONT */
#define f_credits                               fonts[1]                 /* FONT */
#define f_guide                                 fonts[2]                 /* FONT */
#define f_hud                                   fonts[3]                 /* FONT */
#define f_paused                                fonts[4]                 /* FONT */
#define f_starttext                             fonts[5]                 /* FONT */

//Define respective unit.dat sounds files
#define snd_unit_move                           spr->sound[0]            /* SAMP */
#define snd_unit_select                         spr->sound[1]            /* SAMP */

//Define non-data
#define bullet                                  units->get(40)
#define music_aftermatch                        6
#define music_menu                              7
#define music_preparation                       8
#define music_main                              9
#define image_guide                             2
#define explosion                               nonunits->get(0)
#define pointer                                 nonunits->get(0)

#endif
