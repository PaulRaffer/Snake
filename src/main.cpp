/*
    SNAKE
    *****************************

    Version:        1.27.0
    Datum:          25.06.2017
    *****************************

    ENTWICKLER
    Name:           Raffer Paul
    Schule:         HTL Hollabrunn
    Klasse:         1BHEL
    Katalognummer:  22
    *****************************

    INFORMATIONEN ZUM SPIEL

    Spieler: 1-4

    GEBÄUDE:
    Zentrale
    Kanone
    Krankenhaus
    Geldlager
    Mauer

    PUNKTE:
    Essen
    Geld
    Leben
    Hindernis
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <display.h>
#include <time.h>


using namespace std;



typedef struct
{
    double
    start = clock(),
    ende,
    pause;

} Zeitmessung;

typedef struct
{
    unsigned int x, y;

} Koordinaten;

typedef struct
{
    char
    oben,
    unten,
    links,
    rechts,

    oben_links,
    oben_rechts,
    unten_links,
    unten_rechts,

    menue;

} Tasten;

typedef struct
{
    string name;
    unsigned int naechste_seite;

} Seite;

typedef struct
{
    unsigned int
    hintergrund,
    spielfeld = 600,
    wand = 200;

} Farben;

typedef struct
{
    Koordinaten groesse;
    Farben farbe;

    bool
    cheats = false,
    ton = false,
    cursor = true;

    unsigned int
    pause = 10;

    char
    beenden = '!',
    menue_pause = ' ',
    menue_cheats = '0';

    vector <Seite> seite_menue;

} Spielfeld;

typedef struct
{
    vector <Koordinaten> pos;

    char
    richtung,
    richtung_alt,
    richtung_menue;

    bool
    diagonal_fahren = true,
    waende = true,
    name_anzeigen = true,

    bewegen = true;

    Zeitmessung zeit;

} Schlange;

typedef struct
{
    bool
    gebaut = false,
    verschieben = false,
    betreten = false;

    Koordinaten
    start_pos,
    ende_pos;

    int
    reichweite,
    level,
    zahl;

    char
    richtung;

    Zeitmessung zeit_betreten;
    Zeitmessung zeit_ereignis;

} Gebaeude_y;

typedef struct
{
    string
    name,
    info;

    long long
    kosten;

    vector <Gebaeude_y> _;

} Gebaeude_x;

typedef struct
{
    Gebaeude_x zentrale;
    Gebaeude_x kanone;
    Gebaeude_x krankenhaus;
    Gebaeude_x geldlager;
    Gebaeude_x mauer;
    Gebaeude_x teleporter;

} Gebaeude;

typedef struct
{
    Koordinaten
    pos;

    unsigned char
    richtung,
    zeichen;

    unsigned int
    farbe;

    Zeitmessung
    zeit;

} Punkt;

typedef struct
{
    string name;

    long long
    punkte,
    leben,
    geld,
    menue_seite;

    bool
    computer = false,
    gameover = false;

    vector <unsigned int> farbe;

    Schlange schlange;
    Gebaeude gebaeude;
    Tasten tasten;

    vector <Punkt> punkt;

} Spieler;

typedef struct
{
    vector <Punkt> essen;

    vector <Punkt> geld;
    vector <Punkt> leben;
    Zeitmessung zeit;

    vector <Punkt> hindernis;

} Punkte;



int eingaben( Spielfeld &spielfeld, vector <Spieler> &spieler );


void spiel( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte, time_t t );


void spielfeld_erstellen( Spielfeld &spielfeld, vector <Spieler> &spieler );
void punkte_erstellen( vector <Punkt> &punkt, Spielfeld &spielfeld, vector <Spieler> &spieler, time_t t );
void punkte_zeichnen( vector <Punkt> &punkt );
void gebaeude_zeichnen( vector <Spieler> &spieler, Gebaeude_x &gebaeude, unsigned int s, unsigned int g );


void richtung( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte, time_t t );
void richtung_spieler( char richtung, vector <Spieler> &spieler );
void richtung_computer( vector <Spieler> &spieler, Punkte &punkte );

void bewegen( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte, unsigned long long zaehler, time_t t );
void gebaeude_betreten( Spielfeld &spielfeld, vector <Spieler> &spieler, Gebaeude_x &gebaeude, unsigned long long s );
void spieler_bewegen( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte, unsigned long long zaehler, unsigned int s, time_t t );
void gebaeude_farbe( vector <Spieler> spieler, vector <Gebaeude_x> gebaeude, unsigned long long s, unsigned int i );
void gebaeude( vector <Spieler> &spieler, unsigned int s );
void punkte_bewegen( Spielfeld &spielfeld, vector <Spieler> &spieler, unsigned int s );

void spieler_informationen( Spielfeld spielfeld, vector <Spieler> spieler, unsigned int s );
void spieler_menue( Spielfeld &spielfeld, vector <Spieler> &spieler, unsigned int s );
void gebaeude_verschieben( Spielfeld &spielfeld, vector <Spieler> &spieler, vector <Gebaeude_x> &gebaeude, unsigned long long s, bool &v );
void gebaeude_kaufen( Spielfeld &spielfeld, vector <Spieler> &spieler, Gebaeude_x &gebaeude, unsigned long long s );


void menue_pause( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte, time_t t );
void menue_cheats( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte, time_t t );


void leben( Spielfeld &spielfeld, vector <Spieler> &spieler, unsigned int s );
bool gameover( Spielfeld &spielfeld, vector <Spieler> &spieler, vector <Punkt> &hindernis, unsigned int s );
void gebaeude_gameover( Spielfeld &spielfeld, vector <Spieler> &spieler, vector <Gebaeude_x> &gebaeude, unsigned long long s, unsigned long long sp );


void farben();



int eingaben( Spielfeld &spielfeld, vector <Spieler> &spieler )
{
    int s;

    switch( getch() )
    {
    case'1':
        s = 4;
        spielfeld.groesse.x = 156;
        spielfeld.groesse.y = 71;
        break;

    case'2':
        s = 4;
        spielfeld.groesse.x = 235;
        spielfeld.groesse.y = 63;
        break;

    default:
        cout << "ANZAHL DER SPIELER: ";
        cin >> s;

        cout << "SPIELFELDGROESSE:\nX: ";
        cin >> spielfeld.groesse.x;

        cout << "Y: ";
        cin >> spielfeld.groesse.y;
        break;
    }
    return s;
}


void spiel( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte, time_t t )
{
    bool wiederholen = true;

    spielfeld_erstellen( spielfeld, spieler );

    for( unsigned int s = 0; s < spieler.size(); s ++ )
    {
        for( unsigned int g = 0; g < spieler.at(s).gebaeude.zentrale._.size(); g ++ )
        {
            if( spieler.at(s).gebaeude.zentrale._.at(g).gebaut == true )
                gebaeude_zeichnen( spieler, spieler.at(s).gebaeude.zentrale, s, g );
        }

        for( unsigned int g = 0; g < spieler.at(s).gebaeude.kanone._.size(); g ++ )
        {
            if( spieler.at(s).gebaeude.kanone._.at(g).gebaut == true )
                gebaeude_zeichnen( spieler, spieler.at(s).gebaeude.kanone, s, g );
        }

        for( unsigned int g = 0; g < spieler.at(s).gebaeude.krankenhaus._.size(); g ++ )
        {
            if( spieler.at(s).gebaeude.krankenhaus._.at(g).gebaut == true )
                gebaeude_zeichnen( spieler, spieler.at(s).gebaeude.krankenhaus, s, g );
        }

        for( unsigned int g = 0; g < spieler.at(s).gebaeude.geldlager._.size(); g ++ )
        {
            if( spieler.at(s).gebaeude.geldlager._.at(g).gebaut == true )
                gebaeude_zeichnen( spieler, spieler.at(s).gebaeude.geldlager, s, g );
        }

        for( unsigned int g = 0; g < spieler.at(s).gebaeude.teleporter._.size(); g ++ )
        {
            if( spieler.at(s).gebaeude.teleporter._.at(g).gebaut == true )
                gebaeude_zeichnen( spieler, spieler.at(s).gebaeude.teleporter, s, g );
        }
    }

    punkte_zeichnen( punkte.hindernis );
    punkte_zeichnen( punkte.essen );

    for( unsigned int i = 0; i < spieler.size(); i ++ )
    {
        spieler_informationen( spielfeld, spieler, i );
    }

    for( static unsigned long long zaehler = 0; wiederholen == true; zaehler ++ )
    {
        richtung( spielfeld, spieler, punkte, t );

        bewegen( spielfeld, spieler, punkte, zaehler, t );

        wiederholen = true;

        for( unsigned int i = 0; i < spieler.size(); i ++ )
        {
            if( spieler.at(i).gameover == true )
            {
                wiederholen = false;
            }

            else
            {
                wiederholen = true;
                i = spieler.size();
            }
        }
    }
}


void spielfeld_erstellen( Spielfeld &spielfeld, vector <Spieler> &spieler )
{
    system("cls");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe.wand);

    for( unsigned int y = 0; y <= spielfeld.groesse.y + 1; y ++ )
    {

        for( unsigned int x = 0; x <= spielfeld.groesse.x + 1; x ++ )
        {
            if(( x == 0 ) || ( x == spielfeld.groesse.x + 1 )
            || ( y == 0 ) || ( y == spielfeld.groesse.y + 1 ))
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe.wand);
                cout << '+';
            }

            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe.spielfeld);
                cout << ' ';
            }
        }

        cout << endl;
    }

    /*
        SPIELFELD

          0 1 2 3 4 5
        0 + + + + + +
        1 +         +
        2 +         +
        3 +         +
        4 +         +
        5 + + + + + +
    */

    for( unsigned int sp = 0; sp < spieler.size(); sp ++ )
    {
        for( unsigned int i = 0; i < spieler.at(sp).schlange.pos.size(); i ++ )
        {
            SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(sp).farbe.at( i % spieler.at(sp).farbe.size() ));
            gotoXY( spieler.at(sp).schlange.pos.at(i).x, spieler.at(sp).schlange.pos.at(i).y );

            if(( spieler.at(sp).schlange.name_anzeigen == true ) && ( i < spieler.at(sp).name.size() ))
            {
                cout << spieler.at(sp).name.at(i);
            }

            else
            {
                cout << ' ';
            }
        }
    }
}


