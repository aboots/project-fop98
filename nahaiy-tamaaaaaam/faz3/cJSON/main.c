#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct cJSON{
    char* type;
    char* content;
    struct cJSON* before;
    struct cJSON* next;
    char* noe;
    char* valuestring;
} cJSON;
char* cJSON_PrintUnformatted(cJSON* a);
cJSON* cJSON_CreateObject(){
    cJSON* a=calloc(1,sizeof(cJSON));
    a->noe=calloc(1000,sizeof(char));
    a->before=NULL;
    a->type=NULL;
    a->content=NULL;
    a->next=NULL;
    return a;
}
cJSON* cJSON_CreateString(char* str){
    cJSON* a=calloc(1,sizeof(cJSON));
    a->content=calloc(1000,sizeof(char));
    a->type=calloc(1000,sizeof(char));
    char* c;
    c[0]='"';
    c[1]='\0';
    strcpy(a->content,c);
    strcat(a->content,str);
    strcat(a->content,c);
    //strcpy(a->content,str);
    a->before=NULL;
    a->next=NULL;
    a->noe=calloc(1000,sizeof(char));
    strcpy(a->noe,"string");
    return a;
}
void cJSON_AddItemToObject(cJSON* a,char* str,cJSON* b){
     if(strcmp(b->noe,"string")==0){
            if(a->type==NULL && a->content==NULL){
                a->type=calloc(1000,sizeof(char));
                a->content=calloc(1000,sizeof(char));
                strcpy(a->type,str);
                strcpy(a->content,b->content);
            }
            else{
                cJSON* temp=a;
                while(temp->next!=NULL){
                    temp=temp->next;
                }
                b->before=temp;
                temp->next=b;
                b->type=calloc(1000,sizeof(char));
                strcpy(b->type,str);
            }
    }
    else if (strcmp(b->noe,"array")==0){
        char* c=cJSON_PrintUnformatted(b);
        if(a->type==NULL && a->content==NULL){
            a->type=calloc(1000,sizeof(char));
            a->content=calloc(1000,sizeof(char));
            strcpy(a->type,str);
            strcpy(a->content,c);
        }
        else{
            cJSON* temp=a;
            while(temp->next!=NULL){
                temp=temp->next;
            }
            b->before=temp;
            temp->next=b;
            b->type=calloc(1000,sizeof(char));
            strcpy(b->type,str);
            strcpy(b->content,c);
        }
    }
}
char* cJSON_PrintUnformatted(cJSON* a){
    char* finall=calloc(1000,sizeof(char));
    char c='"';
    if (strcmp(a->noe,"string")==0) {
            strcpy(finall,a->content);
    }
    else if(strcmp(a->noe,"array")==0) {
            cJSON* temp=a;
            finall[0]='[';
            char* d=",";
            while(temp->next!=NULL){
                strcat(finall,temp->content);
                strcat(finall,d);
                temp=temp->next;
            }
            finall[strlen(finall)-1]=']';
    }
    else
    {
        sprintf(finall,"{%c%s%c:%s,%c%s%c:%s}",c,a->type,c,a->content,c,(a->next)->type,c,(a->next)->content);
    }
    return finall;
}
cJSON* cJSON_CreateArray(){
    cJSON* a=calloc(1,sizeof(cJSON));
    a->type=calloc(1000,sizeof(char));
    a->content=calloc(1000,sizeof(char));
    a->noe=calloc(50,sizeof(char));
    a->before=NULL;
    strcpy(a->noe,"array");
    a->next=NULL;
    return a;
}
void cJSON_AddItemToArray(cJSON* array,cJSON* add1){
        char* add=cJSON_PrintUnformatted(add1);
        if (array->content[0]==0){
            strcpy(array->content,add);
            cJSON* b=calloc(1,sizeof(cJSON));
            b->type=calloc(1000,sizeof(char));
            b->content=calloc(1000,sizeof(char));
            array->next=b;
            b->before=array;
        }
        else{
            cJSON* temp=array;
            while(temp->next!=NULL){
                temp=temp->next;
            }
            strcpy(temp->content,add);
            cJSON* b=calloc(1,sizeof(cJSON));
            b->type=calloc(1000,sizeof(char));
            b->content=calloc(1000,sizeof(char));
            temp->next=b;
            b->before=temp;

    }
}
int  cJSON_GetArraySize(cJSON* a){
    cJSON* temp=a;
    int counter=0;
    while(temp->next!=NULL){
        counter++;
        temp=temp->next;
    }
    if(counter==0){
    if((a->valuestring)[1]=='{'){
        for(int i=0;i<strlen((a->valuestring));i++){
            if ((a->valuestring[i])=='{') counter++;
        }
    }
    else{
        for(int i=0;i<strlen((a->valuestring));i++){
            if ((a->valuestring[i])==',') counter++;
        }
        counter++;
    }
    }
    return counter;
}
cJSON* cJSON_Parse(char* s1){
        cJSON* a=calloc(1,sizeof(cJSON));
        cJSON* b=calloc(1,sizeof(cJSON));
        a->content=calloc(1000,sizeof(char));
        a->type=calloc(1000,sizeof(char));
        b->content=calloc(1000,sizeof(char));
        b->type=calloc(1000,sizeof(char));
        b->noe=calloc(1000,sizeof(char));
        a->next=b;
        b->before=a;
        b->next=NULL;
        a->before=NULL;
        char c;
        char s[1000];
        strcpy(s,s1);
        int counter1=0,counter3=0;
        int counter2=0,counter4=0;
        int f1=0,f2=0,f3=0,f4=0;
        int flag2=0,flag3=0;
        if(s[2]!='m'){
        for(int i=0;i<strlen(s);i++){
            if(s[i]==' ') counter3++;
            if (s[i]=='"') counter4++;
            if(counter4==7 && flag2==0){
                f3=i;
                flag2=1;
            }
            if(counter4==8 && flag3==0){
                f4=i;
                flag3=1;
            }
            if (s[i]==':' && counter1<2) {
                s[i]=' ';
                counter1++;
            }
            if (s[i]==',' && counter2<1){
                s[i]=' ';
                counter2++;
            }
            if(s[i]=='[') f1=i;
            if(s[i]==']') f2=i;
        }
        if(f1==0 && f2==0 && counter3==0){
                s[strlen(s)-1]='\0';
                sscanf(s,"%c%s %s %s %s",&c,a->type,a->content,(a->next)->type,(a->next)->content);
        }
        else if (f1==0 && f2==0 && counter3>0 && f3!=0 && f4!=0){
            int j=0;
            sscanf(s,"%c%s %s %s",&c,a->type,a->content,(a->next)->type);
            for(int i=f3;i<=f4;i++){
                    ((a->next)->content)[j]=s[i];
                    j++;
            }
            (a->next)->content[j]='\0';
        }
        else {
            int j=0;
            strcpy(b->noe,"array");
            sscanf(s,"%c%s %s %s",&c,a->type,a->content,(a->next)->type);
            for(int i=f1;i<=f2;i++){
                    ((a->next)->content)[j]=s[i];
                    j++;
            }
            ((a->next)->content)[j]='\0';
        }
        }
        if (s[2]=='m'){
            int t1,t2,t3,t4,t5,t6,t7,t8,counter1=0,flagg=0,counter2=0;
            for(int i=0;i<strlen(s);i++){
                if (s[i]=='"' && counter1<2){
                    counter1++;
                    if(counter1==1) t1=i;
                    if (counter1==2) t2=i;
                }
                if(s[i]=='[') t3=i;
                if(s[i]==']') {
                        t4=i;
                        flagg=1;
                }
                if(flagg==1 && s[i]=='"'){
                    counter2++;
                    if(counter2==1) t5=i;
                    if (counter2==2) t6=i;
                    if (counter2==3) t7=i;
                    if (counter2==4) t8=i;
                }
            }
            int j=0;
            for(int i=t7;i<=t8;i++){
                ((a->next)->content)[j]=s[i];
                j++;
            }
            ((a->next)->content)[j]='\0';
            j=0;
            for(int i=t1;i<=t2;i++){
                (a->type)[j]=s[i];
                j++;
            }
            (a->type)[j]='\0';
            j=0;
            for(int i=t3;i<=t4;i++){
                (a->content)[j]=s[i];
                j++;
            }
            (a->content)[j]='\0';
            j=0;
            for(int i=t5;i<=t6;i++){
                ((a->next)->type)[j]=s[i];
                j++;
            }
            ((a->next)->type)[j]='\0';
        }
        //printf("%s\n%s\n%s\n%s\n",a->type,a->content,(a->next)->type,((a->next)->content));
        return a;
}
cJSON* cJSON_GetObjectItem(cJSON* a,char *s){
cJSON* b=calloc(1,sizeof(cJSON));
    b->content=calloc(1000,sizeof(char));
    b->type=calloc(1000,sizeof(char));
    b->noe=calloc(1000,sizeof(char));
    b->valuestring=calloc(1000,sizeof(char));
    char c[2];
    char s1[1000];
    c[0]='"';
    c[1]='\0';
    strcpy(s1,c);
    strcat(s1,s);
    strcat(s1,c);
    if(strcmp(a->type,s1)==0) {
        //printf("%s\n",a->content);
        if(a->content[0]='"'){
            int j=0;
            for(int i=1;i<strlen(a->content)-1;i++){
                (b->valuestring)[j]=(a->content)[i];
                j++;
            }
            (b->valuestring[j])='\0';
            //printf("%s\n",b->valuestring);
        }
        else
        strcpy(b->valuestring,a->content);
    }
    if(strcmp((a->next)->type,s1)==0) {
        if((a->next)->content[0]=='"'){
            int j=0;
            for(int i=1;i<strlen((a->next)->content)-1;i++){
                (b->valuestring)[j]=((a->next)->content)[i];
                j++;
            }
            (b->valuestring[j])='\0';
        }
        else
        strcpy(b->valuestring,(a->next)->content);
    }
    return b;
}
cJSON* cJSON_GetArrayItem(cJSON* a,int index){
    char s[1000],s2[1000];
    int counter1=(-1),j=0;
    strcpy(s,a->valuestring);
    if(s[1]=='{'){
        int flag2=0;
        for(int i=1;i<strlen(s)-1;i++){
            if (s[i-1]=='}' && s[i]==','){
                counter1++;
            }
            if(counter1==(index-1)){
                if(s[i]==',' && s[i-1]=='}' && s[i+1]=='{') continue;
                s2[j]=s[i];
                j++;
            }
        }
        s2[j]='\0';
        //printf("%s\n",s2);
        /* cJSON* b=calloc(1,sizeof(cJSON));
        b->content=calloc(1000,sizeof(char));
        b->type=calloc(1000,sizeof(char));
        b->noe=calloc(1000,sizeof(char));
        b->valuestring=calloc(1000,sizeof(char));
        b->next=NULL;
        b->before=NULL; */
        cJSON *b=cJSON_Parse(s2);
        //printf("baba\n");
        return b;
    }
    else{
        counter1=-1;
        for(int i=1;i<(strlen(s)-1);i++){
            if (s[i]==','){
                counter1++;
            }
            if(counter1==(index-1) && s[i]!=','){
                s2[j]=s[i];
                j++;
            }
        }
        s2[j]='\0';
        //printf("salam %s\n",s2);
        char s3[1000];
        if(s2[0]=='"'){
            int j=0;
            for(int i=1;i<strlen(s2)-1;i++){
                s3[j]=s2[i];
                j++;
            }
            (s3[j])='\0';
        }
        //printf("bye %s\n",s3);
        cJSON* b=calloc(1,sizeof(cJSON));
        b->content=calloc(1000,sizeof(char));
        b->type=calloc(1000,sizeof(char));
        b->noe=calloc(1000,sizeof(char));
        b->valuestring=calloc(1000,sizeof(char));
        b->next=NULL;
        b->before=NULL;
        strcpy(b->valuestring,s3);
        return b;
    }
}
int main(){
    return 0;
}
