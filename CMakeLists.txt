cmake_minimum_required(VERSION 2.8)
project( image_app )

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/qt5")

find_package( OpenCV REQUIRED )
find_package( Qt5 REQUIRED COMPONENTS Core Gui Widgets )

include_directories("include")
qt5_wrap_cpp(project_source_moc ${project_headers})

add_executable(image_app src/main.cpp src/Input.cpp src/Image.cpp)

qt5_use_modules(${PROJECT_NAME} Quick Core)

target_link_libraries(image_app ${OpenCV_LIBS} Qt5::Widgets Qt5::Gui Qt5::Core)
