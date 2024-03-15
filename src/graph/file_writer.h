#ifndef A2_SIMPLE_NAVIGATOR_SRC_GRAPH_FILE_WRITER_H_

#define A2_SIMPLE_NAVIGATOR_SRC_GRAPH_FILE_WRITER_H_

#include <fstream>
#include <string>

#include "../modules/exceptions.h"
#include "../modules/matrix.h"
#include "graph_helper.h"

namespace s21 {
class FileWriter {
 public:
  FileWriter(const FileWriter&) = delete;
  FileWriter(FileWriter&&) = delete;
  FileWriter& operator=(const FileWriter&) = delete;
  FileWriter& operator=(FileWriter&&) = delete;

  static FileWriter& GetInstance() {
    static FileWriter instance;
    return instance;
  }

  void WriteData(const std::string& path, const Matrix& graph, GraphType type);

 private:
  void ChooseTypeAndDash(GraphType type);
  void CheckFileExtension(const std::string& path);
  bool IsExtensionCorrect(const std::string& path,
                          const std::string& extension);

  std::string type_;
  std::string dash_;
  FileWriter() = default;
  const std::string kDot = ".dot";
  const std::string kGv = ".gv";
};
}  // namespace s21

#endif