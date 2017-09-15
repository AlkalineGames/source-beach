#-----------------------------------------------------------
#   Copyright 2002-2017 (c) Alkaline Games LLC
#
#   This Source Code Form is subject to the terms of the Mozilla Public
#   License, v. 2.0. If a copy of the MPL was not distributed with this
#   file, You can obtain one at http://mozilla.org/MPL/2.0/.
#-----------------------------------------------------------
#       file:   makefile
#    project:   Beach Taxonomy
#   platform:   independent
#     format:   GNU Make
#    authors:   Christopher Augustus
#-----------------------------------------------------------
#   Build the taxonomy library.
#-----------------------------------------------------------

#---------------------------------------
#    variables and rules
#---------------------------------------

COMPONENT := taxonomy

PARENT_RELATIVE_PATH := ..

include $(PARENT_RELATIVE_PATH)/make_include_parent
include $(BUILD_DIR)/make_include_settings

#---------------------------------------
#   intermediate targets
#---------------------------------------

OBJECTS :=\
 $(OBJECTS_DIR)/property_catalog.o\
 $(OBJECTS_DIR)/property_group.o\
 $(OBJECTS_DIR)/property_group_collection.o\
 $(OBJECTS_DIR)/property_imp.o\
 $(OBJECTS_DIR)/property_pointer.o\
 $(OBJECTS_DIR)/property_reals.o\
 $(OBJECTS_DIR)/property_set.o\
 $(OBJECTS_DIR)/property_set_of_strings.o\
 $(OBJECTS_DIR)/property_stringex.o\
 $(OBJECTS_DIR)/taxonomy_manager.o

#---------------------------------------
#   targets
#---------------------------------------

include $(BUILD_DIR)/make_include_target_library
	
#---------------------------------------
# (end of file)	 			
