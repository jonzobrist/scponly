#include <stdio.h>	// FILENAME_MAX
#include "config.h"

#define MAX_USERNAME 32
#define MAX_REQUEST (1024)		// any request exceeding this is truncated
#define MAX_ARGC 100			// be reasonable
#define ALLOWABLE "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890 ./-*\\_\'\":?()"
#define WHITE " \t"			// whitespace
#define exact_match(x,y) (0==strcmp(x,y))	// we dont want strncpy for this
#define LOGIDENT "scponly"

#define WINSCP_EOF_REQ_RETVAL	" ; echo \"WinSCP: this is end-of-file:$?\""
#define WINSCP_EOF_REQ_ZERO	" ; echo \"WinSCP: this is end-of-file:0\""
#define WINSCP_EOF_REQ_STATUS " ; echo \"WinSCP: this is end-of-file:$status\""
#define WINSCP_BOF_REQ		"echo \"WinSCP: this is begin-of-file\" ; "

#define WINSCP_EOF      "WinSCP: this is end-of-file:"
#define WINSCP_BOF      "WinSCP: this is begin-of-file"

typedef struct
{
	char *name;
	int argflag;
} cmd_t;

typedef struct
{
	char *name;
	char *badarg;
} cmd_arg_t;
 
/*
 * function prototypes
 */
inline char *strbeg (char *, char *);
inline char *strend (char *, char *);
int valid_chars(char *);
int get_uservar(void);
void show_usage(void);
char *logstamp();
int cntchr(char *, char);
char **build_arg_vector(char *);
char **expand_wildcards(char **);
int valid_arg_vector(char **);
char *substitute_known_path(char *);
char *flatten_vector(char **);
void discard_vector(char **);
int check_dangerous_args(char **av);
