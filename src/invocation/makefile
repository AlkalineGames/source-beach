#-----------------------------------------------------------
#   Copyright 2004-2017 (c) Alkaline Games LLC
#
#   This Source Code Form is subject to the terms of the Mozilla Public
#   License, v. 2.0. If a copy of the MPL was not distributed with this
#   file, You can obtain one at http://mozilla.org/MPL/2.0/.
#-----------------------------------------------------------
#       file:   makefile
#    project:   Beach Invocation
#   platform:   independent
#     format:   GNU Make
#    authors:   Christopher Augustus
#-----------------------------------------------------------
#   Build the invocation library.
#-----------------------------------------------------------

#---------------------------------------
#    variables and rules
#---------------------------------------

COMPONENT := invocation

PARENT_RELATIVE_PATH := ..

include $(PARENT_RELATIVE_PATH)/make_include_parent
include $(BUILD_DIR)/make_include_settings

#---------------------------------------
#   intermediate targets
#---------------------------------------

OBJECTS :=\
 $(OBJECTS_DIR)/command_abstract.o\
 $(OBJECTS_DIR)/command_call_static.o\
 $(OBJECTS_DIR)/command_tracked_abstract.o\
 $(OBJECTS_DIR)/command_trigger.o\
 $(OBJECTS_DIR)/invocation_templates.o\
 $(OBJECTS_DIR)/text_command.o\
 $(OBJECTS_DIR)/text_command_regex.o

#---------------------------------------
#   targets
#---------------------------------------

include $(BUILD_DIR)/make_include_target_library
	
#---------------------------------------
# (end of file)	 			
