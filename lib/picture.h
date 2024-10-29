#ifndef PICTURE_H
#define PICTURE_H
#include <fstream>
#include <cstdint>
#include <iostream>

class Image {
public:
    Image(int width, int height);
    ~Image();

    void Export(const char* path, uint64_t** matrix, int32_t count);
private:
    int m_width;
    int m_height;
    static const uint8_t kFileHeader = 14;
    static const uint8_t kInformationSize = 40;
    static const uint8_t kPalitre = 20;  
};

#endif



