#ifndef USER_GROUP
#define USER_GROUP

/* Included libraries */
#include <inttypes.h>
#include "file_system.h"
#include <stdio.h>

/* Constant values */
#define name_maxsize 30

/*  DESCRIPTION
    This library sets an user-group system with a set of basic functions.
    entities_t are either groups or users, listed separately and implementing an auto-incremental ID system.
    Users and groups mainly consist of their ID, name and a list (ADT: list.h) of linked groups and users.
*/


/* Structures */

typedef struct {                    //entities_t
    list* users;
    uint32_t user_autoinc;
    list* groups;
    uint32_t group_autoinc;
} entities_t;

typedef struct {                    //Users
    uint32_t id;
    char* name;
    list* groups;
} user_t;

typedef struct {                    //Groups
    uint32_t id;
    char* name;
    list* users;
} group_t;

//--------------------------------------------------------------------------------------------
/*  BASIC USER FUNCTIONS:

    These functions allow to create, modify, read and delete an user and its data.
*/

/*  -Creates a new user 
    -Increments the ID (this is an auto-incremental system)
*/
user_t* user_new(entities_t* e,char* name);

/* Creates an user while asking for its data (getName) */
user_t* user_create(entities_t* e);

/* Retrieves user ID */
uint32_t user_getId(user_t* u);

/* Returns username */
char* user_getName(user_t* u);

/* Returns the users' linked group list */
list* user_getGroupList(user_t* u);

/* Removes an user and its reference from each group it´s in */
void user_remove(user_t* u);

//--------------------------------------------------------------------------------------------
/*  LINKS BETWEEN USERS AND GROUPS:     

    Intended to link and unlink both users and groups in one go, with the use of a list in each struct. (User-->Groups & Group-->Users)
    Each list contains a pointer to the user or group, stored as a void pointer.
    To not link them in both lists would be an INCORRECT ocurrence, as it could not logically happen.
*/

/* Link both an user and a group via a pointer to either structure */
void user_group_link(user_t* u,group_t* g);

/* Unlinking group and user */
void user_group_unlink(user_t* u,group_t* g,int cmp(void*,void*));

//--------------------------------------------------------------------------------------------
/*  BASIC GROUP FUNCTIONS:

    These functions allow to create, modify, read and delete a group and its data.
*/

char* group_setName();
group_t* group_new(entities_t* e,char* name);

//--------------------------------------------------------------------------------------------




char* str_read(char* text);
#endif