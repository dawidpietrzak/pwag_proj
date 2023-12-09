#include "PlantFactory.h"

#include <GLM/gtc/matrix_transform.hpp>
#include <stack>


std::vector<PlantSegment> PlantFactory::CreatePlant(const std::string& grammarString, float segmentLength = 1.0f, float angle = 25.0f, float bottomScale = 0.1f, float topScale = 0.1f)
{
    std::vector<PlantSegment> plantSegments;
    std::stack<glm::mat4> transformStack;
    glm::mat4 currentTransform = glm::mat4(1.0f);
    //currentTransform = glm::scale(currentTransform, glm::vec3(1.0f, 1.0f, 0.4f));

    for (char c : grammarString)
    {
        char upperCaseC = std::toupper(c); // Convert character to upper case
        switch (upperCaseC)
        {
            case 'F': // Create a branch segment
            {
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