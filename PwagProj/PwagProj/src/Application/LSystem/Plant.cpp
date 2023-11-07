// Plant.cpp
#include "Plant.h"
#include <stack>
#include <iostream>
#include <Application/Tools/CylinderGenerator.h>
#include <cctype>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace engine {
    Plant::Plant(ILSystemGrammar* lSystemGrammar, const Mesh& mesh, std::string& materialID)
        : m_lSystem(lSystemGrammar), m_baseMesh(mesh), m_materialID(materialID), m_cylinderGen(){
    
        m_cylinderGen.LoadBaseMeshData("assets/cylinderTransformBottom.obj");

        auto app = Application::Get();
        m_assetManager = app->GetAssetManager();
    }

    Plant::~Plant() {
    }

    void Plant::generateMeshInstances() {

        std::string lSystemString = m_lSystem->getCurrentString();
        std::cout << lSystemString << std::endl;
        std::stack<glm::mat4> transformStack;
        glm::mat4 currentTransform = glm::mat4(1.0f);

        float segmentLength = 1.0f; // D³ugoœæ segmentu ga³êzi
        float segmentRadius = 0.1f; // Promieñ segmentu ga³êzi
        
        float angle = 25.0f; // Angle for '+' and '-' rotations
        std::cout << "Test" << std::endl;
        for (char c : lSystemString) {
            char upperCaseC = std::toupper(c); // Convert character to upper case
            switch (upperCaseC) {
            case 'F': // Draw a branch segment

                createBranch(segmentLength, segmentRadius, currentTransform);
                // Przesuñ "turtle" do przodu
                currentTransform = glm::translate(currentTransform, glm::vec3(0.0f, segmentLength, 0.0f));
                break;
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
                // This can be used for bending a branch downward.
                currentTransform = glm::rotate(currentTransform, glm::radians(angle), glm::vec3(1, 0, 0));
                break;
            case '^': // Pitch up (rotate around the X-axis in a negative direction)
                // This would bend a branch upward.
                currentTransform = glm::rotate(currentTransform, glm::radians(-angle), glm::vec3(1, 0, 0));
                break;
            case '<': // Roll left (rotate around the Z-axis in a positive direction)
                // This might be used to twist a branch to the left.
                currentTransform = glm::rotate(currentTransform, glm::radians(angle), glm::vec3(0, 0, 1));
                break;
            case '>': // Roll right (rotate around the Z-axis in a negative direction)
                // This would twist a branch to the right.
                currentTransform = glm::rotate(currentTransform, glm::radians(-angle), glm::vec3(0, 0, 1));
                break;
            case '|': // Turn around (rotate 180 degrees around the Y-axis)
                // This is useful for flipping the direction of growth, like turning a branch to grow in the opposite direction.
                currentTransform = glm::rotate(currentTransform, glm::radians(180.0f), glm::vec3(0, 1, 0));
                break;
            }
        }
    }

    void Plant::createBranch(float segmentLength, float segmentRadius, glm::mat4 currentTransform) {      
        auto cylinderMesh = m_cylinderGen.CreateMesh(segmentRadius, segmentRadius, segmentLength);
        auto m_cylinder = std::make_shared<engine::Entity>(cylinderMesh, m_assetManager->GetMaterial(m_materialID));
        m_branches.push_back(m_cylinder);
        m_cylinder->SetTransformMatrix(currentTransform);        
    }

    void Plant::clearBranches() {
        for (const auto& branch : m_branches) {
            branch->DestroyMesh();
        }

        m_branches.clear();
        std::cout << "All branches cleared.\n";
    }

    void Plant::draw() {
        for (const auto& branch : m_branches) {
            Renderer::Draw(branch);
        }
    }

}