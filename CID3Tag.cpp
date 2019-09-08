/* 
    CID3Tag.cpp
    Feladata: CID3Tag osztaly implementacioja
    Keszitette: Roczei Gabor
    Utolso modositas: 2002. november 17.
*/

#include "CID3Tag.hpp"
#include "CID3Tag_mufaj.hpp"
#include <iostream>
#include <stdlib.h>

/*
    Feladata: CID3Tag osztaly konstruktora
    Hasznalatanak elofeltetelei: Szukseg van egy mp3 fajlra
    Bemeno parameterek: char tipusu pMP3FajlNeve
    Kimeno parameterek: Inicializalja az adattagokat
    Egyeb parameterek: -
    Hivatkozott globalis valtozok: -
    Hivott fuggvenyek: -
    Keszito: Roczei Gabor
    Utolso modositas: 2002. november 20.
*/

CID3Tag :: CID3Tag( char *pMP3FajlNeve )
{
     int i;
     char pTag[3]; // annak az ellenorzesere, hogy tartalmaz e TAG-ot
     m_MP3Fajl.open( pMP3FajlNeve, std::ios::in | std::ios::out | std::ios::binary );
     if ( !m_MP3Fajl.good() ) // hiba eseten
     {
         std::cerr << "Nem sikerult megnyitni: " << pMP3FajlNeve << std::endl;
	 exit (-1);
     }     
     m_MP3Fajl.seekg( -128, std::ios :: end );
     m_pFajlNev = new char[ strlen(pMP3FajlNeve) + 1 ];
     strcpy( m_pFajlNev, pMP3FajlNeve );
     if ( ( m_pCim = new char[31] ) == NULL )
     {  
        std::cerr << "Nincs eleg memoria!" << std::endl;
	exit(-1);
     }     

     if ( ( m_pEloado = new char[31] ) == NULL )
     {  
        std::cerr << "Nincs eleg memoria!" << std::endl;
	exit(-1);
     }
          
     if ( ( m_pAlbum = new char[31] ) == NULL )
     {  
        std::cerr << "Nincs eleg memoria!" << std::endl;
	exit(-1);
     }
          
     if ( ( m_pMegjegyzes = new char[31] ) == NULL )
     {  
        std::cerr << "Nincs eleg memoria!" << std::endl;
	exit(-1);
     }     
     
     if ( ( m_pModositandok = new char[7] ) == NULL )
     {  
        std::cerr << "Nincs eleg memoria!" << std::endl;
	exit(-1);
     }

     if ( ( m_pMufaj = new char[2] ) == NULL )
     {
        std::cerr << "Nincs eleg memoria!" << std::endl;
	exit(-1);
     }

     if ( ( m_pEv = new char[5] ) == NULL )
     {
         std::cerr << "Nincs eleg memoria!" << std::endl;
         exit(-1);
     }

     for ( i = 0; i < 3; i++ ) 
         m_MP3Fajl.get(pTag[i]);
     if ( pTag[0] != 'T' && pTag[1] != 'A' && pTag[2] != 'G' )
     {   // arra az esetre, ha nem tartalmazt TAG-ot
         m_chTAG = 'n';
         for ( i = 0; i < 31; i++ ) 
             m_pCim[i] = '\0';
         for ( i = 0; i < 31; i++ ) 
	     m_pEloado[i] = '\0';
         for ( i = 0; i < 31; i++ )
             m_pAlbum[i] = '\0';
         strcpy( m_pEv, "1900" );
         for ( i = 0; i < 31; i++ )
             m_pMegjegyzes[i] = '\0';
         m_pMufaj[0] = 255;
	 m_pMufaj[1] = '\0';
	 strcpy( m_pModositandok, "ceavmg" );	 
     }
     else
     { // arra az esetre, ha mar van TAG az mp3 szamban
         m_chTAG = 'i';
         for ( i = 0; i < 30; i++ )
             m_MP3Fajl.get(m_pCim[i]); // cim beolvasasa
         m_pCim[30] = '\0';
         for ( i = 0; i < 30; i++ )
    	     m_MP3Fajl.get(m_pEloado[i]); // eloado beolvasasa
         m_pEloado[30] = '\0';
         for ( i = 0; i < 30; i++ )
             m_MP3Fajl.get(m_pAlbum[i]); // album beolvasasa
         m_pAlbum[30] = '\0';
         for ( i = 0; i < 4; i++ )
             m_MP3Fajl.get(m_pEv[i]); // ev beolvasasa
         m_pEv[4] = '\0';
         for ( i = 0; i < 30; i++ )
             m_MP3Fajl.get(m_pMegjegyzes[i]); // megjegyzes beolvasasa
         m_pMegjegyzes[30] = '\0';
         char chKarakter;
	 m_MP3Fajl.get(chKarakter);
	 m_pMufaj[0] = chKarakter;
	 m_pMufaj[1] = '\0';
         for ( i = 0; i < 7; i++ )
	     m_pModositandok[i] = '\0';	
    }
    m_MP3Fajl.seekg( 0, std::ios :: end );
}

