#-----------------------------------------------------------
#   Copyright 2002-2010 (c) Alkaline Games LLC
#
#   This Source Code Form is subject to the terms of the Mozilla Public
#   License, v. 2.0. If a copy of the MPL was not distributed with this
#   file, You can obtain one at http://mozilla.org/MPL/2.0/.
#-----------------------------------------------------------
#       file:   makefile
#    project:   Beach Atoms
#   platform:   independent
#     format:   GNU Make
#    authors:   Christopher Augustus
#-----------------------------------------------------------
#   Build the atoms unit tests.
#-----------------------------------------------------------

#---------------------------------------
#    variables and rules
#---------------------------------------

COMPONENT := test_atoms

PARENT_RELATIVE_PATH := ..

include $(PARENT_RELATIVE_PATH)/make_include_parent
include $(BEACH_DEP_DIR)/make_include_cppunit
include $(BUILD_DIR)/make_include_settings

#---------------------------------------
#   intermediate targets
#---------------------------------------

OBJECTS :=\
 $(OBJECTS_DIR)/test_atoms_main.o\
 $(OBJECTS_DIR)/test_stlport_issues.o\
 $(OBJECTS_DIR)/test_stringex_conversion.o\
 $(OBJECTS_DIR)/test_stringex.o

OBJECTS_TEMPLATED :=\
 $(OBJECTS_DIR)/test_atoms_templates.o

LINK_LIBS :=\
 -lbeach_atoms\
 -lbeach_atoms_allocation\
 $(LINK_LIBS)

#---------------------------------------
#   targets
#---------------------------------------

include $(BUILD_DIR)/make_include_target_executable
	
#---------------------------------------
# (end of file)	 			
