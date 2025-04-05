#include "projectHeader.h"

void cosineWave(int cosineMultiplier, xyCoords coords[])
{
    float angle = 0;
    int i;
    float point = 0;
    int maximum = 0;

    for (i = 0; i < 361; i++)
    {
        point = cosineMultiplier * cos(angle);

        /*if (point > maximum)
        {
            pMaxMinArray->max = point;
            pMaxMinArray->min = pMaxMinArray->max * -1;
        } */

        coords[i].x = i;
        coords[i].y = point;

        angle += 3.14159 / 180;
        /*
        std::cout << "Coords 1 x = " + std::to_string(coords[i].x) + "\n";
        std::cout << "Coords 1 y = " + std::to_string(coords[i].y) + "\n" + "\n";
        */
    }
}