#include "bmp.h"
#include "lib.h"


void Matrix(uint64_t** matrix, Queue& q, int16_t x, int16_t y) {
    for (int16_t i = 0; i < x; i++) {
        for (int16_t j = 0; j < y; j++) {
            if (ContainsCoordinate(q, i, j)) {
                matrix[i][j] = GetElement(q, i, j);
            }
            else {
                matrix[i][j] = 0;
            }
        }
    }
}

void SpreadSand(uint64_t** matrix, int16_t width, int16_t height) {
    for (int i = 1; i < width-1; i++) {
        for (int j = 1; j < height-1; j++) {
            while (matrix[i][j] >= 4) {
                matrix[i][j] -= 4;
                matrix[i-1][j] += 1;
                matrix[i+1][j] += 1; 
                matrix[i][j-1] += 1;
                matrix[i][j+1] += 1; 
            }
        }
    }
}

void FillQueueFour(Queue& q, uint64_t** matrix, int16_t width, int16_t height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (matrix[i][j] >= 4) {
                AddQueue(q, i, j, matrix[i][j]);
            }
        }
    }
}

bool CanSpread(uint64_t** matrix, int16_t width, int16_t height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (matrix[i][j] >= 4) {
                return true;
            }
        }
    }
    return false;
}


void FillQueue(Queue& q, uint64_t** matrix, int16_t width, int16_t height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            AddQueue(q, i, j, matrix[i][j]);
        }
    }

}

void QueueActivisation(Queue& q) {
    q.head = nullptr;
    q.tail = nullptr;
}


bool IsEmpty(Queue& q) {
    return q.head == nullptr;
}

void AddQueue(Queue& q, int16_t x, int16_t y, uint64_t sand) {
    Cord* newnode = new Cord{x, y, sand, nullptr};
    if (IsEmpty(q)) {
        q.head = newnode;
        q.tail = newnode;
    }
    else {
        q.tail->next = newnode;
        q.tail = newnode;
    }
}

Cord* DeleteQueue(Queue& q) {
    if (IsEmpty(q)) {
        return nullptr;
    }
    else {
        Cord* result = q.head;
        q.head = q.head->next;

        if (q.head == nullptr) {
            q.tail = nullptr;
        }

        return result;
    }

}

bool ContainsCoordinate(Queue& q, int16_t x, int16_t y) {
    Cord* current = q.head;
    
    while (current != nullptr) {
        if (current->x == x && current->y == y) {
            return true;
        }
        current = current->next;
    }
    
    return false; 
}


int64_t GetElement(Queue& q, int16_t x, int16_t y) {
    Cord* current = q.head;
    while (current != nullptr) {
        if (current->x == x && current->y == y) {
            return current->sand;
        }
        current = current->next;
    }
    return 0;
}

int16_t MaxX(Queue& q) {
    if (IsEmpty(q)) {
        std::cerr << "Queue is empty" << std::endl;
        return -1;
    }

    Cord* current = q.head;
    int16_t max_x = current->x;

    while (current != nullptr) {
        if (current->x > max_x) {
            max_x = current->x;
        }
        current = current->next;
    }

    return max_x;
}

int16_t MaxY(Queue& q) {
    if (IsEmpty(q)) {
        std::cerr << "Queue is empty" << std::endl;
        return -1;
    }

    Cord* current = q.head;
    int16_t max_y = current->y;

    while (current != nullptr) {
        if (current->y > max_y) {
            max_y = current->y;
        }
        current = current->next;
    }

    return max_y;
}

int16_t MinX(Queue& q) {
    if (IsEmpty(q)) {
        std::cerr << "Queue is empty" << std::endl;
        return -1;
    }

    Cord* current = q.head;
    int16_t min_x = current->x;
    while (current != nullptr) {
        if (current->x < min_x) {
            min_x = current->x;
        }
        current = current->next;
    }
    return min_x;
}

int16_t MinY(Queue& q) {
    if (IsEmpty(q)) {
        std::cerr << "Queue is empty" << std::endl;
        return -1;
    }

    Cord* current = q.head;
    int16_t min_y = current->y;
    while (current != nullptr) {
        if (current->y < min_y) {
            min_y = current->y;
        }
        current = current->next;
    }
    return min_y;
}



void ChangeSize(Queue& q, int16_t min_x, int16_t min_y) {
    Cord* current = q.head;
    while (current != nullptr) {
        current->x -= min_x;
        current->y -= min_y;
        current = current->next;
    }
}

bool CheckIfFits(Queue& q,  int16_t max_x, int16_t max_y) {
    Cord* current = q.head;
    while (current != nullptr) {
        if (current->sand >= 4) {
            if (current->x == 0 || current->x == max_x) {
                return false;
            }
        }
        if (current->sand >= 4) {
            if (current->y == 0 || current->y == max_y) {
                return false;
            }
        }
        current = current->next;
    }
    return true;
}

void ClearMemory(Queue& q) {
    while (!IsEmpty(q)) {
        Cord* temp = DeleteQueue(q);
        delete temp;
    }
}