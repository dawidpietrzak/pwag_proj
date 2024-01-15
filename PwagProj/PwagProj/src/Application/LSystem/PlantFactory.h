#pragma once

#include <Application/LSystem/Grammar/LSystemGrammar.h>
#include <GLM/glm.hpp>
#include <memory>
#include <vector>
#include <functional>


struct PlantSegment
{
    glm::mat4 Transform = glm::mat4(1.0f);
    float TopScale = 1.0f;
    float BottomScale = 1.0f;
    float Length = 1.0f;
};

class PlantFactory
{
public:
    static std::vector<PlantSegment> CreatePlant(const std::string& grammarString, float growthFactor, float segmentLength, float angle, float bottomScale, float topScale, float time, int maxGenerations);
    static std::vector<PlantSegment> CreatePlant(const std::vector<Symbol>& grammarSentence, float growthFactor, float segmentLength, float angle, float bottomScale, float topScale, float time, float timeForSingleGeneration, int maxGenerations);
};

