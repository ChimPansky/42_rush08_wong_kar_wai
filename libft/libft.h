/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:40:07 by tkasbari          #+#    #+#             */
/*   Updated: 2024/03/08 18:37:19 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// this is used in cub3d

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/types.h>

# ifndef SUCCESS
#  define SUCCESS 0
# endif

# ifndef FAILURE
#  define FAILURE 1
# endif

// Helper Functions
int		ft_isspace(char c);
size_t	ft_strlen(const char	*s);

// Mandatory Part I - Libc Functions
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	*ft_memset(void	*s, int c, size_t n);
void	ft_bzero(void	*s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memrchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_itoa(int n);

// Mandatory Part II - Additional Functions:
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
ssize_t	ft_putchar_fd(char c, int fd);
ssize_t	ft_putstr_fd(char *s, int fd);
ssize_t	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// Libft Bonus:
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// Libft Various Additions:
void	*ft_print_memory_width(void *addr, size_t size, size_t wdth);
void	*ft_print_memory(void *addr, size_t size);
int		ft_str_isnum(char *c);
int		ft_str_isint(char *c, int *target);
size_t	ft_str_chr_replace(char *s, char old_c, char new_c);
int		ft_abs(int x);
int		ft_max(int a, int b);
void	ft_free_and_null(void **ptr);
char	*ft_file_get_extension(char *file_path);
bool	ft_file_check_extension(char *file_path, char *ext);
void	ft_free_splitted(char **splitted);

// Libft Additions for Printf:
size_t	ft_get_int_order_base(size_t nb, size_t base_len);
char	*ft_itoa_base_signed(int n, char *base);
char	*ft_itoa_base_unsigned(size_t n, char *base);
char	*ft_strreplicate(char c, size_t len);
char	*ft_strlpad(char *src, char padding, size_t target_size, bool free_src);
char	*ft_strlpad_free(char *s, char cpad, size_t target_size, int to_free);
char	*ft_strrpad(char *src, char padding, size_t target_size, bool free_src);
char	*ft_strjoin_free(char *s1, char *s2, bool free_s1, bool free_s2);
char	*ft_substr_free(char *s, unsigned int start, size_t len, int to_free);
int		ft_iif_int(int condition, int true_val, int false_val);
void	*ft_iif_ptr(int condition, void *true_val, void *false_val);
void	*ft_iif_ptr_f(int cond, char *(*f)(char const *), void *v1, void *v2);
bool	ft_string_is_empty(char *string);

// Printf Additions (Put into separate header?)
# define S_FLAGS "#0- +"
# define S_CONVERSIONS "csdiupxX"
# define S_BASE_U "0123456789"
# define S_BASE_HEX "0123456789abcdef"
# define S_BASE_HEXL "0123456789ABCDEF"

enum e_flags
{
	F_HASH = 1,
	F_ZERO = 2,
	F_MINUS = 4,
	F_SPACE = 8,
	F_PLUS = 16,
	F_PRECISION = 32,
	F_MIN_WIDTH = 64
};

typedef struct s_format
{
	int		flags;
	size_t	width;
	int		prec;
	char	type;
}			t_format;

int		ft_printf(const char *format, ...);
int		ft_dprintf(int fd, const char *format, ...);
int		ft_vdprintf(int fd, const char *format, va_list args);
int		output_percent(int fd, const char **format);
int		output_conversion(int fd, t_format conf, va_list args);
int		output_c(int fd, t_format conf, va_list args);
int		output_regular(int fd, const char **format);
int		set_config(const char **format, t_format *conf);
char	*convert_diuxxp(char conv, va_list args);
char	*manipulate_s(char	*s, t_format conf);
char	*add_prefix(char *s, char *pre);
char	*pad_negative(char *s, char cpad, size_t width, int to_free);
char	*apply_precision_s(char *s, int prec);

// Get Next Line Additions (put in separate header?):
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 65
# endif

# ifndef MAX_FDS
#  define MAX_FDS 1024
# endif

typedef struct s_buffer
{
	char	str[BUFFER_SIZE + 1];
	int		error;
	ssize_t	len;
	ssize_t	last_read;
}				t_buffer;

typedef struct s_line
{
	char	*str;
	int		error;
	ssize_t	len;
}				t_line;

t_line	get_next_line(int fd);

// string and charptrarray additions:
# define T_STRING_INIT_CAPACITY 5
# define STR_ARR_INIT_CAP 8

typedef struct s_string
{
	char	*buf;
	size_t	len;
	size_t	capacity;
}		t_string;

int		string_init(t_string *string, char *str);
int		string_init_fixed_cap(t_string *string, size_t init_capacity);
void	string_init_with_allocated(t_string *string, char *allocated);
int		string_add_str(t_string *string, const char *appendix);
int		string_add_chr(t_string *string, char appendix);
void	string_destroy(t_string *string);

typedef struct s_charptr_array
{
	char	**buf;
	size_t	sz;
	size_t	cap;
}		t_charptr_array;

int		charptr_array_init(t_charptr_array *arr);
int		charptr_array_add_allocated_str(t_charptr_array *arr, char **str);
int		charptr_array_dup_and_add_str(t_charptr_array *arr, const char *str);
void	charptr_array_destroy(t_charptr_array *arr);
void	charptr_array_print(t_charptr_array *arr);

#endif
