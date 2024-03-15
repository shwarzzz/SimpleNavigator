#ifndef A2_SIMPLE_NAVIGATOR_SRC_CONTROLLER_CONTROLLER_H_

#define A2_SIMPLE_NAVIGATOR_SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"

namespace s21 {
class Controller {
 public:
  Controller() = delete;
  Controller(Model* model) : model_(model) {}

  void PrintGraph();
  void LoadGraphFromFile(const std::string& path);
  void SaveGraphToFile(const std::string& path);

  std::vector<int> BreadthFirstSearch(int start);

  std::vector<int> DepthFirstSearch(int start);

  int FindShortestPathBetweenVertices(int vertex1, int vertex2);

  const Matrix FindShortestPathBetweenAllVertices();

  const Matrix FindLeastSpanningTree();

  const TsmResult SolveTSMProblem();

  const std::string& GetStatus();

 private:
  Model* model_;
};
}  // namespace s21
#endif