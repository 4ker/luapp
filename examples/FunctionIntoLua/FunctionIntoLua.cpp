/**
@file   FunctionIntoLua.cpp
@brief  Show you how to call a C function in lua script.
*/

#include <cstdlib>
#include "luapp.hpp"

/* FunctionIntoLua.lua
-----------------------------------------------------

print("Function Into Lua")

param = 6

num = NumberPlus(param)

print("Answer is " .. param .. "+1 = " .. num)

-----------------------------------------------------
*/

lua::Int MyFunction(lua::Int num)
{
    return num+1;
}

int main()
{
    lua::State<>    lua;

    lua.Init();

    lua.AddMainPath(LUAPP_SCRIPT_PATH);

    // 把 lua 脚本中的 NumberPlus 绑定到 MyFunction 这个函数
    lua.RegisterFunction("NumberPlus",&MyFunction);   // Lua script has MyFunction() now.

    // 运行它，因为 lua 不是 type strict，所以不用在“声明”的时候指定 Lua::Int 什么的。
    // 这个 Lua::Int 其实就是 int 的 typedef。
    lua.DoScript("FunctionIntoLua.lua");

    return EXIT_SUCCESS;
}