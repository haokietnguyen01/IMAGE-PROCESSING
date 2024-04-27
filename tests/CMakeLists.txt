# find_package()

# add_library(sifts_internal SHARED sifts_internal.cpp)
# target_link_libraries(sifts_internal ${OpenCV_LIBS})

# set(TEST_BINARY ${PROJECT_NAME}_test)
# add_executable(${TEST_BINARY}
#                test_serialize.cpp
#             #    test_convert_dataset.cpp
#                test_main.cpp)

# # target_link_libraries(${TEST_BINARY}
# #                       convert_dataset
# #                       mat_serialization
# #                       sifts_internal
# #                       )

find_package(GTest REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(
    runTest 
    test_serialize.cpp
    ../src/serialize.cpp
    test_convert_dataset.cpp
    ../src/convert_dataset.cpp
    )

target_link_libraries(
    runTest
    GTest::gtest_main
    ${OpenCV_LIBS}
)