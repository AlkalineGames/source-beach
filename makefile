#-----------------------------------------------------------
#   Copyright 1996-2017 (c) Alkaline Games LLC
#
#   This Source Code Form is subject to the terms of the Mozilla Public
#   License, v. 2.0. If a copy of the MPL was not distributed with this
#   file, You can obtain one at http://mozilla.org/MPL/2.0/.
#-----------------------------------------------------------
#       file:   makefile
#    project:   (any)
#   platform:   independent
#     format:   GNU Make
#    authors:   Christopher Augustus
#-----------------------------------------------------------
#   Build all of Beach.
#-----------------------------------------------------------

PARENT_RELATIVE_PATH := .

include $(PARENT_RELATIVE_PATH)/make_include_parent

#---------------------------------------
#   targets
#---------------------------------------

SUBDIRS :=\
 run\
 src

ifndef BUILD_IGNORE_TESTS
SUBDIRS := $(SUBDIRS)\
 test
endif

include $(BUILD_DIR)/make_include_target_subdirs

#---------------------------------------
# (end of file)
