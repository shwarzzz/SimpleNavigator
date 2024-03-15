#include "view.h"

namespace s21 {
void View::DisplayMenu() {
  std::cout << std::endl;
  std::cout << "=========" << std::endl;
  std::cout << " M E N U " << std::endl;
  std::cout << "=========" << std::endl;
  std::cout << "1. Load the original graph from a file" << std::endl;
  std::cout << "2. Save the original graph in the dot file" << std::endl;
  std::cout << "3. Perform graph traversal in breadth" << std::endl;
  std::cout << "4. Perform graph traversal in depth" << std::endl;
  std::cout << "5. Search for the shortest path between any two vertices"
            << std::endl;
  std::cout << "6. Search for the shortest paths between all pairs of "
               "vertices in the graph"
            << std::endl;
  std::cout << "7. Search for the minimal spanning tree in the graph"
            << std::endl;
  std::cout << "8. Solve the salesman problem" << std::endl;
  std::cout << "9. Print current graph" << std::endl;
  std::cout << "0. Quit" << std::endl << std::endl;
}

void View::PrintVector(const std::vector<int>& src) {
  if (!src.empty()) {
    std::cout << "Result: ";
    for (size_t i = 0; i < src.size(); i++) {
      std::cout << src[i];
      if (i != src.size() - 1) {
        std::cout << " ";
      }
    }
    std::cout << ";\n";
  }
}

int View::PerformChoice() {
  int choice;
  std::cin.clear();
  std::cout << "Input a menu item digit: ";
  std::cin >> choice;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return kNone;
  }
  return choice;
}

int View::PerformVertexNumberInput(std::string pos) {
  int number;
  std::cout << "Enter the " << pos << " vertex number: ";
  std::cin >> number;
  while (std::cin.fail()) {
    std::cout << "Error: Incorrect input data!" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter the " << pos << " vertex number: ";
    std::cin >> number;
  }
  return number;
}

std::string View::PerformPathInput() {
  std::string str;
  std::cout << "Enter the path to the file: ";
  std::cin >> str;
  return str;
}

void View::StartEventLoop() {
  int start;
  int end;
  Choice current_choice;
  while (true) {
    DisplayMenu();
    current_choice = static_cast<Choice>(PerformChoice());
    if (current_choice == kLoad) {
      controller_->LoadGraphFromFile(PerformPathInput());
      std::cout << controller_->GetStatus() << std::endl;
      controller_->PrintGraph();
    } else if (current_choice == kSave) {
      controller_->SaveGraphToFile(PerformPathInput());
      std::cout << controller_->GetStatus() << std::endl;
    } else if (current_choice == kBreadth) {
      start = PerformVertexNumberInput("start");
      PrintVector(controller_->BreadthFirstSearch(start));
      std::cout << controller_->GetStatus() << std::endl;
    } else if (current_choice == kDepth) {
      start = PerformVertexNumberInput("start");
      PrintVector(controller_->DepthFirstSearch(start));
      std::cout << controller_->GetStatus() << std::endl;
    } else if (current_choice == kSearchPath) {
      start = PerformVertexNumberInput("start");
      end = PerformVertexNumberInput("end");
      std::cout << "Result: "
                << controller_->FindShortestPathBetweenVertices(start, end)
                << std::endl;
      std::cout << controller_->GetStatus() << std::endl;
    } else if (current_choice == kSearchAll) {
      std::cout << "Resulting matrix:" << std::endl;
      std::cout << controller_->FindShortestPathBetweenAllVertices()
                << std::endl;
      std::cout << controller_->GetStatus() << std::endl;
    } else if (current_choice == kSpanningTree) {
      std::cout << "Resulting matrix:" << std::endl;
      std::cout << controller_->FindLeastSpanningTree() << std::endl;
      std::cout << controller_->GetStatus() << std::endl;
    } else if (current_choice == kSalesman) {
      std::cout << controller_->SolveTSMProblem();
      std::cout << controller_->GetStatus() << std::endl;
    } else if (current_choice == kPrintGraph) {
      controller_->PrintGraph();
    } else if (current_choice == kExit) {
      std::cout << "Bye!" << std::endl;
      return;
    } else {
      std::cout << "Error: Wrong menu command!";
      continue;
    }
  }
}

}  // namespace s21