cmake_minimum_required (VERSION 3.1.0)
PROJECT (HDF5_VOL_REST_EXAMPLES)

#-----------------------------------------------------------------------------
# Apply Definitions to compiler in this directory and below
#-----------------------------------------------------------------------------
add_definitions (${HDF5_VOL_REST_EXTRA_C_FLAGS})

#-----------------------------------------------------------------------------
# Define Sources
#-----------------------------------------------------------------------------
set (examples
    rv_crtdat
    rv_rdwt
    rv_crtatt
    rv_crtgrp
    rv_crtgrpar
    rv_crtgrpd
    rv_subset
    rv_write
    rv_read
    rv_chunk_read
    rv_compound
    rv_group
    rv_select
    rv_attribute
    rv_extlink
)

foreach (example ${examples})
  if (BUILD_STATIC_LIBS)
    add_executable (${example} ${HDF5_VOL_REST_EXAMPLES_SOURCE_DIR}/${example}.c)
    TARGET_C_PROPERTIES (${example} STATIC " " " ")
    target_link_libraries (${example} PUBLIC ${HDF5_VOL_REST_LIB_TARGET} ${HDF5_LIBRARIES_TO_EXPORT})
    set_target_properties (${example} PROPERTIES FOLDER examples)
  endif ()

  if (BUILD_SHARED_LIBS)
    add_executable (${example}-shared ${HDF5_VOL_REST_EXAMPLES_SOURCE_DIR}/${example}.c)
    TARGET_C_PROPERTIES (${example}-shared SHARED " " " ")
    target_link_libraries (${example}-shared PUBLIC ${HDF5_VOL_REST_LIBSH_TARGET} ${HDF5_LIBRARIES_TO_EXPORT})
    set_target_properties (${example}-shared PROPERTIES FOLDER examples)
  endif ()

  #-----------------------------------------------------------------------------
  # Add Target(s) to CMake Install for import into other projects
  #-----------------------------------------------------------------------------
  if (HDF5_VOL_REST_EXPORTED_TARGETS)
    if (BUILD_STATIC_LIBS)
      install (
          TARGETS
              ${example}
          EXPORT
              ${HDF5_VOL_REST_EXPORTED_TARGETS}
          DESTINATION
              ${HDF5_VOL_REST_INSTALL_DATA_DIR}/rest_vol_examples COMPONENT examples
      )
    endif ()
    if (BUILD_SHARED_LIBS)
      install (
          TARGETS
              ${example}-shared
          EXPORT
              ${HDF5_VOL_REST_EXPORTED_TARGETS}
          DESTINATION
              ${HDF5_VOL_REST_INSTALL_DATA_DIR}/rest_vol_examples COMPONENT examples
      )    
    endif ()
  endif ()
endforeach (example ${examples})

add_subdirectory(hl ${PROJECT_BINARY_DIR}/examples)

if (BUILD_TESTING)
  include (${HDF5_VOL_REST_EXAMPLES_SOURCE_DIR}/CMakeTests.cmake)
endif (BUILD_TESTING)
