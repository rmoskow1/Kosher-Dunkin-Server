#include <stdio.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <regex.h>
#include <curl/curl.h>


/*This will be our Kosher finding regex, for use later*/
#define tofind "kosher\":\"Y\"[^/]+//www.dunkindonuts.com\",\"address\":\"([^\"]+)\""

int main(int argc, char **argv)
{
int MAXLINE = 7000;
  char *buf, *p;
  char full_url[7000], zip[300];
  char arg1[MAXLINE], content[MAXLINE];
  /*Proper header for the generated response*/
    printf("%s%c%c\n","Content-Type:text/plain;charset=iso-8859-1",13,10);
    /*Read zipcode environment variable, store it in zip*/
    if ((buf = getenv("QUERY_STRING")) != NULL) {
   
      /*check to make sure the submission was actually a zipcode*/
      regex_t regex;
      int reti = regcomp(&regex,"^zipcode=[0-9]{5}$",REG_EXTENDED); /*should match 5 numbers exactly*/
      reti = regexec(&regex, buf, 0, NULL,0);
      if(reti!=0){
	printf("This fake %s doesn't work. Please try again with a Kosher (i.e.valid) Zipcode!\n",buf);
	return(0);
      }
      /*now, we can set zip, the proper zipcode environemt*/
      strncpy(zip,buf+8,5);
    }
    
    /*Create the two pieces of the full url. This request to the mapquest api will return all of the dunkin donuts in the 25 mile radius vacinity.*/

    /*Retrieve JSON response from the url, and place it in a file, result*/
    char url1[600] = "\"http://www.mapquestapi.com/search/v2/radius?callback=jQuery1112013032576308156107_1514930541467&key=Gmjtd%7Clu6t2luan5%252C72%253Do5-larsq&origin=";
  char url2[600] = "&units=m&maxMatches=30&radius=25&hostedData=mqap.33454_DunkinDonuts&ambiguities=ignore&_=1514930541469\" > best_result";
  char command[100] = "curl ";
  strcpy(full_url, command);
  strcat(full_url, url1);
  strcat(full_url, zip);
  strcat(full_url, url2);
  system(full_url);

    
    FILE *fp;
    char line[1024];
    int retval = 0;
    regex_t re;
    regmatch_t rm[2];
    /*this file will hold the JSON response for parsing*/
    const char *filename = "./best_result";
    
    /*Compile the regex for searching for the kosher Dunkin Donuts*/
    if (regcomp(&re, tofind, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Failed to compile regex '%s'\n", tofind);
        return EXIT_FAILURE;
    }

    /*Make sure the file opening works out*/
    fp = fopen(filename, "r");
    if (fp == 0)
    {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", filename, errno, strerror(errno));
        return EXIT_FAILURE;
    }

    
    while ((fgets(line, 1024, fp)) != NULL)
    {
        line[strlen(line)-1] = '\0';
        if ((retval = regexec(&re, line, 2, rm, 0)) == 0)
        {
	  /*Within this conditional, we've found a kosher dunkin donuts! They are arranged by proximity, so the first instance of a successful regex find is in fact, the closest. We can break after. */
	  fprintf(stdout,"The address of the closest Kosher Dunkin Donuts store location is: %.*s\n", (int)(rm[1].rm_eo - rm[1].rm_so), line + rm[1].rm_so);
	  fprintf(stdout,"Enjoy the kosh!");
	  fflush(stdout);
	  return EXIT_SUCCESS;
	}
    }
    /*If this point has been reached, no kosher Dunkin Donuts within 25 miles has been found.*/
    fprintf(stdout,"Unfortunately, there are no Kosher Dunkin Donuts in your vacinity. Please move!");
    fflush(stdout);
    return(0);
    return EXIT_SUCCESS;
}
