// main.cpp

#include <iostream>
#include <ctime>

#include "map.h"
#include "game.h"

int main()
{
    srand(static_cast<unsigned int> (time(NULL)));

    map_making(); // подготовка карты

    game start; // создаём объект класса game

    start.set_coord(); // устанавливаем первоначальное расположение хищника и добычи

    while (true)
    {
        start.aim_select(); // получение контейнера с координатами и выбор цели
        start.screen(); // вывод на экран
        start.move_vermin(); // движение хищника к цели
    }
}