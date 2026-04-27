#-------------------------------------------------------------------------------
# compile 'mps-gpx' project
# not doing cleanup of '*.o', leaving for future compiles
# finally figured 'MAKE'
# entire project compiled using project executable name
#-------------------------------------------------------------------------------
# project executable name
prj = mps-gpx

# object list
obj = $(patsubst %.c,%.o,$(wildcard $(prj)*.c))

# executable
#    $@                 left name; could use $(prj)
$(prj): $(obj)
	cc -o $@ $(obj)

# object
# %.o: %.c $(prj).h     '%' name w/o extension from previous rule
#    $<                 1st in right list
%.o: %.c  $(prj).h
	cc -c $<
#-------------------------------------------------------------------------------
