/*
 *  GpIO.cpp
 *  GEPETO
 *
 *  Created by Celso Dantas on 11/8/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GpIO.h"
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

// TODO:: Indicar de onde a função foi tirada da internet!!

char * GpIO::textFileRead(char *fn) {
	
	FILE *fp;
	char *content = NULL;
	
	int f,count;
	f = open(fn, O_RDONLY);
	
	count = lseek(f, 0, SEEK_END);
	
	close(f);
	
	if (fn != NULL) {
		fp = fopen(fn,"r");
		
		if (fp != NULL) {
			
			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	
	return content;
}