void punkte_erstellen( vector <Punkt> &punkt, Spielfeld &spielfeld, vector <Spieler> &spieler, time_t t )
{
    bool wiederholen = false;

    for( unsigned int p = 0; p < punkt.size(); p ++ )
    {
        do
        {
            wiederholen = false;

            punkt.at(p).pos.x = ( rand() % spielfeld.groesse.x ) + 1;
            punkt.at(p).pos.y = ( rand() % spielfeld.groesse.y ) + 1;

            for( unsigned int s = 0; s < spieler.size(); s ++ )
            {
                for( unsigned int i = 0; i < spieler.at(s).schlange.pos.size(); i ++ )
                {
                    if(( punkt.at(p).pos.x == spieler.at(s).schlange.pos.at(i).x ) && ( punkt.at(p).pos.y == spieler.at(s).schlange.pos.at(i).y ))
                    {
                        wiederholen = true;
                    }
                }
            }

            for( unsigned int j = 0; j < p; j ++ )
            {
                if(( punkt.at(p).pos.x == punkt.at(j).pos.x ) && ( punkt.at(p).pos.y == punkt.at(j).pos.y ))
                {
                    wiederholen = true;
                }
            }
        }
        while( wiederholen == true );
    }
}


void punkte_zeichnen( vector <Punkt> &punkt )
{
    for( unsigned int p = 0; p < punkt.size(); p ++ )
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), punkt.at(p).farbe);
        gotoXY( punkt.at(p).pos.x, punkt.at(p).pos.y );
        cout << punkt.at(p).zeichen;
    }
}


void richtung( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte, time_t t )
{

    if( spielfeld.ton == true )
    {
        Beep( 1350, spielfeld.pause );
    }

    else if( spielfeld.ton == false )
    {
        Sleep( spielfeld.pause );
    }

    if( kbhit() )
    {
        char richtung = getch();

        if( richtung == spielfeld.beenden)
        {

        }

        else if( richtung == spielfeld.menue_pause )
        {
            menue_pause( spielfeld, spieler, punkte, t );
        }

        else if( richtung == spielfeld.menue_cheats )
        {
            menue_cheats( spielfeld, spieler, punkte, t );
        }

        richtung_spieler( richtung, spieler );
    }

    richtung_computer( spieler, punkte );
}


void gebaeude_zeichnen( vector <Spieler> &spieler, Gebaeude_x &gebaeude, unsigned int s, unsigned int g )
{
    for( unsigned int y = gebaeude._.at(g).start_pos.y; y <= gebaeude._.at(g).ende_pos.y; y ++ )
    {
        gotoXY( gebaeude._.at(g).start_pos.x, y );

        for( unsigned int x = gebaeude._.at(g).start_pos.x; x <= gebaeude._.at(g).ende_pos.x; x ++ )
        {
            if((( gebaeude.name == "Geldlager" ) && (( x == gebaeude._.at(g).start_pos.x ) || ( x == gebaeude._.at(g).ende_pos.x ) || ( y == gebaeude._.at(g).start_pos.y ) || ( y == gebaeude._.at(g).ende_pos.y )))
            || (( gebaeude.name == "Krankenhaus" ) && (( x - gebaeude._.at(g).start_pos.x == ( gebaeude._.at(g).ende_pos.x - gebaeude._.at(g).start_pos.x ) / 2 ) || ( y - gebaeude._.at(g).start_pos.y == ( gebaeude._.at(g).ende_pos.y - gebaeude._.at(g).start_pos.y ) / 2 )))
            || ( gebaeude.name == "Mauer" )
            || (( gebaeude.name == "Teleporter" ) && (( x - gebaeude._.at(g).start_pos.x == y - gebaeude._.at(g).start_pos.y ) || ( x - gebaeude._.at(g).start_pos.x + y - gebaeude._.at(g).start_pos.y == gebaeude._.at(g).ende_pos.x - gebaeude._.at(g).start_pos.x ))))
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(1));
            }

            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(0));
            }
            cout << ' ';
        }
    }
}


void richtung_spieler( char richtung, vector <Spieler> &spieler )
{
    bool wiederholen;
    unsigned int sp = 0;

    do
    {
        wiederholen = false;

        if(( richtung == spieler.at(sp).tasten.menue )
                || ((( richtung == spieler.at(sp).tasten.oben ) && ( spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.unten ))
                    || (( richtung == spieler.at(sp).tasten.unten ) && ( spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.oben ))
                    || (( richtung == spieler.at(sp).tasten.links ) && ( spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.rechts ))
                    || (( richtung == spieler.at(sp).tasten.rechts ) && ( spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.links ))
                    || (( spieler.at(sp).schlange.diagonal_fahren == true ) && ( richtung == spieler.at(sp).tasten.oben_links ) && ( spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.unten_rechts ))
                    || (( spieler.at(sp).schlange.diagonal_fahren == true ) && ( richtung == spieler.at(sp).tasten.oben_rechts ) && ( spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.unten_links ))
                    || (( spieler.at(sp).schlange.diagonal_fahren == true ) && ( richtung == spieler.at(sp).tasten.unten_links ) && ( spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.oben_rechts ))
                    || (( spieler.at(sp).schlange.diagonal_fahren == true ) && ( richtung == spieler.at(sp).tasten.unten_rechts ) && ( spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.oben_links ))))
        {
            if( spieler.at(sp).schlange.bewegen == true )
            {
                spieler.at(sp).schlange.richtung_alt = spieler.at(sp).schlange.richtung;
            }

            spieler.at(sp).schlange.richtung = richtung;
        }


        else if( sp < spieler.size() - 1 )
        {
            sp ++;
            wiederholen = true;
        }
    }
    while( wiederholen == true );
}


