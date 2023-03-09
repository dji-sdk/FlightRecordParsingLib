/*
 * NEVER EVER edit this manually, fix the mkhelp.pl script instead!
 */
#ifdef USE_MANUAL
#include "tool_hugehelp.h"
void hugehelp(void)
{
   fputs(
"                                  _   _ ____  _\n"
"  Project                     ___| | | |  _ \\| |\n"
"                             / __| | | | |_) | |\n"
"                            | (__| |_| |  _ <| |___\n"
"                             \\___|\\___/|_| \\_\\_____|\n"
"\n"
, stdout) ;
}
#else /* !USE_MANUAL */
/* built-in manual is disabled, blank function */
#include "tool_hugehelp.h"
void hugehelp(void) {}
#endif /* USE_MANUAL */
