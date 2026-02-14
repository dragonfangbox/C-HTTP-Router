#include <stdio.h>
#include <string.h>

#include "router.h"

router_t* router_create() {
	router_t* r = malloc(sizeof(router_t));
	
	r->defaultHandler = NULL;
	ARRAY_INIT((&r->routes));

	return r;
}

void router_destroy(router_t* r) {
	for (int i = 0; i < r->routes.size; i++) {
		route_t route = r->routes.data[i];

		free(route.method);
		free(route.path);
	}

	ARRAY_FREE((&r->routes));

	free(r);
}


void router_addRoute(router_t* r, 
					 const char* method, 
					 const char* path,
				 	 void (*handler)(request_t* req, response_t* res))
{
	route_t route;

	route.method = strdup(method);
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
		if (strcmp(req->method, route.method) == 0 && strcmp(req->path, route.path) == 0) {
			route.handler(req, res);
			return 0;
		}
	}

	if (r->defaultHandler != NULL) {
		r->defaultHandler(req, res);
	}

	return 404;
}

void router_printRoutes(router_t* r) {
	printf("--- ROUTES ---\n");

	for (int i = 0; i < r->routes.size; i++) {
		route_t route = r->routes.data[i];

		printf("METHOD: %s, PATH: %s\n", route.method, route.path);
	}

	printf("--------------\n");
}
