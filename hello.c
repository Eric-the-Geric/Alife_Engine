#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

// Helper function to print a Lua table
void print_table(lua_State *L) {
    lua_pushnil(L);  // First key (nil to start iteration)
    while (lua_next(L, -2) != 0) {  // Pops the key, pushes the next key-value pair
        printf("%s: %s\n", lua_tostring(L, -2), lua_tostring(L, -1));
        lua_pop(L, 1);  // Remove value, keep key for next iteration
    }
}

int main() {
    // Create Lua state
    lua_State *L = luaL_newstate();
    if (!L) {
        printf("Error creating Lua state\n");
        return 1;
    }

    // Open standard libraries
    luaL_openlibs(L);

    // Load and run the Lua script
    if (luaL_dofile(L, "hello.lua") != LUA_OK) {
        printf("Error loading script: %s\n", lua_tostring(L, -1));
        lua_close(L);
        return 1;
    }

    // Call Lua function 1: greet(name)
    lua_getglobal(L, "greet");  // Push the function onto the stack
    lua_pushstring(L, "Alice"); // Push the argument onto the stack
    if (lua_pcall(L, 1, 1, 0) != LUA_OK) {  // Call with 1 argument, 1 return value
        printf("Error calling greet: %s\n", lua_tostring(L, -1));
    } else {
        printf("greet returned: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);  // Pop the return value
    }

    // Call Lua function 2: add(a, b)
    lua_getglobal(L, "add");
    lua_pushnumber(L, 10);  // Push first argument
    lua_pushnumber(L, 20);  // Push second argument
    if (lua_pcall(L, 2, 1, 0) != LUA_OK) {  // Call with 2 arguments, 1 return value
        printf("Error calling add: %s\n", lua_tostring(L, -1));
    } else {
        printf("add returned: %d\n", (int)lua_tonumber(L, -1));
        lua_pop(L, 1);  // Pop the return value
    }

    // Call Lua function 3: get_table()
    lua_getglobal(L, "get_table");
    if (lua_pcall(L, 0, 1, 0) != LUA_OK) {  // Call with 0 arguments, 1 return value
        printf("Error calling get_table: %s\n", lua_tostring(L, -1));
    } else {
        printf("get_table returned a table:\n");
        print_table(L);  // Print the table
        lua_pop(L, 1);  // Pop the table
    }

    // Call Lua function 4: modify_table(t)
    lua_getglobal(L, "modify_table");
    lua_newtable(L);  // Create a new table to pass to Lua
    lua_pushstring(L, "key");
    lua_pushstring(L, "value");
    lua_settable(L, -3);  // Add key-value pair to the table
    if (lua_pcall(L, 1, 1, 0) != LUA_OK) {  // Call with 1 argument, 1 return value
        printf("Error calling modify_table: %s\n", lua_tostring(L, -1));
    } else {
        printf("modify_table returned a modified table:\n");
        print_table(L);  // Print the modified table
        lua_pop(L, 1);  // Pop the table
    }

    // Cleanup
    lua_close(L);
    return 0;
}