/*
    Feladata: CID3Tag destruktora
    Hasznalatanak elofeltetelei: mp3szam legyen megnyitva
    Bemeno parameterek: -
    Kimeno parameterek: -
    Egyeb parameterek: -
    Hivatkozott globalis valtozok: -
    Hivott fuggvenyek: ID3Tag :: Modosit fuggvenyt hivja meg
    Keszito: Roczei Gabor
    Utolso modositas: 2002. november 20.
*/

CID3Tag :: ~CID3Tag()
{
    int i;
    if ( m_chTAG == 'n' ) // abban az esetben, ha TAG-ot meg nem tartalmazott
    {
        m_MP3Fajl.seekg( 0 , std::ios :: end );
	m_MP3Fajl.put('T');
	m_MP3Fajl.put('A');
	m_MP3Fajl.put('G');
	for ( i = 0; i < 125; i++ )
	    m_MP3Fajl.put('\0');
    }
    for ( i = 0; i < 7; i++)
        Modosit(m_pModositandok[i]); // modositott TAG-ok kiirasa

    // dinamikusan lefoglalt memoria resz felszabaditasa
    delete [] m_pFajlNev; 
    delete [] m_pCim;
    delete [] m_pModositandok;
    delete [] m_pMegjegyzes;
    delete [] m_pAlbum;
    delete [] m_pEloado;
    delete [] m_pMufaj;
    delete [] m_pEv;
    m_MP3Fajl.close();
}

/*
    Feladata: Az mp3szam tagjainak a modositasat vegzi el
    Hasznalatanak elofeltetelei: legyen megnyitva az mp3szam
    Bemeno parameterek: char chModositando karakter
    Kimeno parameterek: -
    Egyeb parameterek: -
    Hivatkozott globalis valtozok: -
    Hivott fuggvenyek: -
    Keszito: Roczei Gabor
    Utolso modositas: 2002. november 20.
*/

void CID3Tag :: Modosit( char chModositando )
{
    int i;
    m_MP3Fajl.seekg( -128, std::ios :: end );
    switch (chModositando)
    {
        case 'c':
	    m_MP3Fajl.seekg( 3, std::ios :: cur );
	    for ( i = 0; i < 30; i++ )
	        m_MP3Fajl.put(m_pCim[i]); // cim kiirasa
	    break;
	case 'e':
	    m_MP3Fajl.seekg( 33, std::ios :: cur );
	    for ( i = 0; i < 30; i++ )
	        m_MP3Fajl.put(m_pEloado[i]); // eloado kiirasa
	    break;
	case 'a':
            m_MP3Fajl.seekg( 63, std::ios :: cur );
            for ( i = 0; i < 30; i++ )
                 m_MP3Fajl.put(m_pAlbum[i]); // album kiirasa
	    break;
	case 'v':
            m_MP3Fajl.seekg( 93, std::ios :: cur );
            for ( i = 0; i < 4; i++ )
                m_MP3Fajl.put(m_pEv[i]); // ev kiirasa
            break;
        case 'g':
             m_MP3Fajl.seekg( 97, std::ios :: cur );
             for ( i = 0; i < 30; i++ )
                 m_MP3Fajl.put(m_pMegjegyzes[i]); // megjegyzes kiirasa
             break;
        case 'm':
	     m_MP3Fajl.seekg( -1, std::ios :: end );
	     m_MP3Fajl.put(m_pMufaj[0]); // mufaj kiirasa
	     break;
      } // switch vege
}

