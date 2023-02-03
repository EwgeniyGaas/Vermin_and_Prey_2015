// game.h

#ifndef GAME_H
#define GAME_H

#include <vector>

using std::vector;

class game
{
public:

    void set_coord(); // присвоение значений переменным и получение координат хищника
    void aim_select(); // выбор цели
    void screen(); // вывод на экран
    void move_vermin(); // движение хищника к цели
    void set_respawn_prey_coord(); // получение координат добычи при респауне

    struct object
    {
        int x; // координата объекта по горизонтали
        int y; // координата объекта по вертикали
        char view; // внешний вид объекта
    };

private:

    void set_prey_coord(); // получение координат добычи

    vector<int> store; // хранилище координат
    int amount; // количество добычи
    int del_x; // хранилище адреса пары координат выбранной цели, для очистки значений
    int del_y;
};

#endif