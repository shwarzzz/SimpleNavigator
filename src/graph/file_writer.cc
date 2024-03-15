#include "file_writer.h"

namespace s21 {

void FileWriter::WriteData(const std::string& path, const Matrix& graph,
                           GraphType type) {
  CheckFileExtension(path);
  std::ofstream file;
  file.open(path);
  if (!file.is_open()) {
    throw OpenFileError("Error: Can't open the file!");
  }
  ChooseTypeAndDash(type);
  file << type_ << " graphname {\n";
  int vertexes = graph.GetRows();
  for (int i = 0; i < vertexes; i++) {
    file << "\t" << i + 1 << ";\n";
  }
  for (int i = 0; i < vertexes; i++) {
    for (int j = 0; j < vertexes; j++) {
      if (graph(i, j) != 0 &&
          ((i <= j && type == kUndirected) || type == kDirected)) {
        file << "\t" << i + 1 << dash_ << j + 1 << ";\n";
      }
    }
  }
  file << "}";
  file.close();
}

void FileWriter::ChooseTypeAndDash(GraphType type) {
  if (type == kUndirected) {
    type_ = "graph";
    dash_ = " -- ";
  } else if (type == kDirected) {
    type_ = "digraph";
    dash_ = " -> ";
  }
}

void FileWriter::CheckFileExtension(const std::string& path) {
  if (!(IsExtensionCorrect(path, kDot) || IsExtensionCorrect(path, kGv))) {
    throw FileExtensionError("Error: Wrong file extension!");
  }
}

bool FileWriter::IsExtensionCorrect(const std::string& path,
                                    const std::string& extension) {
  bool is_right = false;
  if (path.size() > extension.size()) {
    is_right = true;
    for (size_t i = 0; i < extension.size(); i++) {
      if (path[path.size() - extension.size() + i] != extension[i]) {
        is_right = false;
        break;
      }
    }
  }
  return is_right;
}

}  // namespace s21