/*
    Feladata: Visszaadja a kivant tagot szoveg formaban
    Hasznalatanak elofeltetelei: legyen megnyitva az mp3szam
    Bemeno parameterek: char chKiolvasando
    Kimeno parameterek: A kivant tagra mutato pointer
    Egyeb parameterek: -
    Hivatkozott globalis valtozok: -
    Hivott fuggvenyek: -
    Keszito: Roczei Gabor
    Utolso modositas: 2002. november 20.
*/

char* CID3Tag :: Kiolvas(char chKiolvasando)
{
     switch (chKiolvasando)
     {
          case 'f':
	       return m_pFajlNev;
	  case 'c':
	       return m_pCim;
	  case 'e':
	       return m_pAlbum;
	  case 'a':
	       return m_pAlbum;
	  case 'v':
	       return m_pEv;
	  case 'm':
	       if ( m_pMufaj[0] > 125 )
	            return mufaj[126];
	       else
	            return mufaj[ m_pMufaj[0] ];
	  case 'g':
	       return m_pMegjegyzes;
    }
}

/*
    Feladata: A menukezelest vegzi el
    Hasznalatanak elofeltetelei: ncurses felulet
    Bemeno parameterek: CID3Ablak tipusu ablak obkektum, int tipusu
        nAktualis, ami azt mutatja, hogy hanyadik menupont aktiv
    Kimeno parameterek: -
    Egyeb parameterek: -
    Hivatkozott globalis valtozok: -
    Hivott fuggvenyek: ID3Ablak :: Kiir es ID3Ablak :: KiirAkt
    Keszito: Roczei Gabor
    Utolso modositas: 2002. november 20.
*/

void CID3Tag :: MenuKezelo( CID3Ablak& ablak, int& nAktualis )
{
    int x, y;
    x = 17;
    y = 5;

    // menupontok szinezese

    wattron( ablak.AblakMutato(), COLOR_PAIR(1) | A_BOLD );
    if ( nAktualis == 1 )
    {
        wattron( ablak.AblakMutato(), A_REVERSE);	       
        mvwprintw( ablak.AblakMutato(), y, x, m_pCim );
        wattroff( ablak.AblakMutato(), A_REVERSE );
    }
    else
        mvwprintw( ablak.AblakMutato(), y, x, m_pCim );
    wrefresh( ablak.AblakMutato() );	
    y += 2; 
    if ( nAktualis == 2 )
    {
        wattron( ablak.AblakMutato(), A_REVERSE );	       
        mvwprintw( ablak.AblakMutato(), y, x, m_pEloado );
        wattroff( ablak.AblakMutato(), A_REVERSE );
    }
    else
        mvwprintw( ablak.AblakMutato(), y, x, m_pEloado );
    y += 2; 
    if ( nAktualis == 3 )
    {
        wattron( ablak.AblakMutato(), A_REVERSE );	       
        mvwprintw( ablak.AblakMutato(), y, x, m_pAlbum );
        wattroff( ablak.AblakMutato(), A_REVERSE );
    }
    else
        mvwprintw( ablak.AblakMutato(), y, x, m_pAlbum );
    y += 2; 
    if ( nAktualis == 4 )
    {
        wattron( ablak.AblakMutato(), A_REVERSE );	       
        mvwprintw( ablak.AblakMutato(), y, x, m_pEv );
        wattroff( ablak.AblakMutato(), A_REVERSE );
    }
    else
        mvwprintw( ablak.AblakMutato(), y, x, m_pEv );
    y += 2;
    if ( nAktualis == 5 )
    {
        wattron( ablak.AblakMutato(), A_REVERSE );	       
        mvwprintw( ablak.AblakMutato(), y, x, m_pMegjegyzes );
        wattroff( ablak.AblakMutato(), A_REVERSE );
    }
    else
        mvwprintw( ablak.AblakMutato(), y, x, m_pMegjegyzes );
    y += 2; 
    if ( nAktualis == 6 )
    {
        wattron( ablak.AblakMutato(), A_REVERSE );	       
	mvwprintw( ablak.AblakMutato(), y, x, Kiolvas('m') );
        wattroff( ablak.AblakMutato(), A_REVERSE );
    }
    else
        mvwprintw( ablak.AblakMutato(), y, x, Kiolvas('m') );
    y += 2;
    if ( nAktualis == 7 )
    {
       wattron( ablak.AblakMutato(), A_REVERSE );
       mvwprintw( ablak.AblakMutato(), y, x, "  OK  " );
       wattroff( ablak.AblakMutato(), A_REVERSE );
    }
    else
       mvwprintw( ablak.AblakMutato(), y, x, "  OK  " );
    wrefresh(ablak.AblakMutato()); // ncurses felulet frissitese
}

