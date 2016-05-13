/**
@file   CallFunctionFromLua.cpp
@brief  Show you how to call a global function of lua script.
*/

#include <cstdio>
#include <cstdlib>
#include "luapp.hpp"

/* CallFunctionFromLua.lua
-----------------------------------------------------

function func(a, b, c)
    local   x=a+b+c
    print( a .. "+" .. b .. "+" .. c .. "=" .. x)
    return x
end

-----------------------------------------------------
*/


int main()
{
    using lua::Int;

    lua::State<>    lua;

    lua.Init();

    lua.AddMainPath(LUAPP_SCRIPT_PATH);

    lua.DoScript("CallFunctionFromLua.lua");

    // 定义一个函数声明（C++ 里必须有 strict 的输入输出）
    lua::Function<Int(Int,Int,Int)>   func;

    // 注册它
    lua.GetFunction("func",&func);

    // 运行，调用的其实是 lua 里的 func 函数，返回一个 int
    printf("Return value is %d\n",func(1,2,3));

    return EXIT_SUCCESS;
}