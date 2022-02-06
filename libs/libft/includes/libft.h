/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 22:55:27 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/06 10:28:07 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

//	~~	Includes ---------------------------------------------------------------

# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

//	~~	Defines ----------------------------------------------------------------

# define AND &&
# define OR ||
# define EOS '\0'

# define debug(x) print_debug(x, __LINE__, __FILE__)

# define RED "\033[1;31m"
# define PURPLE "\033[1;35m"
# define END "\033[0m"

//	~~	Enums ------------------------------------------------------------------

enum e_filedescriptor
{
	STDIN,
	STDOUT,
	STDERR,
};

enum e_state
{
	SUCCES,
	ERROR,
	MALLOC_ERROR,
};

//	~~	Typedefs ---------------------------------------------------------------

typedef struct s_list	t_list;

//	~~	Structures -------------------------------------------------------------

struct s_list
{
	void	*content;
	t_list	*next;
};

//	~~	Prototypes -------------------------------------------------------------

//	~	alloc.c ------------------------

/**
 * Allocates memory space and fill memory space with bytes of value zero.
 * @param count the number of consecutive elements in memory block
 * @param size the size (in bytes) of an element
 * @return if succesful, return a pointer to the allocated memory, otherwise
 * return NULL pointer
 */
void
*ft_calloc(int count, int size);

/**
 * Free memory space.
 * @param pointer the array which to be freed
 * @param size the size of array to free
 */
void
free_array(void **pointer, int size);

//	~	char.c -------------------------

/**
 * Check if the character passed in parameter is alpha-numeric or not.
 * @param character the character to test
 * @return true if the character is alpha-numeric character or false if the
 * character is not alpha-numeric character
 */
bool
ft_isalnum(int character);

/**
 * Check if the character passed in parameter is alphabethical or not.
 * @param character the character to test
 * @return true if the character is alphabethical character or false if the
 * character is not alphabethical character
 */
bool
ft_isalpha(int character);

/**
 * Check if the character passed in parameter is ascii character or not.
 * @param character the character to test
 * @return true if the character is ascii character or false if the character
 * is not ascii character
 */
bool
ft_isascii(int character);

/**
 * Check if the character passed in parameter is decimal or not.
 * @param character the character to test
 * @return true if the character is decimal character or false if the character
 * is not decimal character
 */
bool
ft_isdigit(int character);

/**
 * Check if the character passed in parameter is printable or not.
 * @param character the character to test
 * @return true if the character is printable character or false if the
 * character is not printable character
 */
bool
ft_isprintable(int character);

//	~	convert.c ----------------------

/**
 * Transform a string, representing an integer value, into a numerical value of
 * type int.
 * @param string the string to convert
 * @return if the string to convert does not contain an integer data, the value
 * 0 will be returned, otherwise, a value of type int equivalent to the string
 * passed in parameter
 */
int
ft_atoi(const char *string);

/**
 * Allows and returns a string of characters representing the integer received
 * in parameter, negative numbers must be handled.
 * @param number the integer to convert
 * @return the string representing the number passed in parameter, otherwise,
 * NULL is returned
 */
char
*ft_itoa(int number);

//	~	debug.c ------------------------

/**
 * Display a debug message.
 * @param value the message to display
 */
void
print_debug(char *value, int line, char *file);

//	~	error.c ------------------------

/**
 * Display the error message passed in parameter and exit with the status code
 * passed in parameter.
 * @param message the message to display
 * @param exit_status the status code to exit
 */
void
error(char *message, int exit_status);

//	~	fputs.c ------------------------

/**
 * Output the character passed in parameter to the given file descriptor.
 * @param filedescriptor the file descriptor on which to write
 * @param character the character to output
 */
void
fputchar(int filedescriptor, char character);

/**
 * Output the integer passed in parameter to the given file descriptor.
 * @param filedescriptor the file descriptor on which to write
 * @param number the number to output
 */
void
fputnbr(int filedescriptor, int number);

/**
 * Output the string passed in parameter to the given file descriptor.
 * @param filedescriptor the file descriptor on which to write
 * @param string the string to output
 */
void
fputstring(int filedescriptor, char *string);

//	~	join.c -------------------------

/**
 * Allocate and return a new string, which is result of the concatenation of
 * first_string and second_string.
 * @param first_string the prefix string
 * @param second_string the suffix string
 * @return if succesful, return the new string, otherwise return NULL pointer
 */
char
*ft_strjoin(const char *first_string, const char *second_string);

/**
 * Allocate and return a new string, which is result of the concatenation of
 * first_string and second_string and free the string which be determinated by
 * the number passed in parameter.
 * @param first_string the prefix string
 * @param second_string the suffix string
 * @return if succesful, return the new string, otherwise return NULL pointer
 */
char
*ft_strfjoin(const char *first_string, const char *second_string, int nfree);

//	~	list_clean.c -------------------

/**
 * Deletes and free the memory of the element passed in parameter, and of all
 * the elements that follow, using del and free; Finally the initial pointer
 * must to be set to NULL.
 * @param list the address of the pointer to an element
 * @param del the address of the function allowing to delete the content of an
 * element
 */
void
list_clear(t_list **list, void (*del)(void *));

/**
 * Free the memory of the element passed in parameter by using del function and
 * then with free; The memory of next must not be free.
 * @param list the element to free
 * @param del the address of the function allowing to delete the content of an
 * element
 */
void
list_delone(t_list *list, void (*del)(void *));

//	~	list_create.c ------------------

/**
 * Adds the element new to the end of the list.
 * @param list the address of the pointer to the first element of the list
 * @param new the address of the pointer to the element to add to the list
 */
void
list_add_back(t_list **list, t_list *new);

