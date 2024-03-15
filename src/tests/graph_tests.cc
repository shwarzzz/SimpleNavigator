#include "../graph_algorithms/s21_graph_algorithms.h"
#include "gtest/gtest.h"
#include "test_helper.h"

TEST(FileReaderTests, TestCorrectFile_1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  ASSERT_EQ(graph.GetVertexesCount(), 11);
  ASSERT_EQ(graph.GetType(), s21::kUndirected);
  for (int i = 0; i < 11; i++) {
    for (int j = 0; j < 11; j++) {
      ASSERT_DOUBLE_EQ(graph(i, j), correct_graph_1[i][j]);
    }
  }
}

TEST(FileReaderTests, TestCorrectFile_2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_2.txt");
  ASSERT_EQ(graph.GetVertexesCount(), 8);
  ASSERT_EQ(graph.GetType(), s21::kUndirected);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      ASSERT_DOUBLE_EQ(graph(i, j), correct_graph_2[i][j]);
    }
  }
}

TEST(FileReaderTests, TestCorrectFile_3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_3.txt");
  ASSERT_EQ(graph.GetVertexesCount(), 20);
  ASSERT_EQ(graph.GetType(), s21::kUndirected);
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      ASSERT_DOUBLE_EQ(graph(i, j), correct_graph_3[i][j]);
    }
  }
}

TEST(FileReaderTests, TestCorrectFile_4) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_4.txt");
  ASSERT_EQ(graph.GetVertexesCount(), 10);
  ASSERT_EQ(graph.GetType(), s21::kUndirected);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      ASSERT_DOUBLE_EQ(graph(i, j), correct_graph_4[i][j]);
    }
  }
}

TEST(FileReaderTests, TestCorrectFile_5) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/graph_halina.txt");
  ASSERT_EQ(graph.GetVertexesCount(), 21);
  ASSERT_EQ(graph.GetType(), s21::kUndirected);
  for (int i = 0; i < 21; i++) {
    for (int j = 0; j < 21; j++) {
      ASSERT_DOUBLE_EQ(graph(i, j), graph_halina[i][j]);
    }
  }
}

TEST(FileReaderTests, TestCorrectFile_6) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_5.txt");
  ASSERT_EQ(graph.GetVertexesCount(), 6);
  ASSERT_EQ(graph.GetType(), s21::kDirected);
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      ASSERT_DOUBLE_EQ(graph(i, j), correct_graph_5[i][j]);
    }
  }
}

TEST(FileReaderTests, TestError_1) {
  s21::Graph graph;
  ASSERT_THROW(graph.LoadGraphFromFile("./tests/test_data/empty_file.txt"),
               s21::FileContentError);
}

TEST(FileReaderTests, TestError_2) {
  s21::Graph graph;
  ASSERT_THROW(graph.LoadGraphFromFile("no_such_file.txt"), s21::OpenFileError);
}

TEST(FileReaderTests, TestError_3) {
  s21::Graph graph;
  ASSERT_THROW(graph.LoadGraphFromFile("./tests/test_data/wrong_1.txt"),
               s21::FileContentError);
}

TEST(FileReaderTests, TestError_4) {
  s21::Graph graph;
  ASSERT_THROW(graph.LoadGraphFromFile("./tests/test_data/wrong_2.txt"),
               s21::FileContentError);
}

TEST(FileReaderTests, TestError_5) {
  s21::Graph graph;
  ASSERT_THROW(graph.LoadGraphFromFile("./tests/test_data/wrong_3.txt"),
               s21::FileContentError);
}

TEST(FileReaderTests, TestError_6) {
  s21::Graph graph;
  ASSERT_THROW(graph.LoadGraphFromFile("./tests/test_data/wrong_4.txt"),
               s21::FileContentError);
}

TEST(FileReaderTests, TestError_7) {
  s21::Graph graph;
  ASSERT_THROW(graph.LoadGraphFromFile("./tests/test_data/wrong_5.txt"),
               s21::FileContentError);
}

