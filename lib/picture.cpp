
#include "picture.h"

Image::Image(int width, int height) {
    m_width = width;
    m_height = height;
}
Image::~Image() {}

void Image::Export(const char* path, uint64_t** matrix, int32_t count = 0)
{   
    char path_copy[256];
    if (count > 0) {
        std::sprintf(path_copy, "%s_%d.bmp", path, count);
    } else {
        std::snprintf(path_copy, sizeof(path_copy), "%s.bmp", path);
    }
     
    std::ofstream f;
    f.open(path_copy, std::ios::out | std::ios::binary);

    if (!f.is_open()) {
        std::cout << "Something went wrong with opening" << std::endl;
        return;
    }
    int64_t bmp_pad = std::ceil(static_cast<float>(m_width) / 2);
    const int padding_amount = ((4 - (bmp_pad) % 4) % 4);

    const int filesize = kFileHeader + kInformationSize + kPalitre + m_height * m_width;

    unsigned char FileHeader[kFileHeader];

    FileHeader[0] = 'B';
    FileHeader[1] = 'M';

    FileHeader[2] = filesize;
    FileHeader[3] = filesize >> 8;
    FileHeader[4] = filesize >> 16;
    FileHeader[5] = filesize >> 24;

    FileHeader[6] = 0;
    FileHeader[7] = 0;

    FileHeader[8] = 0;
    FileHeader[9] = 0;

    FileHeader[10] = kFileHeader + kInformationSize + kPalitre;
    FileHeader[11] = 0;
    FileHeader[12] = 0;
    FileHeader[13] = 0;

    unsigned char InformationHeader[kInformationSize + kPalitre];

    InformationHeader[0] = kInformationSize;
    InformationHeader[1] = 0;
    InformationHeader[2] = 0;
    InformationHeader[3] = 0;

    InformationHeader[4] = m_width;
    InformationHeader[5] = m_width >> 8;
    InformationHeader[6] = m_width >> 16;
    InformationHeader[7] = m_width >> 24;

    InformationHeader[8] = m_height;
    InformationHeader[9] = m_height >> 8;
    InformationHeader[10] = m_height >> 16;
    InformationHeader[11] = m_height >> 24;

    InformationHeader[12] = 1;
    InformationHeader[13] = 0;

    InformationHeader[14] = 4;
    InformationHeader[15] = 0;

    InformationHeader[16] = 0;
    InformationHeader[17] = 0;
    InformationHeader[18] = 0;
    InformationHeader[19] = 0;

    InformationHeader[20] = 0;
    InformationHeader[21] = 0;
    InformationHeader[22] = 0;
    InformationHeader[23] = 0;

    InformationHeader[24] = 0;
    InformationHeader[25] = 0;
    InformationHeader[26] = 0;
    InformationHeader[27] = 0;

    InformationHeader[28] = 0;
    InformationHeader[29] = 0;
    InformationHeader[30] = 0;
    InformationHeader[31] = 0;

    InformationHeader[32] = 5;
    InformationHeader[33] = 0;
    InformationHeader[34] = 0;
    InformationHeader[35] = 0;

    InformationHeader[36] = 0;
    InformationHeader[37] = 0;
    InformationHeader[38] = 0;
    InformationHeader[39] = 0;

    InformationHeader[40] = 255;
    InformationHeader[41] = 255;
    InformationHeader[42] = 255;
    InformationHeader[43] = 0;

    InformationHeader[44] = 0;
    InformationHeader[45] = 255;
    InformationHeader[46] = 0;
    InformationHeader[47] = 0;

    InformationHeader[48] = 255;
    InformationHeader[49] = 0;
    InformationHeader[50] = 150;
    InformationHeader[51] = 0;

    InformationHeader[52] = 0;
    InformationHeader[53] = 255;
    InformationHeader[54] = 255;
    InformationHeader[55] = 0;

    InformationHeader[56] = 0;
    InformationHeader[57] = 0;
    InformationHeader[58] = 0;
    InformationHeader[59] = 0;
    
    f.write(reinterpret_cast<char*>(FileHeader), kFileHeader);
    f.write(reinterpret_cast<char*>(InformationHeader), kInformationSize + kPalitre);
    uint64_t value_two;
    uint64_t value;
    unsigned char padding = 0;
    for (int y = m_height - 1; y  >= 0; y--) {
        for (int x = m_width-1; x >= 0; x-=2) {
            value = matrix[y][x];
            if (x - 1 >= 0) {
                value_two = matrix[y][x-1];

            } else {
                value_two = 0;
            }
            if (value > 3) {
                value = 4;
            }
            if (value_two > 3) {
                value_two = 4;
            }
            uint8_t color = (value << 4) | value_two;

            f.write(reinterpret_cast<char*>(&color), 1);
        }
        f.write(reinterpret_cast<char*>(&padding), padding_amount);
    }

    f.close();

    std::cout << "File could be created" << "\n";
}
