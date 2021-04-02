set (encoder_sources
  encoder-core.cc encoder-core.h
  encoder-types.h encoder-types.cc
  encoder-params.h encoder-params.cc
  encoder-context.h encoder-context.cc
  encoder-syntax.h encoder-syntax.cc
  encoder-intrapred.h encoder-intrapred.cc
  encoder-motion.h encoder-motion.cc
  encpicbuf.h encpicbuf.cc
  sop.h sop.cc
)

add_subdirectory (algo)
#osm: renamed target encoder to libde265.encoder so to prevent name clash if parent project is also using x265 project
add_library(libde265.encoder OBJECT ${encoder_sources})
set(ENCODER_OBJECTS $<TARGET_OBJECTS:libde265.encoder> ${ALGO_OBJECTS} PARENT_SCOPE)

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
  SET_TARGET_PROPERTIES(libde265.encoder PROPERTIES COMPILE_FLAGS "-fPIC")
endif(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
