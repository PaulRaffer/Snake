#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <display.h>
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
    diagonal_fahren = true,
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
void essen_zeichnen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler );
void schlange_bewegen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner );

void spieler_bewegen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner );
void gegner_bewegen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner );
bool richtung_ueberpruefen( vector <Spieler> &spieler, int sp );

void menue_pause( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner );
void menue_shop( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner );
void menue_cheats( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner );

void einstellungen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner );

bool gameover( Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner, int &s );

void spiel( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner );



void eingaben( Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner )
{
    cout << "Spielfeldgroesse:";

    cout << "\nX: ";
    cin >> spielfeld.groesse.x;

    cout << "Y: ";
    cin >> spielfeld.groesse.y;

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
    cout << "\nPunkte: ";
}

void essen_erstellen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler )
{
    bool wiederholen;

    do
    {
        time_t t;

        wiederholen = false;

        time(&t);
        srand(( unsigned int )t );

        essen.position.x = ( "%d", rand() % spielfeld.groesse.x + 1 );
        essen.position.y = ( "%d", rand() % spielfeld.groesse.y + 1 );

        for( int s = 0; s < spieler.size(); s ++ )
        {
            for( int i; i < spieler.at(s).informationen.laenge; i ++ )
            {
                if(( essen.position.x == spieler.at(s).position.at(i).x ) && ( essen.position.y == spieler.at(s).position.at(i).y ))
                {
                    wiederholen = true;
                }
            }
        }
    }
    while( wiederholen == true );
}

void essen_zeichnen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler )
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), essen.farbe);
    gotoXY(essen.position.x, essen.position.y);
    cout << ' ';
}

