#include "file_system.h"
#include "user_group.c"

//----------------------------------------------------------------------------------------------
/* Filesystem functions: */

file_system* fs_new(){

    file_system* fs = (file_system*)malloc(sizeof(file_system));
    fs->entities = ent_new();
    fs->file_autoinc = 0;
    fs->root = NULL;
    fs->active_user = NULL;
}

entities_t* fs_getEntities(file_system* fs){
    return fs->entities;
}

user_t* fs_getActiveUser(file_system* fs){
    return fs->active_user;
}

int fs_userLogin(file_system* fs,user_t* u){
    int result = -1;
    if (!fs->active_user) {
        fs->active_user = u;
    }
    return result;
}

user_t* fs_userLogout(file_system* fs){
    user_t* result = NULL;
    if (fs->active_user) {
        result = fs->active_user;
        fs->active_user = NULL;
    }
    return result;
}

ftn* fs_removeFile(file_system* fs,ftn** file){

   
}

void fs_scroll(file_system* fs,void todo(void*,void*),void* ctx){
    if (fs != NULL){
        queue *q = queue_new(fs->file_autoinc);
        ftn* node = fs->root;
        enqueue(q,node);
        while (!queue_isempty(q)){
            node = (ftn*)dequeue(q);
            if (node->children) {
                list_node* l = node->children->head;
                while (l){
                    enqueue(q,l->value);
                    l = l->next;
                } 
            }
            todo(node,ctx);
        }
    }
}

ftn* fs_search(file_system* fs,int cmp(void*,void*),void* ctx){
    ftn* found = NULL;
    if (fs != NULL){
        queue *q = queue_new(fs->file_autoinc);
        ftn* node = fs->root;
        enqueue(q,node);
        while ( (!found) && (!queue_isempty(q))){
            node = (ftn*)dequeue(q);
            if (cmp((void*)node,ctx) == 0){
                found = node;
            }
            if ((!found) && (node->children)) {
                list_node* l = node->children->head;
                while (l){
                    enqueue(q,l->value);
                    l = l->next;
                } 
            }
        }
        //queue_free(q);
    }
    return found;
}

list* fs_searchAll(file_system* fs,int cmp(void*,void*),void* ctx){
    list* found = list_new(1);
    if (fs != NULL){
        queue *q = queue_new(fs->file_autoinc);
        ftn* node = fs->root;
        enqueue(q,node);
        while (!queue_isempty(q)){
            node = (ftn*)dequeue(q);
            if (cmp((void*)node,ctx) == 0){
                list_insert(found,list_length(found),(void*)node);
            }
            if ((node->children)) {
                list_node* l = node->children->head;
                while (l){
                    enqueue(q,l->value);
                    l = l->next;
                } 
            }
        }
        //queue_free(q);
    }
    return found;
}

//----------------------------------------------------------------------------------------------
/* File functions: */

ftn* file_new(file_system* fs,ftn* directory,uint8_t is_dir,char* name,file_metadata* md){
    ftn* file = (ftn*)malloc(sizeof(ftn));
    if (directory == NULL) {
        fs->root = file;
    }
    file->directory = directory;
    file->id = (fs->file_autoinc)++;
    file->name = name;
    file->is_dir = is_dir;
    file->metadata = md;
    if (is_dir == 1) file->children = list_new(1);
    else file->children = NULL;
    return file;
}

ftn* file_create(file_system* fs,ftn* directory,uint8_t is_dir){
    char* name = str_read("Ingrese el nombre del nuevo archivo:\n");
    file_metadata* md = metadata_read(user_getId(fs->active_user));
    ftn* file = file_new(fs,directory,is_dir,name,md);
    return file;
}

void file_delete(ftn* file){

}

int file_addChild(file_system* fs,ftn* file, uint8_t is_dir){
    int result = 0;
    if (file->is_dir == 1){
        ftn* ch = file_create(fs,file,is_dir);
        list_insert(file->children,fs->file_autoinc,(void*)ch);
        result = 1;
    }
    return result;
}

file_metadata* metadata_read(uint32_t active_userid){
    if (active_userid >= 0){
        file_metadata* md = (file_metadata*)malloc(sizeof(file_metadata));
        md->owner_id = active_userid;
        date* aux = NULL;                      
        md->creation_date = aux;                // Left with NULL values for testing purposes
        md->modif_date = aux;                   // " "
        md->group_id = 999;                     // Setting it as max value: stands for non-set
        md->permissions = standard_permissions; // Setting permissions as standard for now
        md->size = 5;                           // Zero for now. Should be taken from external sources (calling a function from here).
        return md;
    }
    // Should add an error state here? (unlogged user)
}

char* file_getName(ftn* file){
    return file->name;
}

/*                        */

/*  Permission handling   */

void file_addGroup(ftn* file,uint32_t group_id){
    file->metadata->group_id = group_id;
}

uint8_t file_getOwnerPermissions(ftn* file){
    return file->metadata->permissions >> 8;
}

uint8_t file_getGroupPermissions(ftn* file){
    return (file->metadata->permissions >> 4) & (0xF);
}

uint8_t file_getGuestPermissions(ftn* file){
    return (file->metadata->permissions & 0xF);
}

uint16_t file_getAllPermissions(ftn* file){
    return (file->metadata->permissions);
}

int file_canUserRead(ftn* file,user_t* user){
    int result = 0;
    list* groups = user_getGroupList(user);
    int* aux = (int*)malloc(sizeof(int));
    *aux = file->metadata->group_id;

    if ( (file->metadata->owner_id == user_getId(user)) && (((file_getOwnerPermissions(file) >> 3) & 0x1) == 1)) result = 1;

    else if ( (file->metadata->group_id != 999)
    &&(list_search(groups,aux,(void*)cmp_int)) 
    && (((file_getGroupPermissions(file) >> 3) & 0x1) == 1)) result = 1;

    else if (((file_getGuestPermissions(file) >> 3) & 0x1) == 1) result = 1;

    free(aux);
    return result;
}


//----------------------------------------------------------------------------------------------
/* Utility functions: */

int cmp_int(int a, int b){
    return a-b;
}

void file_printContents(ftn* file){
    if (file->is_dir == 1) {
        printf("Archivos en directorio %s:\n",file->name);
        ftn* file_aux;
        list_node* aux = file->children->head;
        while (aux){
            file_aux = (ftn*)aux->value;
            file_printBasic(file_aux);
            aux = aux->next;
        }
    }
}

void file_printBasic(ftn* file){
    if (file->is_dir == 1) {
        printf("%s (directorio)\n",file->name);
    }
    else printf("%s (archivo)\n",file->name);
}

void file_printDetailed(ftn* file){

    file_printBasic(file);

    printf("Creado:\t\tUlt. mdf.:\t\tSize:\n");                 //Bad print format. Keeping it 4now
    printf("00/00/00\t\t00/00/00\t\t\t\t%d\n",
    file->metadata->size);
    printf("\nPermisos:\n");
    file_printPermissions(file);
}

void file_printPermissions(ftn* file){                          //This could possibly be the worst function ever done
    uint16_t perm = file_getAllPermissions(file);
    printf("Owner:\tGroup:\tGuest:\n");
    for (int j=2;j>=0;j--){
        char str[4] = {"RWX"};
        uint8_t aux = ((perm >> j*4) & 0xF);
         for (int i=3;i>0;i--) {
            if (((aux >> i) & 0x1) != 1) str[3-i]='-';
        }
        printf("%s\t",str); 
    }
    printf("\n");
}
//----------------------------------------------------------------------------------------------