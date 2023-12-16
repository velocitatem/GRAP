# GRAP Language Snippets

## Bits Operations (`bits.grap`)

This snippet illustrates how to work with binary data.

```grapmem | save | (bin | "a" | "101")
io | say | (mem | get | "a")
io | say | (bits | > | (mem | get | "a"))
```

Here, a binary number "101" is saved to a variable "a", and then it's retrieved and displayed. Additionally, a bit shift operation is performed on "a".
Chain Variable Declaration (chain.grap)

Demonstrating simple variable storage and retrieval.

```grap
mem | save | (var | "pi" | "3.14")
io | say | (mem | get | "pi")
```
The variable "pi" is set with the value "3.14" and then outputted to the user.
Hello World Example (helloworld.grap)

A basic example that shows variable assignment and output.

```grap
mem | save | (var | "pi"    | "3.14")
mem | save | (var | "greet" | "hello")
io  | say  | "PI is equal to:"
io | say | (mem | get | "pi")
io  | say  | "A greeting is:"
io | say | (mem | get | "greet")
io  | say  | "That is it for today! Goodbye!"
```
Defines "pi" and "greet" variables and prints them along with custom messages.
User Input Example (input.grap)

Illustrates how to ask for and store user input.

```grap
mem | save | (var | "name" | (io | ask | "What is your name?"))
io | say | "Your name is:"
io | say | (mem | get | "name")
```
Asks the user for their name and then outputs it.
List Operations (list.grap)

Shows how to manipulate lists.

```grap
mem | set | (list | "lst" | "A")
mem | set | (list | "lst" | "C")
mem | set | (list | "lst" | "D")
mem | set | (list | "lst" | "E")
io | say | (mem | get | "lst")
```
Creates a list "lst" and adds several elements to it, then prints the list.
Mathematical Operations (math.grap)

A snippet to perform and display mathematical calculations.

```grap
mem | save | (int | "s1" | "10")
mem | save | (int | "s2" | "10")
mem | save | (int | "S" | (
    math | mul | "10 20"
))
io | say | "The computed product is:"
io | say | (mem | get | "S")
```
Saves two integers and calculates their product, then outputs the result.
Module Declaration and Usage (module.grap)

Details how to declare a module and use its exported functionalities.

```grap
module | declare | @sayhello
module | export | (
    mem | save | (
        var | "pi" | "3.14338"
        )
    )
module | export | (
    io | say | "This is inside the function"
)
module | export | (
    io | say | (
        mem | get | "pi"
        )
    )
io | say | "This is a regular call"
@sayhello | call | ()
```
Declares a module @sayhello with several exports and demonstrates calling the module.
String Concatenation and Arithmetic (str.grap)

Shows string concatenation followed by an arithmetic operation on those strings.

```grap
mem | save | (var | "a" | (io | ask | "Enter a number: "))
str | concadd | (mem | get | "a")
mem | save | (var | "b" | (io | ask | "Enter a number: "))
str | concadd | " "
str | concadd | (mem | get | "b")
mem | save | (int | "S" | (math | mul | (str | concat | "")))
str | concadd | "The product of "
str | concadd | (mem | get | "a")
str | concadd | " and "
str | concadd | (mem | get | "b")
str | concadd | " is "
str | concadd | (mem | get | "S")
mem | save | (var | "str" | (str | concat | ""))
io | say | (mem | get | "str")
```

