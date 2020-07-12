#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <display.h>
#include <time.h>


using namespace std;

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
    string name;
    unsigned int naechste_seite;

} Seite;

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

    vector <Seite> seite_menue;

} Spielfeld;

typedef struct
{
    vector <Koordinaten> position;

    char
    richtung,
    richtung_alt,
    richtung_menue;

    unsigned int
    pause = 6,
    beschleunigung = 3,
    laenge = 10;

    bool
    diagonal_fahren = true,
    waende = true,
    name_anzeigen = true;

} Schlange;

typedef struct
{
    string
    name,
    info;

    bool
    gebaut = false,
    verschieben = false;

    Koordinaten
    start_pos,
    ende_pos;

    unsigned int
    reichweite,
    kosten,
    level,
    farbe;

} Gebaeude;

typedef struct
{
    vector <Koordinaten> position;
    char richtung;
    unsigned int farbe;

} Punkt;

typedef struct
{
    string name;

    unsigned int
    punkte = 0,
    leben = 3,
    geld = 5000;

    int
    menue_seite = 0;

    bool
    computer = false,
    menue = false,
    gameover = false;

    vector <unsigned int> farbe;

    Schlange schlange;
    vector <Gebaeude> gebaeude;
    Tasten tasten;

    Punkt punkt;

} Spieler;

typedef struct
{
    Punkt essen;
    Punkt geld;
    Punkt leben;
    Punkt hindernis;

} Punkte;



int eingaben( Spielfeld &spielfeld, vector <Spieler> &spieler );


void spiel( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte );


void spielfeld_erstellen( Spielfeld &spielfeld, vector <Spieler> &spieler );
void punkte_erstellen( Punkt &punkt, Spielfeld &spielfeld, vector <Spieler> &spieler );
void punkte_zeichnen( Punkt &punkt );
void gebaeude_zeichnen( vector <Spieler> &spieler, unsigned int s, unsigned int g );


void richtung( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte );
void richtung_spieler( char richtung, vector <Spieler> &spieler );
void richtung_computer( vector <Spieler> &spieler, Punkte &punkte );

void bewegen( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte, unsigned long long zaehler );
void spieler_bewegen( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte, unsigned long long zaehler, unsigned int s );
void gebaeude( vector <Spieler> &spieler, unsigned long long zaehler, unsigned int s );

void spieler_informationen( Spielfeld spielfeld, vector <Spieler> spieler, unsigned int s );
void spieler_menue( Spielfeld &spielfeld, vector <Spieler> &spieler, unsigned int s );


void menue_pause( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte );
void menue_cheats( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte );


void leben( Spielfeld &spielfeld, vector <Spieler> &spieler, unsigned int s );
bool gameover( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkt &hindernis, unsigned int s );


void farben();



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


