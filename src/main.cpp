#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <time.h>


struct Datum
{
	unsigned int
		tag,
		monat,
		jahr;
};

struct Zeitmessung
{
	double
		start = clock(),
		ende,
		pause;
};

struct Koordinaten
{
	unsigned int x, y;
};

struct Tasten
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
};

struct Seite
{
	std::string name;
	unsigned int naechste_seite;
};

struct Farben
{
	unsigned int
		hintergrund,
		spielfeld = 600,
		wand = 200;
};

struct Spielfeld
{
	Koordinaten groesse;
	Farben farbe;
	
	bool
		cheats = false,
		ton = false,
		cursor = true;
	
	unsigned int pause = 10;
	
	char
		beenden = '!',
		menue_pause = ' ',
		menue_cheats = '0';
	
	std::vector <Seite> seite_menue;
	
	Zeitmessung zeit;
};

struct Schlange
{
	std::vector <Koordinaten> pos;
	
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
};

struct Punkt
{
	Koordinaten pos;
	
	bool wand = false;
	
	unsigned char
		richtung,
		zeichen;
	
	unsigned int
		farbe;
	
	Zeitmessung
		zeit;
};

struct Gebaeude_y
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
	
	std::vector <Punkt> punkt;
	
	Zeitmessung zeit_betreten;
	Zeitmessung zeit_ereignis;
};

struct Gebaeude_x
{
	std::string
		name,
		info;
	
	long long kosten;
	
	std::vector <Gebaeude_y> _;
};

struct Gebaeude
{
	Gebaeude_x zentrale;
	Gebaeude_x kanone;
	Gebaeude_x krankenhaus;
	Gebaeude_x geldlager;
	Gebaeude_x mauer;
	Gebaeude_x teleporter;
};

struct Spieler
{
	std::string name;
	
	long long
		punkte,
		leben,
		geld,
		menue_seite;
	
	bool
		computer = false,
		gameover = false;
	
	std::vector <unsigned int> farbe;
	
	Schlange schlange;
	Gebaeude gebaeude;
	Tasten tasten;
};

struct Punkte
{
	std::vector <Punkt> essen;
	
	std::vector <Punkt> geld;
	std::vector <Punkt> leben;
	Zeitmessung zeit;
	
	std::vector <Punkt> hindernis;
};

struct Spiel_info
{
	std::string
		name,
		version;
	
	Datum datum;
};

struct Spiel
{
	std::string name;
	Spielfeld spielfeld;
	std::vector <Spieler> spieler;
	Punkte punkte;
};



void zeile(char zeichen);
void spielanleitung(Spiel_info& spiel_info);

int eingaben(Spielfeld &spielfeld, std::vector <Spieler> &spieler);


void spiel_start(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Punkte &punkte, time_t t);


void spielfeld_erstellen(Spielfeld &spielfeld, std::vector <Spieler> &spieler);
void punkte_erstellen(std::vector <Punkt> &punkt, Spielfeld &spielfeld, std::vector <Spieler> &spieler, time_t t);
void punkte_zeichnen(std::vector <Punkt> &punkt);
void gebaeude_zeichnen(std::vector <Spieler> &spieler, Gebaeude_x &gebaeude, unsigned int s, unsigned int g);


void richtung(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Punkte &punkte, time_t t);
void richtung_spieler(char richtung, std::vector <Spieler> &spieler);
void richtung_computer(std::vector <Spieler> &spieler, Punkte &punkte);

void bewegen(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Punkte &punkte, unsigned long long zaehler, time_t t);
void gebaeude_betreten(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Gebaeude_x &gebaeude, unsigned long long s);
void spieler_bewegen(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Punkte &punkte, unsigned long long zaehler, unsigned int s, time_t t);

void punkte_essen(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Punkte &punkte, unsigned int s, time_t t);
void punkte_geld(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Punkte &punkte, unsigned int s);
void punkte_leben(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Punkte &punkte, unsigned int s);

void gebaeude_farbe(std::vector <Spieler> spieler, unsigned int x, unsigned int y, std::vector <Gebaeude_x> gebaeude, unsigned long long s, unsigned int i);
void gebaeude(Spielfeld &spielfeld, std::vector <Spieler> &spieler, unsigned int s);
void punkte_bewegen(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Punkte &punkte, unsigned int s,  time_t t);

void spieler_informationen(Spielfeld spielfeld, std::vector <Spieler> spieler, unsigned int s);
void spieler_menue(Spielfeld &spielfeld, std::vector <Spieler> &spieler, unsigned int s);
void gebaeude_verschieben(Spielfeld &spielfeld, std::vector <Spieler> &spieler, std::vector <Gebaeude_x> &gebaeude, unsigned long long s, bool &v);
void gebaeude_kaufen(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Gebaeude_x &gebaeude, unsigned long long s);


void menue_pause(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Punkte &punkte, time_t t);
void menue_cheats(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Punkte &punkte, time_t t);


void leben(Spielfeld &spielfeld, std::vector <Spieler> &spieler, unsigned int s);
bool gameover(Spielfeld &spielfeld, std::vector <Spieler> &spieler, std::vector <Punkt> &hindernis, unsigned int s);
void gebaeude_gameover(Spielfeld &spielfeld, std::vector <Spieler> &spieler, std::vector <Gebaeude_x> &gebaeude, unsigned long long s, unsigned long long sp);


void farben();



void zeile(char zeichen)
{
	std::cout << '\n';
	for (unsigned int z = 0; z < 100; z ++)
	{
		std::cout << zeichen;
	}
	std::cout << "\n\n";
}

void spielanleitung(Spiel_info& spiel_info, std::vector <Spieler> &spieler)
{
	std::cout << "SPIELANLEITUNG SNAKE\n";
	zeile('*');
	
	std::cout
		<< "INFORMATIONEN ZUM SPIEL\n"
		<< '\n'
		<< "Name:\t\t" << spiel_info.name << '\n'
		<< "Version:\t" << spiel_info.version << '\n'
		<< "Datum:\t\t" << spiel_info.datum.tag << '.' << spiel_info.datum.monat << '.' << spiel_info.datum.jahr << '\n';
	
	zeile('*');
	
	std::cout
		<< "ENTWICKLER\n"
		<< '\n'
		<< "Name:\t\tRaffer Paul\n"
		<< "Schule:\t\tHTBL Hollabrunn\n"
		<< "Klasse:\t\t1BHEL\n"
		<< "Katalognummer:\t22\n";
	
	zeile('*');
	
	std::cout
		<< "SPIELFELD\n"
		<< '\n'
		<< "Es kann mit voreingestellter Spielfeldgroesse gespielt (\"1\" oder \"2\" druecken, 1: X=156 Y=71, 2: X=235 Y=63) oder die Spielfeldgroesse vor dem Spiel eingegeben werden.\n"
		<< '\n'
		<< "  0 1 2 3 4 5\n"
		<< "0 + + + + + +\n"
		<< "1 +         +\n"
		<< "2 +         +\n"
		<< "3 +         +\n"
		<< "4 +         +\n"
		<< "5 + + + + + +\n";
	
	zeile('*');
	
	std::cout
		<< "STEUERUNG\n"
		<< '\n'
		<< "In den Einstellungen kann man die Tasten, die für die Steuerung verwendet werden festlegen.\n"
		<< "Folgende Tasten sind im Moment eingestellt:\n";
	
	for (unsigned int s = 0; s < spieler.size(); s ++)
	{
		std::cout
			<< "\n\n"
			<< spieler.at(s).name << '\n'
			<< '\n'
			<< spieler.at(s).tasten.oben_links << "   " << spieler.at(s).tasten.oben << "   " << spieler.at(s).tasten.oben_rechts << '\n'
			<< "  \\ | /\n"
			<< spieler.at(s).tasten.links << " --" << spieler.at(s).tasten.menue << "-- " << spieler.at(s).tasten.rechts << '\n'
			<< "  / | \\\n"
			<< spieler.at(s).tasten.unten_links << "   " << spieler.at(s).tasten.unten << "   " << spieler.at(s).tasten.unten_rechts << '\n'
			<< '\n'
			<< "Oben:\t\t" << spieler.at(s).tasten.oben << '\n'
			<< "Unten:\t\t" << spieler.at(s).tasten.unten << '\n'
			<< "Links:\t\t" << spieler.at(s).tasten.links << '\n'
			<< "Rechts:\t\t" << spieler.at(s).tasten.rechts << '\n'
			<< '\n'
			<< "Obenlinks:\t" << spieler.at(s).tasten.oben_links << '\n'
			<< "Obenrechts:\t" << spieler.at(s).tasten.oben_rechts << '\n'
			<< "Untenlinks:\t" << spieler.at(s).tasten.unten_links << '\n'
			<< "Untenrechts:\t" << spieler.at(s).tasten.unten_rechts << '\n'
			<< '\n'
			<< "Pause:\t\t" << spieler.at(s).tasten.menue << '\n';
	}
	
	zeile('*');
	
	std::cout
		<< "GEBAEUDE\n"
		<< '\n'
		<< spieler.at(0).gebaeude.zentrale.name << '\n'
		<< spieler.at(0).gebaeude.zentrale.kosten << "Euro\n"
		<< spieler.at(0).gebaeude.zentrale.info << '\n'
		<< '\n'
		<< spieler.at(0).gebaeude.kanone.name << '\n'
		<< spieler.at(0).gebaeude.kanone.kosten << "Euro\n"
		<< spieler.at(0).gebaeude.kanone.info << '\n'
		<< '\n'
		<< spieler.at(0).gebaeude.krankenhaus.name << '\n'
		<< spieler.at(0).gebaeude.krankenhaus.kosten << "Euro\n"
		<< spieler.at(0).gebaeude.krankenhaus.info << '\n'
		<< '\n'
		<< spieler.at(0).gebaeude.geldlager.name << '\n'
		<< spieler.at(0).gebaeude.geldlager.kosten << "Euro\n"
		<< spieler.at(0).gebaeude.geldlager.info << '\n'
		<< '\n'
		<< spieler.at(0).gebaeude.mauer.name << '\n'
		<< spieler.at(0).gebaeude.mauer.kosten << "Euro\n"
		<< spieler.at(0).gebaeude.mauer.info << '\n';
	
	zeile('*');
}

