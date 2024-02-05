// 22i-2637 Gulsher Khan 22i-8791 Ahsan Faraz

#include <iostream>
#include <windows.h>
#include <chrono>
#include <fstream>
#include "header.h"
#include "queue.h"
#include "list.h"

using namespace std;

int calculateScore(int steps, int coins, int trophies, int obstaclesHit) // Function for calculating score by making formula from steps ,coins ,rophies and obstacles
{
    // values assigning to function variables
    const double stepsWeight = -0.15;
    const double coinsWeight = 3.0;
    const double trophiesWeight = 6.0;
    const double obstaclesWeight = -3.0;
    // Formula for calculating score
    double score = steps * stepsWeight + coins * coinsWeight + trophies * trophiesWeight + obstaclesHit * obstaclesWeight;

    score = max(0.0, score); // initially start from zero

    return static_cast<int>(score); // returns score
}

struct Node
{
    char key;
    Node *left;
    Node *right;
    Node *up;
    Node *down;
    bool visited;
    bool wallLeft;
    bool wallRight;
    bool wallUp;
    bool wallDown;
    int x;
    int y;

    Node(char k = ' ', int x = 0, int y = 0) // parameterizd constructor
        : key(k), left(nullptr), right(nullptr), up(nullptr), down(nullptr), x(x), y(y)
    {
        visited = false;
        wallLeft = false;
        wallRight = false;
        wallUp = false;
        wallDown = false;
    }
};

struct collectible // node for collecting coins, trophies etc
{
    int x;
    int y;
    char key;

    collectible(int x = 0, int y = 0, char key = 'C') : x(x), y(y), key(key) {} // parameterized constructor
};

struct Player // structure for player score, lives etc
{
    string name;
    int x;
    int y;
    int score;
    int lives;
    list<collectible> collectibles; // list for collectables (coins, trophies etc)
    int coins;
    int trophies;
    int obstaclesHit;
    int steps;

    Player(int x = 0, int y = 0, string n = "") : x(x), y(y) // parametrized constructor
    {
        score = 0;
        lives = 5; // maximum lives will be 5
        coins = 0;
        trophies = 0;
        name = n;
        obstaclesHit = 0;
        steps = 0;
    }
};

class Maze // maze class
{
private:
    int size;

public:
    Node **mazeGraph;         // double ponter
    Maze(int s = 0) : size(s) // constructor
    {
        mazeGraph = new Node *[size];
        for (int i = 0; i < size; ++i) // Loop for maze size
        {
            mazeGraph[i] = new Node[size];
            for (int j = 0; j < size; ++j)
            {
                mazeGraph[i][j] = Node('.', j, i);
            }
        }
    }

    void addEdge(int x1, int y1, int x2, int y2) // Function for adding ege using x and y coordinates
    {
        if (x1 < 0 || x1 >= size || y1 < 0 || y1 >= size || x2 < 0 || x2 >= size || y2 < 0 || y2 >= size)
        {
            return;
        }

        if (x1 + 1 < size)
        {
            mazeGraph[y1][x1].right = &mazeGraph[y1][x1 + 1];
            mazeGraph[y1][x1 + 1].left = &mazeGraph[y1][x1];
        }

        if (x2 - 1 >= 0)
        {
            mazeGraph[y2][x2].left = &mazeGraph[y2][x2 - 1];
            mazeGraph[y2][x2 - 1].right = &mazeGraph[y2][x2];
        }

        if (y1 + 1 < size)
        {
            mazeGraph[y1][x1].down = &mazeGraph[y1 + 1][x1];
            mazeGraph[y1 + 1][x1].up = &mazeGraph[y1][x1];
        }

        if (y2 - 1 >= 0)
        {
            mazeGraph[y2][x2].up = &mazeGraph[y2 - 1][x2];
            mazeGraph[y2 - 1][x2].down = &mazeGraph[y2][x2];
        }
    }

