/*
 * prjsv 2016
 * 2016
 * Marco Antognini
 */

#include <Application.hpp>
#include <Utility/Vertex.hpp>
#include <vector>

#include <algorithm>
#include <numeric>
#include <cmath>

std::vector<sf::Vertex> generateVertexes(j::Value const& textures, int nbCell, float cellSize)
{
    auto vertexes = std::vector<sf::Vertex>(nbCell * nbCell * 4); // RVO

    // Load the textures
    auto const& ecmTexture = getAppTexture(textures["ecm"].toString());
    auto const& bloodTexture  = getAppTexture(textures["blood"].toString());
    auto const& liverTexture = getAppTexture(textures["liver"].toString());
	auto const& liverCancerTexture = getAppTexture(textures["cancer"].toString());
	auto const& concentrationTexture = getAppTexture(textures["concentration"].toString());

    // Determine which is the smallest dimension
    auto texWidth  = std::min({ ecmTexture.getSize().x, bloodTexture.getSize().x, liverTexture.getSize().x ,  liverCancerTexture.getSize().x ,concentrationTexture.getSize().x });
    auto texHeight = std::min({ ecmTexture.getSize().y, bloodTexture.getSize().y, liverTexture.getSize().y, liverCancerTexture.getSize().y, concentrationTexture.getSize().y });

    // Generate the vertexes (caches)
    for (int x = 0; x < nbCell; ++x) {
        for (int y = 0; y < nbCell; ++y) {
            auto pos = std::vector<sf::Vector2f>{
                { (x+0.f) * cellSize, (y+0.f) * cellSize },
                { (x+1.f) * cellSize, (y+0.f) * cellSize },
                { (x+1.f) * cellSize, (y+1.f) * cellSize },
                { (x+0.f) * cellSize, (y+1.f) * cellSize }
            };

            // Wrap texture around
            auto size  = static_cast<int>(std::ceil(cellSize));
            auto color = sf::Color::White; // White means not texture recoloring
            auto tex   = std::vector<sf::Vector2f>{
                { static_cast<float>((x+0) * size % texWidth), static_cast<float>((y+0) * size % texHeight) },
                { static_cast<float>((x+1) * size % texWidth), static_cast<float>((y+0) * size % texHeight) },
                { static_cast<float>((x+1) * size % texWidth), static_cast<float>((y+1) * size % texHeight) },
                { static_cast<float>((x+0) * size % texWidth), static_cast<float>((y+1) * size % texHeight) }
            };

            // Update NW, NE, SE, SW vertexes for the current cell
            auto idx = startIndexForCellVertexes(x, y, nbCell);
            for (auto offset : { 0, 1, 2, 3 }) {
                vertexes[idx + offset] = { pos[offset], color, tex[offset] };
            }
        }
    }

    return vertexes;
}

std::size_t startIndexForCellVertexes(int x, int y, int nbCell)
{
    return 4 * (x + y * nbCell);
}

std::vector<std::size_t> indexesForCellVertexes(int x, int y, int nbCell)
{
    std::vector<std::size_t> indexes(4); // RVO
    std::iota(std::begin(indexes), std::end(indexes), startIndexForCellVertexes(x, y, nbCell));
    return indexes;
}
