#-----------------------------------------------------------
#   Copyright 2002-2017 (c) Alkaline Games LLC
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
#   Build the collection libary.
#-----------------------------------------------------------

#---------------------------------------
#    variables and rules
#---------------------------------------

COMPONENT := collection

PARENT_RELATIVE_PATH := ..

include $(PARENT_RELATIVE_PATH)/make_include_parent
include $(BUILD_DIR)/make_include_settings

#---------------------------------------
#   intermediate targets
#---------------------------------------

OBJECTS :=\
 $(OBJECTS_DIR)/list_of_string.o\
 $(OBJECTS_DIR)/ref_set_of_string.o

OBJECTS_TEMPLATED :=\
 $(OBJECTS_DIR)/collection_templates.o 

#---------------------------------------
#   targets
#---------------------------------------

include $(BUILD_DIR)/make_include_target_library
	
#---------------------------------------
# (end of file)	 			