/*
    Feladata: A megfelelo mezo atirasat segiti
    Hasznalatanak elofeltetelei: legyen megnyitva egy mp3szam, ncurses
          felulet szukseges hozza
    Bemeno parameterek: CID3Ablak tipusu ablak objektum es char tipusu
          chAtirando, ami azt tarolja, hogy melyik mezot modositsuk
    Kimeno parameterek: -
    Egyeb parameterek: -
    Hivatkozott globalis valtozok: -
    Hivott fuggvenyek: ID3Ablak :: Kiir
    Keszito: Roczei Gabor
    Utolso modositas: 2002. november 20.
*/

void CID3Tag :: Atir( CID3Ablak& ablak, char chAtirando )
{
    int i, x, y, nHelyx, nHelyy;
    char chBetu;
    char *pTarolo;
    int nSzam;
    x = 17;
    y = 5;
    if ( ( pTarolo = new char[5] ) == NULL )
    {
         std::cout << "Nincs eleg memoria!" << std::endl;
	 exit(-1);
    }
    switch (chAtirando)
    {
       case 'c':
	  y += 0;
	  break;
       case 'e':
	  y += 2;
	  break;
       case 'a':
	  y += 4;
	  break;
       case 'v':
          y += 6;
	  break;
       case 'g':
	  y += 8;
	  break;
       case 'm':
          y += 10;
	  break;
    }
    echo();
    wattron( ablak.AblakMutato(), COLOR_PAIR(4) );
    if ( chAtirando == 'm' ) // mufaj mezo hatter szinezese (frissitese)
    {
        wattron( ablak.AblakMutato(), COLOR_PAIR(1) );
	for ( i = 0; i < 30; i++ )
	    mvwprintw( ablak.AblakMutato(), y, x + i , " " );
	wattron( ablak.AblakMutato(), COLOR_PAIR(4) );
        for ( i = 0; i < 3; i++ )
        mvwprintw( ablak.AblakMutato(), y, x + i, " " );
    }
    else // a tobbi mezo szinezese
        for ( i = 0; i < ( chAtirando == 'v'  ? 4 : 30 ); i++ )
        mvwprintw( ablak.AblakMutato(), y, x + i, " " );
    wrefresh(ablak.AblakMutato()); // ncurses felulet frissitese
    wmove( ablak.AblakMutato(), y, x ); // a megfelelo mezore ugras
    switch (chAtirando)
    {
       case 'c': // cim mezo modositasa
          wgetnstr( ablak.AblakMutato(), m_pCim, 30 );
	  for ( i = strlen(m_pCim); i < 31; i++ )
	      m_pCim[i] = '\0';
	  m_pModositandok[0] = 'c';      
	  break;
       case 'e': // eloado mezo modositasa
          wgetnstr( ablak.AblakMutato(), m_pEloado, 30 );
	  for ( i = strlen(m_pEloado); i < 31; i++ )
	      m_pEloado[i] = '\0';
	  m_pModositandok[1] = 'e';      
	  break;
       case 'a': // album mezo modositasa
          wgetnstr( ablak.AblakMutato(), m_pAlbum, 30 );
	  for ( i = strlen(m_pAlbum); i < 31; i++ )
	      m_pAlbum[i] = '\0';
	  m_pModositandok[2] = 'a';        
	  break;
       case 'g': // megjegyzes mezo modositasa
          wgetnstr( ablak.AblakMutato(), m_pMegjegyzes, 30 );
	  for ( i = strlen(m_pMegjegyzes); i < 31; i++ )
	      m_pMegjegyzes[i] = '\0';
	  m_pModositandok[4] = 'g';      
	  break;
       case 'v': // kiadas ev mezo modositasa
          wgetnstr( ablak.AblakMutato(), pTarolo, 4 );
          nSzam = atoi(pTarolo);
	  if ( nSzam <= 2100 && nSzam >= 1900 )
	  {
	      for ( i = 0; i < 4; i++ )
	          m_pEv[i] = pTarolo[i];
	      m_pModositandok[3] = 'v';
	  }
	  break;	  
       case 'm': // megjegyzes mezo modositasa
          wgetnstr( ablak.AblakMutato(), pTarolo, 3 );
          nSzam = atoi(pTarolo);
	  if ( nSzam <= 255 && nSzam >= 0 )
	  {
	      m_pMufaj[0] = nSzam;
	      m_pModositandok[5] = 'm';
	  }
	  break;	  
    }
    wattron( ablak.AblakMutato(), COLOR_PAIR(1) );
    wmove( ablak.AblakMutato(), y, x );
    for ( i = 0 ; i < 30; i++ )
       mvwprintw( ablak.AblakMutato(), y, x + i, " " );
    noecho();
    delete [] pTarolo;
}

