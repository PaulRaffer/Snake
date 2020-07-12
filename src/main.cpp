#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <display.h>
#include <stdlib.h>
#include <time.h>


using namespace std;



typedef struct
{
    string name;

    char
    richtung = 'x',
    richtung_alt;

    int
    laenge = 10,
    punkte = 0,
    leben = 3,
    geld = 500;

    vector <float> farbe;

    bool
    cheats = true,
    diagonal_fahren = false,
    waende = true,

    gameover = false;

} Informationen;

typedef struct
{
    int x;
    int y;

} Koordinaten;

typedef struct
{
    char
    still = 'x',

    oben = 'w',
    unten = 's',
    links = 'a',
    rechts = 'd',

    oben_links = 'q',
    oben_rechts = 'e',
    unten_links = 'y',
    unten_rechts = 'c',

    beenden = '0',
    menue_pause = '1',
    menue_shop = '2',
    menue_cheats = '3';

} Tasten;

typedef struct
{
    Koordinaten groesse;

    bool ton = false;

    int farbe_spielfeld = 600;
    int farbe_wand = 200;

} Spielfeld;

typedef struct
{
    Informationen informationen;
    vector <Koordinaten> position;
    Tasten tasten;

} Spieler;

typedef struct
{
    Koordinaten position;

} Essen;



void eingaben();

void spielfeld_erstellen( Spielfeld &spielfeld );
void essen_erstellen( Essen &essen, Spielfeld &spielfeld, Spieler &spieler );
void schlange_bewegen( Essen &essen, Spielfeld &spielfeld, Spieler &spieler, Spieler &gegner );

char spieler_bewegen( Essen &essen, Spielfeld &spielfeld, Spieler &spieler, Spieler &gegner );
void gegner_bewegen( Essen &essen, Spielfeld &spielfeld, Spieler &spieler, Spieler &gegner );
bool richtung_ueberpruefen( Spieler &spieler );

void menue_pause( Essen &essen, Spielfeld &spielfeld, Spieler &spieler, Spieler &gegner );
void menue_shop( Essen &essen, Spielfeld &spielfeld, Spieler &spieler, Spieler &gegner );
void menue_cheats( Essen &essen, Spielfeld &spielfeld, Spieler &spieler, Spieler &gegner );

void einstellungen( Essen &essen, Spielfeld &spielfeld, Spieler &spieler, Spieler &gegner );

bool gameover( Spielfeld &spielfeld, Spieler &spieler, Spieler &gegner );

void spiel( Essen &essen, Spielfeld &spielfeld, Spieler &spieler, Spieler &gegner );



void eingaben( Spielfeld &spielfeld, Spieler &spieler, Spieler &gegner )
{
    cout << "Spielfeldgroesse:";

    cout << "\nX: ";
    cin >> spielfeld.groesse.x;
    spieler.position.at(0).x = spielfeld.groesse.x / 2 + 1;

    cout << "Y: ";
    cin >> spielfeld.groesse.y;
    spieler.position.at(0).y = spielfeld.groesse.y / 2 + 1;

    gegner.position.at(0).x = 10;
    gegner.position.at(0).y = 10;
}

void spielfeld_erstellen( Spielfeld &spielfeld )
{
    int x, y;

    system("cls");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe_wand);
    for(x = 0; x <= spielfeld.groesse.x + 1; x ++)
    {
        cout << '+';
    }
    cout << '\n';

    for(y = 1; y <= spielfeld.groesse.y; y ++)
    {
        cout << '+';

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe_spielfeld);
        for(x = 1; x <= spielfeld.groesse.x; x ++)
        {
            cout << ' ';
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe_wand);
        cout << "+\n";
    }

    for( x = 0; x <= spielfeld.groesse.x + 1; x ++ )
    {
        cout << '+';
    }
    cout << "\nPunkte:\t\t\t";
}

