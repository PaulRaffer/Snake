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
    name_anzeigen = true;

    Zeitmessung zeit;

} Schlange;

typedef struct
{
    string
    name,
    info;

    bool
    gebaut = false,
    verschieben = false,
    betreten = false;

    Koordinaten
    start_pos,
    ende_pos;

    int
    reichweite,
    kosten,
    level,
    farbe,
    zahl;

    char
    richtung;

    Zeitmessung zeit;

} Gebaeude;

typedef struct
{
    Koordinaten pos;
    char richtung;
    unsigned int farbe;

} Punkt;

typedef struct
{
    string name;

    int
    punkte,
    leben,
    geld,
    menue_seite;

    bool
    computer = false,
    gameover = false;

    vector <unsigned int> farbe;

    Schlange schlange;
    vector <Gebaeude> gebaeude;
    Tasten tasten;

    vector <Punkt> punkt;
    Zeitmessung zeit;

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


void spiel( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte );


void spielfeld_erstellen( Spielfeld &spielfeld, vector <Spieler> &spieler );
void punkte_erstellen( vector <Punkt> &punkt, Spielfeld &spielfeld, vector <Spieler> &spieler );
void punkte_zeichnen( vector <Punkt> &punkt );
void gebaeude_zeichnen( vector <Spieler> &spieler, unsigned int s, unsigned int g );


void richtung( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte );
void richtung_spieler( char richtung, vector <Spieler> &spieler );
void richtung_computer( vector <Spieler> &spieler, Punkte &punkte );

void bewegen( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte, unsigned long long zaehler );
void spieler_bewegen( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte, unsigned long long zaehler, unsigned int s );
void gebaeude( vector <Spieler> &spieler, unsigned int s );
void punkte_bewegen( Spielfeld &spielfeld, vector <Spieler> &spieler, unsigned int s );

void spieler_informationen( Spielfeld spielfeld, vector <Spieler> spieler, unsigned int s );
void spieler_menue( Spielfeld &spielfeld, vector <Spieler> &spieler, unsigned int s );


void menue_pause( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte );
void menue_cheats( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte );


void leben( Spielfeld &spielfeld, vector <Spieler> &spieler, unsigned int s );
bool gameover( Spielfeld &spielfeld, vector <Spieler> &spieler, vector <Punkt> &hindernis, unsigned int s );


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


void spiel( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte )
{
    bool wiederholen = true;

    spielfeld_erstellen( spielfeld, spieler );

    for( unsigned int s = 0; s < spieler.size(); s ++ )
    {
        for( unsigned int g = 0; g < spieler.at(s).gebaeude.size(); g ++ )
        {
            if( spieler.at(s).gebaeude.at(g).gebaut == true )
                gebaeude_zeichnen( spieler, s, g );
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
        richtung( spielfeld, spieler, punkte );

        bewegen( spielfeld, spieler, punkte, zaehler );

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
    unsigned int x, y;

    system("cls");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe.wand);
    for( x = 0; x <= spielfeld.groesse.x + 1; x ++ )
    {
        cout << '+';
    }
    cout << '\n';

    for( y = 1; y <= spielfeld.groesse.y; y ++ )
    {
        cout << '+';

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe.spielfeld);
        for( x = 1; x <= spielfeld.groesse.x; x ++ )
        {
            cout << ' ';
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe.wand);
        cout << "+\n";
    }

    for( x = 0; x <= spielfeld.groesse.x + 1; x ++ )
    {
        cout << '+';
    }

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


void punkte_erstellen( vector <Punkt> &punkt, Spielfeld &spielfeld, vector <Spieler> &spieler )
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
        cout << ' ';
    }
}


void richtung( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte )
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
            menue_pause( spielfeld, spieler, punkte );
        }

        else if( richtung == spielfeld.menue_cheats )
        {
            menue_cheats( spielfeld, spieler, punkte );
        }

        richtung_spieler( richtung, spieler );
    }

    richtung_computer( spieler, punkte );
}


