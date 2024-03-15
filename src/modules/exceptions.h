#ifndef A2_SIMPLE_NAVIGATOR_SRC_MODULES_EXCEPTIONS_H_

#define A2_SIMPLE_NAVIGATOR_SRC_MODULES_EXCEPTIONS_H_

#include <stdexcept>

namespace s21 {

class FileContentError : public std::runtime_error {
 public:
  explicit FileContentError(const char* message)
      : std::runtime_error(message) {}
};

class OpenFileError : public std::runtime_error {
 public:
  explicit OpenFileError(const char* message) : std::runtime_error(message) {}
};

class FileExtensionError : public std::runtime_error {
 public:
  explicit FileExtensionError(const char* message)
      : std::runtime_error(message) {}
};

class IncorrectGraphError : public std::runtime_error {
 public:
  explicit IncorrectGraphError(const char* message)
      : std::runtime_error(message) {}
};

class IncorrectInputData : public std::runtime_error {
 public:
  explicit IncorrectInputData(const char* message)
      : std::runtime_error(message) {}
};

class GraphAlgorithmsError : public std::runtime_error {
 public:
  explicit GraphAlgorithmsError(const char* message)
      : std::runtime_error(message) {}
};

}  // namespace s21
#endif
