#-------------------------------------------------------------------------------
#    FILE: makefile    -> make
#          mps-gpx.mak -> make -f mps-gpx.mak
# PURPOSE: mps waypoint extraction
# not doing cleanup of '*.o', leaving for compiles
#-------------------------------------------------------------------------------
obj_c = $(wildcard mps-gpx*.c)
obj_o = $(wildcard mps-gpx*.o)

# make executable
mps-gpx: $(obj_o)
	cc -o mps-gpx $(obj_o)

# make all objects
$(obj_o): $(obj_c) mps-gpx.h
	cc -c $(obj_c)
#-------------------------------------------------------------------------------
