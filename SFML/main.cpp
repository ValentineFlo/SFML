#include <SFML/Graphics.hpp>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>



class entite
{
public:
    float x, y;
    float dx, dy;
    int color;
    int lettre;

};

const int TX = 40;
const int TY = 20;

entite avanceE(entite f)
{
	f.x += f.dx;

	if (f.x < 0)
	{
		f.x = 0;
		f.dx = ((float)rand() / RAND_MAX) * 2;
	}
	if (f.x >= TX)
	{
		f.x = TX - 1;
		f.dx = ((float)rand() / RAND_MAX) * -2;
	}

	f.y += f.dy;

	if (f.y < 0)
	{
		f.y = 0;
		f.dy = ((float)rand() / RAND_MAX) * 2;
	}
	if (f.y >= TY)
	{
		f.y = TY - 1;
		f.dy = ((float)rand() / RAND_MAX) * -2;
	}
	return f;
}

int top(int dur)
{
	static int start = 0;
	int res = 0;
	if (clock() > start + dur)
	{
		start = clock();
		res = 1;
	}
	return res;
}
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void textcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void consolecursor(int val)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(console, &cursorInfo);
	cursorInfo.bVisible = val;
	SetConsoleCursorInfo(console, &cursorInfo);
}



entite constructE(int color, int lettre);
void effaceE(entite f);
void afficheE(entite f);
entite avanceE(entite f);

int top(int dur);
void gotoxy(int x, int y);
void textcolor(int color);
void consolecursor(int val);

entite constructE(int color, int lettre)
{
	entite f;
	f.x = rand() % TX;
	f.y = rand() % TY;

	f.dx = ((float)rand() / RAND_MAX) * 4 - 2;
	f.dy = ((float)rand() / RAND_MAX) * 4 - 2;
	f.lettre = lettre;
	f.color = color;
	return f;
}

void effaceE(entite f)
{
	gotoxy(f.x, f.y);
	textcolor(0);
	putchar(f.lettre);
}

void afficheE(entite f)
{
	gotoxy(f.x, f.y);
	textcolor(f.color);
	putchar(f.lettre);
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
         
        window.clear();
        window.draw(shape);
        window.display();
        srand(time(NULL));
        consolecursor(false);

        entite f = constructE(1 + rand() % 255, 'A' + rand() % 26);

        while (!_kbhit)
        {
            if (top(75))
            {
                effaceE(f);
                f = avanceE(f);
                afficheE(f);
            }
        }
    }





}