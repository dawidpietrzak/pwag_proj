#include "PlantFactory.h"

#include <GLM/gtc/matrix_transform.hpp>
#include <stack>


std::vector<PlantSegment> PlantFactory::CreatePlant(const std::string& grammarString)
{
    std::vector<PlantSegment> plantSegments;
    std::stack<glm::mat4> transformStack;
    glm::mat4 currentTransform = glm::mat4(1.0f);
    //currentTransform = glm::scale(currentTransform, glm::vec3(1.0f, 1.0f, 0.4f));

    float segmentLength = 1.0f; // D³ugoœæ segmentu ga³êzi
    float segmentRadius = 1.0f; // Promieñ segmentu ga³êzi

    float angle = 25.0f; // Angle for '+' and '-' rotations
    for (char c : grammarString)
    {
        char upperCaseC = std::toupper(c); // Convert character to upper case
        switch (upperCaseC)
        {
            case 'F': // Create a branch segment
            {
                PlantSegment plantSegment;
                plantSegment.Transform = currentTransform;
                plantSegment.BottomScale = 0.1f;
                plantSegment.TopScale = 0.1f;
                plantSegment.Length = segmentLength;
                plantSegments.push_back(plantSegment);

                currentTransform = glm::translate(currentTransform, glm::vec3(0.0f, segmentLength, 0.0f));
                break;
            }
            case '+': // Rotate
                currentTransform = glm::rotate(currentTransform, glm::radians(angle), glm::vec3(0, 0, 1));
                break;
            case '-': // Rotate in the opposite direction
                currentTransform = glm::rotate(currentTransform, glm::radians(-angle), glm::vec3(0, 0, 1));
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

/*
PlantFactory::PlantFactory()
{

}

PlantFactory::PlantFactory(std::shared_ptr<ILSystemGrammar> lSystemGrammar)
    : m_grammar(lSystemGrammar) {
    // You might want to load the base mesh and material here, or it could be set later.
}

void PlantFactory::setMaterial(const std::string& materialId) {
    m_materialID = materialId;
}

void PlantFactory::setGrammar(std::shared_ptr<ILSystemGrammar> lSystemGrammar) {
    m_grammar = lSystemGrammar;
}

std::shared_ptr<Plant> PlantFactory::createPlant() {
    // Create a new Plant instance using the L-system, base mesh, and material
    std::shared_ptr<Plant> plant = std::make_shared<Plant>(m_grammar.get(), m_baseMesh, m_materialID);
    plant->generateMeshInstances(); // Generate the plant's mesh instances
    m_plants.push_back(plant);
    return plant;
}

std::vector<std::shared_ptr<Plant>> PlantFactory::createPlants(size_t count) {
    std::vector<std::shared_ptr<Plant>> plants;
    plants.reserve(count);
    for (size_t i = 0; i < count; ++i) {
        plants.push_back(createPlant());
        
    }
    return plants;
}

void PlantFactory::ClearPlants() {
    for (const auto& plant : m_plants) {
        plant->clearBranches();
        //plant->~Plant();
    }
    m_plants.clear();
}

void PlantFactory::Draw() {
    for (const auto& plant : m_plants) {
        plant->draw();
    }
}
*/
