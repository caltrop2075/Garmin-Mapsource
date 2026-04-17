#===============================================================================
#    FILE: makefile    -> make
#          mps-gpx.mak -> make -f mps-gpx.mak
# PURPOSE: mps waypoint extraction
#
# the simplest make file; need to work on creating, very baffling...
#-------------------------------------------------------------------------------
mps-gpx: mps-gpx.c
	gcc -Wall -o mps-gpx mps-gpx.c
#===============================================================================
