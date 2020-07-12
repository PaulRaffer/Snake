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
    richtung,
    richtung_alt;

    int
    laenge = 10,
    punkte = 0,
    leben = 3,
    geld = 500;

    vector <float> farbe;

    bool
    computer = false,

    diagonal_fahren = true,
    waende = true,
    name_anzeigen = true,

    menue = false,

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
    still,

    oben,
    unten,
    links,
    rechts,

    oben_links,
    oben_rechts,
    unten_links,
    unten_rechts,

    menue_spieler;

} Tasten;

typedef struct
{
    Koordinaten groesse;

    bool
    cheats = false,
    ton = false;

    int
    farbe_spielfeld = 600,
    farbe_wand = 200;

    char
    beenden = '0',
    menue_pause = '1',
    menue_cheats = '3';

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



int eingaben( Spielfeld &spielfeld, vector <Spieler> &spieler );

void spielfeld_erstellen( Spielfeld &spielfeld, vector <Spieler> &spieler );
void essen_erstellen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler );
void essen_zeichnen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler );
void schlange_bewegen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler );

void spieler_bewegen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler );
void gegner_bewegen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler );

void menue_spieler( Spielfeld &spielfeld, vector <Spieler> &spieler, int s );
void menue_shop(  );

void menue_pause( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler );
void menue_cheats( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler );

void einstellungen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler );

bool gameover( Spielfeld &spielfeld, vector <Spieler> &spieler, int s );

void spiel( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler );



int eingaben( Spielfeld &spielfeld, vector <Spieler> &spieler )
{
    int s;

    cout << "ANZAHL DER SPIELER: ";
    cin >> s;

    cout << "SPIELFELDGROESSE:\nX: ";
    cin >> spielfeld.groesse.x;

    cout << "Y: ";
    cin >> spielfeld.groesse.y;

    return s;
}

void spielfeld_erstellen( Spielfeld &spielfeld, vector <Spieler> &spieler )
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

    int i;

    for( int sp = 0; sp < spieler.size(); sp ++ )
    {
        for( i = 0; i < spieler.at(sp).informationen.laenge; i ++ )
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(sp).informationen.farbe.at( i % spieler.at(sp).informationen.farbe.size() ));
            gotoXY( spieler.at(sp).position.at(i).x, spieler.at(sp).position.at(i).y );

            if(( spieler.at(sp).informationen.name_anzeigen == true ) && ( i < spieler.at(sp).informationen.name.size() ))
            {
                cout << spieler.at(sp).informationen.name.at(i);
            }

            else
            {
                cout << ' ';
            }
        }
    }
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

