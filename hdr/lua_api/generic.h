extern void LuaInitalize(void);
extern lua_State * L;


/*
Lua notes/considerations

There are eight basic types in Lua:
 nil,
  boolean,
   number,
    string,
     function,
      userdata,
       thread,
        and table.
The type nil has one single value, nil, whose main property is to be different from any other value; it often represents the absence of a useful value. The type boolean has two values, false and true. Both nil and false make a condition false; they are collectively called false values. Any other value makes a condition true.

Tables are passed by reference
Strings are immutable

L is passed to every function, its the Lua State

The arguments to the call are pushed in direct order; that is, the first argument is pushed first.

So when parsing arguments, walk up the stack from bot to top

A positive index represents an absolute stack position, starting at 1 as the bottom of the stack;

-1 is the top of the stack

It uses a stack system.
1 is bottom of stack
X is top of stack

-1 is also top of stack
-X is bottom of stack

You need to pop things off stack depending on which func you call.

I execute all lua scripts in sofplus/addons/lua directory on startup.


https://lucasklassmann.com/blog/2019-02-02-how-to-embeddeding-lua-in-c/

The loadfile returns a 'chunk' onto the stack.
A chunk is like a function , essentially.
You have to 'call' that chunk.. then all of the global names it defines will be created.
lua_pcall is popping its arguments off stack, if you eg pushed a function to it.
I'm clearing stack often with lua_settop(L,0).
You can find lua types in lua.h.  You can check for nil return, if the global name does not exist.

lua_pop - pops N elements frmo the stack


If your function does an operation on 1st argument.
Return a new copy because its more convenient for the lua
programmer to do eg.: x = func(bla,bla2) than
before = bla
func(bla,bla2)

Timing is a big issue when it comes to understanding integration with console.

The quake 2 console is parsed before the game frame..

sofplus uses Cbuf_AddText , for callbacks, so all action is happening at beginning of frame.
Thus with data from previous frame, ( 100 msec ago) 

To make lua functions be in sync with the sofplus functions, its important that it does not use
AddText, because it needs higher priority, (i think).
*/