#pragma once

#include <cassert>
#include <vector>

namespace john
{

struct Point2i
{
  uint64_t x;
  uint64_t y;

  bool operator==(const Point2i& other) const noexcept
  {
    return x == other.x
        && y == other.y;
  }

  bool operator!=(const Point2i& other) const noexcept
  {
    return !this->operator==(other);
  }
};


class Map
{
public:
  Map(uint64_t height, uint64_t width, std::vector<int>&& data)
    : m_height(height)
    , m_width(width)
    , m_data(std::move(data))
  {
    assert(static_cast<uint64_t>(m_data.size()) == height * width);
  }

  int operator()(uint64_t x, uint64_t y) const noexcept
  {
    assert(x <= m_width);
    assert(y <= m_height);
    return m_data[y * m_width + x];
  }
  
  uint64_t height() const noexcept { return m_height; }
  uint64_t width() const noexcept { return m_width; }

private:
  uint64_t m_height;
  uint64_t m_width;
  std::vector<int> m_data;
};

}
