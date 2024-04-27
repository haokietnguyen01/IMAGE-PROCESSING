#include "serialize.hpp"

void ipb::serialization::Serialize(const cv::Mat &m,
                                   const std::string &filename) {
  std::ofstream file(filename, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Failed to open file for writing: " << filename << std::endl;
    return;
  }

  int rows = m.rows;
  int cols = m.cols;
  int type = m.type();

  file.write(reinterpret_cast<const char *>(&rows), sizeof(int));
  file.write(reinterpret_cast<const char *>(&cols), sizeof(int));
  file.write(reinterpret_cast<const char *>(&type), sizeof(int));

  if (m.isContinuous()) {
    file.write(reinterpret_cast<const char *>(m.data),
               rows * cols * m.elemSize());
  } else {
    for (int i = 0; i < rows; ++i) {
      file.write(reinterpret_cast<const char *>(m.ptr(i)), cols * m.elemSize());
    }
  }

  file.close();
}

cv::Mat ipb::serialization::Deserialize(const std::string &filename) {
  std::ifstream file(filename, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Failed to open file for reading: " << filename << std::endl;
    return cv::Mat();
  }

  int rows, cols, type;
  file.read(reinterpret_cast<char *>(&rows), sizeof(int));
  file.read(reinterpret_cast<char *>(&cols), sizeof(int));
  file.read(reinterpret_cast<char *>(&type), sizeof(int));

  cv::Mat m(rows, cols, type);

  if (m.isContinuous()) {
    file.read(reinterpret_cast<char *>(m.data), rows * cols * m.elemSize());
  } else {
    for (int i = 0; i < rows; ++i) {
      file.read(reinterpret_cast<char *>(m.ptr(i)), cols * m.elemSize());
    }
  }

  file.close();

  return m;
}
