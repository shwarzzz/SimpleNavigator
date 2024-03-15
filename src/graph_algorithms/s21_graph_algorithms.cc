#include "s21_graph_algorithms.h"

namespace s21 {

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                                   int start_vertex) {
  if (!graph.IsGraphCorrect()) {
    throw IncorrectGraphError("Error: Empty or incorrect graph!");
  }
  int vertexes_count = graph.GetVertexesCount();
  if (start_vertex <= 0 || start_vertex > vertexes_count) {
    throw IncorrectInputData("Error: Input vertex does not exist!");
  }
  std::vector<int> result{start_vertex};
  std::vector<bool> visited(vertexes_count);
  visited[start_vertex - 1] = true;
  s21::stack<int> dfs_stack{start_vertex - 1};
  while (!dfs_stack.empty()) {
    int current_vertex = dfs_stack.top();
    for (int i = 0; i < vertexes_count; i++) {
      if (!visited[i] && graph(current_vertex, i) != 0) {
        dfs_stack.push(i);
        result.push_back(i + 1);
        visited[i] = true;
        break;
      }
    }
    if (current_vertex == dfs_stack.top()) {
      dfs_stack.pop();
    }
  }
  return result;
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                     int start_vertex) {
  if (!graph.IsGraphCorrect()) {
    throw IncorrectGraphError("Error: Empty or incorrect graph!");
  }
  int vertexes_count = graph.GetVertexesCount();
  if (start_vertex <= 0 || start_vertex > vertexes_count) {
    throw IncorrectInputData("Error: The entered vertex does not exist!");
  }
  std::vector<int> result;
  std::vector<bool> visited(vertexes_count);
  visited[start_vertex - 1] = true;
  s21::queue<int> bfs_queue{start_vertex - 1};
  while (!bfs_queue.empty()) {
    int current_vertex = bfs_queue.front();
    result.push_back(current_vertex + 1);
    bfs_queue.pop();
    for (int i = 0; i < vertexes_count; i++) {
      if (!visited[i] && graph(current_vertex, i) != 0) {
        bfs_queue.push(i);
        visited[i] = true;
      }
    }
  }
  return result;
}

int GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                    int vertex2) {
  if (!graph.IsGraphCorrect()) {
    throw IncorrectGraphError("Error: Empty or incorrect graph!");
  }
  int vertexes_count = graph.GetVertexesCount();
  if (vertex1 <= 0 || vertex1 > vertexes_count || vertex2 <= 0 ||
      vertex2 > vertexes_count) {
    throw IncorrectInputData("Error: The entered vertexes do not exist!");
  }
  if (vertex1 == vertex2) {
    throw IncorrectInputData(
        "Error: vertex1 = vertex2 -> path does not exists!");
  }
  std::vector<int> distances(vertexes_count, kInfinity_);
  distances[vertex1 - 1] = 0;
  std::set<std::pair<int, int>> vertexes{{distances[vertex1 - 1], vertex1 - 1}};
  while (!vertexes.empty()) {
    auto current = *(vertexes.begin());
    vertexes.erase(vertexes.begin());
    for (int i = 0; i < vertexes_count; i++) {
      if (graph(current.second, i) != 0) {
        if (distances[i] == kInfinity_ ||
            distances[i] > current.first + graph(current.second, i)) {
          vertexes.erase({distances[i], i});
          distances[i] = current.first + graph(current.second, i);
          vertexes.insert({distances[i], i});
        }
      }
    }
  }
  if (distances[vertex2 - 1] == kInfinity_) {
    throw GraphAlgorithmsError("Error: Path does not exists!");
  }
  return distances[vertex2 - 1];
}

const Matrix GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
  if (!graph.IsGraphCorrect()) {
    throw IncorrectGraphError("Error: Empty or incorrect graph!");
  }
  int vertexes_count = graph.GetVertexesCount();
  Matrix result = graph.GetMatrix();
  PrepareMatrix(result);
  for (int k = 0; k < vertexes_count; k++) {
    for (int i = 0; i < vertexes_count; i++) {
      for (int j = 0; j < vertexes_count; j++) {
        if (result(i, k) != kInfinity_ && result(k, j) != kInfinity_) {
          if (result(i, j) == kInfinity_ ||
              result(i, j) > result(i, k) + result(k, j)) {
            result(i, j) = result(i, k) + result(k, j);
          }
        }
      }
    }
  }
  return result;
}

void GraphAlgorithms::PrepareMatrix(Matrix &matrix) {
  for (int i = 0; i < matrix.GetRows(); i++) {
    for (int j = 0; j < matrix.GetColumns(); j++) {
      if (i == j) {
        matrix(i, j) = 0;
      } else if (matrix(i, j) == 0) {
        matrix(i, j) = kInfinity_;
      }
    }
  }
}

