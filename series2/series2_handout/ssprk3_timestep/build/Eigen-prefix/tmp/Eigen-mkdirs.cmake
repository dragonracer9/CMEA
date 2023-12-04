# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/vikra/Desktop/CMEA/series2/series2_handout/ssprk3_timestep/build/Eigen"
  "C:/Users/vikra/Desktop/CMEA/series2/series2_handout/ssprk3_timestep/build/Eigen-prefix/src/Eigen-build"
  "C:/Users/vikra/Desktop/CMEA/series2/series2_handout/ssprk3_timestep/build/Eigen_install"
  "C:/Users/vikra/Desktop/CMEA/series2/series2_handout/ssprk3_timestep/build/Eigen-prefix/tmp"
  "C:/Users/vikra/Desktop/CMEA/series2/series2_handout/ssprk3_timestep/build/Eigen-prefix/src/Eigen-stamp"
  "C:/Users/vikra/Desktop/CMEA/series2/series2_handout/ssprk3_timestep/build/Eigen-prefix/src"
  "C:/Users/vikra/Desktop/CMEA/series2/series2_handout/ssprk3_timestep/build/Eigen-prefix/src/Eigen-stamp"
)

set(configSubDirs Debug;Release;MinSizeRel;RelWithDebInfo)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/vikra/Desktop/CMEA/series2/series2_handout/ssprk3_timestep/build/Eigen-prefix/src/Eigen-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/vikra/Desktop/CMEA/series2/series2_handout/ssprk3_timestep/build/Eigen-prefix/src/Eigen-stamp${cfgdir}") # cfgdir has leading slash
endif()