void richtung_computer( vector <Spieler> &spieler, Punkte &punkte )
{
    for( unsigned int i = 0; i < spieler.size(); i ++ )
    {
        if( spieler.at(i).computer == true )
        {
            if(( punkte.essen.at(0).pos.y < spieler.at(i).schlange.pos.at(0).y ) && ( spieler.at(i).schlange.richtung != spieler.at(i).tasten.unten ))
            {
                spieler.at(i).schlange.richtung = spieler.at(i).tasten.oben;
            }

            else if(( punkte.essen.at(0).pos.y > spieler.at(i).schlange.pos.at(0).y ) && ( spieler.at(i).schlange.richtung != spieler.at(i).tasten.oben ))
            {
                spieler.at(i).schlange.richtung = spieler.at(i).tasten.unten;
            }

            else if(( punkte.essen.at(0).pos.x < spieler.at(i).schlange.pos.at(0).x ) && ( spieler.at(i).schlange.richtung != spieler.at(i).tasten.rechts ))
            {
                spieler.at(i).schlange.richtung = spieler.at(i).tasten.links;
            }

            else if(( punkte.essen.at(0).pos.x > spieler.at(i).schlange.pos.at(0).x ) && ( spieler.at(i).schlange.richtung != spieler.at(i).tasten.links ))
            {
                spieler.at(i).schlange.richtung = spieler.at(i).tasten.rechts;
            }
        }
    }
}

void gebaeude_betreten( Spielfeld &spielfeld, vector <Spieler> &spieler, Gebaeude_x &gebaeude, unsigned long long s )
{
    for( unsigned int i = 0; i < gebaeude._.size(); i ++ )
    {
        if(( gebaeude._.at(i).gebaut == true )
                && ( gebaeude._.at(i).verschieben == false )
                && ( gebaeude._.at(i).betreten == false )
                && ( spieler.at(s).schlange.pos.at(0).x <= gebaeude._.at(i).ende_pos.x )
                && ( spieler.at(s).schlange.pos.at(0).y <= gebaeude._.at(i).ende_pos.y )
                && ( spieler.at(s).schlange.pos.at(0).x >= gebaeude._.at(i).start_pos.x )
                && ( spieler.at(s).schlange.pos.at(0).y >= gebaeude._.at(i).start_pos.y ))
        {
            spieler.at(s).schlange.bewegen = false;
            gebaeude._.at(i).betreten = true;
            gebaeude._.at(i).zeit_betreten.start = clock();
        }

        else if( gebaeude._.at(i).betreten == true )
        {
            spieler.at(s).schlange.bewegen = true;
            gebaeude._.at(i).betreten = false;
            spieler_informationen( spielfeld, spieler, s );
        }
    }
}

void bewegen( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte, unsigned long long zaehler, time_t t )
{
    for( unsigned int s = 0; s < spieler.size(); s ++ )
    {
        if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.menue )
        {
            gebaeude_betreten( spielfeld, spieler, spieler.at(s).gebaeude.zentrale, s );
            gebaeude_betreten( spielfeld, spieler, spieler.at(s).gebaeude.krankenhaus, s );
            gebaeude_betreten( spielfeld, spieler, spieler.at(s).gebaeude.geldlager, s );
            gebaeude_betreten( spielfeld, spieler, spieler.at(s).gebaeude.teleporter, s );

            spieler.at(s).schlange.richtung = spieler.at(s).schlange.richtung_alt;
        }



        for( unsigned int i = 0; i < spieler.at(s).gebaeude.zentrale._.size(); i ++ )
        {
            if( spieler.at(s).gebaeude.zentrale._.at(i).betreten == true )
            {
                spieler_menue( spielfeld, spieler, s );
                punkte_zeichnen( punkte.essen );
                punkte_zeichnen( punkte.geld );
                punkte_zeichnen( punkte.leben );
                punkte_zeichnen( punkte.hindernis );
            }
        }

        for( unsigned int i = 0; i < spieler.at(s).gebaeude.krankenhaus._.size(); i ++ )
        {
            if( spieler.at(s).gebaeude.krankenhaus._.at(i).betreten == true )
            {
                spieler.at(s).gebaeude.krankenhaus._.at(i).zeit_betreten.ende = clock() - spieler.at(s).gebaeude.krankenhaus._.at(i).zeit_betreten.start;
                if( spieler.at(s).gebaeude.krankenhaus._.at(i).zeit_betreten.ende >= spieler.at(s).gebaeude.krankenhaus._.at(i).zeit_betreten.pause )
                {
                    spieler.at(s).leben ++;
                    spieler.at(s).gebaeude.krankenhaus._.at(i).zeit_betreten.start = clock();

                    spieler_informationen( spielfeld, spieler, s );
                }
            }
        }

        for( unsigned int i = 0; i < spieler.at(s).gebaeude.geldlager._.size(); i ++ )
        {
            if( spieler.at(s).gebaeude.geldlager._.at(i).betreten == true )
            {
                if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.oben )
                {
                    spieler.at(s).gebaeude.geldlager._.at(i).zahl += spieler.at(s).geld;
                    spieler.at(s).geld = 0;
                }

                else if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.unten )
                {
                    spieler.at(s).geld += spieler.at(s).gebaeude.geldlager._.at(i).zahl;
                    spieler.at(s).gebaeude.geldlager._.at(i).zahl = 0;
                }

                spieler_informationen( spielfeld, spieler, s );
            }
        }

        /*
        for( unsigned int i = 0; i < spieler.at(s).gebaeude.teleporter._.size(); i ++ )
        {
            if( spieler.at(s).gebaeude.teleporter._.at(i).betreten == true )
            {
                if(( spieler.at(s).schlange.richtung == spieler.at(s).tasten.unten ) && ( spieler.at(s).gebaeude.teleporter._.size() >= 2 ))
                {
                    if( i == 0 )
                    {
                        spieler.at(s).schlange.pos.at(0).x = ( spieler.at(s).gebaeude.teleporter._.at(1).start_pos.x + spieler.at(s).gebaeude.teleporter._.at(1).ende_pos.x ) / 2;
                        spieler.at(s).schlange.pos.at(0).y = ( spieler.at(s).gebaeude.teleporter._.at(1).start_pos.y + spieler.at(s).gebaeude.teleporter._.at(1).ende_pos.y ) / 2;
                    }

                    else if( i == 1 )
                    {
                        spieler.at(s).schlange.pos.at(1).x = ( spieler.at(s).gebaeude.teleporter._.at(0).start_pos.x + spieler.at(s).gebaeude.teleporter._.at(0).ende_pos.x ) / 2;
                        spieler.at(s).schlange.pos.at(1).y = ( spieler.at(s).gebaeude.teleporter._.at(0).start_pos.y + spieler.at(s).gebaeude.teleporter._.at(0).ende_pos.y ) / 2;
                    }

                    spieler.at(s).schlange.richtung = spieler.at(s).schlange.richtung_alt;
                    spieler.at(s).schlange.bewegen = true;
                    spieler.at(s).gebaeude.teleporter._.at(i).betreten = false;
                    i = spieler.at(s).gebaeude.teleporter._.size() + 1;
                }

                spieler_informationen( spielfeld, spieler, s );
            }
        }
        */

        if( spieler.at(s).schlange.bewegen == true )
        {
            spieler_bewegen( spielfeld, spieler, punkte, zaehler, s, t );
        }

        gebaeude( spieler, s );
        punkte_bewegen( spielfeld, spieler, s );

        if( spielfeld.cursor == false )
        {
            SetCursorPos( 2000, 2000 );
        }
    }

    static unsigned int zufall;

    punkte.zeit.ende = clock() - punkte.zeit.start;

    if( punkte.zeit.ende > 8000 )
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe.spielfeld);

        gotoXY( punkte.geld.at(0).pos.x, punkte.geld.at(0).pos.y );
        cout << ' ';
        punkte.geld.at(0).pos.x = 0;
        punkte.geld.at(0).pos.y = 0;

        gotoXY( punkte.leben.at(0).pos.x, punkte.leben.at(0).pos.y );
        cout << ' ';
        punkte.leben.at(0).pos.x = 0;
        punkte.leben.at(0).pos.y = 0;
    }

    if(( punkte.zeit.ende > 20000 ))
    {
        punkte.zeit.start = clock();

        zufall = rand() % 2 ;
        if( zufall == 0 )
        {
            punkte_erstellen( punkte.geld, spielfeld, spieler, t );
            punkte_zeichnen( punkte.geld );
        }
        else if( zufall == 1 )
        {
            punkte_erstellen( punkte.leben, spielfeld, spieler, t );
            punkte_zeichnen( punkte.leben );
        }
    }
}

