#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t str10tou64(char* str)
{
	uint64_t num = 0;

	while (*str)
	{
		if (*str < '0' || *str > '9') break;
		num = num * 10 + *str - '0';
		str++;
	}

	return num;
}

char* u8tostr16(uint8_t num, char* str)
{
	if (num < 0x10) str[1] = num < 0x0a ? str[1] = '0' + num : 'a' + num - 10;
	else
	{
		str[1] = num % 0x10 < 0x0a ? '0' + num % 0x10 : 'a' + num % 0x10 - 10;
		num = num / 0x10;
		*str = num % 0x10 < 0x0a ? '0' + num % 0x10 : 'a' + num % 0x10 - 10;
	}
	str = str + 2;

	return str;
}

int main(int argc, char* argv[])
{
	char* arg;
	uint64_t off = 0;
	uint64_t lim = -1;
	uint64_t cols = 8;
	uint64_t sects = 2;

	argv++;
	while (arg = *argv)
	{
		argv++;
		if (*arg == '-')
		{
			arg++;
			switch (*arg)
			{
			case 'o':
				arg++;
				if (*arg) off = str10tou64(arg);
				else
				{
					arg = *argv;
					argv++;
					if (arg) off = str10tou64(arg);
				}
				break;
			case 'l':
				arg++;
				if (*arg) lim = str10tou64(arg);
				else
				{
					arg = *argv;
					argv++;
					if (arg) lim = str10tou64(arg);
				}
				break;
			case 'c':
				arg++;
				if (*arg) cols = str10tou64(arg);
				else
				{
					arg = *argv;
					argv++;
					if (arg) cols = str10tou64(arg);
				}
				break;
			case 's':
				arg++;
				if (*arg) sects = str10tou64(arg);
				else
				{
					arg = *argv;
					argv++;
					if (arg) sects = str10tou64(arg);
				}
				break;
			}
		}
		else
		{
			FILE* file = fopen(arg, "rb");

			if (file)
			{
				void* file_cont;

				if (lim == -1)
				{
					fseek(file, 0, SEEK_END);
					lim = ftell(file) - off;
				}
				file_cont = malloc(lim);
				if (file_cont)
				{
					char* cont = file_cont;

					fseek(file, (long)off, SEEK_SET);
					lim = fread(file_cont, 1, lim, file);
					fclose(file);
					while (lim)
					{
						uint64_t cur_sect = 0;

						while (cur_sect < sects)
						{
							uint64_t cur_col = 0;

							while (cur_col < cols)
							{
								char str[3] = { '0', '0', 0 };

								if (lim == 0) goto lim;
								u8tostr16(*cont, str);
								putchar(str[0]);
								putchar(str[1]);
								putchar(' ');
								cont++;
								lim--;
								cur_col++;
							}
							putchar(' ');
							putchar(' ');
							putchar(' ');
							cur_sect++;
						}
						putchar('\n');
					}
				lim:
					free(file_cont);
				}
				else fclose(file);
			}

			break;
		}
	}

	return 0;
}