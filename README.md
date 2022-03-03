# minishell

Minishell is a project of the Unix branch at 42. It's a minimum viable version of a real shell. The main goal is to have a good understanding of process creation and file descriptor using the C programmming language.

## The minishell should:
* Display a **prompt** when waiting for a new command.
* Have a working **history**.
* Search and launch the right executable (based on the **PATH** variable or using a relative or an absolute path).
* Not interpret **\** (backslash) or **;** (semicolon).
* Interpret **'** and **"** like in bash
* Implement redirections (**<**, **>**, **<<** and **>>**)
* Implement **pipes** (**|** character)
* Implement environment variables (**$** followed by a sequence of characters)
* Implement **$?** (exit status code of the last command)
* Handle **ctrl-C**, **ctrl-D** and **ctrl-\\** which should behave like in bash.

## Builtins
* **echo** with option **-n**
* **cd** with only a relative or absolute path
* **pwd** with no options
* **export** with no options
* **unset** with no options
* **env** with no options or arguments
* **exit** with no options

## Compiling
> Run **```make```**

## Running
```
./build/minishell
```
