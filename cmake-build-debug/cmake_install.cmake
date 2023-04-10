<<<<<<< HEAD
# Install script for directory: C:/Users/samue/OneDrive - Universidade do Porto/desktop/Nova pasta/ProjetoDA1
=======
# Install script for directory: C:/Users/Guilherme Ribeiro/Desktop/FEUP/DA/DAProject
>>>>>>> 7c8ef1c97ce35ed79fedbcaa088c9cf0f3ea207f

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/DAProject")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
<<<<<<< HEAD
  set(CMAKE_OBJDUMP "C:/Program Files/JetBrains/CLion 2022.2.3/bin/mingw/bin/objdump.exe")
=======
  set(CMAKE_OBJDUMP "C:/Users/Guilherme Ribeiro/AppData/Local/JetBrains/Toolbox/apps/CLion/ch-0/222.4167.35/bin/mingw/bin/objdump.exe")
>>>>>>> 7c8ef1c97ce35ed79fedbcaa088c9cf0f3ea207f
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
<<<<<<< HEAD
file(WRITE "C:/Users/samue/OneDrive - Universidade do Porto/desktop/Nova pasta/ProjetoDA1/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
=======
file(WRITE "C:/Users/Guilherme Ribeiro/Desktop/FEUP/DA/DAProject/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
>>>>>>> 7c8ef1c97ce35ed79fedbcaa088c9cf0f3ea207f
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
