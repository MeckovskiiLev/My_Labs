#ifndef BMP_H
#define BMP_H
#include <cstdint>
#include <cstdint>
#include <iostream>

struct Cord {
    int16_t x;
    int16_t y;
    uint64_t sand;
    Cord* next;
};

struct Queue {
    Cord* head;
    Cord* tail;
};
void Matrix(uint64_t** matrix, Queue& q, int16_t x, int16_t y);
void QueueActivisation(Queue& q);
bool IsEmpty(Queue& q);
void AddQueue(Queue& q, int16_t x, int16_t y, uint64_t sand);
void FillQueue(Queue& q, uint64_t** matrix, int16_t width, int16_t height);
void FillQueueFour(Queue& q, uint64_t** matrix, int16_t width, int16_t height);
Cord* DeleteQueue(Queue& q);
bool ContainsCoordinate(Queue& q, int16_t x, int16_t y);
int64_t GetElement(Queue& q, int16_t x, int16_t y);
int16_t MaxX(Queue& q);
int16_t MaxY(Queue& q);
int16_t MinX(Queue& q);
int16_t MinY(Queue& q);
void SpreadSand(uint64_t** matrix, int16_t width, int16_t height);
bool CanSpread(uint64_t** matrix, int16_t width, int16_t height);
void SpreadWhilePossible(uint64_t** matrix, int16_t width, int16_t height);
bool CheckIfFits(Queue& q, int16_t max_x, int16_t max_y);
void ChangeSize(Queue& q, int16_t min_x, int16_t min_y);
void ClearMemory(Queue& q);

#endif