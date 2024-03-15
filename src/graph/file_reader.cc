#include "file_reader.h"

namespace s21 {

Matrix FileReader::ReadData(const std::string& path) {
  std::ifstream file;
  Matrix res;
  int size = 0;
  file.open(path);
  if (!file.is_open()) {
    throw OpenFileError("Error: Can't open the file!");
  }
  try {
    file >> size;
    if (file.fail() || size <= 0) {
      throw FileContentError("Error: Incorrect graph size!");
    }
    res.SetRows(size);
    res.SetColumns(size);
    for (int i = 0; i < res.GetRows(); i++) {
      for (int j = 0; j < res.GetColumns(); j++) {
        file >> res(i, j);
        if (file.fail()) {
          throw FileContentError("Error: Wrong matrix data!");
        }
      }
    }
  } catch (...) {
    file.close();
    throw;
  }
  file.close();
  return res;
}
}  // namespace s21