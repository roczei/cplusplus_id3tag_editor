/*
   CID3Ablak.cpp
   Feladata: CID3Ablak osztaly implementacioja
   Keszitette: Roczei Gabor
   Utolso modositas: 2002. november 19.
*/

#include "CID3Tag.hpp"
#include <iostream>

/*
    Feladata: CID3Ablak osztaly konstruktora, az inicializalast vegzi
    Hasznalatanak elofeltetelei: ncurses.h header fajl includalasa
    Bemenoparameterek: int nSSzama, int nOSzama, int nKSor, int nKOszlop
    Kimenoparameterek: a CID3Ablak oszaly adattagjai, ezek kapnak erteket
    Egyeb parameterek: -
    Hivatkozott globalis valtozok: -
    Hivott fuggvenyek: -
    Keszito: Roczei Gabor
    Utolso modositas: 2002. november 20.
*/

CID3Ablak :: CID3Ablak( int nSSzama, int nOSzama, int nKSor, int nKOszlop )
{
     char *pFejlec = " ID3Tag editor ";
     start_color(); // szinek aktivalasa
     init_pair( 1, COLOR_WHITE, COLOR_RED ); // uj szinpar
     init_pair( 2, COLOR_YELLOW, COLOR_RED ); // uj szinpar
     init_pair( 3, COLOR_GREEN, COLOR_RED ); // uj szinpar
     init_pair( 4, COLOR_WHITE, COLOR_GREEN ); // szinpar
     m_ID3Ablak = newwin( nSSzama, nOSzama, nKSor, nKOszlop ); // ablak letrehozasa
     wattron( m_ID3Ablak, COLOR_PAIR(1) );
     int i, j;
     for ( i = 0; i < nSSzama; i++ )
         for ( j = 0; j < nOSzama; j++ )
         mvwprintw( m_ID3Ablak, i, j, " " );    
     wborder( m_ID3Ablak, 0, 0, 0, 0, 0, 0, 0, 0 ); // keret elkeszitese
     wattron( m_ID3Ablak, COLOR_PAIR(3) | A_BOLD );
     mvwprintw( m_ID3Ablak, 0, ( nOSzama - strlen(pFejlec) ) / 2, pFejlec ); // fejlec kiirasa
     wattron( m_ID3Ablak, COLOR_PAIR(2) | A_LEFT );
     mvwprintw( m_ID3Ablak, 2, 6, "Fajl neve:" );
     mvwprintw( m_ID3Ablak, 5, 12, "Cim:" );
     mvwprintw( m_ID3Ablak, 7, 9, "Eloado:" );
     mvwprintw( m_ID3Ablak, 9, 10, "Album:" );
     mvwprintw( m_ID3Ablak, 11, 5, "Kiadas eve:" );
     mvwprintw( m_ID3Ablak, 13, 5, "Megjegyzes:" );
     mvwprintw( m_ID3Ablak, 15, 10, "Mufaj:" );
     wattron( m_ID3Ablak, COLOR_PAIR(1) | A_BOLD );
     wrefresh(m_ID3Ablak); // ablak frissitese
     m_nKezdoSor = nKSor;
     m_nKezdoOszlop = nKOszlop;
     m_nSorokSzama = nSSzama;
     m_nOszlopokSzama = nOSzama;
}

/*
    Feladata: CID3Ablak oszalyban levo m_ID3Ablak altal foglalt
              memoriaresz felszabaditasa
    Hasznalatanak elofeltetelei: -
    Bemenoparameterek: -
    Kimenoparameterek: -
    Egyeb parameterek: -
    Hivatkozott globalis valtozok: -
    Hivott fuggvenyek: -
    Keszito: Roczei Gabor
    Utolso modositas: 2002. november 20.
*/

CID3Ablak :: ~CID3Ablak()
{
     delwin(m_ID3Ablak); // ablak torlese a memoriabol
}

/*
    Feladata: CID3Ablak osztaly copy konstruktora
    Hasznalatanak elofeltetelei: -
    Bemenoparameterek: CID3Ablak tipusu A objektum
    Kimenoparameterek: Inicializal egy objektumot    
    Egyeb parameterek: -
    Hivatkozott globalis valtozok: -
    Hivott fuggvenyek: -
    Keszito: Roczei Gabor
    Utolso modositas: 2002. november 20.
*/

CID3Ablak :: CID3Ablak( const CID3Ablak& A ) // copy konstruktor
{
     m_ID3Ablak = A.m_ID3Ablak; 
     m_nKezdoSor = A.m_nKezdoSor;
     m_nKezdoOszlop = A.m_nKezdoOszlop;
     m_nSorokSzama = A.m_nSorokSzama;
     m_nOszlopokSzama = A.m_nOszlopokSzama;
}  

/*
    Feladata: CID3Ablak ertekadas operator
    Hasznalatanak elofeltetelei: Ket darab CID3Ablak tipusu objektumra
          van szuksege
    Bemenoparameterek: CID3Ablak tipusu A objektum
    Kimenoparameterek: Az egyenloseg operator bal oldalon levo objektum
          adattagjai felveszik a jobboldali objektum adattagjainak 
	  az erteket
    Egyeb parameterek: -
    Hivatkozott globalis valtozok: -
    Hivott fuggvenyek: -
    Keszito: Roczei Gabor
    Utolso modositas: 2002. november 20.
*/

CID3Ablak& CID3Ablak :: operator=( const CID3Ablak& A ) // ertekado operator
{
     if ( this != &A ) // arra az esetre ha a ketto megegyezik
     {
         m_ID3Ablak = A.m_ID3Ablak;
         m_nKezdoSor = A.m_nKezdoSor;
         m_nKezdoOszlop = A.m_nKezdoOszlop;
         m_nSorokSzama = A.m_nSorokSzama;
         m_nOszlopokSzama = A.m_nOszlopokSzama;
     }
     return *this;
}  
