cmake_minimum_required(VERSION 3.5)

project(Parks_Generator)


set(CMAKE_CXX_FLAGS "-std=c++17")
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

FIND_PACKAGE(Boost COMPONENTS unit_test_framework REQUIRED)
IF (Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
  ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

add_library(polyominolib piece/polyomino.cpp)
add_library(utillib utils/polyominoGenerator.cpp utils/boardSizeFinder.cpp)


add_executable(matrixtest board/matrix.test.cpp)
target_link_libraries(matrixtest LINK_PUBLIC ${Boost_LIBRARIES})

add_executable(polyominotest piece/polyomino.test.cpp)
target_link_libraries(polyominotest LINK_PUBLIC polyominolib)
target_link_libraries(polyominotest LINK_PUBLIC ${Boost_LIBRARIES})

add_executable(generatortest utils/polyominoGenerator.test.cpp)
target_link_libraries(generatortest LINK_PUBLIC utillib)
target_link_libraries(generatortest LINK_PUBLIC polyominolib)
target_link_libraries(generatortest LINK_PUBLIC ${Boost_LIBRARIES})

add_executable(gen_0_n tools/generate_on_n.cpp)
target_link_libraries(gen_0_n LINK_PUBLIC utillib)
target_link_libraries(gen_0_n LINK_PUBLIC polyominolib)
