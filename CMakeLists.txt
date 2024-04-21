# CMakeList.txt : CMake project for Song Sage, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)
project (SongSage LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Add source to this project's executable.
add_executable (SongSage src/main.cpp src/songlist.cpp src/Button.cpp)
target_link_libraries(SongSage PRIVATE sfml-graphics sfml-system)
target_compile_features(SongSage PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET SongSage
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:SongSage>
        VERBATIM)
endif()

# TODO: Add tests and install targets if needed.

install(TARGETS SongSage)