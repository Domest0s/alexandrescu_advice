#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <random>
#include <vector>

#include "MapReader.h"
#include "resourcePath.h"

std::vector<uint32_t> generateRandomNumbers(uint32_t numOfElements) noexcept
{
  // Seed with a real random value, if available
  std::random_device rd;
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with
  std::uniform_int_distribution<> distrib(1, 10);
  
  std::vector<uint32_t> result(numOfElements);
  for (int i = 0; i < numOfElements; ++i)
  {
    result[i] = distrib(gen);
  }

  return result;
}


int main(int argc, char* argv[])
{
  std::vector<uint32_t> randNumbers = generateRandomNumbers(10);
  
  for (uint32_t n : randNumbers)
  {
    std::cout << n << ' ';
  }
  std::cout << '\n';
  
  john::Map map = readMap(mission1File);

  return EXIT_SUCCESS;
}