void essen_erstellen( Essen &essen, Spielfeld &spielfeld, Spieler &spieler )
{
    time_t t;

    bool wiederholen;

    time(&t);
    srand((unsigned int)t);

    do
    {
        wiederholen = false;

        essen.position.x = ( "%d ", rand() % spielfeld.groesse.x + 1 );
        essen.position.y = ( "%d ", rand() % spielfeld.groesse.y + 1 );

        for(int i; i < spieler.informationen.laenge; i++)
        {
            if(( essen.position.x == spieler.position.at(i).x ) && ( essen.position.y == spieler.position.at(i).y ))
            {
                wiederholen = true;
            }
        }
    }
    while( wiederholen == true );

    gotoXY(essen.position.x, essen.position.y);
    cout << 'x';
}

void schlange_bewegen( Essen &essen, Spielfeld &spielfeld, Spieler &spieler, Spieler &gegner )
{
    do
    {
        spieler.informationen.richtung = spieler_bewegen( essen, spielfeld, spieler, gegner );
        gegner_bewegen( essen, spielfeld, spieler, gegner );

        if((spieler.position.at(0).x == essen.position.x) && (spieler.position.at(0).y == essen.position.y))
        {
            spieler.informationen.punkte ++;
            gotoXY( 8, spielfeld.groesse.y + 2 );
            cout << spieler.informationen.punkte;

            spieler.informationen.laenge ++;
            spieler.position.resize( spieler.informationen.laenge );

            essen_erstellen( essen, spielfeld, spieler );
        }

        if((gegner.position.at(0).x == essen.position.x) && (gegner.position.at(0).y == essen.position.y))
        {
            gegner.informationen.punkte ++;
            gotoXY( 100, spielfeld.groesse.y + 2 );
            cout << gegner.informationen.punkte;

            gegner.informationen.laenge ++;
            gegner.position.resize( gegner.informationen.laenge );

            essen_erstellen( essen, spielfeld, gegner );
        }
    }
    while( gameover( spielfeld, spieler, gegner ) == false );
}

