#include "util.h"

unsigned long hashcode(const char *str)
{
    unsigned long hash = 5381;
    int c;

	c = *str;

	while (c)
	{
        hash = ((hash << 5) + hash) + c;

        c = *str++;
	}

	hash = ((hash << 5) + hash);

	return hash;
}

int getDistance(int x1, int y1, int x2, int y2)
{
	int x, y;

	x = x2 - x1;
	y = y2 - y1;

	return sqrt(x * x + y *y);
}

int fileExists(const char *filename)
{
	struct stat buffer;

	return (stat(filename, &buffer) == 0);
}

char *readFile(char *filename)
{
	char *buffer;
	long length;
	FILE *file;

	file = fopen(filename, "rb");

	if (file == NULL)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "No such file '%s'", filename);
		exit(1);
	}

	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);

	buffer = malloc(length);
	memset(buffer, 0, length);
	fread(buffer, 1, length, file);

	fclose(file);

	return buffer;
}

int writeFile(const char *filename, const char *data)
{
	FILE *file;

	file = fopen(filename, "wb");

	if (file)
	{
		fprintf(file, "%s\n", data);
		fclose(file);
		return 1;
	}

	return 0;
}
