// ============= 兼容类型 ======== //
// TEST 1 --------
// TU1
struct S {int a;};
extern struct S *x; // 与TU2的x兼容，和TU3的x不兼容

// TU2
struct S;
extern struct S *x; // 与TU1和TU3的x都兼容

// TU3
struct S {float a;};
extern struct S *x; // 与TU2的x兼容，和TU3的x不兼容

// TEST 2 -------
// TU1
#include <stdio.h>

struct s {int i;};  // 兼容TU3
extern struct s x = {0};
extern void f(void);

int main() {
    f();
    return x.i;
}

// TU2
struct s {float f;};    //兼容TU4
extern struct s y = {3.14};
void f() {
    return;
}

// TU3
struct s {int i;};  // 兼容TU1
extern struct s x;

// TU4
struct s {float f;};    // 兼容TU2
extern struct s y;

// ============== 合成类型 ========= //
int f(int (*)(), double (*)[3]);
int f(int (*)(char *), double (*)[]);   //C23：会出现对于f的冲突

// 合成类型
int f(int (*)(char *), double (*)[3]);

// ============= 不完整类型 ========= //
extern char a[];    // a的类型不完整
char a[10];         // a的类型现在完整

struct node {
    struct node* next;  // node的类型在此点不完整
};  // node的类型现在完整

// ========== 类型名 =============//
int n;                                  // 声明int
sizeof(int);                            // 使用类型名

int *a[3];                              // 声明一个存有3个int指针的数组
sizeof(int *[3]);

int (*p)[3];                            // 声明一个指向3个int数组的指针
sizeof(int (*)[3]);

int (*a)[*];                            // 声明一个指向VLA的指针
sizeof(int (*)[*]);

int *f(void);                           // 声明一个函数
sizeof(int *(void));

int (*p)(void);                         // 声明指向函数的指针
sizeof(int (*)(void));

int (*const a[])(unsigned int, ...) = {0}; // 声明指向函数指针的数组
sizeof(int (*const [])(unsigned int, ...));

// 围绕标识符的冗余括号
int (n);        // 声明int类型的n
sizeof(int ());// 使用类型“返回int的函数”

//
void* p = (void*)(struct X {int i;} *)0;
struct X x = {1};
