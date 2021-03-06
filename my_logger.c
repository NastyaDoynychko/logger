#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

FILE *fp ;

typedef enum
{
    INFO,
    WARNINING,
    ERROR,
    FATAL
} LEVELS;

typedef struct
{
    LEVELS my_level;
    char *filename;
} LOGGER;

char* print_time()

{
    time_t timer = time(NULL);
    return ctime(&timer);
}

void log_print(LOGGER my_log, LEVELS prog_log, const char* fmt,...)
{
    
    fp = fopen(my_log.filename,"a");
    
    if (!fp)
    {
        fprintf(stderr, "Can't create or open file log.txt \n");
        return;
    }
    
    if (my_log.my_level < prog_log)
        return;
    
    va_list list;
    fprintf(fp, "%s", print_time());
    va_start( list, fmt );
    vfprintf(fp, fmt, list);
    va_end (list);
    fclose(fp);
    
}


int main()
{
    LOGGER my_log = {ERROR, "log.txt"};
    int i = 5;
    char *s = "mistakes";
    log_print(my_log, WARNINING, "I don't like this %d %s \n",i,s);
    int a = 3;
    if (a < 7)
        log_print(my_log, FATAL, "It is too bad! Your program has a lot of bugs!\n");
    
    return 0;
}
