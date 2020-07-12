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
    richtung_alt,
    richtung_neu,
    richtung_menue;

    unsigned int
    pause = 6,
    beschleunigung = 2,

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

    beschleunigen = false,

    menue = false,

    gameover = false;

} Informationen;

typedef struct
{
    unsigned int x, y;

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
    ton = false,
    cursor = true;

    unsigned int
    pause = 10,

    farbe_spielfeld = 600,
    farbe_wand = 200;

    char
    beenden = '!',
    menue_pause = ' ',
    menue_cheats = '0';

} Spielfeld;

typedef struct
{
    Informationen info;
    vector <Koordinaten> position;
    Tasten tasten;

} Spieler;

typedef struct
{
    Koordinaten position;
    unsigned int farbe = 450;

} Punkt;



int eingaben( Spielfeld &spielfeld, vector <Spieler> &spieler, vector <Punkt> hinderniss );


void spiel( Spielfeld &spielfeld, vector <Spieler> &spieler, vector <Punkt> &essen);


void spielfeld_erstellen( Spielfeld &spielfeld, vector <Spieler> &spieler );
void punkt_erstellen( vector <Punkt> &punkt, Spielfeld &spielfeld, vector <Spieler> &spieler );
void punkt_zeichnen( vector <Punkt> &punkt, Spielfeld &spielfeld, vector <Spieler> &spieler );

void richtung( Spielfeld &spielfeld, vector <Spieler> &spieler, vector <Punkt> &essen );
void richtung_spieler( char richtung, vector <Spieler> &spieler );
void richtung_computer( vector <Spieler> &spieler, vector <Punkt> &essen );

void bewegen( Spielfeld &spielfeld, vector <Spieler> &spieler, vector <Punkt> &essen, unsigned long long zaehler );
void spieler_bewegen( Spielfeld &spielfeld, vector <Spieler> &spieler, vector <Punkt> &essen, unsigned long long zaehler, unsigned int s );

void spieler_informationen( Spielfeld spielfeld, vector <Spieler> spieler, unsigned int s );
void spieler_menue( Spielfeld &spielfeld, vector <Spieler> &spieler, unsigned int s );


void menue_pause( Spielfeld &spielfeld, vector <Spieler> &spieler, vector <Punkt> &essen );
void menue_cheats( Spielfeld &spielfeld, vector <Spieler> &spieler, vector <Punkt> &essen );


void leben( Spielfeld &spielfeld, vector <Spieler> &spieler, unsigned int s );
bool gameover( Spielfeld &spielfeld, vector <Spieler> &spieler, unsigned int s );


void farben();



int eingaben( Spielfeld &spielfeld, vector <Spieler> &spieler, vector <Punkt> hinderniss )
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


void spiel( Spielfeld &spielfeld, vector <Spieler> &spieler, vector <Punkt> &essen )
{
    bool wiederholen = true;

    spielfeld_erstellen( spielfeld, spieler );

    punkt_zeichnen( essen, spielfeld, spieler );

    for( unsigned int i = 0; i < spieler.size(); i ++ )
    {
        spieler_informationen( spielfeld, spieler, i );
    }

    for( unsigned long long zaehler = 0; wiederholen == true; zaehler ++ )
    {
        richtung( spielfeld, spieler, essen );

        bewegen( spielfeld, spieler, essen, zaehler );

        wiederholen = true;

        for( unsigned int i = 0; i < spieler.size(); i ++ )
        {
            if( spieler.at(i).info.gameover == true )
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

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe_wand);
    for( x = 0; x <= spielfeld.groesse.x + 1; x ++ )
    {
        cout << '+';
    }
    cout << '\n';

    for( y = 1; y <= spielfeld.groesse.y; y ++ )
    {
        cout << '+';

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe_spielfeld);
        for( x = 1; x <= spielfeld.groesse.x; x ++ )
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

    for( unsigned int sp = 0; sp < spieler.size(); sp ++ )
    {
        for( unsigned int i = 0; i < spieler.at(sp).info.laenge; i ++ )
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(sp).info.farbe.at( i % spieler.at(sp).info.farbe.size() ));
            gotoXY( spieler.at(sp).position.at(i).x, spieler.at(sp).position.at(i).y );

            if(( spieler.at(sp).info.name_anzeigen == true ) && ( i < spieler.at(sp).info.name.size() ))
            {
                cout << spieler.at(sp).info.name.at(i);
            }

            else
            {
                cout << ' ';
            }
        }
    }
}


