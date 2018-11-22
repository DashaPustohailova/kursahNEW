#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h> /* prototype exit() */
#include <string.h>
#include <locale.h>

#define MAX_SIZE 100
int move_to_front(char *str, char c)
{
	char *q, *p;
	int shift = 0;
	p = (char *)malloc(strlen(str) + 1);
	strcpy(p, str);
	q = strchr(p, c); //returns pointer to location of char c in string str
	shift = q - p;      // no of characters from 0 to position of c in str
	strncpy(str + 1, p, shift);
	str[0] = c;
	free(p);
	//  printf("\n%s\n",str);
	return shift;
}

void decode(int* pass, int size, char *sym)
{
	int i, index;
	char c;
	char table[] = "abcdefghijklmnopqrstuvwxyz";
	for (i = 0; i < size; i++)
	{
		c = table[pass[i]];
		index = move_to_front(table, c);
		if (pass[i] != index) printf("there is an error");
		sym[i] = c;
	}
	sym[size] = '\0';
}

void encode(char *sym, int size, int *pass)
{
	int i = 0;
	char c;
	char table[] = "abcdefghijklmnopqrstuvwxyz";
	for (i = 0; i < size; i++)
	{
		c = sym[i];
		pass[i] = move_to_front(table, c);
	}
}

int check(char *sym, int size, int *pass)
{
	int *pass2 = malloc(sizeof(int)*size);
	char *sym2 = malloc(sizeof(char)*size);
	int i, val = 1;

	encode(sym, size, pass2);
	i = 0;
	while (i < size && pass[i] == pass2[i])i++;
	if (i != size)val = 0;

	decode(pass, size, sym2);
	if (strcmp(sym, sym2) != 0) val = 0;

	//	free(sym2);
	free(pass2);

	return val;
}
void main() {
	setlocale(LC_ALL, "Rus");
	int i = 0, j = 0;
	char base[10][100];
	char base1[10][100];
	FILE *fo, *fi, *fiout, *fa, *farch;
	int cnt = 0;
	char chIn[20], chOut[20], chArch[20];
	int pre = EOF;
	int *pass1;
	// ��������� � ������� �� ������� ����
	system("cls");       // ������� ���� �������
loop1:
	printf("����� ��� ������ ��������� ����������� � ����� D:\\MTF\: "); // ������� ���������
	char start[28] = "D:\\\MTF/";
	char start1[28] = "D:\\\MTF/";
	char start2[28] = "D:\\\MTF/";
	int flag = 0;
	char str[100];
	



	printf("������� ��� ����� ��� �����������:\n "); // ������� ���������
	scanf("%s", &chIn);     // ������ �������� ���������� y
	strncat(start, chIn, 20);
	printf("������ ���� � ��������������� �����=%s\n", start); // ������� ���������
	printf("\n");

loop2:
	printf("������� ��� ����� ��� �������� ����:\n "); // ������� ���������
	scanf("%s", &chOut);     // ������ �������� ���������� y
	strncat(start1, chOut, 20);
	printf("������ ���� � ��������������� �����=%s\n", start1); // ������� ���������
	printf("\n");

	// ��������� ���� ��� ������
	fo = fopen(start, "r");
	if (fo == NULL) {
		printf("������, ���� �� ������\n");
		goto loop1;
	}

	// ��������� ���� ��� ������ out
	fi = fopen(start1, "w");
	if (fi == NULL) {
		printf("������, ���� �� ������\n");
		goto loop2;
	}


	/////////////////////
	while (!feof(fo)) {
		fscanf(fo, "%s", base[i]);
		i++;
	}
	cnt = i;


	printf("%d ", cnt);
	int pass[MAX_SIZE] = { 0 };
	int len;
	for (i = 0; i < cnt; i++)
	{
		len = strlen(base[i]);
		encode(base[i], len, pass);



		for (j = 0; j < len; j++) {
			fprintf(fi, "%d ", pass[j]);
		}
		fprintf(fi, "\n");

		printf("%s : [", base[i]);
		for (j = 0; j < len; j++)
			printf("%d ", pass[j]);

		printf("]\n");

		if (check(base[i], len, pass))
			printf("Correct :)\n");
		else
			printf("Incorrect :(\n");
	}


	///////
	int choice;
loop4:

	printf("�������� ��������: 1 - �������� � ����� ... 2 - ��������� ������:\n");
	scanf("%i", &choice);
	switch (choice)
	{
	case 1:
		fiout = fopen(start, "r");

		fa = fopen("D:\\MTF/archiv.txt", "a");
		fprintf(fa, chIn); fprintf(fa, "*START");
		fprintf(fa, "\n");
		int i1 = 0;
		int cnt1 = 0;
		while (!feof(fiout)) {
			fscanf(fiout, "%s", base1[i1]);
			i1++;
		}
		cnt1 = i1;
		int pass1[MAX_SIZE] = { 0 };
		int len1, j1;
		for (i1 = 0; i1 < cnt1; i1++)
		{
			len1 = strlen(base1[i1]);
			encode(base[i1], len1, pass1);
			for (j1 = 0; j1 < len1; j1++) {
				fprintf(fa, "%d ", pass1[j1]);
			}
			fprintf(fa, "\n");
		}

		fprintf(fa, chIn); fprintf(fa, "*END\n");
		//	fprintf(fa, "\n");
		fclose(fa);
		break;

	case 2:
		printf("������� �� ������ � ����������. �� ��������!");
		fclose(fi);
		fclose(fo);

		break;
	default:
		printf("������������ ����.\n");
	}



	printf("������� �� ������ � ����������. ����������!");
	getchar();

}