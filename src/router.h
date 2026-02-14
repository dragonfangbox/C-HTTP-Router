#ifndef ROUTER_H
#define ROUTER_H

#include "dynarr.h"

typedef struct {
	const char* method;
	const char* path;
} request_t;

typedef struct {
	int code;
	char* body;
} response_t;

typedef struct {
	char* method;
	char* path;
	void (*handler)(request_t* req, response_t* res);
} route_t;

ARRAY_DEFINE(routes_t, route_t);

typedef struct {
	routes_t routes;
	void (*defaultHandler)(request_t* req, response_t* res);
} router_t;

router_t* router_create();
void router_destroy(router_t* r);

void router_addRoute(router_t* r, 
					 const char* method, 
					 const char* path,
				 	 void (*handler)(request_t* req, response_t* res));

int router_handleRoute(router_t* r, 
						request_t* req,
						response_t* res);

void router_printRoutes(router_t* r);

#endif
