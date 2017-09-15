#-----------------------------------------------------------
#   Copyright 2003-2017 (c) Alkaline Games LLC
#
#   This Source Code Form is subject to the terms of the Mozilla Public
#   License, v. 2.0. If a copy of the MPL was not distributed with this
#   file, You can obtain one at http://mozilla.org/MPL/2.0/.
#-----------------------------------------------------------
#       file:   makefile
#    project:   Beach Collection
#   platform:   independent
#     format:   GNU Make
#    authors:   Christopher Augustus
#-----------------------------------------------------------
#   Build the collection unit tests.
#-----------------------------------------------------------

#---------------------------------------
#    variables and rules
#---------------------------------------

COMPONENT := test_collection

PARENT_RELATIVE_PATH := ..

include $(PARENT_RELATIVE_PATH)/make_include_parent
include $(BEACH_DEP_DIR)/make_include_cppunit
include $(BUILD_DIR)/make_include_settings

#---------------------------------------
#   intermediate targets
#---------------------------------------

OBJECTS :=\
 $(OBJECTS_DIR)/test_collection_main.o\

OBJECTS_TEMPLATED :=\
 $(OBJECTS_DIR)/test_ref_set_of_string.o\
 $(OBJECTS_DIR)/test_ref_vector.o\
 $(OBJECTS_DIR)/test_std_map.o

LINK_LIBS :=\
 -lbeach_collection\
 -lbeach_atoms\
 -lbeach_atoms_allocation\
 $(LINK_LIBS)

#---------------------------------------
#   targets
#---------------------------------------

include $(BUILD_DIR)/make_include_target_executable
	
#---------------------------------------
# (end of file)