char spieler_bewegen( Essen &essen, Spielfeld &spielfeld, Spieler &spieler, Spieler &gegner )
{
    bool wiederholen;
    spieler.informationen.richtung_alt = spieler.informationen.richtung;

    for( int i = 0; i < spieler.informationen.laenge; i ++ )
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.informationen.farbe.at(i % spieler.informationen.farbe.size()));
        gotoXY( spieler.position.at(i).x, spieler.position.at(i).y );
        cout << ' ';
    }

    if( spielfeld.ton == true )
    {
        Beep(1350, 100);

    }

    else if( spielfeld.ton == false )
    {
        Sleep(100);
    }

    if(kbhit())
    {
        spieler.informationen.richtung = getch();
    }

    if( richtung_ueberpruefen( spieler ) == false )
    {
        spieler.informationen.richtung = spieler.informationen.richtung_alt;
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe_spielfeld);
    gotoXY(spieler.position.at(spieler.informationen.laenge - 1).x, spieler.position.at(spieler.informationen.laenge - 1).y);
    cout << ' ';

    for( int i = spieler.informationen.laenge - 1; i > 0; i -- )
    {
        spieler.position.at(i).x = spieler.position.at(i - 1).x;
        spieler.position.at(i).y = spieler.position.at(i - 1).y;
    }

    do
    {
        wiederholen = false;

        if( spieler.informationen.richtung == spieler.tasten.oben )
        {
            spieler.position.at(0).y --;
        }

        else if( spieler.informationen.richtung == spieler.tasten.unten )
        {
            spieler.position.at(0).y ++;
        }

        else if( spieler.informationen.richtung == spieler.tasten.links )
        {
            spieler.position.at(0).x --;
        }

        else if( spieler.informationen.richtung == spieler.tasten.rechts )
        {
            spieler.position.at(0).x ++;
        }

        else if(spieler.informationen.richtung == spieler.tasten.beenden)
        {
            return 0;
        }

        else if( spieler.informationen.richtung == spieler.tasten.menue_pause )
        {
            spieler.informationen.richtung = spieler.informationen.richtung_alt;
            menue_pause( essen, spielfeld, spieler, gegner );
        }

        else if( spieler.informationen.richtung == spieler.tasten.menue_shop )
        {
            spieler.informationen.richtung = spieler.informationen.richtung_alt;
            menue_shop( essen, spielfeld, spieler, gegner );
        }

        else if(( spieler.informationen.richtung == spieler.tasten.menue_cheats ))
        {
            spieler.informationen.richtung = spieler.informationen.richtung_alt;
            menue_cheats( essen, spielfeld, spieler, gegner );
        }

        else if( spieler.informationen.diagonal_fahren == true )
        {
            if( spieler.informationen.richtung == spieler.tasten.oben_links )
            {
                spieler.position.at(0).y --;
                spieler.position.at(0).x --;
            }

            else if( spieler.informationen.richtung == spieler.tasten.oben_rechts )
            {
                spieler.position.at(0).y --;
                spieler.position.at(0).x ++;
            }

            else if( spieler.informationen.richtung == spieler.tasten.unten_links )
            {
                spieler.position.at(0).y ++;
                spieler.position.at(0).x --;
            }

            else if( spieler.informationen.richtung == spieler.tasten.unten_rechts )
            {
                spieler.position.at(0).y ++;
                spieler.position.at(0).x ++;
            }

            else
            {
                do
                {
                    spieler.informationen.richtung = 'x';
                    wiederholen = true;
                    spieler.informationen.richtung = getch();
                }
                while( richtung_ueberpruefen( spieler ) == false);
            }
        }

        else
        {
            do
            {
                spieler.informationen.richtung = 'x';
                wiederholen = true;
                spieler.informationen.richtung = getch();
            }
            while( richtung_ueberpruefen( spieler ) == false );
        }

        if( spieler.informationen.waende == false )
        {
            if( spieler.position.at(0).y == 0)
            {
                spieler.position.at(0).y = spielfeld.groesse.y;
            }

            if( spieler.position.at(0).y == spielfeld.groesse.y + 1)
            {
                spieler.position.at(0).y = 1;
            }

            if( spieler.position.at(0).x == 0)
            {
                spieler.position.at(0).x = spielfeld.groesse.x;
            }

            if( spieler.position.at(0).x == spielfeld.groesse.x + 1)
            {
                spieler.position.at(0).x = 1;
            }
        }
    }
    while( wiederholen == true );

    return spieler.informationen.richtung;
}

bool richtung_ueberpruefen( Spieler &spieler )
{
    if(((spieler.informationen.richtung_alt == spieler.tasten.oben) && (spieler.informationen.richtung == spieler.tasten.unten))
    || ((spieler.informationen.richtung_alt == spieler.tasten.unten) && (spieler.informationen.richtung == spieler.tasten.oben))
    || ((spieler.informationen.richtung_alt == spieler.tasten.links) && (spieler.informationen.richtung == spieler.tasten.rechts))
    || ((spieler.informationen.richtung_alt == spieler.tasten.rechts) && (spieler.informationen.richtung == spieler.tasten.links))
    || ((spieler.informationen.richtung_alt == spieler.tasten.oben_links) && (spieler.informationen.richtung == spieler.tasten.unten_rechts))
    || ((spieler.informationen.richtung_alt == spieler.tasten.unten_rechts) && (spieler.informationen.richtung == spieler.tasten.oben_links))
    || ((spieler.informationen.richtung_alt == spieler.tasten.unten_links) && (spieler.informationen.richtung == spieler.tasten.oben_rechts))
    || ((spieler.informationen.richtung_alt == spieler.tasten.oben_rechts) && (spieler.informationen.richtung == spieler.tasten.unten_links)))
    {
        return false;
    }

    else
    {
        return true;
    }
}

