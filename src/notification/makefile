#-----------------------------------------------------------
#   Copyright 2002-2017 (c) Alkaline Games LLC
#
#   This Source Code Form is subject to the terms of the Mozilla Public
#   License, v. 2.0. If a copy of the MPL was not distributed with this
#   file, You can obtain one at http://mozilla.org/MPL/2.0/.
#-----------------------------------------------------------
#       file:   makefile
#    project:   Beach Notification
#   platform:   independent
#     format:   GNU Make
#    authors:   Christopher Augustus
#-----------------------------------------------------------
#   Build the notification library.
#-----------------------------------------------------------

#---------------------------------------
#    variables and rules
#---------------------------------------

COMPONENT := notification

PARENT_RELATIVE_PATH := ..

include $(PARENT_RELATIVE_PATH)/make_include_parent
include $(BUILD_DIR)/make_include_settings

#---------------------------------------
#   intermediate targets
#---------------------------------------

OBJECTS :=\
 $(OBJECTS_DIR)/channel.o\
 $(OBJECTS_DIR)/command_distributed.o\
 $(OBJECTS_DIR)/command_distributed_group.o\
 $(OBJECTS_DIR)/command_packeted.o\
 $(OBJECTS_DIR)/event.o\
 $(OBJECTS_DIR)/event_channel.o\
 $(OBJECTS_DIR)/event_handler.o\
 $(OBJECTS_DIR)/forwarder.o\
 $(OBJECTS_DIR)/menu.o\
 $(OBJECTS_DIR)/observable_atoms.o\
 $(OBJECTS_DIR)/observable_imp.o\
 $(OBJECTS_DIR)/observable_list_of_string.o\
 $(OBJECTS_DIR)/observable_string.o\
 $(OBJECTS_DIR)/observing_pointer.o\
 $(OBJECTS_DIR)/packet_factory.o\
 $(OBJECTS_DIR)/text_buffer.o

OBJECTS_TEMPLATED :=\
 $(OBJECTS_DIR)/notification_templates.o

#---------------------------------------
#   targets
#---------------------------------------

include $(BUILD_DIR)/make_include_target_library
	
#---------------------------------------
# (end of file)	 			
