#pragma once

#include "Plant.h"
#include "Grammar/LSystemGrammar.h"
#include "Engine/Assets/AssetManager.h"
#include <memory>
#include <vector>

namespace engine {

class PlantFactory {
private:
    std::shared_ptr<ILSystemGrammar> m_grammar; // The L-system used for plant generation
    Mesh m_baseMesh; // The base mesh to be used for all plants
    std::string m_materialID; // The material to be used for all plants
    std::vector<std::shared_ptr<Plant>> m_plants; // Stores all the plants created by the factory


public:
    PlantFactory();
    PlantFactory(std::shared_ptr<ILSystemGrammar> lSystem);
    
    void setMaterial(const std::string& materialId);

    void setGrammar(std::shared_ptr<ILSystemGrammar> lSystemGrammar);

    // Function to create a plant
    std::shared_ptr<Plant> createPlant();
    
    // Function to create multiple plants
    std::vector<std::shared_ptr<Plant>> createPlants(size_t count);
    void ClearPlants();
    void Draw();
};

} // namespace engine

