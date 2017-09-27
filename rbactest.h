#ifndef __RBACTEST_H
#define __RBACTEST_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include <stdint.h>
/*************结构体存储用户、角色、权限**********************/
struct s_usrs{
    int32_t user_id;//id=1,2,3
    int32_t role_id;//id=1,2,3
    char user_name[20];//超级管理员、管理员、普通用户
    char user_pwd[20];
};
struct s_roles{
    int32_t role_id;//id=1,2,3
    char role_name[20];//superadmin,admin,user
};
struct s_roles_peivs{
    char role_name[20];//
    char persid[5];
};
struct s_peivs{
    int32_t peiv_id;//
    char peiv_name;
};

/***********************************************所有的接口函数***************************************************/
int32_t usrs_login();
void usr_to_role(int32_t rid);
void role_to_login(char *strrname);
int32_t role_t_per(char rname[20]);
void superadmin_accept(char * strrname);
void admin_accept(char * strrname);
void usr_accpet(char * strrname);
void usrs_pers(int32_t npers);
void usrs_ch_operate();
void usr_read(void);
void usr_write(void);
void usr_add(void);
void usr_del(void);

#endif
