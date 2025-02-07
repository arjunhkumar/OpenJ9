###############################################################################
# Copyright IBM Corp. and others 2016
#
# This program and the accompanying materials are made available under
# the terms of the Eclipse Public License 2.0 which accompanies this
# distribution and is available at https://www.eclipse.org/legal/epl-2.0/
# or the Apache License, Version 2.0 which accompanies this distribution and
# is available at https://www.apache.org/licenses/LICENSE-2.0.
#
# This Source Code may also be made available under the following
# Secondary Licenses when the conditions for such availability set
# forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
# General Public License, version 2 with the GNU Classpath
# Exception [1] and GNU General Public License, version 2 with the
# OpenJDK Assembly Exception [2].
#
# [1] https://www.gnu.org/software/classpath/license.html
# [2] https://openjdk.org/legal/assembly-exception.html
#
# SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
###############################################################################

# This makefile is generated using an UMA template.

# UMA_PATH_TO_ROOT can be overridden by a command-line argument to 'make'.
UMA_PATH_TO_ROOT ?= ../
OMR_DIR ?= $(UMA_PATH_TO_ROOT)omr

# top_srcdir is the top of the omr source tree
top_srcdir := $(OMR_DIR)
include $(top_srcdir)/omrmakefiles/configure.mk

# HOOKABLE_SRCDIR is the location of the j9hookable source code.
HOOKABLE_SRCDIR := $(top_srcdir)/util/hookable/

# UMA fills in the stream-specific name of the j9hookable shared library, e.g. j9hookable29.
MODULE_NAME_NOSTREAM := j9hookable
MODULE_NAME := $(MODULE_NAME_NOSTREAM)${uma.buildinfo.version.major}${uma.buildinfo.version.minor}
ARTIFACT_TYPE := c_shared

include $(HOOKABLE_SRCDIR)hookable_include.mk

# J9 requires that a copyright string be embedded into the DLL.
# Append it and its location to the list of objects.
OBJECTS += copyright$(OBJEXT)
vpath copyright.c $(UMA_PATH_TO_ROOT)makelib

ifeq (win,$(OMR_HOST_OS))
# J9 requires a resource file. The .rc is generated by UMA.
RCFLAGS+=$(call buildCPPIncludeFlags,$(MODULE_INCLUDES) $(GLOBAL_INCLUDES))

# compilation rule for resource files.
%.res: %.rc
	$(RC) $(RCFLAGS) $<

OBJECTS += $(MODULE_NAME_NOSTREAM).res
endif

EXPORT_FUNCTIONS_FILE := $(HOOKABLE_SRCDIR)hookable.exportlist

MODULE_STATIC_LIBS += j9utilcore j9pool
MODULE_SHARED_LIBS += j9thr${uma.buildinfo.version.major}${uma.buildinfo.version.minor}

include $(top_srcdir)/omrmakefiles/rules.mk

ifeq (win,$(OMR_HOST_OS))
# HACK:
# When UMA artifacts link this DLL, UMA omits the stream suffix (e.g. "28", "29")
# from the import library name.
# Make a copy of the import library with the name that UMA expects. 
# We need both files because OMR makefile rules look for the import library 
# _with_ the stream suffix in its name.
.NOTPARALLEL:

all: $(lib_output_dir)/$(MODULE_NAME_NOSTREAM).lib
$(lib_output_dir)/$(MODULE_NAME_NOSTREAM).lib: $(lib_output_dir)/$(MODULE_NAME).lib
	cp $< $@
endif
