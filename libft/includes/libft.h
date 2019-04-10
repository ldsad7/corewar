/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 13:01:05 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/31 14:00:21 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <wchar.h>

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_atoi(const char *str);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strdup(const char *src);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *str, const char *to_find);
char				*ft_strstr_to_find_zero(const char *str,
					const char *to_find);
char				*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isnumeric(char *arr);
int					ft_tolower(int c);
int					ft_toupper(int c);
size_t				ft_strlen(const char *str);

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(const char *s, char (*f)(char));
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int					ft_strequ(const char *s1, const char *s2);
int					ft_strnequ(const char *s1, const char *s2, size_t n);
char				*ft_strsub(const char *s, unsigned int start, size_t len);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strtrim(const char *s);
char				**ft_strsplit(const char *s, char c);
char				*ft_itoa(int n);
char				*ft_itoa_long(long long n);
char				*ft_itoa_base(long long n, int base);
void				ft_putchar(char c);
void				ft_putstr(const char *s);
void				ft_putendl(const char *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(const char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_swap(int *a, int *b);

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstreverse(t_list **lst);

double				ft_sqrt(int nb);
int					ft_sqrt_rational(int nb);
long int			ft_natural_pow(int base, int pow);
int					ft_isin(char *str, char *needle);
int					*ft_range(int min, int max);

# define BUFF_SIZE	1000

int					get_next_line(const int d, char **line);
char				*ft_str_append_char(char **str, char c);
char				*ft_str_append_str(char **str1, char **str2);
char				*ft_strchr_wo_zero(const char *s, int c);
int					ft_isnan(long double n);
int					ft_isinf(long double n);
int					ft_abs(long long n);
long long			ft_atoi_long(const char *str);

# define TRUE 1
# define FALSE 0
# define INT_SPECS "bdiouxX"
# define FLOAT_SPECS "aefg"
# define STR_CHR_SPECS "sc"
# define FLAGS "-+ #0"
# define ERR_BAD_SPEC -1
# define ERR_NO_SPEC -2

enum	e_size		{L_NONE, L_LB, L_HH, L_H, L_Z, L_LL, L_J, L_T, L_L};

typedef struct		s_format
{
	char			*curr_flags;
	int				width_value;
	int				prec_value;
	int				null_c_len;
	int				type_p;
	int				big_f;
	enum e_size		size;
	char			type;
	char			*str;
}					t_format;

extern va_list		g_ap;
extern t_format		*g_f;
extern int			g_count;

int					ft_printf(const char *format, ...);
int					ft_fprintf(int fd, const char *format, ...);
void				parse_print_format(char *format, int i, int fd);
int					parse_precision(const char *format_i);
int					parse_width(const char *format_i);
int					parse_size(const char *format_i);
int					parse_type(const char *format_i, int *spec_end);
int					parse_deprecated(const char *format_i, int *spec_end);
char				*make_size_string(char *str);
char				*ft_str_append_char(char **str, char c);
char				*ft_str_append_str(char **str1, char **str2);
t_format			*g_f_new(void);
void				make_str();
void				make_str_di(void);
void				make_str_boux(void);
void				make_str_aefg(void);
void				make_str_s(void);
void				make_str_c(void);
void				make_str_p(void);
char				*ft_itoa_base_unsigned(unsigned long long n, int base);
void				clear_all_exit(int option);
char				*convert_af(long double tmp, int base);
int					count_decimal_len(char *str);
void				wchar_to_char(char *buffer, int *offset, wchar_t c);
int					wchar_strlen(wchar_t *str);
int					wchar_strlen_symbols(wchar_t *str);
void				upper_lower_aefg(char **str);
void				apply_plus_space_aefg(char **str);
void				apply_zero_aefg(char **str);
char				*write_nan_inf(double tmp);
void				upper_lower_xp(char **str);
char				apply_prefix_boux(char **str, unsigned long long tmp);
void				apply_zero_boux(char **str);
void				fix_prefix_2_16_boux(char **str, char num_sys,
					int len_ini_tmp_str);
void				fix_prefix_16_p(char **str, int len_ini_tmp_str);
void				adjust_width_c_null(char **str);
void				adjust_width_s(char **str);
void				apply_zero_s(char **str);
void				apply_zero_di(char **str);
char				*make_string_from_char(char c);
int					wint_size(wint_t c);
int					check_exclusion_symbol(wint_t c);
int					check_exclusion_symbols(wchar_t *str);
char				*check_colors(char *format, int *i, int fd);
void				write_ordinary_symbols(char *format, int i, int fd);
char				*parse_colors(char *format, int ord, int fd);
int					apply_text_edit(char *format, int j, int ord, int fd);

/*
**			Цвет текста:
**	{black}		чёрный цвет знаков
**	{red}		красный цвет знаков
**	{green}		зелёный цвет знаков
**	{yellow}	желтый цвет знаков
**	{blue}		синий цвет знаков
**	{magenta}	фиолетовый цвет знаков
**	{cyan}		цвет морской волны знаков
**	{gray}		серый цвет знаков
**	{def}		возврат к дефолтным значениям
*/

# define BC_BLACK	"\033[0;30m"
# define BC_RED		"\033[0;31m"
# define BC_GREEN	"\033[0;32m"
# define BC_YELLOW	"\033[0;33m"
# define BC_BLUE	"\033[0;34m"
# define BC_MAGENTA	"\033[0;35m"
# define BC_CYAN	"\033[0;36m"
# define BC_GRAY	"\033[0;37m"
# define BC_DEFAULT	"\033[0m"

/*
**			Дополнительные свойства для текта:
**	{BOLD}			жирный шрифт (интенсивный цвет)
**	{NBOLD}			установить нормальную интенсивность
**	{UNDERLINE}		подчеркивание
**	{NUNDERLINE}	отменить подчеркивание
**	{BLINK}			мигающий
**	{NBLINK}		отменить мигание
**	{INVERSE}		реверсия (знаки приобретают цвет фона, а фон -- цвет знаков)
**	{NINVERSE}		отменить реверсию
**	{DEF}			возврат к дефолтным значениям
*/

# define BC_BOLD		"\033[1m"
# define BC_NBOLD		"\033[22m"
# define BC_UNDERLINE	"\033[4m"
# define BC_NUNDERLINE	"\033[4m"
# define BC_INVERSE		"\033[7m"
# define BC_NINVERSE	"\033[7m"
# define BC_BLINK       "\033[5m"
# define BC_NBLINK      "\033[5m"

/*
**			Цвет фона
**	Должен стоять либо один либо после цвета текста.
**	{BG_BLACK}		чёрный
**	{BG_RED}		красный
**	{BG_GREEN}		зелёный
**	{BG_BROWN}		коричневый
**	{BG_BLUE}		синий
**	{BG_MAGENTA}	фиолетовый
**	{BG_CYAN}		цвет морской волны знаков
**	{BG_GRAY}		серый
**	{BG_DEF}		возврат к дефолтным значениям
*/

# define BC_BG_BLACK	"\033[40m"
# define BC_BG_RED		"\033[41m"
# define BC_BG_GREEN	"\033[42m"
# define BC_BG_BROWN	"\033[43m"
# define BC_BG_BLUE		"\033[44m"
# define BC_BG_MAGENTA	"\033[45m"
# define BC_BG_CYAN		"\033[46m"
# define BC_BG_GRAY		"\033[47m"
# define BC_BG_DEFAULT	"\033[49m"

#endif