void spiel( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte )
{
    bool wiederholen = true;

    spielfeld_erstellen( spielfeld, spieler );

    for( unsigned int i = 0; i < spieler.size(); i ++ )
    {
        gebaeude_zeichnen( spieler, i, 0 );
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
        for( unsigned int i = 0; i < spieler.at(sp).schlange.laenge; i ++ )
        {
            SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(sp).farbe.at( i % spieler.at(sp).farbe.size() ));
            gotoXY( spieler.at(sp).schlange.position.at(i).x, spieler.at(sp).schlange.position.at(i).y );

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


void punkte_erstellen( Punkt &punkt, Spielfeld &spielfeld, vector <Spieler> &spieler )
{
    bool wiederholen = false;
    time_t t;

    time(&t);
    srand(( unsigned int )t );

    for( unsigned int p = 0; p < punkt.position.size(); p ++ )
    {
        do
        {
            wiederholen = false;

            punkt.position.at(p).x = ( "&d", ( rand() + 100 * p ) % spielfeld.groesse.x ) + 1;
            punkt.position.at(p).y = ( "&d", ( rand() + 100 * p ) % spielfeld.groesse.y ) + 1;

            for( unsigned int s = 0; s < spieler.size(); s ++ )
            {
                for( unsigned int i = 0; i < spieler.at(s).schlange.position.size(); i ++ )
                {
                    if(( punkt.position.at(p).x == spieler.at(s).schlange.position.at(i).x ) && ( punkt.position.at(p).y == spieler.at(s).schlange.position.at(i).y ))
                    {
                        wiederholen = true;
                    }
                }
            }

            for( unsigned int j = 0; j < p; j ++ )
            {
                if(( punkt.position.at(p).x == punkt.position.at(j).x ) && ( punkt.position.at(p).y == punkt.position.at(j).y ))
                {
                    wiederholen = true;
                }
            }
        }
        while( wiederholen == true );
    }
}


void punkte_zeichnen( Punkt &punkt )
{
    for( unsigned int p = 0; p < punkt.position.size(); p ++ )
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), punkt.farbe);
        gotoXY(punkt.position.at(p).x, punkt.position.at(p).y);
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
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(0));
        gotoXY( spieler.at(s).gebaeude.at(g).start_pos.x, y );

        for( unsigned int x = spieler.at(s).gebaeude.at(g).start_pos.x; x <= spieler.at(s).gebaeude.at(g).ende_pos.x; x ++ )
        {
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

        if(( richtung == spieler.at(sp).tasten.menue_spieler )
        || ((( richtung == spieler.at(sp).tasten.oben ) && ( spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.unten ))
        || (( richtung == spieler.at(sp).tasten.unten ) && ( spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.oben ))
        || (( richtung == spieler.at(sp).tasten.links ) && ( spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.rechts ))
        || (( richtung == spieler.at(sp).tasten.rechts ) && ( spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.links ))
        || (( spieler.at(sp).schlange.diagonal_fahren == true ) && ( richtung == spieler.at(sp).tasten.oben_links ) && ( spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.unten_rechts ))
        || (( spieler.at(sp).schlange.diagonal_fahren == true ) && ( richtung == spieler.at(sp).tasten.oben_rechts ) && ( spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.unten_links ))
        || (( spieler.at(sp).schlange.diagonal_fahren == true ) && ( richtung == spieler.at(sp).tasten.unten_links ) && ( spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.oben_rechts ))
        || (( spieler.at(sp).schlange.diagonal_fahren == true ) && ( richtung == spieler.at(sp).tasten.unten_rechts ) && ( spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.oben_links ))))
        {
            if( spieler.at(sp).menue == false )
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
            if(( punkte.essen.position.at(0).y < spieler.at(i).schlange.position.at(0).y ) && ( spieler.at(i).schlange.richtung != spieler.at(i).tasten.unten ))
            {
                spieler.at(i).schlange.richtung = spieler.at(i).tasten.oben;
            }

            else if(( punkte.essen.position.at(0).y > spieler.at(i).schlange.position.at(0).y ) && ( spieler.at(i).schlange.richtung != spieler.at(i).tasten.oben ))
            {
                spieler.at(i).schlange.richtung = spieler.at(i).tasten.unten;
            }

            else if(( punkte.essen.position.at(0).x < spieler.at(i).schlange.position.at(0).x ) && ( spieler.at(i).schlange.richtung != spieler.at(i).tasten.rechts ))
            {
                spieler.at(i).schlange.richtung = spieler.at(i).tasten.links;
            }

            else if(( punkte.essen.position.at(0).x > spieler.at(i).schlange.position.at(0).x ) && ( spieler.at(i).schlange.richtung != spieler.at(i).tasten.links ))
            {
                spieler.at(i).schlange.richtung = spieler.at(i).tasten.rechts;
            }
        }
    }
}