int eingaben(Spielfeld &spielfeld, std::vector <Spieler> &spieler)
{
	int s;
	
	switch (getch())
	{
	case '1':
		s = 4;
		spielfeld.groesse.x = 156;
		spielfeld.groesse.y = 71;
		break;
	
	case '2':
		s = 4;
		spielfeld.groesse.x = 235;
		spielfeld.groesse.y = 63;
		break;
	
	default:
		std::cout << "ANZAHL DER SPIELER: ";
		std::cin >> s;
	
		std::cout << "SPIELFELDGROESSE:\nX: ";
		std::cin >> spielfeld.groesse.x;
	
		std::cout << "Y: ";
		std::cin >> spielfeld.groesse.y;
		break;
	}
	return s;
}


void spiel_start(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Punkte &punkte, time_t t)
{
	bool wiederholen = true;
	
	spielfeld_erstellen(spielfeld, spieler);
	
	for (unsigned int s = 0; s < spieler.size(); s ++)
	{
		spieler_informationen(spielfeld, spieler, s);
	}
	
	for (unsigned int s = 0; s < spieler.size(); s ++)
	{
		for (unsigned int g = 0; g < spieler.at(s).gebaeude.zentrale._.size(); g ++)
		{
			if (spieler.at(s).gebaeude.zentrale._.at(g).gebaut == true)
				gebaeude_zeichnen(spieler, spieler.at(s).gebaeude.zentrale, s, g);
		}
		
		for (unsigned int g = 0; g < spieler.at(s).gebaeude.kanone._.size(); g ++)
		{
			if (spieler.at(s).gebaeude.kanone._.at(g).gebaut == true)
				gebaeude_zeichnen(spieler, spieler.at(s).gebaeude.kanone, s, g);
		}
		
		for (unsigned int g = 0; g < spieler.at(s).gebaeude.krankenhaus._.size(); g ++)
		{
			if (spieler.at(s).gebaeude.krankenhaus._.at(g).gebaut == true)
				gebaeude_zeichnen(spieler, spieler.at(s).gebaeude.krankenhaus, s, g);
		}
		
		for (unsigned int g = 0; g < spieler.at(s).gebaeude.geldlager._.size(); g ++)
		{
			if (spieler.at(s).gebaeude.geldlager._.at(g).gebaut == true)
				gebaeude_zeichnen(spieler, spieler.at(s).gebaeude.geldlager, s, g);
		}
		
		for (unsigned int g = 0; g < spieler.at(s).gebaeude.teleporter._.size(); g ++)
		{
			if (spieler.at(s).gebaeude.teleporter._.at(g).gebaut == true)
				gebaeude_zeichnen(spieler, spieler.at(s).gebaeude.teleporter, s, g);
		}
	}
	
	punkte_zeichnen(punkte.hindernis);
	punkte_zeichnen(punkte.essen);
	
	
	for (static unsigned long long zaehler = 0; wiederholen == true; zaehler ++)
	{
		richtung(spielfeld, spieler, punkte, t);
	
		bewegen(spielfeld, spieler, punkte, zaehler, t);
	
		wiederholen = true;
	
		for (unsigned int i = 0; i < spieler.size(); i ++)
		{
			if (spieler.at(i).gameover == true)
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


void spielfeld_erstellen(Spielfeld &spielfeld, std::vector <Spieler> &spieler)
{
	system("cls");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe.wand);
	
	for (unsigned int y = 0; y <= spielfeld.groesse.y + 1; y ++)
	{
		for (unsigned int x = 0; x <= spielfeld.groesse.x + 1; x ++)
		{
			if ((x == 0) || (x == spielfeld.groesse.x + 1)
			|| (y == 0) || (y == spielfeld.groesse.y + 1))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe.wand);
				std::cout << '+';
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe.spielfeld);
				std::cout << ' ';
			}
		}
		std::cout << '\n';
	}
	
	for (unsigned int sp = 0; sp < spieler.size(); sp ++)
	{
		for (unsigned int i = 0; i < spieler.at(sp).schlange.pos.size(); i ++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(sp).farbe.at(i % spieler.at(sp).farbe.size()));
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spieler.at(sp).schlange.pos.at(i).x, spieler.at(sp).schlange.pos.at(i).y});
			
			if ((spieler.at(sp).schlange.name_anzeigen == true) && (i < spieler.at(sp).name.size()))
			{
				std::cout << spieler.at(sp).name.at(i);
			}
			else
			{
				std::cout << ' ';
			}
		}
	}
}


void punkte_erstellen(std::vector <Punkt> &punkt, Spielfeld &spielfeld, std::vector <Spieler> &spieler, time_t t)
{
	bool wiederholen = false;
	
	for (unsigned int p = 0; p < punkt.size(); p ++)
	{
		do
		{
			wiederholen = false;
			
			punkt.at(p).pos.x = (rand() % spielfeld.groesse.x) + 1;
			punkt.at(p).pos.y = (rand() % spielfeld.groesse.y) + 1;
	
			for (unsigned int s = 0; s < spieler.size(); s ++)
			{
				for (unsigned int i = 0; i < spieler.at(s).schlange.pos.size(); i ++)
				{
					if ((punkt.at(p).pos.x == spieler.at(s).schlange.pos.at(i).x) && (punkt.at(p).pos.y == spieler.at(s).schlange.pos.at(i).y))
					{
						wiederholen = true;
					}
				}
			}
			
			for (unsigned int j = 0; j < p; j ++)
			{
				if ((punkt.at(p).pos.x == punkt.at(j).pos.x) && (punkt.at(p).pos.y == punkt.at(j).pos.y))
				{
					wiederholen = true;
				}
			}
		}
		while (wiederholen == true);
	}
}


void punkte_zeichnen(std::vector <Punkt> &punkt)
{
	for (unsigned int p = 0; p < punkt.size(); p ++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), punkt.at(p).farbe);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {punkt.at(p).pos.x, punkt.at(p).pos.y});
		std::cout << punkt.at(p).zeichen;
	}
}


void richtung(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Punkte &punkte, time_t t)
{
	if (spielfeld.ton == true)
	{
		Beep(1350, spielfeld.pause);
	}
	else if (spielfeld.ton == false)
	{
		Sleep(spielfeld.pause);
	}
	if (kbhit())
	{
		char richtung = getch();
		
		if (richtung == spielfeld.beenden)
		{
		
		}
		else if (richtung == spielfeld.menue_pause)
		{
			menue_pause(spielfeld, spieler, punkte, t);
		}
		else if (richtung == spielfeld.menue_cheats)
		{
			menue_cheats(spielfeld, spieler, punkte, t);
		}
		richtung_spieler(richtung, spieler);
	}
	richtung_computer(spieler, punkte);
}


void gebaeude_zeichnen(std::vector <Spieler> &spieler, Gebaeude_x &gebaeude, unsigned int s, unsigned int g)
{
	for (unsigned int y = gebaeude._.at(g).start_pos.y; y <= gebaeude._.at(g).ende_pos.y; y ++)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {gebaeude._.at(g).start_pos.x, y});
	
		for (unsigned int x = gebaeude._.at(g).start_pos.x; x <= gebaeude._.at(g).ende_pos.x; x ++)
		{
			if (((gebaeude.name == "Geldlager") && ((x == gebaeude._.at(g).start_pos.x) || (x == gebaeude._.at(g).ende_pos.x) || (y == gebaeude._.at(g).start_pos.y) || (y == gebaeude._.at(g).ende_pos.y)))
			|| ((gebaeude.name == "Krankenhaus") && ((x - gebaeude._.at(g).start_pos.x == (gebaeude._.at(g).ende_pos.x - gebaeude._.at(g).start_pos.x) / 2) || (y - gebaeude._.at(g).start_pos.y == (gebaeude._.at(g).ende_pos.y - gebaeude._.at(g).start_pos.y) / 2)))
			|| (gebaeude.name == "Mauer")
			|| ((gebaeude.name == "Teleporter") && ((x - gebaeude._.at(g).start_pos.x == y - gebaeude._.at(g).start_pos.y) || (x - gebaeude._.at(g).start_pos.x + y - gebaeude._.at(g).start_pos.y == gebaeude._.at(g).ende_pos.x - gebaeude._.at(g).start_pos.x))))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(1));
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(0));
			}
			std::cout << ' ';
		}
	}
}


