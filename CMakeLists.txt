cmake_minimum_required(VERSION 3.16)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# prevent installing to system directories. 
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE INTERNAL "")

# Declare the project
project(REDBattle)

# Set the name of the executable
set(EXECUTABLE_NAME ${PROJECT_NAME})

# Create an executable
add_executable(${EXECUTABLE_NAME})

target_include_directories(${EXECUTABLE_NAME} 
PUBLIC
	src/AALib/
	src/Game/
)
target_sources(${EXECUTABLE_NAME} 
PRIVATE 
    src/main.cpp
	src/AALib/Base/sys_Collision.cpp
	src/AALib/Base/Jon/JonCommon.cpp
	src/AALib/Base/Jon/tl_Jon.cpp
	src/AALib/Common/cmn_hashex.cpp
	src/AALib/Common/tl_Filepack.cpp
	src/AALib/Common/tl_RandMT.cpp
	src/Game/REDGameCommon.cpp
	src/Game/Battle/battle_TeamManager.cpp
	src/Game/Battle/battle_ObjectManager.cpp
	src/Game/Battle/Object/obj_Base.cpp
	src/Game/Battle/Object/obj_BBScript.cpp
	src/Game/Battle/Object/Char/char_Base.cpp
	src/Game/Scene/scene_Battle.cpp
	src/Game/Scene/scene_Base.cpp
	src/Game/System/game_key.cpp
)

# use C++11
target_compile_features(${EXECUTABLE_NAME} PUBLIC cxx_std_20)

if(CMAKE_SYSTEM_NAME MATCHES Emscripten)
	set(CMAKE_EXECUTABLE_SUFFIX ".html" CACHE INTERNAL "")
endif()

# If targeting Windows UWP, enable Windows Runtime Compilation
# if using a C++ version older than C++20, you also need /ZW
if(WINDOWS_STORE)
    target_compile_options(${EXECUTABLE_NAME} PUBLIC "/EHsc")
endif()

# Configure SDL by calling its CMake file.
# we use EXCLUDE_FROM_ALL so that its install targets and configs don't
# pollute upwards into our configuration.
add_subdirectory(SDL EXCLUDE_FROM_ALL)

# Link SDL to our executable. This also makes its include directory available to us. 
target_link_libraries(${EXECUTABLE_NAME} PUBLIC SDL3::SDL3)
target_compile_definitions(${EXECUTABLE_NAME} PUBLIC SDL_MAIN_USE_CALLBACKS)

install(TARGETS ${EXECUTABLE_NAME} BUNDLE DESTINATION ./install)