TEST(FileReaderTests, TestError_8) {
  s21::Graph graph;
  ASSERT_THROW(graph.LoadGraphFromFile("./tests/test_data/wrong_6.txt"),
               s21::FileContentError);
}

TEST(FileWriterTests, TestCorrectFile_1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  graph.ExportGraphToDot("./tests/generated_files/graph_1.dot");
  graph.ExportGraphToDot("./tests/generated_files/graph_1.gv");
}

TEST(FileWriterTests, TestCorrectFile_2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_2.txt");
  graph.ExportGraphToDot("./tests/generated_files/graph_2.dot");
  graph.ExportGraphToDot("./tests/generated_files/graph_2.gv");
}

TEST(FileWriterTests, TestCorrectFile_3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_3.txt");
  graph.ExportGraphToDot("./tests/generated_files/graph_3.dot");
  graph.ExportGraphToDot("./tests/generated_files/graph_3.gv");
}

TEST(FileWriterTests, TestCorrectFile_4) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_4.txt");
  graph.ExportGraphToDot("./tests/generated_files/graph_4.dot");
  graph.ExportGraphToDot("./tests/generated_files/graph_4.gv");
}

TEST(FileWriterTests, TestCorrectFile_5) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_5.txt");
  graph.ExportGraphToDot("./tests/generated_files/graph_5.dot");
  graph.ExportGraphToDot("./tests/generated_files/graph_5.gv");
}

TEST(FileWriterTests, TestCorrectFile_6) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/graph_halina.txt");
  graph.ExportGraphToDot("./tests/generated_files/graph_6.dot");
  graph.ExportGraphToDot("./tests/generated_files/graph_6.gv");
}

TEST(FileWriterTests, TestError_1) {
  s21::Graph graph;
  ASSERT_THROW(graph.ExportGraphToDot("./tests/test_data/test_1.dot"),
               s21::IncorrectGraphError);
}

TEST(FileWriterTests, TestError_2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  ASSERT_THROW(graph.ExportGraphToDot("test_1.do"), s21::FileExtensionError);
}

TEST(FileWriterTests, TestError_3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  ASSERT_THROW(graph.ExportGraphToDot("test_1.g"), s21::FileExtensionError);
}

TEST(FileWriterTests, TestError_4) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  ASSERT_THROW(graph.ExportGraphToDot("./tests/test_data/test"),
               s21::FileExtensionError);
}

TEST(FileWriterTests, TestError_5) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  ASSERT_THROW(graph.ExportGraphToDot(".gv"), s21::FileExtensionError);
}

TEST(FileWriterTests, TestError_6) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  ASSERT_THROW(graph.ExportGraphToDot(".dot"), s21::FileExtensionError);
}

TEST(FileWriterTests, TestError_7) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  ASSERT_THROW(graph.ExportGraphToDot("./tests/test_data/inaccessible.dot"),
               s21::OpenFileError);
}

TEST(DFSTests, TestCorrect_1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_2.txt");
  auto result = s21::GraphAlgorithms::DepthFirstSearch(graph, 7);
  std::vector<int> check{7, 5, 3, 1, 2, 6, 8, 4};
  ASSERT_TRUE(result == check);
}

TEST(DFSTests, TestCorrect_2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_5.txt");
  auto result = s21::GraphAlgorithms::DepthFirstSearch(graph, 6);
  std::vector<int> check{6, 4, 2, 1, 3, 5};
  ASSERT_TRUE(result == check);
}

TEST(DFSTests, TestCorrect_3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/dfs_graph_test.txt");
  auto result = s21::GraphAlgorithms::DepthFirstSearch(graph, 3);
  std::vector<int> check{3};
  ASSERT_TRUE(result == check);
}

TEST(DFSTests, TestCorrect_4) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_4.txt");
  auto result = s21::GraphAlgorithms::DepthFirstSearch(graph, 6);
  std::vector<int> check{6, 4, 2, 1, 3, 7, 9, 5, 10, 8};
  ASSERT_TRUE(result == check);
}

