/*
    CID3Ablak.hpp
    Keszitette: Roczei Gabor
    Datum: 2002. november 19.
*/

#ifndef __ID3ABLAK__
   #define __ID3ABLAK__
   #include "CID3Tag.hpp"
   #include <ncurses.h>

   class CID3Ablak
   {
      private:
           WINDOW *m_ID3Ablak;  // az ablak megjelenitesehez szukseges mutato
           int m_nKezdoSor;  // azt tarolja, hogy hanyadik sortol kezdodik az ablak
           int m_nKezdoOszlop; // azt tarolja, hogy hanyadik oszloptol kezdodik az ablak
           int m_nSorokSzama; // azt tarolja, hogy hany sorbol all az ablak
           int m_nOszlopokSzama; // azt tarolja, hogy hany oszlopbol all az ablak
      public:
           CID3Ablak( int nSSzama, int nOSzama, int nKSor, int nKOszlop); // konstruktor
           ~CID3Ablak(); // destruktor
           WINDOW* AblakMutato(void) { return m_ID3Ablak; };
	   CID3Ablak& operator=( const CID3Ablak& );
	   CID3Ablak( const CID3Ablak& );
   };
#endif