void gebaeude_farbe( vector <Spieler> &spieler, Gebaeude_x &gebaeude, unsigned long long s, unsigned int i )
{
    for( unsigned int g = 0; g < gebaeude._.size(); g ++ )
    {
        if(( spieler.at(s).schlange.pos.at( spieler.at(s).schlange.pos.size() - 1 ).x <= gebaeude._.at(g).ende_pos.x )
                && ( spieler.at(s).schlange.pos.at( spieler.at(s).schlange.pos.size() - 1 ).y <= gebaeude._.at(g).ende_pos.y )
                && ( spieler.at(s).schlange.pos.at( spieler.at(s).schlange.pos.size() - 1 ).x >= gebaeude._.at(g).start_pos.x )
                && ( spieler.at(s).schlange.pos.at( spieler.at(s).schlange.pos.size() - 1 ).y >= gebaeude._.at(g).start_pos.y )
                && ( gebaeude._.at(g).gebaut == true ))
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(i).farbe.at(0));
        }
    }
}

void spieler_bewegen( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte, unsigned long long zaehler, unsigned int s, time_t t )
{
    spieler.at(s).schlange.zeit.ende = clock() - spieler.at(s).schlange.zeit.start;

    if(( spieler.at(s).schlange.zeit.ende >= spieler.at(s).schlange.zeit.pause ) && ( spieler.at(s).gameover == false ))
    {
        spieler.at(s).schlange.zeit.start = clock();

        for( unsigned int i = 0; i < spieler.at(s).schlange.pos.size(); i ++ )
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at( i % spieler.at(s).farbe.size() ));
            gotoXY( spieler.at(s).schlange.pos.at(i).x, spieler.at(s).schlange.pos.at(i).y );

            if(( spieler.at(s).schlange.name_anzeigen == true ) && ( i < spieler.at(s).name.size() ))
            {
                cout << spieler.at(s).name.at(i);
            }

            else
            {
                cout << ' ';
            }
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe.spielfeld);

        for( unsigned int i = 0; i < spieler.size(); i ++ )
        {
            gebaeude_farbe( spieler, spieler.at(i).gebaeude.zentrale, s, i );
            gebaeude_farbe( spieler, spieler.at(i).gebaeude.kanone, s, i );
            gebaeude_farbe( spieler, spieler.at(i).gebaeude.krankenhaus, s, i );
            gebaeude_farbe( spieler, spieler.at(i).gebaeude.geldlager, s, i );
            gebaeude_farbe( spieler, spieler.at(i).gebaeude.mauer, s, i );
            gebaeude_farbe( spieler, spieler.at(i).gebaeude.teleporter, s, i );
        }

        gotoXY( spieler.at(s).schlange.pos.at( spieler.at(s).schlange.pos.size() - 1 ).x, spieler.at(s).schlange.pos.at( spieler.at(s).schlange.pos.size() - 1 ).y );
        cout << ' ';

        if( spieler.at(s).schlange.richtung != ' ' )
        {
            for( int i = spieler.at(s).schlange.pos.size() - 1; i > 0; i -- )
            {
                spieler.at(s).schlange.pos.at(i).x = spieler.at(s).schlange.pos.at(i - 1).x;
                spieler.at(s).schlange.pos.at(i).y = spieler.at(s).schlange.pos.at(i - 1).y;
            }
        }

        if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.oben )
        {
            spieler.at(s).schlange.pos.at(0).y --;
        }

        else if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.unten )
        {
            spieler.at(s).schlange.pos.at(0).y ++;
        }

        else if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.links )
        {
            spieler.at(s).schlange.pos.at(0).x --;
        }

        else if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.rechts )
        {
            spieler.at(s).schlange.pos.at(0).x ++;
        }

        else if( spieler.at(s).schlange.diagonal_fahren == true )
        {
            if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.oben_links )
            {
                spieler.at(s).schlange.pos.at(0).y --;
                spieler.at(s).schlange.pos.at(0).x --;
            }

            else if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.oben_rechts )
            {
                spieler.at(s).schlange.pos.at(0).y --;
                spieler.at(s).schlange.pos.at(0).x ++;
            }

            else if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.unten_links )
            {
                spieler.at(s).schlange.pos.at(0).y ++;
                spieler.at(s).schlange.pos.at(0).x --;
            }

            else if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.unten_rechts )
            {
                spieler.at(s).schlange.pos.at(0).y ++;
                spieler.at(s).schlange.pos.at(0).x ++;
            }
        }

        /*
            STEUERUNG

            SPIELER 1   *   SPIELER 2   *   SPIELER 3   *   SPIELER 4
                        *               *               *
            q   w   e   *   r   t   z   *   u   i   o   *   7   8   9
              \ | /     *     \ | /     *     \ | /     *     \ | /
            a --+-- d   *   f --+-- h   *   j --+-- l   *   4 --+-- 6
              / | \     *     / | \     *     / | \     *     / | \
            y   s   c   *   v   g   n   *   m   k   .   *   1   5   3
                        *               *               *
            Pause: x    *   Pause: v    *   Pause: ,    *   Pause: 2
        */

        if( spieler.at(s).schlange.waende == false )
        {
            if( spieler.at(s).schlange.pos.at(0).y == 0)
            {
                spieler.at(s).schlange.pos.at(0).y = spielfeld.groesse.y;
            }

            if( spieler.at(s).schlange.pos.at(0).y == spielfeld.groesse.y + 1)
            {
                spieler.at(s).schlange.pos.at(0).y = 1;
            }

            if( spieler.at(s).schlange.pos.at(0).x == 0)
            {
                spieler.at(s).schlange.pos.at(0).x = spielfeld.groesse.x;
            }

            if( spieler.at(s).schlange.pos.at(0).x == spielfeld.groesse.x + 1)
            {
                spieler.at(s).schlange.pos.at(0).x = 1;
            }
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(0));

        if(( spieler.at(s).schlange.pos.at(0).x == punkte.essen.at(0).pos.x ) && ( spieler.at(s).schlange.pos.at(0).y == punkte.essen.at(0).pos.y ))
        {
            spieler.at(s).punkte ++;
            gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 3 );
            cout << spieler.at(s).punkte;

            spieler.at(s).schlange.pos.resize( spieler.at(s).schlange.pos.size() + 1 );
            gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 4 );
            cout << spieler.at(s).schlange.pos.size();

            spieler.at(s).geld += rand() % 11;
            gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 5 );
            cout << spieler.at(s).geld << " Euro";

            punkte_erstellen( punkte.essen, spielfeld, spieler, t );
            punkte_zeichnen( punkte.essen );
        }

        if(( spieler.at(s).schlange.pos.at(0).x == punkte.geld.at(0).pos.x ) && ( spieler.at(s).schlange.pos.at(0).y == punkte.geld.at(0).pos.y ))
        {
            spieler.at(s).geld += zaehler / 100;
            punkte.geld.at(0).pos.x = 0;
            punkte.geld.at(0).pos.y = 0;
            gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 5 );
            cout << spieler.at(s).geld << " Euro";
        }

        if(( spieler.at(s).schlange.pos.at(0).x == punkte.leben.at(0).pos.x ) && ( spieler.at(s).schlange.pos.at(0).y == punkte.leben.at(0).pos.y ))
        {
            spieler.at(s).leben += 1;
            punkte.leben.at(0).pos.x = 0;
            punkte.leben.at(0).pos.y = 0;
            gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 6 );
            cout << spieler.at(s).leben;
        }
    }

    if( spieler.at(s).gameover == false )
    {
        spieler.at(s).gameover = gameover( spielfeld, spieler, punkte.hindernis, s );
    }
}


