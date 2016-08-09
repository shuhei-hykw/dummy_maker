#!/usr/bin/make
##
#  file: Makefile
#  date: 2016.04.26
#
#

target		= DummyMaker

src_dir		= src
include_dir	= include
bin_dir		= bin
build_dir	= $(src_dir)/build

CXX	= g++

root_config	= root-config
root_include	= $(shell $(root_config) --cflags)
root_libs	= $(shell $(root_config) --libs)

clhep_config	= clhep-config
clhep_include	= $(shell $(clhep_config) --include)
clhep_libs	= $(shell $(clhep_config) --libs)

CFLAGS	= -g -O3 -Wall

FLAGS	= $(CFLAGS) -I. -I$(include_dir) $(root_include) $(clhep_include) $(DFLAGS)
LIBS	= $(root_libs) $(clhep_libs) -lz

sources		:= $(wildcard $(src_dir)/*.cc)
dependencies	:= $(sources:$(src_dir)/%.cc=$(build_dir)/%.d)
objects		:= $(sources:$(src_dir)/%.cc=$(build_dir)/%.o)
main_objects	:= $(filter %Main.o, $(objects))

#===========================================================================#

.PHONY: all clean distclean

all: $(bin_dir)/$(target)

-include $(dependencies)

$(bin_dir)/$(target): $(objects)
	@ echo "- Linking $@"
	@ mkdir -p $(bin_dir)
	@ $(CXX) -o $@ $(objects) $(LIBS)

clean:
	@ echo "==> Cleaning up ..."
	@ rm -rfv $(build_dir)
	@ find . \( -name "*~" -o -name "\#*\#" \) -exec rm -fv \{\} \;

$(build_dir)/%.o: $(src_dir)/%.cc
	@ echo "- Compiling $@"
	@ mkdir -p $(build_dir)
	@ set -e; \
	$(CXX) $(FLAGS) -o $@ -MMD -c $<


