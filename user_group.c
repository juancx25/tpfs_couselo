#include "user_group.h"

//--------------------------------------------------------------------------------------------
/* Basic entities functions: */

entities_t* ent_new(){
    entities_t* e = malloc(sizeof(entities_t));
    e->user_autoinc = 0;
    e->group_autoinc = 0;
    e->users = list_new(1);
    e->groups = list_new(1);
    return e;
}

list* ent_getUserList(entities_t* e){
    return e->users;
}

list* ent_getGroupList(entities_t* e){
    return e->groups;
}

//--------------------------------------------------------------------------------------------
/* Basic user functions: */

user_t* user_new(entities_t* e,char* name){
    user_t* u = (user_t*)malloc(sizeof(user_t));
    u->id = (e->user_autoinc)++;
    u->name = name;
    u->groups = NULL;
    list_insert(e->users,e->user_autoinc,(void*)u);
    return u;
}

user_t* user_create(entities_t* e){
    char* name = str_read("Ingrese el nombre del usuario:");
    user_t* u = user_new(e,name);
    return u;
}

uint32_t user_getId(user_t* u){
    return u->id;
}

char* user_getName(user_t* u){
    return u->name;
}

list* user_getGroupList(user_t* u){
    return u->groups;
}

void user_remove(user_t* u){
    for (int i=0;i<u->groups->count;i++){
        
    }
}
//--------------------------------------------------------------------------------------------
/* User and group linking functions: */

void user_group_link(user_t* u,group_t* g){

    if(!(u->groups)){
        u->groups = list_new(1);
    }
    list_insert(u->groups,u->groups->count,(void*)g);

    if(!(g->users)){
        g->users = list_new(1);
    }
    list_insert(g->users,g->users->count,(void*)u);
}

void user_group_unlink(user_t* u,group_t* g,int cmp(void*,void*)){
    uint32_t index;

    index = list_search(u->groups,(void*)g,(void*)cmp);
    if (index >= 0) {
        list_delete(u->groups,index);
    }

    index = list_search(g->users,(void*)u,(void*)cmp);
    if (index >= 0) {
        list_delete(g->users,index);
    }
}
//--------------------------------------------------------------------------------------------
/* Basic group functions: */

group_t* group_new(entities_t* e,char* name){
    group_t* g = (group_t*)malloc(sizeof(group_t));
    g->id = (e->group_autoinc)++;
    g->name = name;
    g->users = NULL;
    list_insert(e->groups,e->group_autoinc,(void*)g);
    return g;
}

group_t* group_create(entities_t* e){
    char* name = str_read("Ingrese el nombre del grupo:");
    group_t* g = group_new(e,name);
    return g;
}

uint32_t group_getId(group_t* g){
    return g->id;
}

char* group_getName(group_t* g){
    return g->name;
}

list* group_getUserList(group_t* g){
    return g->users;
}


//--------------------------------------------------------------------------------------------
/* Utilities: */

char* str_read(char* text){
    char c;
    char* str = (char*)malloc(name_maxsize);
    int i=0;
    printf("%s\n",text);
    while((c!='\n') && (i<name_maxsize)){
        if ((c = getchar()) != '\n'){
            str[i] = c;
            i++;
        }
    }
    str[i] = '\0';
    return str;
}

int cmp(void* a,void* b){
    return a-b;
}

void group_printBasic(void* value){
    group_t* aux = (group_t*)value;
    printf("%s\n",aux->name);
}

void user_printBasic(void* value){
    user_t* aux = (user_t*)value;
    printf("%s\n",aux->name);
}