void gebaeude( vector <Spieler> &spieler, unsigned int s )
{
    for( unsigned int i = 0; i < spieler.at(s).gebaeude.kanone._.size(); i ++ )
    {
        spieler.at(s).gebaeude.kanone._.at(i).zeit_ereignis.ende = clock() - spieler.at(s).gebaeude.kanone._.at(i).zeit_ereignis.start;

        if(( spieler.at(s).gebaeude.kanone._.at(i).gebaut == true )
        && ( spieler.at(s).gebaeude.kanone._.at(i).verschieben == false )
        && ( spieler.at(s).gebaeude.kanone._.at(i).zeit_ereignis.ende >= spieler.at(s).gebaeude.kanone._.at(i).zeit_ereignis.pause ))
        {
            spieler.at(s).gebaeude.kanone._.at(i).zeit_ereignis.start = clock();

            spieler.at(s).punkt.resize( spieler.at(s).punkt.size() + 1 );

            spieler.at(s).punkt.at( spieler.at(s).punkt.size() - 1 ).pos.x = ( spieler.at(s).gebaeude.kanone._.at(i).start_pos.x + spieler.at(s).gebaeude.kanone._.at(i).ende_pos.x ) / 2;
            spieler.at(s).punkt.at( spieler.at(s).punkt.size() - 1 ).pos.y = ( spieler.at(s).gebaeude.kanone._.at(i).start_pos.y + spieler.at(s).gebaeude.kanone._.at(i).ende_pos.y ) / 2;

            spieler.at(s).gebaeude.kanone._.at(i).richtung = 'd';
            spieler.at(s).punkt.at( spieler.at(s).punkt.size() - 1 ).richtung = spieler.at(s).gebaeude.kanone._.at(i).richtung;
        }
    }
}


void punkte_bewegen( Spielfeld &spielfeld, vector <Spieler> &spieler, unsigned int s )
{
    for( unsigned long long i = 0; i < spieler.at(s).punkt.size(); i ++ )
    {
        spieler.at(s).punkt.at(i).zeit.ende = clock() - spieler.at(s).punkt.at(i).zeit.start;

        if( spieler.at(s).punkt.at(i).zeit.ende >= spieler.at(s).punkt.at(i).zeit.pause )
        {
            spieler.at(s).punkt.at(i).zeit.start = clock();

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe.spielfeld);
            gotoXY( spieler.at(s).punkt.at(i).pos.x, spieler.at(s).punkt.at(i).pos.y );
            cout << ' ';

            if( spieler.at(s).punkt.at(i).richtung == spieler.at(s).tasten.rechts )
            {
                spieler.at(s).punkt.at(i).pos.x ++;
            }

            if( spieler.at(s).punkt.at(i).richtung == spieler.at(s).tasten.links )
            {
                spieler.at(s).punkt.at(i).pos.x --;
            }

            if( spieler.at(s).punkt.at(i).richtung == spieler.at(s).tasten.unten )
            {
                spieler.at(s).punkt.at(i).pos.y ++;
            }

            if( spieler.at(s).punkt.at(i).richtung == spieler.at(s).tasten.oben )
            {
                spieler.at(s).punkt.at(i).pos.y --;
            }

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(1));
            gotoXY( spieler.at(s).punkt.at(i).pos.x, spieler.at(s).punkt.at(i).pos.y );
            cout << ' ';

            if(( spieler.at(s).punkt.at(i).pos.x == 0 )
            || ( spieler.at(s).punkt.at(i).pos.y == 0 )
            || ( spieler.at(s).punkt.at(i).pos.x == spielfeld.groesse.x + 1 )
            || ( spieler.at(s).punkt.at(i).pos.y == spielfeld.groesse.y + 1 ))
            {
                spieler.at(s).punkt.at(i).richtung = ' ';
            }
        }
    }
}


void spieler_informationen( Spielfeld spielfeld, vector <Spieler> spieler, unsigned int s )
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(0));

    gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 2 );
    cout << "NAME:   " << spieler.at(s).name;

    gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 3 );
    cout << "PUNKTE: " << spieler.at(s).punkte;

    gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 4 );
    cout << "LAENGE: " << spieler.at(s).schlange.pos.size();

    gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 5 );
    cout << "GELD:   " << spieler.at(s).geld << " EURO";

    gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 6 );
    cout << "LEBEN:  " << spieler.at(s).leben;
}

void gebaeude_verschieben( Spielfeld &spielfeld, vector <Spieler> &spieler, Gebaeude_x &gebaeude, unsigned long long s, bool &v )
{
    for( unsigned int i = 0; i < gebaeude._.size(); i ++ )
    {
        if( gebaeude._.at(i).verschieben == true )
        {
            v = true;

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe.spielfeld);

            for( unsigned int y = gebaeude._.at(i).start_pos.y; y <= gebaeude._.at(i).ende_pos.y; y ++ )
            {
                gotoXY( gebaeude._.at(i).start_pos.x, y );

                for( unsigned int x = gebaeude._.at(i).start_pos.x; x <= gebaeude._.at(i).ende_pos.x; x ++ )
                {
                    cout << ' ';
                }
            }

            if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.rechts )
            {
                gebaeude._.at(i).start_pos.x ++;
                gebaeude._.at(i).ende_pos.x ++;
            }

            else if ( spieler.at(s).schlange.richtung == spieler.at(s).tasten.links )
            {
                gebaeude._.at(i).start_pos.x --;
                gebaeude._.at(i).ende_pos.x --;
            }

            else if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.unten )
            {
                gebaeude._.at(i).start_pos.y ++;
                gebaeude._.at(i).ende_pos.y ++;
            }

            else if ( spieler.at(s).schlange.richtung == spieler.at(s).tasten.oben )
            {
                gebaeude._.at(i).start_pos.y --;
                gebaeude._.at(i).ende_pos.y --;
            }


            bool bauen;

            for( unsigned int j = 0; j < spieler.at(s).gebaeude.zentrale._.size(); j ++ )
            {
                if(( gebaeude._.at(i).start_pos.x <= spieler.at(s).gebaeude.zentrale._.at(j).ende_pos.x + 3 )
                && ( gebaeude._.at(i).start_pos.y <= spieler.at(s).gebaeude.zentrale._.at(j).ende_pos.y + 3 )
                && ( gebaeude._.at(i).ende_pos.x + 3 >= spieler.at(s).gebaeude.zentrale._.at(j).start_pos.x )
                && ( gebaeude._.at(i).ende_pos.y + 3 >= spieler.at(s).gebaeude.zentrale._.at(j).start_pos.y ))
                {
                    bauen = true;
                }
            }

            if (( spieler.at(s).schlange.richtung == spieler.at(s).tasten.oben_rechts ) && ( bauen == true ))
            {
                gebaeude._.at(i).verschieben = false;
                v = false;
            }

            gebaeude_zeichnen( spieler, gebaeude, s, i);
        }
    }
}

void gebaeude_kaufen( Spielfeld &spielfeld, vector <Spieler> &spieler, Gebaeude_x &gebaeude, unsigned long long s )
{
    gebaeude._.resize( gebaeude._.size() + 1 );
    gebaeude._.at( gebaeude._.size() - 1 ).level = 1;
    spieler.at(s).geld -= gebaeude.kosten;
    gebaeude._.at( gebaeude._.size() - 1 ).gebaut = true;
    gebaeude._.at( gebaeude._.size() - 1 ).verschieben = true;

    gebaeude._.at( gebaeude._.size() - 1 ).start_pos.x = spielfeld.groesse.x / 2;
    gebaeude._.at( gebaeude._.size() - 1 ).start_pos.y = spielfeld.groesse.y / 2;
}

