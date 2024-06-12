typedef int int_t;  // 声明int_t为int的别名
typedef char chart_t, *chart_p, (*fp)(void);    // 声明char_t为char别名，char_p为char*的别名，fp为char(*)(void)别名

// =========== 解释 ========= //
void copyt(int n) {
    typedef int B[n];   // B是 VLA，其长度为n，现在求值
    n += 1;
    B a;    // a的长度是 += 1前的n
    int b[n];   // a和b的长度不同
    for (int i=1; i<n; i++) {
        a[i-1] = b[i];
    }
}

// =========== 注解 ======= //
// typedef名可以是不完整类型
typedef int A[];    // A是int[]
A a = {1, 2}, b = {3, 4, 5};

// typedef通常用于将名称从标签命名空间注入到通常命名空间
typedef struct tnode tnode;

struct tnode {
    int count;
    tnode *left, *right; // 同 struct tnode *left, *right;
};

tnode s, *sp;   // 同 struct tnode s, *sp;

// 避免使用标签命名空间
typedef struct {double hi, lo;} range; // 匿名结构体
range z, *zp;

// 简化复杂声明

int (*(*callbacks[5])(void))[3]; // 包含5个函数指针的数组，函数返回指向3个int的数组的指针

typedef int arr_t[3];   // arr_t为3个int的数组
typedef arr_t* (*fp)(void); // 指针指向的函数返回arr_t*
fp callbacks[5];

// 库通常以来系统或配置的类型暴漏为typedef名称，以便对外暴漏统一接口
#if defined(_LP64)
typedef int wchar_t;
#else
typedef long wchar_t;
#endif
