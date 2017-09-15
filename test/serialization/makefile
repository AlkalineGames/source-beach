#-----------------------------------------------------------
#   Copyright 2004-2017 (c) Alkaline Games LLC
#
#   This Source Code Form is subject to the terms of the Mozilla Public
#   License, v. 2.0. If a copy of the MPL was not distributed with this
#   file, You can obtain one at http://mozilla.org/MPL/2.0/.
#-----------------------------------------------------------
#       file:   makefile
#    project:   Beach Serialization
#   platform:   independent
#     format:   GNU Make
#    authors:   Christopher Augustus
#-----------------------------------------------------------
#   Build the serialization tests.
#-----------------------------------------------------------

#---------------------------------------
#    variables and rules
#---------------------------------------

COMPONENT := test_serialization

PARENT_RELATIVE_PATH := ..

include $(PARENT_RELATIVE_PATH)/make_include_parent
include $(BEACH_DEP_DIR)/make_include_cppunit
include $(BUILD_DIR)/make_include_settings

#---------------------------------------
#   intermediate targets
#---------------------------------------

OBJECTS :=\
 $(OBJECTS_DIR)/test_config_file.o\
 $(OBJECTS_DIR)/test_event.o\
 $(OBJECTS_DIR)/test_event_handler.o\
 $(OBJECTS_DIR)/test_event_manager.o\
 $(OBJECTS_DIR)/test_serialization_main.o

LINK_LIBS :=\
 -lbeach_serialization\
 -lbeach_notification\
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
