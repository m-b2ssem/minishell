#include <stdio.h>
#include <stdlib.h>


int	main(void)
{
	char	*original;
	char	*result;

	original = "This is a test string";
	int start = 0; // Start index (inclusive)
	int end = 2;   // End index (inclusive)
	result = create_token_string(original, start, end);
	if (result != NULL)
	{
		printf("Substring: %s\n", result);
		free(result); // Remember to free the memory allocated by the function
	}
	else
	{
		printf("Invalid input or memory allocation failed.\n");
	}
	return (0);
}
