#-----------------------------------------------------------
#   Copyright 2002-2017 (c) Alkaline Games LLC
#
#   This Source Code Form is subject to the terms of the Mozilla Public
#   License, v. 2.0. If a copy of the MPL was not distributed with this
#   file, You can obtain one at http://mozilla.org/MPL/2.0/.
#-----------------------------------------------------------
#       file:   makefile
#    project:   Beach Lifecycle
#   platform:   independent
#     format:   GNU Make
#    authors:   Christopher Augustus
#-----------------------------------------------------------
#   Build the lifecycle tests.
#-----------------------------------------------------------

#---------------------------------------
#    variables and rules
#---------------------------------------

COMPONENT := test_lifecycle

PARENT_RELATIVE_PATH := ..

include $(PARENT_RELATIVE_PATH)/make_include_parent
include $(BEACH_DEP_DIR)/make_include_cppunit
include $(BUILD_DIR)/make_include_settings

#---------------------------------------
#   intermediate targets
#---------------------------------------

OBJECTS :=\
 $(OBJECTS_DIR)/test_lifecycle_main.o\
 $(OBJECTS_DIR)/test_allocation_center.o\
 $(OBJECTS_DIR)/test_object_identification.o

LINK_LIBS :=\
 -lbeach_lifecycle\
 -lbeach_invocation\
 -lbeach_expression\
 -lbeach_collection\
 -lbeach_chain\
 -lbeach_atoms\
 $(LINK_LIBS)

#---------------------------------------
#   targets
#---------------------------------------

include $(BUILD_DIR)/make_include_target_executable
	
#---------------------------------------
# (end of file)	 			
