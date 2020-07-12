#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <display.h>
#include <stdlib.h>


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
    waende = false,

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
    int farbe = 450;

} Essen;



void eingaben();

void spielfeld_erstellen( Spielfeld &spielfeld );
void essen_erstellen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler );
void schlange_bewegen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner );

void spieler_bewegen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner );
void gegner_bewegen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner );
bool richtung_ueberpruefen( vector <Spieler> &spieler );

void menue_pause( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner );
void menue_shop( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner );
void menue_cheats( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner );

void einstellungen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner );

bool gameover( Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner );

void spiel( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner );



void eingaben( Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner )
{
    cout << "Spielfeldgroesse:";

    cout << "\nX: ";
    cin >> spielfeld.groesse.x;
    spieler.at(1).position.at(0).x = spielfeld.groesse.x / 2 + 1;
    spieler.at(2).position.at(0).x = spielfeld.groesse.x / 2 + 11;

    cout << "Y: ";
    cin >> spielfeld.groesse.y;
    spieler.at(1).position.at(0).y = spielfeld.groesse.y / 2 + 1;
    spieler.at(2).position.at(0).x = spielfeld.groesse.x / 2 + 11;

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

void essen_erstellen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler )
{
    bool wiederholen;

    do
    {
        wiederholen = false;

        essen.position.x = rand() % spielfeld.groesse.x + 1;
        essen.position.y = rand() % spielfeld.groesse.y + 1;

        for(int s = 0; s < spieler.size(); s ++)
        {
            for(int i; i < spieler.at(s).informationen.laenge; i++)
            {
                if((( essen.position.x == spieler.at(s).position.at(i).x ) && ( essen.position.y == spieler.at(s).position.at(i).y ))
                {
                    wiederholen = true;
                }
            }
        }
    }
    while( wiederholen == true );

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), essen.farbe);
    gotoXY(essen.position.x, essen.position.y);
    cout << ' ';
}

void schlange_bewegen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner )
{
    do
    {
        spieler_bewegen( essen, spielfeld, spieler, gegner );
        gegner_bewegen( essen, spielfeld, spieler, gegner );

        if((spieler.at(1).position.at(0).x == essen.position.x) && (spieler.at(1).position.at(0).y == essen.position.y))
        {
            spieler.at(1).informationen.punkte ++;
            gotoXY( 8, spielfeld.groesse.y + 2 );
            cout << spieler.at(1).informationen.punkte;

            spieler.at(1).informationen.laenge ++;
            spieler.at(1).position.resize( spieler.at(1).informationen.laenge );

            essen_erstellen( essen, spielfeld, spieler );
        }

        if((gegner.position.at(0).x == essen.position.x) && (gegner.position.at(0).y == essen.position.y))
        {
            gegner.informationen.punkte ++;
            gotoXY( 100, spielfeld.groesse.y + 2 );
            cout << gegner.informationen.punkte;

            gegner.informationen.laenge ++;
            gegner.position.resize( gegner.informationen.laenge );

            essen_erstellen( essen, spielfeld, spieler );
        }
    }
    while( gameover( spielfeld, spieler, gegner ) == false );
}

