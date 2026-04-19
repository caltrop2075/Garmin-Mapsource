#!/usr/bin/sed -Ef
# -E extended regex, stuff like {n,m}
#------------------------------------------------------------------------------#
#                            Programmed By Liz                                 #
#------------------------------------------------------------------------------#
# mps-gpx
# add rules as needed to replace pesky special characters
# '&' is the most common
#-------------------------------------------------------------------------------
s/&/&amp;/g
