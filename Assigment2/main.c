#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#define FILENAME "log.txt"
#define MAXLENGTHFILE 5000
char fileStr[MAXLENGTHFILE];
/// <summary>
/// Hàm cắt chuỗi
/// </summary>
/// <param name="str">Con trỏ xuất phát</param>
/// <param name="num">Số ký tự</param>
/// <returns></returns>
char* strCut(char* str, int num);
/// <summary>
/// Hàm cắt chuối theo kí tự
/// </summary>
/// <param name="str"></param>
/// <param name="c"></param>
/// <returns></returns>
char* strCutc(char* str, char c);
/// <summary>
/// Hàm đổi chữ hoa thành chữ thường
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
char* toLower(char* s);
/// <summary>
/// Hàm kiểm tra có chuỗi con trong chuỗi cha không
/// </summary>
/// <param name="str">Chuỗi cha</param>
/// <param name="subStr">Chuỗi con</param>
/// <returns></returns>
bool checkContain(char* str, char* subStr);
int fileToStr(char* str);
/// <summary>
/// Hàm đếm số lần xuất hiện của chuỗi con
/// </summary>
/// <param name="str">Chuỗi cha</param>
/// <param name="subStr">chuỗi con</param>
/// <returns></returns>
int countSubStr(char* str, char* subStr);
/// <summary>
/// Hàm kiểm tra số bản tin lỗi
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
int countErr(char* str);
/// <summary>
/// Hàm tính đõ trễ lớn nhất
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
int* maxLatency(char* str);
/// <summary>
/// Hàm đếm số lượt gửi đi/ nhận về bản tin từ 1 thiết bị
/// </summary>
/// <param name="device">Mã thiết bị</param>
/// <param name="status">trong thái: set or status</param>
/// <returns></returns>
int countNews_device(char* str, char* device, char* status);
/// <summary>
/// Hàm đếm số công tắc
/// </summary>
/// <returns></returns>
int countSwitch(char* str);
/// <summary>
/// Tách thời gian
/// </summary>
/// <param name="token"></param>
/// <returns></returns>
char* getDate(char* token);
/// <summary>
/// Hàm lấy giờ
/// </summary>
/// <param name="token"></param>
/// <returns></returns>
char* getTime(char* token);
//tru thoi gian
int subTime(char* set, char* status, bool plus);
/// <summary>
/// Tim so lon nhat trong mang
/// </summary>
/// <param name="arr"></param>
/// <param name="n"></param>
/// <returns></returns>
int findMax(int* arr, int n);
int findMax(int* arr, int n)
{
	int max = 0;
	for (int i = 0; i < n; i++)
	{
		if (*(arr + i) > max)
			max = *(arr + i);
	}
	return max;
}
int subTime(char* set, char* status, bool plus)
{
	int sub;

	char* temp = strCut(set, 2);
	int hSet = atoi(temp);
	free(temp);
	temp = strCut(set+3, 2);
	int mSet = atoi(temp);
	free(temp);
	temp = strCut(set + 6, 2);
	int sSet = atoi(temp);
	free(temp);
	temp = strCut(set + 9, 3);
	int msSet = atoi(temp);
	free(temp);

	temp = strCut(status, 2);
	int hSt = atoi(temp);
	free(temp);
	temp = strCut(status + 3, 2);
	int mSt = atoi(temp);
	free(temp);
	temp = strCut(status + 6, 2);
	int sSt = atoi(temp);
	free(temp);
	temp = strCut(status + 9, 3);
	int msSt = atoi(temp);
	if (plus)
		hSt += 24;
	free(temp);

	sub = (hSt * 3600 * 1000 + mSt * 60 * 1000 + sSt * 1000 + msSt) - (hSet * 3600 * 1000 + mSet * 60 * 1000 + sSet * 1000 + msSet);
	return sub;
}
char* getTime(char* token)
{
	//17-28
	char* res = (char*)malloc(13 * sizeof(char));
	for (int i = 17; i < 29; i++)
	{
		*(res + i - 17) = *(token + i);
	}
	*(res + 12) = '\0';
	return res;
}
char* getDate(char* token)
{
	char* res = (char*)malloc(12 * sizeof(char));
	for (int i = 7; i < 17; i++)
	{
		*(res + i - 7) = *(token + i);
	}
	*(res + 10) = '\0';
	return res;
}
char* strCut(char* str, int num)
{
	char* res = (char*)malloc(sizeof(char) * (num + 2));
	for (int i = 0; i < num; i++)
	{
		*(res + i) = *(str + i);
	}
	*(res + num) = '\0';
	return res;
}
bool checkContain(char* str, char* subStr)
{
	char* p = strstr(str, subStr);
	return p != NULL ? true : false;
}
char* toLower(char* s) {
	char* p = (char*)malloc(sizeof(char) * (strlen(s) + 2));
	int count = 0;
	while (*s != '\0')
	{
		*(p+count) = tolower(*s);
		count++;
		s++;
	}
	*(p + count) = '\0';
	return p;
}

