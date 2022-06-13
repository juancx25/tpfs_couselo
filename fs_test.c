#include "file_system.c"

void main(){
    // GROUP AND USER TESTING
    file_system* fs = fs_new();
    user_t* usuario0 = user_new(fs_getEntities(fs),"Pepe");
    user_t* usuario1 = user_new(fs_getEntities(fs),"Maria");
    group_t* grupo0 = group_new(fs_getEntities(fs),"Grupazo");
    user_group_link(usuario1,grupo0);
    user_group_link(usuario0,grupo0);

    printf("Grupos usuario 1:\n");
    list_print(user_getGroupList(usuario1),group_printBasic);
    printf("Usuarios grupo 1:\n");
    list_print(group_getUserList(grupo0),user_printBasic);
    printf("Desconectando usuario 0 y grupo 0...\n");
    user_group_unlink(usuario0,grupo0,cmp);
    printf("Grupos usuario 0:\n");
    list_print(user_getGroupList(usuario0),group_printBasic);
    printf("Usuarios grupo 0:\n");
    list_print(group_getUserList(grupo0),user_printBasic);

    printf("Usuarios en el Filesystem:\n");
    list_print(ent_getUserList(fs_getEntities(fs)),user_printBasic);

    printf("Grupos en el Filesystem:\n");
    list_print(ent_getGroupList(fs_getEntities(fs)),group_printBasic);

    // LOGIN TESTING
    fs_userLogin(fs,usuario0);
    printf("Usuario activo:\n");
    user_printBasic(fs_getActiveUser(fs));
    printf("Rajando a Pepe...\n");
    fs_userLogout(fs);
    fs_userLogin(fs,usuario1);
    printf("Usuario activo:\n");
    user_printBasic(fs_getActiveUser(fs));

    // FILE TESTING
    ftn* root = file_new(fs,NULL,1,"raiz",file_readMetadata(fs));
    /*  file_addChild(fs,root,1);
        file_addChild(fs,root,0);
        file_addChild(fs,root,1);
        file_printContents(root);   */


    // METADATA TESTING
    file_printDetailed(root);

    // PERMISSION TESTING
    int test = file_getAllPermissions(root);
}
