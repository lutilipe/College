#include <vector>
#include <iostream>

#include "Point.h"

void readPoints(std::vector<Point> &vec) {
  Point p;
  while (std::cin >> p) {
    vec.push_back(p);
  }
}

void printPoints(std::vector<Point> &vec) {
  for (Point p: vec) {
    std::cout << p << " ";
  }
  std::cout << std::endl;
}

Point sumAssPoints(std::vector<Point> &vec) {
  Point pSum;
  for (Point p: vec) {
    pSum += p;
  }
  return pSum;
}

Point sumBinPoints(std::vector<Point> &vec) {
  Point pSum;
  for (Point p: vec) {
    pSum = pSum + p;
  }
  return pSum;
}

int main() {
  std::vector<Point> vec;
  char testCase;
  std::cin >> testCase;
  readPoints(vec);
  if (testCase == 'a') {
    std::cout << "Sum = " << sumAssPoints(vec) << std::endl;
  } else if (testCase == 'b') {
    std::cout << "Sum = " << sumBinPoints(vec) << std::endl;
  }
  printPoints(vec);
}