void punkt_erstellen( vector <Punkt> &punkt, Spielfeld &spielfeld, vector <Spieler> &spieler )
{
    bool wiederholen;

    for( unsigned int p = 0; p < punkt.size(); p ++ )
    {
        do
        {
            time_t t;

            wiederholen = false;

            time(&t);
            srand(( unsigned int )t );

            punkt.at(p).position.x = rand() % spielfeld.groesse.x + 1;
            punkt.at(p).position.y = rand() % spielfeld.groesse.y + 1;

            for( unsigned int s = 0; s < spieler.size(); s ++ )
            {
                for( unsigned int i; i < spieler.at(s).info.laenge; i ++ )
                {
                    if(( punkt.at(p).position.x == spieler.at(s).position.at(i).x ) && ( punkt.at(p).position.y == spieler.at(s).position.at(i).y ))
                    {
                        wiederholen = true;
                    }
                }
            }
        }
        while( wiederholen == true );
    }
}


void punkt_zeichnen( vector <Punkt> &punkt, Spielfeld &spielfeld, vector <Spieler> &spieler )
{
    for( unsigned int p = 0; p < punkt.size(); p ++ )
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), punkt.at(p).farbe);
        gotoXY(punkt.at(p).position.x, punkt.at(p).position.y);
        cout << ' ';
    }
}


void richtung( Spielfeld &spielfeld, vector <Spieler> &spieler, vector <Punkt> &essen )
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
            menue_pause( spielfeld, spieler, essen );
        }

        else if( richtung == spielfeld.menue_cheats )
        {
            menue_cheats( spielfeld, spieler, essen );
        }

        richtung_spieler( richtung, spieler );
    }

    richtung_computer( spieler, essen );
}


void richtung_spieler( char richtung, vector <Spieler> &spieler )
{
    bool wiederholen;
    unsigned int sp = 0;

    do
    {
        wiederholen = false;

        if(( richtung == spieler.at(sp).tasten.menue_spieler )
        || ((( richtung == spieler.at(sp).tasten.oben ) && ( spieler.at(sp).info.richtung != spieler.at(sp).tasten.unten ))
        || (( richtung == spieler.at(sp).tasten.unten ) && ( spieler.at(sp).info.richtung != spieler.at(sp).tasten.oben ))
        || (( richtung == spieler.at(sp).tasten.links ) && ( spieler.at(sp).info.richtung != spieler.at(sp).tasten.rechts ))
        || (( richtung == spieler.at(sp).tasten.rechts ) && ( spieler.at(sp).info.richtung != spieler.at(sp).tasten.links ))
        || (( spieler.at(sp).info.diagonal_fahren == true ) && ( richtung == spieler.at(sp).tasten.oben_links ) && ( spieler.at(sp).info.richtung != spieler.at(sp).tasten.unten_rechts ))
        || (( spieler.at(sp).info.diagonal_fahren == true ) && ( richtung == spieler.at(sp).tasten.oben_rechts ) && ( spieler.at(sp).info.richtung != spieler.at(sp).tasten.unten_links ))
        || (( spieler.at(sp).info.diagonal_fahren == true ) && ( richtung == spieler.at(sp).tasten.unten_links ) && ( spieler.at(sp).info.richtung != spieler.at(sp).tasten.oben_rechts ))
        || (( spieler.at(sp).info.diagonal_fahren == true ) && ( richtung == spieler.at(sp).tasten.unten_rechts ) && ( spieler.at(sp).info.richtung != spieler.at(sp).tasten.oben_links ))))
        {
            if( spieler.at(sp).info.menue == false )
            {
                spieler.at(sp).info.richtung_alt = spieler.at(sp).info.richtung;
            }

            spieler.at(sp).info.richtung_neu = richtung;
        }


        else if( sp < spieler.size() - 1 )
        {
            sp ++;
            wiederholen = true;
        }
    }
    while( wiederholen == true );
}


