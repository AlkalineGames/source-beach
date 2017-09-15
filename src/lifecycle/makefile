#-----------------------------------------------------------
#   Copyright 2002-2017 (c) Alkaline Games LLC
#
#   This Source Code Form is subject to the terms of the Mozilla Public
#   License, v. 2.0. If a copy of the MPL was not distributed with this
#   file, You can obtain one at http://mozilla.org/MPL/2.0/.
#-----------------------------------------------------------
#       file:   makefile
#    project:   Beach LifeCycle
#   platform:   independent
#     format:   GNU Make
#    authors:   Christopher Augustus
#-----------------------------------------------------------
#   Build the lifecycle library.
#-----------------------------------------------------------

#---------------------------------------
#    variables and rules
#---------------------------------------

COMPONENT := lifecycle

# we must use the memory manager explicitly and selectively
BEACH_NO_MEMORY_MANAGER := 1

PARENT_RELATIVE_PATH := ..

include $(PARENT_RELATIVE_PATH)/make_include_parent
include $(BUILD_DIR)/make_include_settings

#---------------------------------------
#   intermediate targets
#---------------------------------------

OBJECTS :=\
 $(OBJECTS_DIR)/allocation_center.o\
 $(OBJECTS_DIR)/class_catalog.o\
 $(OBJECTS_DIR)/class_info.o\
 $(OBJECTS_DIR)/counted_object.o\
 $(OBJECTS_DIR)/execution_coordinator.o\
 $(OBJECTS_DIR)/lifecycle_manager.o\
 $(OBJECTS_DIR)/lock.o\
 $(OBJECTS_DIR)/lock_factory.o\
 $(OBJECTS_DIR)/logger.o\
 $(OBJECTS_DIR)/logger_labels.o\
 $(OBJECTS_DIR)/identified_object.o\
 $(OBJECTS_DIR)/initialization_coordinator.o\
 $(OBJECTS_DIR)/object_catalog.o\
 $(OBJECTS_DIR)/object_identification.o\
 $(OBJECTS_DIR)/object_identification_id.o\
 $(OBJECTS_DIR)/object_identification_id_name.o\
 $(OBJECTS_DIR)/object_identification_name.o

OBJECTS_TEMPLATED :=\
 $(OBJECTS_DIR)/lifecycle_templates.o

#---------------------------------------
#   targets
#---------------------------------------

include $(BUILD_DIR)/make_include_target_library
	
#---------------------------------------
# (end of file)
