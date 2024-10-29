add_executable(${PROJECT_NAME} main.cpp)
include_directories("${PROJECT_SOURCE_DIR}/lib")

target_link_libraries(${PROJECT_NAME} PRIVATE lib)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})