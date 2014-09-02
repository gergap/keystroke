project(keystroke C)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

#{{{ Program configuration options
################################################################################
set(PROGRAM_NAME "Keystroke")
set(VERSION "0.0.2" CACHE STRING "Version number.")
set(VERSION_SUFFIX "" CACHE STRING "You can add version suffixes like Beta, Snapshot here.")
option(BUILD_SHARED_LIBS    "Build libraries as shared libraries"       ON)
# don't change code below this line
################################################################################
# create full product name
set(PRODUCTFULLNAME "${PRODUCTNAME}${PRODUCTCONFIG}")
# parse version parts
string(REGEX MATCHALL "[0-9]+" VERSION_PARTS ${VERSION})
list(GET VERSION_PARTS 0 MAJOR_VERSION)
list(GET VERSION_PARTS 1 MINOR_VERSION)
list(GET VERSION_PARTS 2 PATCH_VERSION)
#}}}

#{{{ General CMake configuration options
################################################################################
# get current Git revision:
# the define GIT_SHA1 can be used to compile the current
# git revision into the executable
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
################################################################################

################################################################################
# add a "d" suffix to debug versions
# This CMAKE_DEBUG_POSTFIX variable is only used for libraries.
# For applications this must be set extra using set_target_properties.
# See 'Executables' section.
set(CMAKE_DEBUG_POSTFIX "d")
if ("${CMAKE_BUILD_TYPE}" MATCHES "[Dd]ebug")
    set(CMAKE_CURRENT_POSTFIX "d")
endif()
################################################################################

################################################################################
# configure RPATH for systems which support it.
# RPATH is supported on must UNIX systems:
# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH FALSE)
# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
# the RPATH to be used when installing
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
################################################################################
#}}} General CMake configuration options

#{{{ Compiler configuration
################################################################################
# We try to compile with the highest warning level with all compilers.
# GCC compiler
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # enable all warnings
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
    # disable certain warning (only if necessary)
    if (GCC_VERSION VERSION_GREATER 4.6 OR GCC_VERSION VERSION_EQUAL 4.6)
        # GCC>=6.4 warns about set but unused variables. This is not a bug and a
        # problem for certain variables with debug info
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-but-set-variable")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-but-set-variable")
    endif()
    if (GCC_VERSION VERSION_GREATER 4.8 OR GCC_VERSION VERSION_EQUAL 4.8)
        # GCC>=4.8 supports memory checks using address sanitizer
        OPTION(USE_ADDRESS_SANITIZER "Enabls GCC's address sanitizer to detect memory errors." OFF)
        if (USE_ADDRESS_SANITIZER)
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
        endif()
    endif()
    OPTION(BUILD_WITH_COVERAGE "Enabls GCC's coverage analysis support." OFF)
    if (BUILD_WITH_COVERAGE)
        # this builds the executables with coverage info. Don't use ccache when enabling this.
        set(CMAKE_C_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
        set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage -lgcov")
    endif()
endif()
# MSVC
if(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")
    # set highest warning level for visual studio
    if(CMAKE_C_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
    endif()
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()
#}}}

#{{{ Write config.h
string(TIMESTAMP TIMESTAMP)
configure_file(config.h.in config.h)
add_definitions(-DHAVE_CONFIG)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
#}}} Write config.h

#{{{ executables
add_executable(keystroke main.c keymap.c)
#}}}

#{{{ subprojects
add_subdirectory(gui)
#}}}

#{{{ install targets
install(TARGETS keystroke
    DESTINATION bin
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
                GROUP_EXECUTE GROUP_READ
                WORLD_EXECUTE WORLD_READ
                SETUID)

install(FILES us.map de.map DESTINATION etc/keystroke)
#}}}


# VIM modeline
# vim:ts=4:sw=4:expandtab:tw=120:fdm=marker

