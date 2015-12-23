#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <linux/inotify.h>

#define EVENT_SIZE 	  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )
#define WDIR 		  "/tmp"

int main( )
{
  int length, i = 0;
  int fd;
  int wd;
  char buffer[EVENT_BUF_LEN];

  //necessario
  fd = inotify_init();

  //erro?
  if ( fd < 0 ) {
    perror( "inotify_init" );
  }

  //arquivo ou diretorio
  wd = inotify_add_watch( fd, WDIR, IN_CREATE|IN_MODIFY|IN_DELETE);


  //struct inotify_event {
  //      int      wd;       /* Watch descriptor */
  //      uint32_t mask;     /* Mask of events */
  //      uint32_t cookie;   /* Unique cookie associating related
  //                            events (for rename(2)) */
  //      uint32_t len;      /* Size of name field */
  //      char     name[];   /* Optional null-terminated name */
  //  };


  while ( 1 ) 
  {     
     length = read( fd, buffer, EVENT_BUF_LEN ); 
    
     if ( length < 0 ) {
       perror( "read" );
     }  
     struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];     

     if ( event->len ) {
     printf("Evento ou arquivo monitorado %s ...\n", event->name);

      if ( event->mask & IN_CREATE ) {
        if ( event->mask & IN_ISDIR ) {
          printf("Novo dir %s criado.\n", event->name);
        }
        else {
          printf("Novo arquivo %s criado .\n", event->name); 
        }
      }
      else if ( event->mask & IN_DELETE ) {
        if ( event->mask & IN_ISDIR ) {
          printf("Diretorio %s deletado.\n", event->name);
        }
        else {
          printf("Arquivo %s deletado.\n", event->name);
        }
     } 
     if (event->mask & IN_MODIFY ) { 
     	printf("Arquivo modificado %s \n", event->name);	
     }
    }
    length=0;
  }
   //housekeeping aqui
   inotify_rm_watch( fd, wd );
   close( fd );

}