void richtung_computer( vector <Spieler> &spieler, vector <Punkt> &essen )
{
    for( unsigned int i = 0; i < spieler.size(); i ++ )
    {
        if( spieler.at(i).info.computer == true )
        {
            if(( essen.at(0).position.y < spieler.at(i).position.at(0).y ) && ( spieler.at(i).info.richtung != spieler.at(i).tasten.unten ))
            {
                spieler.at(i).info.richtung_neu = spieler.at(i).tasten.oben;
            }

            else if(( essen.at(0).position.y > spieler.at(i).position.at(0).y ) && ( spieler.at(i).info.richtung != spieler.at(i).tasten.oben ))
            {
                spieler.at(i).info.richtung_neu = spieler.at(i).tasten.unten;
            }

            else if(( essen.at(0).position.x < spieler.at(i).position.at(0).x ) && ( spieler.at(i).info.richtung != spieler.at(i).tasten.rechts ))
            {
                spieler.at(i).info.richtung_neu = spieler.at(i).tasten.links;
            }

            else if(( essen.at(0).position.x > spieler.at(i).position.at(0).x ) && ( spieler.at(i).info.richtung != spieler.at(i).tasten.links ))
            {
                spieler.at(i).info.richtung_neu = spieler.at(i).tasten.rechts;
            }
        }
    }
}


void bewegen( Spielfeld &spielfeld, vector <Spieler> &spieler, vector <Punkt> &essen, unsigned long long zaehler )
{
    for( unsigned int s = 0; s < spieler.size(); s ++ )
    {
        if( spieler.at(s).info.richtung_neu == spieler.at(s).tasten.menue_spieler )
        {
            if( spieler.at(s).info.menue == false )
            {
                spieler.at(s).info.menue = true;
                spieler_menue( spielfeld, spieler, s );
            }

            else if( spieler.at(s).info.menue == true )
            {
                spieler.at(s).info.menue = false;
                spieler_informationen( spielfeld, spieler, s );
            }

            spieler.at(s).info.richtung_neu = spieler.at(s).info.richtung_alt;
        }

        if( spieler.at(s).info.menue == false )
        {
            spieler_bewegen( spielfeld, spieler, essen, zaehler, s );
        }

        if( spielfeld.cursor == false )
        {
            SetCursorPos( 2000, 2000 );
        }
    }
}


