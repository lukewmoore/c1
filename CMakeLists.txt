cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BASEPATH "${CMAKE_SOURCE_DIR}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3 -O0")

# add custom flags
# -DCFLAGS_GFX_SW_PERSP -DCFLAGS_DRAW_EXTENSIONS -DCFLAGS_GOOL_DEBUG
add_definitions(-DCFLAGS_GFX_SW_PERSP -DCFLAGS_DRAW_EXTENSIONS -DCFLAGS_GOOL_DEBUG)
# -g3 -O0

project(c1)

find_package(SDL2 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(FluidSynth CONFIG REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB REQUIRED glib-2.0)

# Add these lines to properly include glib
include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})

set(SRC_FILES src/ns.c
    src/pad.c
    src/math.c
    src/audio.c
    src/midi.c
    src/cam.c
    src/solid.c
    src/slst.c
    src/level.c
    src/misc.c
    src/gfx.c
    src/gool.c
    src/pbak.c
    src/title.c
    src/main.c
    src/pc/init.c
    src/pc/math.c
    src/pc/pad.c
    src/pc/time.c
    src/pc/gfx/tex.c
    src/pc/gfx/soft.c
    src/pc/gfx/gl.c
    src/pc/sound/util.c
    src/pc/sound/midi.c
    src/pc/sound/audio.c
    src/util/list.c
    src/util/tree.c
    src/ext/lib/refl.c
    src/ext/refl.c
    src/ext/disgool.c)

add_executable(c1 ${SRC_FILES})

# Add compile options for glib
target_compile_options(c1 PRIVATE ${GLIB_CFLAGS_OTHER})

target_link_libraries(c1
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_link_libraries(c1 PRIVATE GLEW::GLEW)
target_link_libraries(c1 PRIVATE FluidSynth::libfluidsynth)
target_link_libraries(c1 PRIVATE ${GLIB_LIBRARIES})

add_custom_command(OUTPUT result COMMAND FluidSynth::fluidsynth ARGS ...)
