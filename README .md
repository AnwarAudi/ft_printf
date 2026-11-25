*This project has been created as part of the 42 curriculum by aaudi.*

# ft_printf

## Description

**ft_printf** is a re-implementation of the C standard library function `printf`. The goal of the project is to learn how **variadic functions** work in C (`<stdarg.h>`) and to build a small, reusable formatted-output library, `libftprintf.a`, that can be linked into later 42 projects.

The function has the same prototype as the original:

```c
int	ft_printf(const char *format, ...);
```

It writes the formatted output to the standard output with `write` and returns the **number of characters printed**, or `-1` if a `write` call failed (just like `printf`).

### Supported conversions

| Specifier | Output                                                  |
|-----------|---------------------------------------------------------|
| `%c`      | a single character                                      |
| `%s`      | a string (`(null)` if the pointer is `NULL`)            |
| `%p`      | a `void *` in hexadecimal, prefixed with `0x` (`(nil)` if `NULL`) |
| `%d`      | a signed decimal integer                                |
| `%i`      | a signed decimal integer                                |
| `%u`      | an unsigned decimal integer                             |
| `%x`      | an unsigned integer in lowercase hexadecimal            |
| `%X`      | an unsigned integer in uppercase hexadecimal            |
| `%%`      | a literal `%`                                           |

Flags, field width and precision are **not** handled (they are not part of the mandatory part).

### Project structure

| File           | Content                                                                  |
|----------------|--------------------------------------------------------------------------|
| `ft_printf.c`  | `ft_printf`, `ft_handle_format` (walks the format string), `check_specfier` (picks the conversion) |
| `helpers.c`    | Output helpers: `ft_putchar`, `ft_putstr`, `ft_putnbr`, `ft_putnbr_un`, `ft_putnbr_hex`, `ft_putnbr_hex_ptr`, `ft_putptr`, and the counting helper `ret` |
| `helpers.h`    | Prototypes and the required includes                                     |
| `Makefile`     | Builds `libftprintf.a`                                                   |

## Instructions

### Compilation

The library is built with the project's Makefile (compiled with `cc -Wall -Wextra -Werror`):

```sh
make        # builds libftprintf.a
make clean  # removes the object files
make fclean # removes the object files and libftprintf.a
make re     # fclean + all
```

### Usage

Include the header in your code, then link against the library:

```c
#include "helpers.h"   /* or the header provided for the project */

int	main(void)
{
	int	n;

	n = ft_printf("Hello %s, you are %d years old (0x%x)\n", "Bob", 25, 25);
	ft_printf("printed %d characters\n", n);
	return (0);
}
```

```sh
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o demo
./demo
```

### Testing

The output and the return value can be compared with the real `printf` by running the same call with both functions and comparing what each one wrote. Compile with the sanitizers to catch memory errors:

```sh
cc -g -fsanitize=address,undefined -Wno-format main.c ft_printf.c helpers.c -o test
./test
```

Useful edge cases to check: `INT_MIN`, `UINT_MAX`, `NULL` for `%s` and `%p`, `%%`, a `%` at the very end of the format string, and a failing output (`./test > /dev/full`, where every call must return `-1`).

## Algorithm and data structures

### Overview

`ft_printf` does a **single left-to-right pass** over the format string. There is no intermediate buffer and no dynamic allocation: every character is sent to the standard output as soon as it is known.

1. `ft_printf` starts the argument list (`va_start`), calls `ft_handle_format`, then ends it (`va_end`).
2. `ft_handle_format` reads the string with an index `i`:
   - a normal character is printed directly;
   - a `%` followed by the end of the string stops the loop (the real `printf` has undefined behavior here; stopping is the safe choice);
   - otherwise the character after `%` is given to `check_specfier`, and `i` skips both characters.
3. `check_specfier` is an `if / else if` chain over the specifier. Each branch reads the next argument with `va_arg` using the **correct type** (`int` for `%c`, `%d`, `%i`; `char *` for `%s`; `void *` for `%p`; `unsigned int` for `%u`, `%x`, `%X`) and calls the matching output function. `%%` prints a single `%`.

### Printing numbers: recursion instead of a buffer

To print a number in a given base, the digits must come out **most significant first**, but `n % base` produces them least significant first. The functions solve this with recursion:

```
print(n):
    if n >= base:
        print(n / base)      // higher digits first
    write(digit_table[n % base])
```

