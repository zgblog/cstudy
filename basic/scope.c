// ============ 嵌套作用域 ============= //
// 此处的命名空间为通常标识符

int a;  // 作用域

void f(void) {
    int a = 1;
    {
        int a = 2;
        printf("%d\n", a);
    }
    printf("%d\n", a);
}

void g(int a);

// ============ 块作用域 ================//
void f2(int n)
{
    ++n;
    for(int n=0; n<10; n++)
    {
        printf("%d\n", n);
    }
    printf("%d\n", n);
}

enum {a,b};
int different(void)
{
    // C99前，选择和迭代语句不建立自身块作用域
    if(sizeof(enum {b, a}) != sizeof(int))
        return a;
    return b;
}

// ============= 文件作用域 ============= //
int i;
static int g(int a) { return a;}
int main(void)
{
    i = g(2);
}

// ============ 函数作用域 ============= //
void f3()
{
    {
        goto label;
 label:;
    }
    goto label; // 标号忽略块作用域
}

// ============== 函数原型作用域 ======== //
int f(int n, int a[n]); // n在作用域中并指代第一形参

void f(long double f, char (**a)[10 * sizeof f]);   // f代指第一形参
enum {n=3};
int (*(*g)(int n))[n];
// 返回3个int的数组的指向函数指针的指针

// ============= 声明点 ================ //
struct Node {
    struct Node* next;
}

enum {x = 12;};
{
    enum { x = x + 1, // 新x不在作用域中，初始化x为13
        y = x + 1   // 新的x在作用域中，初始化y为14
        };
}

int x = 2;
{
    int x[x];   // 新声明的x
}

unsigned char y = 32;
{
    unsigned char y = y;
}

unsigned long factorial(unsigned long n)
{
    return n < 2 ? 1: n * factorial(n-1);
}

