#include <stdio.h>
#include <math.h>				//加入数学函数库，以提供幕运算函数fabs()
int main()
{
   double s, t, x;				//定义双精度型变量s、t、x，其中s保存计算结果，t表示下一项的结果，x表示操作数。
   int n;						// 定义整型变量n，n表示公式中的幕
   printf("请输入x的值：");		// 输出提示信息
   scanf("%lf", &x); 			// 获取操作数
   t = x;						// 使t的值等于x，得到公式中第一项的值
   n = 1;						// 初始化幕数n为1
   s = x;						// 将第一项的结果保存到结果s中
   do							// 开始执行循环体
   {
      n += 2;					// 幕数自增2
      t *= (-x * x) / ((float)(n) - 1) / (float) (n);
								// 计算公式中当前项的值
      s += t;					// 将当前项的值加入到结果中
   } while (fabs(t) >= 1e-7);	//判断当前项的值小于大于预期，如果小于则继续执行循环体
   printf("\n sin(%f) = %lf\n", x, s);	// 输出计算结果,好的
   return 0;
}
