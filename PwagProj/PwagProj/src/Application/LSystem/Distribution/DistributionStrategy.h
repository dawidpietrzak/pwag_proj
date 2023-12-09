#pragma once

#include <vector>
#include <glm/glm.hpp>

// Strategy Interface
class IDistributionStrategy {
public:
    virtual std::vector<glm::vec3> GetPositions(int count) = 0;
    virtual void RecalculatePositions() = 0;
private:
};

// Concrete Strategy: Grid-based Random Distribution
class GridRandomDistributionStrategy : public IDistributionStrategy {
public:
    GridRandomDistributionStrategy(glm::vec2& areaSize, int gridSubdivision);
    void RecalculatePositions() override;
    std::vector<glm::vec3> GetPositions(int count) override;

private:
    glm::vec2& m_areaSize;
    int m_gridSubdivision;
    std::vector<glm::vec3> m_positions;
};