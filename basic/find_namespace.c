// ============ 注解 ============== //

struct A {};            // 标签命名空间引入A
typedef struct A A;     // 首先查找标签命名空间的A，然后再名称A引入通常命名空间

struct A* p;            // OK, 此A从标签命名空间中查找
A* q;                   // OK, 此A从通常命名空间中查找


// C中的枚举常量不是结构体成员，其命名为通常标识符的命名空间
struct tagged_union {
    enum {INT, FLOAT, STRING} type;
    union {
        int integer;
        float floating_point;
        char* string;
    }
} tu;

tu.type = INT;  // C中OK，C++中错误【可以看到INT这个枚举中常量可以在外部的通常命名空间中访问】

// ============== 示例 ============== //
void foo (void) { return; } // 通常命名空间，文件作用域

struct foo {    // 标签命名空间，文件作用域
    int foo;    // struct foo的成员命名空间，文件作用域
    enum bar {  // 标签命名空间
        RED     // 通常命名空间
    } bar;      // 成员命名空间
    struct foo* p;  // OK，使用的标签命名空间
};

enum bar x;
// int foo
// union foo {int a, b;};

int main(void) {
    goto foo;   // 标号命名空间，函数作用域

    struct foo {    // 标签命名空间，块作用域
        enum bar x;
    };
    typedef struct foo foo; // 从标签命名空间/块作用域查找到，然后定义的在通常命名空间/块作用域

    (foo){.x = RED};    // 使用标签命名空间/块作用域 和 通常命名空间/文件作用域
 foo:;
}
