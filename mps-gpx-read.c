#include "mps-gpx.h"                         // this project
/*----------------------------------------------------------------------------*/
void read_h(void)                            // read header section
{
   read_s();
   read_x(9);
   read_m();                                 // section ------------------------
   read_n(2);
   read_s();
   read_s();
   read_s();
   read_x(1);
   read_m();                                 // section ------------------------
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
void read_r(void)                            // read route section
{
   sec=0x00;
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
void read_t(void)                            // read track section
{
   pr_gpx_trk();
   pr_gpx_trkp();
   pr_gpx_trke();
   sec=0x00;
}
/*----------------------------------------------------------------------------*/
void read_w(void)                            // read waypoint section
{
   read_s();                                 // nam
      strncpy(data.nam,(char *)&buff,64);
      if(tst) printf("%5s%s\n","",data.nam);
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
      read_n(1);
         data.altf=buff.c;
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
      pr_gpx_wpt();
   }
   read_m();                                 // section ------------------------
}
/*----------------------------------------------------------------------------*/
void read_x(int n)                           // read no buffer
{
   fseek(fp,n,SEEK_CUR);
}
/*----------------------------------------------------------------------------*/
