
#include <fstream>
#include <iostream>
#include <Windows.h>
#include "Snake.h";
#include "ScreenSpecs.h";
#include "3D.h";

using namespace std;

 HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
 COORD cord = { 200,70 };

 double  aspect = (68.0 / 32.0); // соотношение сторон символла в консоли
 bool ison = 1;
 int menudelay = 400;

 int gamefieldsize = 15;
 int gamespeed = 100;
 int objecttype = 0;

 int horiz = 200;
 int vert = 50;

 CHAR_INFO* display;
 wchar_t* gamefield;

void GameSetScreenout()
{
		
	_SMALL_RECT Rect = { 0,0,horiz,vert };
	COORD BUFFER;
	BUFFER.X = horiz;
	BUFFER.Y = vert;
	SetConsoleWindowInfo(console, TRUE, &Rect);
	SetConsoleScreenBufferSize(console, BUFFER);
	SetConsoleCursorPosition(console, cord);
	return;
}
CHAR_INFO* GameDisplaystart()
{
	delete[] display;
	CHAR_INFO* display = new CHAR_INFO[horiz*vert]();
	return display;
}
wchar_t* GameFieldstart()
{
	delete[] gamefield;
	wchar_t* gamefield = new wchar_t[gamefieldsize * gamefieldsize]();
	return gamefield;
}

void GetSettings()
{
	ifstream settings;
	settings.open(L"settings.txt");
	if (settings.is_open())
	{
		settings >> objecttype >> gamefieldsize >> gamespeed;
	}
	else
	{
		objecttype = 1;
		gamefieldsize = 15;
		gamespeed = 50;
	}
	settings.close();
	return;
}
void SaveSettings()
{
	ofstream settings;
	settings.open(L"settings.txt");
	if (settings.is_open())
	{
		settings << objecttype << ' ' << gamefieldsize << ' ' << gamespeed;
	}
	settings.close();
	return;

}


