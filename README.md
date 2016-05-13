# luapp

It's a simple tool for lua.
To help you using lua in C++ style.

Tested

-   Linux + CMake + GNU Make + GCC4.9, :smile:
-   Windows + CMake + Visual Studio 2010

---

-   [lua](lua/CMakeLists.txt)

    这部分把 lua 源码（C）生成了静态链接库。

    ```cmake
    set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})  # 这个配置
    add_library(lua STATIC ${SOURCE})               # 会影响到这个 library 的安装
    ```

    使用的时候，link 它就可以了。（不要忘了加头文件。）

    ```cmake
    target_link_libraries(${NAME} ${LUAPP_LIBRARY_NAME})
    ```

-   [examples/HelloWorld](examples/HelloWorld/HelloWorld.cpp)

    设置脚本路径，载入脚本文件，运行。

    不获取运行结果，也不返回运行输出，只是输出到 stdout。

-   [examples/FunctionIntoLua](examples/FunctionIntoLua/FunctionIntoLua.cpp)

    lua 脚本调用 c++ 里的函数。

    ```cpp
    // 把 lua 脚本中的 NumberPlus 绑定到 MyFunction 这个函数
	lua.RegisterFunction("NumberPlus",&MyFunction);   // Lua script has MyFunction() now.

    // 运行它，因为 lua 不是 type strict，所以不用在“声明”的时候指定 Lua::Int 什么的。
    // 这个 Lua::Int 其实就是 int 的 typedef。
	lua.DoScript("FunctionIntoLua.lua");
    ```

-   [examples/CallFunctionFromLua](examples/CallFunctionFromLua/CallFunctionFromLua.cpp)

    调用 lua 脚本里定义的函数。

    ```cpp
    // 定义一个函数声明（C++ 里必须有 strict 的输入输出）
    lua::Function<Int(Int,Int,Int)>   func;

    // 注册它
    lua.GetFunction("func",&func);

    // 运行，调用的其实是 lua 里的 func 函数，返回一个 int
    printf("Return value is %d\n",func(1,2,3));
    ```

-   [examples/callMultipleReturnValueFunctionFromLua](examples/callMultipleReturnValueFunctionFromLua/callMultipleReturnValueFunctionFromLua.cpp)

    lua 支持多个返回值（当然你也可以看成一个），c++ 不支持，所以把返回值直接传进去。

    ```cpp
    // 因为 using 了 lua::Int 就不用再麻烦得用 Lua::Int 了。
    // 这里定义一个 C++ 函数。
    lua::FunctionExt<void(Int,Int,Int),void(void)> func;

    // 这个函数从 lua 脚本里来。
    lua.GetFunction("func",&func);

    int x,y,z;

    // 从 lua 脚本获取返回值。
    func(&x,&y,&z);
    ```

    我在想，这个 lua 函数需要输入怎么半……

-   [examples/ClassIntoLua](examples/ClassIntoLua/ClassIntoLua.cpp)

    ```cpp
    // 把 C++ 的类注册到 lua
    lua.RegisterClass<MyClass>("MyClass");                 // Lua script has class now.
    // 还有它的类成员
    lua.RegisterMemberFunction("Count",&MyClass::Count);   // Lua script has member function now.

    // 外，上面两句话可以交换顺序

    // 运行程序，获取 DoScript 有返回值。
    if( ! lua.DoScript("ClassIntoLua.lua") ) {
        std::cout<<lua.GetError()<<std::endl;
    }
    ```

-   [examples/GetGlobalVariable](examples/GetGlobalVariable/GetGlobalVariable.cpp)

    从 lua 脚本中获取变量。

    ```cpp
    // 在 C++ 里，它是 std::string
	lua::Str power;

    // 在 lua 里，它是 lua_power，泛型
	lua.GetGlobal("lua_power",&power);

    // 因为已经执行完了 lua 脚本，lua 实例里的值已经拿到了 power 里
    // （即上面的 GetGlobal）
	printf("Power was turn %s\n",power.c_str());
    ```

-   [examples/MemberFunctionIntoLua](examples/MemberFunctionIntoLua/MemberFunctionIntoLua.cpp)

    lua 调用 c++ 函数。

    ```lua
    num = PrintMyWord("good")
    print("Return value is " .. num)
    ```

    这个脚本绑定到的是一个具体的实例。

    ```cpp
    lua.RegisterFunction("PrintMyWord",&MyClass::Count2,&myClass);
    ```

-   [examples/MultipleLuaFile](examples/MultipleLuaFile/MultipleLuaFile.cpp)

    ```lua
    local std = require "std"

    function func(a, b, c)
        local   x=std.sum(a,b,c)
        print( a .. "+" .. b .. "+" .. c .. "=" .. x)
        return x
    end
    ```

    ```cpp
    // 输入是 int，int，int，输出是 int
	lua::Function<Int(Int,Int,Int)> func;

	lua.GetFunction("func",&func);

	printf("Return value is %d\n",func(1,2,3));
    ```

---

### Features

- [x] Header file only.
- [x] To register the class from C++ into lua.
- [x] To register the global function or member function from C++ into lua.
- [x] Read/Add global variable of lua script from C++.
- [x] Call global function of lua script from C++.
- [ ] Create lua module support.
- [ ] Let lua script embedded in C++.
- [ ] Design a C++ container to simulate lua table.

### Version

1.0.0

### Example

```lua
-- ClassIntoLua.lua

object = MyClass()

num = object:Count(3,4)

print("3 + 4 = " .. num)
```

```c++
// main.cpp

#include "luapp.hpp"

class MyClass
{
public:

    MyClass()
    {
        printf("do MyClass::MyClass()\n");
    }

    ~MyClass()
    {
        printf("do MyClass::~MyClass()\n");
    }

    lua::Int Count( lua::Int num01,
                    lua::Int num02)
    {
        return num01+num02;
    }
};

int main()
{
    lua::State<>    lua;

    lua.Init();

    lua.RegisterMemberFunction("Count",&MyClass::Count);

    lua.RegisterClassEx<MyClass>("MyClass");

    lua.DoScript("ClassIntoLua.lua");

    return 0;
}
```