void richtung_spieler(char richtung, std::vector <Spieler> &spieler)
{
	bool wiederholen;
	unsigned int sp = 0;
	
	do
	{
		wiederholen = false;
	
		if ((richtung == spieler.at(sp).tasten.menue)
		|| (((richtung == spieler.at(sp).tasten.oben) && ((spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.unten) || (spieler.at(sp).schlange.bewegen == false)))
		|| ((richtung == spieler.at(sp).tasten.unten) && ((spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.oben) || (spieler.at(sp).schlange.bewegen == false)))
		|| ((richtung == spieler.at(sp).tasten.links) && ((spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.rechts) || (spieler.at(sp).schlange.bewegen == false)))
		|| ((richtung == spieler.at(sp).tasten.rechts) && ((spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.links) || (spieler.at(sp).schlange.bewegen == false)))
		|| ((spieler.at(sp).schlange.diagonal_fahren == true) && (richtung == spieler.at(sp).tasten.oben_links) && (spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.unten_rechts))
		|| ((spieler.at(sp).schlange.diagonal_fahren == true) && (richtung == spieler.at(sp).tasten.oben_rechts) && (spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.unten_links))
		|| ((spieler.at(sp).schlange.diagonal_fahren == true) && (richtung == spieler.at(sp).tasten.unten_links) && (spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.oben_rechts))
		|| ((spieler.at(sp).schlange.diagonal_fahren == true) && (richtung == spieler.at(sp).tasten.unten_rechts) && (spieler.at(sp).schlange.richtung != spieler.at(sp).tasten.oben_links))))
		{
			if (spieler.at(sp).schlange.bewegen == true)
			{
				spieler.at(sp).schlange.richtung_alt = spieler.at(sp).schlange.richtung;
			}
			spieler.at(sp).schlange.richtung = richtung;
		}
		else if (sp < spieler.size() - 1)
		{
			sp ++;
			wiederholen = true;
		}
	}
	while (wiederholen == true);
}


void richtung_computer(std::vector <Spieler> &spieler, Punkte &punkte)
{
	for (unsigned int i = 0; i < spieler.size(); i ++)
	{
		if (spieler.at(i).computer == true)
		{
			if ((punkte.essen.at(0).pos.y < spieler.at(i).schlange.pos.at(0).y) && (spieler.at(i).schlange.richtung != spieler.at(i).tasten.unten))
			{
				spieler.at(i).schlange.richtung = spieler.at(i).tasten.oben;
			}
			else if ((punkte.essen.at(0).pos.y > spieler.at(i).schlange.pos.at(0).y) && (spieler.at(i).schlange.richtung != spieler.at(i).tasten.oben))
			{
				spieler.at(i).schlange.richtung = spieler.at(i).tasten.unten;
			}
			else if ((punkte.essen.at(0).pos.x < spieler.at(i).schlange.pos.at(0).x) && (spieler.at(i).schlange.richtung != spieler.at(i).tasten.rechts))
			{
				spieler.at(i).schlange.richtung = spieler.at(i).tasten.links;
			}
			else if ((punkte.essen.at(0).pos.x > spieler.at(i).schlange.pos.at(0).x) && (spieler.at(i).schlange.richtung != spieler.at(i).tasten.links))
			{
				spieler.at(i).schlange.richtung = spieler.at(i).tasten.rechts;
			}
		}
	}
}

void gebaeude_betreten(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Gebaeude_x &gebaeude, unsigned long long s)
{
	for (unsigned int i = 0; i < gebaeude._.size(); i ++)
	{
		if ((gebaeude._.at(i).gebaut == true)
				&& (gebaeude._.at(i).verschieben == false)
				&& (gebaeude._.at(i).betreten == false)
				&& (spieler.at(s).schlange.pos.at(0).x <= gebaeude._.at(i).ende_pos.x)
				&& (spieler.at(s).schlange.pos.at(0).y <= gebaeude._.at(i).ende_pos.y)
				&& (spieler.at(s).schlange.pos.at(0).x >= gebaeude._.at(i).start_pos.x)
				&& (spieler.at(s).schlange.pos.at(0).y >= gebaeude._.at(i).start_pos.y))
		{
			spieler.at(s).schlange.bewegen = false;
			gebaeude._.at(i).betreten = true;
			gebaeude._.at(i).zeit_betreten.start = clock();
		}
		else if (gebaeude._.at(i).betreten == true)
		{
			spieler.at(s).schlange.bewegen = true;
			gebaeude._.at(i).betreten = false;
		}
	}
}

void bewegen(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Punkte &punkte, unsigned long long zaehler, time_t t)
{
	for (unsigned int s = 0; s < spieler.size(); s ++)
	{
		if (spieler.at(s).schlange.richtung == spieler.at(s).tasten.menue)
		{
			gebaeude_betreten(spielfeld, spieler, spieler.at(s).gebaeude.zentrale, s);
			gebaeude_betreten(spielfeld, spieler, spieler.at(s).gebaeude.kanone, s);
			gebaeude_betreten(spielfeld, spieler, spieler.at(s).gebaeude.krankenhaus, s);
			gebaeude_betreten(spielfeld, spieler, spieler.at(s).gebaeude.geldlager, s);
			gebaeude_betreten(spielfeld, spieler, spieler.at(s).gebaeude.teleporter, s);
	
			spieler.at(s).schlange.richtung = spieler.at(s).schlange.richtung_alt;
		}
		
		for (unsigned int i = 0; i < spieler.at(s).gebaeude.zentrale._.size(); i ++)
		{
			if (spieler.at(s).gebaeude.zentrale._.at(i).betreten == true)
			{
				spieler_menue(spielfeld, spieler, s);
				punkte_zeichnen(punkte.essen);
				punkte_zeichnen(punkte.geld);
				punkte_zeichnen(punkte.leben);
				punkte_zeichnen(punkte.hindernis);
			}
		}
		
		for (unsigned int i = 0; i < spieler.at(s).gebaeude.kanone._.size(); i ++)
		{
			if (spieler.at(s).gebaeude.kanone._.at(i).betreten == true)
			{
				if ((spieler.at(s).schlange.richtung == spieler.at(s).tasten.oben)
				|| (spieler.at(s).schlange.richtung == spieler.at(s).tasten.unten)
				|| (spieler.at(s).schlange.richtung == spieler.at(s).tasten.links)
				|| (spieler.at(s).schlange.richtung == spieler.at(s).tasten.rechts))
				{
					spieler.at(s).gebaeude.kanone._.at(i).richtung = spieler.at(s).schlange.richtung;
				}
			}
		}
		
		for (unsigned int i = 0; i < spieler.at(s).gebaeude.krankenhaus._.size(); i ++)
		{
			if (spieler.at(s).gebaeude.krankenhaus._.at(i).betreten == true)
			{
				spieler.at(s).gebaeude.krankenhaus._.at(i).zeit_betreten.ende = clock() - spieler.at(s).gebaeude.krankenhaus._.at(i).zeit_betreten.start;
				
				if (spieler.at(s).gebaeude.krankenhaus._.at(i).zeit_betreten.ende >= spieler.at(s).gebaeude.krankenhaus._.at(i).zeit_betreten.pause)
				{
					spieler.at(s).leben ++;
					spieler.at(s).gebaeude.krankenhaus._.at(i).zeit_betreten.start = clock();
				}
			}
		}
		
		for (unsigned int i = 0; i < spieler.at(s).gebaeude.geldlager._.size(); i ++)
		{
			if (spieler.at(s).gebaeude.geldlager._.at(i).betreten == true)
			{
				if (spieler.at(s).schlange.richtung == spieler.at(s).tasten.oben)
				{
					spieler.at(s).gebaeude.geldlager._.at(i).zahl += spieler.at(s).geld;
					spieler.at(s).geld = 0;
				}
				
				else if (spieler.at(s).schlange.richtung == spieler.at(s).tasten.unten)
				{
					spieler.at(s).geld += spieler.at(s).gebaeude.geldlager._.at(i).zahl;
					spieler.at(s).gebaeude.geldlager._.at(i).zahl = 0;
				}
			}
		}
		
		if (spieler.at(s).schlange.bewegen == true)
		{
			spieler_bewegen(spielfeld, spieler, punkte, zaehler, s, t);
		}
		
		gebaeude(spielfeld, spieler, s);
		punkte_bewegen(spielfeld, spieler, punkte, s, t);
		
		if (spielfeld.cursor == false)
		{
			SetCursorPos(2000, 2000);
		}
	}
	
	static unsigned int zufall;
	
	punkte.zeit.ende = clock() - punkte.zeit.start;
	
	if (punkte.zeit.ende > 8000)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe.spielfeld);
	
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {punkte.geld.at(0).pos.x, punkte.geld.at(0).pos.y});
		std::cout << ' ';
		punkte.geld.at(0).pos.x = 0;
		punkte.geld.at(0).pos.y = 0;
		
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {punkte.leben.at(0).pos.x, punkte.leben.at(0).pos.y});
		std::cout << ' ';
		punkte.leben.at(0).pos.x = 0;
		punkte.leben.at(0).pos.y = 0;
	}
	
	if ((punkte.zeit.ende > 20000))
	{
		punkte.zeit.start = clock();
		
		zufall = rand() % 2 ;
		if (zufall == 0)
		{
			punkte_erstellen(punkte.geld, spielfeld, spieler, t);
			punkte_zeichnen(punkte.geld);
		}
		else if (zufall == 1)
		{
			punkte_erstellen(punkte.leben, spielfeld, spieler, t);
			punkte_zeichnen(punkte.leben);
		}
	}
}

void gebaeude_farbe(std::vector <Spieler> spieler, unsigned int x, unsigned int y, Gebaeude_x &gebaeude, unsigned long long s, unsigned int i)
{
	for (unsigned int g = 0; g < gebaeude._.size(); g ++)
	{
		if ((x <= gebaeude._.at(g).ende_pos.x)
				&& (y <= gebaeude._.at(g).ende_pos.y)
				&& (x >= gebaeude._.at(g).start_pos.x)
				&& (y >= gebaeude._.at(g).start_pos.y)
				&& (gebaeude._.at(g).gebaut == true))
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(i).farbe.at(0));
		}
	}
}

