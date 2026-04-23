#-------------------------------------------------------------------------------
#    FILE: makefile    -> make
#          mps-gpx.mak -> make -f mps-gpx.mak
# PURPOSE: mps waypoint extraction
# not doing cleanup of '*.o', leaving for future compiles
# MAKE is totally baffling...
#-------------------------------------------------------------------------------
# file definitions
src := $(wildcard mps-gpx*.c)
obj := $(patsubst %.c,%.o,$(wildcard mps-gpx*.c))

mps-gpx: $(obj)
	cc -o $@ $(obj)

%.o: %.c  mps-gpx.h
	cc -c $<
#-------------------------------------------------------------------------------
