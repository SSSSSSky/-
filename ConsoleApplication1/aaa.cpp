#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "string.h"
#include "io.h"


#define ERROR 0

#define ElemType Student

struct Student
{
	// �벻Ҫ���ӡ�ɾ�������޸ĳ�Ա����
	unsigned int	ID;			 // ѧ��
	char			Name[8];
	char			Subject[50]; // ��Ϣ���� �� �����Ϣ��ѧ�빤��
	char			Phone[11];
	int				Sex;		 // ��:0; Ů:1
	int				BirthYear;   // �����꣬����1993

								 // TODO: ����getAge()������ʹ֮��ʵ�ֶ�Student�ĳ�Ա�������и�ֵ

	void init(unsigned int id, const char* name, const char* subject, const char* phone, int sex, int birthyear)

	{
		ID = id;
		strcpy(Name, name);
		strcpy(Phone, phone);
		strcpy(Subject, subject);
		Sex = sex;
		BirthYear = birthyear;
	}

	// TODO: ����getAge()������ʹ֮�ܼ��㲢�����������
	int getAge()
	{
		return 2018 - BirthYear;
	}

	void print()
	{
		// TODO
		// ���ܣ�����Ļ�ϴ�ӡ���ҽ���
		// ʾ����"��Һã��ҽ�������, �У������Ϣ��ѧ�빤��רҵ��ѧ����ѧ����2015050152������25��"
		char SexStr[3];
		switch (Sex)
		{
		case 0:
			sprintf(SexStr, "��");
			break;
		case 1:
			sprintf(SexStr, "Ů");
			break;
		}
		printf("%8s, %3s��%10s��%15d��%5d", \
			Name, SexStr, Subject, ID, getAge());
	}

	// �����ݱ��浽�ļ����ú����Ѿ���ɣ�����Ҫ�޸�
	void save2File()
	{
		char Filename[50];
		sprintf(Filename, "%s.dat", Name);
		FILE* fid = fopen(Filename, "w+");
		fwrite(this, sizeof(Student), 1, fid);
		fclose(fid);
	}
};

struct SqList
{
	ElemType* HeadPtr;
	int UsedLength;
	int MaxLength;

	// ��ʼ��
	void init(int InitLength)
	{
		HeadPtr = (ElemType *)malloc(InitLength * sizeof(ElemType));
		if (HeadPtr == NULL)
		{
			printf("Memory allocation failed.\n");
			exit(0);
		}
		//else
		/*{
			printf("Memory allocation succeeded. Base address = %0.8X\n", HeadPtr);
		}*/
		MaxLength = InitLength;
		UsedLength = 0;
	}

	// ������Ԫ��
	void insert(int Index, ElemType elem)
	{
		// �ж�Indexֵ�Ƿ�Ϸ���1 <= Index <= UsedLength + 1
		if (Index < 1 || Index > UsedLength + 1)
		{
			printf("Invalid index.\n");
			exit(ERROR);
		}

		// ���˳����Ƿ�����
		if (UsedLength + 1 > MaxLength)
		{
			printf("Sequential is full. Reallocation memory is required.\n");
			//printf("Legacy base address = %0.8X\n", HeadPtr);
			HeadPtr = (ElemType*)realloc(HeadPtr, (MaxLength + 1) * sizeof(ElemType));
			//printf("New base address = %0.8X\n", HeadPtr);
			MaxLength++;
		}

		// �ӵ�Index������UsedLength��Ԫ�أ�����һ��λ��
		for (int index = UsedLength; index >= Index; index--)
		{
			*(HeadPtr + index) = *(HeadPtr + index - 1);
		}

		// ����Ԫ�ص�ֵ������Index��λ��
		*(HeadPtr + Index - 1) = elem;

		// UsedLength+1
		UsedLength++;
	}

