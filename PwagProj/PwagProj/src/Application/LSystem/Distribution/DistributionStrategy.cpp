#include "DistributionStrategy.h"


#include <random>
#include <iostream>


GridRandomDistributionStrategy::GridRandomDistributionStrategy(glm::vec2& areaSize, int gridSubdivision): m_areaSize(areaSize), m_gridSubdivision(gridSubdivision)
{
}

void GridRandomDistributionStrategy::RecalculatePositions() {
    m_positions.clear();
    int gridSize = m_gridSubdivision; // Use gridSubdivision for the grid size
    float cellWidth = m_areaSize.x / gridSize;
    float cellHeight = m_areaSize.y / gridSize;

    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0.0, 1.0);

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            // Random position within the cell
            float x = (i + distribution(generator)) * cellWidth;
            float y = 0; // Assuming y is height and remains constant
            float z = (j + distribution(generator)) * cellHeight;

            m_positions.push_back(glm::vec3(x, y, z));
        }
    }
    // Shuffle the positions to ensure randomness
    std::shuffle(m_positions.begin(), m_positions.end(), generator);
}

std::vector<glm::vec3> GridRandomDistributionStrategy::GetPositions(int count) {
    if (m_positions.empty()) {
        std::cout << "Grid positions not calculated. Call RecalculateGridPositions first." << std::endl;
        return {};
    }


    // Return only the requested number of positions
    if (count > m_positions.size())
    {
        std::cerr << "Not enougth grid positions. " << std::endl;
        count = m_positions.size();
    }
    return std::vector<glm::vec3>(m_positions.begin(), m_positions.begin() + count);
}


