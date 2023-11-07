// PlantFactory.cpp
#include <Application/LSystem/PlantFactory.h>

namespace engine {

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

} // namespace engine