void spieler_bewegen( Spielfeld &spielfeld, vector <Spieler> &spieler, vector <Punkt> &essen, unsigned long long zaehler, unsigned int s )
{
    unsigned int pause = zaehler % spieler.at(s).info.pause;

    if( spieler.at(s).info.richtung_neu == spieler.at(s).info.richtung_alt )
    {
        pause /= spieler.at(s).info.beschleunigung;
    }

    if(( pause == 0 ) && ( spieler.at(s).info.gameover == false ))
    {
        spieler.at(s).info.richtung = spieler.at(s).info.richtung_neu;

        for( unsigned int i = 0; i < spieler.at(s).info.laenge; i ++ )
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).info.farbe.at( i % spieler.at(s).info.farbe.size() ));
            gotoXY( spieler.at(s).position.at(i).x, spieler.at(s).position.at(i).y );

            if(( spieler.at(s).info.name_anzeigen == true ) && ( i < spieler.at(s).info.name.size() ))
            {
                cout << spieler.at(s).info.name.at(i);
            }

            else
            {
                cout << ' ';
            }
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe_spielfeld);
        gotoXY(spieler.at(s).position.at(spieler.at(s).info.laenge - 1).x, spieler.at(s).position.at(spieler.at(s).info.laenge - 1).y);
        cout << ' ';

        if( spieler.at(s).info.richtung != ' ' )
        {
            for( int i = spieler.at(s).info.laenge - 1; i > 0; i -- )
            {
                spieler.at(s).position.at(i).x = spieler.at(s).position.at(i - 1).x;
                spieler.at(s).position.at(i).y = spieler.at(s).position.at(i - 1).y;
            }
        }

        if( spieler.at(s).info.richtung == spieler.at(s).tasten.oben )
        {
            spieler.at(s).position.at(0).y --;
        }

        else if( spieler.at(s).info.richtung == spieler.at(s).tasten.unten )
        {
            spieler.at(s).position.at(0).y ++;
        }

        else if( spieler.at(s).info.richtung == spieler.at(s).tasten.links )
        {
            spieler.at(s).position.at(0).x --;
        }

        else if( spieler.at(s).info.richtung == spieler.at(s).tasten.rechts )
        {
            spieler.at(s).position.at(0).x ++;
        }

        else if( spieler.at(s).info.diagonal_fahren == true )
        {
            if( spieler.at(s).info.richtung == spieler.at(s).tasten.oben_links )
            {
                spieler.at(s).position.at(0).y --;
                spieler.at(s).position.at(0).x --;
            }

            else if( spieler.at(s).info.richtung == spieler.at(s).tasten.oben_rechts )
            {
                spieler.at(s).position.at(0).y --;
                spieler.at(s).position.at(0).x ++;
            }

            else if( spieler.at(s).info.richtung == spieler.at(s).tasten.unten_links )
            {
                spieler.at(s).position.at(0).y ++;
                spieler.at(s).position.at(0).x --;
            }

            else if( spieler.at(s).info.richtung == spieler.at(s).tasten.unten_rechts )
            {
                spieler.at(s).position.at(0).y ++;
                spieler.at(s).position.at(0).x ++;
            }
        }

        if( spieler.at(s).info.waende == false )
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

        spieler.at(s).info.gameover = gameover( spielfeld, spieler,  s );

        if(( spieler.at(s).position.at(0).x == essen.at(0).position.x ) && ( spieler.at(s).position.at(0).y == essen.at(0).position.y ))
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).info.farbe.at(0));

            spieler.at(s).info.punkte ++;
            gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 3 );
            cout << spieler.at(s).info.punkte;

            spieler.at(s).info.laenge ++;
            spieler.at(s).position.resize( spieler.at(s).info.laenge );
            gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 4 );
            cout << spieler.at(s).info.laenge;

            punkt_erstellen( essen, spielfeld, spieler );
            punkt_zeichnen( essen, spielfeld, spieler );
        }
    }
}


void spieler_informationen( Spielfeld spielfeld, vector <Spieler> spieler, unsigned int s )
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).info.farbe.at(0));

    gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 2 );
    cout << "NAME:   " << spieler.at(s).info.name;

    gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 3 );
    cout << "PUNKTE: " << spieler.at(s).info.punkte;

    gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 4 );
    cout << "LAENGE: " << spieler.at(s).info.laenge;

    gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 5 );
    cout << "GELD:   " << spieler.at(s).info.geld << " EURO";

    gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 6 );
    cout << "LEBEN:  " << spieler.at(s).info.leben;
}

void spieler_menue( Spielfeld &spielfeld, vector <Spieler> &spieler, unsigned int s )
{
    gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 2 );
    cout << "SPIELERMENUE";
}

void menue_pause( Spielfeld &spielfeld, vector <Spieler> &spieler, vector <Punkt> &essen )
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
            spiel( spielfeld, spieler, essen );

        case'4':
            menue_cheats( spielfeld, spieler, essen );
    }
}


void menue_cheats( Spielfeld &spielfeld, vector <Spieler> &spieler, vector <Punkt> &essen )
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

    spiel( spielfeld, spieler, essen );
}


