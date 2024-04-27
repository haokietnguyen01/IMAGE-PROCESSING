#include "serialize.hpp"
#include <gtest/gtest.h>

// Test fixture class
class SerializationTest : public ::testing::Test {
protected:
  // Set up the test case
  virtual void SetUp() override {
    // Create an example matrix
    example_matrix = (cv::Mat_<int>(2, 3) << 1, 2, 3, 4, 5, 6);
    filename = "example_data";
  }

  // Tear down the test case
  virtual void TearDown() override {
    // Delete the example data file if it exists
    std::remove(filename.c_str());
  }

  // Variables used in the test case
  cv::Mat example_matrix;
  std::string filename;
};

// Test case to check serialization and deserialization
TEST_F(SerializationTest, SerializeDeserializeTest) {
  
  // Serialize the example matrix
  ipb::serialization::Serialize(example_matrix, filename);

  // Deserialize the matrix from the file
  cv::Mat deserialized_matrix = ipb::serialization::Deserialize(filename);

  // Check if the matrices are equal
  EXPECT_EQ(example_matrix.rows, deserialized_matrix.rows);
  EXPECT_EQ(example_matrix.cols, deserialized_matrix.cols);
  EXPECT_EQ(cv::countNonZero(example_matrix != deserialized_matrix), 0);
}

// Main function to run all the tests
int main(int argc, char **argv) {
  // Initialize the testing framework
  ::testing::InitGoogleTest(&argc, argv);
  // Run all tests
  return RUN_ALL_TESTS();
}