void schlange_bewegen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler)
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
            int richtung = getch();

            if( richtung == spielfeld.beenden)
            {

            }

            else if( richtung == spielfeld.menue_pause )
            {
                menue_pause( essen, spielfeld, spieler );
            }


            else if(( richtung == spielfeld.menue_cheats ))
            {
                menue_cheats( essen, spielfeld, spieler );
            }

            do
            {
                wiederholen = false;

                if(( richtung == spieler.at(sp).tasten.menue_spieler )
                || (( richtung == spieler.at(sp).tasten.oben ) && ( spieler.at(sp).informationen.richtung != spieler.at(sp).tasten.unten ))
                || (( richtung == spieler.at(sp).tasten.unten ) && ( spieler.at(sp).informationen.richtung != spieler.at(sp).tasten.oben ))
                || (( richtung == spieler.at(sp).tasten.links ) && ( spieler.at(sp).informationen.richtung != spieler.at(sp).tasten.rechts ))
                || (( richtung == spieler.at(sp).tasten.rechts ) && ( spieler.at(sp).informationen.richtung != spieler.at(sp).tasten.links ))
                || (( spieler.at(sp).informationen.diagonal_fahren == true ) && ( richtung == spieler.at(sp).tasten.oben_links ) && ( spieler.at(sp).informationen.richtung != spieler.at(sp).tasten.unten_rechts ))
                || (( spieler.at(sp).informationen.diagonal_fahren == true ) && ( richtung == spieler.at(sp).tasten.oben_rechts ) && ( spieler.at(sp).informationen.richtung != spieler.at(sp).tasten.unten_links ))
                || (( spieler.at(sp).informationen.diagonal_fahren == true ) && ( richtung == spieler.at(sp).tasten.unten_links ) && ( spieler.at(sp).informationen.richtung != spieler.at(sp).tasten.oben_rechts ))
                || (( spieler.at(sp).informationen.diagonal_fahren == true ) && ( richtung == spieler.at(sp).tasten.unten_rechts ) && ( spieler.at(sp).informationen.richtung != spieler.at(sp).tasten.oben_links )))
                {
                    spieler.at(sp).informationen.richtung_alt = spieler.at(sp).informationen.richtung;
                    spieler.at(sp).informationen.richtung = richtung;
                }

                else if( sp < spieler.size() - 1 )
                {
                    sp ++;
                    wiederholen = true;
                }
            }
            while( wiederholen == true );
        }


        for( int i = 0; i < spieler.size(); i ++ )
        {
            if( spieler.at(i).informationen.computer == true )
            {
                if(( essen.position.y < spieler.at(i).position.at(0).y ) && ( spieler.at(i).informationen.richtung != spieler.at(i).tasten.unten ))
                {
                    spieler.at(i).informationen.richtung = spieler.at(i).tasten.oben;
                }

                else if(( essen.position.y > spieler.at(i).position.at(0).y ) && ( spieler.at(i).informationen.richtung != spieler.at(i).tasten.oben ))
                {
                    spieler.at(i).informationen.richtung = spieler.at(i).tasten.unten;
                }

                else if(( essen.position.x < spieler.at(i).position.at(0).x ) && ( spieler.at(i).informationen.richtung != spieler.at(i).tasten.rechts ))
                {
                    spieler.at(i).informationen.richtung = spieler.at(i).tasten.links;
                }

                else if(( essen.position.x > spieler.at(i).position.at(0).x ) && ( spieler.at(i).informationen.richtung != spieler.at(i).tasten.links ))
                {
                    spieler.at(i).informationen.richtung = spieler.at(i).tasten.rechts;
                }
            }
        }

        spieler_bewegen( essen, spielfeld, spieler );


        for( int s = 0; s < spieler.size(); s ++ )
        {
            if(( spieler.at(s).position.at(0).x == essen.position.x ) && ( spieler.at(s).position.at(0).y == essen.position.y ))
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).informationen.farbe.at(0));

                spieler.at(s).informationen.punkte ++;
                gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 3 );
                cout << spieler.at(s).informationen.punkte;

                spieler.at(s).informationen.laenge ++;
                spieler.at(s).position.resize( spieler.at(s).informationen.laenge );
                gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 4 );
                cout << spieler.at(s).informationen.laenge;

                essen_erstellen( essen, spielfeld, spieler );
                essen_zeichnen( essen, spielfeld, spieler );
            }
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

void spieler_bewegen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler )
{
    for( int s = 0; s < spieler.size(); s ++ )
    {
        if( spieler.at(s).informationen.richtung == spieler.at(s).tasten.menue_spieler )
        {
            if( spieler.at(s).informationen.menue == false )
            {
                spieler.at(s).informationen.menue = true;
            }

            else if( spieler.at(s).informationen.menue == true )
            {
                spieler.at(s).informationen.menue = false;

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).informationen.farbe.at(0));
                gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 2 );
                cout << "NAME:   " << spieler.at(s).informationen.name;
                gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 3 );
                cout << "PUNKTE: " << spieler.at(s).informationen.punkte;
                gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 4 );
                cout << "LAENGE: " << spieler.at(s).informationen.laenge;
                gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 5 );
                cout << "GELD:   " << spieler.at(s).informationen.geld << " EURO";
                gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 6 );
                cout << "LEBEN:  " << spieler.at(s).informationen.leben;
            }

            spieler.at(s).informationen.richtung = spieler.at(s).informationen.richtung_alt;
        }

        if( spieler.at(s).informationen.gameover == false )
        {
            for( int i = 0; i < spieler.at(s).informationen.laenge; i ++ )
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).informationen.farbe.at( i % spieler.at(s).informationen.farbe.size() ));
                gotoXY( spieler.at(s).position.at(i).x, spieler.at(s).position.at(i).y );

                if(( spieler.at(s).informationen.name_anzeigen == true ) && ( i < spieler.at(s).informationen.name.size() ))
                {
                    cout << spieler.at(s).informationen.name.at(i);
                }

                else
                {
                    cout << ' ';
                }
            }

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe_spielfeld);
            gotoXY(spieler.at(s).position.at(spieler.at(s).informationen.laenge - 1).x, spieler.at(s).position.at(spieler.at(s).informationen.laenge - 1).y);
            cout << ' ';

            if( spieler.at(s).informationen.menue == false )
            {
                if( spieler.at(s).informationen.richtung != ' ' )
                {
                    for( int i = spieler.at(s).informationen.laenge - 1; i > 0; i -- )
                    {
                        spieler.at(s).position.at(i).x = spieler.at(s).position.at(i - 1).x;
                        spieler.at(s).position.at(i).y = spieler.at(s).position.at(i - 1).y;
                    }
                }

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

            else if( spieler.at(s).informationen.menue == true )
            {
                menue_spieler( spielfeld, spieler, s );
            }

            spieler.at(s).informationen.gameover = gameover( spielfeld, spieler,  s );
        }
    }
}



