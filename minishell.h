/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 23:03:32 by rmerien           #+#    #+#             */
/*   Updated: 2019/04/02 16:57:07 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/syslimits.h>
# include <unistd.h>

typedef struct				s_env
{
	char					*name;
	char					*content;
	struct s_env			*next;
}							t_env;

typedef struct				s_line
{
	int						lenmal;
	int						pos;
	int						pos2;
	char					bslash;
	char					sub;
}							t_line;

/*
** Functions involved in receiving the command / making them into an arg list
*/

int							write_prompt(char tmp[PATH_MAX]);

/*
** Functions involved in receiving the command / executing it
*/

int							get_line(char **line);
t_line						ft_argsize(char *line, t_env *env);
int							ft_argcount(char *line);
t_line						fill_arg(char *line, t_env *env, char *to_fill);
int							ft_getargs(char ***argv, t_env *env);
int							execute_cmd(char **av, t_env *envir);
int							exe_file(char **ac, t_env *env);

/*
** Functions used to manipulate the env list
*/

int							split_env(t_env **env, char *const *strenv);
int							basic_env(t_env **env);
int							modify_var(t_env **env, char *name, char *content);
int							ft_addvar(t_env **env, char *name, char *content);
char						*find_content(t_env *env, char *content);
char						*search_path_var(char *file, char *path);

/*
** Functions dedicated to freeing variables.
*/

int							free_env(t_env *env);
int							free_tab(char **argv);

/*
** Built In Functions : cd ; echo ; exit ; env
*/

int							parser(t_env **env, char **av);

int							exe_cd(t_env *env, char **av);
int							exe_echo(t_env *env, char **av);
int							exe_env(t_env *env, char **av);
int							exe_setenv(t_env *env, char **av);
int							exe_unsetenv(t_env **env, char **av);
void						exe_exit(t_env *env, char **av);

/*
** Libft / aux functions
*/

int							free_all(t_env *env, char **av);
int							ft_uselessinit(int *c, int *a, char *b);
void						norme_v2(char **a, char *b);
void						norme_v3(char **a, char *b, int *c);
int							ft_insub(char c, char sub);
char						*ft_varname(char *str);
int							ft_atoi(const char *str);
int							ft_abs(int nb);
int							ft_arglen(char *line, int pos);
int							ft_arglen2(char *line, int pos);
int							ft_valid_bslash(char a, char c);
int							ft_strcmp(const char *s1, const char *s2);
char						*ft_strchr(const char *s, int c);
char						*ft_strcpy(char *dst, const char *src);
char						*ft_strjoin(char const *s1, char const *s2);
int							ft_strlen(const char *str);
int							ft_lentoc(const char *str, char c);
void						ft_strdel(char **as);
void						*ft_memalloc(size_t size);
void						ft_memdel(void **mem);
void						ft_putendl_fd(char *str, int fd);
char						*ft_strsub(char const *s,
									unsigned int start, size_t len);
char						*ft_strnew(size_t size);
char						*ft_strdup(const char *s1);
void						normeinit(int *a, int *b, int *c);
char						*ft_strcat(char *s1, const char *s2);

#endif
