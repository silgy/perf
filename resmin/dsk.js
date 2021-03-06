var started;
var batches_done=0;
var elapsed=0;


// --------------------------------------------------------------------------
// show wait animation
// --------------------------------------------------------------------------
function wait()
{
    if ( !document.getElementById("wait") )
    {
        let w = document.createElement("div");
        w.id = "wait";
        w.className = "wt";
        w.style.display = "block";
        document.body.appendChild(w);
    }
    else
        document.getElementById("wait").style.display = "block";
}


// --------------------------------------------------------------------------
// turn the spinning wheel off
// --------------------------------------------------------------------------
function wait_off()
{
    document.getElementById("wait").style.display = "none";
}


// --------------------------------------------------------------------------
// go to link
// --------------------------------------------------------------------------
function gt(l)
{
    wait();
    window.location.href = l;
}


// --------------------------------------------------------------------------
// Enter key hit
// --------------------------------------------------------------------------
function ent(e)
{
    if (e.keyCode==13)  // Enter
    {
        document.getElementById("sbm").click(); // submit
        return false;
    }
    else if (e.keyCode==27) // Esc
    {
        document.getElementById("cnc").click(); // cancel
        return false;
    }
    return true;
}


// --------------------------------------------------------------------------
// Add paragraph
// --------------------------------------------------------------------------
function p(t, c)
{
    let p = document.createElement("p");
    p.innerHTML = t;
    if ( c )
        c.appendChild(p);
    else
        document.body.appendChild(p);
}


// --------------------------------------------------------------------------
// AJAX call
// --------------------------------------------------------------------------
function sendreqs()
{
    wait();

    let url = document.getElementById("url").value;
    let batches = document.getElementById("batches").value;
    let times = document.getElementById("times").value;

    if ( batches < 1 ) batches = 1;
    if ( batches > 1000 ) batches = 1000;

    if ( times < 1 ) times = 1;
    if ( times > 1000 ) times = 1000;

    p("&nbsp;");

    p("Sending "+batches+" batch(es) of "+times+" requests each to "+url);

    url = encodeURIComponent(url);

    batches_done = 0;
    started = performance.now();
    elapsed = 0;

    for ( i=1; i<=batches; ++i )
        sendbatch(url, times, i, batches);

    document.getElementById("url").focus();
}


// --------------------------------------------------------------------------
// Send one request
// --------------------------------------------------------------------------
function sendbatch(url, times, i, batches)
{
    let x = new XMLHttpRequest();

    x.onreadystatechange = function(e)
    {
        if ( x.readyState == 4 )    // Done
        {
            ++batches_done;

            let ret = x.responseText.split("|");

            if ( ret[0]=="0" )  // OK
            {
                p(i+": Average = "+ret[2]+" ms");

//                elapsed += Number(ret[3]);

                if ( batches_done==batches )    // the last one
                {
                    elapsed = performance.now() - started;
                    wait_off();
                    p("elapsed: "+elapsed+" ms");
                    let seconds = elapsed / 1000;
//                    p("seconds: "+seconds);
                    let per_second = (times*batches) / seconds;
                    p(parseInt(per_second, 10) + " per second");
                }
            }
            else    // error
            {
                p(i+": Error: "+ret[1]);
            }
        }
    };

//    p("Sending batch #"+i+"...");
    x.open("GET", "sendreqs?batch="+i+"&url="+url+"&times="+times, true);
    x.send();
//    p("Batch #"+i+" sent");
}