void menue_spieler( Spielfeld &spielfeld, vector <Spieler> &spieler, int s )
{
    gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 2 );
    cout << "SPIELERMENUE";

}

void menue_pause( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler )
{
    system("cls");

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
            spiel( essen, spielfeld, spieler );

        case'4':
            menue_cheats( essen, spielfeld, spieler );

        case'5':
            einstellungen( essen, spielfeld, spieler );
    }
}

void menue_shop(  )
{

}

void menue_cheats( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler )
{
    system("cls");

    if( spielfeld.cheats == true )
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

    spiel( essen, spielfeld, spieler );
}

void einstellungen( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler )
{

}

bool gameover( Spielfeld &spielfeld, vector <Spieler> &spieler, int s )
{
    bool gameover = spieler.at(s).informationen.gameover;

    if((spieler.at(s).informationen.waende == true) && ((spieler.at(s).position.at(0).x == 0) || (spieler.at(s).position.at(0).y == 0) || (spieler.at(s).position.at(0).x == spielfeld.groesse.x + 1) || (spieler.at(s).position.at(0).y == spielfeld.groesse.y + 1)))
    {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).informationen.farbe.at(0));

            spieler.at(s).informationen.leben --;

            if( spieler.at(s).informationen.leben > 0 )
            {
                spieler.at(s).position.at(0).x = spielfeld.groesse.x / 2 + 10 * s + 1;
                spieler.at(s).position.at(0).y = spielfeld.groesse.y / 2 + 1;
            }

            gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 6 );
            cout << spieler.at(s).informationen.leben;
    }

    for(int sp = 0; sp < spieler.size(); sp ++ )
    {
        for( int i = 0; i < spieler.at(sp).informationen.laenge; i ++ )
        {
            if(( spieler.at(s).position.at(0).x == spieler.at(sp).position.at(i).x ) && ( spieler.at(s).position.at(0).y == spieler.at(sp).position.at(i).y ) && ( sp != s ))
            {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).informationen.farbe.at(0));

            spieler.at(s).informationen.leben --;

            if( spieler.at(s).informationen.leben > 0 )
            {
                spieler.at(s).position.at(0).x = spielfeld.groesse.x / 2 + 10 * s + 1;
                spieler.at(s).position.at(0).y = spielfeld.groesse.y / 2 + 1;
            }

            gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 6 );
            cout << spieler.at(s).informationen.leben;
            }
        }
    }

    for( int i = 1; i < spieler.at(s).informationen.laenge; i ++ )
    {
        if(( spieler.at(s).position.at(0).x == spieler.at(s).position.at(i).x ) && ( spieler.at(s).position.at(0).y == spieler.at(s).position.at(i).y ))
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).informationen.farbe.at(0));

            spieler.at(s).informationen.leben --;

            if( spieler.at(s).informationen.leben > 0 )
            {
                spieler.at(s).position.at(0).x = spielfeld.groesse.x / 2 + 10 * s + 1;
                spieler.at(s).position.at(0).y = spielfeld.groesse.y / 2 + 1;
            }

            gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 6 );
            cout << spieler.at(s).informationen.leben;
        }
    }

    if( spieler.at(s).informationen.leben <= 0 )
    {
        gameover = true;
    }

return gameover;
}

void spiel( Essen &essen, Spielfeld &spielfeld, vector <Spieler> &spieler )
{
    spielfeld_erstellen( spielfeld, spieler );

    essen_zeichnen( essen, spielfeld, spieler );

    schlange_bewegen( essen, spielfeld, spieler );
}

