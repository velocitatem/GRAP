# Custom Module Definition

This module is used for custom module definitions. It has 2 key actions:
- `declare`
- `export`
- `call`

By the nature of the graphic language, this module is not required to be used in order to create a program. However, it is useful for creating reusable code.

The way we define a module is by using the `declare` function. This function takes one argument: a module name. This function does not return any value.

Once we have a declared module, we can start linking/exporting code to it. This is done with the `export` function.
Yet again, this works like a stack, we procedurally add code to the module. This function takes one argument: a function object. This function does not return any value.

Finally, we can call the module with the `call` function. This function takes one argument: a module name. This function returns the value returned by the module.
## Usage

The module must be used with the following syntax:

```grap
module | declare | @module_name
module | export | (expression)
@module_name | call | ()
```

where:
- `module_name` is the name of the module to be declared
- `expression` is an expression to be added to the module such as `io | say | "Hello World"`
- `module_name` is the name of the module to be called
- `()` is the arguments to be passed to the module
- `@` is the prefix for the module name

# Example Code
+ [Basic Module](../demos/module.grap)