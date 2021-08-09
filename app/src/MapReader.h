#pragma once

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
  Map(size_t dim1, size_t dim2, std::vector<int>&& data)
    : m_dim1(dim1)
    , m_dim2(dim2)
    , m_data(std::move(data))
  {
    assert(m_data.size() == dim1 * dim2);
  }

  int operator()(size_t a, size_t b) const
  {
    assert(a <= m_dim1);
    assert(b <= m_dim2);
    return m_data[b * m_dim2 + a];
  }

private:
  size_t m_dim1;
  size_t m_dim2;
  std::vector<int> m_data;
};
}

john::Map readMap(const std::string& filePath)
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
  size_t mapWidth = 0;
  ifs >> mapWidth;

  assert('x' == ifs.peek());
  ifs.ignore(1, 'x');

  size_t mapHeight = 0;
  ifs >> mapHeight;

  std::vector<int> data;
  data.reserve(mapWidth * mapHeight);
  while (ifs.good() && !ifs.eof())
  {
    constexpr size_t BUF_SIZE = 256;
    assert(BUF_SIZE > mapWidth);
    char buffer[BUF_SIZE] = {0};
    ifs.getline(buffer, BUF_SIZE);
    std::cout << buffer << "\n";
    
    for (size_t i = 0; i < strlen(buffer); i++)
    {
      data.push_back(buffer[i] - '0');
    }
  }

  return john::Map(mapWidth, mapHeight, std::move(data));
}
