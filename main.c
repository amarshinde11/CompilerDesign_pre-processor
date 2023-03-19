/***********************************************************************************************
////////////////////////////////////////////////////////////////////////////////////////////////
*
* @file: main.c
* @brief: This file contains main function to call all the functions for including header files,
*            macro expansion, comment removal, conditional compilation, etc.
*
* @uthor: Amar G Shinde
* @created: 19/03/2023.
*
////////////////////////////////////////////////////////////////////////////////////////////////
************************************************************************************************/
#include"preprocessor.h"

int main( void )
{
    char * buf;
    FILE * fp1, *fp2;
    NLINES_e flag;

    if ( (fp1 = fopen("dest2.txt", "w")) == NULL )
    {
        printf("File is not opened.\n");
        return;
    }
    fclose(fp1);

    if ( (fp2 = fopen("source.c", "r")) == NULL )
    {
        printf("File is not opened.\n");
        return;
    }

    if ( (buf = malloc(200*sizeof(char))) == NULL ) {
        printf("Memory not allcated.\n");
        return;
    }

    if ( (fp1 = fopen("dest2.txt", "a")) == NULL )
    {
        printf("File is not opened.\n");
        return;
    }
    while( fscanf(fp2, " %[^\n]", buf) != EOF )
    {
        flag = RemoveComments(buf);
        if( flag == stop )
           fprintf(fp1, "%s\n", buf);
    }
    fclose(fp2);
    fclose(fp1);

    if ( (fp1 = fopen("dest2.txt", "a")) == NULL )
    {
        printf("File is not opened.\n");
        return;
    }
    /*
    while( fscanf(fp2, " %[^\n]", buf) != EOF )
    {
        IncludeHeaderFiles(buf);
    }
    */
    fclose(fp2);
    fclose(fp1);

    free(buf);
    return 0;
}

#if (BACKUPCODE==1)
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
#endif

#if (BACKUPCODE==1)
int IncludeUserdefined( const char * filename )
{
    int done = ReplaceHeaderFile(filename);
    if( done == 1 ) {
        printf("Header file %s is included successfully.\n", filename);
    }
    else
        printf("Header file %s is not available.\n", filename);
}
#endif

#if (BACKUPCODE==1)
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
#endif

#if (BACKUPCODE==1)
int IncludePredefined( const char * filename )
{
    FILE * fsrc, * fdest;
    int file;
    char * buf;

    buf = malloc(150 * sizeof (char));
    switch( file )
    {
        case 1: /* include stdio.h */
                printf("%s\n", "stdio.h");
                if( (fsrc = fopen(filename, "r")) != NULL )
                {
                    fdest = fopen("dest2.txt", "a");
                    while( fscanf(fsrc, " %[^\n]", buf) != EOF )
                    {
                    fprintf(fdest, "%s\n", buf);
                    }
                    fclose(fsrc);
                    fclose(fdest);
                }

        break;
        case 2: /* include stdlib.h */
                printf("%s\n", "stdlib.h");
                if( (fsrc = fopen("/usr/include/stdlib.h", "r")) != NULL )
                {
                    fdest = fopen("dest2.txt", "a");
                    while( fscanf(fsrc, " %[^\n]", buf) != EOF )
                    {
                    fprintf(fdest, "%s\n", buf);
                    }
                    fclose(fsrc);
                    fclose(fdest);
                }
        break;
        default:
            printf("file:%s not found.\n", filename );

    }

}
#endif // 0

#if (BACKUPCODE==1)
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
#endif


#if (BACKUPCODE==1)
void ProcessOneLine( const char * buf, FILE * fp1 )
{
     char * p;
    while( *buf != '\0' )
    {
                //DEBUG(while1);
        if( *buf == '#' )
        {
            buf++;
            if( my_strstr(buf, "define") != NULL )
            {
                MacroReplacement(buf, fp1);
                return;
            }
            else if( my_strstr( buf, "include" ) != NULL )
            {
                if( *(buf+7) == '<' )
                {
                    DEBUG(1,PREDEFINED);//
                    return;
                }
                else if( *(buf+7) == '"' )
                {
                    DEBUG(2,PWD);//
                    return;
                }
            }
        }
        else if( *buf != ' ' )
        {
            while( *buf != '\0' )
            {
                if ( ( (*buf == '/') && (*(buf+1) == '/') ))
                {
                    DEBUG(3,IGNORE.....singleline)
                    return;

                }
                else if (( (*buf == '/') && (*(buf+1) == '*' )) )
                {
                    buf++;
                    while( *buf != '/' && *buf != '\0')
                    {
                        DEBUG(4,IGNORE......multiline)
                        buf++;
                    }
                    if( *(buf+1) == '\0' )
                        return;
                }
                else
                {
                            DEBUG(5,STATEMENT...)
                }
                buf++;
            }
            return;
        }
        buf++;
    }
}
#endif

#if (BACKUPCODE==1)
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
#endif

#if (BACKUPCODE==1)
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
#endif
