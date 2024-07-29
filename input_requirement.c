#include "input_requirement.h"

void remove_whitespaces(char* input)
{
    char temp[1000];
    int i_b=0;
    if(input[0]!=' ' && input[0]!='\t')
        temp[i_b++]=input[0];
    for(int i=1; i<strlen(input); i++)
    {
        if((input[i]==' ' && (input[i-1]==' ' || input[i-1]=='\t')) ||  (input[i]=='\t' && (input[i-1]==' ' || input[i-1]=='\t')))
            continue;
        else if(input[i]=='\t')
            temp[i_b++]=' ';
        else
            temp[i_b++]=input[i];
    }
    temp[i_b++]='\0';
    if(temp[strlen(temp)-1]==' ')
        temp[strlen(temp)-1]='\0';
    strcpy(input, temp);
}

st_tokens tokenize(char* input)
{
    int n_commands=0;
    char** tokens=(char**)malloc(sizeof(char*)*50);
    for(int i=0; i<50; i++)
        tokens[i]=(char*)malloc(sizeof(char)*512);

    char* temp;
    temp=strtok(input, ";&");
    while(temp!=NULL)
    {
        strcpy(tokens[n_commands], temp);
        remove_whitespaces(tokens[n_commands++]);
        temp=strtok(NULL, ";&");
    }

    st_tokens commands;
    commands.tokens=tokens;
    commands.n_commands=n_commands;

    return commands;
}

char* symbol_str(char* input)
{
    char* symbol_str=(char*)malloc(sizeof(char)*50);
    int s_count=0;
    char temp=input[0];
    int i=1;
    while(temp != '\0')
    {
        if(temp==';' || temp =='&')
            symbol_str[s_count++]=temp;
        temp=input[i++];
    }
    symbol_str[s_count++]='\0';
    return symbol_str;
}