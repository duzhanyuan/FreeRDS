# FreeRDP X11 Server Next Generation
# xrdp-ng cmake build script
#
# Copyright 2013 Marc-Andre Moreau <marcandre.moreau@gmail.com>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set(MODULE_NAME "freerds")
set(MODULE_PREFIX "FREERDS_CORE")

set(PAM_FEATURE_TYPE "REQUIRED")
set(PAM_FEATURE_PURPOSE "authentication")
set(PAM_FEATURE_DESCRIPTION "user authentication")

find_feature(PAM ${PAM_FEATURE_TYPE} ${PAM_FEATURE_PURPOSE} ${PAM_FEATURE_DESCRIPTION})

include_directories(${PAM_INCLUDE_DIR})

include_directories(".")
include_directories("${CMAKE_SOURCE_DIR}/winpr/tools/makecert")

set(${MODULE_PREFIX}_SRCS
	freerds.c
	freerds.h
	auth.c
	core.c
	core.h
	channels.c
	channels.h
	listener.c
	pipeline.c
	process.c
	client_module.c
	server_module.c)

add_executable(${MODULE_NAME} ${${MODULE_PREFIX}_SRCS})

set(${MODULE_PREFIX}_LIBS ${PAM_LIBRARY})

list(APPEND ${MODULE_PREFIX}_LIBS freerds-module-connector)
list(APPEND ${MODULE_PREFIX}_LIBS freerds-icp)

set_complex_link_libraries(VARIABLE ${MODULE_PREFIX}_LIBS
	MONOLITHIC ${MONOLITHIC_BUILD}
	MODULE winpr
	MODULES winpr-thread winpr-synch winpr-file winpr-path winpr-sysinfo winpr-pipe winpr-environment winpr-sspicli winpr-utils winpr-crt)

set_complex_link_libraries(VARIABLE ${MODULE_PREFIX}_LIBS
	MONOLITHIC ${MONOLITHIC_BUILD}
	MODULE freerdp
	MODULES freerdp-core)
	
list(APPEND ${MODULE_PREFIX}_LIBS freerdp-server)

list(APPEND ${MODULE_PREFIX}_LIBS ${PIXMAN_LIBRARIES})

list(APPEND ${MODULE_PREFIX}_LIBS winpr-makecert-tool)

target_link_libraries(${MODULE_NAME} ${${MODULE_PREFIX}_LIBS})

install(TARGETS ${MODULE_NAME} DESTINATION ${CMAKE_INSTALL_SBINDIR})
