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

// C23
enum {TEN = 10; };
struct S {int x: TEN; }
