#include "../include/socket.h"

/**
 * @brief The purpose of this function is to print out an error message and 
 * exit the program if an error occurs. It does this by first saving 
 * the current value of the errno variable, which can be set by system 
 * or library calls to indicate an error. It then prints out the fmt 
 * string followed by the variable arguments to the standard output 
 * using the (vfprintf) function. It then flushes the output using 
 * the (fflush) function.
 * 
 * @param fmt 
 * @param ... 
 */
void	err_n_die(const char *fmt, ...)
{
	int		errno_save;
	va_list	ap;

	//any system or library call can set errno, so we need to save it now
	errno_save = errno;
	//print out the fmt+args to standard out
	va_start(ap, fmt);
	vfprintf(stdout, fmt, ap);
	fprintf(stdout, "\n");
	fflush(stdout);
	//print out error message is errno was set.
	if (errno_save != 0)
	{
		fprintf(stdout, "(errno = %d) : %s\n", errno_save,
				strerror(errno_save));
		fprintf(stdout, "\n");
		fflush(stdout);
	}
	va_end(ap);
	exit(1);
}

/**
 * @brief Convert binary to hexadecimal
 * 
 * @param input 
 * @param len 
 * @return char* 
 */
char	*bin2hex(const unsigned char *input, size_t len)
{
	char	*result;
	char	*hexits;
	int		resultlength;

	hexits = "0123456789ABCDEF";
	if (input == NULL || len <= 0)
		return (NULL);
	//(2 hexits+space)/chr + NULL¬
	resultlength = (len * 3) + 1;
	result = malloc(resultlength);
	bzero(result, resultlength);
	for (int i = 0; i < len; i++)
	{
		result[i * 3] = hexits[input[i] >> 4];
		result[(i * 3) + 1] = hexits[input[i] & 0x0F];
		result[(i * 3) + 2] = ' '; // for readability
	}
	return (result);
}
