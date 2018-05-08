# ****************************************************************************
#  Project:  Test_ContainerSync
#  Purpose:  Test project
#  Author:   NikitaFeodonit, nfeodonit@yandex.com
# ****************************************************************************
#    Copyright (c) 2018 NikitaFeodonit
#
#    This file is part of the Test_ContainerSync project.
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published
#    by the Free Software Foundation, either version 3 of the License,
#    or (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#    See the GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program. If not, see <http://www.gnu.org/licenses/>.
# ****************************************************************************

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(Test_ContainerSync CXX)
set(tcs_EXE_NAME "${PROJECT_NAME}")

set(tcs_SOURCES
  main.cpp
)

add_executable(${tcs_EXE_NAME} ${tcs_SOURCES})
set_target_properties(${tcs_EXE_NAME} PROPERTIES
  CXX_STANDARD 11
)
