#include <stdlib.h>
#include "fdf.h"

int	count_words(const char *s, char c) {
	int	count;
	int	in_substring;

    count = 0;
    in_substring = 0;
	while (*s) 
    {
		if (*s != c && in_substring == 0) 
        {
			in_substring = 1;
			count++;
		} else if (*s == c)
			in_substring = 0;
		s++;
	}
	return (count);
}

char	*word_dup(const char *s, int start, int finish) 
{
	char	*word;
	int		i;

	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (start < finish)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c) {
	char	**split;
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	start = -1;
	if (!s)
		return (NULL);
	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	while (s[i]) {
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || s[i + 1] == '\0') && start >= 0) {
			split[j++] = word_dup(s, start, i + (s[i] != c));
			start = -1;
		}
		i++;
	}
	if (start >= 0)
		split[j++] = word_dup(s, start, i);
	split[j] = NULL;
	return (split);
}