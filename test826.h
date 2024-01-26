#ifndef __TEST826_H__
#define __TEST826_H__

typedef unsigned char uint8_t;

typedef enum
{
    student_info_continue,
    student_info_exit
} student_ret;

// 学生信息
typedef struct student
{
    uint8_t name[10];
    uint8_t age;
    int id;//需要唯一，不然后续只会返回第一次出现的id，可优化
    uint8_t core;
    struct student *next; // 链表指针
}stu,*Pstu;

student_ret students_info_management();

#endif