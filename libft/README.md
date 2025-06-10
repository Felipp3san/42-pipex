# LIBFT

First project as a student at 42.\
I was asked to recode a few functions from the C standard library, as well as some other utility functions that I will use throughout the whole cursus.

## Getting Started

Run the command `make` to create the **libft.a** library file. See the example below:

```
git clone git@github.com:Felipp3san/42-libft.git libft
cd libft
make
```

In future projects, **libft** will be used by placing this folder inside your project's directory.\
The `libft.a` library will be compiled at the same time as the project by adding the following rule to your Makefile:

```
lbft:
    make -C libft/
```

And by adding the following flags to the compilation of your project's sources:

```
-I./libft/include -L./libft -lft
```

### Dependencies

- Requires `gcc` and `make` installed.
- Compatible with Linux and MacOS systems.

### Makefile Commands

- `make all`        : Creates *libft.a* from object files.
- `make clean`      : Removes all object files.
- `make fclean`     : Removes all object files and *libft.a*.
- `make bonus`      : Creates *libft.a* with bonus functions included.
- `make re`         : Equivalent to *make fclean* followed by *make*.

**Note:** Running `make` alone is equivalent to `make all`.

---

## Available Functions

### Characters - *char/*

- `ft_isalpha`     : Checks for an alphabetic character.
- `ft_isdigit`     : Checks for a digit (0 through 9).
- `ft_isalnum`     : Checks for an alphanumeric character.
- `ft_isascii`     : Checks whether 'c' is a 7-bit unsigned char value that fits into the ASCII character set.
- `ft_isprint`     : Checks for any printable character including space.
- `ft_islower`     : Checks for a lowercase letter.
- `ft_isupper`     : Checks for an uppercase letter.

### Conversions - *conv/*

- `ft_itoa`        : Converts an integer to a string.
- `ft_atoi`        : Converts the initial portion of the string pointed to by 'nptr' to int, ignoring leading whitespace and handling optional signs.
- `ft_toupper`     : Converts the letter 'c' to uppercase, if possible.
- `ft_tolower`     : Converts the letter 'c' to lowercase, if possible.

### Lists - *lst/*

- `ft_lstnew`       : Allocates and returns a new list element. The 'content' is initialized with the given value; 'next' is set to NULL.
- `ft_lstlast`      : Returns the last element of the list.
- `ft_lstmap`       : Iterates through 'lst', applies function 'f' to each content, and creates a new list with the results. If needed, 'del' is used to clean up.
- `ft_lstadd_front` : Adds the element 'new' at the beginning of the list.
- `ft_lstadd_back`  : Adds the element 'new' at the end of the list.
- `ft_lstdelone`    : Frees the memory of an element's content using 'del' and frees the element itself.
- `ft_lstclear`     : Deletes and frees an entire list, using 'del' on each element, then frees the list.
- `ft_lstiter`      : Iterates the list and applies function 'f' to the content of each element.
- `ft_lstsize`      : Counts the number of elements in a list.

### Memory - *mem/*

- `ft_bzero`      : Sets the first 'n' bytes of the area starting at 's' to zero (bytes containing char '\0').
- `ft_calloc`     : Allocates memory for an array of 'nelem' elements of size 'elsize' each and returns a pointer to the allocated memory. The memory is set to zero.
- `ft_memset`     : Fills the first 'n' bytes of the memory area pointed to by 's' with the constant byte 'c'.
- `ft_memcpy`     : Copies 'n' bytes from memory area 'src' to memory area 'dest'. The memory areas must not overlap.
- `ft_memccpy`    : Copies no more than 'n' bytes from memory area 'src' to memory area 'dest', stopping when the character 'c' is found.
- `ft_memmove`    : Copies 'n' bytes from memory area 'src' to memory area 'dest'. The memory areas may overlap.
- `ft_memchr`     : Scans the initial 'n' bytes of the memory area pointed to by 's' for the first instance of 'c'.
- `ft_memrchr`    : Searches backwards for the first instance of 'c' in the 'n' bytes pointed to by 's'.
- `ft_memcmp`     : Compares the first 'n' bytes of the memory areas 's1' and 's2'.

### Output - *put/*

- `ft_putchar_fd`   : Outputs the character 'c' to the given file descriptor.
- `ft_putstr_fd`    : Outputs the string 's' to the given file descriptor.
- `ft_putnstr_fd`   : Outputs up to 'len' characters of the string 's' to the given file descriptor.
- `ft_putendl_fd`   : Outputs the string 's' followed by a newline to the given file descriptor.
- `ft_putnbr_fd`    : Outputs the integer 'n' to the given file descriptor.

### Strings - *str/*

- `ft_strchr`     : Returns a pointer to the first occurrence of the character 'c' in the string 'str'.
- `ft_strrchr`    : Returns a pointer to the last occurrence of the character 'c' in the string 'str'.
- `ft_strnstr`    : Locates the first occurrence of the null-terminated string 'needle' in 'haystack', searching at most 'n' characters.
- `ft_strdup`     : Returns a pointer to a new string which is a duplicate of the string 's'.
- `ft_substr`     : Returns a substring from 's', starting at index 'start' and of maximum size 'len'.
- `ft_strjoin`    : Concatenates 's1' and 's2' into a new string.
- `ft_strtrim`    : Trims characters from 'set' from the beginning and end of 's1'.
- `ft_strmapi`    : Applies the function 'f' to each character of 's', returning a new resulting string.
- `ft_split`      : Splits 's' into an array of strings using 'c' as the delimiter.
- `ft_strlen`     : Calculates the length of the string 'str'.
- `ft_strnlen`    : Calculates the length of 's', up to a maximum of 'maxlen' bytes.
- `ft_strlcpy`    : Copies up to 'size - 1' characters from 'src' to 'dst', NUL-terminating the result.
- `ft_strlcat`    : Appends 'src' to string 'dst' of size 'size', guaranteeing NUL-termination.
- `ft_strncmp`    : Compares at most 'n' characters of 's1' and 's2'.

---

## Testing

The project was tested with a custom tester developed by me, as well as popular testing frameworks from other students:

- [libftTester](https://github.com/Tripouille/libftTester)
- [Libftest](https://github.com/jtoty/Libftest)
- [libft-unit-test](https://github.com/alelievr/libft-unit-test)

---

## Updating

The project is updated regularly with new functions that could be useful for other projects.

All modifications must comply with the [42 norm](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf).

---

## License

This project is for educational purposes at 42 School and follows their academic policies.
