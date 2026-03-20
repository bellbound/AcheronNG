cmake_minimum_required(VERSION 3.21)

project(AcheronNG VERSION 1.7.0 LANGUAGES CXX)

# Output folder configuration
if(DEFINED ENV{SKYRIM_FOLDER} AND IS_DIRECTORY "$ENV{SKYRIM_FOLDER}/Data")
    set(OUTPUT_FOLDER "$ENV{SKYRIM_FOLDER}/Data")
endif()

if(DEFINED ENV{SKYRIM_MODS_FOLDER} AND IS_DIRECTORY "$ENV{SKYRIM_MODS_FOLDER}")
    set(OUTPUT_FOLDER "$ENV{SKYRIM_MODS_FOLDER}/${PROJECT_NAME} ${CMAKE_BUILD_TYPE}")
endif()

# Dependencies
find_package(CommonLibSSE CONFIG REQUIRED)
find_package(directxtk CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Source files
include(cmake/headerlist.cmake)
include(cmake/sourcelist.cmake)

# Create SKSE plugin
add_commonlibsse_plugin(${PROJECT_NAME} NAME "Acheron" SOURCES ${headers} ${sources})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Acheron")

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_precompile_headers(${PROJECT_NAME} PRIVATE src/PCH.h)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        yaml-cpp
        magic_enum::magic_enum
        nlohmann_json::nlohmann_json
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        SKSE_SUPPORT_XBYAK
)

# MSVC-specific flags
if(MSVC)
    target_compile_options(${PROJECT_NAME}
        PRIVATE
            /utf-8
            /Zc:preprocessor
            /Zc:enumTypes
            /fp:contract
            /fp:except-
            /cgthreads4
            /diagnostics:caret
            /external:W0
            /we4715          # not all control paths return a value
            /wd4068          # unknown pragma 'clang'
            /wd4201          # nonstandard extension: nameless struct/union
            /wd4265          # class has virtual functions, but non-trivial destructor is not virtual
            "$<$<CONFIG:Release>:/Zi>"
            "$<$<CONFIG:Release>:/Zc:inline>"
            "$<$<CONFIG:Release>:/JMC->"
            "$<$<CONFIG:Release>:/Ob3>"
            "$<$<CONFIG:Debug>:/bigobj>"
    )
    target_link_options(${PROJECT_NAME}
        PRIVATE
            "$<$<CONFIG:Release>:/DEBUG>"
            "$<$<CONFIG:Release>:/OPT:REF>"
            "$<$<CONFIG:Release>:/OPT:ICF>"
    )
endif()
