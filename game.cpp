// game.cpp

#include <iostream>
#include <Windows.h>
#include <cmath>
#include "game.h"
#include "map.h"
#include "coordinates.h"

using std::cout;
using std::endl;
using std::vector;
using std::pow;
using std::sqrt;

location coordinate(length, width); // создаём объект класса location

game::object vermin; // хищник
game::object prey; // добыча
game::object aim; // цель-добыча

//-----------------------------------------------------------

void game::set_coord() // присваиваем значения переменным
{
    coordinate.set_location(); // установка координат хищника
    vermin.x = coordinate.get_x_coor(); // получение координаты хищника по горизонтали
    vermin.y = coordinate.get_y_coor(); // получение координаты хищника по вертикали
    vermin.view = 'V'; // внешний вид хищника

    map[vermin.y][vermin.x] = vermin.view; // задаём положение хищника

    aim.view = 'A'; // внешний вид цели-добычи
    prey.view = 'P'; // внешний вид добычи
    amount = 5; // количество добычи в начале

    for (int i = 0; i<amount; i++) // получение координат добычи
    {
        set_prey_coord();
    }
}

void game::set_prey_coord() // получение координат добычи
{
    coordinate.set_location(); // установка координат добычи
    prey.x = coordinate.get_x_coor(); // получение координаты добычи по горизонтали
    prey.y = coordinate.get_y_coor(); // получение координаты добычи по вертикали

    map[prey.y][prey.x] = prey.view; // задаём положение добычи
}
//----------------------------------------------------------

void game::aim_select() // выбор цели
{
    store = coordinate.get_store(); // получение контейнера с координатами для выбора цели

    int store_size = store.size(); // размер контейнера

    double d_ctrl = sqrt(pow(length, 2.0) + pow(width, 2.0)); // кратчайшее расстояние (по умолчанию, максимально возможное)
    double dist; // расстояние до цели

    for (int i = 2; i<store_size; i = i + 2) // сравниваем попарно координаты хищника с парами координат добычи
    {
        dist = sqrt(pow(vermin.x - store[i], 2.0) + pow(vermin.y - store[i + 1], 2.0)); // находим расстояние до добычи

        if (dist < d_ctrl) // если измеренное расстояние меньше кратчайшего
        {
            d_ctrl = dist; // сохраняем это расстояние, как кратчайшее
            aim.x = store[i]; // назначаем эту пару координат целью
            aim.y = store[i + 1];
            del_x = i; // сохраняем адрес этой пары координат для очистки значений
            del_y = i + 1;
        }
    }
    map[aim.y][aim.x] = aim.view; // помещаем цель на карту
    coordinate.replace(del_x, del_y); // отправляем её координаты на уничтожение
}
//-------------------------------------------------------------

void game::screen() // вывод на экран
{
    system("cls"); // Очистка экрана от предыдущего ввода

    for (int i = 0; i<width; i++) // выводим карту на экран
    {
        for (int j = 0; j<length; j++)
            cout << map[i][j];

        cout << endl; // переход к следующему ряду карты (следующая строка массива)
    }
}
//-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -

void game::move_vermin() // движение хищника к цели
{
    bool correct = false;

    do
    {
        int dx = vermin.x - aim.x; // находим разности координат хищника идобычи
        int dy = vermin.y - aim.y;

        map[vermin.y][vermin.x] = ' '; // закрашиваем клетку где стоял хищник пробелом

        if (abs(dx) > abs(dy)) // корректируем координаты хищника ориентируясь на координаты добычи
        {
            if (vermin.x > aim.x)
                vermin.x--;
            else if (vermin.x < aim.x)
                vermin.x++;
        }
        else
        {
            if (vermin.y > aim.y)
                vermin.y--;
            else if (vermin.y < aim.y)
                vermin.y++;
        }
        map[vermin.y][vermin.x] = vermin.view; // задаём новое положение хищника

        Sleep(300); // делаем паузу перед следующим шагом хищника

        if (vermin.x == aim.x && vermin.y == aim.y) // добыча поймана и съедена
        {
            correct = true;
            coordinate.respawn(); // респаун добычи
            screen();
        }
        else
            screen();
    } while (correct == false);
}

void game::set_respawn_prey_coord() // получение координат добычи при респауне
{
    prey.x = coordinate.get_x_coor(); // получение координаты добычи по горизонтали
    prey.y = coordinate.get_y_coor(); // получение координаты добычи по вертикали

    map[prey.y][prey.x] = prey.view; // задаём положение добычи
}