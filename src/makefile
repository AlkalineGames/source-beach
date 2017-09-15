#-----------------------------------------------------------
#   Copyright 2002-2017 (c) Alkaline Games LLC
#
#   This Source Code Form is subject to the terms of the Mozilla Public
#   License, v. 2.0. If a copy of the MPL was not distributed with this
#   file, You can obtain one at http://mozilla.org/MPL/2.0/.
#-----------------------------------------------------------
#       file:   makefile
#    project:   Beach
#   platform:   independent
#     format:   GNU Make
#    authors:   Christopher Augustus
#-----------------------------------------------------------
#   Build all Beach libraries.
#-----------------------------------------------------------

PARENT_RELATIVE_PATH := .

include $(PARENT_RELATIVE_PATH)/make_include_parent

#---------------------------------------
#   targets
#---------------------------------------

SUBDIRS :=\
 atoms\
 chain\
 collection\
 expression\
 geometry\
 invocation\
 lifecycle\
 notification\
 serialization\
 taxonomy

include $(BUILD_DIR)/make_include_target_subdirs

#---------------------------------------
# (end of file)
