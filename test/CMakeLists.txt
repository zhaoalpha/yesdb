 cmake_minimum_required(VERSION 3.16)

 set(CMAKE_CXX_STANDARD 17)

 include_directories(/usr/local/include/catch2)
 include_directories(/home/arch/dep/zstd/lib)
 find_package(Catch2 3 REQUIRED)
 find_library(ZSTD_LIBS zstd /home/arch/dep/zstd/lib REQUIRED)
 file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")
# art
 include_directories(../third_party/art)
  include_directories(../third_party/art/art)
 #picobench
 include_directories(../third_party/picobench)

 foreach (test_source ${SRC_FILES})
     get_filename_component(test_filename ${test_source} NAME)
     string(REPLACE ".cpp" "" test_name ${test_filename})
     message(STATUS, " test file = ${test_name}")
     add_executable(${test_name} ${test_source})
     target_link_libraries(${test_name}
             Catch2::Catch2WithMain
             ${ZSTD_LIBS}
             yesdb)
 endforeach ()
