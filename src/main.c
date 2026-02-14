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

	router_addRoute(router, "GET", "/", root);

	router_printRoutes(router);

	request_t req = {"GET", "/"}; 
	response_t res;

	if(router_handleRoute(router, &req, &res) != 0) {
		printf("--- Route not found! ---\n");
	} else {
		printf("--- Route found! ---\n");
	}

	router_destroy(router);

	return 0;
}
