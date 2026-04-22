#include "mps-gpx.h"                         // this project
/*----------------------------------------------------------------------------*/
void cl_gpx(void)                            // clear gpx data
{
   memset(&data,0,sizeof(data));
}
/*----------------------------------------------------------------------------*/
void date(time_t n)                          // epoch -> date & time -> buff
{
   struct tm ts;
   ts=*gmtime(&n);
   strftime(str,sizeof(buff),"%Y-%m-%dT%H:%M:%SZ",&ts); // char *str=(char*)&buff;
}
/*----------------------------------------------------------------------------*/
double lat_lon(int n)                        // garmin mapsource int -> double
{
   return n*360.0/pow(2,32);                 // sneaky garmin encryption
}
/*----------------------------------------------------------------------------*/
void pr_gpx_wpt(void)                        // print gpx waypoint data
{
   printf("%3s%s%f%s%f%s\n","","<wpt lat=\"",data.lat,"\" lon=\"",data.lon,"\">");
   if(strlen(data.nam))
      printf("%6s%s%s%s\n","","<name>",data.nam,"</name>");
   if(strlen(data.cmt))
      printf("%6s%s%s%s\n","","<desc>",data.cmt,"</desc>");
   if(data.altf!=0x00)
      printf("%6s%s%f%s\n","","<ele>",data.alt,"</ele>");
   if(strlen(sym_nam[data.sym]))
      printf("%6s%s%s%s\n","","<sym>",sym_nam[data.sym],"</sym>");
   printf("%3s%s\n","","</wpt>");
   cl_gpx();
}
/*----------------------------------------------------------------------------*/
void pr_gpx_trk(void)                            // print start of track
{
   printf("%3s%s\n","","<trk>");
   if(strlen(data.nam))
      printf("%6s%s%s%s\n","","<name>",data.nam,"</name>");
   printf("%6s%s\n","","<trkseg>");
   cl_gpx();
}
/*----------------------------------------------------------------------------*/
void pr_gpx_trke(void)                           // print end of track
{
   printf("%6s%s\n","","</trkseg>");
   printf("%3s%s\n","","</trk>");
   cl_gpx();
}
/*----------------------------------------------------------------------------*/
void pr_gpx_trkp(void)                      // print gpx track data
{
   printf("%9s%s%f%s%f%s\n","","<trkpt lat=\"",data.lat,"\" lon=\"",data.lon,"\">");
   if(data.altf!=0x00)
      printf("%12s%s%f%s\n","","<ele>",data.alt,"</ele>");
   printf("%9s%s\n","","</trkpt>");
   cl_gpx();
}
/*----------------------------------------------------------------------------*/
void pr_stuff(void)                          // print stuff
{
   if(tst)
   {
      printf("%03li: ",ftell(fp));           // print pos
      for(cnt=0;cnt<=buf;cnt++)              // print buffer & \0
         printf("%02X ",buff.chr[cnt]);
      printf("\n");
   }
}
/*----------------------------------------------------------------------------*/
