#include "global.h"
#include <raylib.h>

using namespace std;

vector<vector<int>> convertTo2D(const vector<string> &originalArray);

int main(int argc, char *argv[])
{
    while (true)
    {
        if(system("clear")) system("cls");
        vector<Graph> mazes{
            Graph("../resources/maze1.maze"),
            Graph("../resources/maze2.maze"),
            Graph("../resources/maze3.maze"),
            Graph("../resources/maze4.maze"),
            Graph("../resources/maze5.maze"),
            Graph("../resources/maze6.maze"),
            Graph("../resources/maze7.maze"),
        };

        paths solution = startMazeSolver(mazes);

        vector<vector<int>> maze = convertTo2D(solution.maze->Data);
        vector<int> traversingPath, resultedPath;
        int count = 0;
        bool isTraverse = false;
        bool isSolved = false, start = false;
        auto edgeList = solution.maze->EdgeList;
        int cellSizeY = 80, cellSizeX = 80;
        int size = sqrt(solution.maze->Data.size());


        InitWindow(cellSizeX*size, cellSizeY*size, "Maze Solver");
        SetTargetFPS(60);
        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(BLACK);
            if (start)
            {
                for (int i = 0; i < maze.size(); i++)
                {
                    if (count > 60 && !solution.traverseList.empty() && !isTraverse)
                    {
                        count = 0;
                        traversingPath.push_back(solution.traverseList.front());
                        solution.traverseList.erase(solution.traverseList.begin());
                    }
                    else if (count > 60 && !solution.Result.empty() && isSolved)
                    {
                        count = 0;
                        resultedPath.push_back(solution.Result.front());
                        solution.Result.erase(solution.Result.begin());
                    }
                    int posy = (i)*cellSizeY, posx = 0;
                    for (int j = 0; j < maze[i].size(); j++)
                    {
                        posx = j * cellSizeX;
                        int bottom = maze[i][j], right = maze[i][j], left = maze[i][j], current = maze[i][j];
                        if (i + 1 < maze.size())
                        {
                            bottom = maze[i + 1][j];
                        }
                        if (j + 1 < maze.size())
                        {
                            right = maze[i][j + 1];
                        }
                        if (j - 1 >= 0)
                        {
                            left = maze[i][j - 1];
                        }
                        if (find(edgeList.begin(), edgeList.end(), make_pair(current, bottom)) != edgeList.end() ||
                            find(edgeList.begin(), edgeList.end(), make_pair(bottom, current)) != edgeList.end())
                        {
                            DrawRectangle(posx, posy, cellSizeX - 10, cellSizeY + 10, RAYWHITE);
                        }
                        if (find(edgeList.begin(), edgeList.end(), make_pair(current, right)) != edgeList.end() ||
                            find(edgeList.begin(), edgeList.end(), make_pair(right, current)) != edgeList.end())
                        {
                            DrawRectangle(posx, posy, cellSizeX + 10, cellSizeY - 10, RAYWHITE);
                        }
                        if (find(edgeList.begin(), edgeList.end(), make_pair(current, left)) != edgeList.end() ||
                            find(edgeList.begin(), edgeList.end(), make_pair(left, current)) != edgeList.end())
                        {
                            DrawRectangle(posx - 10, posy, cellSizeX, cellSizeY - 10, RAYWHITE);
                        }
                        else
                        {
                            DrawRectangle(posx, posy, cellSizeX - 10, cellSizeY - 10, RAYWHITE);
                        }
                        if (maze[i][j] == solution.start)
                        {
                            DrawRectangle(posx, posy, cellSizeX - 10, cellSizeY - 10, GREEN);
                        }
                        if (maze[i][j] == solution.end)
                        {
                            DrawRectangle(posx, posy, cellSizeX - 10, cellSizeY - 10, RED);
                        }

                        if (!isTraverse)
                        {
                            for (int k = 0; k < traversingPath.size(); k++)
                            {
                                if (maze[i][j] == traversingPath[k])
                                {
                                    DrawRectangle(posx, posy, cellSizeX - 10, cellSizeY - 10, BLUE);
                                }
                                else if (traversingPath[k] == solution.end)
                                {
                                    isSolved = true;
                                    isTraverse = true;
                                }
                            }
                        }
                        if (isSolved)
                        {
                            for (int k = 0; k < resultedPath.size(); k++)
                            {
                                if (maze[i][j] == resultedPath[k])
                                {
                                    DrawRectangle(posx, posy, cellSizeX - 10, cellSizeY - 10, PURPLE);
                                }
                            }
                        }
                        // DrawText(TextFormat("%d", maze[i][j]), posx + cellSizeX / 2 - 10, posy + cellSizeY / 2 - 10, 20, BLACK);
                        if (isSolved)
                        {
                            DrawText("Time taken: ", 10, 120, 30, RED);
                            DrawText(TextFormat("%d microseconds", solution.timeTaken), 200, 120, 30, RED);
                            DrawText("Solved", 10, 10, 30, RED);
                            DrawText("Press Escape to restart", 10, 70, 30, RED);
                        }
                    }
                    count++;
                }
            }
            else
            {
                DrawText("Press Enter to start", 10,10, 30, RED);
                if (IsKeyPressed(KEY_ENTER))
                    start = true;
            }
            EndDrawing();
        }
        CloseWindow();
    }
    return 0;
}

vector<vector<int>> convertTo2D(const vector<string> &originalArray)
{
    int length = originalArray.size();
    int n = (int)sqrt(length); // Assuming the original array's size is a perfect square

    vector<vector<int>> twoDArray(n, vector<int>(n));

    for (int i = 0; i < length; ++i)
    {
        int row = i / n;
        int col = i % n;
        twoDArray[row][col] = i;
    }

    return twoDArray;
}