void gebaeude_zeichnen( vector <Spieler> &spieler, unsigned int s, unsigned int g )
{
    for( unsigned int y = spieler.at(s).gebaeude.at(g).start_pos.y; y <= spieler.at(s).gebaeude.at(g).ende_pos.y; y ++ )
    {


        gotoXY( spieler.at(s).gebaeude.at(g).start_pos.x, y );

        for( unsigned int x = spieler.at(s).gebaeude.at(g).start_pos.x; x <= spieler.at(s).gebaeude.at(g).ende_pos.x; x ++ )
        {
            if((( g == 3 ) && (( x == spieler.at(s).gebaeude.at(g).start_pos.x ) || ( x == spieler.at(s).gebaeude.at(g).ende_pos.x ) || ( y == spieler.at(s).gebaeude.at(g).start_pos.y ) || ( y == spieler.at(s).gebaeude.at(g).ende_pos.y )))
            || (( g == 2) && (( x - spieler.at(s).gebaeude.at(g).start_pos.x == ( spieler.at(s).gebaeude.at(g).ende_pos.x - spieler.at(s).gebaeude.at(g).start_pos.x ) / 2 ) || ( y - spieler.at(s).gebaeude.at(g).start_pos.y == ( spieler.at(s).gebaeude.at(g).ende_pos.y - spieler.at(s).gebaeude.at(g).start_pos.y ) / 2 ))))
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
            if( spieler.at(sp).gebaeude.at(0).betreten == false )
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


void bewegen( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte, unsigned long long zaehler )
{
    for( unsigned int s = 0; s < spieler.size(); s ++ )
    {
        if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.menue )
        {
            for( unsigned int i = 0; i < spieler.at(s).gebaeude.size(); i ++ )
            {
                if(( spieler.at(s).gebaeude.at(i).gebaut == true )
                && ( spieler.at(s).gebaeude.at(i).verschieben == false )
                && ( spieler.at(s).gebaeude.at(i).betreten == false )
                && ( spieler.at(s).schlange.pos.at(0).x <= spieler.at(s).gebaeude.at(i).ende_pos.x )
                && ( spieler.at(s).schlange.pos.at(0).y <= spieler.at(s).gebaeude.at(i).ende_pos.y )
                && ( spieler.at(s).schlange.pos.at(0).x >= spieler.at(s).gebaeude.at(i).start_pos.x )
                && ( spieler.at(s).schlange.pos.at(0).y >= spieler.at(s).gebaeude.at(i).start_pos.y ))
                {
                    spieler.at(s).gebaeude.at(i).betreten = true;
                    spieler.at(s).gebaeude.at(i).zeit.start = clock();
                }

                else if( spieler.at(s).gebaeude.at(i).betreten == true )
                {
                    spieler.at(s).gebaeude.at(i).betreten = false;
                    spieler_informationen( spielfeld, spieler, s );
                }
            }

            spieler.at(s).schlange.richtung = spieler.at(s).schlange.richtung_alt;
        }

        else if( spieler.at(s).gebaeude.at(0).betreten == true )
        {
            spieler_menue( spielfeld, spieler, s );
            punkte_zeichnen( punkte.essen );
            punkte_zeichnen( punkte.geld );
            punkte_zeichnen( punkte.leben );
            punkte_zeichnen( punkte.hindernis );
        }

        else if( spieler.at(s).gebaeude.at(2).betreten == true )
        {
            spieler.at(s).gebaeude.at(2).zeit.ende = clock() - spieler.at(s).gebaeude.at(2).zeit.start;
            if( spieler.at(s).gebaeude.at(2).zeit.ende >= 40000 )
            {
                spieler.at(s).leben ++;
                spieler.at(s).gebaeude.at(2).zeit.start = clock();

                spieler_informationen( spielfeld, spieler, s );
                spieler.at(s).schlange.richtung = spieler.at(s).schlange.richtung_alt;
            }
        }

        else if( spieler.at(s).gebaeude.at(3).betreten == true )
        {
            if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.oben )
            {
                spieler.at(s).gebaeude.at(3).zahl += spieler.at(s).geld;
                spieler.at(s).geld = 0;
            }

            else if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.unten )
            {
                spieler.at(s).geld += spieler.at(s).gebaeude.at(3).zahl;
                spieler.at(s).gebaeude.at(3).zahl = 0;
            }

            spieler_informationen( spielfeld, spieler, s );
            spieler.at(s).schlange.richtung = spieler.at(s).schlange.richtung_alt;
        }

        else
        {
            spieler_bewegen( spielfeld, spieler, punkte, zaehler, s );
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
            punkte_erstellen( punkte.geld, spielfeld, spieler );
            punkte_zeichnen( punkte.geld );
        }
        else if( zufall == 1 )
        {
            punkte_erstellen( punkte.leben, spielfeld, spieler );
            punkte_zeichnen( punkte.leben );
        }
    }
}


