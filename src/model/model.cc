#include "model.h"

namespace s21 {

void Model::ReadMatrixFormFile(const std::string& path) {
  try {
    graph_.LoadGraphFromFile(path);
    status_ = "Graph successfully loaded!";
  } catch (std::exception& e) {
    status_ = e.what();
  }
}

void Model::SaveGraphToFile(const std::string& path) {
  try {
    graph_.ExportGraphToDot(path);
    status_ = "Graph successfully exported to file!";
  } catch (std::exception& e) {
    status_ = e.what();
  }
}

const std::string& Model::GetStatus() { return status_; }

void Model::PrintGraph() { std::cout << graph_; }

std::vector<int> Model::PerformBreadthFirstSearch(int start) {
  std::vector<int> res;
  status_ = "BFS has been successfully completed!";
  try {
    res = GraphAlgorithms::BreadthFirstSearch(graph_, start);
  } catch (std::exception& e) {
    status_ = e.what();
    res.clear();
  }
  return res;
}

std::vector<int> Model::PerformDepthFirstSearch(int start) {
  std::vector<int> res;
  status_ = "DFS has been successfully completed!";
  try {
    res = GraphAlgorithms::DepthFirstSearch(graph_, start);
  } catch (std::exception& e) {
    status_ = e.what();
    res.clear();
  }
  return res;
}

int Model::GetShortestPathBetweenVertices(int start, int final) {
  status_ =
      "The search for the shortest path between two vertices is "
      "successful!";
  int res = 0;
  try {
    res = GraphAlgorithms::GetShortestPathBetweenVertices(graph_, start, final);
  } catch (std::exception& e) {
    status_ = e.what();
    res = 0;
  }
  return res;
}

const Matrix Model::GetShortestPathsBetweenAllVertices() {
  status_ =
      "The search for the shortest path between all vertices is "
      "successful!";
  Matrix res;
  try {
    res = GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph_);
  } catch (std::exception& e) {
    status_ = e.what();
    res.SetRows(0);
    res.SetColumns(0);
  }
  return res;
}

const Matrix Model::GetLeastSpanningTree() {
  status_ = "The search for the minimal spanning tree is successful!";
  Matrix res;
  try {
    res = GraphAlgorithms::GetLeastSpanningTree(graph_);
  } catch (std::exception& e) {
    status_ = e.what();
    res.SetRows(0);
    res.SetColumns(0);
  }
  return res;
}

const TsmResult Model::SolveTSMProblem() {
  status_ = "The solving the traveling salesman's problem is successful!";
  TsmResult res;
  try {
    res = GraphAlgorithms::SolveTravelingSalesmanProblem(graph_);
  } catch (std::exception& e) {
    res.Reset();
    status_ = e.what();
  }
  return res;
}

}  // namespace s21