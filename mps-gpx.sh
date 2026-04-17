#!/usr/bin/bash
#------------------------------------------------------------------------------#
#                            Programmed By Liz                                 #
#------------------------------------------------------------------------------#
# mps -> gpx
#
# since 'gpsbabel' quit garmin mapsource mps files I wrote a 'c' program
# currently only does waypoints
#-------------------------------------------------------------------------------
clear
source "$HOME/data/global.dat"
bse="$HOME/WinXP/Garmin"
src="$bse/mps-decode.mps"
gpx="$HOME/Programming/Projects/MPS/mps-gpx"
bin="$HOME/.local/bin"
h=10
m=$((60*h))
#-------------------------------------------------------------------------------
title-80.sh "Processing MPS (<${h}h) -> GPX"
sleep 1

if [[ $* =~ -c ]]
then
   echo "copy new 'mps-gpx'"
   cp "$gpx" "$bin"
   echo $div_s
   sleep 1
fi

while IFS="|" read dir fil
do
   if [[ $dir != $lst ]]
   then
      printf "$Wht%s$nrm\n" "~${dir#$HOME}"
      sleep 0.2
      mkdir -p "$dir/gpx"
   fi
   printf "%3s%s\n" "" "$fil"
   lst="$dir"
   src="$dir/$fil"
   des="$dir/gpx/${fil%.*}.gpx"
   # printf "%-60s %s\n" "~${src#$HOME}" "~${des#$HOME}"
   mps-gpx "$src" > "$des"
done < <(find ~ -type f -mmin -$m -iname "*.mps" -printf "%h|%f\n" | sort)
echo $div_s
#-------------------------------------------------------------------------------
