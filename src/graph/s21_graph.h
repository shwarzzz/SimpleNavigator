#ifndef A2_SIMPLE_NAVIGATOR_SRC_GRAPH_S21_GRAPH_H_

#define A2_SIMPLE_NAVIGATOR_SRC_GRAPH_S21_GRAPH_H_

#include "../modules/matrix.h"
#include "file_reader.h"
#include "file_writer.h"
#include "graph_helper.h"

namespace s21 {

class Graph {
 public:
  Graph();

  void LoadGraphFromFile(std::string filename);
  void ExportGraphToDot(std::string filename);

  void Reset();

  GraphType GetType() const noexcept;
  const Matrix &GetMatrix() const noexcept;
  size_t GetVertexesCount() const noexcept;

  bool IsGraphCorrect() const noexcept;

  double operator()(int i, int j) const;

  friend std::ostream &operator<<(std::ostream &os, const Graph &graph);

 private:
  void ValidateData();
  void DefineGraphType();

  Matrix adjacency_matrix_;
  size_t vertexes_;

  GraphType type_;
};

}  // namespace s21

#endif