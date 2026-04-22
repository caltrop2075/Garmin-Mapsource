#-------------------------------------------------------------------------------
#    FILE: makefile    -> make
#          mps-gpx.mak -> make -f mps-gpx.mak
# PURPOSE: mps waypoint extraction
#-------------------------------------------------------------------------------
obj_c = $(wildcard *.c)
obj_o = $(wildcard *.o)

mps-gpx: $(obj_o)
	cc -o mps-gpx $(obj_o)

all: $(obj_c)
	cc -c $(obj_c)
#-------------------------------------------------------------------------------
