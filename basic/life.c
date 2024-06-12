int* foo(void)
{
    int a = 17;
    return &a;
}

int main(void) {
    // p 指向生命周期结束后的对象（悬垂指针）
    int* p = foo();
    int n = *p; // 未定义行为
}

// ============ 临时生存期 ============ //

struct T {double a[4];};
struct T f(void) { return (struct T) {3.15} }
double g1(double* x) { return *x; }
void g2(double* x) {*x = 1.0;}

int main(void) {
    double d = g1(f().a);
    g2(f().a);
}