void spieler_bewegen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner )
{

    for( int s = 0; s < spieler.size(); s ++ )
    {
        bool wiederholen;
        spieler.at(1).informationen.richtung_alt = spieler.at(1).informationen.richtung;

        for( int i = 0; i < spieler.at(1).informationen.laenge; i ++ )
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(1).informationen.farbe.at(i % spieler.at(1).informationen.farbe.size()));
            gotoXY( spieler.at(1).position.at(i).x, spieler.at(1).position.at(i).y );
            cout << ' ';
        }

        if( spielfeld.ton == true )
        {
            Beep(1350, 100);
        }

        else if( spielfeld.ton == false )
        {
            Sleep(100 / spieler.size());
        }

        if(kbhit())
        {
            spieler.at(1).informationen.richtung = getch();
        }

        if( richtung_ueberpruefen( spieler ) == false )
        {
            spieler.at(1).informationen.richtung = spieler.at(1).informationen.richtung_alt;
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe_spielfeld);
        gotoXY(spieler.at(1).position.at(spieler.at(1).informationen.laenge - 1).x, spieler.at(1).position.at(spieler.at(1).informationen.laenge - 1).y);
        cout << ' ';

        for( int i = spieler.at(1).informationen.laenge - 1; i > 0; i -- )
        {
            spieler.at(1).position.at(i).x = spieler.at(1).position.at(i - 1).x;
            spieler.at(1).position.at(i).y = spieler.at(1).position.at(i - 1).y;
        }

        do
        {
            wiederholen = false;

            if( spieler.at(1).informationen.richtung == spieler.at(1).tasten.oben )
            {
                spieler.at(1).position.at(0).y --;
            }

            else if( spieler.at(1).informationen.richtung == spieler.at(1).tasten.unten )
            {
                spieler.at(1).position.at(0).y ++;
            }

            else if( spieler.at(1).informationen.richtung == spieler.at(1).tasten.links )
            {
                spieler.at(1).position.at(0).x --;
            }

            else if( spieler.at(1).informationen.richtung == spieler.at(1).tasten.rechts )
            {
                spieler.at(1).position.at(0).x ++;
            }

            else if(spieler.at(1).informationen.richtung == spieler.at(1).tasten.beenden)
            {

            }

            else if( spieler.at(1).informationen.richtung == spieler.at(1).tasten.menue_pause )
            {
                spieler.at(1).informationen.richtung = spieler.at(1).informationen.richtung_alt;
                menue_pause( essen, spielfeld, spieler, gegner );
            }

            else if( spieler.at(1).informationen.richtung == spieler.at(1).tasten.menue_shop )
            {
                spieler.at(1).informationen.richtung = spieler.at(1).informationen.richtung_alt;
                menue_shop( essen, spielfeld, spieler, gegner );
            }

            else if(( spieler.at(1).informationen.richtung == spieler.at(1).tasten.menue_cheats ))
            {
                spieler.at(1).informationen.richtung = spieler.at(1).informationen.richtung_alt;
                menue_cheats( essen, spielfeld, spieler, gegner );
            }

            else if( spieler.at(1).informationen.diagonal_fahren == true )
            {
                if( spieler.at(1).informationen.richtung == spieler.at(1).tasten.oben_links )
                {
                    spieler.at(1).position.at(0).y --;
                    spieler.at(1).position.at(0).x --;
                }

                else if( spieler.at(1).informationen.richtung == spieler.at(1).tasten.oben_rechts )
                {
                    spieler.at(1).position.at(0).y --;
                    spieler.at(1).position.at(0).x ++;
                }

                else if( spieler.at(1).informationen.richtung == spieler.at(1).tasten.unten_links )
                {
                    spieler.at(1).position.at(0).y ++;
                    spieler.at(1).position.at(0).x --;
                }

                else if( spieler.at(1).informationen.richtung == spieler.at(1).tasten.unten_rechts )
                {
                    spieler.at(1).position.at(0).y ++;
                    spieler.at(1).position.at(0).x ++;
                }

                else
                {
                    do
                    {
                        spieler.at(1).informationen.richtung = 'x';
                        wiederholen = true;
                        spieler.at(1).informationen.richtung = getch();
                    }
                    while( richtung_ueberpruefen( spieler ) == false);
                }
            }

            else
            {
                do
                {
                    spieler.at(1).informationen.richtung = 'x';
                    wiederholen = true;
                    spieler.at(1).informationen.richtung = getch();
                }
                while( richtung_ueberpruefen( spieler ) == false );
            }

            if( spieler.at(1).informationen.waende == false )
            {
                if( spieler.at(1).position.at(0).y == 0)
                {
                    spieler.at(1).position.at(0).y = spielfeld.groesse.y;
                }

                if( spieler.at(1).position.at(0).y == spielfeld.groesse.y + 1)
                {
                    spieler.at(1).position.at(0).y = 1;
                }

                if( spieler.at(1).position.at(0).x == 0)
                {
                    spieler.at(1).position.at(0).x = spielfeld.groesse.x;
                }

                if( spieler.at(1).position.at(0).x == spielfeld.groesse.x + 1)
                {
                    spieler.at(1).position.at(0).x = 1;
                }
            }
        }
        while( wiederholen == true );
    }

}

bool richtung_ueberpruefen( vector <Spieler> &spieler )
{
    if(((spieler.at(1).informationen.richtung_alt == spieler.at(1).tasten.oben) && (spieler.at(1).informationen.richtung == spieler.at(1).tasten.unten))
    || ((spieler.at(1).informationen.richtung_alt == spieler.at(1).tasten.unten) && (spieler.at(1).informationen.richtung == spieler.at(1).tasten.oben))
    || ((spieler.at(1).informationen.richtung_alt == spieler.at(1).tasten.links) && (spieler.at(1).informationen.richtung == spieler.at(1).tasten.rechts))
    || ((spieler.at(1).informationen.richtung_alt == spieler.at(1).tasten.rechts) && (spieler.at(1).informationen.richtung == spieler.at(1).tasten.links))
    || ((spieler.at(1).informationen.richtung_alt == spieler.at(1).tasten.oben_links) && (spieler.at(1).informationen.richtung == spieler.at(1).tasten.unten_rechts))
    || ((spieler.at(1).informationen.richtung_alt == spieler.at(1).tasten.unten_rechts) && (spieler.at(1).informationen.richtung == spieler.at(1).tasten.oben_links))
    || ((spieler.at(1).informationen.richtung_alt == spieler.at(1).tasten.unten_links) && (spieler.at(1).informationen.richtung == spieler.at(1).tasten.oben_rechts))
    || ((spieler.at(1).informationen.richtung_alt == spieler.at(1).tasten.oben_rechts) && (spieler.at(1).informationen.richtung == spieler.at(1).tasten.unten_links)))
    {
        return false;
    }

    else
    {
        return true;
    }
}

void gegner_bewegen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner )
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

void menue_pause( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner )
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

