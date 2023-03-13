#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


//int ft_isdigit(int c);
//int ft_atoi(const char *str);
//int ft_bzero(void*s, size_t n);
//void *ft_calloc(size_t count, size_t size);
//int ft_isalnum(int c);
//int ft_isalpha(int c);
//int ft_isascii(int c);
//int ft_isprint(int c);
//void *ft_memchr(const void *s, int c, size_t n);
//int ft_memcmp(const void *s1, const void *s2, size_t  n);
//void *ft_memcpy(void *dst, const void *src, size_t n);
//void *ft_memset(void *s, int c, size_t n);
//void ft_putchar_fd(char c, int fd);
//void ft_putendl_fd(char *s, int fd);
//void ft_putnbr_fd(int n, int fd);
//void ft_putstr_fd(char *s, int fd);
//char *ft_strchr(const char *s, int c);
//char *ft_strdup(const char *s1);
//char *ft_strjoin(char const *s1, char const *s2);
//size_t ft_strlcat(char *dst, const char *src, size_t dstsize);
//size_t ft_strlcpy (char *restrict dest, const char* restrict src, size_t dstsize);
//size_t ft_strlen(char *s);
//int ft_strncmp(const char *s1, const char *s2, size_t n);
//char *ft_strrchr(const char *s, int c);
//char *ft_substr(char const *s, unsigned int start, size_t len);
//int ft_tolower( int c);
//int ft_toupper(int c);
char *ft_strnstr(const char *haystack, const char *needle, size_t len);