The digit is read from a lookup string (`"0123456789"`, `"0123456789abcdef"`, `"0123456789ABCDEF"`), so there is no `if (digit < 10)` branching and the case of `%x` / `%X` is just a different table.

**Why recursion?** The alternative is to fill a local array backwards and then print it, or to build a string with `malloc` (like an `itoa`). Recursion needs no buffer, no size computation and no `malloc` (so no allocation failure to handle). The recursion depth is tiny and bounded: at most 10 calls for a decimal `unsigned int`, 8 for a hexadecimal `unsigned int`, and 16 for a pointer.

### Special cases

- **`INT_MIN`**: `-n` overflows for `-2147483648`, so this value is printed as a fixed string. Every other negative number is printed as `-` followed by its absolute value.
- **Pointers**: a pointer does not fit in an `unsigned int` on a 64-bit system, so `%p` uses a separate function (`ft_putnbr_hex_ptr`) that takes an `unsigned long`. A `NULL` pointer prints `(nil)`, which is what the GNU libc does on Linux.
- **`NULL` string**: `%s` with a `NULL` pointer prints `(null)`.
- **Unknown specifier** (for example `%y`): nothing is printed for it and it counts for 0 characters.

### Counting characters and handling `write` errors

Every output function returns **the number of characters it printed, or `-1` on error**. The total is accumulated with a small helper:

```c
void	ret(int *counter, int r)
{
	if (*counter == -1)
		return ;
	if (r == -1)
	{
		*counter = -1;
		return ;
	}
	*counter = *counter + r;
}
```

Once the counter is `-1` it stays `-1`, so a single failed `write` anywhere (even deep inside a recursive call) is passed up unchanged to the return value of `ft_printf`, matching the behavior of the real `printf`. A pointer to the counter is used so the helper can modify the caller's variable.

### Data structures: why none are needed

The state of the algorithm is just an index, a counter and the argument cursor, so no data structure is needed (no list, array of results or buffer). The only structure in play is the `va_list`, which is **passed by pointer** (`va_list *args`) to the helper functions. This matters: the list works as a cursor that moves forward each time `va_arg` is called, and passing it by value to a helper would leave the caller's cursor in its old position (and is undefined behavior if the value is used again afterwards).

### Choices and limitations

| Choice | Reason | Trade-off |
|--------|--------|-----------|
| `if / else if` chain in `check_specfier` | Only 9 specifiers: it is short and very readable | An array of function pointers would scale better if many specifiers were added |
| Recursive number printing | No buffer, no `malloc`, no size computation | Uses a little stack (bounded to at most 16 calls) |
| Lookup strings for digits | No branching on `digit < 10`, same code for `x` and `X` | None worth mentioning |
| One `write` per character | Simple and always correct, nothing to flush | More system calls than a buffered implementation; a buffer flushed at the end would be faster for large outputs |
| Return value `-1` on error | Same contract as `printf`, errors are not hidden | Requires checking results in every function |

## Resources

### References

- `man 3 printf` – behavior and conversion specifiers of the function being re-implemented.
- `man 3 stdarg` – `va_list`, `va_start`, `va_arg`, `va_end`.
- `man 2 write` – the system call used for all output, and its return values.
- [cppreference – `printf`, `fprintf`](https://en.cppreference.com/w/c/io/fprintf) – detailed description of the format specifiers.
- [cppreference – Variadic arguments](https://en.cppreference.com/w/c/variadic) – how variadic functions work in C.
- [GNU C Library manual – Variadic Functions](https://www.gnu.org/software/libc/manual/html_node/Variadic-Functions.html) – how to define and call functions with a variable number of arguments.
- ISO/IEC 9899 (the C standard) – sections on variable arguments (`<stdarg.h>`) and formatted output.

### Use of AI

AI (Claude) was used as a **reviewing and testing assistant**, not to replace understanding the project. Specifically:

- **Code review and debugging**: finding compile errors (include guard typo, missing prototypes, a call to a function that did not exist), an uninitialized counter, an out-of-bounds read when the format string ends with `%`, and an infinite loop on `%%`.
- **Test program**: writing a test `main` that runs `ft_printf` and the real `printf` with the same arguments and compares both the output and the return value, and checks that every call returns `-1` when the output fails.
- **Error handling design**: discussing how to detect and propagate a failing `write`, which led to the `ret` counting helper.
- **README**: drafting this document from the project's code.

All suggestions were read, compiled and tested before being adopted, and every function in the project can be explained by its author.
