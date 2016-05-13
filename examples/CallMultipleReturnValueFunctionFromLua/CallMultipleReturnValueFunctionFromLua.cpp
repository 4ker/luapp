/**
@file   CallMultipleReturnValueFunctionFromLua.cpp
@brief  Show you how to call a global function of lua script.
*/

#include <cstdio>
#include <cstdlib>
#include "luapp.hpp"

/* CallMultipleReturnValueFunctionFromLua.lua
-----------------------------------------------------

function func()
    local   x,y,z=1,2,3
--	local   x=1,y=2,z=3    It's not allow in lua.
    return x,y,z
end

-----------------------------------------------------
*/

int main()
{
    using lua::Int;

    lua::State<>    lua;

    lua.Init();

    lua.AddMainPath(LUAPP_SCRIPT_PATH);

    lua.DoScript("CallMultipleReturnValueFunctionFromLua.lua");

    // 因为 using 了 lua::Int 就不用再麻烦得用 Lua::Int 了。
    // 这里定义一个 C++ 函数。
    lua::FunctionExt<void(Int,Int,Int),void(void)> func;

    // 这个函数从 lua 脚本里来。
    lua.GetFunction("func",&func);

    int x,y,z;

    // 从 lua 脚本获取返回值。
    func(&x,&y,&z);

    printf("Return values:\n");
    printf("x=%d\n",x);
    printf("y=%d\n",y);
    printf("z=%d\n",z);

    return EXIT_SUCCESS;
}