    void print(Player p) // Function to print Maze
    {
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                gotoxy(j * 2, i);

                if (i == p.y && j == p.x)
                    cout << 'P';
                else
                    cout << mazeGraph[i][j].key << " ";
            }
        }
    }

    int getSize() // size getter
    {
        return size;
    }

    void updateConsole(Player p) // Function  for updating console
    {
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (size == 40)
                    gotoxy((j * 2) + 35, i);
                else if (size == 25)
                    gotoxy((j * 2) + 55, i + 5);
                else if (size == 15)
                    gotoxy((j * 2) + 65, i + 10);
                if (i == 0 && j == 0)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
                    cout << 'S';
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
                else if (i == size - 1 && j == size - 1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
                    cout << 'F';
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
                else if (i == p.y && j == p.x)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // green for player
                    cout << 'P';
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
                else
                {
                    char cellKey = mazeGraph[i][j].key;

                    // Set colors based on the cell contents
                    if (cellKey == '#')
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); // Red for walls
                    }
                    else if (cellKey == 'O')
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); // Gray for obstacles
                    }
                    else if (cellKey == 'C' || cellKey == 'T')
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Yellow for coins
                    }
                    else
                    {
                        // Default color (white) for other cells
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    }

                    cout << cellKey << " ";

                    // Reset text color to default
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoxy(0, size);
        gotoxy(0, 2);
        cout << "Steps: " << p.steps << endl; // printing step
        gotoxy(0, 4);
        cout << "Lives: " << p.lives << endl; // printing lives
        gotoxy(0, 6);
        cout << "Coins: " << p.coins << endl; // printing coins
        gotoxy(0, 8);
        cout << "Trophies: " << p.trophies << endl; // printing trophies
        gotoxy(0, 10);
        cout << "Obstacles Hit: " << p.obstaclesHit << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
};

struct obstacle // structure for obstacles
{
    int x;
    int y;
    char key;

    obstacle(int x = 0, int y = 0, char key = 'O') : x(x), y(y), key(key) {} // parameterized constructor
};

// A class to represent a pair of values
template <typename T, typename U>
class Pair
{
public:
    T first;
    U second;

    Pair() : first(T()), second(U()) {}

    Pair(T f, U s) : first(f), second(s) {}

    bool operator==(const Pair &other) const
    {
        return (first == other.first) && (second == other.second);
    }
};

class Game // Game class
{
private:
    Maze maze; // oop concept(association)
    int s;
    int random;                // random variable
    Queue<obstacle> obstacles; // Queue for obstacles
    vector<Pair<int, int>> shortestPathCoordinates;

public:
    Player p; // Assocation

    bool isValid(int x, int y)
    {
        return x >= 0 && x < s && y >= 0 && y < s && maze.mazeGraph[y][x].key != '#';
    }

    void dijkstraShortestPath()
    {
        // Create arrays to store distance and visited status
        int distances[s][s];
        bool visited[s][s];

        // Initialize distances and visited arrays
        for (int i = 0; i < s; ++i)
        {
            for (int j = 0; j < s; ++j)
            {
                distances[i][j] = INT_MAX;
                visited[i][j] = false;
            }
        }

        // Dijkstra's algorithm
        distances[0][0] = 0;

        for (int count = 0; count < s * s - 1; ++count)
        {
            // Find the minimum distance vertex
            int minDistance = INT_MAX;
            int minIndexX = -1;
            int minIndexY = -1;

            for (int i = 0; i < s; ++i)
            {
                for (int j = 0; j < s; ++j)
                {
                    if (!visited[i][j] && distances[i][j] < minDistance)
                    {
                        minDistance = distances[i][j];
                        minIndexX = j;
                        minIndexY = i;
                    }
                }
            }

            // Mark the selected vertex as visited
            visited[minIndexY][minIndexX] = true;

            // Update the distances of the adjacent vertices
            int dx[] = {0, 0, 1, -1};
            int dy[] = {1, -1, 0, 0};

            for (int i = 0; i < 4; ++i)
            {
                int newX = minIndexX + dx[i];
                int newY = minIndexY + dy[i];

                if (isValid(newX, newY) && !visited[newY][newX] && distances[minIndexY][minIndexX] + 1 < distances[newY][newX])
                {
                    distances[newY][newX] = distances[minIndexY][minIndexX] + 1;
                }
            }
        }

        // Store the coordinates of the shortest path
        int currentX = s - 1;
        int currentY = s - 1;

        while (currentX != 0 || currentY != 0)
        {
            shortestPathCoordinates.push({currentX, currentY});

            int dx[] = {0, 0, 1, -1};
            int dy[] = {1, -1, 0, 0};

            for (int i = 0; i < 4; ++i)
            {
                int newX = currentX + dx[i];
                int newY = currentY + dy[i];

                if (isValid(newX, newY) && distances[newY][newX] == distances[currentY][currentX] - 1)
                {
                    currentX = newX;
                    currentY = newY;
                    break;
                }
            }
        }
        // Add the starting point
        shortestPathCoordinates.push({0, 0});
        // Reverse the vector to start from the origin
        shortestPathCoordinates.reverse();
    }

