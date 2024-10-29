#include "lib.h"
#include "bmp.h"


bool IsDigit(char* argv) {
    for (int i = 0; i < strlen(argv);++i) {
        if (!std::isdigit(argv[i])) {
            return false;
        }
    }
    return true;
}


bool CheckArgs(int argc, char** argv) {
    bool error = true;
    for (int i = 1; i < argc; i++) {
        if (((!strcmp(argv[i], "--ouput")) || (!strcmp(argv[i], "-o"))) && i + 1 < argc || 
            ((!strcmp(argv[i], "--input")) || (!strcmp(argv[i], "-i"))) && i + 1 < argc ||
            ((!strcmp(argv[i], "--max-iter")) || (!strcmp(argv[i], "-m"))) && i + 1 < argc && IsDigit(argv[i+1])||
            ((!strcmp(argv[i], "--freq")) || (!strcmp(argv[i], "-f")))  && i + 1 < argc && IsDigit(argv[i+1])){
                i++;
                continue;
            }
        else {           
            error = false;
        }

    }
    return error;
}

void ParsArgs(StructArgs& check, int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        if (!(strcmp(argv[i], "--input")) || (!(strcmp(argv[i], "-i")))) {
            check.input_arg = argv[i+1];
            i++;
        } 
        else if (!(strcmp(argv[i], "--output")) || (!(strcmp(argv[i], "-o")))) {
            check.ouput_arg = argv[i+1];
            i++;
        } 
        else if (!(strcmp(argv[i], "--max-iter")) || (!(strcmp(argv[i], "-m")))) {
            check.max_arg = atoi(argv[i+1]);
            i++;
        } 
        else if (!(strcmp(argv[i], "--freq")) || (!(strcmp(argv[i], "-f")))) {
            check.freq_arg = atoi(argv[i+1]);
            i++;
        } 
    }
}

void OpenFile(StructArgs& check,Queue& q) {
    std::ifstream file(check.input_arg);
    char line[32];
     while (file.getline(line, sizeof(line))) {
        char* start = line;
        char* end = nullptr;
        int const max_am = 3;
        char* cords[max_am];
        int count = 0;
        while ((end = strchr(start, '\t')) != nullptr) {
            *end = '\0';
            cords[count] = start;
            count++;
            start = end + 1;
        }
        if (count < 3) {
            cords[count] = start;
        }
        
        AddQueue(q, strtol(cords[0], nullptr, 10), strtol(cords[1], nullptr, 10), strtol(cords[2], nullptr, 10));
    }  
}