#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AssignmentHeader.h"

// STUDENT CODE START

void demo() {
    char vectorString[50];
    char decisionChar;
    vector3_t vectorOne;
    vector3_t vectorTwo;
    vector3_t vectorArray[33];

    printf("Input from file (F) or manual input (M): ");
    scanf("%c", &decisionChar);
    getchar();

    if (decisionChar == 77) {
        createVectorFromInput(&vectorOne, vectorString);
        createVectorFromInput(&vectorTwo, vectorString);
    } else if (decisionChar == 70) {
        loadFromFile("vectors.txt", &vectorArray);
    }

    float dotProduct = 0;
    vectorDotProduct(vectorOne, vectorTwo, &dotProduct);
    printf("\nDot product of vector 1 is %f\n\n", dotProduct);

    vector3_t crossProductVector;
    vectorCrossProduct(vectorOne, vectorTwo, &crossProductVector);
    printf("Cross product of vector 1 with vector 2 is: \n");
    displayVector(crossProductVector);

    float magProduct = 0;
    vectorMagnitude(vectorOne, &magProduct);
    printf("\nMagnitude of vector 1 is %f\n\n", magProduct);

    vector3_t normalisedVector;
    vectorNormalize(vectorOne, &normalisedVector, magProduct);
    printf("Vector 1 normalised: \n");
    displayVector(normalisedVector);

    //fgets(vectorString, sizeof(vectorString), stdin);
}

//vector loadNumsFromFile(const char fileName[])

void splitVectors(char vectorString[], vector3_t *vector) {
    int position = 0;

    char * splitPointer = strtok(vectorString, " ");
    while(splitPointer != NULL) {
        if (position == 0) {
            vector->x = (float) atof(splitPointer);
        } else if (position == 1) {
            vector->y = (float) atof(splitPointer);
        } else if (position == 2) {
            vector->z = (float) atof(splitPointer);
        }
        splitPointer = strtok(NULL, " ");
        position = position + 1;
    }
    vector->status = 1;
    //printf("X is %f, Y is %f, Z is %f, and initialization is %d.\n", vector->x, vector->y, vector->z, vector->status);
}

void loadFromFile(const char fileName[], vector3_t *vectorArray[]) {
    FILE *fptr;
    fptr = fopen(fileName, "r");
    int iteration = 0;
    float inputNums[100];

    char number[25];
    while (fgets(number, 25, fptr)) {
        inputNums[iteration] = atof(number);
        iteration++;
    }

    for (int i = 0; (int) iteration > i; i = i + 3) {
        vector3_t vector;
        vector.x = inputNums[i];
        vector.y = inputNums[i + 1];
        vector.z = inputNums[i + 2];
        vector.status = 1;

        //*vectorArray[i] = vector;
        displayVector(vector);
        printf("\n");
    }
}

void createVectorFromInput(vector3_t *vector, char vectorString[]) {
    printf("Enter a vector (with decimals): ");
    fgets(vectorString, sizeof(vectorString), stdin);
    splitVectors(vectorString, vector);
    displayVector(*vector);
}

void displayVector(vector3_t vector) {
    printf("X: %.2f\n", vector.x);
    printf("Y: %.2f\n", vector.y);
    printf("Z: %.2f\n", vector.z);
}
// STUDENT CODE END