    void simulateShortestPath()
    {
        dijkstraShortestPath();
        for (int i = 0; i < shortestPathCoordinates.getSize() - 1; i++)
        {
            int x = shortestPathCoordinates[i].first;
            int y = shortestPathCoordinates[i].second;

            maze.mazeGraph[y][x].key = 'P'; // Mark the path with 'P'
            maze.updateConsole(p);
            Sleep(70);
            maze.mazeGraph[y][x].key = '*'; // Reset the cell to its original state
        }
    }
    void generateWalls() // function for printing maze small, medium and large
    {
        if (s == 25)
        {
            random = 4;
        }
        else if (s == 15)
        {
            random = 5;
        }
        else if (s == 40)
        {
            random = 4;
        }

        for (int i = 0; i < maze.getSize(); ++i)
        {
            for (int j = 0; j < maze.getSize(); ++j)
            {

                if (rand() % random == 1)
                {
                    maze.mazeGraph[i][j].key = '#';
                }
            }
        }

        // Fix wall boolean values
        for (int i = 1; i < s - 1; i++)
        {
            for (int j = 1; j < s - 1; j++)
            {
                maze.mazeGraph[i][j].wallLeft = (j > 0 && maze.mazeGraph[i][j - 1].key == '#');
                maze.mazeGraph[i][j].wallRight = (j < s - 1 && maze.mazeGraph[i][j + 1].key == '#');
                maze.mazeGraph[i][j].wallUp = (i > 0 && maze.mazeGraph[i - 1][j].key == '#');
                maze.mazeGraph[i][j].wallDown = (i < s - 1 && maze.mazeGraph[i + 1][j].key == '#');
            }
        }
    }

    //  Function For genrating obstacles
    void generateObstacles()
    {
        for (int i = 0; i < maze.getSize(); ++i)
        {
            for (int j = 0; j < maze.getSize(); ++j)
            {
                if (rand() % 15 == 1)
                {
                    if (maze.mazeGraph[i][j].key != 'S' && maze.mazeGraph[i][j].key != 'F' && maze.mazeGraph[i][j].key != '#')
                    {
                        maze.mazeGraph[i][j].key = 'O';
                        obstacles.enqueue(obstacle(j, i, 'O'));
                    }
                }
            }
        }
    }

    void generateCollectibles() // Function for Generating collectables(F for finish, # for wall, O for obstacle )
    {
        for (int i = 0; i < maze.getSize(); ++i)
        {
            for (int j = 0; j < maze.getSize(); ++j)
            {
                if (rand() % 10 == 1)
                {
                    if (maze.mazeGraph[i][j].key != 'S' && maze.mazeGraph[i][j].key != 'F' && maze.mazeGraph[i][j].key != '#' && maze.mazeGraph[i][j].key != 'O')
                    {
                        maze.mazeGraph[i][j].key = 'C';
                    }
                }
            }
        }

        int t;
        if (s == 15)
            t = 2;
        else if (s == 25)
            t = 3;
        else if (s == 40)
            t = 4;
        for (int i = 0; i < t; ++i)
        {
            int x = rand() % s;
            int y = rand() % s;
            if (maze.mazeGraph[y][x].key != 'S' && maze.mazeGraph[y][x].key != 'F' && maze.mazeGraph[y][x].key != '#' && maze.mazeGraph[y][x].key != 'O' && maze.mazeGraph[y][x].key != 'C')
            {
                maze.mazeGraph[y][x].key = 'T';
            }
            else
            {
                i--;
            }
        }
    }

    Game(int s, string n = "") : maze(s), p{0, 0}
    {
        p.name = n;
        this->s = s;
        // Define the edges of the maze
        for (int i = 0; i < s - 1; ++i)
        {
            maze.addEdge(i, 0, i + 1, 0); // Connect cells in the top row
            maze.addEdge(0, i, 0, i + 1); // Connect cells in the left column
        }

        generateWalls();

        maze.mazeGraph[0][0].key = 'S';         // Starting point
        maze.mazeGraph[s - 1][s - 1].key = 'F'; // Finishing point

        generateObstacles();
        generateCollectibles();
    }

    void pause() // Pause function which show score on txt fle
    {
        Beep(502, 50);
        fstream f;
        f.open("pause.txt", fstream::out);
        f << p.steps << " " << p.coins << " " << p.lives << " " << p.obstaclesHit << " " << p.trophies << " " << p.x << " " << p.y << " " << s << " " << p.name;
        f.close();
    }

