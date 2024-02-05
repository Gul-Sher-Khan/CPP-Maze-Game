// 22i-2637 Gulsher Khan 22i-8791 Ahsan Faraz

#include <iostream>
#include "vector.h"
#include "Game.h"

class MazeSolver // Class maze slver
{
private:
    Node **Mazee;
    int Row, Columns;

public:
    MazeSolver(Node **maze, int s) : Mazee(maze), Row(s), Columns(s) {}

    bool IS_SOLVABLE() // Check if the maze is solvable using Depth-First Search
    {
        vector<vector<bool>> Visit(Row, vector<bool>(Columns, false));

        Node start = Find_Start(); // Find the starting point

        return Depth_First_Search(start.x, start.y, Visit); // Use DFS to explore the maze
    }

private:
    Node Find_Start() // Find the starting point in the maze
    {
        for (int i = 0; i < Row; ++i)
        {
            for (int j = 0; j < Columns; ++j)
            {
                if (Mazee[i][j].key == 'S')
                {
                    return {i, j};
                }
            }
        }

        return {-1, -1}; // No starting point found
    }

    bool Depth_First_Search(int x, int y, vector<vector<bool>> &visited) // Depth-First Search function
    {

        if (x < 0 || x >= Row || y < 0 || y >= Columns || visited[x][y]) // Check if current position is outside the maze or already visited
        {
            return false;
        }

        visited[x][y] = true; // Mark the current position as visited

        if (Mazee[x][y].key == 'F') // Check if the current position is the exit
        {
            return true;
        }

        // Explore neighboring cells in DFS fashion
        bool FOUND = false;
        if (x > 0 && Mazee[x - 1][y].key != '#' && Depth_First_Search(x - 1, y, visited))
        {
            FOUND = true;
        }
        if (x < Row - 1 && Mazee[x + 1][y].key != '#' && Depth_First_Search(x + 1, y, visited))
        {
            FOUND = true;
        }
        if (y > 0 && Mazee[x][y - 1].key != '#' && Depth_First_Search(x, y - 1, visited))
        {
            FOUND = true;
        }
        if (y < Columns - 1 && Mazee[x][y + 1].key != '#' && Depth_First_Search(x, y + 1, visited))
        {
            FOUND = true;
        }

        return FOUND;
    }
};
