#ifndef RANDOM_SPIRALS_TYPES_H
#define RANDOM_SPIRALS_TYPES_H
#include <stdlib.h>
#include "raylib.h"

typedef struct spiralPoint {
    Vector2 point;
    Color color;
} spiralPoint;

typedef struct pointsArray {
    spiralPoint * points;
    size_t size;
    size_t capacity;
} pointsArray;

inline void appendPoint(pointsArray * array, spiralPoint point) {
    if (array->size >= array->capacity) {
        array->capacity = array->capacity == 0 ? 256 : array->capacity * 2;
        array->points = realloc(array->points, array->capacity * sizeof(spiralPoint));
    }
    array->points[array->size++] = point;
}
#endif //RANDOM_SPIRALS_TYPES_H