#include "iman.h"

char *resolve_dns(char *hostname)
{
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_STREAM; // Use TCP

    struct addrinfo *res;

    if (getaddrinfo(hostname, NULL, &hints, &res) != 0)
        printf("Error: Incorrect hostname\n");
    
    char ip4_add[INET_ADDRSTRLEN];
    void *addr;
    struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
    addr = &(ipv4->sin_addr);
    inet_ntop(res->ai_family, addr, ip4_add, sizeof(ip4_add));

    freeaddrinfo(res);

    char *ip4_add_copy = (char *)malloc(sizeof(char) * INET_ADDRSTRLEN);
    strcpy(ip4_add_copy, ip4_add);

    return ip4_add_copy;
}

void strip_html_tags(char *text)
{
    int original=0;
    int new=0;
    int inside_tag = 0;

    while (text[original]!='\0')
    {
        if (text[original] == '<')
            inside_tag = 1;
        else if (text[original] == '>')
        {
            inside_tag = 0;
            original++;
            continue;
        }
        else if (inside_tag==0)
        {
            if (text[original] == '&')
            {
                if (strncmp(text+original, "&amp;", 5) == 0)
                {
                    text[new++] = '&';
                    original += 5;
                }
                else if (strncmp(text+original, "&lt;", 4) == 0)
                {
                    text[new++] = '<';
                    original += 4;
                }
                else if (strncmp(text+original, "&gt;", 4) == 0)
                {
                    text[new++] = '>';
                    original += 4;
                }
                else if (strncmp(text+original, "&quot;", 6) == 0)
                {
                    text[new++] = '"';
                    original += 6;
                }
                else if (strncmp(text+original, "&apos;", 6) == 0)
                {
                    text[new++] = '\'';
                    original += 6;
                }
                else
                    text[new++] = text[original];
            }
            else
                text[new++] = text[original];
        }
        original++;
    }
    text[new] = '\0';
}

int iman(char *command)
{
    const char *ip4_add = resolve_dns("man.he.net");
    int port = 80;

    int sockt = socket(AF_INET, SOCK_STREAM, 0);
    if (sockt == -1)
    {
        perror("Error creating socket");
        return 1;
    }

    struct sockaddr_in serv_add;
    serv_add.sin_family = AF_INET;
    serv_add.sin_port = htons(port);

    if (inet_pton(AF_INET, ip4_add, &serv_add.sin_addr) <= 0)
    {
        perror("Error converting ip address to binary format");
        return 1;
    }

    if (connect(sockt, (struct sockaddr *)&serv_add, sizeof(serv_add)) == -1)
    {
        perror("Error connecting to server");
        return 1;
    }

    char request[1024];
    snprintf(request, sizeof(request), "GET /?topic=%s&section=all HTTP/1.1\r\nHost: man.he.net\r\n\r\n", command);

    if (send(sockt, request, strlen(request), 0) == -1)
    {
        perror("send");
        return 1;
    }

    char response_buffer[4096];
    int bytes_received;

    char html_content[50000]; 
    int html_len = 0;

    html_content[0]='\0';

    while ((bytes_received = recv(sockt, response_buffer, sizeof(response_buffer) - 1, 0)) > 0)
    {
        response_buffer[bytes_received] = '\0'; // Null-terminate the received data

        if (html_len + bytes_received < sizeof(html_content))
        {
            strcat(html_content, response_buffer);
            html_len += bytes_received;
        }
        else
            break; // Break if we're about to overflow the buffer
    }

    if (bytes_received < 0)
        perror("recv");

    close(sockt);

    html_content[html_len] = '\0';


    strip_html_tags(html_content);
    if(strstr(html_content, "No matches for"))
    {
        printf("No such command\n");
        return 0;
    }
    char *start = "NAME";
    char *end = "Man Pages Copyright";
    int start_index = strstr(html_content, start) - html_content;
    int end_index = strstr(html_content, end) - html_content;
    for (int i = start_index; i < end_index; i++)
        printf("%c", html_content[i]);

    return 0;
}