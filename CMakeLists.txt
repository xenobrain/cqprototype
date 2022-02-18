cmake_minimum_required(VERSION 3.21)
project(cqprototype)

file(GLOB_RECURSE ENGINE_SOURCE ${CMAKE_SOURCE_DIR}/engine/source/*.cpp ${CMAKE_SOURCE_DIR}/engine/ext/glad.c)
file(GLOB_RECURSE GAME_SOURCE ${CMAKE_SOURCE_DIR}/game/source/*.cpp)
file(COPY ${CMAKE_SOURCE_DIR}/game/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(SDL2 REQUIRED)
find_package(Vulkan REQUIRED)

add_executable(${PROJECT_NAME} ${GAME_SOURCE} ${ENGINE_SOURCE})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_SDL2=1 RENDERER_VULKAN=1 AUDIO_MINIAUDIO=1)

target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/engine/ext/mruby/build/host/lib)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/engine/source ${CMAKE_SOURCE_DIR}/engine/ext ${CMAKE_SOURCE_DIR}/engine/ext/glad ${install_dir}/include ${CMAKE_SOURCE_DIR}/engine/ext/mruby/include)

if (EMSCRIPTEN)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "index" SUFFIX ".html")
    target_link_options(${PROJECT_NAME} PRIVATE "-s USE_SDL=2 ALLOW_MEMORY_GROWTH=1")
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "--preload-file assets")
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main mruby)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static Vulkan::Headers mruby)
endif()