void GameLogo()
{
	DWORD outnum = 0;
	SMALL_RECT write = { 0,0,horiz,vert };
	             
		
wchar_t logo[] = L"                               77                                                                                                                                                                     "
"                             J5PPPPPP55Y?7                                                                                                                                                            "
"                           7YPGGGGGGPPPPPPPP557                                                                                                                                                        "
"                         7PB########BBBGPPPGB#B    J55YYJ?7                                                                                                                                           "   
"                         JB##############BB#&##G JPPPPPPGGGG57            :                                                                                                                            "
"                          P#################&&#Y PBBBBBBGGGGGG5         7??7                                                                                                                           "
"                           P########BBGGGGGB#5    GB#####BBGBBBGY      YPPPPPPP5                                                                                                                       "
"                            JG######BGGGGGGGGY7   7BB######BBBBBBGY : GGGGPPGB##Y           :     :::::                                                                                                "
"                              ?PB#####BBGGGGGGGG5? JB########BBBBBBGY YB###B#####?:        : J55YYJ?7  :                                                                                               "
"                                 JB######BBBBBBBB#GYG##########BBBBB#BYG#########B         ?5PPPPPPPPBBJ :                                                                                             "
"                                75GBBBB#######B###################B###############P      :7BBBBBGGGB####P :        :                                                                                   "
"                               5GGGGGGPGGB########&&&##############################Y     :?BB############B?        7YPPP55YY7                                                                          "
"                               ?BBBGPPPPPPGB######&&&&#######&######################?    :JBB#########&&###5 :    YPPPPPPPB#B                                                                          "
"                                Y###BBGGGGPPB#########PP######&&####################B    :YBB####B######&###G7    JBBBBBB####G      7JY5555YJ?                                                         "
"                                 JPB################GJ  PB#####&##BYG################P    YBB###BBB######&&###Y    5B#########5   ?Y55PPPPPPY    ?5YYJ?7                                               "
"                                    7J5PGB########BY     GB####&###P JG###############Y   5BB####BBBB######&###G    GB#########? YBB##BBBB57   ?5PPPPPPPPP55YJ??7                                      "
"                                          7?JJYYJ?       ?B#####&###J  JG##############?  PB#####BBGPB######&&##BJ :7BB########B5B#######5     PBBBGGGGPPPPPPPPPPPPPY                                  "
"                                                          YBB####&BY     YB############B  GB#####GPPPPGB#####&&###P :JBB###############BY      7B#######BBBBGGGGGG###J                                 "
"                                                            7?JY5Y         YB###########G GB######BBBBGG#######&&##B? PB##############BY7       YB################&#&G                                 "
"                                                                             5B#########GJBB####################&&###57G#############GPBB5       PB##########B####&#5                                  "
"                                                                               J5PGBB#BJ 7B######BBB5Y5PGBB#######&&#&G5B############B####B5      G######&&##P555PP7                                   "
"                                                                                     7   7PGB####BP7       75######&&&&#####################B57   ?B#######GPGPPPP555YJ?                               "
"                                                                                             7?JY?           JB#####&&&&&#####################B5   Y######BBGGGGGGGGGB##?                              "
"                                                                                                              7G######&&&&#######&##############B57 P############BBB####G                              "
"                                                                                                                J5PGBB#&BYJ#######&&&#G###########B5JB###############&&BY                              "
"                                                                                                                      7?   YGB####&#P7 ?G####################&###PPPGBY                                "
"                                                                                                                              7?J557     JG##################&&#GPP55YJ?7                              "
"                                                                                                                                           JGB################BGGGGGGGGGGPP5P7                         "
"                                                                                                                                              7?JY5GBGJ?B########BBBGGGGGGB##G                         "
"                                                                                                                                                        ?Y5PGB############&&&#J                        "
"                                                                                                                                                              7?JY5PGB####&&BJ                         "
"                                                                                                                                                                      7?JY5Y                           ";
int n = 40;
for (short i = 31; i >= 0; i--)
{
	if (GetAsyncKeyState(VK_RETURN)) n = 0;
	Sleep(n);
	system("CLS");
	WriteConsoleOutputCharacter(console, logo, 6366, {20 ,i }, &outnum);
	
	
}
while (true) {
	SetConsoleCursorPosition(console, { 95,33 });
	cout << "Press \"Enter\"";
	if (GetAsyncKeyState(VK_RETURN)) break;
	Sleep(500);
	if (GetAsyncKeyState(VK_RETURN)) break;;
	SetConsoleCursorPosition(console, { 95,33 });
	if (GetAsyncKeyState(VK_RETURN)) break;;
	cout << "Press          ";
	if (GetAsyncKeyState(VK_RETURN)) break;;
	Sleep(500);
}
SetConsoleCursorPosition(console, cord);
return;
}

//0

