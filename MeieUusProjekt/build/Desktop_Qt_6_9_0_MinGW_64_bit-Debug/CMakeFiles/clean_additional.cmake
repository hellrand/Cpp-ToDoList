# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\MeieUusProjekt_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MeieUusProjekt_autogen.dir\\ParseCache.txt"
  "MeieUusProjekt_autogen"
  )
endif()
