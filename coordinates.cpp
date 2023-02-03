// coordinates.cpp

#include <vector>
#include <cstdlib>
#include "coordinates.h"
#include "game.h"

using std::rand;

location::location(const int length, const int width) // установка размеров игрового поля
{
    length_field = length - 4; // минус стены и у стен
    width_field = width - 4;
    range_amount = 5; // число добычи
    max_length = length * 2; // максимальные значения для исключения из поиска цели
    max_width = width * 2;

    store.reserve(20);
}

void location::set_location() // случайным образом задаём координаты (но не у стен!)
{
    x_coor = 2 + rand() % (length_field);
    y_coor = 2 + rand() % (width_field);
    
    unsigned count = store.size();

    for (unsigned j = 0; j < count; j = j + 2) // если совпали перезапуск подбора координат
    {
        if (x_coor == store[j] && y_coor == store[j + 1])
        {
            set_location();
            return; // чтобы после выполнения вызванной set_location не продолжалось выполнение текущей функции.
					//Иначе иногда выскакивает баг, см ссылку на форум в main.cpp
        }
    }
    for (unsigned i = 0; i < count; i = i + 2) // пишем новые координаты в элементы вектора с максимальными значениями
    {
        if (store[i] == max_length && store[i + 1] == max_width)
        {
            store[i] = x_coor;
            store[i + 1] = y_coor;
            return;
        }
    }
    store.push_back(x_coor); // если макисмальных значений нет - то новые в конец вектора
    store.push_back(y_coor);
}

int location::get_x_coor() // получение х координаты
{
    return x_coor;
}

int location::get_y_coor() // получение у координаты
{
    return y_coor;
}

vector<int> location::get_store() // получение контейнера с координатами для выбора цели
{
    return store;
}

void location::respawn() // респаун добычи
{
    if (range_amount > 7) // если добычи на поле > 7, новых не добавляем
    {
        range_amount--; // минус одна на следующее съедение
        return;
    }
    else if (range_amount < 4) // если добычи на поле < 4, добавляем 2 новые
        amount_respawn = 2;
    else                             // в остальных случаях количество новых определяется рандомно
        amount_respawn = rand() % 3; // количество возродившейся добычи (от 0 до 2)

    range_amount = range_amount + amount_respawn - 1; // счётчик количества добычи на поле (+ новые, -1 убитая)

    for (int i = 0; i<amount_respawn; i++) // запускаем подбор координат и их установку для новой добычи
    {
        set_location();

        game respawn; // создаём объект класса game
        respawn.set_respawn_prey_coord();
    }
}

void location::replace(int del_x, int del_y) // присвоение максимальных значений координатам выбранной цели, для исключения из следующего поиска
{
    store.at(del_x) = max_length; // присваиваем использованным элементам исключающие значения
    store.at(del_y) = max_width;
}