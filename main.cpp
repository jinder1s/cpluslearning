#include <cstdio>

int step_function(int x) {
  int result = 0;
  if (x < 0) {
    return -1;
  } else if (x > 0) {
    return 1;
  }else{
      return 0;
  }
}
int absolute_value(int x){
    if (x >= 0) return x;
    return -1*x;
}

int get_number(int x) { return 5 * x; }

int main() {
  int x = get_number(-5);
  printf("absolute val: %d, %d\n",x, absolute_value(x));
}