void punkte_essen(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Punkte &punkte, unsigned int s, time_t t)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(0));
	
	spieler.at(s).punkte ++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 3});
	std::cout << spieler.at(s).punkte;
	
	spieler.at(s).schlange.pos.resize(spieler.at(s).schlange.pos.size() + 1);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 4});
	std::cout << spieler.at(s).schlange.pos.size();
	
	spieler.at(s).geld += rand() % 11;
	
	spieler_informationen(spielfeld, spieler, s);
	punkte_erstellen(punkte.essen, spielfeld, spieler, t);
	punkte_zeichnen(punkte.essen);
}

void punkte_geld(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Punkte &punkte, unsigned int s)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(0));
	
	spieler.at(s).geld += (clock() - spielfeld.zeit.start) / 1000;
	punkte.geld.at(0).pos.x = 0;
	punkte.geld.at(0).pos.y = 0;
	
	spieler_informationen(spielfeld, spieler, s);
}

void punkte_leben(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Punkte &punkte, unsigned int s)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(0));
	
	spieler.at(s).leben += 1;
	punkte.leben.at(0).pos.x = 0;
	punkte.leben.at(0).pos.y = 0;
	
	spieler_informationen(spielfeld, spieler, s);
}


void spieler_bewegen(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Punkte &punkte, unsigned long long zaehler, unsigned int s, time_t t)
{
	spieler.at(s).schlange.zeit.ende = clock() - spieler.at(s).schlange.zeit.start;
	
	if ((spieler.at(s).schlange.zeit.ende >= spieler.at(s).schlange.zeit.pause) && (spieler.at(s).gameover == false))
	{
		spieler.at(s).schlange.zeit.start = clock();
	
		for (unsigned int i = 0; i < spieler.at(s).schlange.pos.size(); i ++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(i % spieler.at(s).farbe.size()));
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spieler.at(s).schlange.pos.at(i).x, spieler.at(s).schlange.pos.at(i).y});
	
			if ((spieler.at(s).schlange.name_anzeigen == true) && (i < spieler.at(s).name.size()))
			{
				std::cout << spieler.at(s).name.at(i);
			}
	
			else
			{
				std::cout << ' ';
			}
		}
	
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe.spielfeld);
	
		for (unsigned int i = 0; i < spieler.size(); i ++)
		{
			gebaeude_farbe(spieler, spieler.at(s).schlange.pos.at(spieler.at(s).schlange.pos.size() - 1).x, spieler.at(s).schlange.pos.at(spieler.at(s).schlange.pos.size() - 1).y, spieler.at(i).gebaeude.zentrale, s, i);
			gebaeude_farbe(spieler, spieler.at(s).schlange.pos.at(spieler.at(s).schlange.pos.size() - 1).x, spieler.at(s).schlange.pos.at(spieler.at(s).schlange.pos.size() - 1).y, spieler.at(i).gebaeude.kanone, s, i);
			gebaeude_farbe(spieler, spieler.at(s).schlange.pos.at(spieler.at(s).schlange.pos.size() - 1).x, spieler.at(s).schlange.pos.at(spieler.at(s).schlange.pos.size() - 1).y, spieler.at(i).gebaeude.krankenhaus, s, i);
			gebaeude_farbe(spieler, spieler.at(s).schlange.pos.at(spieler.at(s).schlange.pos.size() - 1).x, spieler.at(s).schlange.pos.at(spieler.at(s).schlange.pos.size() - 1).y, spieler.at(i).gebaeude.geldlager, s, i);
			gebaeude_farbe(spieler, spieler.at(s).schlange.pos.at(spieler.at(s).schlange.pos.size() - 1).x, spieler.at(s).schlange.pos.at(spieler.at(s).schlange.pos.size() - 1).y, spieler.at(i).gebaeude.mauer, s, i);
			gebaeude_farbe(spieler, spieler.at(s).schlange.pos.at(spieler.at(s).schlange.pos.size() - 1).x, spieler.at(s).schlange.pos.at(spieler.at(s).schlange.pos.size() - 1).y, spieler.at(i).gebaeude.teleporter, s, i);
		}
	
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spieler.at(s).schlange.pos.at(spieler.at(s).schlange.pos.size() - 1).x, spieler.at(s).schlange.pos.at(spieler.at(s).schlange.pos.size() - 1).y});
		std::cout << ' ';
	
		if (spieler.at(s).schlange.richtung != ' ')
		{
			for (int i = spieler.at(s).schlange.pos.size() - 1; i > 0; i --)
			{
				spieler.at(s).schlange.pos.at(i).x = spieler.at(s).schlange.pos.at(i - 1).x;
				spieler.at(s).schlange.pos.at(i).y = spieler.at(s).schlange.pos.at(i - 1).y;
			}
		}
	
		if (spieler.at(s).schlange.richtung == spieler.at(s).tasten.oben)
		{
			spieler.at(s).schlange.pos.at(0).y --;
		}
	
		else if (spieler.at(s).schlange.richtung == spieler.at(s).tasten.unten)
		{
			spieler.at(s).schlange.pos.at(0).y ++;
		}
	
		else if (spieler.at(s).schlange.richtung == spieler.at(s).tasten.links)
		{
			spieler.at(s).schlange.pos.at(0).x --;
		}
	
		else if (spieler.at(s).schlange.richtung == spieler.at(s).tasten.rechts)
		{
			spieler.at(s).schlange.pos.at(0).x ++;
		}
	
		else if (spieler.at(s).schlange.diagonal_fahren == true)
		{
			if (spieler.at(s).schlange.richtung == spieler.at(s).tasten.oben_links)
			{
				spieler.at(s).schlange.pos.at(0).y --;
				spieler.at(s).schlange.pos.at(0).x --;
			}
	
			else if (spieler.at(s).schlange.richtung == spieler.at(s).tasten.oben_rechts)
			{
				spieler.at(s).schlange.pos.at(0).y --;
				spieler.at(s).schlange.pos.at(0).x ++;
			}
	
			else if (spieler.at(s).schlange.richtung == spieler.at(s).tasten.unten_links)
			{
				spieler.at(s).schlange.pos.at(0).y ++;
				spieler.at(s).schlange.pos.at(0).x --;
			}
	
			else if (spieler.at(s).schlange.richtung == spieler.at(s).tasten.unten_rechts)
			{
				spieler.at(s).schlange.pos.at(0).y ++;
				spieler.at(s).schlange.pos.at(0).x ++;
			}
		}
		
		// STEUERUNG
		// 
		//  SPIELER 1  *  SPIELER 2  *  SPIELER 3  *  SPIELER 4
		//             *             *             *
		//  q   w   e  *  r   t   z  *  u   i   o  *  7   8   9
		//    \ | /    *    \ | /    *    \ | /    *    \ | /
		//  a --+-- d  *  f --+-- h  *  j --+-- l  *  4 --+-- 6
		//    / | \    *    / | \    *    / | \    *    / | \
		//  y   s   c  *  v   g   n  *  m   k   .  *  1   5   3
		//             *             *             *
		//  Pause: x   *  Pause: v   *  Pause: ,   *  Pause: 2
		
		if (spieler.at(s).schlange.waende == false)
		{
			if (spieler.at(s).schlange.pos.at(0).y == 0)
			{
				spieler.at(s).schlange.pos.at(0).y = spielfeld.groesse.y;
			}
			
			if (spieler.at(s).schlange.pos.at(0).y == spielfeld.groesse.y + 1)
			{
				spieler.at(s).schlange.pos.at(0).y = 1;
			}
			
			if (spieler.at(s).schlange.pos.at(0).x == 0)
			{
				spieler.at(s).schlange.pos.at(0).x = spielfeld.groesse.x;
			}
			
			if (spieler.at(s).schlange.pos.at(0).x == spielfeld.groesse.x + 1)
			{
				spieler.at(s).schlange.pos.at(0).x = 1;
			}
		}
		
		if ((spieler.at(s).schlange.pos.at(0).x == punkte.essen.at(0).pos.x) && (spieler.at(s).schlange.pos.at(0).y == punkte.essen.at(0).pos.y))
		{
			punkte_essen(spielfeld, spieler, punkte, s, t);
		}
		
		if ((spieler.at(s).schlange.pos.at(0).x == punkte.geld.at(0).pos.x) && (spieler.at(s).schlange.pos.at(0).y == punkte.geld.at(0).pos.y))
		{
			punkte_geld(spielfeld, spieler, punkte, s);
		}
		
		if ((spieler.at(s).schlange.pos.at(0).x == punkte.leben.at(0).pos.x) && (spieler.at(s).schlange.pos.at(0).y == punkte.leben.at(0).pos.y))
		{
			punkte_leben(spielfeld, spieler, punkte, s);
		}
	}
	
	if (spieler.at(s).gameover == false)
	{
		spieler.at(s).gameover = gameover(spielfeld, spieler, punkte.hindernis, s);
	}
}