TEST(DFSTests, TestCorrect_5) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/graph_halina.txt");
  auto result = s21::GraphAlgorithms::DepthFirstSearch(graph, 17);
  std::vector<int> check{17, 15, 12, 11, 7,  3,  1,  2, 4, 5, 6,
                         21, 20, 19, 18, 16, 14, 13, 9, 8, 10};
  ASSERT_TRUE(result == check);
}

TEST(DFSTests, TestError_1) {
  s21::Graph graph;
  ASSERT_THROW(s21::GraphAlgorithms::DepthFirstSearch(graph, 1),
               s21::IncorrectGraphError);
}

TEST(DFSTests, TestError_2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  ASSERT_THROW(s21::GraphAlgorithms::DepthFirstSearch(graph, -3),
               s21::IncorrectInputData);
}

TEST(DFSTests, TestError_3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  ASSERT_THROW(s21::GraphAlgorithms::DepthFirstSearch(graph, 12),
               s21::IncorrectInputData);
}

TEST(BFSTests, TestCorrect_1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_2.txt");
  auto result = s21::GraphAlgorithms::BreadthFirstSearch(graph, 2);
  std::vector<int> check{2, 1, 3, 6, 8, 4, 5, 7};
  ASSERT_TRUE(result == check);
}

TEST(BFSTests, TestCorrect_2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_5.txt");
  auto result = s21::GraphAlgorithms::BreadthFirstSearch(graph, 6);
  std::vector<int> check{6, 4, 2, 3, 5, 1};
  ASSERT_TRUE(result == check);
}

TEST(BFSTests, TestCorrect_3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/dfs_graph_test.txt");
  auto result = s21::GraphAlgorithms::BreadthFirstSearch(graph, 3);
  std::vector<int> check{3};
  ASSERT_TRUE(result == check);
}

TEST(BFSTests, TestCorrect_4) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_4.txt");
  auto result = s21::GraphAlgorithms::BreadthFirstSearch(graph, 4);
  std::vector<int> check{4, 2, 3, 6, 7, 1, 5, 8, 9, 10};
  ASSERT_TRUE(result == check);
}

TEST(BFSTests, TestCorrect_5) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/graph_halina.txt");
  auto result = s21::GraphAlgorithms::BreadthFirstSearch(graph, 7);
  std::vector<int> check{7, 3,  6, 11, 1,  2,  4,  5,  10, 12, 13,
                         8, 21, 9, 14, 15, 20, 16, 17, 19, 18};
  ASSERT_TRUE(result == check);
}

TEST(BFSTests, TestError_1) {
  s21::Graph graph;
  ASSERT_THROW(s21::GraphAlgorithms::BreadthFirstSearch(graph, 1),
               s21::IncorrectGraphError);
}

TEST(BFSTests, TestError_2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  ASSERT_THROW(s21::GraphAlgorithms::BreadthFirstSearch(graph, -3),
               s21::IncorrectInputData);
}

TEST(BFSTests, TestError_3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  ASSERT_THROW(s21::GraphAlgorithms::BreadthFirstSearch(graph, 12),
               s21::IncorrectInputData);
}

TEST(DijkstraAlgorithmTests, TestCorrect_1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_4.txt");
  int result =
      s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph, 5, 3);
  ASSERT_EQ(result, 21);
}

TEST(DijkstraAlgorithmTests, TestCorrect_2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_4.txt");
  int result =
      s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 10);
  ASSERT_EQ(result, 24);
}

TEST(DijkstraAlgorithmTests, TestCorrect_3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_5.txt");
  int result =
      s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph, 6, 1);
  ASSERT_EQ(result, 11);
}

TEST(DijkstraAlgorithmTests, TestCorrect_4) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/graph_halina.txt");
  int result =
      s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 17);
  ASSERT_EQ(result, 6);
}

TEST(DijkstraAlgorithmTests, TestCorrect_5) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_2.txt");
  int result =
      s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph, 4, 8);
  ASSERT_EQ(result, 2);
}

