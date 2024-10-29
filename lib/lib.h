#ifndef LIB_H
#define LIB_H

#include "bmp.h"
#include <cstdint>
#include <cstring>
#include <fstream>

struct Queue;

struct StructArgs {
    const char* input_arg = nullptr;
    const char* ouput_arg = nullptr;
    int max_arg = 0;
    int freq_arg = 0;
};

bool IsDigit(char* argv);

bool CheckArgs(int argc, char** argv);

void ParsArgs(StructArgs& check, int argc, char** argv);

void OpenFile(StructArgs& check,Queue& q);

#endif