#include "Tower.h"
#include <random>

Tower::Tower(RenderLayout&& upperTower, RenderLayout&& lowerTower)
    : upperTower(std::move(upperTower)), lowerTower(std::move(lowerTower))
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 800);
    std::uniform_int_distribution<std::mt19937::result_type> dist5(1, 2);
    yOffset = dist6(rng);
    int nChance = dist5(rng);
    yOffset = yOffset / 2;

    if (nChance == 2) {
        yOffset = -yOffset;
    }

    std::cout << "\n \nNEW TOWER\n";
    topTowerBottomCoord = upperTower.centre.y - 960.0f/2 + yOffset;
    std::cout << "Top tower's bottom coord is: " << topTowerBottomCoord << "\n";
    bottomTowerTopCoord = lowerTower.centre.y + 960.0f/2 + yOffset;
    std::cout << "Bottom tower's top coord is: " << bottomTowerTopCoord << "\n";


    this->upperTower.modelMatrix = glm::translate(upperTower.modelMatrix, glm::vec3(upperTower.centre.x, upperTower.centre.y + yOffset, 0.0f));
    this->lowerTower.modelMatrix = glm::translate(lowerTower.modelMatrix, glm::vec3(upperTower.centre.x, yOffset, 0.0f));
    //std::cout << yOffset << "\n";
}

Tower::~Tower()
{
    std::cout << "Deleted tower \n";
}
