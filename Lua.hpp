/**
@file   Lua.hpp
@brief  It's just a wrapper of lua.
*/

#ifndef _LUA_HPP_
#define _LUA_HPP_


extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}


#include <vector>
#include <string>



namespace lua{

/*
Those date type have worked in luapp.
You can't use the other date type to work with luapp.
*/
typedef double          Num;
typedef int             Int;
typedef std::string     Str;



typedef lua_State* Handle;
typedef int (*CFunction) (Handle);   // lua::CFunction as lua_CFunction
typedef const char* Name;



inline Handle CreateHandle()
{
	return luaL_newstate();
}
inline void DestroyHandle(Handle h)
{
	lua_close(h);
}
inline int PCall(Handle h,int num01,int num02,int num03)
{
	return lua_pcall(h,num01,num02,num03);
}
inline void OpenLibs(Handle h)
{
	luaL_openlibs(h);
}
inline int DoScript(Handle h,Name filename)
{
	luaL_loadfile(h,filename);
	lua_pcall(h,0,0,0);
	return 0;
}
inline void NewTable(Handle h)
{
	lua_newtable(h);
}
inline int NewMetaTable(Handle h,Name tname)
{
	return luaL_newmetatable(h,tname);
}
inline void* NewUserData(Handle h,size_t size)
{
	return lua_newuserdata(h,size);
}
inline void SetGlobal(Handle h,Name var)
{
	lua_setglobal(h,var);
}
inline void GetGlobal(Handle h,Name var)
{
	lua_getglobal(h,var);
}
inline void SetTable(Handle h,int index)
{
	lua_settable(h,index);
}
inline void GetTable(Handle h,int index)
{
	lua_gettable(h,index);
}
inline void SetField(Handle h,int index, Name name)
{
	lua_setfield(h,index,name);
}
inline void GetField(Handle h,int index, Name k)
{
	lua_getfield(h,index,k);
}
inline int SetMetaTable(Handle h,int index)
{
	return lua_setmetatable(h,index);
}
inline void GetMetaTable(Handle h,Name name)
{
	luaL_getmetatable(h,name);
}
inline void PushClosure(Handle h,CFunction fn,int n)
{
	lua_pushcclosure(h, fn, n);
}
inline void PushFunction(Handle h,CFunction fn)
{
	lua_pushcfunction(h,fn);
}
inline Name PushString(Handle h,Name str)
{
	return lua_pushstring(h, str);
}
inline Name PushString(Handle h,Str str)
{
	return lua_pushstring(h, str.c_str());
}
inline void PushValue(Handle h,int index)
{
	lua_pushvalue(h,index);
}
inline void PushNumber(Handle h,double n)
{
	lua_pushnumber(h,n);
}
inline void PushInteger(Handle h,int num)
{
	lua_pushinteger(h,num);
}
inline double CheckNumber(Handle h,int index)
{
	return luaL_checknumber(h,index);
}
inline int CheckInteger(Handle h,int index)
{
	return luaL_checkinteger(h,index);
}
inline Str CheckString(Handle h,int index)
{
	return Str(luaL_checkstring(h,index));
}
inline void* CheckUserData(Handle h,int ud, Name tname)
{
	return luaL_checkudata(h, ud, tname);
}
inline double ToNumber(Handle h,int index)
{
	return lua_tonumber(h,index);
}
inline int UpValueIndex(int index)
{
	return lua_upvalueindex(index);
}
inline void Pop(Handle h,int num)
{
	lua_pop(h,num);
}
inline void SetTop(Handle h,int num)
{
	lua_settop(h,num);
}
inline int GetTop(Handle h)
{
	return lua_gettop(h);
}


//----------------------tools----------------------start
inline void PushVarToLua(Handle hLua,Int t)
{
	PushInteger(hLua,t);
}
inline void PushVarToLua(lua::Handle hLua,lua::Num t)
{
	lua::PushNumber(hLua,t);
}
inline void PushVarToLua(lua::Handle hLua,lua::Str t)
{
	lua::PushString(hLua,t);
}
inline void CheckVarFromLua(lua::Handle hLua,lua::Int *t,int i)
{
	*t=(lua::Int)lua::CheckInteger(hLua,i);
}
inline void CheckVarFromLua(lua::Handle hLua,lua::Num *t,int i)
{
	*t=(lua::Num)lua::CheckNumber(hLua,i);
}
inline void CheckVarFromLua(lua::Handle hLua,lua::Str *t,int i)
{
	*t=lua::CheckString(hLua,i);
}
//----------------------tools----------------------end


}//namespace lua

#endif//_LUA_HPP_
