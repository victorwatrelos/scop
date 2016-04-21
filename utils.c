#include "utils.h"

char		*filetobuf(const char *file, size_t *size)
{
	FILE *fptr;
	long length;
	char *buf;

	errno = 0;
	fptr = fopen(file, "r");
	if (!fptr)
	{
		ft_printf("Error on file %s, %d, %s\n", file, errno, strerror(errno));
		return (NULL);
	}
	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	if (!(buf = (char*)malloc(length + 1)))
		return (NULL);
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);
	fclose(fptr);
	buf[length] = '\0';
	if (size)
		*size = (size_t)length;
	return (buf);
}