void gegner_bewegen( Essen &essen, Spielfeld &spielfeld, Spieler &spieler, Spieler &gegner )
{
    for( int i = 0; i < gegner.informationen.laenge; i ++ )
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gegner.informationen.farbe.at(i % gegner.informationen.farbe.size()));
        gotoXY( gegner.position.at(i).x, gegner.position.at(i).y );
        cout << ' ';
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe_spielfeld);
    gotoXY(gegner.position.at(gegner.informationen.laenge - 1).x, gegner.position.at(gegner.informationen.laenge - 1).y);
    cout << ' ';

    for( int i = gegner.informationen.laenge - 1; i > 0; i -- )
    {
        gegner.position.at(i).x = gegner.position.at(i - 1).x;
        gegner.position.at(i).y = gegner.position.at(i - 1).y;
    }

    bool
    spieler_oben = false,
    spieler_unten = false,
    spieler_links = false,
    spieler_rechts = false;

    for( int i = 0; i < spieler.informationen.laenge; i ++ )
    {
        if(( gegner.position.at(0).y - 1 == spieler.position.at(i).y ) && ( gegner.position.at(0).x == spieler.position.at(i).x ))
        {
            spieler_oben = true;
        }

        if(( gegner.position.at(0).y + 1 == spieler.position.at(i).y ) && ( gegner.position.at(0).x == spieler.position.at(i).x ))
        {
            spieler_unten = true;
        }

        if(( gegner.position.at(0).x - 1 == spieler.position.at(i).x ) && ( gegner.position.at(0).y == spieler.position.at(i).y ))
        {
            spieler_links = true;
        }

        if(( gegner.position.at(0).x + 1 == spieler.position.at(i).x ) && ( gegner.position.at(0).y == spieler.position.at(i).y ))
        {
            spieler_rechts = true;
        }
    }


    if(( gegner.position.at(0).y > essen.position.y ) && ( gegner.informationen.richtung != 's' ))
    {
        gegner.position.at(0).y --;
        gegner.informationen.richtung = 'w';
    }

    else if(( gegner.position.at(0).y < essen.position.y ) && ( gegner.informationen.richtung != 'w' ))
    {
        gegner.position.at(0).y ++;
        gegner.informationen.richtung = 's';
    }

    else if(( gegner.position.at(0).x > essen.position.x ) && ( gegner.informationen.richtung != 'd' ))
    {
        gegner.position.at(0).x --;
        gegner.informationen.richtung = 'a';
    }

    else if(( gegner.position.at(0).x < essen.position.x ) && ( gegner.informationen.richtung != 'a' ))
    {
        gegner.position.at(0).x ++;
        gegner.informationen.richtung = 'd';
    }
}

void menue_pause( Essen &essen, Spielfeld &spielfeld, Spieler &spieler, Spieler &gegner )
{
    system("cls");

    cout << "PAUSE\n\n1| ZURUECK ZUM SPIEL\n2| SPIEL NEU STARTEN\n3| HAUPTMENUE\n4| SHOP\n5| CHEATS\n6| EINSTELLUNGEN\n0| SPIEL BEENDEN\n\n";
    /*
        PAUSE

        1| ZURUECK ZUM SPIEL
        2| SPIEL NEU STARTEN
        3| HAUPTMENUE
        4| SHOP
        5| CHEATS
        6| EINSTELLUNGEN
        0| SPIEL BEENDEN
    */

    switch( getch() )
    {
        case'1':
            spiel( essen, spielfeld, spieler, gegner );

        case'4':
            menue_shop( essen, spielfeld, spieler, gegner );

        case'5':
            menue_cheats( essen, spielfeld, spieler, gegner );

        case'6':
            einstellungen( essen, spielfeld, spieler, gegner );
    }
}

void menue_shop( Essen &essen, Spielfeld &spielfeld, Spieler &spieler, Spieler &gegner )
{
    cout << "SHOP\n\n";
}

