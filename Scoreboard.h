// 22i-2637 Gulsher Khan 22i-8791 Ahsan Faraz

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Solver.h"

using namespace std;
// Function to check whether the integer is valid
bool is_valid_integer(const std::string &str)
{
    if (str.empty() || ((!isdigit(str[0])) && (str[0] != '-') && (str[0] != '+')))
    {
        return false;
    }

    char *endptr = nullptr;
    strtol(str.c_str(), &endptr, 10);

    return (*endptr == '\0');
}
// score structure
struct scores
{
    string name;
    string scoreVal;
    string coins;
    string trophies;

    scores(string name = "", string score = "", string coins = "", string trophies = "") // parameterized onstructor
    {
        this->name = name;
        this->scoreVal = score;
        this->coins = coins;
        this->trophies = trophies;
    }
};

class treeNode // tree node class
{
public:
    scores data;
    treeNode *left;
    treeNode *right;
    treeNode(scores d)
    {
        data = d;
        left = nullptr;
        right = nullptr;
    }
};

class Tree // tree class
{

public:
    treeNode *root;
    // function to insert data b score
    void insertbyscore(treeNode *&root, scores d)
    {
        if (root == nullptr)
        {
            root = new treeNode(d);
            return;
        }
        // using try catch block for exception
        try
        {
            if (is_valid_integer(d.scoreVal) && stoi(d.scoreVal) > stoi(root->data.scoreVal))
            {
                if (root->left == nullptr)
                {
                    root->left = new treeNode(d);
                    return;
                }
                else
                {
                    insertbyscore(root->left, d);
                }
            }
            else
            {
                if (root->right == nullptr)
                {
                    root->right = new treeNode(d);
                    return;
                }
                else
                {
                    insertbyscore(root->right, d);
                }
            }
        }
        catch (const std::invalid_argument &e)
        {
            cerr << "Invalid argument: " << e.what() << endl;
        }
        catch (const std::out_of_range &e)
        {
            cerr << "Out of range: " << e.what() << endl;
        }
    }
    // function to insert data by coins
    void insertbycoins(treeNode *&root, scores d)
    {
        if (root == nullptr)
        {
            root = new treeNode(d);
            return;
        }
        // using try catch blocks for handling exception
        try
        {
            if (is_valid_integer(d.coins) && stoi(d.coins) > stoi(root->data.coins))
            {
                if (root->left == nullptr)
                {
                    root->left = new treeNode(d);
                    return;
                }
                else
                {
                    insertbycoins(root->left, d);
                }
            }
            else
            {
                if (root->right == nullptr)
                {
                    root->right = new treeNode(d);
                    return;
                }
                else
                {
                    insertbycoins(root->right, d);
                }
            }
        }
        catch (const std::invalid_argument &e)
        {
            cerr << "Invalid argument: " << e.what() << endl;
        }
        catch (const std::out_of_range &e)
        {
            cerr << "Out of range: " << e.what() << endl;
        }
    }
    // function to insert data by trophies
    void insertbytrophies(treeNode *&root, scores d)
    {
        if (root == nullptr)
        {
            root = new treeNode(d);
            return;
        }
        // using try catch blocks for handling exception
        try
        {
            if (is_valid_integer(d.trophies) && stoi(d.trophies) > stoi(root->data.trophies))
            {
                if (root->left == nullptr)
                {
                    root->left = new treeNode(d);
                    return;
                }
                else
                {
                    insertbytrophies(root->left, d);
                }
            }
            else
            {
                if (root->right == nullptr)
                {
                    root->right = new treeNode(d);
                    return;
                }
                else
                {
                    insertbytrophies(root->right, d);
                }
            }
        }
        catch (const std::invalid_argument &e)
        {
            cerr << "Invalid argument: " << e.what() << endl;
        }
        catch (const std::out_of_range &e)
        {
            cerr << "Out of range: " << e.what() << endl;
        }
    }
    // Function for transfering to array
    void transferToArray(treeNode *r, scores *arr, int &i)
    {
        if (r == nullptr)
        {
            return;
        }
        transferToArray(r->left, arr, i);
        arr[i] = r->data;
        i++;
        transferToArray(r->right, arr, i);
    }
};
// function for showing scoreboard
void showScoreboard()
{

    Tree t;
    ifstream fin("scores.csv");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    gotoxy(57, 6);
    cout << "1. Show Stats by Score" << endl;
    gotoxy(57, 8);
    cout << "2. Show Stats by Coins" << endl;
    gotoxy(57, 10);
    cout << "3. Show Stats by Trophies" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    int c;
    cin >> c;

    scores scorelist[10];

    string line, word;
    int s = 0;

    while (getline(fin, line) && s < 10)
    {
        stringstream st(line);
        int i = 0;
        while (getline(st, word, ','))
        {
            if (i == 0)
            {
                scorelist[s].name = word;
            }
            else if (i == 1)
            {
                scorelist[s].scoreVal = word;
            }
            else if (i == 2)
            {
                scorelist[s].coins = word;
            }
            else if (i == 3)
            {
                scorelist[s].trophies = word;
            }
            i++;
        }

        s++;
    }

    if (c == 1)
    {
        for (int i = 0; i < 10; i++)
        {
            t.insertbyscore(t.root, scorelist[i]);
        }
    }
    else if (c == 2)
    {
        for (int i = 0; i < 10; i++)
        {
            t.insertbycoins(t.root, scorelist[i]);
        }
    }
    else if (c == 3)
    {
        for (int i = 0; i < 10; i++)
        {
            t.insertbytrophies(t.root, scorelist[i]);
        }
    }

    int index = 0;
    t.transferToArray(t.root, scorelist, index);

    gotoxy(37, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    cout << setw(3) << right << "Rank"
         << "  "
         << setw(20) << left << "Name"
         << setw(8) << right << "Score"
         << setw(10) << right << "Coins"
         << setw(12) << right << "Trophies"
         << "    "
         << "Medal" << endl;

    for (int i = 0; i < s; i++)
    {
        gotoxy(37, 15 + i);
        cout << setw(3) << right << i + 1 << ".  ";
        cout << setw(20) << left << scorelist[i].name
             << setw(8) << right << scorelist[i].scoreVal
             << setw(10) << right << scorelist[i].coins
             << setw(12) << right << scorelist[i].trophies << "    ";

        if (i == 0)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
            gotoxy(97, 15);
            cout << "Gold";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
        else if (i == 1)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
            gotoxy(97, 16);
            cout << "Silver";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
        else if (i == 2)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            gotoxy(97, 17);
            cout << "Bronze";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }

        cout << endl;
    }
}