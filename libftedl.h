/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftedl.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <mabayle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:40:49 by frameton          #+#    #+#             */
/*   Updated: 2020/02/17 02:40:06 by frameton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTEDL_H
# define LIBFTEDL_H
# define FRED "\033[0;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[0;m"
# define BGREEN "\033[0;30;42m"
# define BCYAN "\033[0;30;46m"
# define BYELLOW "\033[0;30;43m"

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strncpy1(char *dest, const char *src, size_t len);
char				*ft_mstrcpy(char *dest, const char *src);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strclr2(char *s);
char				*ft_strchr(const char *s, int c);
char				*ft_strcat(char *s1, const char *s2);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memmove(void *dst, const void *src, size_t len);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
int					ft_isprint(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isalpha(int c);
void				free_dchar(char ***tab);
void				ft_2eputendl(char *s1, char *s2);
int					ft_isalnum(int c);
void				ft_2eputstr(char *s1, char *s2);
void				ft_bzero(void *s, size_t n);
int					ft_atoi(const char *str);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_fputstr(char **s);
int					ft_ptchar(int c);
void				ft_fputendl(char **s);
void				ft_fputstr_s(char **s);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putstr_s(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memicpy(void *dst, const void *src, size_t n);
char				*ft_strmap(char const *s, char (*f)(char));
size_t				ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_pstrback(char *str);
char				*ft_pstrfront(char *str);
char				*ft_rwspaces(char *str);
char				*ft_pbackws(char *str);
void				ft_2putstr_fd(char const *s, char const *s2, int fd);
char				*ft_pfrontws(char *str);
int					ft_ipbackws(char *str);
int					ft_ipfrontws(char *str);
char				*ft_istrcpy(char *dest, const char *src);
int					ft_nbword(char *str);
int					ft_nbcword(char *s, char c);
int					ft_ipfrontc(char *str, char c);
int					ft_ipbackc(char *str, char c);
void				ft_eputendl_fd(char const *s, int fd);
void				ft_2eputendl_fd(char *s1, char *s2, int fd);
char				*ft_pfrontc(char *str, char c);
char				*ft_pbackc(char *str, char c);
int					ft_nci(int n);
int					ft_ncl(long long n);
void				free_char(char **s);
void				ft_eputendl(char const *s);
char				*ft_ltoa(long long n);
char				*ft_strev(char *s);
void				ft_cswap(char *a, char *b);
void				ft_eputstr(char const *s);
void				ft_e2putstr(char const *s, char const *s2);
void				ft_swap(int *a, int *b);
void				ft_2putstr(char const *s, char const *s2);
char				**ft_splitws(char const *s);
struct s_list		*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(struct s_list **alst,
		void (*del)(void *, size_t));
void				ft_lstdel(struct s_list **alst,
		void (*del)(void *, size_t));
void				ft_lstadd(struct s_list **alst, struct s_list *new);
void				ft_lstiter(struct s_list *lst,
		void (*f)(struct s_list *elem));
int					ft_lstsize(struct s_list *lst);
void				ft_putlstfront(struct s_list **lst);
void				ft_putlstback(struct s_list **lst);
int					check_whitespaces(char c);
void				putendl_dchar(char **s);
char				**ft_sstrev(char **s, int c);
struct s_list		*ft_lstmap(struct s_list *lst,
		struct s_list *(*f)(struct s_list *elem));
void				ft_mputstr(char const *s, int m);
void				ft_mputendl(char const *s, int m);
void				ft_marge(int m);
int					ft_isnum(int c);
#endif
