// coordinates.h

#ifndef COORDINATES_H
#define COORDINATES_H

using std::vector;

class location
{
public:

    location(const int, const int); // конструтор - присвоение значений переменным
    void set_location(); // установка рандомных координат (не в стене и не у стен)
    int get_x_coor(); // получение х координаты
    int get_y_coor(); // получение у координаты
    vector<int> get_store(); // получение контейнера с координатами для выбора цели
    void respawn(); // респаун добычи
    void replace(int, int); // присвоение максимальных значений координатам выбранной цели, для исключения из следующего поиска

private:

    vector<int> store; // хранилище координат
    int x_coor; // х координата
    int y_coor; // у координата
    int length_field; // длина карты, минус по 2 клетки от краёв
    int width_field; // ширина карты, минус по 2 клетки от краёв
    int max_length; // максимальные значения для исключения из поиска цели
    int max_width;
    int amount_respawn; // количество возродившейся добычи
    int range_amount; // регулятор численности добычи
};

#endif