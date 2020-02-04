#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <conio.h>
#include <string.h>
#include "cJSON.h"
#include "cJSON.c"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define SA struct sockaddr
#define MAX 80
#define PORT 12345
int flag1=0;
char autotoken[100];
//char type1[1000],content[1000];
int  soket()
{
    int client_socket, server_socket;
    struct sockaddr_in servaddr, cli;
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    // Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h
    wVersionRequested = MAKEWORD(2, 2);
    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0)
    {
        // Tell the user that we could not find a usable Winsock DLL.
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }

    // Create and verify socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        printf("Socket creation failed...\n");
        exit(0);
    }
    else
        //printf("Socket successfully created..\n");

        // Assign IP and port
        memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // Connect the client socket to server socket
    if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("Connection to the server failed...\n");
        exit(0);
    }
    else
        return client_socket;
    //printf("Successfully connected to the server..\n");
    return 0;
    // Function for chat
    //chat(client_socket);
    // Close the socket
    //closesocket(client_socket);
}
void registerr()
{
    char user[500],pass[500],req[1000]="register ",respond[1000];
    //char* type1=(char*) malloc(10000*sizeof(char));
    //char* content1=(char*) malloc(10000*sizeof(char));
    char chert1;
    char type1[1000];
    char content1[1000];
    system("cls");
    printf("Enter Username:\n");
    scanf("%c",&chert1);
    gets(user);
    //printf("wsdd %s",user);
    printf("Enter Pasword:\n");
    //scanf("%c",&chert1);
    gets(pass);
    //req[] = "register ";
    strcat(req,user);
    strcat(req,", ");
    strcat(req,pass);
    strcat(req,"\n");
    vasl(req,respond,type1,content1);
    printf("----------%s\n",type1);
    printf("-----------%s\n",content1);
    if (*type1=='S')
    {
        system("cls");
        printf(ANSI_COLOR_GREEN  "user registered successfuly\n" ANSI_COLOR_RESET);
        printf("---------------\n");
        return;
    }
    else
    {
        system("cls");
        printf(ANSI_COLOR_RED  "%s\n" ANSI_COLOR_RESET,content1);
        printf("------------------\n");
        return;
    }
}
void vasl(char req[1000],char *respond,char type1[1000],char content1[1000])
{
    int mysocket=soket();
    send(mysocket,req,1000,0);
    memset(respond,0,1000);
    memset(type1,0,1000);
    memset(content1,0,1000);
    recv(mysocket,respond,1000,0);
    //printf("%s\n",respond);
    cJSON* tarjome= cJSON_Parse(respond);
    //printf("ok2");
    cJSON* type=cJSON_GetObjectItem(tarjome,"type");
    //printf("ok3");
    strcpy(type1,type->valuestring);
    //printf("%s\n",type1);
    //printf("ok4");
    cJSON* content=cJSON_GetObjectItem(tarjome,"content");
    //printf("ok5");
    strcpy(content1,content->valuestring);
    //printf("%s\n",type1);
    //printf("ok6");
}
void vaslrefresh(char req[1000],char respond[1000],char type1[1000])
{
    int mysocket=soket();
    char* sender1=(char*) malloc(500*sizeof(char));
    char* payam1=(char*) malloc(3000*sizeof(char));
    send(mysocket,req,1000,0);
    memset(respond,0,1000);
    recv(mysocket,respond,1000,0);
    printf("%s\n",respond);
    cJSON* tarjome= cJSON_Parse(respond);
    cJSON* type=cJSON_GetObjectItem(tarjome,"type");
    strcpy(type1,type->valuestring);
    cJSON* content=cJSON_GetObjectItem(tarjome,"content");
    if(*type1=='L'){
        /* cJSON* payam=NULL;
        cJSON_ArrayForEach(payam,content){

        } */
        int i;
        system("cls");
        for (i = 0 ; i < cJSON_GetArraySize(content) ; i++){
            cJSON * subitem = cJSON_GetArrayItem(content, i);
            cJSON* sender = cJSON_GetObjectItem(subitem, "sender");
            strcpy(sender1,sender->valuestring);
            cJSON* payam = cJSON_GetObjectItem(subitem, "content");
            strcpy(payam1,payam->valuestring);
            if (!strcmp(sender1,"server")) {
                printf(ANSI_COLOR_YELLOW "%s\n",payam1);
            }
            else{
                printf(ANSI_COLOR_YELLOW"%s :",sender1);
                printf(ANSI_COLOR_YELLOW "%s\n",payam1);
            }
        }
        free(sender1);
        free(payam1);
    }
    else {
            system("cls");
            printf(ANSI_COLOR_RED "Try again later\n" ANSI_COLOR_YELLOW);
            free(sender1);
            free(payam1);
    }
}
void vasl_channelmembers(char req[1000],char respond[1000],char type1[1000])
{
    int mysocket=soket();
   // char* members1=(char*) malloc(500*sizeof(char));
    //char* payam1=(char*) malloc(1000*sizeof(char));
    char members1[1000];
    send(mysocket,req,1000,0);
    memset(respond,0,1000);
    recv(mysocket,respond,1000,0);
    cJSON* tarjome= cJSON_Parse(respond);
    cJSON* type=cJSON_GetObjectItem(tarjome,"type");
    strcpy(type1,type->valuestring);
    cJSON* content=cJSON_GetObjectItem(tarjome,"content");
    if(*type1=='L')
    {
        int i;
        system("cls");
        printf("Channel memebers:\n");
        for (i = 0 ; i < cJSON_GetArraySize(content) ; i++)
        {
            cJSON * subitem = cJSON_GetArrayItem(content, i);
            //cJSON* sender = cJSON_GetObjectItem(subitem, "sender");
            strcpy(members1,subitem->valuestring);
            //cJSON* payam = cJSON_GetObjectItem(subitem, "content");
            //strcpy(payam1,payam->valuestring);
            printf(ANSI_COLOR_YELLOW "%s\n",members1);
        }
    }
    else
    {
        system("cls");
        printf(ANSI_COLOR_RED  "Try again later\n" ANSI_COLOR_RESET);
        return;
    }
}
int login()
{
    char user[500],pass[500],req[1000]="login ",respond[1000],type1[1000],content1[1000];
    char chert1;
    system("cls");
    printf("Enter Username\n");
    scanf("%c",&chert1);
    gets(user);
    printf("Enter Password\n");
    gets(pass);
    strcat(req,user);
    strcat(req,", ");
    strcat(req,pass);
    strcat(req,"\n");
    vasl(req,respond,type1,content1);
    if (*type1=='A')
    {
        system("cls");
        printf(ANSI_COLOR_GREEN  "user loged in successfuly\n" ANSI_COLOR_RESET);
        printf("---------------\n");
        strcpy(autotoken,content1);
        flag1=2;
        return;
    }
    else
    {
        system("cls");
        printf(ANSI_COLOR_RED  "%s\n" ANSI_COLOR_RESET,content1);
        printf("------------------\n");
        return;
    }
}
void menuasli()
{
    int s;
    while(1){
        printf("1: Create channel\n");
        printf("2: Join channel\n");
        printf("3: Logout\n");
        scanf("%d",&s);
        if (s==1)
        {
            createchannel();
        }
        if(s==2)
        {
            joinchannel();
        }
        if(s==3)
        {
            logout();
        }
    }
}
void createchannel()
{
    char channel[500],req[1000]="create channel ",respond[1000];
    //char* type1=(char*) malloc(10000*sizeof(char));
    //char* content1=(char*) malloc(10000*sizeof(char));
    char type1[1000],content1[1000];
    char chert1;
    system("cls");
    printf("Enter channel name:\n");
    scanf("%c",&chert1);
    gets(channel);
    //printf("wsdd %s",user);
    //scanf("%c",&chert1);
    //req[] = "register ";
    strcat(req,channel);
    strcat(req,", ");
    strcat(req,autotoken);
    strcat(req,"\n");
    vasl(req,respond,type1,content1);
    //printf("%s\n",type1);
    if (*type1=='S')
    {
        system("cls");
        printf(ANSI_COLOR_GREEN  "channel created successfuly\n" ANSI_COLOR_RESET);
        printf("---------------\n");
        flag1=3;
        return;
    }
    else
    {
        system("cls");
        printf(ANSI_COLOR_RED  "%s\n" ANSI_COLOR_RESET,content1);
        printf("------------------\n");
        return;
    }
}
void joinchannel()
{
    char channel[500],req[1000]="join channel ",respond[1000];
    //char* type1=(char*) malloc(10000*sizeof(char));
    //char* content1=(char*) malloc(10000*sizeof(char));
    char chert1;
    char type1[1000],content1[1000];
    system("cls");
    printf("Enter channel name:\n");
    scanf("%c",&chert1);
    gets(channel);
    //printf("wsdd %s",user);
    //scanf("%c",&chert1);
    //req[] = "register ";
    strcat(req,channel);
    strcat(req,", ");
    strcat(req,autotoken);
    strcat(req,"\n");
    //printf("okkk\n");
    vasl(req,respond,type1,content1);
    //printf("%s\n",type1);
    if (*type1=='S')
    {
        system("cls");
        printf(ANSI_COLOR_GREEN  "user joined successfuly\n" ANSI_COLOR_RESET);
        printf("---------------\n");
        flag1=3;
    }
    else
    {
        system("cls");
        printf(ANSI_COLOR_RED  "%s\n" ANSI_COLOR_RESET,content1);
        printf("------------------\n");
        flag1=2;
        return;
    }
}
void logout()
{
    char req[1000]="logout ",respond[1000];
    //char* type1=(char*) malloc(10000*sizeof(char));
    //char* content1=(char*) malloc(10000*sizeof(char));
    char type1[1000],content1[1000];
    strcat(req,autotoken);
    strcat(req,"\n");
    vasl(req,respond,type1,content1);
    //printf("%s\n",type1);
    if (*type1=='S')
    {
        system("cls");
        printf(ANSI_COLOR_GREEN  "user loged out successfuly\n" ANSI_COLOR_RESET);
        printf("---------------\n");
        flag1=1;
        return;
    }
    else
    {
        system("cls");
        printf(ANSI_COLOR_RED  "%s\n" ANSI_COLOR_RESET,content1);
        printf("------------------\n");
        flag1=2;
        return;
    }
}
void chatroom()
{
    int s;
    while(1)
    {
        printf("1: Send message\n");
        printf("2: Refresh\n");
        printf("3: Channel memebers\n");
        printf("4: Leave channel\n");
        printf("5: Find User\n");
        printf("6: Find word\n");
        scanf("%d",&s);
        if (s==1)
        {
            sendmessage1();
        }
        else if(s==2)
        {
            refresh();
        }
        else if(s==3)
        {
            channelmembers();
        }
        else if(s==4)
        {
            leavechannel();
        }
        else if(s==5)
        {
            find_user();
        }
        else if(s==6)
        {
            find_message();
        }
    }
}
void find_user()
{
    char message1[500],req[1000]="find user ",respond[1000];
    //char* type1=(char*) malloc(10000*sizeof(char));
    //char* content1=(char*) malloc(10000*sizeof(char));
    char type1[1000],content1[1000];
    char chert1;
    system("cls");
    printf("Type user that you want:\n");
    scanf("%c",&chert1);
    gets(message1);
    //printf("wsdd %s",user);
    //scanf("%c",&chert1);
    //req[] = "register ";
    strcat(req,message1);
    strcat(req,", ");
    strcat(req,autotoken);
    strcat(req,"\n");
    vasl(req,respond,type1,content1);
    //printf("%s\n",type1);
    if (*type1=='S')
    {
        printf(ANSI_COLOR_GREEN  "user %s found.\n" ANSI_COLOR_RESET,message1);
        printf("Press enter to Continue\n");
        getchar();
        system("cls");
        flag1=3;
        return;
    }
    else
    {
        printf(ANSI_COLOR_RED  "user %s not found.\n" ANSI_COLOR_RESET,message1);
        printf("Press enter to Continue\n");
        getchar();
        system("cls");
        flag1=3;
        return;
    }
}
void sendmessage1()
{
    char message1[500],req[1000]="send ",respond[1000];
    //char* type1=(char*) malloc(10000*sizeof(char));
    //char* content1=(char*) malloc(10000*sizeof(char));
    char type1[1000],content1[1000];
    char chert1;
    system("cls");
    printf("Type your meesage:\n");
    scanf("%c",&chert1);
    gets(message1);
    //printf("wsdd %s",user);
    //scanf("%c",&chert1);
    //req[] = "register ";
    strcat(req,message1);
    strcat(req,", ");
    strcat(req,autotoken);
    strcat(req,"\n");
    vasl(req,respond,type1,content1);
    //printf("%s\n",type1);
    if (*type1=='S')
    {
        system("cls");
        printf(ANSI_COLOR_GREEN  "message sent successfuly\n" ANSI_COLOR_RESET);
        printf("---------------\n");
        flag1=3;
        return;
    }
    else
    {
        system("cls");
        printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,content1);
        printf("------------------\n");
        flag1=3;
        return;
    }
}
void find_message(){
    char message1[1000],req[1000]="find message ",respond[1000];
    //char* type1=(char*) malloc(10000*sizeof(char));
    //char* content1=(char*) malloc(10000*sizeof(char));
    char type1[1000],content1[1000];
    char chert1;
    system("cls");
    printf("Type word that you want:\n");
    scanf("%c",&chert1);
    gets(message1);
    //printf("wsdd %s",user);
    //scanf("%c",&chert1);
    //req[] = "register ";
    strcat(req,message1);
    strcat(req,", ");
    strcat(req,autotoken);
    strcat(req,"\n");
    vasl(req,respond,type1,content1);
    //printf("%s\n",type1);
    if (*type1=='S')
    {
        printf(ANSI_COLOR_GREEN "message found.\n" ANSI_COLOR_RESET);
        printf("%s\n",content1);
        printf("Press enter to Continue\n");
        getchar();
        system("cls");
        flag1=3;
        return;
    }
    else
    {
        printf(ANSI_COLOR_RED "message not found.\n" ANSI_COLOR_RESET);
        printf("Press enter to Continue\n");
        getchar();
        system("cls");
        flag1=3;
        return;
    }
}
void refresh()
{
    char req[1000]="refresh ",respond[1000];
    //char* type1=(char*) malloc(1000*sizeof(char));
    char type1[1000];
    char chert1;
    strcat(req,autotoken);
    strcat(req,"\n");
    vaslrefresh(req,respond,type1);
    printf(ANSI_COLOR_RESET "Press enter to Continue\n");
    getchar();
    getchar();
    system("cls");
}
void channelmembers()
{
    char message1[500],req[1000]="channel members ",respond[1000];
    //char* type1=(char*) malloc(10000*sizeof(char));
    //char* content1=(char*) malloc(10000*sizeof(char));
    char type1[1000],content1[1000];
    strcat(req,autotoken);
    strcat(req,"\n");
    vasl_channelmembers(req,respond,type1);
    printf(ANSI_COLOR_RESET "Press enter to Continue\n");
    getchar();
    getchar();
    system("cls");
    flag1=3;
    return;
}
void leavechannel()
{
    char req[1000]="leave ",respond[1000];
    //char* type1=(char*) malloc(10000*sizeof(char));
    //char* content1=(char*) malloc(10000*sizeof(char));
    char type1[1000],content1[1000];
    strcat(req,autotoken);
    strcat(req,"\n");
    vasl(req,respond,type1,content1);
    if (*type1=='S')
    {
        system("cls");
        printf(ANSI_COLOR_GREEN  "user left successfuly\n" ANSI_COLOR_RESET);
        printf("---------------\n");
        flag1=2;
        return;
    }
    else
    {
        system("cls");
        printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET,content1);
        printf("------------------\n");
        flag1=3;
        return;
    }
}
int arrow_play_menu1(){
    int counter=1;
    while(1){
        char c;
        c =_getch();
        //scanf("%c",&c);
        if (c==13) {
                break;
        }
        if (c==115){
            if(counter<3) counter++;
            else counter=1;
        }
        if (c==119){
            if (counter>1) counter--;
            else counter=3;
        }
        if (counter==1){
            system("cls");
            printf("Acount menu\n");
            printf(ANSI_COLOR_YELLOW "1: Register\n" ANSI_COLOR_RESET);
            printf("2: Login\n");
            printf("3: close app\n");
        }
        if (counter==2){
            system("cls");
            printf("Acount menu\n");
            printf("1: Register\n");
            printf(ANSI_COLOR_YELLOW "2: Login\n" ANSI_COLOR_RESET);
            printf("3: close app\n");
        }
        if (counter==3){
            system("cls");
            printf("Acount menu\n");
            printf("1: Register\n");
            printf("2: Login\n");
            printf(ANSI_COLOR_YELLOW "3: close app\n"ANSI_COLOR_RESET);
        }
    }
    return counter;

}
int arrow_play_menu2(){
    int counter=1;
    while(1){
        char c;
        c =_getch();
        if (c==13) {
                break;
        }
        if (c==115){
            if(counter<3) counter++;
            else counter=1;
        }
        if (c==119){
            if (counter>1) counter--;
            else counter=3;
        }
        if (counter==1){
            system("cls");
            printf(ANSI_COLOR_YELLOW "1: Create channel\n" ANSI_COLOR_RESET);
            printf("2: Join channel\n");
            printf("3: Logout\n");
        }
        if (counter==2){
            system("cls");
            printf("1: Create channel\n");
            printf(ANSI_COLOR_YELLOW "2: Join channel\n" ANSI_COLOR_RESET);
            printf("3: Logout\n");
        }
        if (counter==3){
            system("cls");
            printf("1: Create channel\n");
            printf("2: Join channel\n");
            printf(ANSI_COLOR_YELLOW "3: Logout\n" ANSI_COLOR_RESET);
        }
    }
    return counter;
}
int arrow_play_menu3(){
    int counter=1;
    while(1){
        char c;
        c =_getch();
        if (c==13) {
                break;
        }
        if (c==115){
            if(counter<6) counter++;
            else counter=1;
        }
        if (c==119){
            if (counter>1) counter--;
            else counter=6;
        }
        if (counter==1){
            system("cls");
            printf(ANSI_COLOR_YELLOW "1: Send message\n" ANSI_COLOR_RESET);
            printf("2: Refresh\n");
            printf("3: Channel memebers\n");
            printf("4: Leave channel\n");
            printf("5: Find User\n");
            printf("6: Find word\n");
        }
        if (counter==2){
            system("cls");
            printf("1: Send message\n");
            printf(ANSI_COLOR_YELLOW "2: Refresh\n" ANSI_COLOR_RESET);
            printf("3: Channel memebers\n");
            printf("4: Leave channel\n");
            printf("5: Find User\n");
            printf("6: Find word\n");
        }
        if (counter==3){
            system("cls");
            printf("1: Send message\n");
            printf("2: Refresh\n");
            printf(ANSI_COLOR_YELLOW "3: Channel memebers\n" ANSI_COLOR_RESET);
            printf("4: Leave channel\n");
            printf("5: Find User\n");
            printf("6: Find word\n");
        }
        if (counter==4){
            system("cls");
            printf("1: Send message\n");
            printf("2: Refresh\n");
            printf("3: Channel memebers\n");
            printf(ANSI_COLOR_YELLOW "4: Leave channel\n" ANSI_COLOR_RESET);
            printf("5: Find User\n");
            printf("6: Find word\n");
        }
        if (counter==5){
            system("cls");
            printf("1: Send message\n");
            printf("2: Refresh\n");
            printf("3: Channel memebers\n");
            printf("4: Leave channel\n");
            printf(ANSI_COLOR_YELLOW "5: Find User\n" ANSI_COLOR_RESET);
            printf("6: Find word\n");
        }
        if (counter==6){
            system("cls");
            printf("1: Send message\n");
            printf("2: Refresh\n");
            printf("3: Channel memebers\n");
            printf("4: Leave channel\n");
            printf("5: Find User\n");
            printf(ANSI_COLOR_YELLOW "6: Find word\n" ANSI_COLOR_RESET);
        }
    }
    return counter;
}
int flag2=0;
int main()
{
    int n,s,m;
    char c;
    while(1)
    {
        n=1;
        if(flag1==0){
            printf("how do you want to work with options?\n");
            printf("1: with numbers\n");
            printf("2: with arrowkeys\n");
            int m;
            scanf("%d",&m);
            if (m==1) flag2=1;
            if (m==2) flag2=2;
            system("cls");
            flag1=1;
        }
        if(flag1==1){
            printf("Acount menu\n");
            printf("1: Register\n");
            printf("2: Login\n");
            printf("3: close app\n");
            if(flag2==1) scanf("%d",&n);
            else n=arrow_play_menu1();
            if (n==1)
            {
                registerr();
                continue;
            }
            if (n==2)
            {
                login();
                continue;
            }
            if(n==3)
            {
                int mysocket=soket();
                send(mysocket,"exit",1000,0);
                system("cls");
                printf(ANSI_COLOR_BLUE  "good bye :)" ANSI_COLOR_RESET);
                exit(0);
            }
        }
         else if(flag1==2){
            printf("1: Create channel\n");
            printf("2: Join channel\n");
            printf("3: Logout\n");
            if(flag2==1) scanf("%d",&s);
            else s=arrow_play_menu2();
            if (s==1)
            {
                createchannel();
                continue;
            }
            if(s==2)
            {
                joinchannel();
                continue;
            }
            if(s==3)
            {
                logout();
                continue;
            }
        }
        else if(flag1==3){
            printf("1: Send message\n");
            printf("2: Refresh\n");
            printf("3: Channel memebers\n");
            printf("4: Leave channel\n");
            printf("5: Find User\n");
            printf("6: Find word\n");
            if(flag2==1) scanf("%d",&s);
            else s=arrow_play_menu3();
            if (s==1)
            {
                sendmessage1();
                continue;
            }
            else if(s==2)
            {
                refresh();
                continue;
            }
            else if(s==3)
            {
                channelmembers();
                continue;
            }
            else if(s==4)
            {
                leavechannel();
                continue;
            }
            else if(s==5)
            {
                find_user();
                continue;
            }
            else if(s==6)
            {
                find_message();
                continue;
            }
        }
    }
}
