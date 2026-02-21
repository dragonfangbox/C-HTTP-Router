#include <stdio.h>
#include <string.h>

#include "router.h"

// url params work like this: https://website.com?helloworld=12345&yourmom=hi
//												 ^ params start	  ^end of param
router_t* router_create() {
	router_t* r = malloc(sizeof(router_t));
	
	r->defaultHandler = NULL;
	ARRAY_INIT((&r->routes));

	return r;
}

void router_setDefaultHandler(router_t* r, void (*handler)(request_t* req, response_t* res)) {
	r->defaultHandler = handler;
}

void router_destroy(router_t* r) {
	for (int i = 0; i < r->routes.size; i++) {
		route_t route = r->routes.data[i];

		free(route.path);
	}

	ARRAY_FREE((&r->routes));

	free(r);
}


void router_addRoute(router_t* r, 
					 const int method, 
					 const char* path,
				 	 void (*handler)(request_t* req, response_t* res))
{
	route_t route;

	route.method = method;
	route.path = strdup(path);
	route.handler = handler;

	ARRAY_APPEND((&r->routes), (route));
}

int router_handleRoute(router_t* r, 
					   request_t* req,
					   response_t* res)
{
	for (int i = 0; i < r->routes.size; i++) {
		route_t route = r->routes.data[i];
		if (route.method == req->method && strcmp(req->path, route.path) == 0) {
			route.handler(req, res);
			return 0;
		}
	}

	if (r->defaultHandler != NULL) {
		r->defaultHandler(req, res);
	}

	return 404;
}

void* router_getQueryParam(const char* path, char* param) {
	char* params = strdup(path);
	char* tok = strtok(params, "&");
	if (tok == NULL) {
		return 0;
	}

	while(tok != NULL) {
		if (strstr(tok, param) != NULL) {
			char* val = strchr(tok, '=') + 1;
			return val;
		}

		tok = strtok(0, "?");
	}

	return 0;
}

void router_printMethods() {
	printf("--- METHODS ---\n");
	printf("GET: %d\n", GET);
	printf("POST: %d\n", POST);
	printf("PUT: %d\n", PUT);
	printf("DELETE: %d\n", DELETE);
}

void router_printRoutes(router_t* r) {
	printf("--- ROUTES ---\n");

	for (int i = 0; i < r->routes.size; i++) {
		route_t route = r->routes.data[i];

		printf("METHOD: %d, PATH: %s\n", route.method, route.path);
	}
}
