#include "AssignmentHeader.h"
#include <math.h>

// STUDENT CODE START

int vectorDotProduct(vector3_t vecA, vector3_t vecB, float *result) {
    *result = (vecA.x * vecB.x) + (vecA.y * vecB.y) + (vecA.z * vecB.z);
    return 1;
}

int vectorCrossProduct(vector3_t vecA, vector3_t vecB, vector3_t *vecOut) {
    vecOut->x = (vecA.y * vecB.z) - (vecA.z * vecB.y);
    vecOut->y = (vecA.z * vecB.x) - (vecA.x * vecB.z);
    vecOut->z = (vecA.x * vecB.y) - (vecA.y * vecB.x);
    return 1;
}

int vectorMagnitude(vector3_t vec, float *magOut) {
    float bigNumber = (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z);
    *magOut = sqrt((double)bigNumber);
    return 1;
}

int vectorNormalize(vector3_t vecIn, vector3_t *vecUnitOut, float magnatude) {
    if (magnatude == 0) {
        return -1;
    }
    vecUnitOut->x = vecIn.x / magnatude;
    vecUnitOut->y = vecIn.y / magnatude;
    vecUnitOut->z = vecIn.z / magnatude;
    return 1;
}


// STUDENT CODE END