/**
 * Adds the element new to the beginning of the list.
 * @param list the address of the pointer to the first element of the list
 * @param new the address of the pointer to the element to add to the list
 */
void
list_add_front(t_list **list, t_list *new);

/**
 * Allocates and return a new element, content is initialized with the value
 * passed in parameter; The variable next is initialized to NULL.
 * @param content the content of the new element
 * @return the new element
 */
t_list
*list_new(void *content);

//	~	list_utils.c -------------------

/**
 * Return the last element of the list.
 * @param list the beginning of the list
 * @return last item in the list
 */
t_list
*list_last(t_list *list);

/**
 * Count the number of items in the list.
 * @param list the beginning of the list
 * @return the length of the list
 */
int
list_size(t_list *list);

//	~	maths.c ------------------------

/**
 * Check if the number passed in parameter is smaller than 0.
 * @param number the number to check if is negative
 * @return true if the number is negative, otherwise false
 */
bool
ft_isnegative(int number);

//	~	memory.c -----------------------

/**
 * Copies a block of memory specified by the source parameter, and whose size is
 * specified by the size parameter, to a new location designed to the
 * destination parameter.
 * @param destination the address of the memory block to receive the data
 * @param source the address of the memory block to duplicate
 * @param size the number of bytes to duplicate
 * @return the address of the destination memory block
 */
void
*ft_memcpy(void *destination, const void *source, int size);

/**
 * Copies a memory block specified by the source parameter to a new location
 * designated by the destination parameter, accepting that the two memory
 * areas may overlap.
 * @param destination the address of the memory block to receive the data
 * @param source the address of the memory block to duplicate
 * @param size the number of bytes to duplicate
 * @return the address of the destination memory block
 */
void
*ft_memmove(void *destination, const void *source, int size);

/**
 * Fills a memory area with a precise value.
 * @param buffer the address of memory block
 * @param character the value to use fill the memory block
 * @param length the number of bytes to initialize
 * @return the address of the re-initialized memory
 */
void
*ft_memset(void *buffer, int character, int length);

//	~	split.c ------------------------

/**
 * Allocate and returns an array of strings obtained by separating string with
 * the character charset, used as delimiter, the array must be terminated by NULL
 * @param string the string to be cut
 * @param charset the delimiting character
 * @return the array of new strings, resulting from the splitting, NULL if the
 * allocation failed
 */
char
**ft_split(const char *string, char charset);

//	~	strchr.c -----------------------

/**
 * Searches for the first occurrence of the character passed in parameter in the
 * string passed in parameter.
 * @param string the string which to search
 * @param character the desired character
 * @return if the searched character is present in the string, a pointer to the
 * first occurrence of the character will be returned, otherwise NULL is return
 */
char
*ft_strchr(const char *string, int character);

/**
 * Searches for the last occurrence of the character passed in parameter in the
 * string passed in parameter.
 * @param string the string which to search
 * @param character the desired character
 * @return if the searched character is present in the string, a pointer to the
 * last occurrence of the character will be returned, otherwise NULL is return
 */
char
*ft_strrchr(const char *string, int character);

//	~	strings.c ----------------------

/**
 * Calculates the length of the string passed in parameter.
 * @param string the string for which to calculate its length
 * @return the number of character found
 */
int
ft_strlen(const char *string);

/**
 * Duplicate the string passed in parameter.
 * @param string the address of the string to duplicate
 * @return if there enough memory to produce the new string, the function return
 * the address of the duplicated string, otherwise NULL is return
 */
char
*ft_strdup(const char *string);

//	~	strings_l.c --------------------

/**
 * Copy and concatenate strings, take the full size of the destination buffer
 * and guarantee NUL-terminaison if there is room.
 * @param destination the address of the string to which the content of the
 * other string should be concatenated
 * @param source the address of the string to concatenate
 * @param size the maximal number of character to concatenate
 * @return the address of the string resulting from concatenation
 */
int
ft_strlcat(char *destination, const char *source, int size);

/**
 * Copy and concatenate strings, take the full size of the destination buffer
 * and guarantee NUL-terminaison if there is room, copies up to size - 1
 * character from source to destination, NUL-terminating the result if size is
 * not 0.
 * @param destination the address of the string to which the content of the
 * other string should be concatenated
 * @param source the address of the string to concatenate
 * @param size the maximal number of character to concatenate
 * @return the address of the string resulting from concatenation
 */
int
ft_strlcpy(char *destination, const char *source, int size);

//	~	strings_n.c --------------------

/**
 * Compare two strings and know if the first string is inferior, equals or
 * superior to the second string.
 * @param first_string the first string to compare
 * @param second_string the second string to compare
 * @param size the maximal number of character to compare
 * @return if the two strings are equals, 0 is return, if the first string is
 * smaller than the second, a negative value is return, otherwise a positive
 * value is return
 */
int
ft_strncmp(const char *first_string, const char *second_string, int size);

/**
 * Duplicate the string passed in parameter where size is passed in parameter.
 * @param string the address of the string to duplicate
 * @return if there enough memory to produce the new string, the function return
 * the address of the duplicated string, otherwise NULL is return
 */
char
*ft_strndup(const char *string, int size);

/**
 * Locate the first occurrence of the NUL-terminated string to_find in the
 * string string, where not more than size characters are searched.
 * @param string the string in which to search
 * @param to_find the substring to search in string string
 * @param size the size of the string to be analyzed
 * @return if to_find is an empty string, string is returned; if to_find occurs
 * nowhere in string, NULL is returned; otherwise a pointer to the first
 * character of the first occurrence of to_find is returned
 */
char
*ft_strnstr(const char *string, const char *to_find, int size);

#endif
