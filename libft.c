#include "pipex.h"

// https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901 pipex tutorial

size_t	ft_strlen(const char *str) {

	int i = 0;

	while (str[i])
		i++;

	return i;
}

void	ft_bzero(void *s, size_t n) {

	char *str = (char *)s;

	for (size_t i = 0; i < n; i++)
		str[i] = '\0';
}

void *ft_calloc(size_t number, size_t size) {

	void *memory = malloc(number * size);
	if (!(memory))
		return NULL;

	ft_bzero(memory, (number * size));

	return memory;
}

char *ft_substr(char const *s, unsigned int start, size_t len) {

	unsigned int i = 0;

	if (!s)
		return NULL;

	if ((start >= ft_strlen(s)) || (len == 0))
		return (ft_calloc(1, sizeof(char)));

	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;

	char *res = (char *)malloc(sizeof(char) * (len + 1));

	if (!(res))
		return NULL;

	while (i < len)
		res[i++] = s[start++];

	res[i] = '\0';

	return res;
}


static size_t ft_count_words(char const *s, char c) {

	size_t count = 0;

	while (*s) {

		while (*s == c)
			s++;
		if (*s != c && *s)
			count++;
		while (*s != c && *s)
			s++;
	}

	return count;
}

void ft_free_memory(char **memory) {

	for (int i = 0; memory[i]; i++) 
		free(memory[i]);

	free(memory);
}

size_t ft_word_len(const char *str, char c) {

	int	i = 0;

	while (*str == c)
		str++;

	while (*str && *str != c) {
		i++;
		str++;
	}

	return i;
}

char **ft_pre_split(char const *s, char c) {

	if (!s)
		return NULL;

	size_t i = ft_count_words(s, c);
	char **str = ft_calloc(i + 1, sizeof(char *));

	if (str == NULL)
		return NULL;

	size_t j = 0;
	while (i > j) {

		while (*s == c)
			s++;

		str[j] = ft_substr(s, 0, ft_word_len(s, c));

		if (str[j++] == NULL) {
			ft_free_memory(str);
			return NULL;
		}

		s += ft_word_len(s, c);
	}

	str[j] = NULL;

	return str;
}

char **ft_split(char const *s, char c) {

	if (!s)
		return NULL;

	char **str = ft_pre_split(s, c);

	if (!str)
		return NULL;

	return str;
}

/*..............................................................................................................*/

char *ft_strjoin(char const *s1, char c, char const *s2) {

	size_t i = 0, j = 0;

	int len = (ft_strlen(s1) + ft_strlen(s2) + 2);

	char *string = (char *)malloc(sizeof(char) * len);
	if (!string)
		return NULL;

	while (i < ft_strlen(s1)) {
		string[i] = s1[i];
		i++;
	}

	string[i++] = c;

	while (j < ft_strlen(s2)) {

		string[i++] = s2[j++];
	}

	string[i] = '\0';

	return string;
}

void free_array(char **array) {

	if (!array)
		return ;

	for (int i = 0; array[i]; i++)
		free(array[i++]);

	free(array);
}