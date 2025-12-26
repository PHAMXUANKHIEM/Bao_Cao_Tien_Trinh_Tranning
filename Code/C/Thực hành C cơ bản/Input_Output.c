#include <stdio.h>
int main()
{
  int a;
  int b;
  int c;
  char x;
  printf("Nhập số a và b: ");
  scanf("%d%d", &a, &b);
  printf("Nhập dấu: ");
  scanf(" %c", &x);

  if (x == '/')
  {
    if (b == 0)
    {
      printf("Lỗi không chia được\n");
    } else {
        if (a%b==0){
          printf("Giá trị của c là: %d", a/b);
          }
        else{
          printf("Giá trị của c là: %f", (float)a/b);

        }
    }
  }
  else if (x == '+'){
    c = a+b;
    printf("Giá trị của c là: %d", c);
  }
  else if (x == '-'){
    c =a - b;
    printf("Giá trị của c là: %d", c);
    }
  else{
    c = a * b;
    printf("Giá trị của c là: %d", c);
    }
  return 0;
} 