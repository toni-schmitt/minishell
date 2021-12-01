/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 17:23:59 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/01 11:41:44 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* INCLUDES */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdbool.h>

/* LIST */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *list);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* INPUT / OUTPUT */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int nbr, int fd);
int		ft_printf(const char *format, ...);
int		ft_putlnbr(long nbr);
int		ft_putnbr(int nbr);
int		ft_putstr(const char *str);
int		ft_putchar(char c);
int		ft_putptr(void *ptr);
int		ft_putunbr(unsigned int nbr);
int		ft_putlhex(unsigned long long nbr);
int		ft_putuhex(unsigned long long nbr);
int		ft_puterror(char *message);
int		putstderr(char *error_message);

/* MEMORY */
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/* READ / WRITE */
char	*get_next_line(int fd);
int		ft_get_line_count(char *path);

/* STRING */
int		ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *s, const char *to_find, size_t n);
char	*ft_strstr(const char *s, const char *to_find);
int		ft_strhas(char *str, char *set);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_issign(char c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(const char *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strdup(const char *str);
char	*ft_strndup(char *str, size_t n);
char	*ft_append(char **dst, char *src);
char	*ft_htoa(unsigned long long dec, int uppercase);
char	*ft_itoa(int nbr);
char	*ft_getlongeststr(char **array);
int		ft_chrcount(const char *str, char ch);
char	**ft_split_set(char *str, char *set);
char	*ft_strset(char *str, char *set);
char	**ft_str_arr_dup(char **arr);
int		ft_str_arr_len(char **arr);
char	*ft_realloc_str(char *str, int size);
char	**ft_realloc_str_arr(char **arr, int size);
char	*ft_strstrjoin(char *s1, char *s2, char *divider);
int		ft_strclen(char *str, char c);
char	*ft_append_len_div(char **dst, char *src, int len, char *div);
char	*ft_in_front_div(char **dst, char *src, char *div);
char	**ft_str_arr_realloc(char *array[], size_t size);
char	**ft_add_single_str(char ***arr, int pos, char *new);

/* UTILS */
int		ft_hexnbrlen(unsigned long long nbr);
int		ft_nbrlen(long nbr);
void	*ft_free_split(char **split);
void	*ft_free(void **p);
void	ft_free_str(char **str);
void	ft_free_str_array(char ***str);
void	ft_free_single_str(char ***arr, int i);

#endif