void spieler_menue( Spielfeld &spielfeld, vector <Spieler> &spieler, unsigned int s )
{
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), spieler.at(s).farbe.at(0) );

    bool v = false;

    gebaeude_verschieben( spielfeld, spieler, spieler.at(s).gebaeude.zentrale, s, v );
    gebaeude_verschieben( spielfeld, spieler, spieler.at(s).gebaeude.kanone, s, v );
    gebaeude_verschieben( spielfeld, spieler, spieler.at(s).gebaeude.krankenhaus, s, v );
    gebaeude_verschieben( spielfeld, spieler, spieler.at(s).gebaeude.geldlager, s, v );
    gebaeude_verschieben( spielfeld, spieler, spieler.at(s).gebaeude.mauer, s, v );
    gebaeude_verschieben( spielfeld, spieler, spieler.at(s).gebaeude.teleporter, s, v );

    if( v == false )
    {
        if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.rechts )
        {
            spieler.at(s).menue_seite ++;
        }

        else if ( spieler.at(s).schlange.richtung == spieler.at(s).tasten.links )
        {
            spieler.at(s).menue_seite --;
        }


        if( spieler.at(s).menue_seite == -1 )
        {
            spieler.at(s).menue_seite = 3;
        }

        else if( spieler.at(s).menue_seite == 4 )
        {
            spieler.at(s).menue_seite = 0;
        }

        else if( spieler.at(s).menue_seite == 99 )
        {
            spieler.at(s).menue_seite = 106;
        }

        else if( spieler.at(s).menue_seite == 107 )
        {
            spieler.at(s).menue_seite = 100;
        }


        if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.unten )
        {
            if(( spieler.at(s).menue_seite == 100 ) && ( spieler.at(s).gebaeude.zentrale.kosten <= spieler.at(s).geld ))
            {
                gebaeude_kaufen( spielfeld, spieler, spieler.at(s).gebaeude.zentrale, s );

                spieler.at(s).gebaeude.zentrale._.at( spieler.at(s).gebaeude.zentrale._.size() - 1 ).ende_pos.x = spieler.at(s).gebaeude.zentrale._.at( spieler.at(s).gebaeude.zentrale._.size() - 1 ).start_pos.x + 19;
                spieler.at(s).gebaeude.zentrale._.at( spieler.at(s).gebaeude.zentrale._.size() - 1 ).ende_pos.y = spieler.at(s).gebaeude.zentrale._.at( spieler.at(s).gebaeude.zentrale._.size() - 1 ).start_pos.y + 19;
            }

            else if(( spieler.at(s).menue_seite == 101 ) && ( spieler.at(s).gebaeude.kanone.kosten <= spieler.at(s).geld ))
            {
                gebaeude_kaufen( spielfeld, spieler, spieler.at(s).gebaeude.kanone, s );

                spieler.at(s).gebaeude.kanone._.at( spieler.at(s).gebaeude.kanone._.size() - 1 ).zeit_ereignis.pause = 1000;

                spieler.at(s).gebaeude.kanone._.at( spieler.at(s).gebaeude.kanone._.size() - 1 ).ende_pos.x = spieler.at(s).gebaeude.kanone._.at( spieler.at(s).gebaeude.kanone._.size() - 1 ).start_pos.x + 4;
                spieler.at(s).gebaeude.kanone._.at( spieler.at(s).gebaeude.kanone._.size() - 1 ).ende_pos.y = spieler.at(s).gebaeude.kanone._.at( spieler.at(s).gebaeude.kanone._.size() - 1 ).start_pos.y + 4;
            }

            else if(( spieler.at(s).menue_seite == 102 ) && ( spieler.at(s).gebaeude.krankenhaus.kosten <= spieler.at(s).geld ))
            {
                gebaeude_kaufen( spielfeld, spieler, spieler.at(s).gebaeude.krankenhaus, s );

                spieler.at(s).gebaeude.krankenhaus._.at( spieler.at(s).gebaeude.krankenhaus._.size() - 1 ).zeit_betreten.pause = 60000;

                spieler.at(s).gebaeude.krankenhaus._.at( spieler.at(s).gebaeude.krankenhaus._.size() - 1 ).ende_pos.x = spieler.at(s).gebaeude.krankenhaus._.at( spieler.at(s).gebaeude.krankenhaus._.size() - 1 ).start_pos.x + 8;
                spieler.at(s).gebaeude.krankenhaus._.at( spieler.at(s).gebaeude.krankenhaus._.size() - 1 ).ende_pos.y = spieler.at(s).gebaeude.krankenhaus._.at( spieler.at(s).gebaeude.krankenhaus._.size() - 1 ).start_pos.y + 8;
            }

            else if(( spieler.at(s).menue_seite == 103 ) && ( spieler.at(s).gebaeude.geldlager.kosten <= spieler.at(s).geld ))
            {
                gebaeude_kaufen( spielfeld, spieler, spieler.at(s).gebaeude.geldlager, s );

                spieler.at(s).gebaeude.geldlager._.at( spieler.at(s).gebaeude.geldlager._.size() - 1 ).ende_pos.x = spieler.at(s).gebaeude.geldlager._.at( spieler.at(s).gebaeude.geldlager._.size() - 1 ).start_pos.x + 11;
                spieler.at(s).gebaeude.geldlager._.at( spieler.at(s).gebaeude.geldlager._.size() - 1 ).ende_pos.y = spieler.at(s).gebaeude.geldlager._.at( spieler.at(s).gebaeude.geldlager._.size() - 1 ).start_pos.y + 11;
            }

            else if(( spieler.at(s).menue_seite == 104 ) && ( spieler.at(s).gebaeude.mauer.kosten <= spieler.at(s).geld ))
            {
                gebaeude_kaufen( spielfeld, spieler, spieler.at(s).gebaeude.mauer, s );

                spieler.at(s).gebaeude.mauer._.at( spieler.at(s).gebaeude.mauer._.size() - 1 ).ende_pos.x = spieler.at(s).gebaeude.mauer._.at( spieler.at(s).gebaeude.mauer._.size() - 1 ).start_pos.x;
                spieler.at(s).gebaeude.mauer._.at( spieler.at(s).gebaeude.mauer._.size() - 1 ).ende_pos.y = spieler.at(s).gebaeude.mauer._.at( spieler.at(s).gebaeude.mauer._.size() - 1 ).start_pos.y;
            }

            else if(( spieler.at(s).menue_seite == 105 ) && ( spieler.at(s).gebaeude.teleporter.kosten <= spieler.at(s).geld ))
            {
                gebaeude_kaufen( spielfeld, spieler, spieler.at(s).gebaeude.teleporter, s );

                spieler.at(s).gebaeude.teleporter._.at( spieler.at(s).gebaeude.teleporter._.size() - 1 ).ende_pos.x = spieler.at(s).gebaeude.teleporter._.at( spieler.at(s).gebaeude.teleporter._.size() - 1 ).start_pos.x + 7;
                spieler.at(s).gebaeude.teleporter._.at( spieler.at(s).gebaeude.teleporter._.size() - 1 ).ende_pos.y = spieler.at(s).gebaeude.teleporter._.at( spieler.at(s).gebaeude.teleporter._.size() - 1 ).start_pos.y + 7;
            }

            else
            {
                spieler.at(s).menue_seite = spielfeld.seite_menue.at( spieler.at(s).menue_seite ).naechste_seite;
            }
        }

        gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 2 );
        cout << "SPIELERMENUE";

        if( spieler.at(s).menue_seite == 100 )
        {
            gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 3 );
            cout << "< " << spieler.at(s).gebaeude.zentrale.name << " >";

            gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 4 );
            cout << "Kosten: " << spieler.at(s).gebaeude.zentrale.kosten << " Euro\t";
        }

        else if( spieler.at(s).menue_seite == 101 )
        {
            gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 3 );
            cout << "< " << spieler.at(s).gebaeude.kanone.name << " >";

            gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 4 );
            cout << "Kosten: " << spieler.at(s).gebaeude.kanone.kosten << " Euro\t";
        }

        else if( spieler.at(s).menue_seite == 102 )
        {
            gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 3 );
            cout << "< " << spieler.at(s).gebaeude.krankenhaus.name << " >";

            gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 4 );
            cout << "Kosten: " << spieler.at(s).gebaeude.krankenhaus.kosten << " Euro\t";
        }

        else if( spieler.at(s).menue_seite == 103 )
        {
            gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 3 );
            cout << "< " << spieler.at(s).gebaeude.geldlager.name << " >";

            gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 4 );
            cout << "Kosten: " << spieler.at(s).gebaeude.geldlager.kosten << " Euro\t";
        }

        else if( spieler.at(s).menue_seite == 104 )
        {
            gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 3 );
            cout << "< " << spieler.at(s).gebaeude.mauer.name << " >";

            gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 4 );
            cout << "Kosten: " << spieler.at(s).gebaeude.mauer.kosten << " Euro\t";
        }

        else if( spieler.at(s).menue_seite == 105 )
        {
            gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 3 );
            cout << "< " << spieler.at(s).gebaeude.teleporter.name << " >";

            gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 4 );
            cout << "Kosten: " << spieler.at(s).gebaeude.teleporter.kosten << " Euro\t";
        }

        else
        {
            gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 3 );
            cout << "< " << spielfeld.seite_menue.at( spieler.at(s).menue_seite ).name << " >";
        }
    }

    spieler.at(s).schlange.richtung = ' ';
}

