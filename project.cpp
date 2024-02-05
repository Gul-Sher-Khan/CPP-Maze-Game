// 22i-2637 Gulsher Khan 22i-8791 Ahsan Faraz

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Scoreboard.h"
using namespace std;

void drawHeading()
{
    gotoxy(54, 2);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << " ___   ___   ____  ____      ____  ___   ___" << endl;
    gotoxy(54, 3);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "|___| |___| |     |____     |     |___| |___|" << endl;
    gotoxy(54, 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "|  \\  |   | |____ |____     |____ |   | |  \\" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

int menu(string &n)
{
    system("cls");
    drawHeading();

    gotoxy(64, 8);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "-------------------" << endl;
    gotoxy(64, 9);
    cout << "|     1. Play     |";
    gotoxy(64, 10);
    cout << "-------------------" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    gotoxy(64, 12);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "-------------------" << endl;
    gotoxy(64, 13);
    cout << "|  2. Scoreboard  |";
    gotoxy(64, 14);
    cout << "-------------------" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    gotoxy(64, 16);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "-------------------" << endl;
    gotoxy(64, 17);
    cout << "|    3. Resume    |";
    gotoxy(64, 18);
    cout << "-------------------" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    gotoxy(64, 20);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "-------------------" << endl;
    gotoxy(64, 21);
    cout << "|      4. Auto    |";
    gotoxy(64, 22);
    cout << "-------------------" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    gotoxy(64, 24);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "-------------------" << endl;
    gotoxy(64, 25);
    cout << "|      5. Exit    |";
    gotoxy(64, 26);
    cout << "-------------------" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    int c;
    cin >> c;

    if (c == 1)
    {
        // Play
        cin.ignore();
        cout << "Enter your name: ";
        cin >> n;
        cout << "Choose difficulty: " << endl;
        cout << "1. Easy" << endl;
        cout << "2. Medium" << endl;
        cout << "3. Hard" << endl;
        cin >> c;

        switch (c)
        {
        case 1:
            return 15;
        case 2:
            return 25;
        case 3:
            return 40;
        }
    }
    else if (c == 2)
    {
        // Scoreboard
        system("cls");
        gotoxy(64, 3);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        cout << "SCOREBOARD" << endl
             << endl;
        showScoreboard();
        cout << endl
             << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << "Press any key to exit ..." << endl;

        char q;
        cin >> q;
    }
    else if (c == 3)
    {
        return 6;
    }
    else if (c == 4)
    {
        cout << "Enter your name: ";
        cin >> n;
        cout << "Choose difficulty: " << endl;
        cout << "1. Easy" << endl;
        cout << "2. Medium" << endl;
        cout << "3. Hard" << endl;
        cin >> c;
        int x;
        if (c == 1)
            x = 15;
        else if (c == 2)
            x = 25;
        else if (c == 3)
            x = 40;

        Player p;
        Game game(x, n);
        MazeSolver solver(game.getMazeGraph(), x);
        while (!solver.IS_SOLVABLE())
        {
            game = Game(x);
            solver = MazeSolver(game.getMazeGraph(), x);
        }
        setcursor(0, 0);
        char c;
        system("cls");

        game.simulateShortestPath();
        cout << "Press any key to exit ..." << endl;
        cin >> c;

        return 7;
    }
    else
    {
        // Exit
        exit(0);
    }

    return 5;
}

int main()
{
    while (1)
    {
        string name;
        srand(time(0));
        int s = menu(name);

        if (s == 5)
        {
            continue;
        }
        if (s == 7)
            continue;
        Player p;

        Game game(s, name);

        if (s == 6)
        {
            string n;
            s = game.resume(p);
            game = Game(s, n);
            game.p = p;
        }

        // Check if the maze is solvable
        MazeSolver solver(game.getMazeGraph(), s);

        // regenerate the maze until it is solvable
        while (!solver.IS_SOLVABLE())
        {
            game = Game(s);
            solver = MazeSolver(game.getMazeGraph(), s);
        }

        setcursor(0, 0);
        char c;
        system("cls");

        bool flag;
        while (true)
        {
            flag = false;
            game.print();
            if (game.isFinished())
            {
                break;
            }
            c = getInput();
            if (c == 'p')
            {
                game.pause();
                flag = true;
                break;
            }
            game.movePlayer(c);
            game.playerCollision();
        }
        if (!flag)
            game.gameOverScreen();
    }

    return 0;
}
