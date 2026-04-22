/*----------------------------------------------------------------------------*/
// INCLUDE
#include <math.h>                            // math
#include <stdbool.h>                         // boolean
#include <stdio.h>                           // file i/o
#include <stdlib.h>                          // misc, malloc, calloc, etc...
#include <string.h>                          // string utilities
#include <time.h>                            // time
/*----------------------------------------------------------------------------*/
// TYPEDEFS
typedef union                                        // use 'str'' for \0 terminated strings
{                                            // byte  desc
   unsigned char        chr[128];            // 128    buffer size
   char                 c;                   //   1    single byte
   short int            ssi;                 //   2    misc
   unsigned short int   usi;                 //   2    misc
   int                  si;                  //   4    lat/lon/tim
   unsigned int         ui;                  //   4    lat/lon
   long int             uli;                 //   8    -
   signed long int      slil;                //   8    maybe for time
   double               df;                  //   8    altitude (proximity/depth)
} buff_t;

typedef struct                                       // gpx structure
{
   char         altf;                        //  1          altitude flag
   unsigned int sym;                         //  4 <sym>    symbol
   unsigned int tim;                         //  4 <time>   epoch
   double       lat;                         //  8 <wpt     latitude
   double       lon;                         //  8 <wpt     longitude
   double       alt;                         //  8 <ele>    altitude
   double       prx;                         //  8          proximity
   double       dep;                         //  8          depth
   char         icn[32];                     // 32 <sym>    symbol name
   char         nam[64];                     // 64 <name>   waypoint name
   char         cmt[64];                     // 64 <desc>   comment
   char         dir[64];                     // 64          directions
} data_t;
/*----------------------------------------------------------------------------*/
// DATA
extern char          sym_nam[256][32];
/*----------------------------------------------------------------------------*/
// VARIABLES
extern data_t data;
extern buff_t buff;

extern bool          tst;                           // test run flag
extern bool          flg;                           // general use flag
extern FILE          *fp;                           // file pointer
extern int           cnt;                           // general purpose counter
extern int           buf;                           // buffer read count
extern char          *str;                          // buffer string pointer
extern char          chr;                           // general purpose char
extern char          sec;                           // section character
extern unsigned char typ;                           // waypoint type
/*----------------------------------------------------------------------------*/
// PROTOTYPING
extern void   cl_gpx(void);
extern void   date(time_t n);
extern double lat_lon(int n);
extern void   pr_gpx_trk(void);
extern void   pr_gpx_trke(void);
extern void   pr_gpx_trkp(void);
extern void   pr_gpx_wpt(void);
extern void   pr_stuff(void);
extern void   pr_stuff(void);
extern void   read_h(void);
extern void   read_m(void);
extern void   read_n(int n);
extern void   read_r(void);
extern void   read_s(void);
extern void   read_t(void);
extern void   read_w(void);
extern void   read_x(int n);
/*----------------------------------------------------------------------------*/
