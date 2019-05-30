/* --------------------------------------------------------------------------
   Silgy Web App
   Jurek Muszynski
-----------------------------------------------------------------------------
   Web App Performance Tester
-------------------------------------------------------------------------- */


#include <silgy.h>


/* --------------------------------------------------------------------------
   Output HTML & page header
-------------------------------------------------------------------------- */
void gen_header(int ci)
{
    OUT("<!DOCTYPE html>");
    OUT("<html>");
    OUT("<head>");
    OUT("<title>%s</title>", APP_WEBSITE);
    if ( REQ_MOB )  // if mobile request
        OUT("<meta name=\"viewport\" content=\"width=device-width\">");
    OUT("<link rel=\"stylesheet\" type=\"text/css\" href=\"dsk.css\">");
    OUT("<script src=\"dsk.js\"></script>");
    OUT("</head>");

    OUT("<body>");

    if ( REQ("") || REQ("dashboard") )
        OUT("<h1>%s</h1>", APP_WEBSITE);
    else
        OUT("<h1><a href=\"/\" %s>%s</a></h1>", WAIT, APP_WEBSITE);

    char lnk_home[256]="<a href=\"/\" onClick=\"wait();\">Home</a>";

    if ( REQ("") )
        strcpy(lnk_home, "Home");

    OUT("<div class=mm>");
    if ( !REQ("") ) OUT(lnk_home);
    OUT("</div>");
}


/* --------------------------------------------------------------------------
   Output footer; body & html tags close here
-------------------------------------------------------------------------- */
void gen_footer(int ci)
{
    OUT("<div id=\"wait\" class=wt></div>");
    OUT("</body></html>");
}


/* --------------------------------------------------------------------------
   Show main page
-------------------------------------------------------------------------- */
void gen_page_main(int ci)
{
    gen_header(ci);

    OUT("<table class=m10>");
    OUT("<tr><td class=\"gr rt\">URL:</td><td><input id=\"url\" style=\"width:40em;\" value=\"127.0.0.1:1234\" autofocus %s></td></tr>", ONKEYDOWN);
    OUT("<tr><td class=\"gr rt\">Batches:</td><td><input id=\"batches\" value=\"1\" %s></td></tr>", ONKEYDOWN);
    OUT("<tr><td class=\"gr rt\">Times:</td><td><input id=\"times\" value=\"10\" %s></td></tr>", ONKEYDOWN);
    OUT("<tr><td></td><td><button id=\"sbm\" onClick=\"sendreqs();\" style=\"width:7em;height:2.2em;\">Go!</button></td></tr>");
    OUT("</table>");

    gen_footer(ci);
}


/* --------------------------------------------------------------------------
   Send requests (AJAX)
-------------------------------------------------------------------------- */
void sendreqs(int ci)
{
    QSVAL batch;
    if ( !QS("batch", batch) ) return;
    QSVAL url;
    if ( !QS("url", url) ) return;
    QSVAL times;
    if ( !QS("times", times) ) return;

    AUS.batch = atoi(batch);
    strcpy(AUS.url, url);
    AUS.times = atoi(times);
    if ( AUS.times < 1 ) AUS.times = 1;
    if ( AUS.times > 1000 ) AUS.times = 1000;

    INF("batch = %d", AUS.batch);
    INF("URL [%s]", AUS.url);
    INF("times = %d", AUS.times);

    CALL_ASYNC_TM("sendreqs", 600);   // 10 minutes timeout
}


/* --------------------------------------------------------------------------------
   Called after parsing HTTP request header
   ------------------------------
   This is the main entry point for a request
   ------------------------------
   Response status will be 200 by default
   Use RES_STATUS() if you want to change it
-------------------------------------------------------------------------------- */
void silgy_app_main(int ci)
{
    if ( REQ("sendreqs") )
        sendreqs(ci);
    else
        gen_page_main(ci);
}


/* --------------------------------------------------------------------------------
   Called when application starts
   ------------------------------
   Return true if everything OK
   ------------------------------
   Returning false will stop booting process,
   silgy_app_done() will be called and application will be terminated
-------------------------------------------------------------------------------- */
bool silgy_app_init(int argc, char *argv[])
{
    return true;
}


/* --------------------------------------------------------------------------------
   Called when new anonymous user session starts
   ------------------------------
   Return true if everything OK
   ------------------------------
   Returning false will cause the session to be closed
   and silgy_app_session_done() will be called
   Response status will be set to 500
-------------------------------------------------------------------------------- */
bool silgy_app_session_init(int ci)
{
    return true;
}


/* --------------------------------------------------------------------------------
   ******* Only for USERS *******
   ------------------------------
   Called after successful authentication (using password or cookie)
   when user session is upgraded from anonymous to logged in
   ------------------------------
   Return true if everything OK
   ------------------------------
   Returning false will cause the session to be downgraded back to anonymous
   and silgy_app_user_logout() will be called
-------------------------------------------------------------------------------- */
bool silgy_app_user_login(int ci)
{
    return true;
}


/* --------------------------------------------------------------------------------
   ******* Only for USERS *******
   ------------------------------
   Called when downgrading logged in user session to anonymous
-------------------------------------------------------------------------------- */
void silgy_app_user_logout(int ci)
{
}


/* --------------------------------------------------------------------------------
   Called when closing anonymous user session
   After calling this the session memory will be zero-ed
-------------------------------------------------------------------------------- */
void silgy_app_session_done(int ci)
{
}


/* --------------------------------------------------------------------------------
   Called when application shuts down
-------------------------------------------------------------------------------- */
void silgy_app_done()
{
}
