#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include "parser.h"
#include "main.h"


int ProcessLine(char *line, char *searchPattern) {

	regex_t *preg;
	int iRC;
	char buffer[80]; 


	preg = malloc(sizeof(regex_t));
	if (NULL == preg) {
		// malloc failed
		return(-1);	
	}

	//iRC = regcomp(preg,"^[A-Z]+$",REG_NOSUB|REG_NEWLINE);
	//iRC = regcomp(preg,"^[A-Z]+$",REG_EXTENDED|REG_NOSUB|REG_NEWLINE);
	//iRC = regcomp(preg,"^[A-Z]+[[:space:]]$",REG_EXTENDED|REG_NOSUB);
	//iRC = regcomp(preg,"^[A-Z]+\\s",REG_EXTENDED|REG_NOSUB);
	iRC = regcomp(preg,searchPattern,REG_EXTENDED|REG_NOSUB);
	if (0 != iRC ) {
		// regex compile failed.
		return(-2);	
	}

	//iRC = regexec(preg,line,0,NULL,REG_NOTEOL);
	iRC = regexec(preg,line,0,NULL,0);
	if (REG_NOMATCH == iRC ) {
		// regexec failed to find a match
		regerror (iRC, preg, buffer, 80);
		//printf("%s\n",buffer);
		goto processline_cleanup;
	} else  if (0 != iRC ) {
		// regexec had some other error.
		regerror (iRC, preg, buffer, 80);
		printf("%s\n",buffer);
		goto processline_cleanup;
	} 

	// A match was found
	//printf("%s",line);

processline_cleanup:
	regfree(preg);
	free(preg);

	return(iRC);


}



