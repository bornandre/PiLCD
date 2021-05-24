/*
 *	main.c
 */

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h> /* for strncpy */
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "daemonize.h"
#include "st7036.h"

int main(int argc, char **argv)
{
  daemonize();

  log_message("pilcd.log","starting Raspberry Pi LCD driver...\n");

  log_message("pilcd.log","initializing wiringPi ...i\n");
  wiringPiSetup();


  time_t s, val = 1;
  struct tm* cur_tim;
  char buffer [50];
  char x [20];
  int n,fd;
  struct ifreq ifr;

  fd = socket(AF_INET, SOCK_DGRAM, 0);
  /* I want to get an IPv4 IP address */
  ifr.ifr_addr.sa_family = AF_INET;
  /* I want IP address attached to "eth0" */
  strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);
  ioctl(fd, SIOCGIFADDR, &ifr);
  close(fd);

  log_message("pilcd.log","initializing LCD ST7036\n");
  ST7036_init();

  while(1)
  {
    // time in seconds
    s = time(NULL);

    // to get current time
    cur_tim = localtime(&s);

    //sprintf(buffer, "%02d:%02d:%02d\n", cur_tim->tm_hour, cur_tim->tm_min, cur_tim->tm_sec);
    //log_message("pilcd.log",buffer);

    ST7036_goto_xy(0,0);
    ST7036_puts("Controme Heizung");

    n=sprintf(buffer,"IP:%s",inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
    ST7036_goto_xy(16,0);
    ST7036_puts(buffer);

    sprintf(buffer,"%02d:%02d %02d.%02d.%04d", cur_tim->tm_hour, cur_tim->tm_min, cur_tim->tm_mday, cur_tim->tm_mon, cur_tim->tm_year+1900);
    ST7036_goto_xy(0,1);
    ST7036_puts(buffer);

    delay(30000);
  }
  return 0;
}

