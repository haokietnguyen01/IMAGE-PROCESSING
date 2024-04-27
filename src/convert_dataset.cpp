#include "convert_dataset.hpp"

void ipb::serialization::sifts::ConvertDataset(
    const std::filesystem::path &img_path) {
  if (fs::exists(img_path)) {
    // std::cout << "exist" << std::endl;
    for (const auto &f : fs::directory_iterator(img_path)) {
      std::string file_name = f.path().string();
      // std::cout << f << std::endl;
      // Tim keypoint
      cv::Mat image = cv::imread(file_name, cv::IMREAD_GRAYSCALE);
      auto detector = cv::SiftFeatureDetector::create();
      std::vector<cv::KeyPoint> keypoints;
      detector->detect(image, keypoints);
      cv::Mat image_with_keypoints;
      drawKeypoints(image, keypoints, image_with_keypoints);
      auto extractor = cv::SiftDescriptorExtractor::create();
      cv::Mat descriptors;
      extractor->compute(image, keypoints, descriptors);

      // Luu thanh folder bin

      std::string getFileName = fs::path(f).stem();

      fs::create_directories("../data/freiburg/bin/");
      // std::cout << getFileName << std::endl;
      ipb::serialization::Serialize(
          image_with_keypoints, "../data/freiburg/bin/" + getFileName + ".bin");
    }
    std::cout << "convert success!!" << std::endl;
  } else
    std::cout << "does not exist" << std::endl;
}

std::vector<cv::Mat>
ipb::serialization::sifts::LoadDataset(const std::filesystem::path &bin_path) {
  // Check if the provided path exists
  vectorMat image;

  if (fs::exists(bin_path)) {
    for (const auto &b : fs::directory_iterator(bin_path)) {
      // std::string b_path = b.path().string();
      cv::Mat img = ipb::serialization::Deserialize(b.path().string());
      if (!img.empty()) {
        image.push_back(img);
      } else {
        std::cerr << "Error file bin" << std::endl;
        return image;
      }
    }
  }
  return image;
}