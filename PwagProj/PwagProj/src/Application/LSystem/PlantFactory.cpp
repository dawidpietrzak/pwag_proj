#include "PlantFactory.h"

#include <GLM/gtc/matrix_transform.hpp>
#include <stack>
#include <iostream>


std::vector<PlantSegment> PlantFactory::CreatePlant(const std::string& grammarString, float growthFactor, float segmentLength = 1.0f, float angle = 25.0f, float bottomScale = 0.1f, float topScale = 0.08f, float time = 1, int maxGenerations = 1)
{
    std::vector<PlantSegment> plantSegments;
    std::stack<glm::mat4> transformStack;
    glm::mat4 currentTransform = glm::mat4(1.0f);
    //currentTransform = glm::scale(currentTransform, glm::vec3(1.0f, 1.0f, 0.4f));

    float gFactor = growthFactor;
    for (char c : grammarString)
    {
        char upperCaseC = std::toupper(c); // Convert character to upper case
        switch (upperCaseC)
        {
            case 'F': // Create a branch segment
            {
				if (gFactor <= 0.0f) break;

                // B³¹d ale lepiej wizualnie wygl¹da
                bottomScale = gFactor;
                topScale = gFactor;
                segmentLength = gFactor;

                PlantSegment plantSegment;
                plantSegment.Transform = currentTransform;
                plantSegment.BottomScale = bottomScale;
                plantSegment.TopScale = topScale;
                plantSegment.Length = segmentLength;
                plantSegments.push_back(plantSegment);

                currentTransform = glm::translate(currentTransform, glm::vec3(0.0f, segmentLength, 0.0f));
                break;
            }
            case '+': // Rotate
                currentTransform = glm::rotate(currentTransform, glm::radians(angle), glm::vec3(0, 1, 0));
                break;
            case '-': // Rotate in the opposite direction
                currentTransform = glm::rotate(currentTransform, glm::radians(-angle), glm::vec3(0, 1, 0));
                break;
            case '[': // Save the current state
                transformStack.push(currentTransform);
                break;
            case ']': // Restore the saved state
                currentTransform = transformStack.top();
                transformStack.pop();
                break;
            case '&': // Pitch down (rotate around the X-axis in a positive direction)
                currentTransform = glm::rotate(currentTransform, glm::radians(angle), glm::vec3(1, 0, 0));
                break;
            case '^': // Pitch up (rotate around the X-axis in a negative direction)
                currentTransform = glm::rotate(currentTransform, glm::radians(-angle), glm::vec3(1, 0, 0));
                break;
            case '<': // Roll left (rotate around the Z-axis in a positive direction)
                currentTransform = glm::rotate(currentTransform, glm::radians(angle), glm::vec3(0, 0, 1));
                break;
            case '>': // Roll right (rotate around the Z-axis in a negative direction)
                currentTransform = glm::rotate(currentTransform, glm::radians(-angle), glm::vec3(0, 0, 1));
                break;
            case '|': // Turn around (rotate 180 degrees around the Y-axis)
                currentTransform = glm::rotate(currentTransform, glm::radians(180.0f), glm::vec3(0, 1, 0));
                break;

        }
    }
    return plantSegments;
}


std::vector<PlantSegment> PlantFactory::CreatePlant(const std::vector<Symbol>& grammarSentence, float growthFactor, float segmentLengthD = 1.0f, float angle = 25.0f, float bottomScaleD = 0.1f, float topScaleD = 0.08f, float time = 1, float timeForSingleGeneration = 100, int maxGenerations = 2)
{
    std::vector<PlantSegment> plantSegments;
    std::stack<glm::mat4> transformStack;
    glm::mat4 currentTransform = glm::mat4(1.0f);
    //currentTransform = glm::scale(currentTransform, glm::vec3(1.0f, 1.0f, 0.4f));

    float gFactor = growthFactor;
    for (const Symbol& s : grammarSentence)
    {

        switch (s.symbol)
        {
        case 'F': // Create a branch segment
        {

            float generationProgress = 1.0f - time/ (timeForSingleGeneration* maxGenerations);

            int segmentGeneration = (maxGenerations) + s.age;

            float ageFactor = (segmentGeneration+1) / (float)(maxGenerations);

            float combindedFactor = std::min(gFactor * (ageFactor-generationProgress), 1.0f);

            if (combindedFactor <= 0.0f) break;
           
            float bottomScale = combindedFactor*bottomScaleD;
            float topScale = combindedFactor*topScaleD;
            float segmentLength = combindedFactor* segmentLengthD;

            PlantSegment plantSegment;
            plantSegment.Transform = currentTransform;
            plantSegment.BottomScale = bottomScale;
            plantSegment.TopScale = topScale;
            plantSegment.Length = segmentLength;
            plantSegments.push_back(plantSegment);

            currentTransform = glm::translate(currentTransform, glm::vec3(0.0f, segmentLength*1.9, 0.0f));
            break;
        }
        case '+': // Rotate
            currentTransform = glm::rotate(currentTransform, glm::radians(angle), glm::vec3(0, 1, 0));
            break;
        case '-': // Rotate in the opposite direction
            currentTransform = glm::rotate(currentTransform, glm::radians(-angle), glm::vec3(0, 1, 0));
            break;
        case '[': // Save the current state
            transformStack.push(currentTransform);
            break;
        case ']': // Restore the saved state
            currentTransform = transformStack.top();
            transformStack.pop();
            break;
        case '&': // Pitch down (rotate around the X-axis in a positive direction)
            currentTransform = glm::rotate(currentTransform, glm::radians(angle), glm::vec3(1, 0, 0));
            break;
        case '^': // Pitch up (rotate around the X-axis in a negative direction)
            currentTransform = glm::rotate(currentTransform, glm::radians(-angle), glm::vec3(1, 0, 0));
            break;
        case '<': // Roll left (rotate around the Z-axis in a positive direction)
            currentTransform = glm::rotate(currentTransform, glm::radians(angle), glm::vec3(0, 0, 1));
            break;
        case '>': // Roll right (rotate around the Z-axis in a negative direction)
            currentTransform = glm::rotate(currentTransform, glm::radians(-angle), glm::vec3(0, 0, 1));
            break;
        case '|': // Turn around (rotate 180 degrees around the Y-axis)
            currentTransform = glm::rotate(currentTransform, glm::radians(180.0f), glm::vec3(0, 1, 0));
            break;

        }
    }
    return plantSegments;
}