void bewegen( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkte &punkte, unsigned long long zaehler )
{
    static double time1 = 0.0, tstart = clock();

    for( unsigned int s = 0; s < spieler.size(); s ++ )
    {
        if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.menue_spieler )
        {
            if(( spieler.at(s).menue == false )
            && ( spieler.at(s).schlange.position.at(0).x < spieler.at(s).gebaeude.at(0).ende_pos.x )
            && ( spieler.at(s).schlange.position.at(0).y < spieler.at(s).gebaeude.at(0).ende_pos.y )
            && ( spieler.at(s).schlange.position.at(0).x > spieler.at(s).gebaeude.at(0).start_pos.x )
            && ( spieler.at(s).schlange.position.at(0).y > spieler.at(s).gebaeude.at(0).start_pos.y ))
            {
                spieler.at(s).menue = true;
            }

            else if( spieler.at(s).menue == true )
            {
                spieler.at(s).menue = false;
                spieler_informationen( spielfeld, spieler, s );
            }

            spieler.at(s).schlange.richtung = spieler.at(s).schlange.richtung_alt;
        }

        if( spieler.at(s).menue == false )
        {
            spieler_bewegen( spielfeld, spieler, punkte, zaehler, s );
        }

        else if( spieler.at(s).menue == true )
        {
            spieler_menue( spielfeld, spieler, s );
            punkte_zeichnen( punkte.essen );
            punkte_zeichnen( punkte.geld );
            punkte_zeichnen( punkte.leben );
            punkte_zeichnen( punkte.hindernis );
        }

        gebaeude( spieler, zaehler, s );

        if( spielfeld.cursor == false )
        {
            SetCursorPos( 2000, 2000 );
        }
    }

    static unsigned int zufall;

    time1 = clock() - tstart;

    if( time1 > 5000 )
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe_spielfeld);

        gotoXY( punkte.geld.position.at(0).x, punkte.geld.position.at(0).y );
        cout << ' ';
        gotoXY( punkte.leben.position.at(0).x, punkte.leben.position.at(0).y );
        cout << ' ';
        punkte.geld.position.at(0).x = 0;
        punkte.geld.position.at(0).y = 0;
        punkte.leben.position.at(0).x = 0;
        punkte.leben.position.at(0).y = 0;
    }

    if(( time1 > 12000 ))
    {
        tstart = clock();

        zufall = ( "&d", rand() % 2 );
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
    unsigned int pause = zaehler % spieler.at(s).schlange.pause, sp;

    time_t t;

    time(&t);
    srand(( unsigned int )t );

    if( spieler.at(s).schlange.richtung == spieler.at(s).schlange.richtung_alt )
    {
        pause /= spieler.at(s).schlange.beschleunigung;
    }

    if(( pause == 0 ) && ( spieler.at(s).gameover == false ))
    {
        for( unsigned int i = 0; i < spieler.at(s).schlange.laenge; i ++ )
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at( i % spieler.at(s).farbe.size() ));
            gotoXY( spieler.at(s).schlange.position.at(i).x, spieler.at(s).schlange.position.at(i).y );

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
                if(( spieler.at(s).schlange.position.at( spieler.at(s).schlange.laenge - 1 ).x <= spieler.at(i).gebaeude.at(g).ende_pos.x )
                && ( spieler.at(s).schlange.position.at( spieler.at(s).schlange.laenge - 1 ).y <= spieler.at(i).gebaeude.at(g).ende_pos.y )
                && ( spieler.at(s).schlange.position.at( spieler.at(s).schlange.laenge - 1 ).x >= spieler.at(i).gebaeude.at(g).start_pos.x )
                && ( spieler.at(s).schlange.position.at( spieler.at(s).schlange.laenge - 1 ).y >= spieler.at(i).gebaeude.at(g).start_pos.y ))
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
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe_spielfeld);
        }

        gotoXY( spieler.at(s).schlange.position.at( spieler.at(s).schlange.laenge - 1 ).x, spieler.at(s).schlange.position.at( spieler.at(s).schlange.laenge - 1 ).y );
        cout << ' ';

        if( spieler.at(s).schlange.richtung != ' ' )
        {
            for( int i = spieler.at(s).schlange.laenge - 1; i > 0; i -- )
            {
                spieler.at(s).schlange.position.at(i).x = spieler.at(s).schlange.position.at(i - 1).x;
                spieler.at(s).schlange.position.at(i).y = spieler.at(s).schlange.position.at(i - 1).y;
            }
        }

        if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.oben )
        {
            spieler.at(s).schlange.position.at(0).y --;
        }

        else if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.unten )
        {
            spieler.at(s).schlange.position.at(0).y ++;
        }

        else if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.links )
        {
            spieler.at(s).schlange.position.at(0).x --;
        }

        else if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.rechts )
        {
            spieler.at(s).schlange.position.at(0).x ++;
        }

        else if( spieler.at(s).schlange.diagonal_fahren == true )
        {
            if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.oben_links )
            {
                spieler.at(s).schlange.position.at(0).y --;
                spieler.at(s).schlange.position.at(0).x --;
            }

            else if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.oben_rechts )
            {
                spieler.at(s).schlange.position.at(0).y --;
                spieler.at(s).schlange.position.at(0).x ++;
            }

            else if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.unten_links )
            {
                spieler.at(s).schlange.position.at(0).y ++;
                spieler.at(s).schlange.position.at(0).x --;
            }

            else if( spieler.at(s).schlange.richtung == spieler.at(s).tasten.unten_rechts )
            {
                spieler.at(s).schlange.position.at(0).y ++;
                spieler.at(s).schlange.position.at(0).x ++;
            }
        }

        if( spieler.at(s).schlange.waende == false )
        {
            if( spieler.at(s).schlange.position.at(0).y == 0)
            {
                spieler.at(s).schlange.position.at(0).y = spielfeld.groesse.y;
            }

            if( spieler.at(s).schlange.position.at(0).y == spielfeld.groesse.y + 1)
            {
                spieler.at(s).schlange.position.at(0).y = 1;
            }

            if( spieler.at(s).schlange.position.at(0).x == 0)
            {
                spieler.at(s).schlange.position.at(0).x = spielfeld.groesse.x;
            }

            if( spieler.at(s).schlange.position.at(0).x == spielfeld.groesse.x + 1)
            {
                spieler.at(s).schlange.position.at(0).x = 1;
            }
        }

        spieler.at(s).gameover = gameover( spielfeld, spieler, punkte.hindernis, s );

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(0));

        if(( spieler.at(s).schlange.position.at(0).x == punkte.essen.position.at(0).x ) && ( spieler.at(s).schlange.position.at(0).y == punkte.essen.position.at(0).y ))
        {
            spieler.at(s).punkte ++;
            gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 3 );
            cout << spieler.at(s).punkte;

            spieler.at(s).schlange.laenge ++;
            spieler.at(s).schlange.position.resize( spieler.at(s).schlange.laenge );
            gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 4 );
            cout << spieler.at(s).schlange.laenge;

            spieler.at(s).geld += rand() % 11;
            gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 5 );
            cout << spieler.at(s).geld << " EURO";

            punkte_erstellen( punkte.essen, spielfeld, spieler );
            punkte_zeichnen( punkte.essen );
        }

        if(( spieler.at(s).schlange.position.at(0).x == punkte.geld.position.at(0).x ) && ( spieler.at(s).schlange.position.at(0).y == punkte.geld.position.at(0).y ))
        {
            spieler.at(s).geld += zaehler / 100;
            punkte.geld.position.at(0).x = 0;
            punkte.geld.position.at(0).y = 0;
            gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 5 );
            cout << spieler.at(s).geld << " EURO";
        }

        if(( spieler.at(s).schlange.position.at(0).x == punkte.leben.position.at(0).x ) && ( spieler.at(s).schlange.position.at(0).y == punkte.leben.position.at(0).y ))
        {
            spieler.at(s).leben += 1;
            punkte.leben.position.at(0).x = 0;
            punkte.leben.position.at(0).y = 0;
            gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 6 );
            cout << spieler.at(s).leben;
        }
    }
}


