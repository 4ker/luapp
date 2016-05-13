/**
@file   GetGlobalVariable.cpp
@brief  Show you how to get global variable from lua script.
*/

#include <cstdio>
#include <cstdlib>
#include "luapp.hpp"

/* GetGlobalVariable.lua
-----------------------------------------------------

lua_power="on"

-----------------------------------------------------
*/

int main()
{
    lua::State<> lua;

    lua.Init();

    lua.AddMainPath(LUAPP_SCRIPT_PATH);

    lua.DoScript("GetGlobalVariable.lua");

    // 在 C++ 里，它是 std::string
    lua::Str power;

    // 在 lua 里，它是 lua_power，泛型
    lua.GetGlobal("lua_power",&power);

    // 因为已经执行完了 lua 脚本，lua 实例里的值已经拿到了 power 里
    // （即上面的 GetGlobal）
    printf("Power was turn %s\n",power.c_str());

    return EXIT_SUCCESS;
}