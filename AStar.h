//
// Created by alessio on 01/09/22.
//

#ifndef PLATFORMGAME_ASTAR_H
#define PLATFORMGAME_ASTAR_H

#include <vector>
#include <functional>
#include <set>
#include <algorithm>
#include <cmath>
#include "SFML/Graphics.hpp"

namespace AStar
{
    struct Vec2i
    {
        int x, y;

        bool operator == (const Vec2i& coordinates) const;
    };

    using HeuristicFunction = std::function<unsigned int(Vec2i, Vec2i)>;
    using CoordinateList = std::vector<Vec2i>;

    struct Node
    {
        unsigned int G, H;
        Vec2i coordinates{};
        Node *parent;

        explicit Node(Vec2i coord, Node *parent = nullptr);
        unsigned int getScore() const;
    };

    using NodeSet = std::vector<Node*>;

    class Generator
    {
        bool detectCollision(Vec2i coordinates);
        static Node* findNodeOnList(NodeSet& nodeSet, Vec2i coordinates);
        static void releaseNodes(NodeSet& nodeSet);

    public:
        Generator();
        void setWorldSize(sf::Vector2f size);
        void setDiagonalMovement(bool enable);
        void setHeuristic(const HeuristicFunction &heur);
        CoordinateList findPath(Vec2i source, Vec2i target);
        void addCollision(Vec2i coordinates, sf::Vector2f size);
        void addNode(Vec2i coordinates, sf::Vector2f size);
        void removeCollision(Vec2i coordinates);
        void clearCollisions();
        void render(sf::RenderTarget *target);
        void findSourceTarget(bool isFound);

    private:
        HeuristicFunction heuristic;
        CoordinateList direction, walls;
        std::vector<sf::RectangleShape> collisionTiles;
        std::vector<sf::RectangleShape> nodes;
        sf::Vector2f worldSize;
        unsigned int directions;
        bool found;
    };

    class Heuristic
    {
        static Vec2i getDelta(Vec2i source, Vec2i target);

    public:
        static unsigned int manhattan(Vec2i source, Vec2i target);
        static unsigned int euclidean(Vec2i source, Vec2i target);
        static unsigned int octagonal(Vec2i source, Vec2i target);
    };
}


#endif //PLATFORMGAME_ASTAR_H
