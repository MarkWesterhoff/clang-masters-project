#include "foo.h"

bool  function_not_in_header(){
  return true;
}

int function_only_declared(int a){
  return a;
}

bool Foo::member_only_declared(bool b){
  return b;
}

int main(){
  Foo f;
  function_not_in_header();
  function_only_declared(5);
  f.member_only_declared(true);
  return 0;
}