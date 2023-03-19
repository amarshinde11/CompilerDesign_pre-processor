/***********************************************************************************************
////////////////////////////////////////////////////////////////////////////////////////////////
*
* @file:preprocessor.h
* @brief: This file contains all the function prototypes for including header files, macro
*           expansion, comment removal, conditional compilation, etc.
*
* @uthor: Amar G Shinde
* @created: 19/03/2023.
*
////////////////////////////////////////////////////////////////////////////////////////////////
************************************************************************************************/
#ifndef   __PRE_PROCESSOR_H
#define   __PRE_PROCESSOR_H

#include <stdio.h>
#include <stdlib.h>


/*
C:\Users\hp\Downloads\codeblocks-20.03mingw-32bit-nosetup\MinGW\x86_64-w64-mingw32\include\stdio.h
*/
#define SUCCESS     (1)
#define FAIL        (0)
#define BACKUPCODE  (0)
#define TEST        (0)
#define DEBUG       (1)
#define DEBUGER(x, FUNC) printf("Debug: %d Inside a function => %s\n", x, #FUNC);

typedef enum commentlinecount {
    single  = 0,
    stop    = 0,
    conti   = 1,
    multi   = 1
}NLINES_e;

char * my_strstr(const char * str1, const char * str2 );
char * my_strchr( const char * str , char ch );

void IncludeHeaderFiles( char * line );
int IncludeUserdefined( const char * filename );
int IncludePredefined( const char * filename );
int ReplaceHeaderFile( const char * filename );
NLINES_e RemoveComments( char * line );



#endif