void menue_cheats( Essen &essen, Spielfeld &spielfeld, Spieler &spieler, Spieler &gegner )
{
    system("cls");

    if( spieler.informationen.cheats == true )
    {
        string cheat;

        cout << "CHEATS\n\n";
        cin >> cheat;

        if( cheat == "beenden" )
        {

        }

        else if( cheat == "teleportieren" )
        {
            cin >> spieler.position.at(0).x >> spieler.position.at(0).y;
        }

        else if( cheat == "richtung" )
        {
            cin >> spieler.informationen.richtung;
        }

        else if( cheat == "laenge" )
        {
            cin >> spieler.informationen.laenge;
            spieler.position.resize( spieler.informationen.laenge );
        }

        else if( cheat == "punkte" )
        {
            cin >> spieler.informationen.punkte;
        }

        else if( cheat == "geld" )
        {
            cin >> spieler.informationen.geld;
        }

        else if( cheat == "spielfeld" )
        {
            cin >> spielfeld.groesse.x >> spielfeld.groesse.y;
        }

        else
        {
            cout << cheat << " WURDE NICHT ERKANNT!";
            Sleep(800);
        }
    }

    else
    {
        cout << "CHEATS SIND DEAKTIVIERT!";
        Sleep(800);
    }

    spiel( essen, spielfeld, spieler, gegner );
}

void einstellungen( Essen &essen, Spielfeld &spielfeld, Spieler &spieler, Spieler &gegner )
{
    system("cls");

    cout << "EINSTELLUNGEN\n\nCHEATS\t\t" << spieler.informationen.cheats << "\nDIAGONAL FAHREN\t" << spieler.informationen.diagonal_fahren << "\nWAENDE\t\t" << spieler.informationen.waende;
    /*
        EINSTELLUNGEN

        CHEATS          1/0
        DIAGONAL FAHREN 1/0
        WAENDE          1/0
    */
}

bool gameover( Spielfeld &spielfeld, Spieler &spieler, Spieler &gegner )
{
    bool gameover = false;

    if( (spieler.informationen.waende == true) && ((spieler.position.at(0).x == 0) || (spieler.position.at(0).y == 0) || (spieler.position.at(0).x == spielfeld.groesse.x + 1) || (spieler.position.at(0).y == spielfeld.groesse.y + 1)) )
    {
        gameover = true;
    }

    for( int i = 0; i < gegner.informationen.laenge; i ++ )
    {
        if(( spieler.position.at(0).x == gegner.position.at(i).x ) && ( spieler.position.at(0).y == gegner.position.at(i).y ))
        {
            gameover = true;
        }
    }

    for(int i = 1; i < spieler.informationen.laenge; i ++)
    {
        if((spieler.position.at(0).x == spieler.position.at(i).x) && (spieler.position.at(0).y == spieler.position.at(i).y))
        {
            gameover = true;
        }
    }

return gameover;
}

void spiel( Essen &essen, Spielfeld &spielfeld, Spieler &spieler, Spieler &gegner )
{
    spielfeld_erstellen( spielfeld );

    essen_erstellen( essen, spielfeld, spieler );

    schlange_bewegen( essen, spielfeld, spieler, gegner );
}

int main()
{
    Spielfeld spielfeld;
    Spieler spieler;
    Spieler gegner;
    Essen essen;

    spieler.position.resize( spieler.informationen.laenge );
    gegner.position.resize( gegner.informationen.laenge );
    spieler.informationen.farbe.resize( 2 );
    gegner.informationen.farbe.resize( 2 );

    spieler.informationen.farbe.at(0) = 200;
    spieler.informationen.farbe.at(1) = 255;

    gegner.informationen.farbe.at(0) = 50;
    gegner.informationen.farbe.at(1) = 0;


    eingaben( spielfeld, spieler, gegner );

    spiel( essen, spielfeld, spieler, gegner );

    return 0;
}
