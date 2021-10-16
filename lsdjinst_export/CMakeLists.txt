cmake_minimum_required(VERSION 3.0.0)

# Create the executable target
add_executable(lsdjinst-export main.cpp instrument.hpp instrument.cpp inst_exporter.hpp inst_exporter.cpp ../common/common.hpp ../common/common.cpp)
source_group(\\ FILES main.cpp instrument.hpp instrument.cpp inst_exporter.hpp inst_exporter.cpp ../common/common.hpp ../common/common.cpp)

target_compile_features(lsdjinst-export PUBLIC cxx_std_14)
target_include_directories(lsdjinst-export PUBLIC ${PROJECT_SOURCE_DIR}/dependency)
target_link_libraries(lsdjinst-export liblsdj)

install(TARGETS lsdjinst-export DESTINATION bin)