TEST(DijkstraAlgorithmTests, TestError_1) {
  s21::Graph graph;
  ASSERT_THROW(
      s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 2),
      s21::IncorrectGraphError);
}

TEST(DijkstraAlgorithmTests, TestError_2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  ASSERT_THROW(
      s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph, 12, 1),
      s21::IncorrectInputData);
}

TEST(DijkstraAlgorithmTests, TestError_3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  ASSERT_THROW(
      s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 12),
      s21::IncorrectInputData);
}

TEST(DijkstraAlgorithmTests, TestError_4) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  ASSERT_THROW(
      s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph, 0, 3),
      s21::IncorrectInputData);
}

TEST(DijkstraAlgorithmTests, TestError_5) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  ASSERT_THROW(
      s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph, 5, 0),
      s21::IncorrectInputData);
}

TEST(DijkstraAlgorithmTests, TestError_6) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  ASSERT_THROW(
      s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph, -2, 3),
      s21::IncorrectInputData);
}

TEST(DijkstraAlgorithmTests, TestError_7) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  ASSERT_THROW(
      s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph, 10, -1),
      s21::IncorrectInputData);
}

TEST(DijkstraAlgorithmTests, TestError_8) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  ASSERT_THROW(
      s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph, -2, 15),
      s21::IncorrectInputData);
}

TEST(DijkstraAlgorithmTests, TestError_9) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  ASSERT_THROW(
      s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph, 100, 0),
      s21::IncorrectInputData);
}

TEST(DijkstraAlgorithmTests, TestError_10) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  ASSERT_THROW(
      s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph, 2, 2),
      s21::IncorrectInputData);
}

TEST(DijkstraAlgorithmTests, TestError_11) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/dfs_graph_test.txt");
  ASSERT_THROW(
      s21::GraphAlgorithms::GetShortestPathBetweenVertices(graph, 3, 1),
      s21::GraphAlgorithmsError);
}

TEST(FloydAlgorithmTests, TestCorrect_1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  s21::Matrix result =
      s21::GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
  ASSERT_EQ(graph.GetVertexesCount(), 11);
  for (int i = 0; i < 11; i++) {
    for (int j = 0; j < 11; j++) {
      ASSERT_DOUBLE_EQ(result(i, j), floyd_data_1[i][j]);
    }
  }
}

TEST(FloydAlgorithmTests, TestCorrect_2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_2.txt");
  s21::Matrix result =
      s21::GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
  ASSERT_EQ(graph.GetVertexesCount(), 8);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      ASSERT_DOUBLE_EQ(result(i, j), floyd_data_2[i][j]);
    }
  }
}

TEST(FloydAlgorithmTests, TestCorrect_3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_3.txt");
  s21::Matrix result =
      s21::GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
  ASSERT_EQ(graph.GetVertexesCount(), 20);
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      ASSERT_DOUBLE_EQ(result(i, j), floyd_data_3[i][j]);
    }
  }
}

TEST(FloydAlgorithmTests, TestCorrect_4) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_4.txt");
  s21::Matrix result =
      s21::GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
  ASSERT_EQ(graph.GetVertexesCount(), 10);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      ASSERT_DOUBLE_EQ(result(i, j), floyd_data_4[i][j]);
    }
  }
}

TEST(FloydAlgorithmTests, TestCorrect_5) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_5.txt");
  s21::Matrix result =
      s21::GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
  ASSERT_EQ(graph.GetVertexesCount(), 6);
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      ASSERT_DOUBLE_EQ(result(i, j), floyd_data_5[i][j]);
    }
  }
}

TEST(FloydAlgorithmTests, TestCorrect_6) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/dfs_graph_test.txt");
  s21::Matrix result =
      s21::GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
  ASSERT_EQ(graph.GetVertexesCount(), 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(result(i, j), floyd_data_6[i][j]);
    }
  }
}