void gebaeude(Spielfeld &spielfeld, std::vector <Spieler> &spieler, unsigned int s)
{
	for (unsigned int i = 0; i < spieler.at(s).gebaeude.kanone._.size(); i ++)
	{
		spieler.at(s).gebaeude.kanone._.at(i).zeit_ereignis.ende = clock() - spieler.at(s).gebaeude.kanone._.at(i).zeit_ereignis.start;
		
		if ((spieler.at(s).gebaeude.kanone._.at(i).gebaut == true)
		&& (spieler.at(s).gebaeude.kanone._.at(i).verschieben == false)
		&& (spieler.at(s).gebaeude.kanone._.at(i).zeit_ereignis.ende >= 2000)
		&& (spieler.at(s).gebaeude.kanone._.at(i).richtung != ' '))
		{
			spieler.at(s).gebaeude.kanone._.at(i).zeit_ereignis.start = clock();
			if (spieler.at(s).gebaeude.kanone._.at(i).punkt.size() < spieler.at(s).gebaeude.kanone._.at(i).level)
			{
				spieler.at(s).gebaeude.kanone._.at(i).punkt.resize(spieler.at(s).gebaeude.kanone._.at(i).punkt.size() + 1);
				
				spieler.at(s).gebaeude.kanone._.at(i).punkt.at(spieler.at(s).gebaeude.kanone._.at(i).punkt.size() - 1).pos.x = (spieler.at(s).gebaeude.kanone._.at(i).start_pos.x + spieler.at(s).gebaeude.kanone._.at(i).ende_pos.x) / 2;
				spieler.at(s).gebaeude.kanone._.at(i).punkt.at(spieler.at(s).gebaeude.kanone._.at(i).punkt.size() - 1).pos.y = (spieler.at(s).gebaeude.kanone._.at(i).start_pos.y + spieler.at(s).gebaeude.kanone._.at(i).ende_pos.y) / 2;
				
				spieler.at(s).gebaeude.kanone._.at(i).punkt.at(spieler.at(s).gebaeude.kanone._.at(i).punkt.size() - 1).richtung = spieler.at(s).gebaeude.kanone._.at(i).richtung;
				spieler.at(s).gebaeude.kanone._.at(i).punkt.at(spieler.at(s).gebaeude.kanone._.at(i).punkt.size() - 1).zeit.pause = 100;
			}
		}
	}
}



void punkte_bewegen(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Punkte &punkte, unsigned int s, time_t t)
{
	for (unsigned long long i = 0; i < spieler.at(s).gebaeude.kanone._.size(); i ++)
	{
		for (unsigned long long p = 0; p < spieler.at(s).gebaeude.kanone._.at(i).punkt.size(); p ++)
		{
			spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).zeit.ende = clock() - spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).zeit.start;
			
			if (spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).zeit.ende >= spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).zeit.pause)
			{
				spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).zeit.start = clock();
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe.spielfeld);
				
				for (unsigned int sp = 0; sp < spieler.size(); sp ++)
				{
					gebaeude_farbe(spieler, spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.x, spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.y, spieler.at(sp).gebaeude.zentrale, s, sp);
					gebaeude_farbe(spieler, spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.x, spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.y, spieler.at(sp).gebaeude.kanone, s, sp);
					gebaeude_farbe(spieler, spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.x, spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.y, spieler.at(sp).gebaeude.krankenhaus, s, sp);
					gebaeude_farbe(spieler, spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.x, spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.y, spieler.at(sp).gebaeude.geldlager, s, sp);
					gebaeude_farbe(spieler, spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.x, spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.y, spieler.at(sp).gebaeude.mauer, s, sp);
					gebaeude_farbe(spieler, spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.x, spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.y, spieler.at(sp).gebaeude.teleporter, s, sp);
				}
				
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.x, spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.y});
				std::cout << ' ';
				
				if (spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).richtung == spieler.at(s).tasten.rechts)
				{
					spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.x ++;
				}
				
				if (spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).richtung == spieler.at(s).tasten.links)
				{
					spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.x --;
				}
				
				if (spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).richtung == spieler.at(s).tasten.unten)
				{
					spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.y ++;
				}
				
				if (spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).richtung == spieler.at(s).tasten.oben)
				{
					spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.y --;
				}
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(1));
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.x, spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.y});
				std::cout << ' ';
	
				if ((spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.x == punkte.essen.at(0).pos.x) && (spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.y == punkte.essen.at(0).pos.y))
				{
					punkte_essen(spielfeld, spieler, punkte, s, t);
				}
				
				if ((spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.x == punkte.geld.at(0).pos.x) && (spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.y == punkte.geld.at(0).pos.y))
				{
					punkte_geld(spielfeld, spieler, punkte, s);
				}
				
				if ((spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.x == punkte.leben.at(0).pos.x) && (spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.y == punkte.leben.at(0).pos.y))
				{
					punkte_leben(spielfeld, spieler, punkte, s);
				}
				
				for (unsigned int h = 0; h < punkte.hindernis.size(); h ++)
				{
					if ((spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.x == punkte.hindernis.at(h).pos.x) && (spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.y == punkte.hindernis.at(h).pos.y))
					{
						spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.x = 0;
						spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.y = 0;
						spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).richtung = ' ';
					}
				}
				
				if ((spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.x == 0)
				|| (spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.y == 0)
				|| (spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.x == spielfeld.groesse.x + 1)
				|| (spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.y == spielfeld.groesse.y + 1))
				{
					spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.x = (spieler.at(s).gebaeude.kanone._.at(i).start_pos.x + spieler.at(s).gebaeude.kanone._.at(i).ende_pos.x) / 2;
					spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).pos.y = (spieler.at(s).gebaeude.kanone._.at(i).start_pos.y + spieler.at(s).gebaeude.kanone._.at(i).ende_pos.y) / 2;
					
					spieler.at(s).gebaeude.kanone._.at(i).punkt.at(p).richtung = spieler.at(s).gebaeude.kanone._.at(i).richtung;
				}
			}
		}
	}
}


void spieler_informationen(Spielfeld spielfeld, std::vector <Spieler> spieler, unsigned int s)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(0));
	
	Gebaeude_x info;
	info._.resize(1);
	info._.at(0).start_pos.x = spielfeld.groesse.x / spieler.size() * s;
	info._.at(0).start_pos.y = spielfeld.groesse.y + 2;
	info._.at(0).ende_pos.x = spielfeld.groesse.x / spieler.size() * (s + 1) - 1;
	info._.at(0).ende_pos.y = spielfeld.groesse.y + 6;
	
	gebaeude_zeichnen(spieler, info, s, 0);
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 2});
	std::cout << "Name:   " << spieler.at(s).name;
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 3});
	std::cout << "Punkte: " << spieler.at(s).punkte;
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 4});
	std::cout << "Laenge: " << spieler.at(s).schlange.pos.size();
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 5});
	std::cout << "Geld:   " << spieler.at(s).geld << " Euro";
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 6});
	std::cout << "Leben:  " << spieler.at(s).leben;
}

void gebaeude_verschieben(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Gebaeude_x &gebaeude, unsigned long long s, bool &v)
{
	for (unsigned int i = 0; i < gebaeude._.size(); i ++)
	{
		if (gebaeude._.at(i).verschieben == true)
		{
			v = true;
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spielfeld.farbe.spielfeld);
			
			for (unsigned int y = gebaeude._.at(i).start_pos.y; y <= gebaeude._.at(i).ende_pos.y; y ++)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {gebaeude._.at(i).start_pos.x, y});
				
				for (unsigned int x = gebaeude._.at(i).start_pos.x; x <= gebaeude._.at(i).ende_pos.x; x ++)
				{
					std::cout << ' ';
				}
			}
			
			if (spieler.at(s).schlange.richtung == spieler.at(s).tasten.rechts)
			{
				gebaeude._.at(i).start_pos.x ++;
				gebaeude._.at(i).ende_pos.x ++;
			}
			
			else if (spieler.at(s).schlange.richtung == spieler.at(s).tasten.links)
			{
				gebaeude._.at(i).start_pos.x --;
				gebaeude._.at(i).ende_pos.x --;
			}
			
			else if (spieler.at(s).schlange.richtung == spieler.at(s).tasten.unten)
			{
				gebaeude._.at(i).start_pos.y ++;
				gebaeude._.at(i).ende_pos.y ++;
			}
			
			else if (spieler.at(s).schlange.richtung == spieler.at(s).tasten.oben)
			{
				gebaeude._.at(i).start_pos.y --;
				gebaeude._.at(i).ende_pos.y --;
			}
			
			bool bauen;
			
			for (unsigned int j = 0; j < spieler.at(s).gebaeude.zentrale._.size(); j ++)
			{
				if ((gebaeude._.at(i).start_pos.x <= spieler.at(s).gebaeude.zentrale._.at(j).ende_pos.x + 3)
				&& (gebaeude._.at(i).start_pos.y <= spieler.at(s).gebaeude.zentrale._.at(j).ende_pos.y + 3)
				&& (gebaeude._.at(i).ende_pos.x + 3 >= spieler.at(s).gebaeude.zentrale._.at(j).start_pos.x)
				&& (gebaeude._.at(i).ende_pos.y + 3 >= spieler.at(s).gebaeude.zentrale._.at(j).start_pos.y))
				{
					bauen = true;
				}
			}
			
			if ((spieler.at(s).schlange.richtung == spieler.at(s).tasten.oben_rechts) && (bauen == true))
			{
				gebaeude._.at(i).verschieben = false;
				v = false;
			}
			
			gebaeude_zeichnen(spieler, gebaeude, s, i);
		}
	}
}

