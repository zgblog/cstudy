float fa[11], *afp[17]; // 数组，指针数组

// ============= 已知常量大小数组 ==== //
int n[10];                  // 10 是常量
char o[sizeof(double)];     // sizeof是常量表达式
enum { MAX_SIZE = 100; };   // 枚举常量是常量表达式
int n[MAX_SIZE];

int a[5] = {1, 2, 3};   // 初始化为 1, 2, 3, 0, 0
char str[] = "abc";     // char[4] 初始化为 abc\0

// static
void fadd(double a[static 10], const double b[static 10]) {
    for (int i=0; i<10; i++) {
        if (a[i] < 0.0) return;
        a[i] += b[i];
    }
}

int main() {
    double a[10] = {0}, b[20] = {0};
    fadd(a, b); // OK
    double x[5] = {0};
    fadd(x, b); // 未定义行为；数组参数太小
}
// const 限定
int f(const int a[20]) {
    // 函数中，a类型为const int*
}
int g(const int a[const 20]) {
    // 函数中，a类型为const int* const（指向const int的const指针）
}

// restrict 限定
void fadd(double a[static restrict 10],
    const double b[static restrict 10]) {
    
    for (int i=0; i<10; i++) {
        if (a[i] < 0.0)
            break;
        a[i] += b[i];
    }
}

// =============== 非常量长度数组 ========== //
#include <stdio.h>

int main(void) {
    int n = 1;
 label:;
    int a[n]; // 重分配10次，每次拥有不同大小
    printf("The array has %zu elements\n", sizeof a / sizeof *a);
    if (n++ < 10)
        goto label; // 离开作用域的VLA结束其生命周期
}

void foo(size_t x, int a[*]);
void foo(size_t x, int a[x]) { // VLA处理成*
    printf("%zu\n", sizeof a); // 大小同sizeof(int*)
}

// VLA与被它们派生的类型（如指向他们的指针等），通称为“可变修改类型VM”. VM只能声明于块作用域或者函数作用域
extern int n;
int A[n];           // ERR
extern int (*p2)[n];    //ERR
int B[100]; // OK
void fvla(int m, int C[m][m]);  // OK；原型作用域VLA

// 指向VLA的指针，但不是VLA自身可以拥有静态存储期；VM类型不能有链接
void fvla(int m, int C[m][m]) {
    typedef int VLA[m][m];
    int D[m];   // OK
    // static int E[m]; // ERR，静态存储期VLA
    // extern int F[m]; // ERR，拥有链接的VLA
    int (*s)[m];
    s = malloc(m * sizeof(int));
    // extern int (*r)[m]
    static int (*q)[m] = &B;
}

// 可变修改类型不能是结构体或者联合体的成员
struct tag {
    int z[n]; // ERR，VLA结构体成员
    int (*y)[n]; //ERR，VM结构体成员
}

// ================== 未知大小数组 =========== //
extern int x[]; // 边界未知
int a[] = {1, 2, 3};

// struct中，未知大小数组可以作为最后一个元素出现
struct s { int n; double d[]; }; // s.d是柔性数组成员
struct s *s1 = malloc(sizeof ( struct s) + (sizeof (double) * 8));// 如同d是double d[8]

// ============= 限定符 ================== //
// 数组声明具有const、volatile、或 restrict 限定符，限定的是元素类型
// 始终认为数组类型与其元素类型有等同的限定，但不认为数组类型有_Atomic限定

typedef int A[2][3];
const A a = {{4, 5, 6}, {7, 8, 9}};
int *pi = a[0]; // ERR，a[0]类型为const int*
void *unqual_ptr = a;// C23前OK
// 不能对数组类型_Atomic
typedef int A[2];
_Atomic int a2[2] = {0};
_Atomic(int) a3[2] = {0};

// ================= 赋值 ================ //
int a[3] = {1, 2, 3}, b[3] = {4, 5, 6};
int (*p)[3] = &a;   // OK
// a = b; // ERR
struct { int c[3]; } s1, s2 = {3, 4, 5};
s1 = s2; // OK

// =============== 数组到指针转换 =========== //

int a[3] = {1, 2, 3};
int *p = a;
printf("%zu\n", sizeof a);  // 打印数组大小
printf("%zu\n", sizeof p); // 打印指针大小

#include <stdio.h>

void f(int a[], int sz) {   // 实际上声明void f(int *a, int sz)
    for (int i=0; i<sz; ++i) {
        printf("%d\n", a[i]);
    }
}

void g(int (*a)[10]) {
    for (int i=0; i<10; ++i) {
        printf("%d\n", (*a)[i]);
    }
}

int main(void) {
    int a[10] = {0};
    f(a, 10);
    g(&a);
}

// =========== 多维数组 =========== //
int a[2][3] = {{1, 2, 3}, {4, 5, 6}};

int a[2][3];
int (*p1)[3] = a;
int b[3][3][3];
int (*p2)[3][3] = b;

// =========== 注解 ============== //
int n = 5, m = 5;
size_t sz = sizeof(int (*[n++])[m++]); // n自增，m可能自增也可能不自增
