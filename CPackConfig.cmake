# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


SET(CPACK_BINARY_7Z "")
SET(CPACK_BINARY_BUNDLE "")
SET(CPACK_BINARY_CYGWIN "")
SET(CPACK_BINARY_DEB "")
SET(CPACK_BINARY_DRAGNDROP "")
SET(CPACK_BINARY_IFW "")
SET(CPACK_BINARY_NSIS "")
SET(CPACK_BINARY_OSXX11 "")
SET(CPACK_BINARY_PACKAGEMAKER "")
SET(CPACK_BINARY_RPM "")
SET(CPACK_BINARY_STGZ "")
SET(CPACK_BINARY_TBZ2 "")
SET(CPACK_BINARY_TGZ "")
SET(CPACK_BINARY_TXZ "")
SET(CPACK_BINARY_TZ "")
SET(CPACK_BINARY_WIX "")
SET(CPACK_BINARY_ZIP "")
SET(CPACK_CMAKE_GENERATOR "Unix Makefiles")
SET(CPACK_COMPONENTS_ALL "libs;devel;doc")
SET(CPACK_COMPONENTS_ALL_SET_BY_USER "TRUE")
SET(CPACK_COMPONENT_DEV_DEPENDS "libs")
SET(CPACK_COMPONENT_DEV_DESCRIPTION "Development header files and libraries, as well as cmake config files.")
SET(CPACK_COMPONENT_DEV_DISPLAY_NAME "Development files")
SET(CPACK_COMPONENT_DEV_GROUP "Development")
SET(CPACK_COMPONENT_DOCS_DESCRIPTION "User Documentation")
SET(CPACK_COMPONENT_DOCS_DISPLAY_NAME "Documents")
SET(CPACK_COMPONENT_DOCS_GROUP "Documentation")
SET(CPACK_COMPONENT_INSTALL "ON")
SET(CPACK_COMPONENT_LIBS_DEPENDS "doc")
SET(CPACK_COMPONENT_LIBS_DESCRIPTION "Runtime libraries.")
SET(CPACK_COMPONENT_LIBS_DISPLAY_NAME "Libraries")
SET(CPACK_COMPONENT_LIBS_GROUP "Runtime")
SET(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
SET(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
SET(CPACK_DEBIAN_PACKAGE_CONFLICTS "")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Remy Saissy <remy.saissy@gmail.com>")
SET(CPACK_GENERATOR "TGZ;DEB")
SET(CPACK_INSTALL_CMAKE_PROJECTS "/home/remy/Projects/perso/os/examour-exokernel;Project;ALL;/")
SET(CPACK_INSTALL_PREFIX "/usr/local")
SET(CPACK_MODULE_PATH "/home/remy/Projects/perso/os/examour-exokernel/cmake;/home/remy/Projects/perso/os/examour-exokernel/libs/libslds/../cmake;/home/remy/Projects/perso/os/examour-exokernel/libs/libslds/cmake")
SET(CPACK_NSIS_DISPLAY_NAME "slds 0.0.0")
SET(CPACK_NSIS_INSTALLER_ICON_CODE "")
SET(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
SET(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
SET(CPACK_NSIS_PACKAGE_NAME "slds 0.0.0")
SET(CPACK_OSX_PACKAGE_VERSION "10.5")
SET(CPACK_OUTPUT_CONFIG_FILE "/home/remy/Projects/perso/os/examour-exokernel/CPackConfig.cmake")
SET(CPACK_PACKAGE_CONTACT "Remy Saissy <remy.saissy@gmail.com>")
SET(CPACK_PACKAGE_DEFAULT_LOCATION "/")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake-3.2/Templates/CPack.GenericDescription.txt")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Examour")
SET(CPACK_PACKAGE_FILE_NAME "slds-0.0.0-Linux")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "slds 0.0.0")
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "slds 0.0.0")
SET(CPACK_PACKAGE_NAME "slds")
SET(CPACK_PACKAGE_RELOCATABLE "true")
SET(CPACK_PACKAGE_VENDOR "https://github.com/remysaissy/examour-exokernel")
SET(CPACK_PACKAGE_VERSION "0.0.0")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CPACK_RESOURCE_FILE_LICENSE "/usr/share/cmake-3.2/Templates/CPack.GenericLicense.txt")
SET(CPACK_RESOURCE_FILE_README "/usr/share/cmake-3.2/Templates/CPack.GenericDescription.txt")
SET(CPACK_RESOURCE_FILE_WELCOME "/usr/share/cmake-3.2/Templates/CPack.GenericWelcome.txt")
SET(CPACK_RPM_COMPONENT_INSTALL "ON")
SET(CPACK_RPM_PACKAGE_DEBUG "0")
SET(CPACK_RPM_PACKAGE_GROUP "Development/Libraries")
SET(CPACK_RPM_PACKAGE_LICENSE "GPL")
SET(CPACK_RPM_PACKAGE_VERSION "0.0.0")
SET(CPACK_SET_DESTDIR "OFF")
SET(CPACK_SOURCE_7Z "")
SET(CPACK_SOURCE_CYGWIN "")
SET(CPACK_SOURCE_GENERATOR "TBZ2;TGZ;TXZ;TZ")
SET(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/home/remy/Projects/perso/os/examour-exokernel/CPackSourceConfig.cmake")
SET(CPACK_SOURCE_TBZ2 "ON")
SET(CPACK_SOURCE_TGZ "ON")
SET(CPACK_SOURCE_TXZ "ON")
SET(CPACK_SOURCE_TZ "ON")
SET(CPACK_SOURCE_ZIP "OFF")
SET(CPACK_SYSTEM_NAME "Linux")
SET(CPACK_TOPLEVEL_TAG "Linux")
SET(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/home/remy/Projects/perso/os/examour-exokernel/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
