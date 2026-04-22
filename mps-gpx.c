/*==============================================================================
 * MPS -> GPX
 * 2026-04-22
 * read byte by byte & decode
 * buffer is 128 bytes
 *    always \0 terminated, pr_stuff prints bytes read
 * int types gave some issue on this system
 *    found out that int is actually long
 * Garmin Mapsource encryption; lat/lon = int * 360.0 / 2^32
 *    never would have figured this without the documentation I found
 *    why THEY didn't just use 'double'...?; just to FUCK WITH US!
 * records are variable length due to \0 terminated strings
 * debugging: 'tst=true;' in 'main()'
 * wrestled with epoch seconds -> date/time
 *
 * TODO
 * waypoint
 *    gpx      done
 * routes      baffling; going to take some time; currently bypassing
 *    gpx
 * tracks      straight forward, in progress
 *    gpx
==============================================================================*/
#include "mps-gpx.h"                         // this project
/*----------------------------------------------------------------------------*/
// VARIABLES
buff_t buff;
data_t data;

bool          tst;                           // test run flag
bool          flg;                           // general use flag
FILE          *fp;                           // file pointer
int           cnt;                           // general purpose counter
int           buf;                           // buffer read count
char          *str=(char*)&buff;             // buffer string pointer
char          chr;                           // general purpose char
char          sec;                           // section character
unsigned char typ;                           // waypoint type
/*----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
   tst=false;                                // test flag
   if(tst) system("clear");                  // clear screen
   if(tst) printf ("MPS -> GPX conversion testing\n"); // message
   //---------------------------------------------------------------------------
   if (argc>1 && strcmp(argv[1],"-v")==0)    // version display
   {
      printf("%s\n","version: 2026-04-22");
      exit(1);
   }
   //---------------------------------------------------------------------------
   if (argc==1)                              // no command line
   {
      printf("%s\n","mps-gpx FILE_NAME");
      exit(1);
   }
   //---------------------------------------------------------------------------
   if(tst) printf("%s   %s   %s\n","argc","prgm","file"); // command line
   if(tst) printf("%d   %s   %s\n",argc,argv[0],argv[1]);
   //---------------------------------------------------------------------------
   fp=fopen(argv[1],"r");                    // open file for reading
   if(fp==NULL)
   {
      printf("%s\n","file not found");
      exit(1);
   }
   if(tst) printf("%s\n","===============");
   //---------------------------------------------------------------------------
   read_h();                                 // read header, no gpx data
   if(!tst) printf("%s\n","<gpx>");
   //---------------------------------------------------------------------------
   do read_w(); while (sec==0x57);           // read waypoints -> gpx
   do read_r(); while (sec==0x52);           // read routes    -> gpx
   do read_t(); while (sec==0x54);           // read tracks    -> gpx
   //---------------------------------------------------------------------------
   if(!tst) printf("%s\n","</gpx>");
   if(tst) printf("%s\n","===============");
   fclose(fp);                               // close file
}
/*----------------------------------------------------------------------------*/
