#include "rbactest.h"

/*系统存储的用户角色权限信息*/
static struct s_usrs usrs[3]={{1,1,"Fan","123456"},{2,2,"Huang","123456"},{3,3,"Zhang","123456"}};//uid,rid,un,up
static struct s_roles roles[3]={{1,"superadmin"},{2,"admin"},{3,"user"}};//rid,rna
static struct s_roles_peivs role_pers[3]={{"superadmin","rwad"},{"admin","rw"},{"user","r"}};//1111=r,w,a,d
static struct s_peivs peivs[4]={{1,'r'},{2,'w'},{4,'a'},{8,'d'}};

/*存储权限的集合值*/
int32_t g_sum_pers;
/*操作权限标志位*/
int32_t g_per_a,g_per_d,g_per_w,g_per_r;
/*权限集合*/
char g_pers[4];
/*角色的名称：superadmin,admin,user*/
char g_r_name[20];
/*通过角色ID发现角色name*/
void usr_to_role(int32_t rid)
{
    printf("#########################################\n");
    printf("一、通过角色ID发现角色name。\n");
    int32_t i,r_id;
    r_id=rid;
    for(i = 0; i < 3; i++){
        if(roles[i].role_id==r_id){
           strcpy(g_r_name,roles[i].role_name);
        }	
    }
}
/*用户登录*/
int32_t usrs_login()
{
    int32_t i;
    int32_t r_index=0;//角色的ID
	int32_t login_succeed = 0;
    //find usrname
    /*存储用户输入名称和密码*/
    char usrname[20]={'0'},usrpwd[20]={'0'};
    printf("Please login user>>>>>>>>>>\n");
    printf("Input user's name:\n");
    scanf("%s",usrname);
    printf("Input user's pwd:\n");
    scanf("%s",usrpwd);
    for(i = 0; i < 3; i++){
        if((strcmp(usrs[i].user_name,usrname)==0) && \ 
		           (strcmp(usrs[i].user_pwd,usrpwd)==0)){
		     r_index=usrs[i].role_id;  
			 login_succeed = 1;
		}  
    }
	if(!login_succeed){
		printf("！！！错误提示：！！！刚才输入的用户名或密码错误，请重新登录\n");
        return 0;
	}
	else{
        usr_to_role(r_index);
        role_to_login(g_r_name);
	}
    return 0;
}
/********通过角色name分配角色登录***************/
void role_to_login(char *strrname)
{
    printf("#########################################\n");
    printf("二、开始分配登录域了。\n");
    char temp[20];
    stpcpy(temp,strrname);
    const char *spadmin="superadmin";
    const char *admin="admin";
    const char *user="user";
    char ch_u;
    if((strcmp(temp,spadmin)==0)){
	    ch_u='s';/*****superadmin**********/
    }
    else if((strcmp(temp,admin)==0)){
	    ch_u='a';/****admin****/
    }	
    else if((strcmp(temp,user)==0)){
	    ch_u='u';
    }	
    switch(ch_u){
	    case 's':
            superadmin_accept(g_r_name);
            break;
        case 'a':
            admin_accept(g_r_name);
            break;
        case 'u':
            usr_accpet(g_r_name);
            break;
        default :
            usr_accpet(g_r_name);
            break;
	}
}
/*********通过角色获取权限集****************/
int32_t role_t_per(char *rname)
{
	/*********************以上是用户名和角色名关联*********************************/
    printf("#########################################\n");
    printf("四、通过角色计算权限集\n");
	/*****find pers_id*****/
	int32_t i;
	char temp[20];
	const char * str;
	//temp=rname;
	stpcpy(temp,rname);
	int32_t per_r=0;
	int32_t per_w=0;
	int32_t per_a=0;
	int32_t per_d=0;
	for(i = 0; i < 3; i++){
        if(strcmp(role_pers[i].role_name,temp)==0){
                strcpy(g_pers,role_pers[i].persid);
            }
    }
	str=g_pers;
	g_sum_pers=0;
	while(*str!='\0'){
        for(i = 0; i < 4; i++){	
		    if(peivs[i].peiv_name==*str){
			    g_sum_pers+=peivs[i].peiv_id;
		    }	
	    }
	    str++;
	}
	return g_sum_pers;
}
/*************不同角色分配到不同的域*****************************/
void superadmin_accept(char *strrname)
{
	printf("#########################################\n");
	printf("三、现在登录的是超级管理员:\n");
	int32_t sp_pers=0;
	sp_pers=role_t_per(strrname);
	printf("Now g_pers is %d,1111\n",sp_pers);
	usrs_pers(sp_pers);
	usrs_ch_operate();
}
void admin_accept(char * strrname)
{
	printf("#########################################\n");
	printf("三、现在登录的是管理员:\n");
	int32_t admin_pers=0;
	admin_pers=role_t_per(strrname);
	printf("Now g_pers is %d,1100\n",admin_pers);
	usrs_pers(admin_pers);
	usrs_ch_operate();
}
void usr_accpet(char * strrname)
{
	printf("#########################################\n");
	printf("三、现在登录的是普通用户。\n");
	int32_t usr_pers=0;
	usr_pers=role_t_per(strrname);
	printf("Now g_pers is %d，1000\n",usr_pers);
	usrs_pers(usr_pers);
	usrs_ch_operate();
}
/**************决策权限集的使能*****************************/
void usrs_pers(int32_t npers)
{
	printf("#########################################\n");
	printf("五、决定哪些权限使能\n");
	int32_t usrpers = npers;
	switch(usrpers){
		case 15:
		    g_per_r=1;
			g_per_w=1;
			g_per_a=1;
			g_per_d=1;
			break;
		case 3:
			g_per_r=1;
			g_per_w=1;
			g_per_a=0;
			g_per_d=0;
			break;
		case 1:
		    g_per_r=1;
			g_per_w=0;
			g_per_a=0;
			g_per_d=0;
			break;
		default :
		    g_per_r=0;
			g_per_w=0;
			g_per_a=0;
			g_per_d=0;
		    break;
	}
}
/***************用户的相应操作*********************************/
void usrs_ch_operate()
{
	printf("#########################################\n");
	printf("六、准备开始执行您的权限吧\n");
	char usr_x;
	int32_t flag=1;
	printf("请输入您要执行的操作:\n");
	printf("可以执行r,w,a,d##代表###r:read;w:write;a:add;d:del:\n");
	printf("Now RWAD is %d,%d,%d,%d\n",g_per_r,g_per_w,g_per_a,g_per_d);
	while(flag){	
	 scanf(" %c",&usr_x);
	    switch(usr_x){
            case 'r':
			    if(g_per_r)
					usr_read();
				else
					printf("您可能没有这个权限！\n");
				break;
            case 'w':
			    if(g_per_w)
				    usr_write();
				else
				    printf("您可能没有这个权限！\n");
				break;
			case 'a':
			    if(g_per_a)
					usr_add();
				else
					printf("您可能没有这个权限！\n");
				break;
			case 'd':
			    if(g_per_d)
					usr_del();
				else
					printf("您可能没有这个权限！\n");
				break;
			case 'q':
			    flag=0;
			    printf("拜拜！！！！\n");
			    break;
			default :		    
				printf("您可能没有这个权限！\n");				
				break;	
		}
	}
}
void usr_read(void)
{	
    printf("读一个文件.\n");	
}
void usr_write(void)
{	
    printf("写一个文件.\n");
}
void usr_add(void)
{
    printf("修改一个文件。\n");
}
void usr_del(void)
{
    printf("删除一个文件。\n");
}