void schlange_bewegen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner )
{
    bool wiederholen;

    do
    {
        if( spielfeld.ton == true )
        {
            Beep( 1350, 100 );
        }

        else if( spielfeld.ton == false )
        {
            Sleep( 100 );
        }

        int sp = 0;

        if( kbhit() )
        {
            spieler.at(sp).informationen.richtung_alt = spieler.at(sp).informationen.richtung;
            int richtung = getch();

            do
            {
                wiederholen = false;

                if(( richtung == spieler.at(sp).tasten.oben ) && ( spieler.at(sp).informationen.richtung_alt != spieler.at(sp).tasten.unten )
                || ( richtung == spieler.at(sp).tasten.unten ) && ( spieler.at(sp).informationen.richtung_alt != spieler.at(sp).tasten.oben )
                || ( richtung == spieler.at(sp).tasten.links ) && ( spieler.at(sp).informationen.richtung_alt != spieler.at(sp).tasten.rechts )
                || ( richtung == spieler.at(sp).tasten.rechts ) && ( spieler.at(sp).informationen.richtung_alt != spieler.at(sp).tasten.links )
                || ( richtung == spieler.at(sp).tasten.oben_links ) && ( spieler.at(sp).informationen.richtung_alt != spieler.at(sp).tasten.unten_rechts )
                || ( richtung == spieler.at(sp).tasten.oben_rechts ) && ( spieler.at(sp).informationen.richtung_alt != spieler.at(sp).tasten.unten_links )
                || ( richtung == spieler.at(sp).tasten.unten_links ) && ( spieler.at(sp).informationen.richtung_alt != spieler.at(sp).tasten.oben_rechts )
                || ( richtung == spieler.at(sp).tasten.unten_rechts ) && ( spieler.at(sp).informationen.richtung_alt != spieler.at(sp).tasten.oben_links )
                || ( richtung == spieler.at(sp).tasten.beenden )
                || ( richtung == spieler.at(sp).tasten.menue_pause )
                || ( richtung == spieler.at(sp).tasten.menue_shop )
                || ( richtung == spieler.at(sp).tasten.menue_cheats ))
                {
                    spieler.at(sp).informationen.richtung = richtung;
                }

                else
                {
                    sp ++;
                    if( sp >= spieler.size() )
                    {
                        spiel( essen, spielfeld, spieler, gegner );
                    }
                    wiederholen = true;
                }
            }
            while( wiederholen == true );
        }

        spieler_bewegen( essen, spielfeld, spieler, gegner );

        gegner_bewegen( essen, spielfeld, spieler, gegner );

        for( int s = 0; s < spieler.size(); s ++ )
        {
            if(( spieler.at(s).position.at(0).x == essen.position.x ) && ( spieler.at(s).position.at(0).y == essen.position.y ))
            {
                spieler.at(s).informationen.punkte ++;
                gotoXY( 8, spielfeld.groesse.y + 2 );
                cout << spieler.at(s).informationen.punkte;

                spieler.at(s).informationen.laenge ++;
                spieler.at(s).position.resize( spieler.at(s).informationen.laenge );

                essen_erstellen( essen, spielfeld, spieler );
                essen_zeichnen( essen, spielfeld, spieler );
            }
        }

        if(( gegner.position.at(0).x == essen.position.x ) && ( gegner.position.at(0).y == essen.position.y ))
        {
            gegner.informationen.punkte ++;
            gotoXY( 100, spielfeld.groesse.y + 2 );
            cout << gegner.informationen.punkte;

            gegner.informationen.laenge ++;
            gegner.position.resize( gegner.informationen.laenge );

            essen_erstellen( essen, spielfeld, spieler );
            essen_zeichnen( essen, spielfeld, spieler );
        }

        wiederholen = true;

        for( int i = 0; i < spieler.size(); i ++ )
        {
            if( spieler.at(i).informationen.gameover == true )
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
    while( wiederholen == true );
}

void spieler_bewegen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner )
{
    for( int s = 0; s < spieler.size(); s ++ )
    {
        if( spieler.at(s).informationen.gameover == false )
        {
            bool wiederholen;

            for( int i = 0; i < spieler.at(s).informationen.laenge; i ++ )
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).informationen.farbe.at(i % spieler.at(s).informationen.farbe.size()));
                gotoXY( spieler.at(s).position.at(i).x, spieler.at(s).position.at(i).y );
                cout << ' ';
            }

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe_spielfeld);
            gotoXY(spieler.at(s).position.at(spieler.at(s).informationen.laenge - 1).x, spieler.at(s).position.at(spieler.at(s).informationen.laenge - 1).y);
            cout << ' ';

            for( int i = spieler.at(s).informationen.laenge - 1; i > 0; i -- )
            {
                spieler.at(s).position.at(i).x = spieler.at(s).position.at(i - 1).x;
                spieler.at(s).position.at(i).y = spieler.at(s).position.at(i - 1).y;
            }

            do
            {
                wiederholen = false;

                if( spieler.at(s).informationen.richtung == spieler.at(s).tasten.oben )
                {
                    spieler.at(s).position.at(0).y --;
                }

                else if( spieler.at(s).informationen.richtung == spieler.at(s).tasten.unten )
                {
                    spieler.at(s).position.at(0).y ++;
                }

                else if( spieler.at(s).informationen.richtung == spieler.at(s).tasten.links )
                {
                    spieler.at(s).position.at(0).x --;
                }

                else if( spieler.at(s).informationen.richtung == spieler.at(s).tasten.rechts )
                {
                    spieler.at(s).position.at(0).x ++;
                }

                else if(spieler.at(s).informationen.richtung == spieler.at(s).tasten.beenden)
                {

                }

                else if( spieler.at(s).informationen.richtung == spieler.at(s).tasten.menue_pause )
                {
                    spieler.at(s).informationen.richtung = spieler.at(s).informationen.richtung_alt;
                    menue_pause( essen, spielfeld, spieler, gegner );
                }

                else if( spieler.at(s).informationen.richtung == spieler.at(s).tasten.menue_shop )
                {
                    spieler.at(s).informationen.richtung = spieler.at(s).informationen.richtung_alt;
                    menue_shop( essen, spielfeld, spieler, gegner );
                }

                else if(( spieler.at(s).informationen.richtung == spieler.at(s).tasten.menue_cheats ))
                {
                    spieler.at(s).informationen.richtung = spieler.at(s).informationen.richtung_alt;
                    menue_cheats( essen, spielfeld, spieler, gegner );
                }

                else if( spieler.at(s).informationen.diagonal_fahren == true )
                {
                    if( spieler.at(s).informationen.richtung == spieler.at(s).tasten.oben_links )
                    {
                        spieler.at(s).position.at(0).y --;
                        spieler.at(s).position.at(0).x --;
                    }

                    else if( spieler.at(s).informationen.richtung == spieler.at(s).tasten.oben_rechts )
                    {
                        spieler.at(s).position.at(0).y --;
                        spieler.at(s).position.at(0).x ++;
                    }

                    else if( spieler.at(s).informationen.richtung == spieler.at(s).tasten.unten_links )
                    {
                        spieler.at(s).position.at(0).y ++;
                        spieler.at(s).position.at(0).x --;
                    }

                    else if( spieler.at(s).informationen.richtung == spieler.at(s).tasten.unten_rechts )
                    {
                        spieler.at(s).position.at(0).y ++;
                        spieler.at(s).position.at(0).x ++;
                    }
                }

                if( spieler.at(s).informationen.waende == false )
                {
                    if( spieler.at(s).position.at(0).y == 0)
                    {
                        spieler.at(s).position.at(0).y = spielfeld.groesse.y;
                    }

                    if( spieler.at(s).position.at(0).y == spielfeld.groesse.y + 1)
                    {
                        spieler.at(s).position.at(0).y = 1;
                    }

                    if( spieler.at(s).position.at(0).x == 0)
                    {
                        spieler.at(s).position.at(0).x = spielfeld.groesse.x;
                    }

                    if( spieler.at(s).position.at(0).x == spielfeld.groesse.x + 1)
                    {
                        spieler.at(s).position.at(0).x = 1;
                    }
                }
            }
            while( wiederholen == true );

            spieler.at(s).informationen.gameover = gameover( spielfeld, spieler, gegner, s );
        }
    }

}

