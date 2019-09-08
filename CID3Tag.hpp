/*
   CID3Tag.hpp
   Keszitette: Roczei Gabor
   Utolso modositas: 2002. november 19.
*/

#ifndef __ID3V1TAG__
   #define __ID3V1TAG__
   #include <fstream>
   #include "CID3Ablak.hpp"

   class CID3Tag
   {
       private:
            std::fstream m_MP3Fajl; // a Mp3 fajl megnyitasara, es kezelesere szolgalo objektum
            char *m_pFajlNev; // a fajl nevet tartalmazza
            char *m_pCim; // az Mp3 szam cimet tarolja
            char *m_pEloado;  // az Mp3 szam eloadojanak a nevet tarolja
            char *m_pAlbum; // az Mp3 szam albumcimet tarolja
            char *m_pEv; // a kiadasi evet tarolja
            char *m_pMegjegyzes; // a megjegyzesrovatot tarolja
            char *m_pMufaj; // a mufajahoz hozzarendelt szamot tarolj
            char *m_pModositandok; // ez tarolja, hogy mely TAG-ok valtoztak meg
	    char m_chTAG;
       public:
            CID3Tag( char* pMP3FajlNeve ); // konstruktor
            ~CID3Tag(); // destruktor
            char* Kiolvas( char chKiolvasando ); // Visszaadja a kert tag memoria cimet
            void Modosit( char chModositando ); // modosito fuggveny
	    void Atir( CID3Ablak&, char ); 
	    void MenuKezelo( CID3Ablak&, int& );
	    CID3Tag& operator=( const CID3Tag& ); // ertekado operator overloading
	    CID3Tag( const CID3Tag& ); // copy konstruktor

   };
#endif
