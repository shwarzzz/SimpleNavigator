#ifndef A2_SIMPLE_NAVIGATOR_SRC_GRAPH_FILE_READER_H_

#define A2_SIMPLE_NAVIGATOR_SRC_GRAPH_FILE_READER_H_

#include <fstream>
#include <string>

#include "../modules/exceptions.h"
#include "../modules/matrix.h"

namespace s21 {

class FileReader {
 public:
  FileReader(const FileReader&) = delete;
  FileReader(FileReader&&) = delete;
  FileReader& operator=(const FileReader&) = delete;
  FileReader& operator=(FileReader&&) = delete;

  static FileReader& GetInstance() {
    static FileReader instance;
    return instance;
  }

  Matrix ReadData(const std::string& path);

 private:
  FileReader() = default;
};
}  // namespace s21
#endif
