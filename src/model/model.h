#ifndef A2_SIMPLE_NAVIGATOR_SRC_MODEL_MODEL_H_

#define A2_SIMPLE_NAVIGATOR_SRC_MODEL_MODEL_H_

#include <iostream>

#include "../graph_algorithms/s21_graph_algorithms.h"

namespace s21 {

class Model {
 public:
  Model() = default;

  void ReadMatrixFormFile(const std::string& path);

  void SaveGraphToFile(const std::string& path);

  void PrintGraph();

  const std::string& GetStatus();

  std::vector<int> PerformBreadthFirstSearch(int start);

  std::vector<int> PerformDepthFirstSearch(int start);

  int GetShortestPathBetweenVertices(int start, int final);

  const Matrix GetShortestPathsBetweenAllVertices();

  const Matrix GetLeastSpanningTree();

  const TsmResult SolveTSMProblem();

 private:
  Graph graph_;
  std::string status_;
};

}  // namespace s21
#endif