cmake_minimum_required(VERSION 3.10)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 COMPONENTS Core Gui QuickControls2 QuickWidgets REQUIRED)
find_package(Qt5Gui ${QT_MIN_VERSION} CONFIG REQUIRED Private)
qt5_add_resources(RESOURCES qml/cluster-gauges.qrc qml/images/images.qrc)
QT5_WRAP_CPP(MOC_FILES include/your_stuff.hpp)
find_package(Qt5 COMPONENTS Core Quick QuickControls2 REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB appdisplay_src "src/*.cpp")
add_executable(display main.cpp ${appdisplay_src} ${RESOURCES} ${MOC_FILES} )


# qt5_add_resources(RCC_SOURCES qml/cluster-gauges.qrc)
# target_link_libraries(display PUBLIC Qt5::Core Qt5::QuickControls2)

include_directories(include
                    ${CMAKE_CURRENT_SOURCE_DIR}/include/
                    include_directories(${Qt5Gui_PRIVATE_INCLUDE_DIRS})
                    ${QTAPPFW_INCLUDE_DIRS}
                    ../Common/include)
target_link_libraries(display
	#    canio
    Qt5::Core
    Qt5::QuickControls2
    Qt5::QuickWidgets
    ${QTAPPFW_LIBRARIES}
)