    int resume(Player &p)
    {
        fstream f("pause.txt");
        string a, b, c, d, e, g, h, i, j;
        f >> a;
        f >> b;
        f >> c;
        f >> d;
        f >> e;
        f >> g;
        f >> h;
        f >> i;
        f >> j;

        p.steps = stoi(a);
        p.coins = stoi(b);
        p.lives = stoi(c);
        p.obstaclesHit = stoi(d);
        p.trophies = stoi(e);
        p.x = stoi(g);
        p.y = stoi(h);

        int x = stoi(i);
        p.name = j;

        return x;
    }

    void print() // updating console plus printing
    {

        maze.updateConsole(p);
    }

    void movePlayer(char dir)
    {
        switch (dir)
        {
        case 'w':
            if (p.y > 0 && !maze.mazeGraph[p.y][p.x].wallUp)
            {
                p.y--;
            }
            break;
        case 'a':
            if (p.x > 0 && !maze.mazeGraph[p.y][p.x].wallLeft)
            {
                p.x--;
            }
            break;
        case 's':
            if (p.y < s - 1 && !maze.mazeGraph[p.y][p.x].wallDown)
            {
                p.y++;
            }
            break;
        case 'd':
            if (p.x < s - 1 && !maze.mazeGraph[p.y][p.x].wallRight)
            {
                p.x++;
            }
            break;
        }
        // beep when player moves
        Beep(523, 50);
    }

    void removeObstacle(int x, int y, Queue<obstacle> &obstacles) // function for removing obstacles
    {
        Queue<obstacle> temp;        // Temporary Queue not built in
        while (!obstacles.isEmpty()) // loop for checking if queue is empty or not if not then there is another condition
        {
            obstacle o = obstacles.dequeue();
            if (o.x != x || o.y != y)
            {
                temp.enqueue(o);
            }
        }
        obstacles = temp;
    }
    // function for player collision
    void playerCollision()
    {

        if (maze.mazeGraph[p.y][p.x].key == 'O')
        {
            p.steps++;
            p.obstaclesHit++;
            p.lives--;
            maze.mazeGraph[p.y][p.x].key = '.';
            removeObstacle(p.x, p.y, obstacles);
        }
        else if (maze.mazeGraph[p.y][p.x].key == 'F')
        {
            p.steps++;
            p.score += 10;
        }
        else if (maze.mazeGraph[p.y][p.x].key == '.')
        {
            p.steps++;
        }
        else if (maze.mazeGraph[p.y][p.x].key == 'C')
        {
            p.steps++;
            p.coins++;
            maze.mazeGraph[p.y][p.x].key = '.';
            p.collectibles.add(collectible(p.x, p.y, 'C'));
        }
        else if (maze.mazeGraph[p.y][p.x].key == 'T')
        {
            p.steps++;
            p.trophies++;
            maze.mazeGraph[p.y][p.x].key = '.';
            p.collectibles.add(collectible(p.x, p.y, 'T'));
        }
    }
    // function for finshing of game
    bool isFinished()
    {
        if (p.lives == 0)
        {
            gotoxy(0, s + 5);
            cout << "Game Over!" << endl;
            return true;
        }
        else if (p.x == s - 1 && p.y == s - 1)
        {
            gotoxy(0, s + 5);
            cout << "You Win!" << endl;
            return true;
        }
        return false;
    }
    // Function to clear game screen and shows scores etcalso csv file handing to store this data in csv file
    void gameOverScreen()
    {
        p.score = calculateScore(p.steps, p.coins, p.trophies, p.obstaclesHit); // calling callculate score function for calculting score
        system("cls");
        gotoxy(0, 0);
        cout << "Game Over!" << endl;
        cout << "Name: " << p.name << endl;
        cout << "Steps: " << p.steps << endl;
        cout << "Coins: " << p.coins << endl;
        cout << "Trophies: " << p.trophies << endl;
        cout << "Obstacles Hit: " << p.obstaclesHit << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        cout << "Score: " << p.score << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << "Press any key to exit..." << endl;
        char q;
        cin >> q;
        // save score to a csv file
        ofstream myfile;
        myfile.open("scores.csv", ios::app);
        myfile << p.name << "," << p.score << "," << p.coins << "," << p.trophies << endl;
        myfile.close();
    }

    Node **getMazeGraph()
    {
        return maze.mazeGraph;
    }

    // print shortest path on the maze by
    void printShortestPath()
    {
    }
};