void spieler_bewegen( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte, unsigned long long zaehler, unsigned int s )
{
    bool gebaeude = false;
    unsigned int sp;

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

        for( unsigned int i = 0; i < spieler.size(); i ++ )
        {
            for( unsigned int g = 0; g < spieler.at(s).gebaeude.size(); g ++ )
            {
                if(( spieler.at(s).schlange.pos.at( spieler.at(s).schlange.pos.size() - 1 ).x <= spieler.at(i).gebaeude.at(g).ende_pos.x )
                        && ( spieler.at(s).schlange.pos.at( spieler.at(s).schlange.pos.size() - 1 ).y <= spieler.at(i).gebaeude.at(g).ende_pos.y )
                        && ( spieler.at(s).schlange.pos.at( spieler.at(s).schlange.pos.size() - 1 ).x >= spieler.at(i).gebaeude.at(g).start_pos.x )
                        && ( spieler.at(s).schlange.pos.at( spieler.at(s).schlange.pos.size() - 1 ).y >= spieler.at(i).gebaeude.at(g).start_pos.y )
                        && ( spieler.at(i).gebaeude.at(g).gebaut == true ))
                {
                    gebaeude = true;
                    sp = i;
                }
            }
        }


        if( gebaeude == true )
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(sp).farbe.at(0) );
        }

        if( gebaeude == false )
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe.spielfeld);
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

        spieler.at(s).gameover = gameover( spielfeld, spieler, punkte.hindernis, s );

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
            cout << spieler.at(s).geld << " EURO";

            punkte_erstellen( punkte.essen, spielfeld, spieler );
            punkte_zeichnen( punkte.essen );
        }

        if(( spieler.at(s).schlange.pos.at(0).x == punkte.geld.at(0).pos.x ) && ( spieler.at(s).schlange.pos.at(0).y == punkte.geld.at(0).pos.y ))
        {
            spieler.at(s).geld += zaehler / 100;
            punkte.geld.at(0).pos.x = 0;
            punkte.geld.at(0).pos.y = 0;
            gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 5 );
            cout << spieler.at(s).geld << " EURO";
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
}


void gebaeude( vector <Spieler> &spieler, unsigned int s )
{
    spieler.at(s).gebaeude.at(1).zeit.ende = clock() - spieler.at(s).gebaeude.at(1).zeit.start;

    if(( spieler.at(s).gebaeude.at(1).gebaut == true ) && ( spieler.at(s).gebaeude.at(1).verschieben == false ) && ( spieler.at(s).gebaeude.at(1).zeit.ende >= 800 ))
    {
        spieler.at(s).gebaeude.at(1).zeit.start = clock();

        spieler.at(s).punkt.resize( spieler.at(s).punkt.size() + 1 );

        spieler.at(s).punkt.at( spieler.at(s).punkt.size() - 1 ).pos.x = ( spieler.at(s).gebaeude.at(1).start_pos.x + spieler.at(s).gebaeude.at(1).ende_pos.x ) / 2;
        spieler.at(s).punkt.at( spieler.at(s).punkt.size() - 1 ).pos.y = ( spieler.at(s).gebaeude.at(1).start_pos.y + spieler.at(s).gebaeude.at(1).ende_pos.y ) / 2;

        spieler.at(s).punkt.at( spieler.at(s).punkt.size() - 1 ).farbe = spieler.at(s).farbe.at(0);

        unsigned int zufall = rand() % 4;

        if( zufall == 0 )
        {
            spieler.at(s).punkt.at( spieler.at(s).punkt.size() - 1 ).richtung = spieler.at(s).tasten.oben;
        }

        else if( zufall == 1 )
        {
            spieler.at(s).punkt.at( spieler.at(s).punkt.size() - 1 ).richtung = spieler.at(s).tasten.unten;
        }

        else if( zufall == 2 )
        {
            spieler.at(s).punkt.at( spieler.at(s).punkt.size() - 1 ).richtung = spieler.at(s).tasten.links;
        }

        else if( zufall == 3 )
        {
            spieler.at(s).punkt.at( spieler.at(s).punkt.size() - 1 ).richtung = spieler.at(s).tasten.rechts;
        }
    }
}


