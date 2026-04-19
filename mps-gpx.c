/*==============================================================================
 * MPS -> GPX
 * 2026-04-17
 * read byte by byte & decode
 * buffer is 64 bytes
 *    always \0 terminated but prints 'buf' bytes
 * int types gave some issue on this system
 *    found out that int is actually long
 * Garmin Mapsource encryption; lat/lon = int * 360.0 / 2^32
 *    nexer would have figured this without the documentation I found
 *    why THEY didn't just use 'double'...?; just to FUCK WITH US!
 * records are variable length due to \0 terminated strings
 * debugging: set 'tst=true;' in 'main()'
 *
 * TODO
 * waypoint
 *    gpx      done
 * routes      baffling
 *    gpx
 * tracks      straight forward
 *    gpx
==============================================================================*/
// INCLUDE
#include <math.h>                            // math
#include <stdbool.h>                         // boolean
#include <stdio.h>                           // file i/o
#include <stdlib.h>                          // misc, malloc, calloc, etc...
#include <string.h>                          // string utilities
/*----------------------------------------------------------------------------*/
// VARIABLE DECLARATION
union buff
{                                            // byte  desc
   unsigned char        chr[128];            // 64    buffer size
   short int            ssi;                 //  2    misc
   unsigned short int   usi;                 //  2    misc
   int                  si;                  //  4    lat/lon
   unsigned int         ui;                  //  4    lat/lon
   double               df;                  //  8    altitude/proximity/depth
} buff;

struct data                                  // gpx structure
{
   char         icn[32];                     // <sym>    symbol icon name
   char         wpt[64];                     // <name>   waypoint name
   char         cmt[64];                     // <desc>   comment
   char         dir[64];                     //          directions
   unsigned int sym;                         // <sym>    symbol
   double       lat;                         // <wpt     latitude
   double       lon;                         // <wpt     longitude
   double       alt;                         // <ele>    altitude
   double       prx;                         //          proximity
   double       dep;                         //          depth
} data;