const Matrix GraphAlgorithms::GetLeastSpanningTree(Graph &graph) {
  if (graph.GetType() == kDirected || !graph.IsGraphCorrect()) {
    throw IncorrectGraphError("Error: Empty or incorrect graph!");
  }
  int vertexes_count = graph.GetVertexesCount();
  Matrix result(vertexes_count, vertexes_count);
  std::set<int> unvisited;
  for (int i = 1; i < vertexes_count; i++) {
    unvisited.insert(i);
  }
  std::set<int> visited;
  visited.insert(0);
  while (!unvisited.empty()) {
    std::pair<int, int> edge(-1, -1);
    for (auto i = visited.begin(); i != visited.end(); i++) {
      for (auto j = unvisited.begin(); j != unvisited.end(); j++) {
        if (graph(*i, *j) != 0 &&
            (edge.first == -1 ||
             graph(edge.first, edge.second) > graph(*i, *j))) {
          edge = {*i, *j};
        }
      }
    }
    result(edge.first, edge.second) = graph(edge.first, edge.second);
    result(edge.second, edge.first) = graph(edge.first, edge.second);
    unvisited.erase(edge.second);
    visited.insert(edge.second);
  }
  return result;
}

const TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph) {
  if (!graph.IsGraphCorrect()) {
    throw IncorrectGraphError("Error: Empty or incorrect graph!");
  }
  AntsAlgorithmData ants_data(graph.GetVertexesCount());
  SetStartPheromone(ants_data.pheromones, graph);
  std::set<std::pair<int, double>> variants;
  for (int iter = 0; iter < kMaxIterationsNumber_; iter++) {
    ants_data.Reset();
    for (int k = 0; k < ants_data.vertexes_count; k++) {
      int count = 0;
      int current_vertex = k;
      int new_vertex = 0;
      std::vector<bool> visited(ants_data.vertexes_count);
      ants_data.routes(k, count) = current_vertex + 1;
      while (true) {
        visited[current_vertex] = true;
        variants.clear();
        double sum = 0;
        for (int i = 0; i < ants_data.vertexes_count; i++) {
          if (graph(current_vertex, i) != 0 &&
              ((!visited[i] && i != current_vertex) ||
               (i == k && count == ants_data.vertexes_count - 1))) {
            double value =
                pow(ants_data.pheromones(current_vertex, i), kAlpha_) *
                pow(kQ_ / graph(current_vertex, i), kBeta_);
            variants.insert({i, value});
            sum += value;
          }
        }
        if (variants.empty()) {
          break;
        }
        new_vertex = MakeChoice(variants, sum);
        ants_data.distances[k] += graph(current_vertex, new_vertex);
        count++;
        current_vertex = new_vertex;
        ants_data.routes(k, count) = current_vertex + 1;
      }
      if (count != ants_data.vertexes_count) {
        ants_data.distances[k] = 0;
      }
    }
    UpdatePheromones(ants_data);
    if (IsNewRouteFound(ants_data)) {
      iter = -1;
    }
  }
  if (ants_data.result.distance == -1) {
    ants_data.result.Reset();
    throw GraphAlgorithmsError("Error: There are no possible paths!");
  }
  return ants_data.result;
}

void GraphAlgorithms::SetStartPheromone(Matrix &dst, const Graph &graph) {
  int vertexes_count = graph.GetVertexesCount();
  for (int i = 0; i < vertexes_count; i++) {
    for (int j = 0; j < vertexes_count; j++) {
      if (graph(i, j) != 0 && i != j) {
        dst(i, j) = kStartPheromone_;
      }
    }
  }
}

void GraphAlgorithms::UpdatePheromones(AntsAlgorithmData &data) {
  for (int i = 0; i < data.vertexes_count; i++) {
    for (int j = 0; j < data.vertexes_count; j++) {
      data.pheromones(i, j) *= (1.0 - kEvaporation_);
    }
  }
  for (int i = 0; i < data.vertexes_count; i++) {
    if (data.distances[i] != 0) {
      double pheromones_add = kQ_ / data.distances[i];
      int start = 0;
      int end = 0;
      for (int j = 0; j < data.vertexes_count; j++) {
        start = data.routes(i, j) - 1;
        end = data.routes(i, j + 1) - 1;
        data.pheromones(start, end) += pheromones_add;
        data.pheromones(end, start) += pheromones_add;
      }
    }
  }
}

bool GraphAlgorithms::IsNewRouteFound(AntsAlgorithmData &data) {
  int min_index = -1;
  for (int i = 0; i < data.vertexes_count; i++) {
    if (data.distances[i] != 0) {
      if (data.result.distance == -1 ||
          data.distances[i] < data.result.distance) {
        if (min_index == -1 || data.distances[min_index] > data.distances[i]) {
          min_index = i;
        }
      }
    }
  }
  if (min_index != -1) {
    for (int i = 0; i <= data.vertexes_count; i++) {
      data.result.vertices[i] = data.routes(min_index, i);
    }
    data.result.distance = data.distances[min_index];
  }
  return min_index != -1;
}

int GraphAlgorithms::MakeChoice(std::set<std::pair<int, double>> &variants,
                                double sum) {
  int vertex = -1;
  double choice = GenerateValue();
  double value = 0;
  for (auto i = variants.begin(); i != variants.end(); i++) {
    value += (*i).second / sum;
    if (value >= choice) {
      vertex = (*i).first;
      break;
    }
  }
  return vertex;
}

double GraphAlgorithms::GenerateValue() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dist(0, 1);
  return dist(gen);
}

std::ostream &operator<<(std::ostream &os, const TsmResult &tsm) {
  os << "Final distance: " << tsm.distance << ";\n";
  os << "Path: ";
  for (size_t i = 0; i < tsm.vertices.size(); i++) {
    os << tsm.vertices[i];
    if (i != tsm.vertices.size() - 1) {
      os << "--";
    } else {
      os << ";\n";
    }
  }
  return os;
}

}  // namespace s21