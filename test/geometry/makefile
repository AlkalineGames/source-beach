#-----------------------------------------------------------
#   Copyright 2012-2017 (c) Alkaline Games LLC
# 
#   This Source Code Form is subject to the terms of the Mozilla Public
#   License, v. 2.0. If a copy of the MPL was not distributed with this
#   file, You can obtain one at http://mozilla.org/MPL/2.0/.
#-----------------------------------------------------------
#       file:   makefile
#    project:   Beach Geometry
#   platform:   independent
#     format:   GNU Make
#    authors:   Christopher Augustus
#-----------------------------------------------------------
#   Build the geometry tests.
#-----------------------------------------------------------

#---------------------------------------
#    variables and rules
#---------------------------------------

COMPONENT 	:= test_geometry
LINK_MATH	:= 1

PARENT_RELATIVE_PATH := ..

include $(PARENT_RELATIVE_PATH)/make_include_parent
include $(BEACH_DEP_DIR)/make_include_cppunit
include $(BUILD_DIR)/make_include_settings

#---------------------------------------
#   intermediate targets
#---------------------------------------

OBJECTS :=\
 $(OBJECTS_DIR)/test_cuboid_aligned.o\
 $(OBJECTS_DIR)/test_geometry_main.o

OBJECTS_TEMPLATED :=\
 $(OBJECTS_DIR)/test_geometry_templates.o

LINK_LIBS :=\
 -lbeach_geometry\
 -lbeach_expression\
 -lbeach_collection\
 -lbeach_chain\
 -lbeach_atoms\
 -lbeach_atoms_allocation\
 $(LINK_LIBS)

#---------------------------------------
#   targets
#---------------------------------------

include $(BUILD_DIR)/make_include_target_executable
	
#---------------------------------------
# (end of file)	 			
