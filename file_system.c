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
    file_metadata* md = file_readMetadata(fs);
    ftn* file = file_new(fs,directory,is_dir,name,md);
    return file;
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

file_metadata* file_readMetadata(file_system* fs){
    if (fs->active_user){
        file_metadata* md = (file_metadata*)malloc(sizeof(file_metadata));
        md->owner_id = fs->active_user->id;
        date* aux = NULL;                      
        md->creation_date = aux;                // Left with NULL values for testing purposes
        md->modif_date = aux;                   // " "
        md->group_id = UINT32_MAX;              // Setting it as max value: stands for non-set
        md->permissions = standard_permissions; // Setting permissions as standard for now
        md->size = 0;                           // Zero for now. Should be taken from external sources (calling a function from here).
        return md;
    }
    // Should add an error state here? (unlogged user)
}

/*                        */

/*  Permission handling   */

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


//----------------------------------------------------------------------------------------------
/* Utility functions: */

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