void gebaeude( vector <Spieler> &spieler, unsigned long long zaehler, unsigned int s )
{
    if(( spieler.at(s).gebaeude.at(1).gebaut == true ) && ( spieler.at(s).gebaeude.at(1).verschieben == false ))
    {
        spieler.at(s).punkt.position.resize( spieler.at(s).punkt.position.size() + 1 );
        spieler.at(s).punkt.position.at( spieler.at(s).punkt.position.size() - 1 ).x = ( spieler.at(s).gebaeude.at(1).start_pos.x + spieler.at(s).gebaeude.at(1).ende_pos.x ) / 2;
        spieler.at(s).punkt.position.at( spieler.at(s).punkt.position.size() - 1 ).y = ( spieler.at(s).gebaeude.at(1).start_pos.y + spieler.at(s).gebaeude.at(1).ende_pos.y ) / 2;
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
    cout << "LAENGE: " << spieler.at(s).schlange.laenge;

    gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 5 );
    cout << "GELD:   " << spieler.at(s).geld << " EURO";

    gotoXY( spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 6 );
    cout << "LEBEN:  " << spieler.at(s).leben;
}

void spieler_menue( Spielfeld &spielfeld, vector <Spieler> &spieler, unsigned int s )
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(0));

    bool v = false;
    for( unsigned int i = 0; i < spieler.at(s).gebaeude.size(); i ++)
    {
        if( spieler.at(s).gebaeude.at(i).verschieben == true )
        {
            v = true;

                for( unsigned int y = spieler.at(s).gebaeude.at(i).start_pos.y; y <= spieler.at(s).gebaeude.at(i).ende_pos.y; y ++ )
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe_spielfeld);
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
            spiel( spielfeld, spieler, punkte );

        case'4':
            menue_cheats( spielfeld, spieler, punkte );
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

    if( spieler.at(s).leben > 0 )
    {
        spieler.at(s).schlange.richtung = ' ';
        spieler.at(s).schlange.position.at(0).x = spielfeld.groesse.x / spieler.size() * s + spielfeld.groesse.x / ( spieler.size() * 2 );
        spieler.at(s).schlange.position.at(0).y = spielfeld.groesse.y / 2 + 1;
    }

    gotoXY( spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 6 );
    cout << spieler.at(s).leben;
}