char sym_nam[256][32]=                       // symbol names
{
   "Anchor",
   "Bell",
   "Diamond, Green",
   "Diamond, Red",
   "Diver Down Flag 1",
   "Diver Down Flag 2",
   "Bank",
   "Fishing Area",
   "Gas Station",
   "Horn",
   "Residence",
   "Restaurant",
   "Light",
   "Bar",
   "Skull and Crossbones",
   "Square, Green",
   "Square, Red",
   "Buoy, White",
   "Waypoint",
   "Shipwreck",
   "Man Overboard",
   "Navaid, Amber",
   "Navaid, Black",
   "Navaid, Blue",
   "Navaid, Green",
   "Navaid, Green/Red",
   "Navaid, Green/White",
   "Navaid, Orange",
   "Navaid, Red",
   "Navaid, Red/Green",
   "Navaid, Red/White",
   "Navaid, Violet",
   "Navaid, White",
   "Navaid, White/Green",
   "Navaid, White/Red",
   "Dot, White",
   "Radio Beacon",
   "Boat Ramp",
   "Campground",
   "Restroom",
   "Shower",
   "Drinking Water",
   "Telephone",
   "Medical Facility",
   "Information",
   "Parking Area",
   "Park",
   "Picnic Area",
   "Scenic Area",
   "Skiing Area",
   "Swimming Area",
   "Dam",
   "Controlled Area",
   "Danger Area",
   "Restricted Area",
   "Ball Park",
   "Car",
   "Hunting Area",
   "Shopping Center",
   "Lodging",
   "Mine",
   "Trail Head",
   "Truck Stop",
   "Exit",
   "Flag",
   "Circle with X",
   "Mile Marker",
   "TracBack Point",
   "Golf Course",
   "City (Small)",
   "City (Medium)",
   "City (Large)",
   "City (Capitol)",
   "Amusement Park",
   "Bowling",
   "Car Rental",
   "Car Repair",
   "Fast Food",
   "Fitness Center",
   "Movie Theater",
   "Museum",
   "Pharmacy",
   "Pizza",
   "Post Office",
   "RV Park",
   "School",
   "Stadium",
   "Department Store",
   "Zoo",
   "Convenience Store",
   "Live Theater",
   "Scales",
   "Toll Booth",
   "Bridge",
   "Building",
   "Cemetery",
   "Church",
   "Civil",
   "Crossing",
   "Ghost Town",
   "Levee",
   "Military",
   "Oil Field",
   "Tunnel",
   "Beach",
   "Forest",
   "Summit",
   "Airport",
   "Heliport",
   "Private Field",
   "Soft Field",
   "Tall Tower",
   "Short Tower",
   "Glider Area",
   "Ultralight Area",
   "Parachute Area",
   "Seaplane Base",
   "Geocache",
   "Geocache Found",
   "Contact, Afro",
   "Contact, Alien",
   "Contact, Ball Cap",
   "Contact, Big Ears",
   "Contact, Biker",
   "Contact, Bug",
   "Contact, Cat",
   "Contact, Dog",
   "Contact, Dreadlocks",
   "Contact, Female1",
   "Contact, Female2",
   "Contact, Female3",
   "Contact, Goatee",
   "Contact, Kung-Fu",
   "Contact, Pig",
   "Contact, Pirate",
   "Contact, Ranger",
   "Contact, Smiley",
   "Contact, Spike",
   "Contact, Sumo",
   "Water Hydrant",
   "Flag, Red",
   "Flag, Blue",
   "Flag, Green",
   "Pin, Red",
   "Pin, Blue",
   "Pin, Green",
   "Block, Red",
   "Block, Blue",
   "Block, Green",
   "Bike Trail",
   "Fishing Hot Spot Facility",
   "Police Station",
   "Ski Resort",
   "Ice Skating",
   "Wrecker",
   "Anchor Prohibited",
   "Beacon",
   "Coast Guard",
   "Reef",
   "Weed Bed",
   "Dropoff",
   "Dock",
   "Marina",
   "Bait and Tackle",
   "Stump",
   "Circle, Red",
   "Circle, Green",
   "Circle, Blue",
   "Diamond, Blue",
   "Oval, Red",
   "Oval, Green",
   "Oval, Blue",
   "Rectangle, Red",
   "Rectangle, Green",
   "Rectangle, Blue",
   "Square, Blue",
   "Letter A, Blue",
   "Letter A, Green",
   "Letter A, Red",
   "Letter B, Blue",
   "Letter B, Green",
   "Letter B, Red",
   "Letter C, Blue",
   "Letter C, Green",
   "Letter C, Red",
   "Letter D, Blue",
   "Letter D, Green",
   "Letter D, Red",
   "Number 0, Blue",
   "Number 0, Green",
   "Number 0, Red",
   "Number 1, Blue",
   "Number 1, Green",
   "Number 1, Red",
   "Number 2, Blue",
   "Number 2, Green",
   "Number 2, Red",
   "Number 3, Blue",
   "Number 3, Green",
   "Number 3, Red",
   "Number 4, Blue",
   "Number 4, Green",
   "Number 4, Red",
   "Number 5, Blue",
   "Number 5, Green",
   "Number 5, Red",
   "Number 6, Blue",
   "Number 6, Green",
   "Number 6, Red",
   "Number 7, Blue",
   "Number 7, Green",
   "Number 7, Red",
   "Number 8, Blue",
   "Number 8, Green",
   "Number 8, Red",
   "Number 9, Blue",
   "Number 9, Green",
   "Number 9, Red",
   "Triangle, Blue",
   "Triangle, Green",
   "Triangle, Red",
   "Contact, Blonde",
   "Contact, Clown",
   "Contact, Glasses",
   "Contact, Panda",
   "Multi-Cache",
   "Letterbox Cache",
   "Puzzle Cache",
   "Library",
   "Bus Station",
   "City Hall",
   "Winery",
   "ATV",
   "Big Game",
   "Blind",
   "Blood Trail",
   "Cover",
   "Covey",
   "Food Source",
   "Furbearer",
   "Lodge",
   "Small Game",
   "Animal Tracks",
   "Treed Quarry",
   "Tree Stand",
   "Truck",
   "Upland Game",
   "Waterfowl",
   "Water Source",
   "unknown",
   "unknown",
   "unknown",
   "unknown",
   "unknown",
   "unknown",
   "unknown"
};

