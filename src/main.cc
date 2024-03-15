#include "view/view.h"

int main() {
  s21::Model model;
  s21::Controller controller(&model);
  s21::View view(&controller);
  view.StartEventLoop();
  return 0;
}