bool gameover( Spielfeld &spielfeld, vector <Spieler> &spieler, Punkt &hindernis, unsigned int s )
{
    bool gameover = spieler.at(s).gameover;

    if((spieler.at(s).schlange.waende == true) && ((spieler.at(s).schlange.position.at(0).x == 0) || (spieler.at(s).schlange.position.at(0).y == 0) || (spieler.at(s).schlange.position.at(0).x == spielfeld.groesse.x + 1) || (spieler.at(s).schlange.position.at(0).y == spielfeld.groesse.y + 1)))
    {
        leben( spielfeld, spieler, s );
    }

    for( unsigned int p = 1; p < hindernis.position.size() - 1; p ++ )
    {
        if(( spieler.at(s).schlange.position.at(0).x == hindernis.position.at(p).x ) && ( spieler.at(s).schlange.position.at(0).y == hindernis.position.at(p).y ))
        {
            leben( spielfeld, spieler, s );
        }
    }

    for( unsigned int sp = 0; sp < spieler.size(); sp ++ )
    {
        for( unsigned int i = 0; i < spieler.at(sp).schlange.laenge; i ++ )
        {
            if(( spieler.at(s).schlange.position.at(0).x == spieler.at(sp).schlange.position.at(i).x ) && ( spieler.at(s).schlange.position.at(0).y == spieler.at(sp).schlange.position.at(i).y ) && ( sp != s ))
            {
                leben( spielfeld, spieler, s );
            }
        }

        for( unsigned int i = 1; i < spieler.at(sp).gebaeude.size(); i ++ )
        {
            if(( spieler.at(s).schlange.position.at(0).x <= spieler.at(sp).gebaeude.at(i).ende_pos.x )
            && ( spieler.at(s).schlange.position.at(0).y <= spieler.at(sp).gebaeude.at(i).ende_pos.y )
            && ( spieler.at(s).schlange.position.at(0).x >= spieler.at(sp).gebaeude.at(i).start_pos.x )
            && ( spieler.at(s).schlange.position.at(0).y >= spieler.at(sp).gebaeude.at(i).start_pos.y )
            && ( spieler.at(sp).gebaeude.at(i).gebaut == true )
            && ( spieler.at(sp).gebaeude.at(i).verschieben == false )
            && ( sp != s ))
            {
                leben( spielfeld, spieler, s );
            }
        }
    }

    for( unsigned int i = 1; i < spieler.at(s).schlange.laenge; i ++ )
    {
        if(( spieler.at(s).schlange.position.at(0).x == spieler.at(s).schlange.position.at(i).x ) && ( spieler.at(s).schlange.position.at(0).y == spieler.at(s).schlange.position.at(i).y ))
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
	system( "color 84" );

    Spielfeld spielfeld;
    Punkte punkte;

    punkte.essen.position.resize(1);
    punkte.geld.position.resize(1);
    punkte.leben.position.resize(1);
    punkte.hindernis.position.resize(10);

    punkte.essen.farbe = 240;
    punkte.geld.farbe = 224;
    punkte.leben.farbe = 192;
    punkte.hindernis.farbe = 128;

    vector <Spieler> spieler( eingaben( spielfeld, spieler ) );

    for( unsigned int i = 0; i < spieler.size(); i ++ )
    {
        spieler.at(i).gebaeude.resize(10);

        spieler.at(i).gebaeude.at(0).name = "BAUPLATZ         ";

        spieler.at(i).gebaeude.at(1).name = "KANONE           ";
        spieler.at(i).gebaeude.at(1).kosten = 1000;
        spieler.at(i).gebaeude.at(1).start_pos.x = spielfeld.groesse.x / 2;
        spieler.at(i).gebaeude.at(1).start_pos.y = spielfeld.groesse.y / 2;
        spieler.at(i).gebaeude.at(1).ende_pos.x = spieler.at(i).gebaeude.at(1).start_pos.x + 4;
        spieler.at(i).gebaeude.at(1).ende_pos.y = spieler.at(i).gebaeude.at(1).start_pos.y + 4;

        spieler.at(i).gebaeude.at(2).name = "KRANKENHAUS      ";
        spieler.at(i).gebaeude.at(2).kosten = 1500;

        spieler.at(i).gebaeude.at(3).name = "GELDLAGER        ";
        spieler.at(i).gebaeude.at(3).kosten = 1000;
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

    if( spieler.size() >= 1 )
    {
        spieler.at(0).name = "MOONY     ";
        spieler.at(0).farbe.resize(2);
        spieler.at(0).farbe.at(0) = 200;
        spieler.at(0).farbe.at(1) = 253;

        spieler.at(0).gebaeude.at(0).start_pos.x = 1;
        spieler.at(0).gebaeude.at(0).start_pos.y = 1;
        spieler.at(0).gebaeude.at(0).ende_pos.x = 30;
        spieler.at(0).gebaeude.at(0).ende_pos.y = 30;

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
        spieler.at(1).name = "PRONGS    ";
        spieler.at(1).farbe.resize(2);
        spieler.at(1).farbe.at(0) = 15;
        spieler.at(1).farbe.at(1) = 241;

        spieler.at(1).gebaeude.at(0).start_pos.x = spielfeld.groesse.x - 29;
        spieler.at(1).gebaeude.at(0).start_pos.y = 1;
        spieler.at(1).gebaeude.at(0).ende_pos.x = spielfeld.groesse.x;
        spieler.at(1).gebaeude.at(0).ende_pos.y = 30;

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
        spieler.at(2).name = "PADFOOT     ";
        spieler.at(2).farbe.resize(2);
        spieler.at(2).farbe.at(0) = 52;
        spieler.at(2).farbe.at(1) = 100;

        spieler.at(2).gebaeude.at(0).start_pos.x = 1;
        spieler.at(2).gebaeude.at(0).start_pos.y = spielfeld.groesse.y - 29;
        spieler.at(2).gebaeude.at(0).ende_pos.x = 30;
        spieler.at(2).gebaeude.at(0).ende_pos.y = spielfeld.groesse.y;

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
        spieler.at(3).name = "WORMTAIL     ";
        spieler.at(3).farbe.resize(2);
        spieler.at(3).farbe.at(0) = 180;
        spieler.at(3).farbe.at(1) = 280;

        spieler.at(3).gebaeude.at(0).start_pos.x = spielfeld.groesse.x - 29;
        spieler.at(3).gebaeude.at(0).start_pos.y = spielfeld.groesse.y - 29;
        spieler.at(3).gebaeude.at(0).ende_pos.x = spielfeld.groesse.x;
        spieler.at(3).gebaeude.at(0).ende_pos.y = spielfeld.groesse.y;

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

            spieler.at(i).tasten.menue_spieler = 'X';
        }
    }

    for( unsigned int i = 0; i < spieler.size(); i ++ )
    {
        spieler.at(i).schlange.position.resize( spieler.at(i).schlange.laenge );
        spieler.at(i).schlange.richtung = ' ';

        spieler.at(i).schlange.position.at(0).x = spielfeld.groesse.x / spieler.size() * i + spielfeld.groesse.x / ( spieler.size() * 2 );
        spieler.at(i).schlange.position.at(0).y = spielfeld.groesse.y / 2 + 1;

        spieler.at(i).punkt.position.resize(0);
    }

    punkte_erstellen( punkte.essen, spielfeld, spieler );
    punkte_erstellen( punkte.hindernis, spielfeld, spieler );

    spiel( spielfeld, spieler, punkte );

    return 0;
}