	// ɾ��Ԫ��
	void remove(int Index)
	{
		// �ж�Indexֵ�Ƿ�Ϸ�
		if (Index < 1 || Index > UsedLength)
		{
			printf("Invalid index.\n");
			exit(ERROR);
		}

		// �ӵ�Index+1����UsedLength��Ԫ����ǰ�ƶ�һ��λ��
		for (int index = Index; index < UsedLength; index++)
		{
			*(HeadPtr + index - 1) = *(HeadPtr + index);
		}

		// UsedLength-1
		UsedLength--;
	}

	// ��ȡ˳����е�ĳһ��Ԫ��
	ElemType get(int Index)
	{
		// �ж�Indexֵ�Ƿ�Ϸ���1 <= Index <= UsedLength + 1
		if (Index < 1 || Index > UsedLength)
		{
			printf("Invalid index.\n");
			exit(ERROR);
		}

		ElemType elem = *(HeadPtr + Index - 1);

		return elem;
	}

	// �滻˳����е�ĳһ��Ԫ��
	void replace(int Index, ElemType elem)
	{
		// �ж�Indexֵ�Ƿ�Ϸ���1 <= Index <= UsedLength + 1
		if (Index < 1 || Index > UsedLength + 1)
		{
			printf("Invalid index.\n");
			exit(ERROR);
		}

		*(HeadPtr + Index - 1) = elem;
	}

	// �����ǰ��˳���
	void print()
	{
		printf("\n------˳���ʼ------\n");
		for (int index = 1; index <= UsedLength; index++)
		{
			printf("[%0.3d]\t", index);
			(HeadPtr + index - 1)->print();
			printf("\n",index);
		}
		printf("------˳������------\n\n");
	}

	// ����Ԫ��
	int indexOf(ElemType elem, int(*MatchMethod)(ElemType, ElemType))
	{
		for (int index = 1; index <= UsedLength; index++)
		{
			ElemType TmpElem = *(HeadPtr + index - 1);
			if (MatchMethod(elem, TmpElem) == 1)
			{
				return index;
			}
		}
		return 0;
	}
};

int byName(ElemType TargetStudent, ElemType TmpStudent)
{
	if (strcmp(TargetStudent.Name, TmpStudent.Name) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main()
{
	SqList sqList;
	sqList.init(10);

	Student student1, student2, student3;
	student1.init(1001, "Apple", "Art", "87654321", 0, 2001);
	student2.init(1002, "Banana", "Biology", "87654321", 0, 2002);
	student3.init(1003, "Cherry", "Chinese", "87654321", 0, 2003);

	sqList.insert(1, student1);
	sqList.insert(2, student2);
	sqList.insert(3, student3);

	sqList.print();
	system("pause");

	/*
	sqList.remove(2);

	sqList.print();
	system("pause");

	Student student2Find;
	strcpy(student2Find.Name, "Cherry");
	int index = sqList.indexOf(student2Find, byName);

	Student student2Get;
	student2Get = sqList.get(2);
	sqList.print();
	system("pause");

	sqList.replace(2, student2);
	sqList.print();


	struct _finddata_t files;
	int File_Handle;
	int i = 0;
	char* FileFolder = "C:/Users/lab404/Desktop/Code/DataStructure/��һ����ҵ";
	char Pattern[255];
	sprintf(Pattern, "%s/*.dat", FileFolder);

	File_Handle = _findfirst(Pattern, &files);
	if (File_Handle == -1)
	{
	printf("error\n");
	return;
	}
	do
	{
	printf("%s \n", files.name);

	char FilePath[255];
	sprintf(FilePath, "%s/%s", FileFolder, files.name);
	FILE* fid = fopen(FilePath, "r");
	Student student;
	fread(&student, sizeof(Student), 1, fid);
	fclose(fid);

	sqList.insert(1, student);

	i++;
	} while (0 == _findnext(File_Handle, &files));
	_findclose(File_Handle);
	printf("Find %d files\n", i);

	sqList.print();



	system("pause");*/

}