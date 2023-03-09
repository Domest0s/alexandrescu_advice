#pragma once

#include <cstring>
#include <array>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>

namespace john
{

struct Point2i
{
  int x;
  int y;
};


class Map
{
public:
  Map(size_t height, size_t width, std::vector<int>&& data)
    : m_height(height)
    , m_width(width)
    , m_data(std::move(data))
  {
    assert(m_data.size() == height * width);
  }

  int operator()(size_t x, size_t y) const noexcept
  {
    assert(x <= m_width);
    assert(y <= m_height);
    return m_data[y * m_width + x];
  }

  size_t height() const noexcept { return m_height; }
  size_t width() const noexcept { return m_width; }

private:
  size_t m_height;
  size_t m_width;
  std::vector<int> m_data;
};


struct MapStartEnd
{
  john::Map map;
  john::Point2i start;
  john::Point2i finish;
};

MapStartEnd readMap(const std::string& filePath)
{
  std::ifstream ifs(filePath, std::ios_base::in);

  //std::string fileContent(
  //  (std::istreambuf_iterator<char>(ifs)),
  //  (std::istreambuf_iterator<char>()));

  //std::cout << fileContent << "\n";
  //ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip bad input

  // read start and finish points
  john::Point2i start;
  ifs >> start.x;
  ifs >> start.y;

  john::Point2i finish;
  ifs >> finish.x;
  ifs >> finish.y;

  //assert('\n' == ifs.peek());
  //ifs.ignore(1, '\n');

  // read map size, format %ix%i
  size_t mapHeight = 0;
  ifs >> mapHeight;

  assert('x' == ifs.peek());
  ifs.ignore(1, 'x');

  size_t mapWidth = 0;
  ifs >> mapWidth;

  ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // finish this line

  std::vector<int> data;
  data.reserve(mapWidth * mapHeight);
  for (size_t i = 0; i < mapHeight; i++)
  {
    assert(ifs.good() && !ifs.eof());
    constexpr size_t BUF_SIZE = 256;
    assert(BUF_SIZE > mapWidth);
    char buffer[BUF_SIZE] = {0};

    ifs.getline(buffer, BUF_SIZE);
    //std::cout << buffer << "\n";
    assert(std::strlen(buffer) == mapWidth);

    for (size_t ci = 0; ci < std::strlen(buffer); ci++)
    {
      data.push_back(buffer[ci] - '0');
    }
  }

  return { john::Map(mapHeight, mapWidth, std::move(data)), start, finish};
}

} // namespace john
