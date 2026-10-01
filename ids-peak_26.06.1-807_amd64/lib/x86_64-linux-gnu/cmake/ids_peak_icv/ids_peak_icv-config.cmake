
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was libicv-config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../../" ABSOLUTE)

# Use original install prefix when loaded through a "/usr move"
# cross-prefix symbolic link such as /lib -> /usr/lib.
get_filename_component(_realCurr "${CMAKE_CURRENT_LIST_DIR}" REALPATH)
get_filename_component(_realOrig "/usr/lib/x86_64-linux-gnu/cmake/ids_peak_icv" REALPATH)
if(_realCurr STREQUAL _realOrig)
  set(PACKAGE_PREFIX_DIR "/usr")
endif()
unset(_realOrig)
unset(_realCurr)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

if(NOT CMAKE_C_COMPILER)
    message(FATAL_ERROR "C language support is required but not enabled.")
endif()

find_package(ids_peak_common REQUIRED
    HINTS
    "${CMAKE_CURRENT_LIST_DIR}/.."
)

find_package(ids_peak_ipl QUIET)
include("${CMAKE_CURRENT_LIST_DIR}/ids_peak_icv_targets.cmake")

if(NOT TARGET ids_peak_icv)
    add_library(ids_peak_icv ALIAS ids_peak_icv::ids_peak_icv_cpp)
endif()

if(NOT TARGET ids_peak_icv_c)
    add_library(ids_peak_icv_c ALIAS ids_peak_icv::ids_peak_icv_c)
endif()

if(NOT TARGET ids_peak_icv::ids_peak_icv)
    add_library(ids_peak_icv::ids_peak_icv ALIAS ids_peak_icv::ids_peak_icv_cpp)
endif()

if(NOT TARGET ids_peak_icv::ids_peak_icv_cpp_dynamically_loaded_with_shared_ids_peak_ipl)

    add_library(ids_peak_icv::ids_peak_icv_cpp_dynamically_loaded_with_shared_ids_peak_ipl
        ALIAS ids_peak_icv::ids_peak_icv_cpp_dynamically_loaded) 
endif()

if (WIN32 AND NOT ids_peak_icv_DISABLE_DLL_COPY)
    function(ids_peak_icv_deploy target)
        if(TARGET ids_peak_ipl)
            message(STATUS "[${target}] Adding post build copy for ids_peak_icv dependencies")

            add_custom_command(
                TARGET ${target}
                POST_BUILD
                COMMAND
                ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:ids_peak_ipl> $<TARGET_FILE_DIR:${target}>/
                COMMENT
                "[${PROJECT_NAME}] Post build copy for ids_peak_icv dependency files"
            )
        endif()
        add_custom_command(
            TARGET ${target}
            POST_BUILD
            COMMAND
            ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:ids_peak_icv::ids_peak_icv_c> $<TARGET_FILE_DIR:${target}>/
            COMMAND
            ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE_DIR:ids_peak_icv::ids_peak_icv_c>/tbb12.dll $<TARGET_FILE_DIR:${target}>/
            COMMENT
            "[${PROJECT_NAME}] Post build copy for ids_peak_icv"
        )
    endfunction()
else()
    function(ids_peak_icv_deploy target)
    endfunction()
endif()