int main()
{
	/*
	printf("PRUEBAS ATOI\n");
	const char *prueba = "45678765";
	printf("ATOI OFICIAL ---> %d\n", atoi(prueba));
   printf("MI ATOI ----> %d\n", ft_atoi(prueba));	
   return (0);
   */


/*

	printf("PRUEBAS BZERO\n");
	char str[50] = "GeeksForGeeks is for programming geeks.";
	printf("\nBefore bzero(): %s\n", str);

	bzero(str + 13, 8*sizeof(char));
	printf("\nAfter official bzero() ----> %s\n", str);
s	ft_bzero(str + 13, 8 * sizeof(char));
	printf("\nAfter my bzero() ----> %s\n", str);
	return (0);
	*/

	/*
	printf("PRUEBAS CALLOC\n");
	char *p = "hola";
	char *p1 = "hola";
	p = calloc(10, 5);
	p1 = ft_calloc(10, 5);
	printf("Official calloc ----> %s\n", p);
	printf("My calloc ----> %s\n", p1);
	return (0);
	*/

	/*
	printf("PRUEBAS ISALNUM\n");
	printf("%d\n", ft_isalnum('8'));
	return (0);
	*/

	/*
	printf("PRUEBAS ISALPHA\n");
	printf("%d\n", ft_isalpha(26));
	return (0);
	*/

	/*
	printf("PRUEBAS ISASCII\n");
	printf("%d\n", ft_isascii(200));
	return (0);
	*/

	/*
	printf("PRUEBAS ISDIGIT\n");
	printf("%d\n", ft_isdigit('a'));
	return (0);
	*/


	/*
	printf("PRUEBAS ISPRINT\n");
	printf("%d\n", ft_isprint(0263));
	return (0);
	*/

	/*
	printf("PRUEBAS MEMCHR\n");
	char *a = "hola buenass tardes";
	int b = 'z';
	printf("Official memchr ----> %s\n", memchr(a, b, strlen(a)));
	printf("My memchr ----> %s\n", ft_memchr(a, b, strlen(a)));
	return (0);
	*/

	/*
	printf("PRUEBAS MEMCMP\n");
	char *a = "hola";
	char *b = "holo";
	printf("Official memcmp ----> %d\n", memcmp(a, b, 5));
	printf("My memcmp ----> %d\n", ft_memcmp(a, b, 5));
	return (0);
	*/

	/*
	printf("PRUEBAS MEMCPY\n");
	const char src1[50] = "hola buenas tardes y mañanas";
	const char src[50] = "hola buenas tardes y mañanas";
	char dest[50];
	char dest1[50];
	strcpy(dest, "hellooooo");
	strcpy(dest1, "helloooo");
	printf("Before memcpy dest = %s\n", dest);
	memcpy(dest, src, strlen(src) + 1);
	printf("After memcpy dest = %s\n", dest);
	printf("Before my memcpy des1 = %s\n", dest1);
	ft_memcpy(dest1, src1, strlen(src1) + 1);
	printf("After my my memcpy dest = %s\n", dest1);
	return (0);
	*/


	/*
	printf("PRUEBAS MEMSET\n");
	char str[50] ="GeeksForGeeks is for programming geeks.";
	printf("\nBefore memset() ----> %s\n", str);
	memset(str + 13, '.', 8 * sizeof(char));
	printf("After memset() ----> %s\n", str);
	ft_memset(str + 13, '.', 8 * sizeof(char));
	printf("\nAfter my memset() ----> %s\n", str);
	return (0);

	*/


/*	
	printf("PRUEBAS FT_PUTCHAR_FD\n");
	char a = 'u';
	int fd = 0;
	ft_putchar_fd(a, fd);
	printf("%d\n", fd);

	return (0);

*/	

/*	
	printf("PRUEBAS FT_PUTENDl_FD\n");
	int fd = 0;
	char *s = "Hola buenas tardes";
	ft_putendl_fd(s, fd);
	printf("%d\n", fd);
	return (0);
*/	

/*	
	printf("PRUEBAS FT_PUTNBR_FD\n");
	int fd = 0;
	int i = 56789;
	ft_putnbr_fd(i, fd);
	printf("%d\n", fd);
	return (0); 
*/	

	/*
	printf("PRUEBAS FT_PUTSTR\n");
	int fd = 2;
	char *s = "Hola buenas tardes";
	ft_putstr_fd(s, fd);
	printf("%d\n", fd);
	return (0);

	*/

	/*
	printf("PRUEBAS FT_STRCHR\n");
	const char *a = "Hola buenas tardes";
	int b = '\0';
	printf("Official strchr ----> %s\n", strchr(a, b));
	printf("My strchr ----> %s\n", ft_strchr(a, b));
	return (0);

	*/

	/*
	printf("PRUEBAS FT_STRDUP\n");
	char array1[] = "This is the array";
	char *p;
	char *p1;
	p = strdup(array1);
	p1 = ft_strdup(array1);
	printf("Original ----> %s\n", array1);
	printf("Official duplicated ----> %s\n", p);
	printf("My duplicated ----> %s\n", p1);
	return (0);
	*/

	/*
	printf("PRUEBAS FT_STRJOIN\n");
	char const *a = "Buenas tardes";
	char const *b = "Buenas noches";
	printf("%s\n", ft_strjoin(a, b));
	return (0);
	*/

	/*
	printf("PRUEBAS FT_STRLCAT");
	char src[50] = "This is the source";
	char dst [50] = "This is the destination";
	printf("Before official strlcat ----> %s\n", dst);
	strlcat(dst, src, 50);
	printf("After official strlcat ----> %s\n", dst);
	char src1[50] = "This is the source";
	char dst1[50] = "This is the destination";
	printf("Before my strlcat ----> %s\n", dst1);
	ft_strlcat(dst1, src1, 50);
	printf("After my strlcat ----> %s\n", dst1);
	return (0);
	*/

	/*
	printf("PRUEBAS FT_STRLCPY\n");
	char *restrict dest = "Hola buennas tardes";
	const char* restrict src = "Hola buenas noches";
	size_t size = 10;
	printf("%zu\n", ft_strlcpy(dest, src, size));
	return (0);

	ARRIBA BUS ERROR
	*/

	/*
	printf("PRUEBAS FT_STRLEN\n");
	printf("Official strlen ----> %zu\n", strlen("hola"));
	printf("My strlen ----> %zu\n", ft_strlen("hola"));
	return (0);
	*/

	/*
	printf("PRUEBAS FT_STRNCMP\n");
	const char *a = "Hola";
	const char *b = "Holo";
	printf("%d\n", ft_strncmp(a, b, 4));
	return (0);
	*/

	/*
	printf("PRUEBAS FT_STRRCHAR\n");
	const char *a = "Hola buenas tardes";
	int b = '\0';
	printf("Official strrchar ----> %s\n", strrchr(a, b));
	printf("My strrchar ----> %s\n", ft_strrchr(a, b));
	return (0);
	*/

	/*
	printf("PRUEBAS FT_SUBSTR\n");
	char const *a = "Hola buenas tardes y buenas noches";
	printf("El nuevo array es ----> %s\n", ft_substr(a, 10, 5));
	return (0);
	*/

	/*
	printf("PRUEBAS FT_TOLOWER\n");
	printf("%d\n", ft_tolower('T'));
	return (0);
	*/

	/*
	printf("PRUEBAS TOUPPER\n");
	printf("My toupper ----> %d\n", ft_toupper('t'));
	printf("official toupper ----> %d\n", toupper('t'));
	return (0);
	*/

	printf("PRUEBAS STRNSTR\n");
	const char *a = "hola buenas tardes";
	const char *b = "tardes";
	size_t len = 30;
	printf("Official strnstr ----> %s\n", strnstr(a, b, len));
	printf("My strnstr ----> %s\n", ft_strnstr(a, b, len));
	return (0);








}
