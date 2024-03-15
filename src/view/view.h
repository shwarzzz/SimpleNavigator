#ifndef A2_SIMPLE_NAVIGATOR_SRC_VIEW_VIEW_H_

#define A2_SIMPLE_NAVIGATOR_SRC_VIEW_VIEW_H_

#include "../controller/controller.h"

namespace s21 {

enum Choice {
  kLoad = 1,
  kSave = 2,
  kBreadth = 3,
  kDepth = 4,
  kSearchPath = 5,
  kSearchAll = 6,
  kSpanningTree = 7,
  kSalesman = 8,
  kPrintGraph = 9,
  kExit = 0,
  kNone = -1
};

class View {
 public:
  View() = delete;
  View(Controller* controller) : controller_(controller) {}

  void StartEventLoop();

  void DisplayMenu();

  void PrintVector(const std::vector<int>& src);

  int PerformChoice();

  int PerformVertexNumberInput(std::string pos);
  std::string PerformPathInput();

 private:
  Controller* controller_;
};
}  // namespace s21
#endif