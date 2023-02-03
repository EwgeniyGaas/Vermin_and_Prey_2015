// map.h

#ifndef MAP_H
#define MAP_H

#define length 22 // длина карты (длина поля +2 на стены по краям)
#define width 17 // ширина карты (ширина поля +2 на стены по краям)

extern char map[width][length]; // карта игры

void map_making(); // построение карты

#endif