void gebaeude_kaufen(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Gebaeude_x &gebaeude, unsigned long long s)
{
	gebaeude._.resize(gebaeude._.size() + 1);
	gebaeude._.at(gebaeude._.size() - 1).level = 1;
	spieler.at(s).geld -= gebaeude.kosten;
	gebaeude._.at(gebaeude._.size() - 1).gebaut = true;
	gebaeude._.at(gebaeude._.size() - 1).verschieben = true;
	
	gebaeude._.at(gebaeude._.size() - 1).richtung = ' ';
	gebaeude._.at(gebaeude._.size() - 1).start_pos.x = spielfeld.groesse.x / 2;
	gebaeude._.at(gebaeude._.size() - 1).start_pos.y = spielfeld.groesse.y / 2;
}

void spieler_menue(Spielfeld &spielfeld, std::vector <Spieler> &spieler, unsigned int s)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(0));
	
	bool v = false;
	
	gebaeude_verschieben(spielfeld, spieler, spieler.at(s).gebaeude.zentrale, s, v);
	gebaeude_verschieben(spielfeld, spieler, spieler.at(s).gebaeude.kanone, s, v);
	gebaeude_verschieben(spielfeld, spieler, spieler.at(s).gebaeude.krankenhaus, s, v);
	gebaeude_verschieben(spielfeld, spieler, spieler.at(s).gebaeude.geldlager, s, v);
	gebaeude_verschieben(spielfeld, spieler, spieler.at(s).gebaeude.mauer, s, v);
	gebaeude_verschieben(spielfeld, spieler, spieler.at(s).gebaeude.teleporter, s, v);
	
	if (v == false)
	{
		if (spieler.at(s).schlange.richtung == spieler.at(s).tasten.rechts)
		{
			spieler.at(s).menue_seite ++;
		}
		
		else if (spieler.at(s).schlange.richtung == spieler.at(s).tasten.links)
		{
			spieler.at(s).menue_seite --;
		}
		
		
		if (spieler.at(s).menue_seite == -1)
		{
			spieler.at(s).menue_seite = 3;
		}
		
		else if (spieler.at(s).menue_seite == 4)
		{
			spieler.at(s).menue_seite = 0;
		}
		
		else if (spieler.at(s).menue_seite == 99)
		{
			spieler.at(s).menue_seite = 106;
		}
		
		else if (spieler.at(s).menue_seite == 107)
		{
			spieler.at(s).menue_seite = 100;
		}
		
		
		if (spieler.at(s).schlange.richtung == spieler.at(s).tasten.unten)
		{
			if ((spieler.at(s).menue_seite == 100) && (spieler.at(s).gebaeude.zentrale.kosten <= spieler.at(s).geld))
			{
				gebaeude_kaufen(spielfeld, spieler, spieler.at(s).gebaeude.zentrale, s);
				
				spieler.at(s).gebaeude.zentrale._.at(spieler.at(s).gebaeude.zentrale._.size() - 1).ende_pos.x = spieler.at(s).gebaeude.zentrale._.at(spieler.at(s).gebaeude.zentrale._.size() - 1).start_pos.x + 19;
				spieler.at(s).gebaeude.zentrale._.at(spieler.at(s).gebaeude.zentrale._.size() - 1).ende_pos.y = spieler.at(s).gebaeude.zentrale._.at(spieler.at(s).gebaeude.zentrale._.size() - 1).start_pos.y + 19;
			}
			
			else if ((spieler.at(s).menue_seite == 101) && (spieler.at(s).gebaeude.kanone.kosten <= spieler.at(s).geld))
			{
				gebaeude_kaufen(spielfeld, spieler, spieler.at(s).gebaeude.kanone, s);
				
				spieler.at(s).gebaeude.kanone._.at(spieler.at(s).gebaeude.kanone._.size() - 1).zeit_ereignis.pause = 1000;
				
				spieler.at(s).gebaeude.kanone._.at(spieler.at(s).gebaeude.kanone._.size() - 1).punkt.resize(0);
				
				spieler.at(s).gebaeude.kanone._.at(spieler.at(s).gebaeude.kanone._.size() - 1).ende_pos.x = spieler.at(s).gebaeude.kanone._.at(spieler.at(s).gebaeude.kanone._.size() - 1).start_pos.x + 4;
				spieler.at(s).gebaeude.kanone._.at(spieler.at(s).gebaeude.kanone._.size() - 1).ende_pos.y = spieler.at(s).gebaeude.kanone._.at(spieler.at(s).gebaeude.kanone._.size() - 1).start_pos.y + 4;
			}
			
			else if ((spieler.at(s).menue_seite == 102) && (spieler.at(s).gebaeude.krankenhaus.kosten <= spieler.at(s).geld))
			{
				gebaeude_kaufen(spielfeld, spieler, spieler.at(s).gebaeude.krankenhaus, s);
				
				spieler.at(s).gebaeude.krankenhaus._.at(spieler.at(s).gebaeude.krankenhaus._.size() - 1).zeit_betreten.pause = 60000;
				
				spieler.at(s).gebaeude.krankenhaus._.at(spieler.at(s).gebaeude.krankenhaus._.size() - 1).ende_pos.x = spieler.at(s).gebaeude.krankenhaus._.at(spieler.at(s).gebaeude.krankenhaus._.size() - 1).start_pos.x + 8;
				spieler.at(s).gebaeude.krankenhaus._.at(spieler.at(s).gebaeude.krankenhaus._.size() - 1).ende_pos.y = spieler.at(s).gebaeude.krankenhaus._.at(spieler.at(s).gebaeude.krankenhaus._.size() - 1).start_pos.y + 8;
			}
			
			else if ((spieler.at(s).menue_seite == 103) && (spieler.at(s).gebaeude.geldlager.kosten <= spieler.at(s).geld))
			{
				gebaeude_kaufen(spielfeld, spieler, spieler.at(s).gebaeude.geldlager, s);
				
				spieler.at(s).gebaeude.geldlager._.at(spieler.at(s).gebaeude.geldlager._.size() - 1).ende_pos.x = spieler.at(s).gebaeude.geldlager._.at(spieler.at(s).gebaeude.geldlager._.size() - 1).start_pos.x + 11;
				spieler.at(s).gebaeude.geldlager._.at(spieler.at(s).gebaeude.geldlager._.size() - 1).ende_pos.y = spieler.at(s).gebaeude.geldlager._.at(spieler.at(s).gebaeude.geldlager._.size() - 1).start_pos.y + 11;
			}
			
			else if ((spieler.at(s).menue_seite == 104) && (spieler.at(s).gebaeude.mauer.kosten <= spieler.at(s).geld))
			{
				gebaeude_kaufen(spielfeld, spieler, spieler.at(s).gebaeude.mauer, s);
				
				spieler.at(s).gebaeude.mauer._.at(spieler.at(s).gebaeude.mauer._.size() - 1).ende_pos.x = spieler.at(s).gebaeude.mauer._.at(spieler.at(s).gebaeude.mauer._.size() - 1).start_pos.x;
				spieler.at(s).gebaeude.mauer._.at(spieler.at(s).gebaeude.mauer._.size() - 1).ende_pos.y = spieler.at(s).gebaeude.mauer._.at(spieler.at(s).gebaeude.mauer._.size() - 1).start_pos.y;
			}
			
			else if ((spieler.at(s).menue_seite == 105) && (spieler.at(s).gebaeude.teleporter.kosten <= spieler.at(s).geld))
			{
				gebaeude_kaufen(spielfeld, spieler, spieler.at(s).gebaeude.teleporter, s);
				
				spieler.at(s).gebaeude.teleporter._.at(spieler.at(s).gebaeude.teleporter._.size() - 1).ende_pos.x = spieler.at(s).gebaeude.teleporter._.at(spieler.at(s).gebaeude.teleporter._.size() - 1).start_pos.x + 7;
				spieler.at(s).gebaeude.teleporter._.at(spieler.at(s).gebaeude.teleporter._.size() - 1).ende_pos.y = spieler.at(s).gebaeude.teleporter._.at(spieler.at(s).gebaeude.teleporter._.size() - 1).start_pos.y + 7;
			}
			
			else
			{
				spieler.at(s).menue_seite = spielfeld.seite_menue.at(spieler.at(s).menue_seite).naechste_seite;
			}
		}
		
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 2});
		std::cout << "SPIELERMENUE";
		
		if (spieler.at(s).menue_seite == 100)
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 3});
			std::cout << "< " << spieler.at(s).gebaeude.zentrale.name << " >";
			
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 4});
			std::cout << "Kosten: " << spieler.at(s).gebaeude.zentrale.kosten << " Euro\t";
		}
		
		else if (spieler.at(s).menue_seite == 101)
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 3});
			std::cout << "< " << spieler.at(s).gebaeude.kanone.name << " >";
			
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 4});
			std::cout << "Kosten: " << spieler.at(s).gebaeude.kanone.kosten << " Euro\t";
		}
		
		else if (spieler.at(s).menue_seite == 102)
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 3});
			std::cout << "< " << spieler.at(s).gebaeude.krankenhaus.name << " >";
			
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 4});
			std::cout << "Kosten: " << spieler.at(s).gebaeude.krankenhaus.kosten << " Euro\t";
		}
		
		else if (spieler.at(s).menue_seite == 103)
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 3});
			std::cout << "< " << spieler.at(s).gebaeude.geldlager.name << " >";
			
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 4});
			std::cout << "Kosten: " << spieler.at(s).gebaeude.geldlager.kosten << " Euro\t";
		}
		
		else if (spieler.at(s).menue_seite == 104)
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 3});
			std::cout << "< " << spieler.at(s).gebaeude.mauer.name << " >";
			
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 4});
			std::cout << "Kosten: " << spieler.at(s).gebaeude.mauer.kosten << " Euro\t";
		}
		
		else if (spieler.at(s).menue_seite == 105)
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 3});
			std::cout << "< " << spieler.at(s).gebaeude.teleporter.name << " >";
			
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 4});
			std::cout << "Kosten: " << spieler.at(s).gebaeude.teleporter.kosten << " Euro\t";
		}
		
		else
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 3});
			std::cout << "< " << spielfeld.seite_menue.at(spieler.at(s).menue_seite).name << " >";
		}
		
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s, spielfeld.groesse.y + 5});
		std::cout << "Geld: " << spieler.at(s).geld << " Euro\t";
	}
	
	spieler.at(s).schlange.richtung = ' ';
}

