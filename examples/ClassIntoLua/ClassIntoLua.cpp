/**
@file   ClassIntoLua.cpp
@brief  Show you how to new a C++ object in lua script.
*/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "luapp.hpp"

/* ClassIntoLua.lua
-----------------------------------------------------

object = MyClass()

param = 6

num = object:Count(param,0.1,0.2,"Good"," job")

print("Answer is " .. param .. "+1 = " .. num)

-----------------------------------------------------
*/

class MyClass
{
public:

    MyClass() {
        printf("do MyClass::MyClass()\n");
    }

    ~MyClass()
    {
        printf("do MyClass::~MyClass()\n");
    }

    lua::Int Count( lua::Int num01,
        lua::Num num02,
        lua::Num num03,
        lua::Str num04,
        lua::Str num05)
    {
        printf("do MyClass::Count() start\n");

        printf("param2+param3=%f\n",num02+num03);
        printf("param4+param5=%s\n",(num04+num05).c_str());

        printf("do MyClass::Count() end\n");
        return num01+1;
    }
};

int main()
{
    lua::State<> lua;

    lua.Init();

    lua.AddMainPath(LUAPP_SCRIPT_PATH);

    // �� C++ ����ע�ᵽ lua
    lua.RegisterClass<MyClass>("MyClass");                 // Lua script has class now.
    // �����������Ա
    lua.RegisterMemberFunction("Count",&MyClass::Count);   // Lua script has member function now.

    // �⣬�������仰���Խ���˳��

    // ���г��򣬻�ȡ DoScript �з���ֵ��
    if( ! lua.DoScript("ClassIntoLua.lua") ) {
        std::cout<<lua.GetError()<<std::endl;
    }

    return EXIT_SUCCESS;
}
