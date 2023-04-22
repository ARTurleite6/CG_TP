#ifndef IO_H
#define IO_H

template <std::uint32_t N>
static std::array<std::string_view, N> split_N(std::string_view str, std::string_view delimiter) {
  std::array<std::string_view, N> arr;

  std::size_t pos = 0;
  std::size_t start = 0;
  std::size_t i = 0;
  while (i < N && (pos = str.find(delimiter, start)) != std::string::npos) {
    arr[i] = str.substr(start, pos - start);
    i++;
    start = pos + 1;
  }
  if (start != std::string::npos && i < N)
    arr[i++] = str.substr(start, pos);

  return arr;
}

static void my_split(std::vector<std::string_view> &vec, std::string_view str, std::string_view delimiter) {

  std::size_t pos = 0;
  std::size_t start = 0;
  std::size_t i = 0;
  while ((pos = str.find(delimiter, start)) != std::string::npos) {
    vec.push_back(str.substr(start, pos - start));
    i++;
    start = pos + 1;
  }
  if (start != std::string::npos)
    vec.push_back(str.substr(start, pos));
}

#endif // IO_H