void menue_pause(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Punkte &punkte, time_t t)
{
	system("cls");
	
	std::cout
		<< "PAUSE\n"
		<< "\n"
		<< "1| ZURUECK ZUM SPIEL\n"
		<< "2| SPIEL NEU STARTEN\n"
		<< "3| HAUPTMENUE\n"
		<< "4| CHEATS\n"
		<< "5| EINSTELLUNGEN\n"
		<< "0| SPIEL BEENDEN\n";
	
	switch (getch())
	{
	case '1':
		spiel_start(spielfeld, spieler, punkte, t);
		break;
	
	case '4':
		menue_cheats(spielfeld, spieler, punkte, t);
		break;
	}
}


void menue_cheats(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Punkte &punkte, time_t t)
{
	system("cls");
	
	if (spielfeld.cheats == true)
	{
		std::string cheat;
		
		std::cout << "CHEATS\n\n";
		std::cin >> cheat;
		
		if (cheat == "?")
		{
		
		}
		else
		{
			std::cout << "falsche Eingabe!";
		}
	}
	
	else
	{
		std::cout << "CHEATS SIND DEAKTIVIERT!";
		Sleep(800);
	}
	
	spiel_start(spielfeld, spieler, punkte, t);
}


void leben(Spielfeld &spielfeld, std::vector <Spieler> &spieler, unsigned int s)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(s).farbe.at(0));
	
	spieler.at(s).leben --;
	spieler.at(s).geld = 0;
	
	if (spieler.at(s).leben > 0)
	{
		spieler.at(s).schlange.richtung = ' ';
		spieler.at(s).schlange.pos.at(0).x = spielfeld.groesse.x / spieler.size() * s + spielfeld.groesse.x / (spieler.size() * 2);
		spieler.at(s).schlange.pos.at(0).y = spielfeld.groesse.y / 2 + 1;
	}
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 6});
	std::cout << spieler.at(s).leben;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * s + 8, spielfeld.groesse.y + 5});
	std::cout << spieler.at(s).geld << " EURO      ";
}

void gebaeude_gameover(Spielfeld &spielfeld, std::vector <Spieler> &spieler, Gebaeude_x &gebaeude, unsigned long long s, unsigned long long sp)
{
	for (unsigned int i = 0; i < gebaeude._.size(); i ++)
	{
		if ((spieler.at(s).schlange.pos.at(0).x <= gebaeude._.at(i).ende_pos.x)
		&& (spieler.at(s).schlange.pos.at(0).y <= gebaeude._.at(i).ende_pos.y)
		&& (spieler.at(s).schlange.pos.at(0).x >= gebaeude._.at(i).start_pos.x)
		&& (spieler.at(s).schlange.pos.at(0).y >= gebaeude._.at(i).start_pos.y)
		&& (gebaeude._.at(i).gebaut == true)
		&& (gebaeude._.at(i).verschieben == false)
		&& (sp != s))
		{
			spieler.at(sp).geld += spieler.at(s).geld;
			leben(spielfeld, spieler, s);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(sp).farbe.at(0));
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * sp + 8, spielfeld.groesse.y + 5});
			std::cout << spieler.at(sp).geld << " EURO      ";
		}
	}
}

bool gameover(Spielfeld &spielfeld, std::vector <Spieler> &spieler, std::vector <Punkt> &hindernis, unsigned int s)
{
	bool gameover = spieler.at(s).gameover;
	
	if ((spieler.at(s).schlange.waende == true)
	&& ((spieler.at(s).schlange.pos.at(0).x == 0)
	|| (spieler.at(s).schlange.pos.at(0).y == 0)
	|| (spieler.at(s).schlange.pos.at(0).x == spielfeld.groesse.x + 1)
	|| (spieler.at(s).schlange.pos.at(0).y == spielfeld.groesse.y + 1)))
	{
		leben(spielfeld, spieler, s);
	}
	
	for (unsigned int p = 0; p < hindernis.size(); p ++)
	{
		if ((spieler.at(s).schlange.pos.at(0).x == hindernis.at(p).pos.x) && (spieler.at(s).schlange.pos.at(0).y == hindernis.at(p).pos.y))
		{
			leben(spielfeld, spieler, s);
		}
	}
	
	for (unsigned int sp = 0; sp < spieler.size(); sp ++)
	{
		for (unsigned int i = 0; i < spieler.at(sp).schlange.pos.size(); i ++)
		{
			if ((spieler.at(s).schlange.pos.at(0).x == spieler.at(sp).schlange.pos.at(i).x) && (spieler.at(s).schlange.pos.at(0).y == spieler.at(sp).schlange.pos.at(i).y) && (sp != s))
			{
				spieler.at(sp).geld += spieler.at(s).geld;
				leben(spielfeld, spieler, s);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(sp).farbe.at(0));
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * sp + 8, spielfeld.groesse.y + 5});
				std::cout << spieler.at(sp).geld << " EURO      ";
			}
		}
		
		for (unsigned int i = 0; i < spieler.at(s).schlange.pos.size(); i ++)
		{
			for (unsigned int j = 0; j < spieler.at(sp).gebaeude.kanone._.size(); j ++)
			{
				for (unsigned int p = 0; p < spieler.at(sp).gebaeude.kanone._.at(j).punkt.size(); p ++)
				{
					if ((spieler.at(s).schlange.pos.at(i).x == spieler.at(sp).gebaeude.kanone._.at(j).punkt.at(p).pos.x)
					&& (spieler.at(s).schlange.pos.at(i).y == spieler.at(sp).gebaeude.kanone._.at(j).punkt.at(p).pos.y)
					&& (sp != s))
					{
						spieler.at(sp).geld += spieler.at(s).geld;
						leben(spielfeld, spieler, s);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), spieler.at(sp).farbe.at(0));
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {spielfeld.groesse.x / spieler.size() * sp + 8, spielfeld.groesse.y + 5});
						std::cout << spieler.at(sp).geld << " EURO      ";
					}
				}
			}
		}
		
		gebaeude_gameover(spielfeld, spieler, spieler.at(sp).gebaeude.kanone, s, sp);
		gebaeude_gameover(spielfeld, spieler, spieler.at(sp).gebaeude.krankenhaus, s, sp);
		gebaeude_gameover(spielfeld, spieler, spieler.at(sp).gebaeude.geldlager, s, sp);
		gebaeude_gameover(spielfeld, spieler, spieler.at(sp).gebaeude.mauer, s, sp);
		gebaeude_gameover(spielfeld, spieler, spieler.at(sp).gebaeude.teleporter, s, sp);
	}
	
	for (unsigned int i = 1; i < spieler.at(s).schlange.pos.size(); i ++)
	{
		if ((spieler.at(s).schlange.pos.at(0).x == spieler.at(s).schlange.pos.at(i).x) && (spieler.at(s).schlange.pos.at(0).y == spieler.at(s).schlange.pos.at(i).y))
		{
			leben(spielfeld, spieler, s);
		}
	}
	
	if (spieler.at(s).leben <= 0)
	{
		gameover = true;
	}
	
	return gameover;
}


void farben()
{
	system("cls");
	
	for (unsigned int f = 0; f < 256; f ++)
	{
		unsigned char z = f;
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		std::cout << f << '\t' << z << '\n';
	}
	
	getch();
}


