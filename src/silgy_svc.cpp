/* --------------------------------------------------------------------------
   Silgy Web App
   Jurek Muszynski
-----------------------------------------------------------------------------
   Web App Performance Tester
-------------------------------------------------------------------------- */


#include <silgy.h>


/* ======================================================================= */
/* =============================== SERVICES ============================== */
/* ======================================================================= */


/* --------------------------------------------------------------------------
   Service
-------------------------------------------------------------------------- */
int sendreqs()
{
    INF("sendreqs");

    INF("batch = %d", AUS.batch);
    INF("URL [%s]", AUS.url);
    INF("times = %d", AUS.times);

    struct timespec start;
    clock_gettime(MONOTONIC_CLOCK_NAME, &start);

    str1k tmp;

    for ( int i=0; i<AUS.times; ++i )
    {
        DBG_LINE_LONG;
        DBG_LINE_LONG;

        sprintf(tmp, "%02d%02d%02d%04d%04d", G_ptm->tm_hour, G_ptm->tm_min, G_ptm->tm_sec, AUS.batch, i);
        DBG("perfreqid: %s", tmp);
        REST_HEADER_SET("perfreqid", tmp);

        if ( !CALL_HTTP(NULL, NULL, "GET", AUS.url) )
        {
            ERR("Remote call failed\n");
            AUS.elapsed = lib_elapsed(&start);
            return ERR_REMOTE_CALL;
        }
//        else if ( !CALL_HTTP_STATUS_OK )
//        {
//            WAR("Remote call status %d", CALL_HTTP_STATUS);
//            return ERR_REMOTE_CALL_STATUS;
//        }

        DBG("Remote call OK\n");
    }

    AUS.elapsed = lib_elapsed(&start);

    INF("elapsed: %.3lf ms\n", AUS.elapsed);

    return OK;
}




/* ======================================================================= */
/* ========================== END OF SERVICES ============================ */
/* ======================================================================= */



/* --------------------------------------------------------------------------
   Entry point
-------------------------------------------------------------------------- */
void silgy_svc_main()
{
    if ( SVC("sendreqs") )
        ASYNC_ERR_CODE = sendreqs();

    OUT("%d|", ASYNC_ERR_CODE);

    if ( ASYNC_ERR_CODE == ERR_REMOTE_CALL )
        OUT("Call failed");
    else if ( ASYNC_ERR_CODE == ERR_REMOTE_CALL_STATUS )
        OUT("Call response status wasn't successful");
    else if ( ASYNC_ERR_CODE == OK )
        OUT("OK");

    char formatted[64];
    amtd(formatted, G_rest_average);
    OUT("|%s", formatted);
    OUT("|%f", AUS.elapsed);

    RES_DONT_CACHE;
}


/* --------------------------------------------------------------------------
   Server start
   Return true if successful
-------------------------------------------------------------------------- */
bool silgy_svc_init()
{
    return true;
}


/* --------------------------------------------------------------------------
   Server stop
-------------------------------------------------------------------------- */
void silgy_svc_done()
{
}
