/* --------------------------------------------------------------------------
   Silgy Web App
   Jurek Muszynski
   Started: August 2015
-----------------------------------------------------------------------------
   Sample service module
-------------------------------------------------------------------------- */


#include "silgy.h"


int getCustomer(const char *req, char *res);
int getAccounts(const char *req, char *res);


/* --------------------------------------------------------------------------
   Entry point
-------------------------------------------------------------------------- */
int service_app_process_req(const char *service, const char *req, char *res)
{
    if ( S("getCustomer") )
        return getCustomer(req, res);
    else if ( S("getAccounts") )
        return getAccounts(req, res);

    return ERR_ASYNC_NO_SUCH_SERVICE;
}


/* --------------------------------------------------------------------------
   Service
-------------------------------------------------------------------------- */
int getCustomer(const char *req, char *res)
{
    strcpy(res, "Hello from getCustomer service!");
    return OK;
}


/* --------------------------------------------------------------------------
   Service
-------------------------------------------------------------------------- */
int getAccounts(const char *req, char *res)
{
    strcpy(res, "Hello from getAccounts service!");
    return OK;
}




/* --------------------------------------------------------------------------
   Server start
   Return TRUE if successful
-------------------------------------------------------------------------- */
bool service_init()
{
    return TRUE;
}


/* --------------------------------------------------------------------------
   Server stop
-------------------------------------------------------------------------- */
void service_done()
{
}
