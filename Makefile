#!/usr/bin/make
##
#  file: Makefile
#  date: 2017.02.03
#
#

##### configuration ###################################################
target		= DummyMaker

src_dir		= src
include_dir	= include
bin_dir		= bin
build_dir	= $(src_dir)/build

CXX	= g++

root_config	= root-config
root_include	= $(shell $(root_config) --cflags)
root_libs	= $(shell $(root_config) --libs)

CFLAGS	= -g -O3 -Wall

FLAGS	= $(CFLAGS) -I. -I$(include_dir) $(root_include) $(DFLAGS)
LIBS	= $(root_libs) -lz

sources		:= $(wildcard $(src_dir)/*.cc)
dependencies	:= $(sources:$(src_dir)/%.cc=$(build_dir)/%.d)
objects		:= $(sources:$(src_dir)/%.cc=$(build_dir)/%.o)
main_objects	:= $(filter %Main.o, $(objects))

#######################################################################
.PHONY: all clean distclean

all: $(bin_dir)/$(target)

-include $(dependencies)

$(bin_dir)/$(target): $(objects)
	@ echo -e "\e[35;1m=== Linking $@\e[m"
	@ mkdir -p $(bin_dir)
	$(CXX) -o $@ $(objects) $(LIBS)

clean:
	@ echo -e "\e[32;1m=== Cleaning\e[m"
	@ rm -rfv $(build_dir)
	@ find . \( -name "*~" -o -name "\#*\#" \) -exec rm -fv \{\} \;

$(build_dir)/%.o: $(src_dir)/%.cc
	@ echo -e "\e[32;1m=== Compiling $@\e[m"
	@ mkdir -p $(build_dir)
	$(CXX) $(FLAGS) -o $@ -MMD -c $<


