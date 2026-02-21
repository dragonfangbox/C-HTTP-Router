# C HTTP Router

A simple, lightweight router in C.

## EXAMPLE USAGE

```C
#include "router.h"

    // create a default handler that gets called when no route is found.
    void defaultHandler(request_t* req, response_t* res) {
        res->code = 404;
        res->body = "404: Page not found!";
    }

    // create a handler
    void root(request_t* req, response_t* res) {
        res->code = 200;
        res->body = "some json or html or something...";
    }

    int main() {
        // initalize a new router
        router_t* router = router_create();

        // set the default handler
        router_setDefaultHandler(router, defaultHandler);

        // create a new route
        router_addRoute(router, GET, "/foo?bar=123", root);

        // print all routes for debugging
        router_printRoutes(router);

        // print all method enum values
        router_printMethods();

        // create a request and a response structure
        request_t req = ...;
        response_t res;

        // handle the request and set the response
        if(router_handleRoute(router, &req, &res) != 0) {
            printf("--- Route not found! ---\n");
        } else {
            printf("--- Route found! ---\n");
        }

        // get a query paramter
        void* value = router_getQueryParam(req.path, "bar");

        // free the router
        router_destroy(router);

        return 0;
}
```

### TODO

* Query param function currently doesn't detect the type of the parameter and only returns it as a string
