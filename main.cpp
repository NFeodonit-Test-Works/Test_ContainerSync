/*****************************************************************************
 * Project:  Test_ContainerSync
 * Purpose:  Test project
 * Author:   NikitaFeodonit, nfeodonit@yandex.com
 *****************************************************************************
 *   Copyright (c) 2017-2018 NikitaFeodonit
 *
 *    This file is part of the Test_ContainerSync project.
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published
 *    by the Free Software Foundation, either version 3 of the License,
 *    or (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *    See the GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program. If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <random>
#include <utility>
#include <vector>

void printVector(const std::vector<int>& v)
{
  std::cout << "testVector: ";
  for(auto iv : v) {
    std::cout << iv << " ";
  }
  std::cout << "\n";
}

void printMap(const std::map<int, int>& m)
{
  auto printMap = [](const std::pair<int, int>& element) {
    std::cout << "[" << element.first << "]==" << element.second << " ";
  };
  std::cout << "testMap: ";
  std::for_each(m.begin(), m.end(), printMap);
  std::cout << "\n";
}

int main()
{
  constexpr int min = 1;
  constexpr int max = 9;
  constexpr int size = 20;
  constexpr int deleteMax = 15;

  std::vector<int> testVector(size);
  std::map<int, int> testMap;

  // Random generator functions.
  // https://stackoverflow.com/a/19728404
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> initRnd(min, max);
  std::uniform_int_distribution<int> deleteRnd(0, deleteMax);
  auto randomIntFunc = [&rng, &initRnd]() -> int { return initRnd(rng); };
  auto randomPairFunc = [&rng, &initRnd, &testMap]() -> std::pair<int, int> {
    return std::make_pair(testMap.size(), initRnd(rng));
  };

  // Fill the containers with a random values.
  std::generate(testVector.begin(), testVector.end(), randomIntFunc);
  std::generate_n(
      std::inserter(testMap, testMap.begin()), size, randomPairFunc);

  std::cout << "Initial state, size:" << size << "\n";
  printVector(testVector);
  printMap(testMap);

  // Remove a random count of elements from the containers.
  int newSize = testVector.size() - deleteRnd(rng);
  if(newSize < 0) {
    newSize = 0;
  }

  // From vector
  testVector.resize(newSize);

  // From map.
  auto im = testMap.rbegin();
  while(im != testMap.rend()) {
    if(newSize < testMap.size()) {
      std::advance(im, 1);
      testMap.erase(im.base());
    } else {
      break;
    }
  }

  std::cout << "\nNew size:" << newSize << "\n";
  printVector(testVector);
  printMap(testMap);

  return 0;
}
