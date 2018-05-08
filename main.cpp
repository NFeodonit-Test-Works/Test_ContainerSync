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

int main()
{
  constexpr int min = 1;
  constexpr int max = 9;
  constexpr int size = 50;

  std::vector<int> testVector(size);
  std::map<int, int> testMap;

  // https://stackoverflow.com/a/19728404
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> uni(min, max);
  auto randomIntFunc = [&rng, &uni]() -> int { return uni(rng); };
  auto randomPairFunc = [&rng, &uni, &testMap]() -> std::pair<int, int> {
    return std::make_pair(testMap.size(), uni(rng));
  };

  std::generate(testVector.begin(), testVector.end(), randomIntFunc);
  std::generate_n(
      std::inserter(testMap, testMap.begin()), size, randomPairFunc);

  std::cout << "Initial state:\n";

  std::cout << "testVector: ";
  for(auto iv : testVector) {
    std::cout << iv << " ";
  }
  std::cout << "\n";

  auto printMap = [](const std::pair<int, int>& element) {
    std::cout << "[" << element.first << "]==" << element.second << " ";
  };
  std::cout << "testMap: ";
  std::for_each(testMap.begin(), testMap.end(), printMap);
  std::cout << "\n";

  return 0;
}