void GameKill()
{
	ison = 0;	
	return;
}
bool GamePressToStart()
{
	SetConsoleCursorPosition(console, { (short)(0),(short)(20) });
	cout << 
	"-------------------------\n"
	"|                       |\n"
	"|   Arrows - move       |\n"
	"|                       |\n"
	"|   Esc - pause         |\n"
	"|                       |\n"
	"|   When paused:        |\n"
	"|  Arrows - move        |\n"
	"|            Camera     |\n"
	"|  NUM0 - camera closer |\n"
    "|                       |\n"
    "|  NUM1 - camera further|\n"
	"|                       |\n"
	"-------------------------\n";


	SetConsoleCursorPosition(console, { (short)(90),(short)(25)});
	cout << "Press \"Enter\" to start";
	while (true)
	{
		if (GetAsyncKeyState(VK_RETURN)) return 1;
	}
}
void GameChooseToContinue(bool &restart,bool &gtg)
{
	SetConsoleCursorPosition(console, { (short)(90),(short)(23) });
	cout << "Restart Game";
	SetConsoleCursorPosition(console, { (short)(90),(short)(27) });
	cout << "Goto Menu";
	SetConsoleCursorPosition(console, { (short)(90 - 3),(short)(23) });
	cout << "-> ";
	short pos = 0;
	while (true)
	{
		if (GetAsyncKeyState(VK_UP)) {
			SetConsoleCursorPosition(console, { (short)(90-3),(short)(23+pos*4) });
			cout << "   ";
			pos -= 1; if (pos == -1) pos = 1;
			SetConsoleCursorPosition(console, { (short)(90 - 3),(short)(23 + pos * 4) });
			cout << "-> ";
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			SetConsoleCursorPosition(console, { (short)(90 - 3),(short)(23 + pos * 4) });
			cout << "   ";
			pos += 1; if (pos == 2) pos = 0;
			SetConsoleCursorPosition(console, { (short)(90 - 3),(short)(23 + pos * 4) });
			cout << "-> ";
		}
		else if (GetAsyncKeyState(VK_RETURN))
		{
			switch (pos)
			{
			case 0: {ison = 1, gtg = 0; 
				gamefield = GameFieldstart();	 
				return; }
			case 1: {restart = 0; return; }
			}
		}
		Sleep(menudelay);

	}

}
void GamePlay()
{
	bool restart = 1;
	do
	{
	DWORD outnum = 0;
	SMALL_RECT write = { 0,0,horiz,vert };
	vec plane(0, 0);
	float x, y;
	float anglez, anglexy;
	snake player;
	berry fruit;
	wchar_t t = ' ';
	player.increase();
	player.increase();
	bool gtg = 0;
	ison = 1;
	float angz = 0;
	float angx = 0;
	float dist = 0;
	bool pause = 0;

	while (ison)
	{
		int goodmove;
		
		if (GetAsyncKeyState(VK_ESCAPE) && pause == 0) 
		{
			pause = 1; Sleep(100);
	     }
		if (pause)
		{
			float s = 0.1;
			if (GetAsyncKeyState(VK_UP)) { //w
				angx += s;

			}
			else if (GetAsyncKeyState(VK_DOWN)) { // s
				angx -= s;
			}
			else if (GetAsyncKeyState(VK_LEFT)) { // a
				angz += s;
			}
			else if (GetAsyncKeyState(VK_RIGHT)) { // d
				angz -= s;
			}
			else if (GetAsyncKeyState(VK_NUMPAD0)) { // d
				dist -= s;
			}
			else if (GetAsyncKeyState(VK_NUMPAD1)) { // d
				dist += s;
			}
			if (GetAsyncKeyState(VK_ESCAPE)) { pause = 0; }
		}
		else
		{
			player.changespeed();
			player.checkforberry(fruit);
			goodmove = player.move();
			if (goodmove) break;
		}
		
		
		
		for (int i = 0; i < vert; i++)
		{
			for (int k = 0; k < horiz; k++)
			{
				t = ' ';
				plane = (vec(k, i) / vec(horiz, vert)) * 2.0f;
				plane.x -= 1;
				plane.y -= 1;
				plane.x *= (horiz / vert) / (68.0 / 32.0);
				vec ro = vec(0, 0, -4);
				vec rd = vec(plane.x, plane.y, 1);
				ro.z += dist;
				ro = vec(sin(angz) * ro.z + cos(angz) * ro.x, ro.y, ro.z * cos(angz) - sin(angz) * ro.x);
				rd = vec(sin(angz) * rd.z + cos(angz) * rd.x, rd.y, rd.z * cos(angz) - sin(angz) * rd.x);
				ro = vec(ro.x, cos(angx) * ro.y - sin(angx) * ro.z, sin(angx) * ro.y + cos(angx) * ro.z);
				rd = vec(rd.x, cos(angx) * rd.y - sin(angx) * rd.z, sin(angx) * rd.y + cos(angx) * rd.z);

				rd.norm();
				if (t == ' ') {
					t = (objecttype == 0?projectcubessnake(ro, rd, player) : projectspheressnake (ro,rd,player));
					display[i * horiz + k].Char.UnicodeChar = t;
					display[i * horiz + k].Attributes = FOREGROUND_GREEN;
				}
				if (t == ' ')
				{
					t = (objecttype == 0 ? projectcubesberry(ro, rd, fruit) : projectspheresberry(ro, rd, fruit));
					display[i * horiz + k].Char.UnicodeChar = t;
					display[i * horiz + k].Attributes = FOREGROUND_RED;
				}
				if (t == ' ')
				{
					t = projectborders(ro, rd,objecttype+1);
					display[i * horiz + k].Char.UnicodeChar = t;
					display[i * horiz + k].Attributes = FOREGROUND_BLUE;
				}

			}
		}
		Sleep(gamespeed);
		WriteConsoleOutputA(console, display, { (short)horiz,(short)vert }, { 0,0 }, &write);
		if (!gtg) gtg = GamePressToStart();
	}
	GameChooseToContinue(restart, gtg);
	} while (restart);
	return;
}

