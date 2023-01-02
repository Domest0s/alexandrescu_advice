#pragma once

#include <vector>

#include "Map.h"

namespace john {

/**
* checks if the cell is a road cell
 */
bool isRoad(const Point2i& p, const Map& map)
{
  // check the map borders and cell type
  return p.x >= 0
    && p.y >= 0
    && p.x < map.width()
    && p.y < map.height()
    && map(p.x,p.y) == 0;
}


/**
 *  returns list of adjacent road cells where the path can be extended
 */
std::vector<Point2i> getFreeRoadCellsAround(const Map& map, Point2i current, const std::vector<Point2i>& path)
{
  // every cell has 4 adjacent cells (nodes)
  std::vector<Point2i> nextCells =
  {
    { current.x, current.y - 1 }, // v - down
    { current.x, current.y + 1 }, // ^ - up
    { current.x - 1, current.y }, // < - left
    { current.x + 1, current.y }  // > - right
  };

  // remove cells that are not road or cells already added to the path
  nextCells.erase(std::remove_if(nextCells.begin(), nextCells.end(),
    [&map, &path](const Point2i& p)
    {
      return !isRoad(p, map) || std::find(path.begin(), path.end(), p) != path.end();
    }), nextCells.end());

  return nextCells;
}


/**
 * @desc finds shortest path on 2d map
 * @return vector of points from start to finish.
*/
std::vector<john::Point2i> findPath(const Map& map, Point2i start, Point2i finish)
{
  // the distance to the closest cells is constant.
  // The first search head that reached the finish point means the shortest path.
  // Effectively we perform blind Depth-First Search
  typedef std::vector<Point2i> Path;
  for (std::vector<Path> nextRoundPath, thisRoundPath = { {start} };
      !thisRoundPath.empty();
      thisRoundPath = nextRoundPath)  // bring alive paths to the next round
  {
    for (const auto& currentPath : thisRoundPath)
    {
      std::vector<Point2i> nextCells = getFreeRoadCellsAround(map, currentPath.back(), currentPath);

      for (Point2i p : nextCells)
      {
        // alive paths - the ones that being extended on new search iteration.
        // alive paths proceeed to the next iteration.
        // Dead-ended paths are implicitly dropped from the loop.
        std::vector<Point2i> alivePath = currentPath;
        alivePath.push_back(p);
        nextRoundPath.push_back(alivePath);
      }
    }

    for (const std::vector<Point2i>& path : nextRoundPath)
    {
      if (path.back() == finish)
      {
        // the finish was reached
        return path;
      }
    }
  }

  // path to the finish does not exists
  return {};
}


std::vector<std::vector<Point2i>> nextStepFindPath(const john::Map& map,
  const std::vector<std::vector<john::Point2i>>& lastStepPaths)
{
  // the distance to the closest cells is constant.
  // The first search head that reached the finish point means the shortest path.
  // Effectively we perform blind Depth-First Search
  typedef std::vector<john::Point2i> Path;
  std::vector<Path> nextRoundPath;
  std::vector<Path> thisRoundPath = lastStepPaths;

    for (const auto& currentPath : thisRoundPath)
    {
      std::vector<Point2i> nextCells = john::getFreeRoadCellsAround(map, currentPath.back(), currentPath);

      for (Point2i p : nextCells)
      {
        // alive paths - the ones that being extended on new search iteration.
        // alive paths proceeed to the next iteration.
        // Dead-ended paths are implicitly dropped from the loop.
        std::vector<Point2i> alivePath = currentPath;
        alivePath.push_back(p);
        nextRoundPath.push_back(alivePath);
      }
    }

  // path to the finish does not exists
  return nextRoundPath;
}


} // namespace john