int main()
{
    Spielfeld spielfeld;
    vector <Spieler> spieler;
    Essen essen;

    spieler.resize( eingaben( spielfeld, spieler ) );

    if( spieler.size() >= 1 )
    {
        spieler.at(0).informationen.name = "MOONY";
        spieler.at(0).informationen.farbe.resize( 2 );
        spieler.at(0).informationen.farbe.at(0) = 200;
        spieler.at(0).informationen.farbe.at(1) = 253;

        spieler.at(0).tasten.oben = 'w';
        spieler.at(0).tasten.unten = 's';
        spieler.at(0).tasten.links = 'a';
        spieler.at(0).tasten.rechts = 'd';

        spieler.at(0).tasten.oben_links = 'q';
        spieler.at(0).tasten.oben_rechts = 'e';
        spieler.at(0).tasten.unten_links = 'y';
        spieler.at(0).tasten.unten_rechts = 'c';

        spieler.at(0).tasten.menue_spieler = 'x';
    }

    if( spieler.size() >= 2 )
    {
        spieler.at(1).informationen.name = "PRONGS";
        spieler.at(1).informationen.farbe.resize( 2 );
        spieler.at(1).informationen.farbe.at(0) = 15;
        spieler.at(1).informationen.farbe.at(1) = 241;

        spieler.at(1).tasten.oben = 't';
        spieler.at(1).tasten.unten = 'g';
        spieler.at(1).tasten.links = 'f';
        spieler.at(1).tasten.rechts = 'h';

        spieler.at(1).tasten.oben_links = 'r';
        spieler.at(1).tasten.oben_rechts = 'z';
        spieler.at(1).tasten.unten_links = 'v';
        spieler.at(1).tasten.unten_rechts = 'n';

        spieler.at(1).tasten.menue_spieler = 'b';
    }

    if( spieler.size() >= 3 )
    {
        spieler.at(2).informationen.name = "PADFOOT";
        spieler.at(2).informationen.farbe.resize( 2 );
        spieler.at(2).informationen.farbe.at(0) = 52;
        spieler.at(2).informationen.farbe.at(1) = 100;

        spieler.at(2).tasten.oben = 'i';
        spieler.at(2).tasten.unten = 'k';
        spieler.at(2).tasten.links = 'j';
        spieler.at(2).tasten.rechts = 'l';

        spieler.at(2).tasten.oben_links = 'u';
        spieler.at(2).tasten.oben_rechts = 'o';
        spieler.at(2).tasten.unten_links = 'm';
        spieler.at(2).tasten.unten_rechts = '.';

        spieler.at(2).tasten.menue_spieler = ',';
    }

    if( spieler.size() >= 4 )
    {
        spieler.at(3).informationen.name = "WORMTAIL";
        spieler.at(3).informationen.farbe.resize( 2 );
        spieler.at(3).informationen.farbe.at(0) = 180;
        spieler.at(3).informationen.farbe.at(1) = 280;

        spieler.at(3).tasten.oben = '8';
        spieler.at(3).tasten.unten = '5';
        spieler.at(3).tasten.links = '4';
        spieler.at(3).tasten.rechts = '6';

        spieler.at(3).tasten.oben_links = '7';
        spieler.at(3).tasten.oben_rechts = '9';
        spieler.at(3).tasten.unten_links = '1';
        spieler.at(3).tasten.unten_rechts = '3';

        spieler.at(3).tasten.menue_spieler = '2';
    }

    if( spieler.size() >= 5 )
    {
        for( int i = 4; i < spieler.size(); i ++ )
        {
            spieler.at(i).informationen.computer = true;

            spieler.at(i).informationen.name = "SPIELER";
            spieler.at(i).informationen.farbe.resize( 2 );
            spieler.at(i).informationen.farbe.at(0) = 200;
            spieler.at(i).informationen.farbe.at(1) = 280;

            spieler.at(i).tasten.oben = 'W';
            spieler.at(i).tasten.unten = 'S';
            spieler.at(i).tasten.links = 'A';
            spieler.at(i).tasten.rechts = 'D';

            spieler.at(i).tasten.oben_links = 'Q';
            spieler.at(i).tasten.oben_rechts = 'E';
            spieler.at(i).tasten.unten_links = 'Y';
            spieler.at(i).tasten.unten_rechts = 'C';

            spieler.at(i).tasten.menue_spieler = 'X';
        }
    }

    for( int i = 0; i < spieler.size(); i ++ )
    {
        spieler.at(i).position.resize( spieler.at(i).informationen.laenge );
        spieler.at(i).informationen.richtung = ' ';

        spieler.at(i).position.at(0).x = spielfeld.groesse.x / 2 + 10 * i + 1;
        spieler.at(i).position.at(0).y = spielfeld.groesse.y / 2 + 1;
    }

    essen_erstellen( essen, spielfeld, spieler );

    spiel( essen, spielfeld, spieler );

    return 0;
}