char* strCutc(char* str, char c)
{
	int count = 0;
	char* res = (char*)malloc(sizeof(char) * 10);
	while (*(str) != c)
	{
		*(res + count) = *str;
		str++;
		count++;
	}
	*(res + count) = '\0';
	return res;
}
int countSubStr(char* str, char* subStr)
{
	int len = strlen(subStr);
	int count = 0;

	
	char* token;
	token = strtok(str, "\n");


	char* where;
	if (len)
		while (token!= NULL)
		{
			where = token;
			if ((where = strstr(where, subStr)))
			{
				count++;
				printf("%s\n", token);
			}
			token = strtok(NULL, "\n");
		}


	return count;
}
int countNews_device(char*str, char* device, char* status)
{
	char* dev = toLower(device);
	int len = strlen(dev);
	int count = 0;
	int dem = 0;
	char* token = NULL;
	char* strOri = str;
	if(len)
		while (*(str)!='\0')
		{	
			dem++;
			if (*(str) == '\n')
			{
				token = strCut(strOri, dem);
				if (checkContain(token, dev) && checkContain(token, status))
				{
					count++;
					printf("%s\n", token);
				}
				free(token);
				dem = 0;
				strOri = str + 1;
			}
			
			str++;
		}

	free(dev);
	return count;
}
int countSwitch(char* str)
{
	int dev = 0;
	char arr[20][20];//20 pt, moi pt toi da 20 ky tu
	char res[10][20];//mang luu ket qua cuoi cung
	int dem = 0;
	char* strOri = str;
	char* token = NULL;
	int count = 0;
	int temp = 0;
	//Lay ra mang cac chuoi
	while (*(str) != '\0')
	{
		dem++;
		if (*(str) == '\n')
		{			
			token = strCut(strOri, dem);
			char* p = strstr(token ,"zwave-");
			//them vao mang
			while (*(p+6) != '"')
			{
				arr[count][temp] = *(p+6);
				p++;
				temp++;
			}
			arr[count][temp] = '\0';
			temp = 0;
			dem = 0;
			strOri = str + 1;
			count++;
		}
		str++;
	}
	for (int i = 0; i < count; i++)
	{
		if (i == 0)
		{
			int n = 0;
			for (int k = 0; k < strlen(arr[i]); k++)
			{
				res[dev][k] = arr[i][k];
				n++;
			}
			res[dev][n] = '\0';
			dev++;
		}
		//Ma thiet bi tai phan tu thu i;
		char* p = strCutc(arr[i], ':');
		for (int j = 0; j < i; j++)
		{
			char* q = strCutc(arr[j], ':');
			//neu co 2 chuoi trung nhau thi thoat
			if (strcmp(p, q) == 0)
			{
				break;
			}
			//neu di den cuoi mang
			if (j == i - 1)
			{
				if (strcmp(p, q) == 0)
				{
					break;
				}
				else
				{
					int n = 0;
					for (int k = 0; k < strlen(arr[i]); k++)
					{
						res[dev][k] = arr[i][k];
						n++;
					}
					res[dev][n] = '\0';
					dev++;
				}
			}
			free(q);
		}
		free(p);
	}	
	for (int i = 0; i < dev; i++)
	{
		char* endpoint = NULL;
		char* name = NULL;

		name = strCutc(res[i], ':');

		char* e = strchr(res[i], '-');
		int index = (int)(e - res[i]);

		endpoint = strtok((res[i] + index), "-");

		printf("thiet bi thu %d co dia chi: NWK - %s, ENDPOINT - %s\n", i + 1, name, endpoint);
		free(name);
	}
	return dev;
}
int countErr(char* str)
{
	int count = 0;
	char* strcy = (char*)malloc(sizeof(char) * 4001);
	strcpy(strcy, str);

	char* set = strtok(strcy, "\n");
	char* status= strtok(NULL, "\n");

	char* set1 = (char*)malloc(sizeof(char) * 20);
	char* status1 = (char*)malloc(sizeof(char) * 20);

	

	while (status != NULL)
	{
		strcpy(set1, strstr(set,"reqid"));

		strcpy(status1, strstr(status, "reqid"));

		if (strcmp(set1, status1) != 0)
			count++;

		set = strtok(NULL, "\n");
		status = strtok(NULL, "\n");
	}

	//free(strcy);
	free(set1);
	free(status1);
	return count;
}
int* maxLatency(char* str)
{
	int* res = (int*)malloc(3 * sizeof(int));
	int late[11];
	int count = 0;
	char* strcy = (char*)malloc(sizeof(char) * 4001);
	strcpy(strcy, str);

	char* set = strtok(strcy, "\n");
	char* status = strtok(NULL, "\n");

	char* set1 = (char*)malloc(sizeof(char) * 20);
	char* status1 = (char*)malloc(sizeof(char) * 20);

	char* dateSet = NULL;
	char* timeSet = NULL;
	char* dateStatus = NULL;
	char* timeStatus = NULL;

	while (status != NULL)
	{
		strcpy(set1, strstr(set, "reqid"));

		strcpy(status1, strstr(status, "reqid"));
		//Nếu bản ghi không lỗi
		if (strcmp(set1, status1) == 0)
		{

			dateSet = getDate(set);
			dateStatus = getDate(status);
			timeSet = getTime(set);
			timeStatus = getTime(status);

			
			int sub = 0;

			if (strcmp(dateSet, dateStatus) == 0)
			{
				sub = subTime(timeSet, timeStatus, false);
			}
			else
			{
				sub = subTime(timeSet, timeStatus, true);
			}
			late[count] = sub;
			count++;

			free(dateSet);
			free(timeSet);
			free(timeStatus);
			free(dateStatus);
		}


		set = strtok(NULL, "\n");
		status = strtok(NULL, "\n");
	}

	//free(strcy);
	free(set1);
	free(status1);
	int max = findMax(late, count);
	int avarage = 0;

	for (int i = 0; i < count; i++)
	{
		avarage += late[i];
	}
	avarage /= count;
	*(res + 0) = max;
	*(res + 1) = avarage;

	return res;
}
int fileToStr(char* str)
{
	int status;
	FILE* fp = NULL;
	fp = fopen(FILENAME, "r");
	if (fp == NULL)
	{
		printf("File khong ton tai");
		return -1;
	}	
	status = fread(str, MAXLENGTHFILE, 1, fp);
	*(str + 4000) = '\0';

	char* strcy = (char*)malloc(sizeof(char) * 4001);
	strcpy(strcy, str);
	
	//region
	char* subStr = "set";
	char* device = (char*)malloc(15*sizeof(char));
	int count = countSubStr(str, subStr);
	
	printf("So ban tin gui di: %d\n", count);

	printf("----------------------------------------------------\n");

	printf("Xin moi nhap vao ma thiet bi: ");

	fgets(device, 15, stdin);

	char* ptr = strchr(device, '\n');
	if (ptr)
	{
		//if new line found replace with null character
		*ptr = '\0';
	}

	int counDev = countNews_device(strcy, device, "set");
	printf("So ban tin gui di tu thiet bi %s: %d\n", device, counDev);
	free(device);

	printf("----------------------------------------------------\n");

	countSwitch(strcy);

	printf("----------------------------------------------------\n");
	
	int err = countErr(strcy);

	printf("So ban tin bi loi: %d\n", err);

	printf("----------------------------------------------------\n");

	int* res = maxLatency(strcy);

	printf("Do tre lon nhat la: %d(ms)\n", res[0]);
	printf("----------------------------------------------------\n");
	printf("Do tre trung binh la: %d(ms)\n", res[1]);
	free(res);
	//end region
	fclose(fp);
	fp = NULL;
	free(strcy);
	strcy = NULL;
	return status;
}

int main()
{
	char* str = (char*)malloc(sizeof(char)* MAXLENGTHFILE);
	fileToStr(str);

	free(str);



	return 0;
}