bool          tst;                           // test run flag
bool          flg;                           // general use flag
FILE          *fp;                           // file pointer
int           cnt;                           // general purpose counter
int           buf;                           // buffer read count
char          *str=(char*)&buff;             // buffer string pointer
char          chr;                           // general purpose char
char          sec;                           // section character
unsigned char typ;                           // waypoint type
/*============================================================================*/
// FUNCTIONS
void cl_gpx(void)                            // clear gpx data
{
   data.icn[0]=0x00;                         // <sym>
   data.wpt[0]=0x00;                         // <name>
   data.cmt[0]=0x00;                         // <desc>
   data.dir[0]=0x00;                         //       directions
   data.sym=0;                               // <sym>
   data.lat=0;                               // <wpt  latitude
   data.lon=0;                               // <wpt  longitude
   data.alt=0;                               // <ele>
   data.prx=0;                               //       proximity
   data.dep=0;                               //       depth
}
/*----------------------------------------------------------------------------*/
void pr_gpx(void)                            // print gpx data
{
   printf("%3s%s%f%s%f%s\n","","<wpt lat=\"",data.lat,"\" lon=\"",data.lon,"\">");
   printf("%6s%s%s%s\n","","<name>",data.wpt,"</name>");
   if(strlen(sym_nam[data.sym]))
      printf("%6s%s%s%s\n","","<sym>",sym_nam[data.sym],"</sym>");
      // printf("%6s%s%d-%s%s\n","","<sym>",data.sym,sym_nam[data.sym],"</sym>");
   if(strlen(data.cmt))
      printf("%6s%s%s%s\n","","<desc>",data.cmt,"</desc>");
   printf("%3s%s\n","","</wpt>");
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
double lat_lon(int n)                        // garmin mapsource int -> double
{
   return n*360.0/pow(2,32);                 // sneaky encryption
}
/*----------------------------------------------------------------------------*/
void read_m(void)             // read until match  A    R    T    V    W  xFF
{                                            // 0x41 0x52 0x54 0x56 0x57 0xFF
   flg=true;
   do
   {
      chr=(char)fgetc(fp);
      if (chr==0x41) flg=false;
      if (chr==0x52) flg=false;
      if (chr==0x54) flg=false;
      if (chr==0x56) flg=false;
      if (chr==0x57) flg=false;
      if (chr==0xFF) flg=false;
   }
   while (flg);                        // issue with long expression; using flag
   buff.chr[0]=chr;                           // buffer character
   buff.chr[1]=0x00;
   sec=chr;                                  // save current section
   if(tst) printf("%s %s\n",str,"-------------");
}
/*----------------------------------------------------------------------------*/
void read_n(int n)                           // read into buffer & \0
{
   fread(&buff,1,n,fp);
   buff.chr[n]=0x00;
   buf=n;
   pr_stuff();
}
/*----------------------------------------------------------------------------*/
void read_s(void)                            // read into buffer & \0
{
   cnt=-1;
   do
   {
      cnt++;
      buff.chr[cnt]=(char)fgetc(fp);
   }
   while (buff.chr[cnt]!=0);
   buf=cnt;
   pr_stuff();
}
/*----------------------------------------------------------------------------*/
void read_x(int n)                           // read no buffer
{
   fseek(fp,n,SEEK_CUR);
}
/*----------------------------------------------------------------------------*/
void read_h(void)                            // read header section
{
   read_s();
   read_x(9);
   read_m();
   read_n(2);
   read_s();
   read_s();
   read_s();
   read_x(1);
   read_m();                                 // section ------------------------
}
/*----------------------------------------------------------------------------*/
void read_w(void)                            // read waypoint section
{
   cl_gpx();
   read_s();                                 // nam
      strncpy(data.wpt,(char *)&buff,64);
      if(tst) printf("%5s%s\n","",data.wpt);
   read_n(1);                                // typ
      typ=buff.chr[0];
   if(typ!=0x00)                             // skip route waypoiints
   {
      if(tst) printf("%s\n","---NO DATA---");
      read_x(84);
      read_s();                              // directions if any
      if(tst) printf("%5s%s\n","",(char *)&buff);
   }
   else                                      // user waypoints
   {
      read_x(26);
      read_n(4);                             // lat
         data.lat=lat_lon(buff.si);
         if(tst) printf("%5s%f\n","",data.lat);
      read_n(4);                             // lon
         data.lon=lat_lon(buff.si);
         if(tst) printf("%5s%f\n","",data.lon);
      read_x(1);
      read_n(8);                             // alt
         data.alt=buff.df;
      read_s();                              // cmt
         strncpy(data.cmt,(char *)&buff,64);
         if(tst) printf("%5s%s\n","",data.cmt);
      read_x(17);
      read_n(1);                             // sym
         data.sym=buff.usi;
         if(tst) printf("%s%s\n","",sym_nam[data.sym]);
      read_x(27);
      pr_gpx();
   }
   read_m();                                 // section ------------------------
}
/*----------------------------------------------------------------------------*/
void read_r(void)                            // read route section
{
      sec=0x00;
}
/*----------------------------------------------------------------------------*/
void read_t(void)                            // read track section
{
      sec=0x00;
}
/*============================================================================*/
// MAIN
int main(int argc, char *argv[])
{
   tst=false;                                // test flag
   if(tst) system("clear");                  // clear screen
   if(tst) printf ("MPS -> GPX conversion testing\n"); // message

   if (argc>1 && strcmp(argv[1],"-v")==0)    // version display
   {
      printf("%s\n","version: 2026-04-19");
      exit(1);
   }

   if (argc==1)                              // no command line
   {
      printf("%s\n","mps-gpx FILE_NAME");
      exit(1);
   }

   if(tst) printf("%s   %s   %s\n","argc","prgm","file"); // command line
   if(tst) printf("%d   %s   %s\n",argc,argv[0],argv[1]);

   fp=fopen(argv[1],"r");                    // open file for reading
   if(fp==NULL)
   {
      printf("%s\n","file not found");
      exit(1);
   }
   if(tst) printf("%s\n","===============");

   read_h();
   if(!tst) printf("%s\n","<gpx>");

   do read_w(); while (sec==0x57);           // read waypoints
   do read_r(); while (sec==0x52);           // read routes
   do read_t(); while (sec==0x54);           // read tracks

   if(!tst) printf("%s\n","</gpx>");
   if(tst) printf("%s\n","===============");
   fclose(fp);                               // close file
}
/*============================================================================*/