void punkte_bewegen( Spielfeld &spielfeld, vector <Spieler> &spieler, unsigned int s )
{
    spieler.at(s).zeit.ende = clock() - spieler.at(s).zeit.start;

    if( spieler.at(s).zeit.ende >= 70 )
    {
        spieler.at(s).zeit.start = clock();

        for( unsigned int i = 0; i < spieler.at(s).punkt.size(); i ++ )
        {
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

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(0));
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

void spieler_menue( Spielfeld &spielfeld, vector <Spieler> &spieler, unsigned int s )
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(0));

    bool v = false;
    for( unsigned int i = 0; i < spieler.at(s).gebaeude.size(); i ++ )
    {
        if( spieler.at(s).gebaeude.at(i).verschieben == true )
        {
            v = true;

            for( unsigned int y = spieler.at(s).gebaeude.at(i).start_pos.y; y <= spieler.at(s).gebaeude.at(i).ende_pos.y; y ++ )
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe.spielfeld);
                gotoXY( spieler.at(s).gebaeude.at(i).start_pos.x, y );

                for( unsigned int x = spieler.at(s).gebaeude.at(i).start_pos.x; x <= spieler.at(s).gebaeude.at(i).ende_pos.x; x ++ )
                {
                    cout << ' ';
                }
            }

            if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.rechts )
            {
                spieler.at(s).gebaeude.at(i).start_pos.x ++;
                spieler.at(s).gebaeude.at(i).ende_pos.x ++;
            }

            else if ( spieler.at(s).schlange.richtung == spieler.at(s).tasten.links )
            {
                spieler.at(s).gebaeude.at(i).start_pos.x --;
                spieler.at(s).gebaeude.at(i).ende_pos.x --;
            }

            else if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.unten )
            {
                spieler.at(s).gebaeude.at(i).start_pos.y ++;
                spieler.at(s).gebaeude.at(i).ende_pos.y ++;
            }

            else if ( spieler.at(s).schlange.richtung == spieler.at(s).tasten.oben )
            {
                spieler.at(s).gebaeude.at(i).start_pos.y --;
                spieler.at(s).gebaeude.at(i).ende_pos.y --;
            }

            else if ( spieler.at(s).schlange.richtung == spieler.at(s).tasten.oben_rechts )
            {
                spieler.at(s).gebaeude.at(i).verschieben = false;
                v = false;
            }

            gebaeude_zeichnen( spieler, s, i);
        }
    }

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

        else if ( spieler.at(s).schlange.richtung == spieler.at(s).tasten.unten )
        {
            if( spieler.at(s).menue_seite >= 100 )
            {
                if(( spieler.at(s).geld >= spieler.at(s).gebaeude.at( spieler.at(s).menue_seite - 100 ).kosten )
                        || ( spieler.at(s).gebaeude.at( spieler.at(s).menue_seite - 100 ).gebaut == true ))
                {
                    spieler.at(s).geld -= spieler.at(s).gebaeude.at( spieler.at(s).menue_seite - 100 ).kosten;
                    spieler.at(s).gebaeude.at( spieler.at(s).menue_seite - 100 ).gebaut = true;
                    spieler.at(s).gebaeude.at( spieler.at(s).menue_seite - 100 ).verschieben = true;
                }
            }

            else
            {
                spieler.at(s).menue_seite = spielfeld.seite_menue.at( spieler.at(s).menue_seite ).naechste_seite;
            }
        }

        if( spieler.at(s).menue_seite == -1 )
        {
            spieler.at(s).menue_seite = 3;
        }

        if( spieler.at(s).menue_seite == 4 )
        {
            spieler.at(s).menue_seite = 0;
        }

        if( spieler.at(s).menue_seite == 99 )
        {
            spieler.at(s).menue_seite = spieler.at(s).gebaeude.size() + 99;
        }

        if( spieler.at(s).menue_seite == spieler.at(s).gebaeude.size() + 100 )
        {
            spieler.at(s).menue_seite = 100;
        }

        gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 2 );
        cout << "SPIELERMENUE     ";

        if(( spieler.at(s).menue_seite >= 100 ) && ( spieler.at(s).menue_seite < 109 ))
        {
            gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 3 );
            cout << "< " << spieler.at(s).gebaeude.at( spieler.at(s).menue_seite - 100 ).name << " >";

            gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 4 );
            cout << "KOSTEN: " << spieler.at(s).gebaeude.at( spieler.at(s).menue_seite - 100 ).kosten << " EURO      ";
        }

        else
        {
            gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 3 );
            cout << "< " << spielfeld.seite_menue.at( spieler.at(s).menue_seite ).name << " >";
        }
    }

    spieler.at(s).schlange.richtung = ' ';
}

