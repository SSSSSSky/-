#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "string.h"
#include "io.h"       //文件        
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
		printf("%8s, %3s，%20s，%15d，%5d", Name, SexStr, Subject, ID, getAge());
		//printf("%15d ", ID);
	}

};

struct SqList
{
	//动态分配顺序存储空间
	ElemType *elem;
	int length;
	int listsize;
	ElemType *p;

	//初始化顺序表 
	void init(int InitLength)
	{
		elem = (ElemType*)malloc(InitLength * sizeof(ElemType));
		if (!elem)
		{
			printf("分配内存失败");
			exit(ERROR);              //超出内存表示范围，退出程序并返回OVERFLOW的值给主调进程 
		}
		else
		{
			printf("分配内存成功\n");
		}
		length = 0;                        //空表长度为0 
		listsize = InitLength;            //初始存储容量 	
	}


	//在位置Index处插入元素e
	//Index的合法值为1<=Index<=length+1
	void insert(int Index, ElemType e)
	{

		if (Index < 1 || Index > length + 1)
			exit(0);
		if (length >= listsize)	     //检查顺序表是否已满 
		{
			elem = (ElemType*)realloc(elem, (listsize + 1) * sizeof(ElemType));  //分配新内存 
			listsize++;
		}
		for (int index = length; index >= Index; index--)
			*(elem + index) = *(elem + index - 1);   //数据后移 
		*(elem + Index - 1) = e;
		length++;
	}

	//在顺序表中删除第Index个元素
	//Index的合法值为1<=Index<=length
	void remove(int Index)
	{
		if ((Index < 1) || Index > length)
			exit(0);
		else
		{
			for (int index = Index; index < length-1 ;index++)
				*(elem + index) = *(elem + index + 1);
				--length;
		}
		
	}

	//查找某个元素e
	int indexOf(ElemType e, int(*MatchMethod)(ElemType, ElemType))
	{
		int index = 1;
		p= elem;
		while (index <= length && !(*MatchMethod)(*p++, e))
			++index;
		if (index<= length)
			return index;
		else return 0;
		
		/*
		for (int index = 1; index <= length; index++)  
		{
			ElemType TmpElem = *(elem + index - 1);
			if (MatchMethod(e, TmpElem) == 0)
				return index;
		}
		return 0;
		*/
		
	}

	// 获取顺序表中的某一个元素
	ElemType get(int Index)
	{
		// 判断Index值是否合法，1 <= Index <= UsedLength + 1
		if (Index < 1 || Index > length)
		{
			printf("Invalid index.\n");
			exit(ERROR);
		}

		ElemType e = *(elem + Index - 1);

		return e;
	}
	/*ElemType get(int Index, ElemType e)
	{
		p = elem;
		int j = 1;
		while (p&&j < 1)
		{
			p = p->elem;
			++j;
		}
		if (!p||j>i)

	}*/

	// 替换顺序表中的某一个元素
	// 判断Index值是否合法，1 <= Index <= length + 1
	void replace(int Index, ElemType e)
	{

		if (Index < 1 || Index >length + 1)
		{
			printf("Invalid index.\n");
			exit(ERROR);
		}

		*(elem + Index - 1) = e;
	}


	// 输出当前的顺序表
	void print()
	{
		printf("\n------顺序表开始------\n");
		for (int index = 1; index <= length; index++)  //index修改 
		{
			printf("[%0.3d]\t", index);
			(elem + index - 1)->print();
			printf("\n");
		}
		printf("------顺序表结束------\n\n");
	}

	// 将数据保存到文件，该函数已经完成，不需要修改
	void save2File(const char *str)
	{
		char Filename[50];
		sprintf(Filename, "%s.dat", str);
		FILE* fid = fopen(Filename, "w+");
		fwrite(this, sizeof(ElemType), 1, fid);
		fclose(fid);
	}
};

int byName(ElemType TargetStudent, ElemType TmpStudent)
{
	if (strcmp(TargetStudent.Name, TmpStudent.Name) == 0)
		return 1;
	else
		return 0;

}

int bySex(ElemType TargetStudent, ElemType TmpStudent)
{
	if ((TargetStudent.Sex==TmpStudent.Sex)==1)
		return 0;
	else
		return 1;

}

int main()
{
	SqList sqList;
	sqList.init(10);
	struct _finddata_t files;
	int File_Handle;
	int i = 0;
	const char* FileFolder = "C:/Users/Administrator/Desktop/dat";
	//将char*改为const char*，其路径为一常量值，不能直接用char*
	char Pattern[255];
	sprintf(Pattern, "%s/*.dat", FileFolder);

	File_Handle = _findfirst(Pattern, &files);
	if (File_Handle == -1)
	{
		printf("error\n");
		return 0;
		//修改return为return 0
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


	//对于所有同学所得的顺序表
	/*sqList.save2File("CompleteSqList");
	sqList.print();*/
	

	//删除李姓同学
	/*Student student1Find, student2Find, student3Find;
	strcpy(student1Find.Name, "李家裕");
    int index1= sqList.indexOf(student1Find ,byName);
	sqList.remove(index1-1);

	strcpy(student2Find.Name, "李戎");
	int index2 = sqList.indexOf(student2Find, byName);
	sqList.remove(index2-1);

	strcpy(student3Find.Name, "李欢津");
	int index3 = sqList.indexOf(student3Find, byName);
	sqList.remove(index3-1);
	
	sqList.save2File("SqListWithoutLi");
	sqList.print();
*/
	
	//女同学的学号顺序表
	Student student4Find;
	student4Find.Sex =0;
	//int index4;
	//index4 = sqList.indexOf(student4Find, bySex);
	for (int index =1; index<=sqList.length; ++index)
	{   
		index = sqList.indexOf(student4Find, bySex);
		sqList.remove(index-1);
	}
	sqList.print();
	
	
	system("pause");
	return 0;
}
