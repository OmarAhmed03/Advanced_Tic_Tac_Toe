cmake_minimum_required(VERSION 3.5)

project(Advanced-Tic-Tac-Toe VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql)

set(PROJECT_SOURCES
        main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Advanced-Tic-Tac-Toe
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        utilities/main_includes.h
        src/ui/main_screen/main_screen.h
        src/ui/main_screen/main_screen.cpp
        src/ui/main_screen/mainscreen.ui
        src/ui/game_screen/CellButton.cpp
        src/ui/game_screen/CellButton.h
        src/ui/game_screen/game_screen.h
        src/ui/game_screen/game_screen.cpp
        src/ui/game_screen/gamescreen.ui
        utilities/Buttons/Custom_Button.cpp
        utilities/Animation/animation.cpp
        utilities/Animation/animation.h
        utilities/Buttons/custom_button.h
        src/ui/main_screen/main_screen.cpp
        src/ui/main_screen/main_screen.h
        src/ui/main_screen/main_screen.cpp
        src/ui/sign_screen/sign_screen.h src/ui/sign_screen/sign_screen.cpp
        src/ui/sign_screen/signscreen.ui
        src/ui/sign_screen/database.h
        src/ui/sign_screen/database.cpp

        src/ui/history_screen/history_screen.h src/ui/history_screen/history_screen.cpp src/ui/history_screen/historyscreen.ui
        src/ui/game_screen/CellButton.cpp src/ui/game_screen/CellButton.h src/ui/game_screen/game_screen.cpp src/ui/game_screen/game_screen.h src/ui/game_screen/gamescreen.ui src/ui/history_screen/history_screen.cpp src/ui/history_screen/history_screen.h src/ui/history_screen/historyscreen.ui src/ui/main_screen/main_screen.cpp src/ui/main_screen/main_screen.h src/ui/main_screen/mainscreen.ui src/ui/sign_screen/database.cpp src/ui/sign_screen/database.h src/ui/sign_screen/sign_screen.cpp src/ui/sign_screen/sign_screen.h src/ui/sign_screen/signscreen.ui
        src/ui/replay_screen/mainwindow.ui
        src/ui/replay_screen/replayscreen.h src/ui/replay_screen/replayscreen.cpp
        src/ui/replay_screen/CellButtonR.cpp src/ui/replay_screen/CellButtonR.h
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Advanced-Tic-Tac-Toe APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Advanced-Tic-Tac-Toe SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Advanced-Tic-Tac-Toe
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Advanced-Tic-Tac-Toe PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Advanced-Tic-Tac-Toe PRIVATE Qt6::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Advanced-Tic-Tac-Toe)
endif()
set_target_properties(Advanced-Tic-Tac-Toe PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Advanced-Tic-Tac-Toe
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Advanced-Tic-Tac-Toe)
endif()
