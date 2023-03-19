/***********************************************************************************************
////////////////////////////////////////////////////////////////////////////////////////////////
*
* @file:preprocessor.c
* @brief: This file contains all the function definition for including header files, macro
*           expansion, comment removal, conditional compilation, etc.
*
* @uthor: Amar G Shinde
* @created: 19/03/2023.
*
////////////////////////////////////////////////////////////////////////////////////////////////
************************************************************************************************/

#include"preprocessor.h"

/*****************************************************************************************************/
NLINES_e RemoveComments( char * line )
{
    char *ptr1, *ptr2;
    int i = 0, j = 0;

    ptr1 = ptr2 = line;
    //printf("%s........\n", ptr1);
    printf("\n");
    while( *ptr1 != '\0' )
    {
        printf("%c ", *ptr2);
        if( *ptr1 == '/' )
        {
            //printf("%c inside....\n", *ptr2);
            ptr2 = ptr1;
            DEBUGER(1, singleline )
            if ( ( (*ptr2 == '/') && (*(ptr2+1) == '/') ) )
            {
                DEBUGER(2, singleline )
                while( *ptr2 != '\0' )
                {
                    *ptr2 = ' ';
                    ptr2++;
                }
                return stop;
            }
            else if ( ( (*ptr2 == '/') && (*(ptr2+1) == '*' ) ) )
            {
                i = 0, j = 0;
                while( (ptr2[i] != '\0') && (ptr2[i] != '*' || ptr2[i+1] != '/') )
                    i++;
                i++;
                while( i >= 0 )
                {
                    j = 0;
                    while( ptr2[j] != '\0' )
                    {
                        ptr2[j] = ptr2[j+1];
                        j++;
                    }
                    i--;
                }
                if( *ptr2 != '\0' )
                    ptr2--;
            }
            ptr1 = ptr2;
        }
        ptr1++;
    }
    return stop;
}

/***************************************************************************************************/
void MacroReplacement(const char * macro , FILE * fp )
{
    while( *macro != ' ' ) //till define
        macro++;
    while( *macro == ' ' ) //upto macro name
        macro++;
    while( *macro != ' ' )//till macro name
        macro++;
    while( *macro == ' ' )//upto macro body
        macro++;
    fprintf(fp, "%s", macro);
}

/***********************************************************************************/
void IncludeHeaderFiles( char * line )
{
    char * ptr1, * ptr2;
    char filename[15];
    int i = 0;

    ptr1 = ptr2 = line;

    while( *ptr1 != '\0' )
    {
        if( *ptr1 == '#' )
        {
            ptr2 = ptr1;
            if( my_strstr( ptr2+1, "include" ) != NULL )
            {
                while( *ptr2 != '\0' )
                {
                    if( *ptr2 == '<' ) /* traverse if spaces present
                                                in #include & <file.h> OR "file.h"
                                            */
                        break;
                    else if( *ptr2 == '"' )
                        break;
                    ptr2++;
                }
                if( *(ptr2) == '<' ) /* predefined header */
                {
                    ptr2++;
                    i = 0;
                    while( (ptr2[i] != '>') && (ptr2[i] != '\0') )
                    {
                        filename[i] = ptr2[i];
                        i++;
                    }
                    filename[i] = '\0';
                    IncludePredefined(filename);
                    printf("%s\n", filename);
                }
                else if( *(ptr2) == '"' ) /* user-defined header */
                {
                    ptr2++;
                    i = 0;
                    while( (ptr2[i] != '"') && (ptr2[i] != '\0') )
                    {
                        filename[i] = ptr2[i];
                        i++;
                    }
                    filename[i] = '\0';
                    IncludeUserdefined(filename);
                }
                ptr1 = ptr2;
            }
        }
        ptr1++;
    }
}


/***************************************************************************************/
int IncludeUserdefined( const char * filename )
{
    int done = ReplaceHeaderFile(filename);
    if( done == 1 ) {
        printf("Header file %s is included successfully.\n", filename);
    }
    else
        printf("Header file %s is not available.\n", filename);
}


/*********************************************************************************/
int IncludePredefined( const char * filename )
{
    int done = 0;
    if( my_strstr(filename, "stdio.h") != NULL ) {
#if (DEBUG==1)
        printf("Replacement:%s \n", filename);
#endif //DEBUG
        done = ReplaceHeaderFile("/usr/include/stdio.h");
    }

    else if( my_strstr(filename, "stdlib.h") != NULL ) {
#if (DEBUG==1)
        printf("Replacement:%s \n", filename);
#endif //DEBUG
        done = ReplaceHeaderFile("/usr/include/stdlib.h");
    }

    else if( my_strstr(filename, "string.h") != NULL ) {
#if (DEBUG==1)
        printf("Replacement:%s \n", filename);
#endif //DEBUG
        done = ReplaceHeaderFile("/usr/include/string.h");
    }

    else if(  my_strstr(filename, "unistd.h") != NULL ) {
#if (DEBUG==1)
        printf("Replacement:%s \n", filename);
#endif //DEBUG
        done = ReplaceHeaderFile("/usr/include/unistd.h");
    }

    if( done == SUCCESS ) {
        printf("Header file %s is included successfully.\n", filename);
        return SUCCESS; //success
    }
    else{
        printf("Header file %s is not available.\n", filename);
        return FAIL; //fail.
    }
}


/****************************************************************************************/
int ReplaceHeaderFile( const char * filename )
{
    FILE * fsrc, *fdest;
    char * buf;

    if( (fsrc = fopen(filename, "r")) != NULL ) /* open the source header file to include */
    { /* if header file opened successfully then read file and write into .i file */
        if( (buf = malloc(200 * sizeof(char))) == NULL ){
            return;
        }

        fdest = fopen("dest2.txt", "a"); /* open the destination .i file */

        while( fscanf(fsrc, " %[^\n]", buf) != EOF )
        {
            fprintf(fdest, "%s\n", buf); /* write into dest file */
        }
        fclose(fsrc);   /* close the source header file */
        fclose(fdest);  /* close the destination .i file */
        free(buf);      /* deallocate the buffer */
        return SUCCESS;
    }
    return FAIL;
}

/****************************************************************************************************/
char * my_strstr(const char * str1, const char * str2 )
{
    char *p, *q;
    p = str1;
    q = str2;
    int i = 0;

    while( *str1 != '\0' )
    {
        if( *str1 == *str2 )
        {
            p = str1;
            while( *q != '\0' )
            {
                if( *p != *q )
                    break;
                p++, q++;
            }
            if( *q == '\0' )
            {
                //printf("TREU:final...q=%s\n", q );
                //printf("TREU:final...p=%s\n", p );
                return (char *)str1;
            }
            else{
                //printf("FALSE:final...q=%s\n", q );
                //printf("FALSE:final...p=%s\n\n", p );
            }

        }
        str1++;
    }
    return NULL;
}

/*****************************************************************************************************/
char * my_strchr( const char * str , char ch )
{
    while( *str != '\0' )
    {
        if( *str == ch )
            return str;
        str++;
    }
    return NULL;
}

/*****************************************************************************************************/
