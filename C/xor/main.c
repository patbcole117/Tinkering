#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void PrintBytesW(wchar_t* str, int size);
void GenerateKeyW(wchar_t* key, wchar_t* pt);

void PrintBytesA(char* str, int size);
void GenerateKeyA(char* key, char* pt);

int main(int argc, char* argv[]) {

	char ctA[] = "GetCalendarSupportedDateRange";
	char ptA[] = "WTSEnumerateProcessesW";
	GenerateKeyA(ctA, ptA);		

	//wchar_t ctW[] = L"GetCalendarSupportedDateRange";
	//wchar_t ptW[] = L"WTSEnumerateProcessesW";
	//GenerateKeyW(ctW, ptE);

	return EXIT_SUCCESS;
}

void GenerateKeyW(wchar_t *ct, wchar_t *pt) {
	wchar_t key[64] = {0};
	int szct = wcslen(ct), szpt = wcslen(pt);

	wprintf(L"CT: %s ( len: %d )\n", ct, szct);
	wprintf(L"PT: %s ( len: %d )\n", pt, szpt);
	wprintf(L"KEY: %s ( len: %d )\n", key, szpt);

	for (int i = 0; i < szpt; i++) {
		key[i] = ct[i] ^ pt[i];
	}

	PrintBytesW(ct, szct);
	PrintBytesW(pt, szpt);
	wprintf(L"***\n\n");
	PrintBytesW(key, szpt);
	wprintf(L"\n***\n");

	wchar_t new_pt[64] = { 0 };
	wchar_t new_key[64] = { 0x10, 0x31, 0x27, 0x06, 0x0f, 0x19, 0x08, 0x0b, 0x16, 0x00, 0x06, 0x36, 0x25, 0x02, 0x1f, 0x0c, 0x17, 0x07, 0x16, 0x01, 0x37, 0x36 };
	for (int i = 0; i < szpt; i++) {
		new_pt[i] = ct[i] ^ key[i];
	}

	wprintf(L"NEW_PT: %s ( len: %d )\n", pt, szpt);
	PrintBytesW(new_pt, szpt);
}

void PrintBytesW(wchar_t* str, int size) {
	wprintf(L"{ ");
	for (int i = 0; i < size; i++) {
		wprintf(L"0x%02x, ", str[i]);
	}
	wprintf(L" }\n");
}

void GenerateKeyA(char *ct, char *pt) {
	char key[64] = {0};
	int szct = strlen(ct), szpt = strlen(pt);

	printf("CT: %s ( len: %d )\n", ct, szct);
	printf("PT: %s ( len: %d )\n", pt, szpt);
	printf("KEY: %s ( len: %d )\n", key, szpt);

	for (int i = 0; i < szpt; i++) {
		key[i] = ct[i] ^ pt[i];
	}

	PrintBytesA(ct, szct);
	PrintBytesA(pt, szpt);
	printf("***\n\n");
	PrintBytesA(key, szpt);
	printf("\n***\n");

	char new_pt[64] = { 0 };
	char new_key[64] = { 0x10, 0x31, 0x27, 0x06, 0x0f, 0x19, 0x08, 0x0b, 0x16, 0x00, 0x06, 0x36, 0x25, 0x02, 0x1f, 0x0c, 0x17, 0x07, 0x16, 0x01, 0x37, 0x36 };
	for (int i = 0; i < szpt; i++) {
		new_pt[i] = ct[i] ^ key[i];
	}

	printf("NEW_PT: %s ( len: %d )\n", pt, szpt);
	PrintBytesA(new_pt, szpt);
}

void PrintBytesA(char* str, int size) {
	printf("{ ");
	for (int i = 0; i < size; i++) {
		printf("0x%02x, ", str[i]);
	}
	printf(" }\n");
}