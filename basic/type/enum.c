enum color_t {RED, GREEN, BLUE} c = RED, *cp = &c;
// 引入类型enum color_t
// 整数常量RED, GREEN, BLUE
// 对象c拥有类型enum color_t

// ============= 解释 ======== //
enum color {RED, GREEN, BLUE} r = RED;
switch(r) {
    case RED:
        puts("red");
        break;
    case GREEN:
        puts("green");
        break;
    case BLUE:
        puts("blue");
        break;
}

enum color g = GREEN;
// color x = GREEND; // error
typedef enum color color_t;
color_t x = GREEN;  // OK

//

enum { ONE = 1, TWO } e;
long n = ONE; // 提升
double d = ONE; // 转换
e = 1.2; // 转换，e现在是ONE
e = e + 1; // 转换，e现在是TWO

// =========== 注解 ============ //
enum Color; // 错误，C中无enum的前置声明
enum Color { RED, GREEN, BLUE };

#define TEN 10
struct S { int x: TEN; }; // OK
// or
enum { TEN = 10 };
struct S { int x: TEN; }; // OK


// C23
enum {TEN = 10; };
struct S {int x: TEN; }

struct Element {
    int z;
    enum State { SOLID, LIQUID, GAS, PLASMA } state;
} oxygen = { 8, GAS };

void foo(void) {
    enum State e = LIQUID;
    printf("%d %d %d ", e, oxygen.state, PLASMA); // 打印1 2 3
}

// ============== 示例 ============= //
#include <stdio.h>

int main(void) {
    enum TV { FOX = 11, CNN = 25, ESPN = 15, HBO = 22, MAX = 30, NBC = 32 };

    printf("List of cable stations:\n");
    printf(" FOX: \t%2d\n", FOX);
    printf(" HBO: \t%2d\n", HBO);
    printf(" MAX: \t%2d\n", MAX);
}
