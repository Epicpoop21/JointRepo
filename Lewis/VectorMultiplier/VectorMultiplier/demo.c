#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AssignmentHeader.h"
#include <time.h>

// STUDENT CODE START

void demo() {
    char vectorString[50];
    char decisionChar;
    vector3_t vectorOne;
    vector3_t vectorTwo;

    vector3_t *fileVectors = NULL;
    int numOfVectors = 0;

    printf("Input from file (F) or manual input (M): ");
    scanf("%c", &decisionChar);
    getchar();

    if (decisionChar == 77) {
        createVectorFromInput(&vectorOne, vectorString);
        createVectorFromInput(&vectorTwo, vectorString);
    } else if (decisionChar == 70) {
        loadFromFile("vectors.txt", &fileVectors, &numOfVectors);
        printf("%d vectors formed from the inputs.\n \n", numOfVectors);

        for (int i = 0; i < numOfVectors; i++) {
            printf("Vector %d: \n", i + 1);
            displayVector(fileVectors[i]);
            printf("\n");
        }

        int decisionVector;
        printf("Select vector to be vector 1: ");
        scanf("%d", &decisionVector);
        vectorOne = fileVectors[decisionVector - 1];

        printf("Select vector to be vector 2: ");
        scanf("%d", &decisionVector);
        vectorTwo = fileVectors[decisionVector - 1];
    }

    clock_t begin = clock();

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

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("TOOK %f SECONDS", time_spent);

    fgets(vectorString, sizeof(vectorString), stdin);
}

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
    //printf("X is %f, Y is %f, Z is %f, and initialization is %d.\n", vector->x, vector->y, vector->z, vector->status);
}

void loadFromFile(const char fileName[], vector3_t **vectorArray, int *numOfVectors) {
    FILE *fptr;
    fptr = fopen(fileName, "r");
    if (fptr == NULL) {
        printf("Error opening file: %s\n", fileName);
        return;
    }

    int capacity = 10;
    *vectorArray = malloc(capacity * sizeof(vector3_t));
    if (*vectorArray == NULL) {
        printf("Memory allocation failed!\n");
        fclose(fptr);
        return;
    }

    float temp[3];
    *numOfVectors = 0;

    while (fscanf(fptr, "%f" "%f" "%f", &temp[0], &temp[1], &temp[2]) == 3) {
        if (*numOfVectors >= capacity) {
            capacity *= 2;
            *vectorArray = realloc(*vectorArray, capacity * sizeof(vector3_t));
            if (*vectorArray == NULL) {
                printf("Memory reallocation failed!\n");
                fclose(fptr);
                return;
            }
        }
        (*vectorArray)[*numOfVectors].x = temp[0];
        (*vectorArray)[*numOfVectors].y = temp[1];
        (*vectorArray)[*numOfVectors].z = temp[2];
        (*vectorArray)[*numOfVectors].status = 1;

        (*numOfVectors)++;
    }
    fclose(fptr);
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
