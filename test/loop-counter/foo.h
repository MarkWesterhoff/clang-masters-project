#pragma once
int function_only_declared(int a);

class Foo{
public:
  bool member_only_declared(bool b);
  void member_defined(){
    return;
  }
};