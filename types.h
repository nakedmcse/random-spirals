#ifndef RANDOM_SPIRALS_TYPES_H
#define RANDOM_SPIRALS_TYPES_H
#include <stddef.h>
#include <stdlib.h>
#include "raylib.h"

typedef struct pointsArray {
    Vector2 * points;
    size_t size;
    size_t capacity;
} pointsArray;

inline void appendPoint(pointsArray * array, Vector2 point) {
    if (array->size >= array->capacity) {
        if (array->capacity == 0) array->capacity = 256;
        else array-> capacity *= 2;
        array->points = realloc(array->points, array->capacity * sizeof(Vector2));
    }
    array->points[array->size++] = point;
}
#endif //RANDOM_SPIRALS_TYPES_H