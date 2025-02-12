function hello()
    print("Hello from Lua!")
    return 42  -- Return a value to C
end
--
-- Function 1: Simple greeting
function greet(name)
    print("Hello, " .. name .. " from Lua!")
    return "Greeting successful"
end

-- Function 2: Add two numbers
function add(a, b)
    return a + b
end

-- Function 3: Return a table
function get_table()
    return { name = "Lua", version = "5.3", message = "Hello from a table!" }
end

-- Function 4: Modify a table passed from C
function modify_table(t)
    t.modified = true
    return t
end
