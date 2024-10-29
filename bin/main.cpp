#include <iostream>
#include "../lib/lib.h"
#include "../lib/bmp.h"
#include "../lib/picture.h"
#include <cstdint>

int main(int argc, char** argv) {
    StructArgs check;
    Queue q;
    QueueActivisation(q);
    
    if (argc < 2) {
        std::cout << "Not enough arguments" << "\n";
        return 1;
    }
    if (!CheckArgs(argc, argv)) {
        std::cout << "Some args are incorrect, please, try again" << "\n";
    } else {
        ParsArgs(check, argc, argv);
    }
    
    if (check.input_arg != nullptr) {
        OpenFile(check, q);
    }
    char full_path[256];
    std::snprintf(full_path, sizeof(full_path), "%s/output", check.ouput_arg);


    int16_t max_x = MaxX(q);
    int16_t max_y = MaxY(q);
    int16_t min_x = MinX(q);
    int16_t min_y = MinY(q);
    
    int16_t height = max_y - min_y +1;
    int16_t width = max_x - min_x +1;

    uint64_t** matrix = new uint64_t*[width];
    for (int i = 0; i < width; i++) {
        matrix[i] = new uint64_t[height]; 
    }
    ChangeSize(q, min_x, min_y);

    Matrix(matrix, q, width, height);
    ClearMemory(q);
    FillQueueFour(q, matrix, width, height);

    uint64_t count_iter = 0;

    while (!IsEmpty(q) && (check.max_arg == 0 || check.max_arg > count_iter)) {
        if (!CheckIfFits(q, width, height)) {
            width += 2;
            height +=2;
            uint64_t** new_matrix = new uint64_t*[width];
            for (int i = 0; i < width; i++) {
                new_matrix[i] = new uint64_t[height];
                std::fill(new_matrix[i], new_matrix[i] + height, 0);
            }

            for (int i =0; i < width -2; i++) {
                for (int j = 0; j < height -2; j++) {
                    new_matrix[i+1][j+1] = matrix[i][j];
                }
            }
            ChangeSize(q, -1, -1);
            for (int i = 0; i < width - 2; i++) {
            delete[] matrix[i];
                }
            delete[] matrix;
            matrix = new_matrix;  
        } 
        SpreadSand(matrix, width, height);
        ClearMemory(q);
        FillQueueFour(q, matrix, width, height);
        if (check.freq_arg != 0 && count_iter % check.freq_arg == 0 && count_iter != 0) {
            Image image(width, height);
            image.Export(full_path, matrix, count_iter);
        }
        count_iter++;

    }
    if (check.freq_arg == 0) {
        Image image(width, height);
        image.Export(full_path, matrix, count_iter);
    }
    return 0;
}