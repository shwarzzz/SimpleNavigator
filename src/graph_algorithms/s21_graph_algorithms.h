#ifndef A2_SIMPLE_NAVIGATOR_SRC_GRAPH_ALGORITHMS_S21_GRAPH_ALGORITHMS_H_

#define A2_SIMPLE_NAVIGATOR_SRC_GRAPH_ALGORITHMS_S21_GRAPH_ALGORITHMS_H_

#include <chrono>
#include <random>
#include <set>
#include <vector>

#include "../graph/s21_graph.h"
#include "../modules/queue.h"
#include "../modules/stack.h"

namespace s21 {
struct TsmResult {
  std::vector<int> vertices;
  double distance;
  void Reset() {
    vertices.clear();
    distance = 0;
  }
};

struct AntsAlgorithmData {
  int vertexes_count;
  Matrix pheromones;
  Matrix routes;
  std::vector<int> distances;
  TsmResult result;

  AntsAlgorithmData(int vertexes) {
    vertexes_count = vertexes;
    pheromones.SetRows(vertexes);
    pheromones.SetColumns(vertexes);
    routes.SetRows(vertexes);
    routes.SetColumns(vertexes + 1);
    distances.resize(vertexes_count);
    result.distance = -1;
    result.vertices.resize(vertexes + 1);
  }

  void Reset() {
    routes.Fill(0);
    for (int i = 0; i < vertexes_count; i++) {
      distances[i] = 0;
    }
  }
};

class GraphAlgorithms {
 public:
  static std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);
  static std::vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);

  static int GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                            int vertex2);

  static const Matrix GetShortestPathsBetweenAllVertices(Graph &graph);

  static const Matrix GetLeastSpanningTree(Graph &graph);

  static const TsmResult SolveTravelingSalesmanProblem(Graph &graph);

 private:
  static void PrepareMatrix(Matrix &matrix);

  static void SetStartPheromone(Matrix &dst, const Graph &graph);
  static int MakeChoice(std::set<std::pair<int, double>> &variants, double sum);
  static double GenerateValue();
  static bool IsNewRouteFound(AntsAlgorithmData &data);
  static void UpdatePheromones(AntsAlgorithmData &data);

  static constexpr int kInfinity_ = -1;

  static constexpr double kAlpha_ = 1;
  static constexpr double kBeta_ = 1;
  static constexpr double kQ_ = 4;
  static constexpr double kMaxIterationsNumber_ = 100;
  static constexpr double kStartPheromone_ = 0.2;
  static constexpr double kEvaporation_ = 0.34;
};

std::ostream &operator<<(std::ostream &os, const TsmResult &tsm);
}  // namespace s21

#endif