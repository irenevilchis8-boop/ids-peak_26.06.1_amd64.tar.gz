cmake_minimum_required(VERSION 3.2...3.12 FATAL_ERROR)

if(POLICY CMP0076)
    cmake_policy(SET CMP0076 NEW)
endif()

project ("sequencer_live_qml_cpp")

option(USE_QT6_VERSION OFF)
option(USE_QTQUICK_COMPILER ON)

message (STATUS "[${PROJECT_NAME}] Processing ${CMAKE_CURRENT_LIST_FILE}")

if(USE_QT6_VERSION)
    set(QT_VERSION 6)
else()
    set(QT_VERSION 5)
endif()

set (CMAKE_AUTOMOC TRUE)
set (CMAKE_AUTORCC TRUE)

if (MSVC)
    set (SAMPLE_TARGET_DEFINITION_ADDENDUM WIN32)
endif ()

# Setup target executable with the same name as our project
add_executable (${PROJECT_NAME} ${SAMPLE_TARGET_DEFINITION_ADDENDUM}
    main.cpp
    backend.h
    backend.cpp
    camera.h
    camera.cpp
    acquisitionworker.h
    acquisitionworker.cpp
    imageitem.h
    imageitem.cpp
    entrylistmodel.h
    entrylistmodel.cpp
    entrylistobject.h
    entrylistobject.cpp
    imageconverterworker.h
    imageconverterworker.cpp
    modelupdatethreadworker.h
    modelupdatethreadworker.cpp
    nodelistmodel.h
    nodelistmodel.cpp
    nodelistobject.h
    nodelistobject.cpp
)

if(QT_VERSION EQUAL 6)
    set(QML_FILES
        qml6/Dialog_Error.qml
        qml6/Dialog_Folder.qml
        qml6/Dialog_RoiSize.qml
        qml6/Dialog_SaveChanges.qml
        qml6/Dialog_SequencerTrigger.qml
        qml6/main.qml
        qml6/PropertyContainer.qml
        qml6/PropertyControl_CommandButton.qml
        qml6/PropertyControl_EnumComboBox.qml
        qml6/PropertyControl_FloatSlider.qml
        qml6/ToolTip.qml
        qml6/Window_Image.qml
    )
    set(RESOURCES
        qml6.qrc
    )
else()
    set(QML_FILES
        qml5/Dialog_Error.qml
        qml5/Dialog_Folder.qml
        qml5/Dialog_RoiSize.qml
        qml5/Dialog_SaveChanges.qml
        qml5/Dialog_SequencerTrigger.qml
        qml5/main.qml
        qml5/PropertyContainer.qml
        qml5/PropertyControl_CommandButton.qml
        qml5/PropertyControl_EnumComboBox.qml
        qml5/PropertyControl_FloatSlider.qml
        qml5/ToolTip.qml
        qml5/Window_Image.qml
    )
    set(RESOURCES
        qml5.qrc
    )
endif()

target_sources(${PROJECT_NAME} PUBLIC
    ${RESOURCES}
    ${QML_FILES}
)

# Find packages
if (NOT TARGET ids_peak)
    find_package (ids_peak REQUIRED)
endif ()

if (NOT TARGET ids_peak_icv)
    find_package (ids_peak_icv REQUIRED)
endif()

find_package (Threads REQUIRED)

find_package (Qt${QT_VERSION} COMPONENTS Widgets Quick Qml REQUIRED)

set(QT_INSTALL_PREFIX "${_qt${QT_VERSION}Core_install_prefix}")

if (USE_QTQUICK_COMPILER)
    if(QT_VERSION EQUAL 6)
        qt_add_qml_module(${PROJECT_NAME}
            URI "SequencerQmlDemo"
            VERSION "1.0"
            QML_FILES ${QML_FILES}
            RESOURCES ${RESOURCES}
            # ENABLE_TYPE_COMPILER
        )
    else()
        find_package(Qt5 COMPONENTS QuickCompiler REQUIRED)
        qtquick_compiler_add_resources(RESOURCES ${RESOURCES})
    endif()
endif()

# Set include directories
target_include_directories (${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link against libraries
target_link_libraries (${PROJECT_NAME} PRIVATE
    ids_peak::ids_peak
    ids_peak_icv::ids_peak_icv
    ${CMAKE_THREAD_LIBS_INIT}
    Qt${QT_VERSION}::Widgets
    Qt${QT_VERSION}::Quick
    Qt${QT_VERSION}::Qml
)

# Call deploy functions
# These functions will add a post-build steps to your target in order to copy all needed files (e.g. DLL's) to the output directory.
ids_peak_deploy(${PROJECT_NAME})
ids_peak_icv_deploy(${PROJECT_NAME})

if ((CMAKE_CXX_COMPILER_ID MATCHES GNU) OR (CMAKE_CXX_COMPILER_ID MATCHES Clang))
    # ignore errors in headers from qt widgets include directories
    foreach (INCLUDE_DIR ${Qt5Widgets_INCLUDE_DIRS})
        if (NOT "${INCLUDE_DIR}" STREQUAL "/usr/include")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem ${INCLUDE_DIR}")
        endif ()
    endforeach ()
endif ()

# Set C++ standard to 14 (required for ids_peak)
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS NO
)

# Enable multiprocessing for MSVC
if (MSVC)
    target_compile_options (${PROJECT_NAME}
        PRIVATE "/MP"
    )
endif ()

if (WIN32)
    if(NOT WINDEPLOYQT_EXECUTABLE)
        get_target_property(_qmake_executable Qt${QT_VERSION}::qmake IMPORTED_LOCATION)
        get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
        find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")
    endif()

    # Copy Qt files to the output folder
    message (STATUS "[${PROJECT_NAME}] Add PostBuildStep for copy of the Qt libs.")
    add_custom_command (TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${WINDEPLOYQT_EXECUTABLE}"
                --no-translations
                --no-system-d3d-compiler
                --no-opengl-sw
                -qml
                --qmldir "${CMAKE_CURRENT_LIST_DIR}/qml${QT_VERSION}"
                --no-svg
                --dir $<TARGET_FILE_DIR:${PROJECT_NAME}>
                $<TARGET_FILE:${PROJECT_NAME}>
    )
endif ()

# For unix Build we need the environment variable GENICAM_GENTL32_PATH respectivily GENICAM_GENTL64_PATH to find the GenTL producer libraries.
# To set these environment variables a shell script is used. This script can be automatically generated via ids_peak_generate_starter_script.
# The shell script will be saved at ${CMAKE_CURRENT_BINARY_DIR}/${targetName}.sh and automatically copied to the output directory during post-build.

# To run the samples run this script, not the binary.
if(UNIX)
    ids_peak_generate_starter_script(${PROJECT_NAME})
endif()
