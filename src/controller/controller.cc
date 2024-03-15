#include "controller.h"

namespace s21 {
void Controller::PrintGraph() { model_->PrintGraph(); }

void Controller::LoadGraphFromFile(const std::string& path) {
  model_->ReadMatrixFormFile(path);
}

void Controller::SaveGraphToFile(const std::string& path) {
  model_->SaveGraphToFile(path);
}

std::vector<int> Controller::BreadthFirstSearch(int start) {
  return model_->PerformBreadthFirstSearch(start);
}

std::vector<int> Controller::DepthFirstSearch(int start) {
  return model_->PerformDepthFirstSearch(start);
}

const std::string& Controller::GetStatus() { return model_->GetStatus(); }

int Controller::FindShortestPathBetweenVertices(int vertex1, int vertex2) {
  return model_->GetShortestPathBetweenVertices(vertex1, vertex2);
}

const Matrix Controller::FindShortestPathBetweenAllVertices() {
  return model_->GetShortestPathsBetweenAllVertices();
}

const Matrix Controller::FindLeastSpanningTree() {
  return model_->GetLeastSpanningTree();
}

const TsmResult Controller::SolveTSMProblem() {
  return model_->SolveTSMProblem();
}

}  // namespace s21