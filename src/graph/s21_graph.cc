#include "s21_graph.h"

namespace s21 {

Graph::Graph() { Reset(); }

void Graph::LoadGraphFromFile(std::string filename) {
  Reset();
  Matrix tmp = FileReader::GetInstance().ReadData(filename);
  adjacency_matrix_ = tmp;
  vertexes_ = adjacency_matrix_.GetRows();
  ValidateData();
  DefineGraphType();
}

void Graph::ExportGraphToDot(std::string filename) {
  if (type_ == kDefault) {
    throw IncorrectGraphError("Error: Graph is empty!");
  }
  FileWriter::GetInstance().WriteData(filename, adjacency_matrix_, type_);
}

void Graph::ValidateData() {
  for (int i = 0; i < adjacency_matrix_.GetRows(); i++) {
    for (int j = 0; j < adjacency_matrix_.GetColumns(); j++) {
      if (adjacency_matrix_(i, j) < 0 ||
          adjacency_matrix_(i, j) - std::trunc(adjacency_matrix_(i, j)) > 0) {
        Reset();
        throw FileContentError("Error: Data must be natural numbers!");
      }
    }
  }
}

void Graph::DefineGraphType() {
  type_ = kUndirected;
  for (int i = 0; i < adjacency_matrix_.GetRows(); i++) {
    for (int j = 0; j < adjacency_matrix_.GetColumns(); j++) {
      if (i != j) {
        if (adjacency_matrix_(i, j) != adjacency_matrix_(j, i)) {
          type_ = kDirected;
          break;
        }
      }
    }
  }
}

void Graph::Reset() {
  type_ = kDefault;
  vertexes_ = 0;
  adjacency_matrix_.SetRows(0);
  adjacency_matrix_.SetColumns(0);
}

GraphType Graph::GetType() const noexcept { return type_; }

const Matrix &Graph::GetMatrix() const noexcept { return adjacency_matrix_; }

size_t Graph::GetVertexesCount() const noexcept { return vertexes_; }

bool Graph::IsGraphCorrect() const noexcept { return type_ != kDefault; }

double Graph::operator()(int i, int j) const { return adjacency_matrix_(i, j); }

std::ostream &operator<<(std::ostream &os, const Graph &graph) {
  os << "\n\tGraph info:\n";
  os << "Vertexes count: " << graph.vertexes_ << ";\n";
  os << "Adjacency Matrix:\n";
  os << graph.adjacency_matrix_;
  return os;
}

}  // namespace s21