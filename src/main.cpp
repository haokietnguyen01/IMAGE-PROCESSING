#include "convert_dataset.hpp"
#include "serialize.hpp"
#include <vector>

int main() {
  // Task 1

  cv::Mat image = cv::imread("../data/lenna.png", cv::IMREAD_GRAYSCALE);

  auto detector = cv::SiftFeatureDetector::create();
  std::vector<cv::KeyPoint> keypoints;
  detector->detect(image, keypoints);
  cv::Mat image_with_keypoints;
  drawKeypoints(image, keypoints, image_with_keypoints);
  auto extractor = cv::SiftDescriptorExtractor::create();
  cv::Mat descriptors;
  extractor->compute(image, keypoints, descriptors);

  ipb::serialization::Serialize(image_with_keypoints, "../data/lenna.bin");
  // Serialize the image

  cv::Mat loaded_image = ipb::serialization::Deserialize(
      "../data/lenna.bin"); // Deserialize the image

  // Task 2

  ipb::serialization::sifts::ConvertDataset("../data/freiburg/images");

  std::vector<cv::Mat> load =
      ipb::serialization::sifts::LoadDataset("../data/freiburg/bin/");
  for (const auto &img : load) {
    std ::string window_name = "Window name";
    // Create a window.
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
    cv::imshow(window_name, img); // Show image.
    cv::waitKey();                // Don't close window instantly.
                                  // std::cout << img << std::endl;
  }
  return 0;
}