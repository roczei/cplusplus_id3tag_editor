/*
   main.cpp
   Feladata: ID3V1Tag editor megvalositasa ncurses feluleten 
   Keszitette: Roczei Gabor
   Utolso modositas: 2002. november 19.
*/

#include "CID3Tag.hpp"
#include "CID3Ablak.hpp"
#include <iostream>

int
main( int argc, char *argv[] )
{
      int chBetu; // egy betu tarolasara alkalmas valtozo
      int nAktualis = 1; // ez tarolja, hogy melyik az aktualis menupont
      char chKilep = 'n'; // kilepes eseten 'i' az erteke
      if ( argc < 2 || argc > 2 ) // arra az esetre, ha rossz parameter lett megadva
      {
          std::cout << std::endl << "A program hasznalata:" << std::endl << std::endl;
	  std::cout << argv[0] << " Fajl.mp3" << std::endl << std::endl;
	  exit(1);
      }
      CID3Tag mp3szam(argv[1]);
      initscr(); // ncurses felulet inditasa
      clear(); // hatter torlese (clrscr)
      CID3Ablak ablak( 20, 60, 4, 5 ); // ablak keszites a megadott meret szerint
      mvwprintw( ablak.AblakMutato(), 2, 17, argv[1] );
      keypad( ablak.AblakMutato(), TRUE ); // engedelyezem az osszes letezo gombot a billetyuzeten     
      noecho(); // kikapcsolom a kiirast a kepernyore
      mp3szam.MenuKezelo( ablak, nAktualis ); 
      do
      {
          chBetu = wgetch(ablak.AblakMutato());
	  switch (chBetu) // megvizsgalja hogy melyik gomb lett megnyomva a billentyun
	  { 
              case KEY_UP: // felfele leptetes eseten
	         if ( nAktualis == 1 ) 
		      nAktualis = 7;
		 else
	 	      nAktualis--;
		 break;
              case KEY_DOWN: // lefele leptetes eseten
	         if ( nAktualis == 7 )
		      nAktualis = 1;
		 else
		      nAktualis++;
		 break;
              case 10:  // az Enter gomb megnyomasa eseten
	         switch (nAktualis)
                 {
                     case 1:
		         mp3szam.Atir( ablak, 'c' ); // cim menupont
			 break;
		     case 2:
		         mp3szam.Atir( ablak, 'e' ); // eloado menupont
			 break;
                     case 3:
		         mp3szam.Atir( ablak, 'a' ); // album menupont
			 break;
		     case 4:
		         mp3szam.Atir( ablak, 'v' ); // kiadas eve menupont
			 break;
	             case 5:			 
		         mp3szam.Atir( ablak, 'g'); // megjegyzes menupont
			 break;
	             case 6:
                         mp3szam.Atir( ablak, 'm' ); // mufaj menupont
			 break;
	             case 7:
		         chKilep = 'i'; // OK menupont
			 break;
	         }		     
		 break;
          }
	  mp3szam.MenuKezelo( ablak, nAktualis );
      } while( chKilep == 'n' );      
      endwin(); // ncurses felulet kikapcsolasa
      return 0;
}