TEST(FloydAlgorithmTests, TestCorrect_7) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/graph_halina.txt");
  s21::Matrix result =
      s21::GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
  ASSERT_EQ(graph.GetVertexesCount(), 21);
  for (int i = 0; i < 21; i++) {
    for (int j = 0; j < 21; j++) {
      ASSERT_DOUBLE_EQ(result(i, j), floyd_graph_halina[i][j]);
    }
  }
}

TEST(FloydAlgorithmTests, TestError) {
  s21::Graph graph;
  ASSERT_THROW(s21::GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph),
               s21::IncorrectGraphError);
}

TEST(PrimAlgorithmTests, TestCorrect_1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_2.txt");
  s21::Matrix result = s21::GraphAlgorithms::GetLeastSpanningTree(graph);
  ASSERT_EQ(graph.GetVertexesCount(), 8);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      ASSERT_DOUBLE_EQ(result(i, j), prim_data_1[i][j]);
    }
  }
}

TEST(PrimAlgorithmTests, TestCorrect_2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_4.txt");
  s21::Matrix result = s21::GraphAlgorithms::GetLeastSpanningTree(graph);
  ASSERT_EQ(graph.GetVertexesCount(), 10);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      ASSERT_DOUBLE_EQ(result(i, j), prim_data_2[i][j]);
    }
  }
}

TEST(PrimAlgorithmTests, TestError_1) {
  s21::Graph graph;
  ASSERT_THROW(s21::GraphAlgorithms::GetLeastSpanningTree(graph),
               s21::IncorrectGraphError);
}

TEST(PrimAlgorithmTests, TestError_2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_5.txt");
  ASSERT_THROW(s21::GraphAlgorithms::GetLeastSpanningTree(graph),
               s21::IncorrectGraphError);
}

TEST(PrimAlgorithmTests, TestError_3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/dfs_graph_test.txt");
  ASSERT_THROW(s21::GraphAlgorithms::GetLeastSpanningTree(graph),
               s21::IncorrectGraphError);
}

TEST(AntsAlgorithmTests, TestCorrect_1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_1.txt");
  s21::TsmResult result =
      s21::GraphAlgorithms::SolveTravelingSalesmanProblem(graph);
  ASSERT_EQ(result.distance, 253);
}

TEST(AntsAlgorithmTests, TestCorrect_2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_2.txt");
  s21::TsmResult result =
      s21::GraphAlgorithms::SolveTravelingSalesmanProblem(graph);
  ASSERT_EQ(result.distance, 8);
}

TEST(AntsAlgorithmTests, TestCorrect_3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_3.txt");
  s21::TsmResult result =
      s21::GraphAlgorithms::SolveTravelingSalesmanProblem(graph);
  ASSERT_EQ(result.distance, 61);
}

TEST(AntsAlgorithmTests, TestCorrect_4) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_4.txt");
  s21::TsmResult result =
      s21::GraphAlgorithms::SolveTravelingSalesmanProblem(graph);
  ASSERT_EQ(result.distance, 87);
}

TEST(AntsAlgorithmTests, TestCorrect_5) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/ant_test.txt");
  s21::TsmResult result =
      s21::GraphAlgorithms::SolveTravelingSalesmanProblem(graph);
  ASSERT_EQ(result.distance, 24);
}

TEST(AntsAlgorithmTests, TestError_1) {
  s21::Graph graph;
  ASSERT_THROW(s21::GraphAlgorithms::SolveTravelingSalesmanProblem(graph),
               s21::IncorrectGraphError);
}

TEST(AntsAlgorithmTests, TestError_2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/dfs_graph_test.txt");
  ASSERT_THROW(s21::GraphAlgorithms::SolveTravelingSalesmanProblem(graph),
               s21::GraphAlgorithmsError);
}

TEST(AntsAlgorithmTests, TestError_3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/test_data/correct_graph_5.txt");
  ASSERT_THROW(s21::GraphAlgorithms::SolveTravelingSalesmanProblem(graph),
               s21::GraphAlgorithmsError);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}