//1
void GameOptions()
{


	short h = 85;
	short v = 33;
	SetConsoleCursorPosition(console, { h,v - 2 });
	cout << "Type of snake/berry: " << (objecttype == 0? "Cube": "Sphere");
	SetConsoleCursorPosition(console, { h,v });
	cout << "Field size: " << gamefieldsize << "        ";
	SetConsoleCursorPosition(console, { h,v + 2 });
	cout << "GameSpeed: " << gamespeed<< "        ";
	SetConsoleCursorPosition(console, { h,v + 4 });
	cout << "To menu ";
	SetConsoleCursorPosition(console, { h - 3,v - 2 });
	cout << "-> ";
	short pos = 0;
	while (true)
	{
		if (GetAsyncKeyState(VK_UP)) {
			SetConsoleCursorPosition(console, { h - 3,v - 2 + pos * 2 });
			cout << "   ";
			pos -= 1; if (pos == -1) pos = 3;
			SetConsoleCursorPosition(console, { h - 3,v - 2 + pos * 2 });
			cout << "-> ";
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			SetConsoleCursorPosition(console, { h - 3,v - 2 + pos * 2 });
			cout << "   ";
			pos += 1; if (pos == 4) pos = 0;
			SetConsoleCursorPosition(console, { h - 3,v - 2 + pos * 2 });
			cout << "-> ";
		}
		else if (GetAsyncKeyState(VK_RETURN))
		{
			switch (pos)
			{
			case 0: {
				objecttype = (objecttype + 1 == 2 ? 0 : 1);
				SetConsoleCursorPosition(console, { h,v - 2 });
				cout << "Type of snake/berry: " << (objecttype == 0 ? "Cube      " : "Sphere");
				break; }
			case 1: {
				gamefieldsize = (gamefieldsize + 5 == 25? 10: gamefieldsize+5);
				SetConsoleCursorPosition(console, { h,v });
				cout << "Field size: " << gamefieldsize << "        ";
				break; }
			case 2: {
				gamespeed = (gamespeed * 2 == 200 ? 25 : gamespeed * 2);
				SetConsoleCursorPosition(console, { h,v + 2 });
				cout << "GameSpeed: " << gamespeed << "        ";
				break; }
			case 3: {return; }
			}
		}
		Sleep(menudelay);

	}
	return;
}


void GameMainMenu(bool &conti)
{
	short h = 95;
	short v = 33;
	SetConsoleCursorPosition(console, {h,v-2});
	cout << "Start";
	SetConsoleCursorPosition(console, { h,v });
	cout << "Options            ";
	SetConsoleCursorPosition(console, { h,v +2 });
	cout << "Exit";
	SetConsoleCursorPosition(console, { h - 3,v - 2  });
		cout << "-> ";
	short pos = 0;
	while (true)
	{
		if (GetAsyncKeyState(VK_UP)) { 
			SetConsoleCursorPosition(console, { h-3,v - 2+pos*2 });
			cout << "   ";
			pos -= 1; if (pos == -1) pos = 2; 
			SetConsoleCursorPosition(console, { h - 3,v - 2 + pos * 2 });
			cout << "-> ";
		}
		else if (GetAsyncKeyState(VK_DOWN)) { 
			SetConsoleCursorPosition(console, { h - 3,v - 2 + pos * 2 });
			cout << "   ";
			pos += 1; if (pos == 3) pos = 0; 
			SetConsoleCursorPosition(console, { h - 3,v - 2 + pos * 2 });
			cout << "-> ";
		}
		else if (GetAsyncKeyState(VK_RETURN))
		{
			switch (pos)
			{
			case 0: {GamePlay(); return; }
			case 1: {GameOptions(); return; }
			case 2: {conti = 0; return; }
			}
		}
		Sleep(menudelay);

	}
	return;
}

int main()
{
	GameSetScreenout();
	GetSettings();
	bool conti = 1;
	while (conti)
	{
	display = GameDisplaystart();
	gamefield = GameFieldstart();	
		GameSetScreenout();
		GameLogo();
		GameMainMenu(conti);
	}
	SaveSettings();
	return 0;
}