void menue_pause( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte )
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
        spiel( spielfeld, spieler, punkte );
        break;

    case'4':
        menue_cheats( spielfeld, spieler, punkte );
        break;
    }
}


void menue_cheats( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte )
{
    system("cls");

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
        Sleep(800);
    }

    spiel( spielfeld, spieler, punkte );
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
                    spieler.at(sp).punkt.at(j).pos.x = 0;
                    spieler.at(sp).punkt.at(j).pos.y = 0;

                    spieler.at(sp).geld += spieler.at(s).geld;
                    leben( spielfeld, spieler, s );
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(sp).farbe.at(0));
                    gotoXY( spielfeld.groesse.x / spieler.size() * sp + 8, spielfeld.groesse.y + 5 );
                cout << spieler.at(sp).geld << " EURO      ";
                }
            }
        }

        for( unsigned int i = 1; i < spieler.at(sp).gebaeude.size(); i ++ )
        {
            if(( spieler.at(s).schlange.pos.at(0).x <= spieler.at(sp).gebaeude.at(i).ende_pos.x )
                    && ( spieler.at(s).schlange.pos.at(0).y <= spieler.at(sp).gebaeude.at(i).ende_pos.y )
                    && ( spieler.at(s).schlange.pos.at(0).x >= spieler.at(sp).gebaeude.at(i).start_pos.x )
                    && ( spieler.at(s).schlange.pos.at(0).y >= spieler.at(sp).gebaeude.at(i).start_pos.y )
                    && ( spieler.at(sp).gebaeude.at(i).gebaut == true )
                    && ( spieler.at(sp).gebaeude.at(i).verschieben == false )
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

    for( unsigned int i = 0; i < 256; i ++ )
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
        cout << i << endl;
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
        }

        punkte.geld.resize(1);
        for( unsigned int i = 0; i < punkte.geld.size(); i ++ )
        {
            punkte.geld.at(i).farbe = 224;
        }

        punkte.leben.resize(1);
        for( unsigned int i = 0; i < punkte.leben.size(); i ++ )
        {
            punkte.leben.at(i).farbe = 192;
        }

        punkte.hindernis.resize(50);
        for( unsigned int i = 0; i < punkte.hindernis.size(); i ++ )
        {
            punkte.hindernis.at(i).farbe = 0;
        }

        for( unsigned int i = 0; i < spieler.size(); i ++ )
        {
            spieler.at(i).gebaeude.resize(5);

            spieler.at(i).gebaeude.at(0).name = "BAUPLATZ         ";

            spieler.at(i).gebaeude.at(1).name = "KANONE           ";
            spieler.at(i).gebaeude.at(1).kosten = 1000;
            spieler.at(i).gebaeude.at(1).start_pos.x = spielfeld.groesse.x / 2;
            spieler.at(i).gebaeude.at(1).start_pos.y = spielfeld.groesse.y / 2;
            spieler.at(i).gebaeude.at(1).ende_pos.x = spieler.at(i).gebaeude.at(1).start_pos.x + 4;
            spieler.at(i).gebaeude.at(1).ende_pos.y = spieler.at(i).gebaeude.at(1).start_pos.y + 4;

            spieler.at(i).gebaeude.at(2).name = "KRANKENHAUS      ";
            spieler.at(i).gebaeude.at(2).kosten = 1500;
            spieler.at(i).gebaeude.at(2).start_pos.x = spielfeld.groesse.x / 2;
            spieler.at(i).gebaeude.at(2).start_pos.y = spielfeld.groesse.y / 2;
            spieler.at(i).gebaeude.at(2).ende_pos.x = spieler.at(i).gebaeude.at(2).start_pos.x + 9;
            spieler.at(i).gebaeude.at(2).ende_pos.y = spieler.at(i).gebaeude.at(2).start_pos.y + 9;

            spieler.at(i).gebaeude.at(3).name = "GELDLAGER        ";
            spieler.at(i).gebaeude.at(3).kosten = 1000;
            spieler.at(i).gebaeude.at(3).start_pos.x = spielfeld.groesse.x / 2;
            spieler.at(i).gebaeude.at(3).start_pos.y = spielfeld.groesse.y / 2;
            spieler.at(i).gebaeude.at(3).ende_pos.x = spieler.at(i).gebaeude.at(3).start_pos.x + 11;
            spieler.at(i).gebaeude.at(3).ende_pos.y = spieler.at(i).gebaeude.at(3).start_pos.y + 11;
        }


        spielfeld.seite_menue.resize(1000);

        spielfeld.seite_menue.at(0).name = "SHOP             ";
        spielfeld.seite_menue.at(0).naechste_seite = 10;

        spielfeld.seite_menue.at(1).name = "                 ";

        spielfeld.seite_menue.at(2).name = "                 ";

        spielfeld.seite_menue.at(3).name = "                 ";

        spielfeld.seite_menue.at(10).name = "GEBAEUDE         ";
        spielfeld.seite_menue.at(10).naechste_seite = 100;

        for( unsigned int i = 100; i < spieler.at(0).gebaeude.size(); i ++ )
        {
            spielfeld.seite_menue.at(100).naechste_seite = 1000;
        }

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
            datei >> spieler.at(i).farbe.at(0)
                  >> spieler.at(i).farbe.at(1);
        }

        if( spieler.size() >= 1 )
        {
            spieler.at(0).gebaeude.at(0).start_pos.x = 1;
            spieler.at(0).gebaeude.at(0).start_pos.y = 1;
            spieler.at(0).gebaeude.at(0).ende_pos.x = 30;
            spieler.at(0).gebaeude.at(0).ende_pos.y = 30;
        }

        if( spieler.size() >= 2 )
        {
            spieler.at(1).gebaeude.at(0).start_pos.x = spielfeld.groesse.x - 29;
            spieler.at(1).gebaeude.at(0).start_pos.y = 1;
            spieler.at(1).gebaeude.at(0).ende_pos.x = spielfeld.groesse.x;
            spieler.at(1).gebaeude.at(0).ende_pos.y = 30;
        }

        if( spieler.size() >= 3 )
        {
            spieler.at(2).gebaeude.at(0).start_pos.x = 1;
            spieler.at(2).gebaeude.at(0).start_pos.y = spielfeld.groesse.y - 29;
            spieler.at(2).gebaeude.at(0).ende_pos.x = 30;
            spieler.at(2).gebaeude.at(0).ende_pos.y = spielfeld.groesse.y;
        }

        if( spieler.size() >= 4 )
        {
            spieler.at(3).gebaeude.at(0).start_pos.x = spielfeld.groesse.x - 29;
            spieler.at(3).gebaeude.at(0).start_pos.y = spielfeld.groesse.y - 29;
            spieler.at(3).gebaeude.at(0).ende_pos.x = spielfeld.groesse.x;
            spieler.at(3).gebaeude.at(0).ende_pos.y = spielfeld.groesse.y;
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
            spieler.at(i).geld = 5000;
            spieler.at(i).menue_seite = 0;
            spieler.at(i).gameover = false;

            spieler.at(i).schlange.pos.resize( 10 );
            spieler.at(i).schlange.richtung = ' ';

            spieler.at(i).schlange.pos.at(0).x = spielfeld.groesse.x / spieler.size() * i + spielfeld.groesse.x / ( spieler.size() * 2 );
            spieler.at(i).schlange.pos.at(0).y = spielfeld.groesse.y / 2 + 1;

            spieler.at(i).gebaeude.at(0).gebaut = true;

            spieler.at(i).punkt.resize(0);

            spieler.at(i).schlange.zeit.pause = 50;
        }

        punkte_erstellen( punkte.essen, spielfeld, spieler );
        punkte_erstellen( punkte.hindernis, spielfeld, spieler );

        spiel( spielfeld, spieler, punkte );



        system( "cls" );
        cout << "SPIELENDE";

        Spielfeld spielende;
        spielende.groesse.x = 20 * spieler.size();
        spielende.groesse.y = 0;

        for( unsigned int s = 0; s < spieler.size(); s ++ )
        {
            spieler_informationen( spielende, spieler, s );
        }

        cout << endl << endl
             << "1| WIEDERHOLEN\n"
             << "2| NEUES SPIEL\n"
             << "0| BEENDEN\n";

        wiederholen = getch();
    }
    while(( wiederholen == '1' ) || ( wiederholen == '2' ));


    return 0;
}