int main()
{
	Spiel_info spiel_info;
	
	spiel_info.name = "Snake";
	spiel_info.version = "1.30.0";
	spiel_info.datum.tag = 00;
	spiel_info.datum.monat = 6;
	spiel_info.datum.jahr = 2017;
	
	system("color 84");
	
	Spiel spiel;
	
	time_t t;
	
	time(&t);
	srand((unsigned int)t);
	
	spiel.spieler.resize(eingaben(spiel.spielfeld, spiel.spieler));
	
	spiel.punkte.essen.resize(1);
	for (unsigned int i = 0; i < spiel.punkte.essen.size(); i ++)
	{
		spiel.punkte.essen.at(i).farbe = 240;
		spiel.punkte.essen.at(i).zeichen = 'o';
	}
	
	spiel.punkte.geld.resize(1);
	for (unsigned int i = 0; i < spiel.punkte.geld.size(); i ++)
	{
		spiel.punkte.geld.at(i).farbe = 224;
		spiel.punkte.geld.at(i).zeichen = '$';
	}
	
	spiel.punkte.leben.resize(1);
	for (unsigned int i = 0; i < spiel.punkte.leben.size(); i ++)
	{
		spiel.punkte.leben.at(i).farbe = 192;
		spiel.punkte.leben.at(i).zeichen = 197;
	}
	
	spiel.punkte.hindernis.resize(0);
	for (unsigned int i = 0; i < spiel.punkte.hindernis.size(); i ++)
	{
		spiel.punkte.hindernis.at(i).farbe = 15;
		spiel.punkte.hindernis.at(i).zeichen = 'X';
	}
	
	for (unsigned int i = 0; i < spiel.spieler.size(); i ++)
	{
		spiel.spieler.at(i).gebaeude.zentrale._.resize(1);
		spiel.spieler.at(i).gebaeude.zentrale.name = "Zentrale";
		spiel.spieler.at(i).gebaeude.zentrale.info = "";
		spiel.spieler.at(i).gebaeude.zentrale.kosten = 10000;
		
		spiel.spieler.at(i).gebaeude.kanone._.resize(0);
		spiel.spieler.at(i).gebaeude.kanone.name = "Kanone";
		spiel.spieler.at(i).gebaeude.kanone.info = "";
		spiel.spieler.at(i).gebaeude.kanone.kosten = 1500;
		
		spiel.spieler.at(i).gebaeude.krankenhaus._.resize(0);
		spiel.spieler.at(i).gebaeude.krankenhaus.name = "Krankenhaus";
		spiel.spieler.at(i).gebaeude.krankenhaus.info = "";
		spiel.spieler.at(i).gebaeude.krankenhaus.kosten = 3000;
		
		spiel.spieler.at(i).gebaeude.geldlager._.resize(0);
		spiel.spieler.at(i).gebaeude.geldlager.name = "Geldlager";
		spiel.spieler.at(i).gebaeude.geldlager.info = "";
		spiel.spieler.at(i).gebaeude.geldlager.kosten = 200;
		
		spiel.spieler.at(i).gebaeude.mauer._.resize(0);
		spiel.spieler.at(i).gebaeude.mauer.name = "Mauer";
		spiel.spieler.at(i).gebaeude.mauer.info = "";
		spiel.spieler.at(i).gebaeude.mauer.kosten = 20;
		
		spiel.spieler.at(i).gebaeude.teleporter._.resize(0);
		spiel.spieler.at(i).gebaeude.teleporter.name = "Teleporter";
		spiel.spieler.at(i).gebaeude.teleporter.info = "";
		spiel.spieler.at(i).gebaeude.teleporter.kosten = 1000;
	}
	
	spiel.spielfeld.seite_menue.resize(1000);
	
	spiel.spielfeld.seite_menue.at(0).name = "SHOP";
	spiel.spielfeld.seite_menue.at(0).naechste_seite = 10;
	
	spiel.spielfeld.seite_menue.at(1).name = "";
	
	spiel.spielfeld.seite_menue.at(2).name = "";
	
	spiel.spielfeld.seite_menue.at(3).name = "";
	
	spiel.spielfeld.seite_menue.at(10).name = "GEBAEUDE";
	spiel.spielfeld.seite_menue.at(10).naechste_seite = 100;
	
	std::string name;
	std::cin >> name;
	
	std::ifstream datei(name + ".txt");
	
	if (datei.eof() == false)
	{
		std::ofstream datei(name + ".txt");
		
		datei
			<< "ROT\n"
			<< "0\n"
			<< "2  192 64\n"
			<< "w s a d   q e y c   x\n"
			<< "0\n"
			<< "3\n"
			<< "200\n"
			<< "0\n"
			<< '\n'
			<< "BLAU\n"
			<< "0\n"
			<< "2  144 16\n"
			<< "t g f h   r z v n   b\n"
			<< "0\n"
			<< "3\n"
			<< "200\n"
			<< "0\n"
			<< '\n'
			<< "GELB\n"
			<< "0\n"
			<< "2  224 96\n"
			<< "i k j l   u o m .   ,\n"
			<< "0\n"
			<< "3\n"
			<< "200\n"
			<< "0\n"
			<< '\n'
			<< "GRUEN\n"
			<< "0\n"
			<< "2  160 32\n"
			<< "8 5 4 6   7 9 1 3   2\n"
			<< "0\n"
			<< "3\n"
			<< "200\n"
			<< "0\n";
	}
	
	for (unsigned int i = 0; i < spiel.spieler.size(); i ++)
	{
		unsigned int farben;
		
		datei
			>> spiel.spieler.at(i).name
			>> spiel.spieler.at(i).gameover
			>> farben;
		spiel.spieler.at(i).farbe.resize(farben);
		
		for (unsigned int f = 0; f < spiel.spieler.at(i).farbe.size(); f ++)
		{
			datei >> spiel.spieler.at(i).farbe.at(f);
		}
		
		datei
			>> spiel.spieler.at(i).tasten.oben
			>> spiel.spieler.at(i).tasten.unten
			>> spiel.spieler.at(i).tasten.links
			>> spiel.spieler.at(i).tasten.rechts
			
			>> spiel.spieler.at(i).tasten.oben_links
			>> spiel.spieler.at(i).tasten.oben_rechts
			>> spiel.spieler.at(i).tasten.unten_links
			>> spiel.spieler.at(i).tasten.unten_rechts
			
			>> spiel.spieler.at(i).tasten.menue
			
			>> spiel.spieler.at(i).punkte
			>> spiel.spieler.at(i).leben
			>> spiel.spieler.at(i).geld
			
			>> spiel.spieler.at(i).menue_seite;
	}
	
	datei.close();
	
	if (spiel.spieler.size() >= 1)
	{
		spiel.spieler.at(0).gebaeude.zentrale._.at(0).start_pos.x = 1;
		spiel.spieler.at(0).gebaeude.zentrale._.at(0).start_pos.y = 1;
		spiel.spieler.at(0).gebaeude.zentrale._.at(0).ende_pos.x = 20;
		spiel.spieler.at(0).gebaeude.zentrale._.at(0).ende_pos.y = 20;
	}
	
	if (spiel.spieler.size() >= 2)
	{
		spiel.spieler.at(1).gebaeude.zentrale._.at(0).start_pos.x = spiel.spielfeld.groesse.x - 19;
		spiel.spieler.at(1).gebaeude.zentrale._.at(0).start_pos.y = 1;
		spiel.spieler.at(1).gebaeude.zentrale._.at(0).ende_pos.x = spiel.spielfeld.groesse.x;
		spiel.spieler.at(1).gebaeude.zentrale._.at(0).ende_pos.y = 20;
	}
	
	if (spiel.spieler.size() >= 3)
	{
		spiel.spieler.at(2).gebaeude.zentrale._.at(0).start_pos.x = 1;
		spiel.spieler.at(2).gebaeude.zentrale._.at(0).start_pos.y = spiel.spielfeld.groesse.y - 19;
		spiel.spieler.at(2).gebaeude.zentrale._.at(0).ende_pos.x = 20;
		spiel.spieler.at(2).gebaeude.zentrale._.at(0).ende_pos.y = spiel.spielfeld.groesse.y;
	}
	
	if (spiel.spieler.size() >= 4)
	{
		spiel.spieler.at(3).gebaeude.zentrale._.at(0).start_pos.x = spiel.spielfeld.groesse.x - 19;
		spiel.spieler.at(3).gebaeude.zentrale._.at(0).start_pos.y = spiel.spielfeld.groesse.y - 19;
		spiel.spieler.at(3).gebaeude.zentrale._.at(0).ende_pos.x = spiel.spielfeld.groesse.x;
		spiel.spieler.at(3).gebaeude.zentrale._.at(0).ende_pos.y = spiel.spielfeld.groesse.y;
	}
	
	if (spiel.spieler.size() >= 5)
	{
		for (unsigned int i = 4; i < spiel.spieler.size(); i ++)
		{
			spiel.spieler.at(i).computer = true;
	
			spiel.spieler.at(i).name = "SPIELER";
			spiel.spieler.at(i).farbe.resize(2);
			spiel.spieler.at(i).farbe.at(0) = 200;
			spiel.spieler.at(i).farbe.at(1) = 280;
			
			spiel.spieler.at(i).tasten.oben = 'W';
			spiel.spieler.at(i).tasten.unten = 'S';
			spiel.spieler.at(i).tasten.links = 'A';
			spiel.spieler.at(i).tasten.rechts = 'D';
			
			spiel.spieler.at(i).tasten.oben_links = 'Q';
			spiel.spieler.at(i).tasten.oben_rechts = 'E';
			spiel.spieler.at(i).tasten.unten_links = 'Y';
			spiel.spieler.at(i).tasten.unten_rechts = 'C';
			
			spiel.spieler.at(i).tasten.menue = 'X';
		}
	}
	
	for (unsigned int i = 0; i < spiel.spieler.size(); i ++)
	{
		spiel.spieler.at(i).schlange.pos.resize(10);
		spiel.spieler.at(i).schlange.richtung = ' ';
		
		spiel.spieler.at(i).schlange.pos.at(0).x = spiel.spielfeld.groesse.x / spiel.spieler.size() * i + spiel.spielfeld.groesse.x / (spiel.spieler.size() * 2);
		spiel.spieler.at(i).schlange.pos.at(0).y = spiel.spielfeld.groesse.y / 2 + 1;
		
		spiel.spieler.at(i).gebaeude.zentrale._.at(0).gebaut = true;
		spiel.spieler.at(i).schlange.zeit.pause = 50;
	}
	
	punkte_erstellen(spiel.punkte.essen, spiel.spielfeld, spiel.spieler, t);
	punkte_erstellen(spiel.punkte.hindernis, spiel.spielfeld, spiel.spieler, t);
	
	spielanleitung(spiel_info, spiel.spieler);
	
	spiel.spielfeld.zeit.start = clock();
	spiel_start(spiel.spielfeld, spiel.spieler, spiel.punkte, t);
	
	return 0;
}