bool richtung_ueberpruefen( vector <Spieler> &spieler, int sp )
{
    if(((spieler.at(sp).informationen.richtung_alt == spieler.at(sp).tasten.oben) && (spieler.at(sp).informationen.richtung == spieler.at(sp).tasten.unten))
    || ((spieler.at(sp).informationen.richtung_alt == spieler.at(sp).tasten.unten) && (spieler.at(sp).informationen.richtung == spieler.at(sp).tasten.oben))
    || ((spieler.at(sp).informationen.richtung_alt == spieler.at(sp).tasten.links) && (spieler.at(sp).informationen.richtung == spieler.at(sp).tasten.rechts))
    || ((spieler.at(sp).informationen.richtung_alt == spieler.at(sp).tasten.rechts) && (spieler.at(sp).informationen.richtung == spieler.at(sp).tasten.links))
    || ((spieler.at(sp).informationen.richtung_alt == spieler.at(sp).tasten.oben_links) && (spieler.at(sp).informationen.richtung == spieler.at(sp).tasten.unten_rechts))
    || ((spieler.at(sp).informationen.richtung_alt == spieler.at(sp).tasten.unten_rechts) && (spieler.at(sp).informationen.richtung == spieler.at(sp).tasten.oben_links))
    || ((spieler.at(sp).informationen.richtung_alt == spieler.at(sp).tasten.unten_links) && (spieler.at(sp).informationen.richtung == spieler.at(sp).tasten.oben_rechts))
    || ((spieler.at(sp).informationen.richtung_alt == spieler.at(sp).tasten.oben_rechts) && (spieler.at(sp).informationen.richtung == spieler.at(sp).tasten.unten_links)))
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

    if( spieler.at(0).informationen.cheats == true )
    {
        string cheat;

        cout << "CHEATS\n\n";
        cin >> cheat;

        if( cheat == "spieler" )
        {
            cin >> cheat;

            if( cheat == "name" )
            {
                cin >> spieler.at(0).informationen.name;
            }



            else if( cheat == "cheats" )
            {
                cin >> spieler.at(0).informationen.cheats;
            }

            else if( cheat == "diagonal_fahren" )
            {
                cin >> spieler.at(0).informationen.diagonal_fahren;
            }

            else if( cheat == "waende" )
            {
                cin >> spieler.at(0).informationen.waende;
            }



            else if( cheat == "laenge" )
            {
                cin >> spieler.at(0).informationen.laenge;
                spieler.at(0).position.resize( spieler.at(0).informationen.laenge );
            }

            else if( cheat == "richtung" )
            {
                cin >> spieler.at(0).informationen.richtung;
            }

            else if( cheat == "teleportieren" )
            {
                cin >> spieler.at(0).position.at(0).x >> spieler.at(0).position.at(0).y;
            }



            else if( cheat == "punkte" )
            {
                cin >> spieler.at(0).informationen.punkte;
            }

            else if( cheat == "geld" )
            {
                cin >> spieler.at(0).informationen.geld;
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

    cout << "EINSTELLUNGEN\n\nCHEATS\t\t" << spieler.at(0).informationen.cheats << "\nDIAGONAL FAHREN\t" << spieler.at(0).informationen.diagonal_fahren << "\nWAENDE\t\t" << spieler.at(0).informationen.waende;
    /*
        EINSTELLUNGEN

        CHEATS          1/0
        DIAGONAL FAHREN 1/0
        WAENDE          1/0
    */
}

bool gameover( Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner, int &s )
{
    static int aufrufe = 0;

    bool gameover = spieler.at(s).informationen.gameover;

    if((spieler.at(s).informationen.waende == true) && ((spieler.at(s).position.at(0).x == 0) || (spieler.at(s).position.at(0).y == 0) || (spieler.at(s).position.at(0).x == spielfeld.groesse.x + 1) || (spieler.at(s).position.at(0).y == spielfeld.groesse.y + 1)))
    {
        gameover = true;
    }

    for( int i = 0; i < gegner.informationen.laenge; i ++ )
    {
        if(( spieler.at(s).position.at(0).x == gegner.position.at(i).x ) && ( spieler.at(s).position.at(0).y == gegner.position.at(i).y ))
        {
            gameover = true;
        }
    }

    for( int sp = 0; sp < spieler.size(); sp ++ )
    {
        for( int i = 0; i < spieler.at(sp).informationen.laenge; i ++ )
        {
            if(( spieler.at(s).position.at(0).x == spieler.at(sp).position.at(i).x ) && ( spieler.at(s).position.at(0).y == spieler.at(sp).position.at(i).y ) && ( s != sp ))
            {
                gameover = true;
            }
        }
    }



    /*for( int i = 1; i < spieler.at(0).informationen.laenge; i ++ )
    {
        if(( spieler.at(s).position.at(0).x == spieler.at(0).position.at(i).x ) && ( spieler.at(s).position.at(0).y == spieler.at(s).position.at(i).y ))
        {
            gameover = true;
        }
    }*/

    aufrufe ++;

return gameover;
}

void spiel( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler, Spieler &gegner )
{
    spielfeld_erstellen( spielfeld );

    essen_zeichnen( essen, spielfeld, spieler );

    schlange_bewegen( essen, spielfeld, spieler, gegner );
}

int main()
{
    Spielfeld spielfeld;
    vector <Spieler> spieler;
    Spieler gegner;
    Essen essen;


    spieler.resize( 4 );


    spieler.at(0).position.resize( spieler.at(0).informationen.laenge );
    spieler.at(0).informationen.farbe.resize( 2 );
    spieler.at(0).informationen.farbe.at(0) = 200;
    spieler.at(0).informationen.farbe.at(1) = 255;


    spieler.at(1).position.resize( spieler.at(1).informationen.laenge );
    spieler.at(1).informationen.farbe.resize( 2 );
    spieler.at(1).informationen.farbe.at(0) = 0;
    spieler.at(1).informationen.farbe.at(1) = 255;

    spieler.at(1).tasten.oben = 't';
    spieler.at(1).tasten.unten = 'g';
    spieler.at(1).tasten.links = 'f';
    spieler.at(1).tasten.rechts = 'h';

    spieler.at(1).tasten.oben_links = 'r';
    spieler.at(1).tasten.oben_rechts = 'z';
    spieler.at(1).tasten.unten_links = 'v';
    spieler.at(1).tasten.unten_rechts = 'n';


    spieler.at(2).position.resize( spieler.at(2).informationen.laenge );
    spieler.at(2).informationen.farbe.resize( 2 );
    spieler.at(2).informationen.farbe.at(0) = 50;
    spieler.at(2).informationen.farbe.at(1) = 100;

    spieler.at(2).tasten.oben = 'i';
    spieler.at(2).tasten.unten = 'k';
    spieler.at(2).tasten.links = 'j';
    spieler.at(2).tasten.rechts = 'l';

    spieler.at(2).tasten.oben_links = 'u';
    spieler.at(2).tasten.oben_rechts = 'o';
    spieler.at(2).tasten.unten_links = 'm';
    spieler.at(2).tasten.unten_rechts = '.';


    spieler.at(3).position.resize( spieler.at(3).informationen.laenge );
    spieler.at(3).informationen.farbe.resize( 2 );
    spieler.at(3).informationen.farbe.at(0) = 200;
    spieler.at(3).informationen.farbe.at(1) = 300;

    spieler.at(3).tasten.oben = '8';
    spieler.at(3).tasten.unten = '5';
    spieler.at(3).tasten.links = '4';
    spieler.at(3).tasten.rechts = '6';

    spieler.at(3).tasten.oben_links = '7';
    spieler.at(3).tasten.oben_rechts = '9';
    spieler.at(3).tasten.unten_links = '1';
    spieler.at(3).tasten.unten_rechts = '3';


    gegner.position.resize( gegner.informationen.laenge );
    gegner.informationen.farbe.resize( 2 );
    gegner.informationen.farbe.at(0) = 50;
    gegner.informationen.farbe.at(1) = 0;



    eingaben( spielfeld, spieler, gegner );

    for( int i = 0; i < spieler.size(); i ++ )
    {
        spieler.at(i).position.at(0).x = spielfeld.groesse.x / 2 + 10 * i + 1;
    }

    for( int i = 0; i < spieler.size(); i ++ )
    {
        spieler.at(i).position.at(0).y = spielfeld.groesse.y / 2 + 1;
    }

    essen_erstellen( essen, spielfeld, spieler );

    spiel( essen, spielfeld, spieler, gegner );

    return 0;
}
