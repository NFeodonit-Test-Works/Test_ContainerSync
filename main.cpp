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
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <random>
#include <utility>
#include <vector>

int main()
{
  namespace ph = std::placeholders;

  using keyType = int;
  using valueType = int;

  constexpr valueType min = 1;
  constexpr valueType max = 9;
  constexpr int size = 20;
  constexpr int deleteMax = 15;

  // Our containers.
  std::map<keyType, valueType> testMap;
  std::vector<valueType> testVector(size);

  // Printers.
  auto printVectorFunc = [](const std::vector<valueType>& v) -> void {
    std::cout << "\ntestVector.size(): " << v.size() << "\n";
    std::cout << "testVector: ";
    for(auto iv : v) {
      std::cout << iv << " ";
    }
    std::cout << "\n";
  };

  auto printMapFunc = [](const std::map<keyType, valueType>& m) -> void {
    auto printMapFunc = [](
        const std::pair<keyType, valueType>& element) -> void {
      std::cout << "[" << element.first << "]==" << element.second << " ";
    };
    std::cout << "\ntestMap.size(): " << m.size() << "\n";
    std::cout << "testMap: ";
    std::for_each(m.begin(), m.end(), printMapFunc);
    std::cout << "\n";
  };

  // Random generator functions.
  // https://stackoverflow.com/a/19728404
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<valueType> initRnd(min, max);
  std::uniform_int_distribution<valueType> deleteRnd(0, deleteMax);
  auto randomIntFunc = [&rng, &initRnd]() -> valueType { return initRnd(rng); };
  auto randomPairFunc = [&rng, &initRnd,
      &testMap]() -> std::pair<keyType, valueType> {
    return std::make_pair(testMap.size(), initRnd(rng));
  };

  // Fill the containers with a random values.

  std::generate(testVector.begin(), testVector.end(), randomIntFunc);
  std::generate_n(
      std::inserter(testMap, testMap.begin()), size, randomPairFunc);

  // Print state.
  std::cout << "Initial state.\n";
  printVectorFunc(testVector);
  printMapFunc(testMap);

  // Remove a random count of elements from the containers.

  int newSize = testVector.size() - deleteRnd(rng);
  if(newSize < 0) {
    newSize = 0;
  }

  // Remove from end of vector.
  testVector.resize(newSize);

  // Remove from end of map.
  auto rim = testMap.rbegin();
  while(rim != testMap.rend()) {
    if(newSize < testMap.size()) {
      std::advance(rim, 1);
      testMap.erase(rim.base());
    } else {
      break;
    }
  }

  // Print state.
  std::cout << "\nAfter removing.\n";
  printVectorFunc(testVector);
  printMapFunc(testMap);

  // Sync the containers.

  // Map by vector.
  auto im = testMap.begin();
  while(im != testMap.end()) {
    if(testVector.end()
        != std::find_if(testVector.begin(), testVector.end(),
               std::bind(std::equal_to<valueType>(), ph::_1, im->second))) {
      ++im;
    } else {
      im = testMap.erase(im);
    }
  }

  // Vector by map.
  auto mapEqFunc = [](const std::pair<keyType, valueType>& element,
      const valueType& value) -> bool { return element.second == value; };

  std::vector<valueType> tmp;
  tmp.reserve(testVector.size());

  for(auto iv = testVector.begin(); iv != testVector.end(); ++iv) {
    if(testMap.end() != std::find_if(testMap.begin(), testMap.end(),
                            std::bind(mapEqFunc, ph::_1, *iv))) {
      tmp.emplace_back(*iv);
    }
  }
  testVector.resize(tmp.size());
  testVector.clear();
  std::move(tmp.begin(), tmp.end(), std::back_inserter(testVector));
  tmp.clear();

  // Print state.
  std::cout << "\nAfter sync.\n";
  printVectorFunc(testVector);
  printMapFunc(testMap);

  return 0;
}
