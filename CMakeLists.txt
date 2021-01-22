cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME obs-rtss)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MFC_FLAG 2)

set(${PROJECT_NAME}_HEADERS
	"RTSSSharedMemoryInterface.h"
)

set(${PROJECT_NAME}_SOURCES
	"obs-rtss.cpp"
	"RTSSSharedMemoryInterface.cpp"
)

add_library(${PROJECT_NAME} MODULE
	${${PROJECT_NAME}_HEADERS}
	${${PROJECT_NAME}_SOURCES}
)

add_definitions(-D_AFXDLL -DUNICODE -D_UNICODE)

target_precompile_headers(${PROJECT_NAME} PUBLIC
	"pch.h"
)

target_link_libraries(${PROJECT_NAME}
	libobs
	obs-frontend-api
)

include_directories(SYSTEM
	"${CMAKE_SOURCE_DIR}/UI/obs-frontend-api"
	"C:/Program Files (x86)/RivaTuner Statistics Server/SDK/Include"
)

install_obs_plugin_with_data(${PROJECT_NAME} data)
