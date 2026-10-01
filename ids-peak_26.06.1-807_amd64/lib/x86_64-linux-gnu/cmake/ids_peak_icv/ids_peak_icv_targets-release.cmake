#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ids_peak_icv::ids_peak_icv_c" for configuration "Release"
set_property(TARGET ids_peak_icv::ids_peak_icv_c APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ids_peak_icv::ids_peak_icv_c PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/x86_64-linux-gnu/libids_peak_icv.so.1.5.0.11292"
  IMPORTED_SONAME_RELEASE "libids_peak_icv.so.1"
  )

list(APPEND _cmake_import_check_targets ids_peak_icv::ids_peak_icv_c )
list(APPEND _cmake_import_check_files_for_ids_peak_icv::ids_peak_icv_c "${_IMPORT_PREFIX}/lib/x86_64-linux-gnu/libids_peak_icv.so.1.5.0.11292" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
