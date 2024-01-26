#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include "test826.h"

// // #define add(a,b) (a)*(b)
// #define hiwdad      \
//     do              \
//     {               \
//         dadadaadada \
//     } while (0);

Pstu head = NULL;

// 初始化学生信息链表
Pstu stu_info_init()
{
#if 0
    (void *)head  = malloc(sizeof(stu));
    // memset(head,0,sizeof(head));
    bzero(head,sizeof(head));
#endif

    head = (Pstu)calloc(1, sizeof(stu));

    if (head == NULL)
    {
        printf("init head note err!\n");
        return NULL;
    }
    printf("stu_info_init success!\n");
    head->age = 18;
    head->id = 0;
    head->core = 100;
    memcpy(head->name, "张三", sizeof(head->name));
    head->next = NULL;

    return head;
}

// 判断head是否已初始化
bool head_isORnot(Pstu head)
{
    if (head == NULL)
    {
        return false;
    }
    return true;
}
// 加入新节点信息,尾插法
void add_note(Pstu note)
{
    if (!head_isORnot)
    {
        // 不存在头节点则先创建头节点
        stu_info_init();
    }
    Pstu cur = head;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = note;
}

// 增加学生信息
bool add_stu_info(uint8_t age, uint8_t core, int id, uint8_t *name)
{
    // 创建新节点
    Pstu new_note = calloc(1, sizeof(stu));
    if (new_note == NULL)
    {
        printf("增加学生信息失败\n");
        return false;
    }

    new_note->age = age;
    new_note->core = core;
    new_note->id = id;
    strcpy(new_note->name, name);

    new_note->next = NULL;

    add_note(new_note);
    return true;
}

// 按名字剔除学生信息,默认的头节点不支持删除
bool remove_stuinfo_by_name(uint8_t *name)
{
    if (!head_isORnot)
    {
        // printf("暂无学生信息");
        return false;
    }
    Pstu rm_note = head;
    Pstu backup_note = NULL;
    while (rm_note->next != NULL) // 遍历到尾节点，此时的尾节点其实对比过是否符合
    {
        backup_note = rm_note;
        rm_note = rm_note->next;
        if (strcmp(rm_note->name, name) == 0)
        {
            if (rm_note->next == NULL)
            {
                backup_note->next = NULL;
            }
            else
            {
                backup_note = rm_note->next; // 指向被删除的节点的下一节点
            }
            // 释放节点
            free(rm_note);
            return true;
        }
    }

    // 循环完都没找到
    return false;
}

// 按id剔除学生信息
bool remove_stuinfo_by_id(int id)
{
    if (!head_isORnot)
    {
        // printf("暂无学生信息");
        return false;
    }
    Pstu rm_note = head;
    Pstu backup_note = NULL;
    while (rm_note->next != NULL) // 遍历到尾节点，此时的尾节点其实对比过是否符合
    {
        backup_note = rm_note;
        rm_note = rm_note->next;
        if (rm_note->id == id)
        {
            if (rm_note->next == NULL)
            {
                backup_note->next = NULL;
            }
            else
            {
                backup_note = rm_note->next; // 指向被删除的节点的下一节点
            }
            // 释放节点
            free(rm_note);
            return true;
        }
    }
    // 循环完都没找到
    return false;
}

// 按id查询学生信息
bool cheack_stuinfo_by_id(int id, void (*callback)(Pstu info))
{
    if (!head_isORnot)
    {
        // printf("暂无学生信息");
        return false;
    }
    Pstu cur = head;
    while (cur != NULL)
    {
        if (cur->id == id)
        {
            callback(cur);
            return true;
        }
        cur = cur->next;
    }
    // 循环完都没找到
    return false;
}

// 按姓名查询学生信息
bool cheack_stuinfo_by_name(uint8_t *name, void (*callback)(Pstu info))
{
    if (!head_isORnot)
    {
        // printf("暂无学生信息");
        return false;
    }
    Pstu cur = head;
    while (cur != NULL)
    {
        if (strcmp(cur->name, name)==0)
        {
            callback(cur);
            return true;
        }
        cur = cur->next;
    }
    // 循环完都没找到
    return false;
}

// 遍历学生信息,遍历出来的节点交给回调处理，头节点也删除
void ergodic_stu_node(Pstu head, void (*callback)(Pstu info))
{
    if (!head_isORnot) // 系统未创建
    {
        // printf("no student info!\n");
        return;
    }
    Pstu callback_note = head;
    Pstu backup_note = head; // 备份下一个节点作为head，防止是删除节点的回调函数删除节点后遍历出错

    while (backup_note != NULL) // 遍历到尾节点处理后跳出
    {
        backup_note = callback_note->next;
        callback(callback_note);
        callback_note = backup_note;
    }
}
// 显示回调函数
void show_info(Pstu info)
{
    printf("姓名:%s 年龄:%hhd 学号:%d 升学成绩:%hhd\n", info->name, info->age, info->id, info->core);
}

// 删库回调函数
void remove_note(Pstu note)
{
    free(note);
}

// 清空缓冲区
void clear_buf()
{
    char buf;
    while ((buf = getchar()) != '\n')
        ;
}

