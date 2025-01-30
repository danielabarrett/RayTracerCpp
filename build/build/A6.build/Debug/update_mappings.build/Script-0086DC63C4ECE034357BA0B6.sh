#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/danielbarrett/glm/glfw-3.3.9/src
  /Applications/CMake.app/Contents/bin/cmake -P /Users/danielbarrett/glm/glfw-3.3.9/CMake/GenerateMappings.cmake mappings.h.in mappings.h
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/danielbarrett/glm/glfw-3.3.9/src
  /Applications/CMake.app/Contents/bin/cmake -P /Users/danielbarrett/glm/glfw-3.3.9/CMake/GenerateMappings.cmake mappings.h.in mappings.h
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/danielbarrett/glm/glfw-3.3.9/src
  /Applications/CMake.app/Contents/bin/cmake -P /Users/danielbarrett/glm/glfw-3.3.9/CMake/GenerateMappings.cmake mappings.h.in mappings.h
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/danielbarrett/glm/glfw-3.3.9/src
  /Applications/CMake.app/Contents/bin/cmake -P /Users/danielbarrett/glm/glfw-3.3.9/CMake/GenerateMappings.cmake mappings.h.in mappings.h
fi

