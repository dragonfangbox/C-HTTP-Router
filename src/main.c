/* 
 * i use this file for testing out my code 
 * please ignore :)
 */

#include "router.h"

void defaultHandler(request_t* req, response_t* res) {
	res->code = 404;
	res->body = "404: Page not found!";
}

void root(request_t* req, response_t* res) {
	res->code = 200;
	res->body = "some json or html or something...";
}

int main() {
	router_t* router = router_create();
	router_setDefaultHandler(router, defaultHandler);

	router_addRoute(router, GET, "/", root);

	router_printRoutes(router);
	router_printMethods();

	response_t res;
	request_t req = {GET, "yourmother/hi&what=yourmother?hello=192"}; 

	if(router_handleRoute(router, &req, &res) != 0) {
		printf("--- Route not found! ---\n");
		printf("Body: %s\n", res.body);
	} else {
		printf("--- Route found! ---\n");
		printf("Body: %s\n", res.body);
	}

	req.method = 127;
	if(router_handleRoute(router, &req, &res) != 0) {
		printf("--- Route not found! ---\n");
		printf("Body: %s\n", res.body);
	} else {
		printf("--- Route found! ---\n");
		printf("Body: %s\n", res.body);
	}

	char* val = router_getQueryParam(req.path, "what");
	printf("query value: %s\n", val);

	router_destroy(router);

	return 0;
}
