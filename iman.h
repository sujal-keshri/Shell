#ifndef __IMAN_H_
#define __IMAN_H_

#include "headers.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>

char *resolve_dns(char *hostname);
void strip_html_tags(char *text);
int iman(char *command);

#endif