// 给系统调用的api
bool cheak_by_id()
{
    int id = -1;
    printf("请输入你要查询的学号\n");
    scanf("%d", &id);
    printf("你的输入为:%d\n",id);
    clear_buf();
    return cheack_stuinfo_by_id(id, show_info);
}
bool cheak_by_name()
{
    char buf[10] = {0};
    printf("请输入你要查询的姓名\n");
    scanf("%s", buf);
    clear_buf();
    return cheack_stuinfo_by_name(buf, show_info);
}
// 录入学生信息
bool add_student()
{
    int flag = 0;
    int id = 0;
    uint8_t core = 0, age = 0;
    uint8_t name[10] = {0};
    int yesORnot = -1;
    while (1)
    {
        switch (flag)
        {
        case 0:
            printf("请输入学生名字:\n");
            if (scanf("%s", &name) != 1)
            {
                flag = 0;
                clear_buf();
                printf("输入有误请重新输入!!\n");
            }
            else
            {
                clear_buf();
                flag = 1;
            }
            break;
        case 1:
            printf("请输入学生学号:\n");
            if (scanf("%d", &id) != 1)
            {
                flag = 1;
                clear_buf();
                printf("输入有误请重新输入!!\n");
            }
            else
            {
                clear_buf();
                flag = 2;
            }
            break;

        case 2:
            printf("请输入学生年龄:\n");
            if (scanf("%hhd", &age) != 1)
            {
                flag = 2;
                clear_buf();
                printf("输入有误请重新输入!!\n");
            }
            else
            {
                clear_buf();
                flag = 3;
            }
            break;

        case 3:
            printf("请输入学生升学成绩:\n");
            if (scanf("%hhd", &core) != 1)
            {
                flag = 3;
                clear_buf();
                printf("输入有误请重新输入!!\n");
            }
            else
            {
                clear_buf();
                flag = 4;
            }
            break;

        case 4:

            printf("名字:%s\n", name);
            printf("学号:%d\n", id);
            printf("年龄:%hhd\n", age);
            printf("分数:%hhd\n", core);
            printf("请确认你的输入:(重新输入:0)/(确认录入:1)/(取消录入:其他数字)\n");
            if (scanf("%d", &yesORnot) == 1)
            {
                printf("你的输入为:%d\n", yesORnot);
                clear_buf();
                if (yesORnot == 1)
                {
                    flag = 5;
                    printf("确认完成,正在录入!!\n");
                }
                else if (yesORnot == 0)
                {
                    flag = 1;
                }
                else
                    return false;
            }
            break;
        case 5:
            if (!add_stu_info(age, core, id, name))
            {
                // flag = 1;
                printf("录入成功学生信息失败！\n");
                return false;
            }
            else
            {
                printf("录入成功学生信息成功！\n");
                return true;
            }
            break;

        default:
            break;
        }
    }
}
// 删除对应学生信息
bool del_stuinfo()
{
    int flag = -1;
    int id = 0;
    uint8_t name[10] = {0};
    printf("0:按id删除 1:按名字删除\n请选择:\n");
    scanf("%d", &flag);
    clear_buf();
    printf("你的选择是:%d\n", flag);
    switch (flag)
    {
    case 0:
        printf("请输入ID\n");
        if (scanf("%d", &id) == 1)
        {
            if (!remove_stuinfo_by_id(id))
            {
                printf("查无此人!\n");
                return false;
            }
        }
        break;
    case 1:
        printf("请输入名字\n");
        if (scanf("%s", name) == 1)
        {
            if (!remove_stuinfo_by_name(name))
            {
                printf("查无此人!");
                return false;
            }
        }
        break;
    default:
        printf("输入有误!\n");
        return false;
        break;
    }
    return true;
}

student_ret students_info_management()
{
    student_ret rett = student_info_continue;
    int cmd = -1;
    printf("------------------------------------------------------------------------\n");
    printf("|------------------------请输入你的选择：------------------------------|\n");
    printf("|所有学生信息:0---按学号查询:1---按姓名查询:2---升学办理:3---退学办理:4|\n");
    printf("|--------------------其他:删除信息库并退出系统-------------------------|\n");
    printf("------------------------------------------------------------------------\n");
    scanf("%d", &cmd);
    clear_buf();
    printf("你输入的数字为:%d\n", cmd);
    switch (cmd)
    {
    case 0:
        ergodic_stu_node(head, show_info);
        break;

    case 1:
        if (!cheak_by_id())
            printf("查无此人!\n");
        // rett = student_info_exit;
        break;

    case 2:
        if (!cheak_by_name())
            printf("查无此人!\n");
        // rett = student_info_exit;
        break;

    case 3:
        if (!add_student())
        {
            printf("录入已取消\n");
        }
        break;

    case 4:
        if (del_stuinfo())
        {
            printf("删除成功!\n");
        }
        break;
    default:
        printf("退出并删除...c错误码%d\n", cmd);
        return student_info_exit;
        break;
    }
}

int main(int argc, char const *argv[])
{
    printf("欢迎使用学生升学信息管理系统!\n");
    printf("作者:谭婉华\n");
    student_ret ret = student_info_exit;
    // 初始化学生链表
    // head = ;
    stu_info_init();
    while (1)
    {
        ret = students_info_management(); // 未退出则循环
        if (ret == student_info_exit)
            break;
    }
    // 删除所有信息
    ergodic_stu_node(head, remove_note);
    return 0;
}