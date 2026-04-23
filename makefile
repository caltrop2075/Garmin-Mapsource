#-------------------------------------------------------------------------------
#    FILE: makefile    -> make
#          mps-gpx.mak -> make -f mps-gpx.mak
# PURPOSE: mps waypoint extraction
# not doing cleanup of '*.o', leaving for future compiles
# MAKE is totally baffling...
#-------------------------------------------------------------------------------
# project definition
bse = mps-gpx

# file definitions
src = $(wildcard $(bse)*.c)
obj = $(patsubst %.c,%.o,$(src))

# executable
mps-gpx: $(obj)
	cc -o $@ $(obj)

# object files from source
%.o: %.c  $(bse).h
	cc -c $<
#-------------------------------------------------------------------------------
