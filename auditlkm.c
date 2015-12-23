#include <sys/inotify.h>
#include <stdio.h>
#include <time.h>




int main (){

	int fd=0;
	int fd_inotify=0;
	int res=-1;
	fd = open("/tmp/audit", "r");
	printf("Bora\n");

	fd_inotify = inotify_init();

	while (res=-1)
	{
		printf("ok\n");
		res= inotify_add_watch(fd_inotify, "/tmp/audit", IN_ALL_EVENTS );
		//incluir read
	}

	printf("Resultado %d", res);


	return 0 ;
}