void menue_pause( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte, time_t t )
{
    system( "cls" );

    cout << "PAUSE\n"
         << "\n"
         << "1| ZURUECK ZUM SPIEL\n"
         << "2| SPIEL NEU STARTEN\n"
         << "3| HAUPTMENUE\n"
         << "4| CHEATS\n"
         << "5| EINSTELLUNGEN\n"
         << "0| SPIEL BEENDEN\n";

    switch( getch() )
    {
    case'1':
        spiel( spielfeld, spieler, punkte, t );
        break;

    case'4':
        menue_cheats( spielfeld, spieler, punkte, t );
        break;
    }
}


void menue_cheats( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte, time_t t )
{
    system( "cls" );

    if( spielfeld.cheats == true )
    {
        string cheat;

        cout << "CHEATS\n\n";
        cin >> cheat;

        if( cheat == "?" )
        {

        }

        else
        {
            cout << "falsche Eingabe!";
        }
    }

    else
    {
        cout << "CHEATS SIND DEAKTIVIERT!";
        Sleep( 800 );
    }

    spiel( spielfeld, spieler, punkte, t );
}


void leben( Spielfeld &spielfeld, vector <Spieler> &spieler, unsigned int s )
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(0));

    spieler.at(s).leben --;
    spieler.at(s).geld = 0;

    if( spieler.at(s).leben > 0 )
    {
        spieler.at(s).schlange.richtung = ' ';
        spieler.at(s).schlange.pos.at(0).x = spielfeld.groesse.x / spieler.size() * s + spielfeld.groesse.x / ( spieler.size() * 2 );
        spieler.at(s).schlange.pos.at(0).y = spielfeld.groesse.y / 2 + 1;
    }

    gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 6 );
    cout << spieler.at(s).leben;
    gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 5 );
    cout << spieler.at(s).geld << " EURO      ";
}

void gebaeude_gameover( Spielfeld &spielfeld, vector <Spieler> &spieler, Gebaeude_x &gebaeude, unsigned long long s, unsigned long long sp )
{
    for( unsigned int i = 0; i < gebaeude._.size(); i ++ )
    {
        if(( spieler.at(s).schlange.pos.at(0).x <= gebaeude._.at(i).ende_pos.x )
                && ( spieler.at(s).schlange.pos.at(0).y <= gebaeude._.at(i).ende_pos.y )
                && ( spieler.at(s).schlange.pos.at(0).x >= gebaeude._.at(i).start_pos.x )
                && ( spieler.at(s).schlange.pos.at(0).y >= gebaeude._.at(i).start_pos.y )
                && ( gebaeude._.at(i).gebaut == true )
                && ( gebaeude._.at(i).verschieben == false )
                && ( sp != s ))
        {
            spieler.at(sp).geld += spieler.at(s).geld;
            leben( spielfeld, spieler, s );
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(sp).farbe.at(0));
            gotoXY( spielfeld.groesse.x / spieler.size() * sp + 8, spielfeld.groesse.y + 5 );
            cout << spieler.at(sp).geld << " EURO      ";
        }
    }
}

bool gameover( Spielfeld &spielfeld, vector <Spieler> &spieler, vector <Punkt> &hindernis, unsigned int s )
{
    bool gameover = spieler.at(s).gameover;

    if(( spieler.at(s).schlange.waende == true )
    && (( spieler.at(s).schlange.pos.at(0).x == 0 )
    || ( spieler.at(s).schlange.pos.at(0).y == 0)
    || (spieler.at(s).schlange.pos.at(0).x == spielfeld.groesse.x + 1)
    || (spieler.at(s).schlange.pos.at(0).y == spielfeld.groesse.y + 1)))
    {
        leben( spielfeld, spieler, s );
    }

    for( unsigned int p = 0; p < hindernis.size(); p ++ )
    {
        if(( spieler.at(s).schlange.pos.at(0).x == hindernis.at(p).pos.x ) && ( spieler.at(s).schlange.pos.at(0).y == hindernis.at(p).pos.y ))
        {
            leben( spielfeld, spieler, s );
        }
    }

    for( unsigned int sp = 0; sp < spieler.size(); sp ++ )
    {
        for( unsigned int i = 0; i < spieler.at(sp).schlange.pos.size(); i ++ )
        {
            if(( spieler.at(s).schlange.pos.at(0).x == spieler.at(sp).schlange.pos.at(i).x ) && ( spieler.at(s).schlange.pos.at(0).y == spieler.at(sp).schlange.pos.at(i).y ) && ( sp != s ))
            {
                spieler.at(sp).geld += spieler.at(s).geld;
                leben( spielfeld, spieler, s );
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(sp).farbe.at(0));
                gotoXY( spielfeld.groesse.x / spieler.size() * sp + 8, spielfeld.groesse.y + 5 );
                cout << spieler.at(sp).geld << " EURO      ";
            }
        }

        for( unsigned int i = 0; i < spieler.at(s).schlange.pos.size(); i ++ )
        {
            for( unsigned int j = 0; j < spieler.at(sp).punkt.size(); j ++ )
            {
                if(( spieler.at(s).schlange.pos.at(i).x == spieler.at(sp).punkt.at(j).pos.x )
                && ( spieler.at(s).schlange.pos.at(i).y == spieler.at(sp).punkt.at(j).pos.y )
                && ( sp != s ))
                {
                    spieler.at(sp).geld += spieler.at(s).geld;
                    leben( spielfeld, spieler, s );
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(sp).farbe.at(0));
                    gotoXY( spielfeld.groesse.x / spieler.size() * sp + 8, spielfeld.groesse.y + 5 );
                    cout << spieler.at(sp).geld << " EURO      ";
                }
            }
        }

        gebaeude_gameover( spielfeld, spieler, spieler.at(sp).gebaeude.kanone, s, sp );
        gebaeude_gameover( spielfeld, spieler, spieler.at(sp).gebaeude.krankenhaus, s, sp );
        gebaeude_gameover( spielfeld, spieler, spieler.at(sp).gebaeude.geldlager, s, sp );
        gebaeude_gameover( spielfeld, spieler, spieler.at(sp).gebaeude.mauer, s, sp );
        gebaeude_gameover( spielfeld, spieler, spieler.at(sp).gebaeude.teleporter, s, sp );
    }

    for( unsigned int i = 1; i < spieler.at(s).schlange.pos.size(); i ++ )
    {
        if(( spieler.at(s).schlange.pos.at(0).x == spieler.at(s).schlange.pos.at(i).x ) && ( spieler.at(s).schlange.pos.at(0).y == spieler.at(s).schlange.pos.at(i).y ))
        {
            leben( spielfeld, spieler, s );
        }
    }



    if( spieler.at(s).leben <= 0 )
    {
        gameover = true;
    }

    return gameover;
}


void farben()
{
    system( "cls" );

    for( unsigned int f = 0; f < 256; f ++ )
    {
        unsigned char z = f;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << f << '\t' << z << endl;
    }

    getch();
}


