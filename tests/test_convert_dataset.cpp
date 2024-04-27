#include "convert_dataset.hpp"
#include "serialize.hpp"
#include <gtest/gtest.h>

namespace {

// Test case for the ConvertDataset function
TEST(ConvertDatasetTest, BasicTest) {
  // Tạo một thư mục tạm thời để lưu trữ hình ảnh PNG để kiểm tra
  std::filesystem::path temp_dir =
      std::filesystem::temp_directory_path() / "test_images";
  std::filesystem::create_directory(temp_dir);

  // Tạo một hình ảnh PNG tạm thời để kiểm tra
  cv::Mat image(100, 100, CV_8UC1, cv::Scalar(128));
  cv::imwrite((temp_dir / "test_image.png").string(), image);

  // Chạy hàm ConvertDataset với hình ảnh PNG tạm thời
  ipb::serialization::sifts::ConvertDataset(temp_dir);

  // Kiểm tra xem tệp nhị phân đã được tạo thành công không
  std::filesystem::path bin_file = "../data/freiburg/bin/test_image.bin";
  EXPECT_TRUE(std::filesystem::exists(bin_file));
  
  // Xóa hình ảnh tạm thời và thư mục tạm thời
  std::filesystem::remove_all(temp_dir);
}

// Test case for the LoadDataset function
TEST(LoadDatasetTest, BasicTest) {
  /// Tạo một thư mục tạm thời để lưu trữ hình ảnh PNG để kiểm tra
  std::filesystem::path temp_dir = "../tests/test_data";
  std::filesystem::create_directory(temp_dir);

  // Tạo một hình ảnh PNG tạm thời để kiểm tra
  cv::Mat image(100, 100, CV_8UC1, cv::Scalar(128));
  cv::imwrite((temp_dir / "test_image.png").string(), image);

  // Chạy hàm ConvertDataset với hình ảnh PNG tạm thời
  ipb::serialization::sifts::ConvertDataset(temp_dir);

  // Chạy hàm LoadDataset với thư mục tạm thời
  std::vector<cv::Mat> dataset =
      ipb::serialization::sifts::LoadDataset("../data/freiburg/bin/");

  // Kiểm tra xem dataset có chứa ma trận không
  EXPECT_FALSE(dataset.empty());

  // Xóa tệp nhị phân tạm thời và thư mục tạm thời
  std::filesystem::remove_all(temp_dir);
  std::filesystem::remove_all("../data/freiburg/bin/");
}

TEST(LoadDatasetTest, EmptyFolderTest) {
  /// Tạo một thư mục tạm thời để lưu trữ hình ảnh PNG để kiểm tra
  std::filesystem::path temp_dir = "../tests/test_data";
  std::filesystem::create_directory(temp_dir);

  // Chạy hàm LoadDataset với thư mục tạm thời
  std::vector<cv::Mat> dataset =
      ipb::serialization::sifts::LoadDataset("../data/freiburg/bin/");

  // Kiểm tra xem dataset có chứa ma trận không
  EXPECT_TRUE(dataset.empty());

  // Xóa tệp nhị phân tạm thời và thư mục tạm thời
  std::filesystem::remove_all(temp_dir);
  std::filesystem::remove_all("../data/freiburg/bin/");
}
} // namespace
