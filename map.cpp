// map.cpp

#include "map.h"

char map[width][length]; // карта игры

void map_making() // построение карты
{
    char wall = '#';

    for (int i = 0; i<width; i = i + width - 1) // создаём горизонтальные стены
    {
        for (int j = 0; j<length; j++)
            map[i][j] = wall;
    }
    for (int i = 1; i<width - 1; i++) // создаём вертикальные стены
    {
        for (int j = 0; j<length; j = j + length - 1)
            map[i][j] = wall;
    }
    for (int i = 1; i<width - 1; i++) // инициализация внутренних клеток игровой карты пробелами
    {
        for (int j = 1; j<length - 1; j++)
            map[i][j] = ' ';
    }
}