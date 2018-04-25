#ifndef EXITPROGRAM_H
#define EXITPROGRAM_H

///////////////////////////////////////////////////
/// Function to prepare for exiting the program ///
///////////////////////////////////////////////////
void endgame()
{
     //Remove mouse and buffer
     set_mouse_sprite(NULL);
	 destroy_bitmap(buffer);
     
     //Functions to remove all menu resources
     delete buttons;
     
     //Remove *dat files
     for (unsigned char i=0; i<DATA_SIZE; i++)
          if (i!=2 && i!=6 && i!=8 && i!=9)
               unload_datafile(datafiles[i]);
	  
	 //Shutdown
	 allegro_exit();
}

////////////////////////////////////////////////////////////////////
/// Function to delete units when exiting match, but not program ///
////////////////////////////////////////////////////////////////////
void erase_sprites()
{
     //Remove unit sprite objects
	 delete buttons;
	 delete bg_mains;
	 delete units;
	 
	 if (restart == 0)
          delete nonunits;
}

#endif
