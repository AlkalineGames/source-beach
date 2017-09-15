#-----------------------------------------------------------
#   Copyright 2002-2017 (c) Alkaline Games LLC
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
#   Build the serialization library.
#-----------------------------------------------------------

#---------------------------------------
#    variables and rules
#---------------------------------------

COMPONENT := serialization

PARENT_RELATIVE_PATH := ..

include $(PARENT_RELATIVE_PATH)/make_include_parent
include $(BUILD_DIR)/make_include_settings

#---------------------------------------
#   intermediate targets
#---------------------------------------

OBJECTS :=\
 $(OBJECTS_DIR)/class_info_serializable.o\
 $(OBJECTS_DIR)/command_packet_read.o\
 $(OBJECTS_DIR)/context_reading.o\
 $(OBJECTS_DIR)/context_writing.o\
 $(OBJECTS_DIR)/event_channel_serializable.o\
 $(OBJECTS_DIR)/event_manager.o\
 $(OBJECTS_DIR)/event_serializable.o\
 $(OBJECTS_DIR)/reader.o\
 $(OBJECTS_DIR)/reader_packeted.o\
 $(OBJECTS_DIR)/selector.o\
 $(OBJECTS_DIR)/serializable.o\
 $(OBJECTS_DIR)/serializable_factory.o\
 $(OBJECTS_DIR)/serializable_logging.o\
 $(OBJECTS_DIR)/serializable_manager.o\
 $(OBJECTS_DIR)/serializable_spec.o\
 $(OBJECTS_DIR)/serialized_object.o\
 $(OBJECTS_DIR)/text_stream_appender.o\
 $(OBJECTS_DIR)/text_stream_eraser.o\
 $(OBJECTS_DIR)/text_stream_reader.o\
 $(OBJECTS_DIR)/text_stream_rewriter.o\
 $(OBJECTS_DIR)/text_stream_writer.o\
 $(OBJECTS_DIR)/writer.o\
 $(OBJECTS_DIR)/writer_forwarded.o

OBJECTS_TEMPLATED :=\
 $(OBJECTS_DIR)/config_file.o

#---------------------------------------
#   targets
#---------------------------------------

include $(BUILD_DIR)/make_include_target_library
    
#---------------------------------------
# (end of file)             
