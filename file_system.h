#ifndef FILE_SYSTEM
#define FILE_SYSTEM

/**
 * @file file_system.h
 * @author Juan Couselo
 * @brief This library defines a filesystem with files, directories, users and groups.
 * @version 0.1
 * @date 2022-06-07
 */

/*  TODO LIST:
    Functions:
        fs_remove();
        file_remove();
        file_rename();
        various get functions (get)
        file_isOwner(); | file_isOnGroup();
        file_canUserWrite(); ...

        ----- TAKING IDEAS HERE ------
*/



/*  Include list: */

#include <inttypes.h>
#include <stdlib.h>
#include "sources/list.h"
#include "sources/datetime.h"
#include "user_group.h"
#include "sources/queue_dynamic.c"

/*  Constants: */
#define standard_permissions 0xEA8
//  0000 1110 1010 1000
#define ownerOnly_permissions 0xE00
//  0000 1110 0000 0000

/*  RWXO RWXO RWXO RWXO     <-- "O" is a reserved value (not used)
   |----|OWNR|GRP.|GUEST    <-- 4MSB are left blank
*/

//----------------------------------------------------------------------------------------------

/*  STRUCTURES:  */

typedef struct _file_metadata {         //Metadata
    uint32_t group_id;
    uint32_t owner_id;
    date* creation_date;
    date* modif_date;
    uint16_t permissions;
    uint64_t size;
} file_metadata;

typedef struct _ftn {                   //File node
    uint32_t id;
    char* name;
    uint8_t is_dir;
    struct _ftn* directory;
    file_metadata* metadata;
    list* children;
} ftn;

typedef struct _fs{                    //Filesystem
    entities_t* entities;
    ftn* root;
    uint32_t file_autoinc;
    user_t* active_user;
} file_system;

//----------------------------------------------------------------------------------------------

/*  FILESYSTEM FUNCTIONS:
    Functions related to the filesystem itself.
*/

/* Basic filesystem functions: */

/* Creates a new filesystem, returns pointer to it */
file_system* fs_new();


/* User/Group handling: */

/* Gets all entities linked to the filesystem */
entities_t* fs_getEntities(file_system* fs);

/* Retrieves a pointer to the logged user */
user_t* fs_getActiveUser(file_system* fs);

/* Process of logging in an user */
int fs_userLogin(file_system* fs,user_t* u);

/* Logs out an user */
user_t* fs_userLogout(file_system* fs);

ftn* fs_removeFile(file_system* fs,ftn** file);

void fs_scroll(file_system* fs,void todo(void*,void*),void* ctx);

ftn* fs_search(file_system* fs,int cmp(void*,void*),void* ctx);

list* fs_searchAll(file_system* fs,int cmp(void*,void*),void* ctx);

//----------------------------------------------------------------------------------------------

/*  FILE FUNCTIONS: 
    Every function regarding the creation, modification
    or destruction of files.
*/

/* Basic file functions: */

/* Makes a new file and connects it to the filesystem. Requires all data */
ftn* file_new(file_system* fs,ftn* directory,uint8_t is_dir,char* name,file_metadata* md);

/* Same as file_new but reads data from keyboard directly */
ftn* file_create(file_system* fs,ftn* directory,uint8_t is_dir);

void file_delete(ftn* file);

/* Creates a child to the sent file and connects it */
int file_addChild(file_system* fs,ftn* file, uint8_t is_dir);

void file_addGroup(ftn* file,uint32_t group_id);

char* file_getName(ftn* file);



/*  File permissions handling   */

uint8_t file_getOwnerPermissions(ftn* file);
uint8_t file_getGroupPermissions(ftn* file);
uint8_t file_getGuestPermissions(ftn* file);

/* Gets file permissions for owner, group and guest */
uint16_t file_getAllPermissions(ftn* file);

int file_canUserRead(ftn* file,user_t* user);
int file_canUserWrite(ftn* file,user_t* user);
int file_canUserOpen(ftn* file,user_t* user);


// METADATA:

/* Reads all metadata info from keyboard. */
file_metadata* metadata_read(uint32_t active_userid);

file_metadata* file_getMetadata(ftn* file);
list* file_getChildren(ftn* file);
uint32_t file_getGroupId(ftn* file);
uint32_t file_getOwnerId(ftn* file);
date* file_getCreationDate(ftn* file);
date* file_getModifDate(ftn* file);
uint64_t file_getSize(ftn* file);

//----------------------------------------------------------------------------------------------



/*  UTILITY FUNCTIONS:
    Functions with utilitary use (prints, etc)
*/

int cmp_int(int a, int b);

/* Prints basic information about the sent file */
void file_printBasic(ftn* file);

/* Prints file permissions in an "RWX" fashion, i.e.:
    Owner:  Group:  Guest:
    RWX     R-X     R--
*/
void file_printPermissions(ftn* file);

/* Prints basic information about every file contained in the directory */
void file_printContents(ftn* file);

/* Prints detailed information about a certain file */
void file_printDetailed(ftn* file);

//----------------------------------------------------------------------------------------------
#endif

