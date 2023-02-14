#include "pipex.h"

void ft_bzero(void *s, size_t n)
{

	char *string = (char *)s;

	for (size_t i = 0; i < n; i++)
		string[i] = '\0';
}

void *ft_calloc(size_t n, size_t size)
{

	void *res = malloc(size * n);

	if (!res)
		return NULL;

	ft_bzero(res, size * n);

	return res;
}

size_t ft_strlen(const char *str)
{

	size_t len = 0;

	while (str[len])
		len++;

	return len;
}

char *ft_substr(char const *s, unsigned int start, size_t len)
{

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

static size_t ft_count_words(char const *str, char c)
{

	size_t words = 0, i = 0;

	while (str[i])
	{

		while (str[i] == c)
			i++;

		if (str[i] != c && str[i] != '\0')
			words++;

		while (str[i] != c && str[i] != '\0')
			i++;
	}

	return words;
}

static size_t ft_counts_len_word(char const *str, char c)
{

	size_t count = 0, i = 0;

	while (str[i] == c)
		i++;

	while (str[i] != c && str[i] != '\0')
	{
		count++;
		i++;
	}

	return count;
}

static void ft_free_memory(char **array)
{

	for (size_t i = 0; array[i]; i++)
		free(array[i]);

	free(array);
}

char **ft_split(char const *s, char c)
{

	size_t i = 0;

	if (!s)
		return (NULL);

	size_t words = ft_count_words((char *)s, c);

	char **array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);

	while (i < words)
	{

		while (*s == c)
			s++;

		array[i] = ft_substr(s, 0, ft_counts_len_word(s, c));

		if (!array[i++])
		{
			ft_free_memory(array);
			return NULL;
		}

		s += ft_counts_len_word(s, c);
	}

	array[i] = NULL;
	return array;
}

/*..............................................................................................................*/

char *ft_strjoin(char const *s1, char c, char const *s2)
{

	size_t i = 0, j = 0;

	int len = (ft_strlen(s1) + ft_strlen(s2) + 2);
	char *string = (char *)malloc(sizeof(char) * len);

	if (!string)
		return 0;

	while (i < ft_strlen(s1))
	{
		string[i] = s1[i];
		i++;
	}

	string[i++] = c;

	while (j < ft_strlen(s2))
		string[i++] = s2[j++];

	string[i] = '\0';
	return (string);
}

void free_array(char **array)
{

	if (!array)
		return;

	for (int i = 0; array[i]; i++)
		free(array[i]);

	free(array);
}