void leben( Spielfeld &spielfeld, vector <Spieler> &spieler, unsigned int s )
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).info.farbe.at(0));

    spieler.at(s).info.leben --;


    if( spieler.at(s).info.leben > 0 )
    {
        spieler.at(s).info.richtung_neu = ' ';
        spieler.at(s).position.at(0).x = spielfeld.groesse.x / spieler.size() * s + spielfeld.groesse.x / ( spieler.size() * 2 );
        spieler.at(s).position.at(0).y = spielfeld.groesse.y / 2 + 1;
    }

    gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 6 );
    cout << spieler.at(s).info.leben;
}


bool gameover( Spielfeld &spielfeld, vector <Spieler> &spieler, unsigned int s )
{
    bool gameover = spieler.at(s).info.gameover;

    if((spieler.at(s).info.waende == true) && ((spieler.at(s).position.at(0).x == 0) || (spieler.at(s).position.at(0).y == 0) || (spieler.at(s).position.at(0).x == spielfeld.groesse.x + 1) || (spieler.at(s).position.at(0).y == spielfeld.groesse.y + 1)))
    {
        leben( spielfeld, spieler, s );
    }

    for( unsigned int sp = 0; sp < spieler.size(); sp ++ )
    {
        for( unsigned int i = 0; i < spieler.at(sp).info.laenge; i ++ )
        {
            if(( spieler.at(s).position.at(0).x == spieler.at(sp).position.at(i).x ) && ( spieler.at(s).position.at(0).y == spieler.at(sp).position.at(i).y ) && ( sp != s ))
            {
                leben( spielfeld, spieler, s );
            }
        }
    }

    for( unsigned int i = 1; i < spieler.at(s).info.laenge; i ++ )
    {
        if(( spieler.at(s).position.at(0).x == spieler.at(s).position.at(i).x ) && ( spieler.at(s).position.at(0).y == spieler.at(s).position.at(i).y ))
        {
            leben( spielfeld, spieler, s );
        }
    }

    if( spieler.at(s).info.leben <= 0 )
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
	system( "color 84" );

    Spielfeld spielfeld;
    vector <Punkt> essen(1);
    vector <Punkt> hinderniss;

    vector <Spieler> spieler( eingaben( spielfeld, spieler, hinderniss ) );

    if( spieler.size() >= 1 )
    {
        spieler.at(0).info.name = "MOONY";
        spieler.at(0).info.farbe.resize(2);
        spieler.at(0).info.farbe.at(0) = 200;
        spieler.at(0).info.farbe.at(1) = 253;

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
        spieler.at(1).info.name = "PRONGS";
        spieler.at(1).info.farbe.resize(2);
        spieler.at(1).info.farbe.at(0) = 15;
        spieler.at(1).info.farbe.at(1) = 241;

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
        spieler.at(2).info.name = "PADFOOT";
        spieler.at(2).info.pause = 3;
        spieler.at(2).info.farbe.resize(2);
        spieler.at(2).info.farbe.at(0) = 52;
        spieler.at(2).info.farbe.at(1) = 100;

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
        spieler.at(3).info.name = "WORMTAIL";
        spieler.at(3).info.farbe.resize(2);
        spieler.at(3).info.farbe.at(0) = 180;
        spieler.at(3).info.farbe.at(1) = 280;

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
        for( unsigned int i = 4; i < spieler.size(); i ++ )
        {
            spieler.at(i).info.computer = true;

            spieler.at(i).info.name = "SPIELER";
            spieler.at(i).info.farbe.resize(2);
            spieler.at(i).info.farbe.at(0) = 200;
            spieler.at(i).info.farbe.at(1) = 280;

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

    for( unsigned int i = 0; i < spieler.size(); i ++ )
    {
        spieler.at(i).position.resize( spieler.at(i).info.laenge );
        spieler.at(i).info.richtung_neu = ' ';

        spieler.at(i).position.at(0).x = spielfeld.groesse.x / spieler.size() * i + spielfeld.groesse.x / ( spieler.size() * 2 );
        spieler.at(i).position.at(0).y = spielfeld.groesse.y / 2 + 1;
    }

    punkt_erstellen( essen, spielfeld, spieler );

    spiel( spielfeld, spieler, essen );

    return 0;
}
