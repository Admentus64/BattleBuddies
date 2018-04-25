#ifndef ADDSPRITES_H
#define ADDSPRITES_H

////////////////////////////////////////////////////
/// Function to add sprites to the spritehandler ///
////////////////////////////////////////////////////
void init_sprites()
{
     //create the sprite handlers	
	 buttons = new spritehandler();
	 bg_mains = new spritehandler();
	 units = new spritehandler();
     
     //Add sprites to the sprite handler
     for (n=0; n<NUM_B; n++) //create the button sprites
     {
          button = new sprite();
          button->load_data_img("data/buttons/images - button.dat", 1);
          button->load_data_style("data/buttons/fonts - button.dat", 1);
          button->name = "Button";
          button->width = 128; button->height = 32;
          button->alive = 1;
          buttons->add(button); //Add 1 button to the spritehandler
     } //End of button sprites
     
     buttons->get(0)->text = "Restart";
     buttons->get(1)->text = "Next Song";
     buttons->get(2)->text = "Background";
     buttons->get(3)->text = "Resign";
     
     buttons->get(4)->text = "Chopper";
     buttons->get(5)->text = "Light Tank";
     buttons->get(6)->text = "MEC";
     buttons->get(7)->text = "Odin";
     buttons->get(8)->text = "F9 Fighter";

     
     //Before creating the bg_main sprites, the bg scenery is decided and the number of debris (number 1 is the main bg, higher numbers are debris)
     bg_scenery = rand()%3;
     if (last_bg_scenery == bg_scenery)
     {
          while (last_bg_scenery == bg_scenery)
               bg_scenery = rand()%3;
     }
     last_bg_scenery = bg_scenery;
     NUM_BG = rand()%21+1;

	 for (n=0; n<NUM_BG; n++) //create the bg_main sprites
     {
          bg_main = new sprite();
          if (bg_scenery == 0)
          {
               bg_main->load_data_img("data/backgrounds/images - grass.dat", 1);
               bg_main->name = "BG";
               bg_main->totalframes = 7;
          }
          if (bg_scenery == 1)
          {
               bg_main->load_data_img("data/backgrounds/images - sand.dat", 1);
               bg_main->name = "BG";
               bg_main->totalframes = 6;
          }
          if (bg_scenery == 2)
          {
               bg_main->load_data_img("data/backgrounds/images - snow.dat", 1);
               bg_main->name = "BG";
               bg_main->totalframes = 6;
          }
          bg_main->width = 40; bg_main->height = 40;
          bg_mains->add(bg_main); //Add 1 bg_main to the spritehandler
     } //End of bg_main sprites
     
     if (restart == 0)
     {
          nonunits = new spritehandler();
          nonunit = new sprite(); //Add pointer
          nonunit->load_data_img("data/misc/images - pointer.dat", 1);
          nonunit->width = 32; nonunit->height = 32;
          nonunit->alive = 1;
          nonunit->x = coord_x[1]+4;
          nonunit->y = coord_y[2]-30; nonunit->y1 = nonunit->y-10; nonunit->y2 = nonunit->y+10;
          nonunit->ydelay = 10; nonunit->vely = 1;
          nonunits->add(nonunit);
     }
     if (restart == 1)
     {
          nonunit->x = coord_x[1]+4;
          nonunit->y = coord_y[2]-30;
          nonunit->y1 = nonunit->y-10;
          nonunit->y2 = nonunit->y+10;
          nonunit->curframe = 0;
     }
}

#endif
