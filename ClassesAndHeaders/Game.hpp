#pragma once
#include <iostream>
#include <cstdlib>
#include <random>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN "cls"
#else
#include <unistd.h>
#define CLEAR_SCREEN "clear"
#endif

const int MAX_OBJECTS = 100;

struct FallingObject {
    int x;
    int y;
    float value;
    bool active;
};

class Game {
public:
    static float startBeerGame(int maxObjects, float pijanstwo) {
        const int width = 6;
        const int height = 10;

        int playerPos = width / 2;
        int caught = 0;
        int dropped = 0;
        int spawned = 0;

        int lastSpawnX = width / 2;
        FallingObject objects[MAX_OBJECTS];

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dice(1, 12);
        std::uniform_int_distribution<int> moveDist(0, 2);
        std::uniform_real_distribution<float> probDist(0.0f, 1.0f);

        float spawnChanceFactor = 1.0f + pijanstwo * 2.0f;

        for (int i = 0; i < MAX_OBJECTS; ++i) {
            objects[i].active = false;
        }

        while (caught + dropped < maxObjects) {
            if (spawned < maxObjects) {
                std::uniform_real_distribution<float> spawnChance(0, 1);
                if (spawnChance(gen) < spawnChanceFactor) {
                    int minX = std::max(0, lastSpawnX - 1);
                    int maxX = std::min(width - 1, lastSpawnX + 1);
                    std::uniform_int_distribution<int> limitedPosDist(minX, maxX);
                    int spawnX = limitedPosDist(gen);

                    objects[spawned].x = spawnX;
                    objects[spawned].y = 0;
                    objects[spawned].value = dice(gen);
                    objects[spawned].active = true;
                    lastSpawnX = spawnX;
                    ++spawned;
                }
            }

            std::system(CLEAR_SCREEN);

            for (int r = 0; r < height; ++r) {
                for (int c = 0; c < width; ++c) {
                    bool printed = false;
                    for (int i = 0; i < maxObjects; ++i) {
                        if (objects[i].active && objects[i].x == c && objects[i].y == r) {
                            std::cout << " * ";
                            printed = true;
                            break;
                        }
                    }
                    if (!printed) {
                        if (r == height - 1 && c == playerPos)
                            std::cout << "[O]";
                        else
                            std::cout << " . ";
                    }
                }
                std::cout << "\n";
            }

            std::cout << "\nCaught: " << caught << " | Slipped in fingers: " << dropped
                      << " | Remaining: " << (maxObjects - caught - dropped) << "\n";

            // Smarter AI movement based on pijanstwo
            FallingObject* target = nullptr;
            int minDistance = height;
            for (int i = 0; i < maxObjects; ++i) {
                if (!objects[i].active)
                    continue;
                int distance = (height - 1) - objects[i].y;
                if (distance < minDistance) {
                    minDistance = distance;
                    target = &objects[i];
                }
            }

            float decision = probDist(gen);
            if (target && decision < (1.0f - pijanstwo)) {
                // Move toward target if sober enough
                if (target->x < playerPos)
                    playerPos = std::max(0, playerPos - 1);
                else if (target->x > playerPos)
                    playerPos = std::min(width - 1, playerPos + 1);
            } else {
                // Otherwise, move randomly
                int randomMove = moveDist(gen);
                if (randomMove == 0)
                    playerPos = std::max(0, playerPos - 1);
                else if (randomMove == 1)
                    playerPos = std::min(width - 1, playerPos + 1);
            }

            for (int i = 0; i < maxObjects; ++i) {
                if (!objects[i].active) continue;

                if (objects[i].y == height - 2 && objects[i].x == playerPos) {
                    ++caught;
                    objects[i].active = false;
                } else if (objects[i].y == height - 2) {
                    ++dropped;
                    objects[i].active = false;
                } else {
                    objects[i].y += 1;
                }
            }

#ifdef _WIN32
            Sleep(200);
#else
            usleep(200000);
#endif
        }

        std::system(CLEAR_SCREEN);
        std::cout << "End of the game!\n";
        std::cout << "Caught " << caught << " beers out of " << maxObjects << " ("
                  << ((100.0f * caught) / maxObjects) << "% efficiency).\n";
        return (100.0f * caught) / maxObjects;
    }
};
