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
	// 请不要增加、删除或者修改成员变量
	unsigned int	ID;			 // 学号
	char			Name[8];
	char			Subject[50]; // 信息工程 或 光电信息科学与工程
	char			Phone[11];
	int				Sex;		 // 男:0; 女:1
	int				BirthYear;   // 出生年，例如1993

								 // TODO: 完善getAge()函数，使之能实现对Student的成员变量进行赋值

	void init(unsigned int id, const char* name, const char* subject, const char* phone, int sex, int birthyear)

	{
		ID = id;
		strcpy(Name, name);
		strcpy(Phone, phone);
		strcpy(Subject, subject);
		Sex = sex;
		BirthYear = birthyear;
	}

	// TODO: 完善getAge()函数，使之能计算并返回你的岁数
	int getAge()
	{
		return 2018 - BirthYear;
	}

	void print()
	{
		// TODO
		// 功能：在屏幕上打印自我介绍
		// 示例："大家好！我叫孙世贤, 男，光电信息科学与工程专业的学生，学号是2015050152，今年25岁"
		char SexStr[3];
		switch (Sex)
		{
		case 0:
			sprintf(SexStr, "男");
			break;
		case 1:
			sprintf(SexStr, "女");
			break;
		}
		printf("%8s, %3s，%10s，%15d，%5d", \
			Name, SexStr, Subject, ID, getAge());
	}

	// 将数据保存到文件，该函数已经完成，不需要修改
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

	// 初始化
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

	// 插入新元素
	void insert(int Index, ElemType elem)
	{
		// 判断Index值是否合法，1 <= Index <= UsedLength + 1
		if (Index < 1 || Index > UsedLength + 1)
		{
			printf("Invalid index.\n");
			exit(ERROR);
		}

		// 检查顺序表是否已满
		if (UsedLength + 1 > MaxLength)
		{
			printf("Sequential is full. Reallocation memory is required.\n");
			//printf("Legacy base address = %0.8X\n", HeadPtr);
			HeadPtr = (ElemType*)realloc(HeadPtr, (MaxLength + 1) * sizeof(ElemType));
			//printf("New base address = %0.8X\n", HeadPtr);
			MaxLength++;
		}

		// 从第Index个到第UsedLength个元素，后移一个位置
		for (int index = UsedLength; index >= Index; index--)
		{
			*(HeadPtr + index) = *(HeadPtr + index - 1);
		}

		// 将新元素的值赋给第Index个位置
		*(HeadPtr + Index - 1) = elem;

		// UsedLength+1
		UsedLength++;
	}

	// 删除元素
	void remove(int Index)
	{
		// 判断Index值是否合法
		if (Index < 1 || Index > UsedLength)
		{
			printf("Invalid index.\n");
			exit(ERROR);
		}

		// 从第Index+1到第UsedLength个元素向前移动一个位置
		for (int index = Index; index < UsedLength; index++)
		{
			*(HeadPtr + index - 1) = *(HeadPtr + index);
		}

		// UsedLength-1
		UsedLength--;
	}

	// 获取顺序表中的某一个元素
	ElemType get(int Index)
	{
		// 判断Index值是否合法，1 <= Index <= UsedLength + 1
		if (Index < 1 || Index > UsedLength)
		{
			printf("Invalid index.\n");
			exit(ERROR);
		}

		ElemType elem = *(HeadPtr + Index - 1);

		return elem;
	}

	// 替换顺序表中的某一个元素
	void replace(int Index, ElemType elem)
	{
		// 判断Index值是否合法，1 <= Index <= UsedLength + 1
		if (Index < 1 || Index > UsedLength + 1)
		{
			printf("Invalid index.\n");
			exit(ERROR);
		}

		*(HeadPtr + Index - 1) = elem;
	}

	// 输出当前的顺序表
	void print()
	{
		printf("\n------顺序表开始------\n");
		for (int index = 1; index <= UsedLength; index++)
		{
			printf("[%0.3d]\t", index);
			(HeadPtr + index - 1)->print();
			printf("\n",index);
		}
		printf("------顺序表结束------\n\n");
	}

	// 查找元素
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
	char* FileFolder = "C:/Users/lab404/Desktop/Code/DataStructure/第一次作业";
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