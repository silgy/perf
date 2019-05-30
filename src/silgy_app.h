/* --------------------------------------------------------------------------
   Silgy Web App
   Jurek Muszynski
-----------------------------------------------------------------------------
   Web App Performance Tester
-------------------------------------------------------------------------- */

#ifndef SILGY_APP_H
#define SILGY_APP_H


#define APP_WEBSITE                 "Web App Performance Tester"
#define APP_VERSION                 "0.5"
#define DEF_RES_AUTH_LEVEL          AUTH_LEVEL_ANONYMOUS


#define ASYNC
#define APP_ASYNC_ID                3
#define ASYNC_AUSES

#define MEM_MEDIUM
#define SILGY_AS_BOT

#define WAIT                        "onClick=\"wait();\""
#define ONKEYDOWN                   "onkeydown=\"ent(event);\""


/* app user session */

typedef struct {
    char url[256];
    int  batch;
    int  times;
    double elapsed;
} ausession_t;


#endif  /* SILGY_APP_H */