void menue_shop( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner )
{
    cout << "SHOP\n\n";
}

void menue_cheats( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner )
{
    system("cls");

    if( spieler.at(1).informationen.cheats == true )
    {
        string cheat;

        cout << "CHEATS\n\n";
        cin >> cheat;

        if( cheat == "spieler" )
        {
            cin >> cheat;

            if( cheat == "name" )
            {
                cin >> spieler.at(1).informationen.name;
            }



            else if( cheat == "cheats" )
            {
                cin >> spieler.at(1).informationen.cheats;
            }

            else if( cheat == "diagonal_fahren" )
            {
                cin >> spieler.at(1).informationen.diagonal_fahren;
            }

            else if( cheat == "waende" )
            {
                cin >> spieler.at(1).informationen.waende;
            }



            else if( cheat == "laenge" )
            {
                cin >> spieler.at(1).informationen.laenge;
                spieler.at(1).position.resize( spieler.at(1).informationen.laenge );
            }

            else if( cheat == "richtung" )
            {
                cin >> spieler.at(1).informationen.richtung;
            }

            else if( cheat == "teleportieren" )
            {
                cin >> spieler.at(1).position.at(0).x >> spieler.at(1).position.at(0).y;
            }



            else if( cheat == "punkte" )
            {
                cin >> spieler.at(1).informationen.punkte;
            }

            else if( cheat == "geld" )
            {
                cin >> spieler.at(1).informationen.geld;
            }
        }

        else if( cheat == "spielfeld" )
        {
            cin >> cheat;

            if( cheat == "groesse" )
            {
                cin >> spielfeld.groesse.x >> spielfeld.groesse.y;
            }

            else if( cheat == "farbe" )
            {
                cin >> cheat;

                if( cheat == "spielfeld" )
                {
                    cin >> spielfeld.farbe_spielfeld;
                }

                else if( cheat == "wand" )
                {
                    cin >> spielfeld.farbe_wand;
                }
            }

            else if( cheat == "ton" )
            {
                cin >> spielfeld.ton;
            }
        }

        else
        {
            cout << "falsche Eingebe!";
        }
    }

    else
    {
        cout << "CHEATS SIND DEAKTIVIERT!";
        Sleep(800);
    }

    spiel( essen, spielfeld, spieler, gegner );
}

void einstellungen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner )
{
    system("cls");

    cout << "EINSTELLUNGEN\n\nCHEATS\t\t" << spieler.at(1).informationen.cheats << "\nDIAGONAL FAHREN\t" << spieler.at(1).informationen.diagonal_fahren << "\nWAENDE\t\t" << spieler.at(1).informationen.waende;
    /*
        EINSTELLUNGEN

        CHEATS          1/0
        DIAGONAL FAHREN 1/0
        WAENDE          1/0
    */
}

bool gameover( Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner )
{
    bool gameover = false;

    if( (spieler.at(1).informationen.waende == true) && ((spieler.at(1).position.at(0).x == 0) || (spieler.at(1).position.at(0).y == 0) || (spieler.at(1).position.at(0).x == spielfeld.groesse.x + 1) || (spieler.at(1).position.at(0).y == spielfeld.groesse.y + 1)) )
    {
        gameover = true;
    }

    for( int i = 0; i < gegner.informationen.laenge; i ++ )
    {
        if(( spieler.at(1).position.at(0).x == gegner.position.at(i).x ) && ( spieler.at(1).position.at(0).y == gegner.position.at(i).y ))
        {
            gameover = true;
        }
    }

    for(int i = 1; i < spieler.at(1).informationen.laenge; i ++)
    {
        if((spieler.at(1).position.at(0).x == spieler.at(1).position.at(i).x) && (spieler.at(1).position.at(0).y == spieler.at(1).position.at(i).y))
        {
            gameover = true;
        }
    }

return gameover;
}

void spiel( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner )
{
    spielfeld_erstellen( spielfeld );

    essen_erstellen( essen, spielfeld, spieler );

    schlange_bewegen( essen, spielfeld, spieler, gegner );
}

int main()
{
    Spielfeld spielfeld;
    vector <Spieler> spieler;
    Spieler gegner;
    Essen essen;


    spieler.resize( 2 );

    spieler.at(1).position.resize( spieler.at(1).informationen.laenge );
    spieler.at(1).informationen.farbe.resize( 2 );
    spieler.at(1).informationen.farbe.at(0) = 200;
    spieler.at(1).informationen.farbe.at(1) = 255;

    /*spieler.at(2).position.resize( spieler.at(2).informationen.laenge );
    spieler.at(2).informationen.farbe.resize( 2 );
    spieler.at(2).informationen.farbe.at(0) = 0;
    spieler.at(2).informationen.farbe.at(1) = 255;*/

    gegner.position.resize( gegner.informationen.laenge );
    gegner.informationen.farbe.resize( 2 );
    gegner.informationen.farbe.at(0) = 50;
    gegner.informationen.farbe.at(1) = 0;


    eingaben( spielfeld, spieler, gegner );

    spiel( essen, spielfeld, spieler, gegner );

    return 0;
}
