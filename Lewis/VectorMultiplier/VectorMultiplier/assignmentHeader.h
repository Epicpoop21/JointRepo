#ifndef ASSIGNMENT_HEADER_H
#define ASSIGNMENT_HEADER_H

#include <stdint.h>

// Vector structure
typedef struct {
    float x;
    float y;
    float z;
    int status; // 0 = uninitialized, 1 = initialized
} vector3_t;

// Function declarations
int vectorDotProduct(vector3_t vecA, vector3_t vecB, float *result);
int vectorCrossProduct(vector3_t vecA, vector3_t vecB, vector3_t *vecOut);
int vectorMagnitude(vector3_t vec, float *magOut);
int vectorNormalize(vector3_t vecIn, vector3_t *vecUnitOut, float magnatude);

int validateFloatInput(const char *inputStr, float *validatedFloat);
void displayVector(vector3_t vector);
void splitVectors(char vectorString[], vector3_t *vector);

#endif // ASSIGNMENT_HEADER_H
