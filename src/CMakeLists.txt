cmake_minimum_required(VERSION 3.5)



########################################################################
# Setup the include and linker paths
########################################################################

include_directories (${PROJECT_INCLUDES})

########################################################################
# Build and testing
########################################################################
add_library(cpp-skeleton-core ${SOURCE_FILES})
add_executable(cpp-skeleton main.cpp)
target_link_libraries(cpp-skeleton ${PROJECT_LIBRARIES} cpp-skeleton-core)