/*
    Feladata: CID3Tag ertekado operator
    Hasznalatanak elofeltetelei: meg kell adni neki egy CID3Tag tipusu
           objektumot
    Bemeno parameterek: 'A' objektum adattagjai
    Kimeno parameterek: CID3Tag objektum
    Egyeb parameterek: -
    Hivatkozott globalis valtozok: -
    Hivott fuggvenyek: -
    Keszito: Roczei Gabor
    Utolso modositas: 2002. november 20.
*/

CID3Tag& CID3Tag :: operator=( const CID3Tag& A ) // ertekado operator
{
    if ( this != &A )
    {
        strcpy( m_pFajlNev, A.m_pFajlNev );
	strcpy( m_pCim, A.m_pCim );
	strcpy( m_pEloado, A.m_pEloado );
	strcpy( m_pAlbum, A.m_pAlbum );
	strcpy( m_pEv, A.m_pEv );
	strcpy( m_pMegjegyzes, A.m_pMegjegyzes );
	strcpy( m_pModositandok, A.m_pModositandok );
	strcpy( m_pMufaj, A.m_pMufaj );
	m_chTAG = A.m_chTAG;
    }	
    return *this;
}

/*
    Feladata: CID3Tag copy konstruktora
    Hasznalatanak elofeltetelei: meg kell adni neki egy CID3Tag
            objektumot
    Bemeno parameterek: CID3Tag tipusu A objektum
    Kimeno parameterek: -
    Egyeb parameterek: -
    Hivatkozott globalis valtozok: -
    Hivott fuggvenyek: -
    Keszito: Roczei Gabor
    Utolso modositas: 2002. november 20.
*/

CID3Tag :: CID3Tag( const CID3Tag& A ) // copy konstruktor
{
      strcpy( m_pFajlNev, A.m_pFajlNev );
      strcpy( m_pCim, A.m_pCim );
      strcpy( m_pEloado, A.m_pEloado );
      strcpy( m_pAlbum, A.m_pAlbum );
      strcpy( m_pEv, A.m_pEv );
      strcpy( m_pMegjegyzes, A.m_pMegjegyzes );
      strcpy( m_pModositandok, A.m_pModositandok );
      strcpy( m_pMufaj, A.m_pMufaj );
      m_chTAG = A.m_chTAG;
}