int main()
{
    char wiederholen = '2';

    system( "color 84" );

    Spielfeld spielfeld;
    Punkte punkte;
    vector <Spieler> spieler;

    time_t t;

    time(&t);
    srand(( unsigned int )t );

    do
    {

        if( wiederholen == '2' )
        {
            spieler.resize( eingaben( spielfeld, spieler ) );
        }

        punkte.essen.resize(1);
        for( unsigned int i = 0; i < punkte.essen.size(); i ++ )
        {
            punkte.essen.at(i).farbe = 240;
            punkte.essen.at(i).zeichen = 'o';
        }

        punkte.geld.resize(1);
        for( unsigned int i = 0; i < punkte.geld.size(); i ++ )
        {
            punkte.geld.at(i).farbe = 224;
            punkte.geld.at(i).zeichen = '$';
        }

        punkte.leben.resize(1);
        for( unsigned int i = 0; i < punkte.leben.size(); i ++ )
        {
            punkte.leben.at(i).farbe = 192;
            punkte.leben.at(i).zeichen = 197;
        }

        punkte.hindernis.resize(50);
        for( unsigned int i = 0; i < punkte.hindernis.size(); i ++ )
        {
            punkte.hindernis.at(i).farbe = 15;
            punkte.hindernis.at(i).zeichen = 'X';
        }

        for( unsigned int i = 0; i < spieler.size(); i ++ )
        {
            spieler.at(i).gebaeude.zentrale._.resize(1);
            spieler.at(i).gebaeude.zentrale.name = "Zentrale";
            spieler.at(i).gebaeude.zentrale.kosten = 10000;

            spieler.at(i).gebaeude.kanone._.resize(0);
            spieler.at(i).gebaeude.kanone.name = "Kanone";
            spieler.at(i).gebaeude.kanone.kosten = 1500;

            spieler.at(i).gebaeude.krankenhaus._.resize(0);
            spieler.at(i).gebaeude.krankenhaus.name = "Krankenhaus";
            spieler.at(i).gebaeude.krankenhaus.kosten = 3000;

            spieler.at(i).gebaeude.geldlager._.resize(0);
            spieler.at(i).gebaeude.geldlager.name = "Geldlager";
            spieler.at(i).gebaeude.geldlager.kosten = 200;

            spieler.at(i).gebaeude.mauer._.resize(0);
            spieler.at(i).gebaeude.mauer.name = "Mauer";
            spieler.at(i).gebaeude.mauer.kosten = 20;

            spieler.at(i).gebaeude.teleporter._.resize(0);
            spieler.at(i).gebaeude.teleporter.name = "Teleporter";
            spieler.at(i).gebaeude.teleporter.kosten = 1000;
        }


        spielfeld.seite_menue.resize(1000);

        spielfeld.seite_menue.at(0).name = "SHOP";
        spielfeld.seite_menue.at(0).naechste_seite = 10;

        spielfeld.seite_menue.at(1).name = "";

        spielfeld.seite_menue.at(2).name = "";

        spielfeld.seite_menue.at(3).name = "";

        spielfeld.seite_menue.at(10).name = "GEBAEUDE";
        spielfeld.seite_menue.at(10).naechste_seite = 100;

        ifstream datei( "spieler.txt" );

        for( unsigned int i = 0; i < spieler.size(); i ++ )
        {
            unsigned int farben;

            datei >> spieler.at(i).name

                  >> spieler.at(i).tasten.oben
                  >> spieler.at(i).tasten.unten
                  >> spieler.at(i).tasten.links
                  >> spieler.at(i).tasten.rechts

                  >> spieler.at(i).tasten.oben_links
                  >> spieler.at(i).tasten.oben_rechts
                  >> spieler.at(i).tasten.unten_links
                  >> spieler.at(i).tasten.unten_rechts

                  >> spieler.at(i).tasten.menue

                  >> farben;

            spieler.at(i).farbe.resize( farben );

            for( unsigned int f = 0; f < spieler.at(i).farbe.size(); f ++ )
            {
                datei >> spieler.at(i).farbe.at(f);
            }
        }

        if( spieler.size() >= 1 )
        {
            spieler.at(0).gebaeude.zentrale._.at(0).start_pos.x = 1;
            spieler.at(0).gebaeude.zentrale._.at(0).start_pos.y = 1;
            spieler.at(0).gebaeude.zentrale._.at(0).ende_pos.x = 20;
            spieler.at(0).gebaeude.zentrale._.at(0).ende_pos.y = 20;
        }

        if( spieler.size() >= 2 )
        {
            spieler.at(1).gebaeude.zentrale._.at(0).start_pos.x = spielfeld.groesse.x - 19;
            spieler.at(1).gebaeude.zentrale._.at(0).start_pos.y = 1;
            spieler.at(1).gebaeude.zentrale._.at(0).ende_pos.x = spielfeld.groesse.x;
            spieler.at(1).gebaeude.zentrale._.at(0).ende_pos.y = 20;
        }

        if( spieler.size() >= 3 )
        {
            spieler.at(2).gebaeude.zentrale._.at(0).start_pos.x = 1;
            spieler.at(2).gebaeude.zentrale._.at(0).start_pos.y = spielfeld.groesse.y - 19;
            spieler.at(2).gebaeude.zentrale._.at(0).ende_pos.x = 20;
            spieler.at(2).gebaeude.zentrale._.at(0).ende_pos.y = spielfeld.groesse.y;
        }

        if( spieler.size() >= 4 )
        {
            spieler.at(3).gebaeude.zentrale._.at(0).start_pos.x = spielfeld.groesse.x - 19;
            spieler.at(3).gebaeude.zentrale._.at(0).start_pos.y = spielfeld.groesse.y - 19;
            spieler.at(3).gebaeude.zentrale._.at(0).ende_pos.x = spielfeld.groesse.x;
            spieler.at(3).gebaeude.zentrale._.at(0).ende_pos.y = spielfeld.groesse.y;
        }

        if( spieler.size() >= 5 )
        {
            for( unsigned int i = 4; i < spieler.size(); i ++ )
            {
                spieler.at(i).computer = true;

                spieler.at(i).name = "SPIELER";
                spieler.at(i).farbe.resize(2);
                spieler.at(i).farbe.at(0) = 200;
                spieler.at(i).farbe.at(1) = 280;

                spieler.at(i).tasten.oben = 'W';
                spieler.at(i).tasten.unten = 'S';
                spieler.at(i).tasten.links = 'A';
                spieler.at(i).tasten.rechts = 'D';

                spieler.at(i).tasten.oben_links = 'Q';
                spieler.at(i).tasten.oben_rechts = 'E';
                spieler.at(i).tasten.unten_links = 'Y';
                spieler.at(i).tasten.unten_rechts = 'C';

                spieler.at(i).tasten.menue = 'X';
            }
        }

        for( unsigned int i = 0; i < spieler.size(); i ++ )
        {
            spieler.at(i).punkte = 0;
            spieler.at(i).leben = 3;
            spieler.at(i).geld = 10000;
            spieler.at(i).menue_seite = 0;
            spieler.at(i).gameover = false;

            spieler.at(i).schlange.pos.resize( 10 );
            spieler.at(i).schlange.richtung = ' ';

            spieler.at(i).schlange.pos.at(0).x = spielfeld.groesse.x / spieler.size() * i + spielfeld.groesse.x / ( spieler.size() * 2 );
            spieler.at(i).schlange.pos.at(0).y = spielfeld.groesse.y / 2 + 1;

            spieler.at(i).gebaeude.zentrale._.at(0).gebaut = true;

            spieler.at(i).punkt.resize(0);

            spieler.at(i).schlange.zeit.pause = 50;
        }

        punkte_erstellen( punkte.essen, spielfeld, spieler, t );
        punkte_erstellen( punkte.hindernis, spielfeld, spieler, t );

        spiel( spielfeld, spieler, punkte, t );



        system( "cls" );
        cout << "SPIELENDE";

        Spielfeld spielende;
        spielende.groesse.x = 20 * spieler.size();
        spielende.groesse.y = 0;

        for( unsigned int s = 0; s < spieler.size(); s ++ )
        {
            spieler_informationen( spielende, spieler, s );
        }

        cout << endl
             << endl
             << "1| WIEDERHOLEN\n"
             << "2| NEUES SPIEL\n"
             << "0| BEENDEN\n";

        wiederholen = getch();
    }
    while(( wiederholen == '1' ) || ( wiederholen == '2' ));


    return 0;
}
