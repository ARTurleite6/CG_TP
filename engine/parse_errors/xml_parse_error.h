#ifndef XML_PARSE_ERROR_H
#define XML_PARSE_ERROR_H

#include <fmt/format.h>
#include <exception>

namespace errors {
class XMLParseError : public std::exception {
public:
  explicit XMLParseError(std::string_view message) : message(message) {}
  ~XMLParseError() override = default;

  [[nodiscard]] inline const char *what() const noexcept override {
    return this->message.data();
  }

private:
  std::string message;
};
}; // namespace errors

#endif // XML_PARSE_ERROR_H
