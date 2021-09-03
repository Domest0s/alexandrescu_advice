#include <cassert>
#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <random>
#include <vector>
#include <sstream>

#include "MapReader.h"
#include "resourcePath.h"
#include "vt100.h"

std::vector<uint32_t> generateRandomNumbers(uint32_t numOfElements) noexcept
{
  // Seed with a real random value, if available
  std::random_device rd;
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with
  std::uniform_int_distribution<> distrib(1, 10);
  
  std::vector<uint32_t> result(numOfElements);
  for (uint32_t i = 0; i < numOfElements; ++i)
  {
    result[i] = distrib(gen);
  }

  return result;
}

std::string getMapAsString(const john::Map& map)
{
  std::stringstream result;
  for (size_t y = 0; y < map.height(); y++)
  {
    for (size_t x = 0; x < map.width(); x++)
    {
      result << map(x, y);
    }
    result << "\n";
  }
  return result.str();
}

void renderPoint(john::Point2i point,
    const john::Map& map,
    char letter,
    vt100::Color color)
{
  // cursor is located beyond the map
  // first move it on the map
  printf(MOVE_UP(1));

  assert(point.x < map.width());
  assert(point.y < map.height());
  // move to the location
  // MOVE_UP();
  printf("%s%s%s%c",
    vt100::color(color),
    vt100::move_up(point.y).c_str(),
    vt100::move_forward(point.x).c_str(),
    letter);
  
  // move back to where we started
  printf("%s\r", vt100::move_down(point.y + 1).c_str());
  printf(COL_RESET);
}

void renderMap(const john::Map& map, john::Point2i start, john::Point2i end)
{
  // print map
  std::cout << getMapAsString(map);
  // after map is printed we end up at start of the line next to the map

  // print path

  // print start & finish
  renderPoint(start, map, 'S', vt100::Color::Blue);
  renderPoint(end, map, 'E', vt100::Color::Red);
}

int main(int /*argc*/, char* /*argv*/[])
{
  //std::vector<uint32_t> randNumbers = generateRandomNumbers(10);
    
  john::MapStartEnd task = john::readMap(mission1File);
  john::Map map = task.map;
  john::Point2i start = task.start;
  john::Point2i finish = task.finish;
  renderMap(map, start, finish);

  //printf(COL_BLUE "some text\n" COL_RESET);
  //printf(COL_CYAN "some text\n" COL_RESET);
  //printf(MOVE_UP(2) CLEAR_LINE "KURVA\n");

  return EXIT_SUCCESS;
}