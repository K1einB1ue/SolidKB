#include<SolidKernel.h>
extern void Kernel_Init();
extern void Kernel_Run();
extern void Kernel_Exit();
__attribute__((weak)) void Kernel_Init(){return;};
__attribute__((weak)) void Kernel_Run(){return;};
__attribute__((weak)) void Kernel_Exit(){return;};
int main(){
    Kernel_Init();
    Kernel_Run();
    Kernel_Exit();
    return 0;
}