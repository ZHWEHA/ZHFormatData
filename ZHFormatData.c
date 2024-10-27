#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"ZHFormatData.h"

#define ArrayLength(Ar) (sizeof(Ar)/sizeof(Ar[0]))

#define 结束字符		('\0')
#define 翻译字符		('`')

#define 空白文本		("")

#define 群组开始字符		('(')
#define 群组结束字符		(')')
#define 条目开始字符		('<')
#define 条目结束字符		('>')
#define 数据开始字符		('[')
#define 数据结束字符		(']')
#define 注释开始字符		('{')
#define 注释结束字符		('}')

#define 开始文本		("True")
#define 结束文本		("False")

#define 群组文本(文本) ("("##文本")")
#define 条目文本(文本) ("("##文本")")
#define 数据文本(文本) ("("##文本")")
#define 群组注释(注释) ("{("##注释")}")
#define 条目注释(注释) ("{("##注释")}")
#define 数据注释(注释) ("{("##注释")}")

typedef void VOID, * VOIDPo;
typedef size_t DATAMAXI, * DATAMAXIPo;
typedef char 字符类型, * 字符类型Po, 文本类型, * 文本类型Po;

typedef enum StateEn
{
	F = 0,
	T = 1
} STATE;

/*元素*/
typedef struct 数据类型St
{
	文本类型Po 文本Po;		/*数据文本*/
	文本类型Po 注释Po;		/*数据注释*/
} 数据类型, * 数据类型Po;
typedef struct 条目类型St
{
	文本类型Po 文本Po;		/*条目文本*/
	文本类型Po 注释Po;		/*条目注释*/
	DATAMAXI 数据数量;		/*数据数量*/
	数据类型Po 数据PoAr[0];	/*数据类型群组{弹性数组}*/
} 条目类型, * 条目类型Po;
typedef struct 群组类型St
{
	文本类型Po 文本Po;		/*群组文本*/
	文本类型Po 注释Po;		/*群组注释*/
	DATAMAXI 条目数量;		/*条目数量*/
	条目类型Po 条目PoAr[0];	/*条目类型群组{弹性数组}*/
} 群组类型, * 群组类型Po;
typedef struct ZHFormatDataSt
{
	DATAMAXI 群组数量;		/*群组数量*/
	群组类型Po 群组PoAr[0];	/*群组类型群组{弹性数组}*/
} 格式数据类型, * 格式数据类型Po, ZHFDSt, * ZHFDStPo;

/*格式文本*/
typedef struct 格式文本St
{
	文本类型Po 群组文本Po;		/*群组文本*/
	文本类型Po 条目文本Po;		/*条目文本*/
	size_t 数据标识;			/*数据索引*/
} 格式文本类型, * 格式文本类型Po;

static const char 分隔字符Ar[] = { ':', '.' };

static const 文本类型 开始状态Ar[] = { 'T','t','S','s','O','o','+','*','1','2','3','4','5','6','7','8','9' };
static const 文本类型 结束状态Ar[] = { 'F','f','E','e','C','c','-','/','0' };


/*----------------------------------------------------------------
文本：阴面{底层}
----------------------------------------------------------------*/

/**
 * @brief 文本开始。
 * @param P文本BA 文本字节数量。
 * @return 成功返回：文本内存Po；失败返回：NULL；
 *
 * 注解：
 * - 函数分配 文本内存，将 文本内存 写入0。
 * - 结束需要使用 文本结束FFu 函数释放。
 *
 * 示例：
 * - 文本类型Po 文本Po = 文本开始FFu(文本长度 + 1);
 */
static 文本类型Po 文本开始FFu(DATAMAXI P文本BA)
{
	if (P文本BA == 0) return NULL;
	文本类型Po 文本Po = malloc(P文本BA * sizeof(文本类型));
	if (文本Po != NULL) memset(文本Po, 0, sizeof(文本类型));
	return 文本Po;
}
/**
 * @brief 文本结束。
 * @param P文本Po 文本Po。
 *
 * 注解：
 * - 将 文本类型 内存 销毁。
 *
 * 示例：
 * - 文本结束FFu(文本Po);
 */
static VOID 文本结束FFu(文本类型Po P文本Po)
{
	free(P文本Po);
}

/**
 * @brief 文本比较。
 * @param P文本阴Po 文本Po，可以为NULL。
 * @param P文本阳Po 文本Po，可以为NULL。
 * @param P检测 F：忽略大小写；否则：判断大小写；
 * @return F：文本不同；T：文本相同；
 *
 * 注解：
 * - 比较 P文本阴Po 和 P文本阳Po 是否 相同。
 * - 如果 P文本阴Po 和 P文本阳Po 同时为 NULL，则 相同。
 *
 * 示例：
 * - if (文本比较FFu(P文本阴Po, P文本阳Po, F) == F)
 * - if (文本比较FFu(P文本阴Po, P文本阳Po, F) != F)
 */
static STATE 文本比较FFu(const char* P文本阴Po, const char* P文本阳Po, STATE P检测)
{
	/*判断 P文本阴Po 和 P文本阳Po 同时为 NULL*/
	if (P文本阴Po == NULL && P文本阳Po == NULL) return T;
	if (P文本阴Po == NULL || P文本阳Po == NULL) return F;
	size_t 文本长度 = strlen(P文本阴Po);
	if (文本长度 != strlen(P文本阳Po)) return F;
	if (P检测 == F)
	{
		for (size_t Accu = 0; Accu < 文本长度; Accu++)
			if ((P文本阴Po[Accu] >= 'a' && P文本阴Po[Accu] <= 'z' ? P文本阴Po[Accu] - 32 : P文本阴Po[Accu]) !=
				(P文本阳Po[Accu] >= 'a' && P文本阳Po[Accu] <= 'z' ? P文本阳Po[Accu] - 32 : P文本阳Po[Accu])) return F;
	}
	else if (strcmp(P文本阴Po, P文本阳Po) != 0) return F;
	return T;
}

/*----------------------------------------------------------------
格式文本：阴面{底层}
----------------------------------------------------------------*/

VOID 格式文本结束FFu(格式文本类型Po P格式文本信息Po);

/**
 * @brief 格式文本开始。
 * @param P格式文本Po 格式文本。
 * @return 成功返回：格式文本类型Po；失败返回：NULL；
 *
 * 注解：
 * - 函数分配 格式文本类型 内存，P格式文本Po 内容 写入 格式文本类型 内存。
 * - 格式多余信息忽略，信息之间以 分隔符号 分隔。
 * - 如果 编号 不是数值，则返回 失败。
 * - 结束需要使用 格式文本结束FFu 函数释放。
 *
 * 示例：
 * - 格式文本类型Po 格式文本Po = 格式文本开始FFu(""); 为{NULL,NULL,0}
 * - 格式文本类型Po 格式文本Po = 格式文本开始FFu("群组"); 为{群组,NULL,0}
 * - 格式文本类型Po 格式文本Po = 格式文本开始FFu("群组:条目"); 为{群组,条目,0}
 * - 格式文本类型Po 格式文本Po = 格式文本开始FFu("群组:条目:1"); 为{群组,条目,1}
 * - 格式文本类型Po 格式文本Po = 格式文本开始FFu(":条目:1"); 为{NULL,条目,1}
 * - 格式文本类型Po 格式文本Po = 格式文本开始FFu("::1"); 为{NULL,NULL,1}
 * - 格式文本类型Po 格式文本Po = 格式文本开始FFu("::"); 为{NULL,NULL,0}
 */
static 格式文本类型Po 格式文本开始FFu(const 文本类型Po P格式文本Po)
{
	if (P格式文本Po == NULL) return NULL;
	格式文本类型Po 格式文本信息Po = malloc(sizeof(格式文本类型));
	if (格式文本信息Po == NULL) return NULL;
	memset(格式文本信息Po, 0, sizeof(格式文本类型));
	const DATAMAXI 信息数量 = 3, 文本BA = strlen(P格式文本Po) + 1;
	DATAMAXI 开始索引 = 0, 结束索引 = 0;
	/*群组文本*/
	文本类型Po 群组文本Po = NULL;
	{
		DATAMAXI 群组文本长度 = 0;
		while (1)
		{
			if (P格式文本Po[结束索引] == 结束字符) break;
			STATE 结束状态 = F;
			for (size_t i = 0; i < ArrayLength(分隔字符Ar); i++)
				if (P格式文本Po[结束索引] == 分隔字符Ar[i]) 结束状态 = T;
			if (结束状态 == T) break;
			结束索引++;
		}
		群组文本长度 = 结束索引 - 开始索引;
		/*开始文本*/
		if (群组文本长度 == 0);
		else
		{
			群组文本Po = 文本开始FFu(群组文本长度 + 1);
			if (群组文本Po == NULL) goto Error;
			/*读取文本*/
			for (size_t i = 0; i < 群组文本长度; i++)
				群组文本Po[i] = P格式文本Po[开始索引 + i];
			群组文本Po[群组文本长度] = 结束字符;
		}
	}
	格式文本信息Po->群组文本Po = 群组文本Po;
	if (P格式文本Po[结束索引 + 1] == 结束字符) return 格式文本信息Po;
	结束索引 += 1;
	开始索引 = 结束索引;
	/*条目文本*/
	文本类型Po 条目文本Po = NULL;
	{
		DATAMAXI 条目文本长度 = 0;
		while (1)
		{
			if (P格式文本Po[结束索引] == 结束字符) break;
			STATE 结束状态 = F;
			for (size_t i = 0; i < ArrayLength(分隔字符Ar); i++)
				if (P格式文本Po[结束索引] == 分隔字符Ar[i]) 结束状态 = T;
			if (结束状态 == T) break;
			结束索引++;
		}
		条目文本长度 = 结束索引 - 开始索引;
		/*开始文本*/
		if (条目文本长度 == 0);
		else
		{
			条目文本Po = 文本开始FFu(条目文本长度 + 1);
			if (条目文本Po == NULL) goto Error;
			/*读取文本*/
			for (size_t i = 0; i < 条目文本长度; i++)
				条目文本Po[i] = P格式文本Po[开始索引 + i];
			条目文本Po[条目文本长度] = 结束字符;
		}
	}
	格式文本信息Po->条目文本Po = 条目文本Po;
	if (P格式文本Po[结束索引 + 1] == 结束字符) return 格式文本信息Po;
	结束索引 += 1;
	开始索引 = 结束索引;
	/*编号文本*/
	文本类型Po 编号文本Po = NULL;
	{
		DATAMAXI 编号文本长度 = 0;
		while (1)
		{
			if (P格式文本Po[结束索引] == 结束字符) break;
			STATE 结束状态 = F;
			for (size_t i = 0; i < ArrayLength(分隔字符Ar); i++)
				if (P格式文本Po[结束索引] == 分隔字符Ar[i]) 结束状态 = T;
			if (结束状态 == T) break;
			结束索引++;
		}
		编号文本长度 = 结束索引 - 开始索引;
		/*开始文本*/
		if (编号文本长度 == 0);
		else
		{
			编号文本Po = 文本开始FFu(编号文本长度 + 1);
			if (编号文本Po == NULL) goto Error;
			/*读取文本*/
			for (size_t i = 0; i < 编号文本长度; i++)
				编号文本Po[i] = P格式文本Po[开始索引 + i];
			编号文本Po[编号文本长度] = 结束字符;
		}
	}
	if (编号文本Po == NULL)
		格式文本信息Po->数据标识 = 0;
	else
		格式文本信息Po->数据标识 = strtoull(编号文本Po, NULL, 10);
	/*错误||溢出*/
	if (errno == EINVAL || errno == ERANGE) goto Error;
	return 格式文本信息Po;
Error:
	格式文本结束FFu(格式文本信息Po);
	return NULL;
}
/**
 * @brief 格式文本信息结束。
 * @param P格式文本信息Po 格式文本信息Po。
 *
 * 注解：
 * - 函数释放 格式文本类型 内存。
 *
 * 示例：
 * - 格式文本结束FFu(格式文本Po);
 */
static VOID 格式文本结束FFu(格式文本类型Po P格式文本信息Po)
{
	free(P格式文本信息Po->群组文本Po);
	free(P格式文本信息Po->条目文本Po);
	free(P格式文本信息Po);
}

/*----------------------------------------------------------------
搜索：阴面{底层}
----------------------------------------------------------------*/

/**
 * @brief 搜索群组。
 * @param P格式数据Po 格式数据类型Po。
 * @param P文本Po 群组文本Po。
 * @return 成功返回：群组Po；失败返回：NULL；
 *
 * 注解：
 * - P文本Po 可以为 NULL。
 * - 函数会跳过指针为 NULL 的 群组。
 *
 * 示例：
 * - 群组类型Po 群组Po = 搜索群组FFu(P格式数据Po, P文本Po);
 */
static 群组类型Po 搜索群组FFu(const 格式数据类型Po P格式数据Po, const 文本类型Po P文本Po)
{
	if (P格式数据Po == NULL) return NULL;
	if (P格式数据Po->群组数量 == 0) return NULL;/*没有群组*/
	群组类型Po 群组Po = NULL;
	for (size_t i = 0; i < P格式数据Po->群组数量; i++)
	{/*循环寻找群组*/
		if (P格式数据Po->群组PoAr[i] == NULL) continue;/*跳过 NULL 群组*/
		if (文本比较FFu(P格式数据Po->群组PoAr[i]->文本Po, P文本Po, T) == T)
		{/*相同返回*/
			群组Po = P格式数据Po->群组PoAr[i];
			break;
		}
	}
	return 群组Po;
}
/**
 * @brief 搜索条目。
 * @param P群组Po 群组类型Po。
 * @param P文本Po 文本类型Po。
 * @return 成功返回：条目Po；失败返回：NULL；
 *
 * 注解：
 * - P文本Po 可以为 NULL。
 * - 函数会跳过指针为 NULL 的 条目。
 *
 * 示例：
 * - 条目类型Po 条目Po = 搜索条目FFu(P群组Po, P文本Po);
 */
static 条目类型Po 搜索条目FFu(const 群组类型Po P群组Po, const 文本类型Po P文本Po)
{
	if (P群组Po == NULL) return NULL;
	if (P群组Po->条目数量 == 0) return NULL;/*没有条目*/
	条目类型Po 条目Po = NULL;
	for (size_t i = 0; i < P群组Po->条目数量; i++)
	{/*循环寻找条目*/
		if (P群组Po->条目PoAr[i] == NULL) continue;/*跳过 NULL 条目*/
		if (文本比较FFu(P群组Po->条目PoAr[i]->文本Po, P文本Po, T) == T)
		{/*相同返回*/
			条目Po = P群组Po->条目PoAr[i];
			break;
		}
	}
	return 条目Po;
}

/*----------------------------------------------------------------
结构：阴面{底层}
----------------------------------------------------------------*/

/**
 * @brief 开始数据结构。
 * @return 成功返回：数据Po；失败返回：NULL；
 *
 * 注解：
 * - 创建数据结构内存，并将内存写入0。
 * - 结束需要使用 结构数据结束FFu 函数释放。
 *
 * 示例：
 * - 数据类型Po 数据Po = 结构数据开始FFu();
 */
static 数据类型Po 结构数据开始FFu(VOID) {
	数据类型Po StPo = malloc(sizeof(数据类型));
	if (StPo == NULL) return NULL;
	memset(StPo, 0, sizeof(数据类型));
	return StPo;
}
/**
 * @brief 结束数据结构。
 * @param P数据Po 数据结构Po，可以为 NULL。
 *
 * 注解：
 * - 将 数据类型 内存 销毁。
 *
 * 示例：
 * - 结构数据结束FFu(P数据Po);
 */
static VOID 结构数据结束FFu(数据类型Po P数据Po)
{
	free(P数据Po->文本Po);
	P数据Po->文本Po = NULL;
	free(P数据Po->注释Po);
	P数据Po->注释Po = NULL;
	free(P数据Po);
}

/**
 * @brief 开始条目结构。
 * @return 成功返回：条目Po；失败返回：NULL；
 *
 * 注解：
 * - 创建条目结构内存，并将内存写入0。
 * - 结束需要使用 结构条目结束FFu 函数释放。
 *
 * 示例：
 * - 条目类型Po 条目Po = 结构条目开始FFu();
 */
static 条目类型Po 结构条目开始FFu(VOID) {
	条目类型Po StPo = malloc(sizeof(条目类型));
	if (StPo == NULL) return NULL;
	memset(StPo, 0, sizeof(条目类型));
	return StPo;
}
/**
 * @brief 结束条目结构。
 * @param P条目Po 数据结构Po。
 *
 * 注解：
 * - 将 条目类型 内存 和 数据类型 内存 销毁。
 *
 * 示例：
 * - 结构条目结束FFu(P条目Po);
 */
static VOID 结构条目结束FFu(条目类型Po P条目Po)
{
	if (P条目Po == NULL) return;
	for (size_t i = 0; i < P条目Po->数据数量; i++)
	{
		结构数据结束FFu(P条目Po->数据PoAr[i]);
		P条目Po->数据PoAr[i] = NULL;
	}
	free(P条目Po->文本Po);
	P条目Po->文本Po = NULL;
	free(P条目Po->注释Po);
	P条目Po->注释Po = NULL;
	free(P条目Po);
}

/**
 * @brief 开始群组结构。
 * @return 成功返回：群组Po；失败返回：NULL；
 *
 * 注解：
 * - 创建群组结构内存，并将内存写入0。
 * - 结束需要使用 结构群组结束FFu 函数释放。
 *
 * 示例：
 * - 群组类型Po 群组Po = 结构群组开始FFu();
 */
static 群组类型Po 结构群组开始FFu(VOID) {
	群组类型Po StPo = malloc(sizeof(群组类型));
	if (StPo == NULL) return NULL;
	memset(StPo, 0, sizeof(群组类型));
	return StPo;
}
/**
 * @brief 结束群组结构。
 * @param P群组Po 数据结构Po。
 *
 * 注解：
 * - 将 群组类型 内存、条目类型 内存 和 数据类型 内存 销毁。
 *
 * 示例：
 * - 结构群组结束FFu(P群组Po);
 */
static VOID 结构群组结束FFu(群组类型Po P群组Po)
{
	if (P群组Po == NULL) return;
	for (size_t i = 0; i < P群组Po->条目数量; i++)
	{
		结构条目结束FFu(P群组Po->条目PoAr[i]);
		P群组Po->条目PoAr[i] = NULL;
	}
	free(P群组Po->文本Po);
	P群组Po->文本Po = NULL;
	free(P群组Po->注释Po);
	P群组Po->注释Po = NULL;
	free(P群组Po);
}

/**
 * @brief 开始格式数据结构。
 * @return 成功返回：格式数据Po；失败返回：NULL；
 *
 * 注解：
 * - 创建格式数据结构内存，并将内存写入0。
 * - 结束需要使用 结构格式数据结束FFu 函数释放。
 *
 * 示例：
 * - 格式数据类型Po 格式数据Po = 结构格式数据开始FFu();
 */
static 格式数据类型Po 结构格式数据开始FFu(VOID) {
	格式数据类型Po StPo = malloc(sizeof(格式数据类型));
	if (StPo == NULL) return NULL;
	memset(StPo, 0, sizeof(格式数据类型));
	return StPo;
}
/**
 * @brief 销毁格式数据结构，以及内部申请的内存。
 * @param P格式数据Po 数据结构Po，可以为 NULL。
 *
 * 注解：
 * - 将 群组类型 内存、条目类型 内存 和 数据类型 内存 销毁。
 *
 * 示例：
 * - 结构格式数据结束FFu(P群组Po);
 */
static VOID 结构格式数据结束FFu(格式数据类型Po P格式数据Po)
{
	if (P格式数据Po == NULL) return;
	for (size_t i = 0; i < P格式数据Po->群组数量; i++)
	{
		结构群组结束FFu(P格式数据Po->群组PoAr[i]);
		P格式数据Po->群组PoAr[i] = NULL;
	}
	P格式数据Po->群组数量 = 0;
	free(P格式数据Po);
}

/*----------------------------------------------------------------
文件：阴面{底层}
----------------------------------------------------------------*/

/**
 * @brief 读取文件输入字符。将字符转义后读取。
 * @param P文件Po 文件Po。
 * @return 字符。
 *
 * 注解：
 * - 将 文件输入字符 进行转换，返回转换后的字符。
 */
static int 文件字符读取FFu(FILE* P文件Po)
{
	int 字符 = fgetc(P文件Po);
	if (字符 == 翻译字符)
	{
		/*记录位置*/
		fpos_t 读取位置 = 0;
		if (fgetpos(P文件Po, &读取位置)) return EOF;
		/*读取下一字符*/
		if ((字符 = fgetc(P文件Po)) == EOF) return EOF;
		/*是否为转义字符*/
		switch (字符)
		{
		case 'a':/*响铃*/
			return '\a';
		case 'b':/*退格*/
			return '\b';
		case 't':/*垂直制表*/
			return '\t';
		case 'n':/*换行*/
			return '\n';
		case 'v':/*水平制表*/
			return '\v';
		case 'f':/*换页*/
			return '\f';
		case 'r':/*移至行首*/
			return '\r';
			/*翻译字符*/
		case 翻译字符:
			/*元素字符*/
		case 群组开始字符:
		case 群组结束字符:
		case 条目开始字符:
		case 条目结束字符:
		case 数据开始字符:
		case 数据结束字符:
		case 注释开始字符:
		case 注释结束字符:
			break;
		default:/*不是转义字符*/
			/*还原读取位置*/
			if (fsetpos(P文件Po, &读取位置)) return EOF;
			/*返回翻译字符*/
			return 翻译字符;
		}
	}
	return 字符;
}
/**
 * @brief 创建文件输入元素文本，并写入元素文本。
 * @param P文件Po 文件Po。
 * @param P结束字符 结束字符。
 * @param 文本PoPo 文本PoPo。
 * @return 成功返回：T；失败返回：F；
 *
 * 注解：
 * - 如果是文本为 ""，文本PoPo 则为 NULL。
 * - 结束需要使用 结束文本FFu 函数释放。
 */
static STATE 文件元素文本开始FFu(FILE* P文件Po, int P结束字符, 文本类型Po* P文本PoPo)
{
	if (P文件Po == NULL) return F;
	int 字符 = 0;
	文本类型Po 文本Po = NULL;
	/*获取文本长度*/
	DATAMAXI 文本长度 = 0;
	{
		fpos_t 文件位置 = 0;
		if (fgetpos(P文件Po, &文件位置)) return F;
		while ((字符 = fgetc(P文件Po)) != EOF)
		{
			if (字符 == 翻译字符)
			{/*两个字符增加一个长度*/
				字符 = fgetc(P文件Po);
				文本长度++;
				continue;
			}
			else if (字符 == P结束字符) break;
			文本长度++;
		}
		if (fsetpos(P文件Po, &文件位置)) return F;
	}
	if (文本长度 == 0)
		*P文本PoPo = NULL;
	else
	{
		/*创建内存*/
		if ((文本Po = 文本开始FFu(文本长度 + 1)) == NULL) return F;
		/*写入内存*/
		for (size_t i = 0; i < 文本长度; i++)
			文本Po[i] = 文件字符读取FFu(P文件Po);
		文本Po[文本长度] = 结束字符;
		*P文本PoPo = 文本Po;
	}
	return T;
}

/*----------------------------------------------------------------
元素：阳面{顶层}{增加没有同名结构，在结构中删除结构}
----------------------------------------------------------------*/

static STATE 群组删减FFu(格式数据类型Po* P格式数据PoPo, 群组类型Po P群组Po);
static STATE 条目删减FFu(群组类型Po* P群组PoPo, 条目类型Po P条目Po);
static STATE 数据删减FFu(条目类型Po* P条目PoPo, 数据类型Po P数据Po);

/**
 * @brief 在 格式数据 中增加 群组。
 * @param P格式数据PoPo 格式数据类型Po的Po。
 * @param P文本Po 条目文本。
 * @return 成功返回：增加的群组Po；失败返回：NULL；
 *
 * 如果 群组 重名，则返回 群组。
 * 如果 群组 分配失败，则 失败。
 * 如果 格式数据 分配失败，则 失败。
 * 如果 文本 为 NULL、""，则文本为 NULL。
 * 如果 文本 分配失败，则 失败。
 *
 */
static 群组类型Po 群组增加FFu(格式数据类型Po* P格式数据PoPo, const 文本类型Po P文本Po)
{
	if (P格式数据PoPo == NULL || *P格式数据PoPo == NULL) return NULL;
	群组类型Po 群组Po = 搜索群组FFu(*P格式数据PoPo, P文本Po);
	if (群组Po == NULL)
	{/*没有同名*/
		群组Po = 结构群组开始FFu();
		if (群组Po == NULL) return NULL;
		格式数据类型Po 格式数据Po = realloc(*P格式数据PoPo, sizeof(格式数据类型) + (sizeof(群组类型Po) * ((*P格式数据PoPo)->群组数量 + 1)));
		if (格式数据Po == NULL)
		{/*失败返回，原格式数据没有释放*/
			结构群组结束FFu(群组Po);
			return NULL;
		}
		*P格式数据PoPo = 格式数据Po;
		格式数据Po->群组数量++;
		格式数据Po->群组PoAr[格式数据Po->群组数量 - 1] = 群组Po;
		if (P文本Po == NULL) return 群组Po;
		DATAMAXI 文本长度 = strlen(P文本Po);
		if (文本长度 == 0) return 群组Po;
		文本类型Po 文本Po = 文本开始FFu(文本长度 + 1);
		if (文本Po == NULL)
		{
			群组删减FFu(P格式数据PoPo, 群组Po);
			return NULL;
		}
		strcpy(文本Po, P文本Po);
		群组Po->文本Po = 文本Po;
	}
	return 群组Po;
}
/**
 * @brief 在格式数据中删减群组。
 * @param P格式数据PoPo 格式数据类型Po的Po。
 * @param P群组Po 群组类型Po。
 * @return 成功返回：T；失败返回：F；
 *
 * 如果 群组 为 NULL，则 成功。
 * 如果 群组 不是 格式数据 的 群组，则 失败。
 * 如果 格式数据 分配失败，则 失败。
 *
 */
static STATE 群组删减FFu(格式数据类型Po* P格式数据PoPo, 群组类型Po P群组Po)
{
	if (P格式数据PoPo == NULL || *P格式数据PoPo == NULL) return F;
	if (P群组Po == NULL) return T;
	size_t 索引 = 0;
	{
		for (; 索引 < (*P格式数据PoPo)->群组数量; 索引++)
			if ((*P格式数据PoPo)->群组PoAr[索引] == P群组Po) break;
		if (索引 == (*P格式数据PoPo)->群组数量) return F;
	}
	结构群组结束FFu(P群组Po);
	/*将后方群组前移*/
	for (; 索引 < (*P格式数据PoPo)->群组数量 - 1; 索引++)
		(*P格式数据PoPo)->群组PoAr[索引] = (*P格式数据PoPo)->群组PoAr[索引 + 1];
	/*防止分配失败，提前进行置NULL*/
	(*P格式数据PoPo)->群组PoAr[索引] = NULL;
	/*重新分配内存*/
	格式数据类型Po 格式数据Po = realloc(*P格式数据PoPo, sizeof(格式数据类型) + (sizeof(群组类型Po) * ((*P格式数据PoPo)->群组数量 - 1)));
	if (格式数据Po == NULL) return F;
	*P格式数据PoPo = 格式数据Po;
	格式数据Po->群组数量--;
	return T;
}

/**
 * @brief 在条目中增加群组。
 * @param P格式数据Po 格式数据类型Po。
 * @param P群组PoPo 群组类型Po。
 * @param P文本Po 条目文本Po。
 * @return 成功返回：增加的条目Po；失败返回：NULL；
 *
 * 如果 条目 重名，则返回 条目。
 * 如果 条目 分配失败，则 失败。
 * 如果 群组 分配失败，则 失败。
 * 如果 文本 为 NULL、""，则文本为 NULL。
 * 如果 文本 分配失败，则 失败。
 *
 */
static 条目类型Po 条目增加FFu(格式数据类型Po P格式数据Po, 群组类型Po* P群组PoPo, const 文本类型Po P文本Po)
{
	if (P格式数据Po == NULL || P群组PoPo == NULL || *P群组PoPo == NULL) return NULL;
	/*搜索同名群组*/
	条目类型Po 条目Po = 搜索条目FFu(*P群组PoPo, P文本Po);
	if (条目Po == NULL)
	{/*没有同名*/
		/*判断 群组 是否 为格式数据中的群组*/
		{
			size_t i = 0;
			for (; i < P格式数据Po->群组数量; i++)
				if (P格式数据Po->群组PoAr[i] == *P群组PoPo) break;
			if (i == P格式数据Po->群组数量) return NULL;
		}
		/*创建条目*/
		条目Po = 结构条目开始FFu();
		if (条目Po == NULL) return NULL;
		群组类型Po 群组Po = realloc(*P群组PoPo, sizeof(群组类型) + (sizeof(条目类型Po) * ((*P群组PoPo)->条目数量 + 1)));
		if (群组Po == NULL)
		{/*失败返回，原群组没有释放*/
			结构条目结束FFu(条目Po);
			return NULL;
		}
		/*更新格式数据*/
		for (size_t i = 0; i < P格式数据Po->群组数量; i++)
			if (P格式数据Po->群组PoAr[i] == *P群组PoPo)
			{
				P格式数据Po->群组PoAr[i] = 群组Po;
				break;
			}
		/*更新群组*/
		*P群组PoPo = 群组Po;
		/*增加条目*/
		群组Po->条目数量++;
		群组Po->条目PoAr[群组Po->条目数量 - 1] = 条目Po;
		if (P文本Po == NULL) return 条目Po;
		DATAMAXI 文本长度 = strlen(P文本Po);
		if (文本长度 == 0) return 条目Po;
		文本类型Po 文本Po = 文本开始FFu(文本长度 + 1);
		if (文本Po == NULL)
		{
			条目删减FFu(P群组PoPo, 条目Po);
			return NULL;
		}
		strcpy(文本Po, P文本Po);
		条目Po->文本Po = 文本Po;
	}
	return 条目Po;
}
/**
 * @brief 在群组中删减条目。
 * @param P群组PoPo 群组类型Po的Po。
 * @param P条目Po 条目类型Po。
 * @return 成功返回：T；失败返回：F；
 *
 * 如果 条目 为 NULL，则 成功。
 * 如果 条目 不是 群组 的 条目，则 失败。
 * 如果 群组 分配失败，则 失败。
 *
 */
static STATE 条目删减FFu(群组类型Po* P群组PoPo, 条目类型Po P条目Po)
{
	if (P群组PoPo == NULL || *P群组PoPo == NULL) return F;
	if (P条目Po == NULL) return T;
	size_t 索引 = 0;
	{
		for (; 索引 < (*P群组PoPo)->条目数量; 索引++)
			if ((*P群组PoPo)->条目PoAr[索引] == P条目Po) break;
		if (索引 == (*P群组PoPo)->条目数量) return F;
	}
	结构条目结束FFu(P条目Po);
	/*将后方群组前移*/
	for (; 索引 < ((*P群组PoPo)->条目数量 - 1); 索引++)
		(*P群组PoPo)->条目PoAr[索引] = (*P群组PoPo)->条目PoAr[索引 + 1];
	/*防止分配失败，提前进行置NULL*/
	(*P群组PoPo)->条目PoAr[索引] = NULL;
	/*重新分配内存*/
	群组类型Po 群组Po = realloc(*P群组PoPo, sizeof(群组类型) + (sizeof(条目类型Po) * ((*P群组PoPo)->条目数量 - 1)));
	if (群组Po == NULL) return F;
	/*成功写入信息*/
	*P群组PoPo = 群组Po;
	群组Po->条目数量--;
	return T;
}

/**
 * @brief 在条目中增加数据。
 * @param P群组Po 群组Po。
 * @param P条目PoPo 条目类型Po的Po。
 * @param P文本Po 条目文本。
 * @return 成功返回：增加的数据Po；失败返回：NULL；
 *
 * 如果 数据 分配失败，则 失败。
 * 如果 条目 分配失败，则 失败。
 * 如果 文本 为 NULL、""，则文本为 NULL。
 * 如果 文本 分配失败，则 失败。
 *
 */
static 数据类型Po 数据增加FFu(群组类型Po P群组Po, 条目类型Po* P条目PoPo, const 文本类型Po P文本Po)
{
	if (P群组Po == NULL || P条目PoPo == NULL || *P条目PoPo == NULL) return NULL;
	/*判断 条目 是否 为 群组 中的 条目*/
	{
		size_t i = 0;
		for (; i < P群组Po->条目数量; i++)
			if (P群组Po->条目PoAr[i] == *P条目PoPo) break;
		if (i == P群组Po->条目数量) return NULL;
	}
	数据类型Po 数据Po = 结构数据开始FFu();
	if (数据Po == NULL) return NULL;
	条目类型Po 条目Po = realloc(*P条目PoPo, sizeof(条目类型) + (sizeof(数据类型Po) * ((*P条目PoPo)->数据数量 + 1)));
	if (条目Po == NULL)
	{/*失败返回，原条目没有释放*/
		结构数据结束FFu(数据Po);
		return NULL;
	}
	/*更新群组*/
	for (size_t i = 0; i < P群组Po->条目数量; i++)
		if (P群组Po->条目PoAr[i] == *P条目PoPo)
			P群组Po->条目PoAr[i] = 条目Po;
	/*更新条目*/
	*P条目PoPo = 条目Po;
	/*增加数据*/
	条目Po->数据数量++;
	条目Po->数据PoAr[条目Po->数据数量 - 1] = 数据Po;
	if (P文本Po == NULL) return 数据Po;
	DATAMAXI 文本长度 = strlen(P文本Po);
	if (文本长度 == 0) return 数据Po;
	文本类型Po 文本Po = 文本开始FFu(文本长度 + 1);
	if (文本Po == NULL)
	{
		数据删减FFu(P条目PoPo, 数据Po);
		return NULL;
	}
	strcpy(文本Po, P文本Po);
	数据Po->文本Po = 文本Po;
	return 数据Po;
}
/**
 * @brief 在条目中删减数据。
 * @param P条目PoPo 条目类型Po的Po。
 * @param P数据Po 数据类型Po。
 * @return 成功返回：T；失败返回：F；
 *
 * 如果 数据 为 NULL，则 成功。
 * 如果 数据 不是 条目 的 数据，则 失败。
 * 如果 条目 分配失败，则 失败。
 *
 */
static STATE 数据删减FFu(条目类型Po* P条目PoPo, 数据类型Po P数据Po)
{
	if (P条目PoPo == NULL || *P条目PoPo == NULL) return F;
	if (P数据Po == NULL) return T;
	size_t 索引 = 0;
	{
		for (; 索引 < (*P条目PoPo)->数据数量; 索引++)
			if ((*P条目PoPo)->数据PoAr[索引] == P数据Po) break;
		if (索引 == (*P条目PoPo)->数据数量) return F;
	}
	结构数据结束FFu(P数据Po);
	/*将后方数据前移*/
	for (; 索引 < ((*P条目PoPo)->数据数量 - 1); 索引++)
		(*P条目PoPo)->数据PoAr[索引] = (*P条目PoPo)->数据PoAr[索引 + 1];
	/*防止分配失败，提前进行置NULL*/
	(*P条目PoPo)->数据PoAr[索引] = NULL;
	/*重新分配内存*/
	条目类型Po 条目Po = realloc(*P条目PoPo, sizeof(条目类型) + (sizeof(数据类型Po) * ((*P条目PoPo)->数据数量 - 1)));
	if (条目Po == NULL) return F;
	/*成功写入信息*/
	*P条目PoPo = 条目Po;
	条目Po->数据数量--;
	return T;
}

/*----------------------------------------------------------------
结构：阳面{顶层}
----------------------------------------------------------------*/

/**
 * @brief 通过格式文本，寻找并返回群组。
 * @param P格式数据Po 格式数据类型Po。
 * @param P格式文本Po 格式文本Po。
 * @return 成功返回：数据Po；失败返回：NULL；
 */
static 群组类型Po 结构群组读取FFu(const 格式数据类型Po P格式数据Po, const 文本类型Po P格式文本Po)
{
	if (P格式数据Po == NULL || P格式文本Po == NULL) return NULL;
	格式文本类型Po 格式文本信息Po = 格式文本开始FFu(P格式文本Po);
	if (格式文本信息Po == NULL) return NULL;
	群组类型Po 群组Po = 搜索群组FFu(P格式数据Po, 格式文本信息Po->群组文本Po);
	格式文本结束FFu(格式文本信息Po);
	if (群组Po == NULL) return NULL;
	return 群组Po;
}
/**
 * @brief 通过格式文本，寻找并返回条目。
 * @param P格式数据Po 格式数据类型Po。
 * @param P格式文本Po 格式文本Po。
 * @return 成功返回：数据Po；失败返回：NULL；
 */
static 条目类型Po 结构条目读取FFu(const 格式数据类型Po P格式数据Po, const 文本类型Po P格式文本Po)
{
	if (P格式数据Po == NULL || P格式文本Po == NULL) return NULL;
	格式文本类型Po 格式文本信息Po = 格式文本开始FFu(P格式文本Po);
	if (格式文本信息Po == NULL) return NULL;
	条目类型Po 条目Po = NULL;
	{
		/*寻找群组*/
		群组类型Po 群组Po = 搜索群组FFu(P格式数据Po, 格式文本信息Po->群组文本Po);
		if (群组Po == NULL) goto Error;
		/*寻找条目*/
		条目Po = 搜索条目FFu(群组Po, 格式文本信息Po->条目文本Po);
		if (条目Po == NULL) goto Error;
	}
	格式文本结束FFu(格式文本信息Po);
	return 条目Po;
Error:
	{
		格式文本结束FFu(格式文本信息Po);
		return NULL;
	}
}
/**
 * @brief 通过格式文本，寻找并返回数据。
 * @param P格式数据Po 格式数据类型Po。
 * @param P格式文本Po 格式文本Po。
 * @return 成功返回：数据Po；失败返回：NULL；
 */
static 数据类型Po 结构数据读取FFu(const 格式数据类型Po P格式数据Po, const 文本类型Po P格式文本Po)
{
	if (P格式数据Po == NULL || P格式文本Po == NULL) return NULL;
	格式文本类型Po 格式文本信息Po = 格式文本开始FFu(P格式文本Po);
	if (格式文本信息Po == NULL) return NULL;
	数据类型Po 数据Po = NULL;
	{
		/*寻找群组*/
		群组类型Po 群组Po = 搜索群组FFu(P格式数据Po, 格式文本信息Po->群组文本Po);
		if (群组Po == NULL) goto Error;
		/*寻找条目*/
		条目类型Po 条目Po = 搜索条目FFu(群组Po, 格式文本信息Po->条目文本Po);
		if (条目Po == NULL) goto Error;
		if (条目Po->数据数量 < 格式文本信息Po->数据标识) goto Error;
		数据Po = 条目Po->数据PoAr[格式文本信息Po->数据标识];
	}
	格式文本结束FFu(格式文本信息Po);
	return 数据Po;
Error:
	{
		格式文本结束FFu(格式文本信息Po);
		return NULL;
	}
}

/*----------------------------------------------------------------
文件：阳面{底层}
----------------------------------------------------------------*/

/**
 * @brief 读取文件写入结构数据。
 * @param P格式数据PoPo 格式数据类型Po。
 * @param P文件名称Po 文件名称Po。
 * @return 成功返回：T；失败返回：F。
 *
 * 可以将一个已经拥有数据的格式数据传入，将文件内容和格式数据的数据合并成一个格式数据。
 *
 */
static STATE 文件读取FFu(格式数据类型Po* P格式数据PoPo, const 文本类型Po P文件名称Po)
{
	if (P文件名称Po == NULL || P格式数据PoPo == NULL || *P格式数据PoPo == NULL) return F;
	const FILE* 文件Po = fopen(P文件名称Po, "r");
	if (文件Po == NULL) return F;
	/*读取文件*/
	{
		群组类型Po 群组Po = NULL;
		条目类型Po 条目Po = NULL;
		数据类型Po 数据Po = NULL;
		/*当前字符*/
		int 字符 = 0;
		while ((字符 = fgetc(文件Po)) != EOF)
		{
			/*解析符号*/
			switch (字符)
			{
			case 群组开始字符:
			{
				/*创建读取群组文本*/
				文本类型Po 文本Po = NULL;
				if (文件元素文本开始FFu(文件Po, 群组结束字符, &文本Po) == F) goto Error;
				群组Po = 群组增加FFu(P格式数据PoPo, 文本Po);
				文本结束FFu(文本Po);
				if (群组Po == NULL) goto Error;
				/*清除关系*/
				条目Po = NULL;
				数据Po = NULL;
			}
			break;
			case 条目开始字符:
			{
				/*创建群组*/
				if (群组Po == NULL)
					群组Po = 群组增加FFu(P格式数据PoPo, NULL);
				if (群组Po == NULL) goto Error;
				/*创建条目*/
				文本类型Po 文本Po = NULL;
				if (文件元素文本开始FFu(文件Po, 条目结束字符, &文本Po) == F) goto Error;
				条目Po = 条目增加FFu(*P格式数据PoPo, &群组Po, 文本Po);
				文本结束FFu(文本Po);
				if (条目Po == NULL) goto Error;
				/*清除关系*/
				数据Po = NULL;
			}
			break;
			case 数据开始字符:
			{
				/*创建群组、条目*/
				if (条目Po == NULL)
				{
					/*创建群组*/
					if (群组Po == NULL)
						群组Po = 群组增加FFu(P格式数据PoPo, NULL);
					if (群组Po == NULL) goto Error;
					/*创建条目*/
					条目Po = 条目增加FFu(*P格式数据PoPo, &群组Po, NULL);
					if (条目Po == NULL) goto Error;
				}
				/*创建数据*/
				文本类型Po 文本Po = NULL;
				if (文件元素文本开始FFu(文件Po, 数据结束字符, &文本Po) == F) goto Error;
				数据Po = 数据增加FFu(群组Po, &条目Po, 文本Po);
				文本结束FFu(文本Po);
				if (数据Po == NULL) goto Error;
			}
			break;
			case 注释开始字符:
			{
				fpos_t 文件位置 = 0;
				if (fgetpos(文件Po, &文件位置)) goto Error;
				if ((字符 = fgetc(文件Po)) == EOF) goto Error;
				switch (字符)
				{
				case 群组开始字符:
				{
					if (群组Po == NULL) break;
					if (群组Po->注释Po != NULL) break;
					文本类型Po 注释文本Po = NULL;
					if (文件元素文本开始FFu(文件Po, 群组结束字符, &注释文本Po) == F) goto Error;
					群组Po->注释Po = 注释文本Po;
				}
				break;
				case 条目开始字符:
				{
					if (条目Po == NULL) break;
					if (条目Po->注释Po != NULL) break;
					文本类型Po 注释文本Po = NULL;
					if (文件元素文本开始FFu(文件Po, 条目结束字符, &注释文本Po) == F) goto Error;
					条目Po->注释Po = 注释文本Po;
				}
				break;
				case 数据开始字符:
				{
					if (数据Po == NULL) break;
					if (数据Po->注释Po != NULL) break;
					文本类型Po 注释文本Po = NULL;
					if (文件元素文本开始FFu(文件Po, 数据结束字符, &注释文本Po) == F) goto Error;
					数据Po->注释Po = 注释文本Po;
				}
				break;
				default:
					if (fsetpos(文件Po, &文件位置) != 0) goto Error;
					break;
				}
			}
			break;
			default:
				break;
			}
		}
		if (字符 != EOF) goto Error;
	}
	fclose(文件Po);
	return T;
Error:
	{
		fclose(文件Po);
		/*创建空格式数据*/
		/*格式数据重新创建
		结构格式数据结束FFu(*P格式数据PoPo);
		*P格式数据PoPo = 结构格式数据开始FFu();
		*/
		return F;
	}
}
/**
 * @brief 读取结构数据写入文件。
 * @param P格式数据PoPo 格式数据类型Po。
 * @param P文件名称Po 文件名称Po。
 * @return 成功返回：T；失败返回：F。
 */
static STATE 文件写入FFu(const 格式数据类型Po P格式数据PoPo, const 文本类型Po P文件名称Po)
{
	if (P格式数据PoPo == NULL || P文件名称Po == NULL) return F;
	/*打开文件*/
	const FILE* 文件Po = fopen(P文件名称Po, "w");
	if (文件Po == NULL) return F;
	for (size_t i = 0; i < P格式数据PoPo->群组数量; i++)
	{/*群组循环*/
		if (P格式数据PoPo->群组PoAr[i]->文本Po == NULL);//fprintf(文件Po, 群组文本());
		else fprintf(文件Po, 群组文本("%s"), P格式数据PoPo->群组PoAr[i]->文本Po);
		if (P格式数据PoPo->群组PoAr[i]->注释Po == NULL);//fprintf(文件Po, 群组注释());
		else fprintf(文件Po, 群组注释("%s"), P格式数据PoPo->群组PoAr[i]->注释Po);
		fprintf(文件Po, "\n");
		for (size_t j = 0; j < P格式数据PoPo->群组PoAr[i]->条目数量; j++)
		{
			if (P格式数据PoPo->群组PoAr[i]->条目PoAr[j]->文本Po == NULL);//fprintf(文件Po, 条目文本());
			else fprintf(文件Po, 条目文本("%s"), P格式数据PoPo->群组PoAr[i]->条目PoAr[j]->文本Po);
			if (P格式数据PoPo->群组PoAr[i]->条目PoAr[j]->注释Po == NULL);//fprintf(文件Po, 条目注释());
			else fprintf(文件Po, 条目注释("%s"), P格式数据PoPo->群组PoAr[i]->条目PoAr[j]->注释Po);
			fprintf(文件Po, "\n");
			for (size_t k = 0; k < P格式数据PoPo->群组PoAr[i]->条目PoAr[j]->数据数量; k++)
			{
				if (P格式数据PoPo->群组PoAr[i]->条目PoAr[j]->数据PoAr[k]->文本Po == NULL);//fprintf(文件Po, 数据文本());
				else fprintf(文件Po, 数据文本("%s"), P格式数据PoPo->群组PoAr[i]->条目PoAr[j]->数据PoAr[k]->文本Po);
				if (P格式数据PoPo->群组PoAr[i]->条目PoAr[j]->数据PoAr[k]->注释Po == NULL);//fprintf(文件Po, 数据注释());
				else fprintf(文件Po, 数据注释("%s"), P格式数据PoPo->群组PoAr[i]->条目PoAr[j]->数据PoAr[k]->注释Po);
				fprintf(文件Po, "\n");
			}
		}
	}
	fclose(文件Po);
	return T;
}




/*----------------------------------------------------------------
接口函数
*/

/*----------------------------------------------------------------
* 格式数据：阴面{底层}
----------------------------------------------------------------*/

/**
 * @brief 格式数据结构开始。
 * @return 成功返回：格式数据结构Po；失败返回：NULL。
 *
 * 注解：
 * - 结束需要使用 ZHFD_FDEnd_PFu 函数释放。
 *
 * 示例：
 * - ZHFDStPo ZHFDPo = ZHFD_FDStart_PFu();
 */
extern ZHFDStPo ZHFD_FDStart_PFu(void)
{
	return 结构格式数据开始FFu();
}
/**
 * @brief 格式数据结构结束。
 * @param PFDPo 格式数据结构Po。
 *
 * 注解：
 * - 函数释放 ZHFDSt 内存。
 *
 * 示例：
 * - ZHFD_FDEnd_PFu(ZHFDSt);
 */
extern void ZHFD_FDEnd_PFu(_PA_IN_ ZHFDStPo PFDPo)
{
	结构格式数据结束FFu(PFDPo);
	return;
}

/*----------------------------------------------------------------
* 文件读写：阴面{底层}
----------------------------------------------------------------*/

/**
 * @brief 格式数据写入文件。
 * @param PFDPo 格式数据结构Po。
 * @param PFileNamePo 文件名称。
 * @return 成功返回：0；失败返回：1。
 *
 * 注解：
 * - 函数将 格式数据 写入 文件。
 *
 * 示例：
 * - if(ZHFD_FDFWrite_FFu(PFDPo,PFileNamePo)) //Error;
 */
extern uint8_t ZHFD_FDFWrite_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFileNamePo)
{
	return 文件写入FFu(PFDPo, PFileNamePo) == F ? 1 : 0;
}
/**
 * @brief 文件写入格式数据。
 * @param PFDPoPo 格式数据结构Po的Po。
 * @param PFileNamePo 文件名称。
 * @return 成功返回：0；失败返回：1。
 *
 * 注解：
 * - 函数将 文件 写入 格式数据。
 * - 函数失败 PFDPo 可能会被破坏。
 *
 * 示例：
 * - if(ZHFD_FDFRead_FFu(&PFDPo,PFileNamePo)) //Error;
 */
extern uint8_t ZHFD_FDFRead_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFileNamePo)
{
	return 文件读取FFu(PFDPoPo, PFileNamePo) == F ? 1 : 0;
}

/*----------------------------------------------------------------
* 元素：阴面{底层}
----------------------------------------------------------------*/

/**
 * @brief 开始群组。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PTextPo 文本Po。
 * @param PCommentPo 注释文本Po。
 * @return 成功返回：0；失败返回：!0；
 *
 * 用于创建群组，写入文本、注释信息。
 * 如果有同文本群组，并且有注释，则将新注释写入群组。
 *
 */
extern uint8_t ZHFD_FDGroupStart_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PTextPo, _PA_IN_ const char* PCommentPo)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL) return 1;
	群组类型Po 群组Po = 群组增加FFu(PFDPoPo, PTextPo);
	if (群组Po == NULL) return 1;
	if (PCommentPo != NULL)
	{
		DATAMAXI 文本长度 = strlen(PCommentPo);
		if (文本长度 == 0) return 0;
		文本类型Po 注释Po = 文本开始FFu(文本长度 + 1);
		if (注释Po == NULL)
		{
			群组删减FFu(PFDPoPo, 群组Po);
			return 1;
		}
		strcpy(注释Po, PCommentPo);
		群组Po->注释Po = 注释Po;
	}
	return 0;
}
/**
 * @brief 结束群组。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PFormatTextPo 格式文本Po。
 * @return 成功返回：0；失败返回：!0；
 */
extern uint8_t ZHFD_FDGroupEnd_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL || PFormatTextPo == NULL) return 1;
	格式文本类型Po 格式文本信息Po = 格式文本开始FFu(PFormatTextPo);
	if (格式文本信息Po == NULL) return 1;
	群组类型Po 群组Po = 搜索群组FFu(*PFDPoPo, 格式文本信息Po->群组文本Po);
	格式文本结束FFu(格式文本信息Po);
	if (群组Po == NULL) return 1;
	if (群组删减FFu(PFDPoPo, 群组Po) == F) return 1;
	return 0;
}

/**
 * @brief 开始条目。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PFormatTextPo 格式文本Po。
 * @param PTextPo 文本Po。
 * @param PCommentPo 注释文本Po。
 * @return 成功返回：0；失败返回：!0；
 */
extern uint8_t ZHFD_FDItemStart_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const char* PTextPo, _PA_IN_ const char* PCommentPo)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL || PFormatTextPo == NULL) return 1;
	格式文本类型Po 格式文本信息Po = 格式文本开始FFu(PFormatTextPo);
	if (格式文本信息Po == NULL) return 1;
	群组类型Po 群组Po = 群组增加FFu(PFDPoPo, 格式文本信息Po->群组文本Po);
	格式文本结束FFu(格式文本信息Po);
	if (群组Po == NULL) return 1;
	条目类型Po 条目Po = 条目增加FFu(*PFDPoPo, &群组Po, PTextPo);
	if (条目Po == NULL)
	{
		群组删减FFu(PFDPoPo, 群组Po);
		return 1;
	}
	if (PCommentPo != NULL)
	{
		DATAMAXI 文本长度 = strlen(PCommentPo);
		if (文本长度 == 0) return 0;
		文本类型Po 注释Po = 文本开始FFu(文本长度 + 1);
		if (注释Po == NULL)
		{
			条目删减FFu(&群组Po, 条目Po);
			群组删减FFu(PFDPoPo, 群组Po);
			return 1;
		}
		strcpy(注释Po, PCommentPo);
		条目Po->注释Po = 注释Po;
	}
	return 0;
}
/**
 * @brief 结束条目。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PFormatTextPo 格式文本Po。
 * @return 成功返回：0；失败返回：!0；
 *
 * 如果群组内没有目标条目，则返回成功。
 *
 */
extern uint8_t ZHFD_FDItemEnd_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL || PFormatTextPo == NULL) return 1;
	格式文本类型Po 格式文本信息Po = 格式文本开始FFu(PFormatTextPo);
	if (格式文本信息Po == NULL) return 1;
	群组类型Po 群组Po = 搜索群组FFu(*PFDPoPo, 格式文本信息Po->群组文本Po);
	if (群组Po == NULL) goto Error;
	条目类型Po 条目Po = 搜索条目FFu(群组Po, 格式文本信息Po->条目文本Po);
	if (条目Po != NULL)
		if (条目删减FFu(&群组Po, 条目Po) == F) goto Error;
	格式文本结束FFu(格式文本信息Po);
	return 0;
Error:
	格式文本结束FFu(格式文本信息Po);
	return 1;
}

/**
 * @brief 开始数据。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PFormatTextPo 格式文本Po。
 * @param PTextPo 文本Po。
 * @param PCommentPo 注释文本Po。
 * @return 成功返回：0；失败返回：!0；
 */
extern uint8_t ZHFD_FDDataStart_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const char* PTextPo, _PA_IN_ const char* PCommentPo)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL || PFormatTextPo == NULL || PTextPo == NULL || PCommentPo == NULL) return 1;
	格式文本类型Po 格式文本信息Po = 格式文本开始FFu(PFormatTextPo);
	if (格式文本信息Po == NULL) return 1;
	群组类型Po 群组Po = 群组增加FFu(PFDPoPo, 格式文本信息Po->群组文本Po);
	if (群组Po == NULL)
	{
		格式文本结束FFu(格式文本信息Po);
		return 1;
	}
	条目类型Po 条目Po = 条目增加FFu(*PFDPoPo, &群组Po, 格式文本信息Po->条目文本Po);
	if (条目Po == NULL)
	{
		格式文本结束FFu(格式文本信息Po);
		return 1;
	}
	格式文本结束FFu(格式文本信息Po);
	数据类型Po 数据Po = 数据增加FFu(群组Po, &条目Po, PTextPo);
	if (PCommentPo != NULL)
	{
		DATAMAXI 文本长度 = strlen(PCommentPo);
		if (文本长度 == 0) return 0;
		文本类型Po 注释Po = 文本开始FFu(文本长度 + 1);
		if (注释Po == NULL)
		{
			数据删减FFu(&条目Po, 数据Po);
			条目删减FFu(&群组Po, 条目Po);
			群组删减FFu(PFDPoPo, 群组Po);
			return 1;
		}
		strcpy(注释Po, PCommentPo);
		数据Po->注释Po = 注释Po;
	}
	return 0;
}
/**
 * @brief 结束数据。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PFormatTextPo 格式文本Po。
 * @return 成功返回：0；失败返回：!0；
 */
extern uint8_t ZHFD_FDDataEnd_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL || PFormatTextPo == NULL) return 1;
	格式文本类型Po 格式文本信息Po = 格式文本开始FFu(PFormatTextPo);
	if (格式文本信息Po == NULL) return 1;
	群组类型Po 群组Po = 搜索群组FFu(*PFDPoPo, 格式文本信息Po->群组文本Po);
	if (群组Po == NULL) goto Error;
	条目类型Po 条目Po = 搜索条目FFu(群组Po, 格式文本信息Po->条目文本Po);
	if (条目Po == NULL) goto Error;
	数据删减FFu(&条目Po, 条目Po->数据PoAr[格式文本信息Po->数据标识]);
	格式文本结束FFu(格式文本信息Po);
	return 0;
Error:
	格式文本结束FFu(格式文本信息Po);
	return 1;
}

/*----------------------------------------------------------------
* 元素读写：阴面{底层}
----------------------------------------------------------------*/

/**
 * @brief 群组写入。
 * @param PFDPo 格式数据Po。
 * @param PFormatTextPo 格式文本Po。
 * @param PTextPo 文本Po。
 * @param PCommentPo 注释文本Po。
 * @return 成功返回：0；失败返回：!0；
 *
 * 在群组中写入新的信息。
 * PTextPo 或 PCommentPo 如果为 NULL 则不改变。
 * PTextPo 或 PCommentPo 如果为 ""，则改为 NULL。
 * PTextPo 或 PCommentPo 如果不为 NULL 或 ""，复制文本到群组。
 * 如果重名，则返回失败。
 * 此函数失败可能会导致群组结构错误。
 *
 */
extern uint8_t ZHFD_FDGroupWrite_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ char* PTextPo, _PA_IN_ char* PCommentPo)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	/*重名返回失败*/
	if (搜索群组FFu(PFDPo, PTextPo) != NULL) return 1;
	格式文本类型Po 格式文本信息Po = 格式文本开始FFu(PFormatTextPo);
	if (格式文本信息Po == NULL) return 1;
	群组类型Po 群组Po = 搜索群组FFu(PFDPo, 格式文本信息Po->群组文本Po);
	格式文本结束FFu(格式文本信息Po);
	if (群组Po == NULL) return 1;
	/*文本*/
	if (PTextPo == NULL)
		/*NULL，则不变*/;
	else if (文本比较FFu(PTextPo, 空白文本, F) == F)
		/*""，则清空文本*/
		文本结束FFu(群组Po->文本Po);
	else
	{/*复制文本*/
		DATAMAXI 文本长度 = strlen(PTextPo);
		文本类型Po 文本Po = 文本开始FFu(文本长度 + 1);
		if (文本Po == NULL) return 1;
		strcpy(文本Po, PTextPo);
		文本结束FFu(群组Po->文本Po);
		群组Po->文本Po = 文本Po;
	}
	/*注释*/
	if (PCommentPo == NULL)
		/*NULL，则不变*/;
	else if (文本比较FFu(PCommentPo, 空白文本, F) == F)
		/*""，则清空文本*/
		文本结束FFu(群组Po->注释Po);
	else
	{/*复制文本*/
		DATAMAXI 文本长度 = strlen(PCommentPo);
		文本类型Po 注释Po = 文本开始FFu(文本长度 + 1);
		if (注释Po == NULL) return 1;
		strcpy(注释Po, PCommentPo);
		文本结束FFu(群组Po->注释Po);
		群组Po->注释Po = 注释Po;
	}
	return 0;
}
/**
 * @brief 群组读取。
 * @param PFDPo 格式数据Po。
 * @param PFormatTextPo 格式文本Po。
 * @param PTextPo 文本Po。
 * @param PTextBA 文本字节数量。
 * @param PCommentPo 注释文本Po。
 * @param PCommentBA 注释字节数量。
 * @return 成功返回：0；失败返回：!0；
 */
extern uint8_t ZHFD_FDGroupRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo,
	_PA_OUT_ char* PTextPo, _PA_IN_OUT_ size_t* PTextBA, _PA_OUT_ char* PCommentPo, _PA_IN_OUT_ size_t* PCommentBA)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	if (PTextPo != NULL && *PTextBA == 0) return 1;
	if (PCommentPo != NULL && *PCommentBA == 0) return 1;
	格式文本类型Po 格式文本信息Po = 格式文本开始FFu(PFormatTextPo);
	if (格式文本信息Po == NULL) return 1;
	群组类型Po 群组Po = 搜索群组FFu(PFDPo, 格式文本信息Po->群组文本Po);
	格式文本结束FFu(格式文本信息Po);
	if (群组Po == NULL) return 1;
	if (PTextPo != NULL && 群组Po->文本Po != NULL)
	{
		DATAMAXI 文本BA = strlen(群组Po->文本Po) + 1;
		if (文本BA > *PTextBA) goto Error;
		strcpy(PTextPo, 群组Po->文本Po);
	}
	if (PCommentPo != NULL && 群组Po->注释Po != NULL)
	{
		DATAMAXI 文本BA = strlen(群组Po->注释Po) + 1;
		if (文本BA > *PCommentBA) goto Error;
		strcpy(PCommentPo, 群组Po->注释Po);
	}
	return 0;
Error:
	if (群组Po->文本Po != NULL)
		*PTextBA = strlen(群组Po->文本Po) + 1;
	if (群组Po->注释Po != NULL)
		*PCommentBA = strlen(群组Po->注释Po) + 1;
	return 1;
}

/**
 * @brief 条目写入。
 * @param PFDPo 格式数据Po。
 * @param PFormatTextPo 格式文本Po。
 * @param PTextPo 文本Po。
 * @param PCommentPo 注释文本Po。
 * @return 成功返回：0；失败返回：!0；
 *
 * 在条目中写入新的信息。
 * PTextPo 或 PCommentPo 如果为 NULL 则不改变。
 * PTextPo 或 PCommentPo 如果为 ""，则改为 NULL。
 * PTextPo 或 PCommentPo 如果不为 NULL 或 ""，复制文本到条目。
 * 如果重名，则返回失败。
 * 此函数失败可能会导致条目结构错误。
 *
 */
extern uint8_t ZHFD_FDItemWrite_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ char* PTextPo, _PA_IN_ char* PCommentPo)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	/*重名返回失败*/
	if (搜索条目FFu(PFDPo, PTextPo) != NULL) return 1;
	格式文本类型Po 格式文本信息Po = 格式文本开始FFu(PFormatTextPo);
	if (格式文本信息Po == NULL) return 1;
	群组类型Po 群组Po = 搜索群组FFu(PFDPo, 格式文本信息Po->群组文本Po);
	if (群组Po == NULL)
	{
		格式文本结束FFu(格式文本信息Po);
		return 1;
	}
	条目类型Po 条目Po = 搜索条目FFu(群组Po, 格式文本信息Po->条目文本Po);
	格式文本结束FFu(格式文本信息Po);
	if (条目Po == NULL) return 1;
	/*文本*/
	if (PTextPo == NULL)
		/*NULL，则不变*/;
	else if (文本比较FFu(PTextPo, 空白文本, F) == F)
		/*""，则清空文本*/
		文本结束FFu(条目Po->文本Po);
	else
	{/*复制文本*/
		DATAMAXI 文本长度 = strlen(PTextPo);
		文本类型Po 文本Po = 文本开始FFu(文本长度 + 1);
		if (文本Po == NULL) return 1;
		strcpy(文本Po, PTextPo);
		文本结束FFu(条目Po->文本Po);
		条目Po->文本Po = 文本Po;
	}
	/*注释*/
	if (PCommentPo == NULL)
		/*NULL，则不变*/;
	else if (文本比较FFu(PCommentPo, 空白文本, F) == F)
		/*""，则清空文本*/
		文本结束FFu(条目Po->注释Po);
	else
	{/*复制文本*/
		DATAMAXI 文本长度 = strlen(PCommentPo);
		文本类型Po 注释Po = 文本开始FFu(文本长度 + 1);
		if (注释Po == NULL) return 1;
		strcpy(注释Po, PCommentPo);
		文本结束FFu(条目Po->注释Po);
		条目Po->注释Po = 注释Po;
	}
	return 0;
}
/**
 * @brief 条目读取。
 * @param PFDPo 格式数据Po。
 * @param PFormatTextPo 格式文本Po。
 * @param PTextPo 文本Po。
 * @param PTextBA 文本字节数量。
 * @param PCommentPo 注释文本Po。
 * @param PCommentBA 注释字节数量。
 * @return 成功返回：0；失败返回：!0；
 */
extern uint8_t ZHFD_FDItemRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo,
	_PA_OUT_ char* PTextPo, _PA_IN_OUT_ size_t* PTextBA, _PA_OUT_ char* PCommentPo, _PA_IN_OUT_ size_t* PCommentBA)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	if (PTextPo != NULL && *PTextBA == 0) return 1;
	if (PCommentPo != NULL && *PCommentBA == 0) return 1;
	格式文本类型Po 格式文本信息Po = 格式文本开始FFu(PFormatTextPo);
	if (格式文本信息Po == NULL) return 1;
	群组类型Po 群组Po = 搜索群组FFu(PFDPo, 格式文本信息Po->群组文本Po);
	if (群组Po == NULL)
	{
		格式文本结束FFu(格式文本信息Po);
		return 1;
	}
	条目类型Po 条目Po = 搜索条目FFu(群组Po, 格式文本信息Po->条目文本Po);
	格式文本结束FFu(格式文本信息Po);
	if (PTextPo != NULL && 条目Po->文本Po != NULL)
	{
		DATAMAXI 文本BA = strlen(条目Po->文本Po) + 1;
		if (文本BA > *PTextBA) goto Error;
		strcpy(PTextPo, 条目Po->文本Po);
	}
	if (PCommentPo != NULL && 条目Po->注释Po != NULL)
	{
		DATAMAXI 文本BA = strlen(条目Po->注释Po) + 1;
		if (文本BA > *PCommentBA) goto Error;
		strcpy(PCommentPo, 条目Po->注释Po);
	}
	return 0;
Error:
	if (条目Po->文本Po != NULL)
		*PTextBA = strlen(条目Po->文本Po) + 1;
	if (条目Po->注释Po != NULL)
		*PCommentBA = strlen(条目Po->注释Po) + 1;
	return 1;
}

/**
 * @brief 数据写入。
 * @param PFDPo 格式数据Po。
 * @param PFormatTextPo 格式文本Po。
 * @param PTextPo 文本Po。
 * @param PCommentPo 注释文本Po。
 * @return 成功返回：0；失败返回：!0；
 *
 * 在数据中写入新的信息。
 * PTextPo 或 PCommentPo 如果为 NULL 则不改变。
 * PTextPo 或 PCommentPo 如果为 ""，则改为 NULL。
 * PTextPo 或 PCommentPo 如果不为 NULL 或 ""，复制文本到数据。
 * 如果重名，则返回失败。
 * 此函数失败可能会导致数据结构错误。
 *
 */
extern uint8_t ZHFD_FDDataWrite_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ char* PTextPo, _PA_IN_ char* PCommentPo)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	格式文本类型Po 格式文本信息Po = 格式文本开始FFu(PFormatTextPo);
	if (格式文本信息Po == NULL) return 1;
	群组类型Po 群组Po = 搜索群组FFu(PFDPo, 格式文本信息Po->群组文本Po);
	if (群组Po == NULL)
	{
		格式文本结束FFu(格式文本信息Po);
		return 1;
	}
	条目类型Po 条目Po = 搜索条目FFu(群组Po, 格式文本信息Po->条目文本Po);
	DATAMAXI 数据索引 = 格式文本信息Po->数据标识;
	格式文本结束FFu(格式文本信息Po);
	if (条目Po == NULL) return 1;
	/*文本*/
	if (PTextPo == NULL)
		/*NULL，则不变*/;
	else if (文本比较FFu(PTextPo, 空白文本, F) == F)
		/*""，则清空文本*/
		文本结束FFu(条目Po->数据PoAr[数据索引]->文本Po);
	else
	{/*复制文本*/
		DATAMAXI 文本长度 = strlen(PTextPo);
		文本类型Po 文本Po = 文本开始FFu(文本长度 + 1);
		if (文本Po == NULL) return 1;
		strcpy(文本Po, PTextPo);
		文本结束FFu(条目Po->数据PoAr[数据索引]->文本Po);
		条目Po->数据PoAr[数据索引]->文本Po = 文本Po;
	}
	/*注释*/
	if (PCommentPo == NULL)
		/*NULL，则不变*/;
	else if (文本比较FFu(PCommentPo, 空白文本, F) == F)
		/*""，则清空文本*/
		文本结束FFu(条目Po->数据PoAr[数据索引]->注释Po);
	else
	{/*复制文本*/
		DATAMAXI 文本长度 = strlen(PCommentPo);
		文本类型Po 注释Po = 文本开始FFu(文本长度 + 1);
		if (注释Po == NULL) return 1;
		strcpy(注释Po, PCommentPo);
		文本结束FFu(条目Po->数据PoAr[数据索引]->注释Po);
		条目Po->数据PoAr[数据索引]->注释Po = 注释Po;
	}
	return 0;
}
/**
 * @brief 数据读取。
 * @param PFDPo 格式数据Po。
 * @param PFormatTextPo 格式文本Po。
 * @param PTextPo 文本Po。
 * @param PTextBA 文本字节数量。
 * @param PCommentPo 注释文本Po。
 * @param PCommentBA 注释字节数量。
 * @return 成功返回：0；失败返回：!0；
 */
extern uint8_t ZHFD_FDDataRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo,
	_PA_OUT_ char* PTextPo, _PA_IN_OUT_ size_t* PTextBA, _PA_OUT_ char* PCommentPo, _PA_IN_OUT_ size_t* PCommentBA)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	if (PTextPo != NULL && *PTextBA == 0) return 1;
	if (PCommentPo != NULL && *PCommentBA == 0) return 1;
	格式文本类型Po 格式文本信息Po = 格式文本开始FFu(PFormatTextPo);
	if (格式文本信息Po == NULL) return 1;
	群组类型Po 群组Po = 搜索群组FFu(PFDPo, 格式文本信息Po->群组文本Po);
	if (群组Po == NULL) return 1;
	条目类型Po 条目Po = 搜索条目FFu(群组Po, 格式文本信息Po->条目文本Po);
	if (条目Po == NULL) return 1;
	DATAMAXI 编号 = 格式文本信息Po->数据标识;
	格式文本结束FFu(格式文本信息Po);
	if (PTextPo != NULL && 条目Po->数据PoAr[编号]->文本Po != NULL)
	{
		DATAMAXI 文本BA = strlen(条目Po->数据PoAr[编号]->文本Po) + 1;
		if (文本BA > *PTextBA) goto Error;
		strcpy(PTextPo, 条目Po->数据PoAr[编号]->文本Po);
	}
	if (PCommentPo != NULL && 条目Po->数据PoAr[编号]->注释Po != NULL)
	{
		DATAMAXI 文本BA = strlen(条目Po->数据PoAr[编号]->注释Po) + 1;
		if (文本BA > *PCommentBA) goto Error;
		strcpy(PCommentPo, 条目Po->数据PoAr[编号]->注释Po);
	}
	return 0;
Error:
	if (条目Po->数据PoAr[编号]->文本Po != NULL)
		*PTextBA = strlen(条目Po->数据PoAr[编号]->文本Po) + 1;
	if (条目Po->数据PoAr[编号]->注释Po != NULL)
		*PCommentBA = strlen(条目Po->数据PoAr[编号]->注释Po) + 1;
	return 1;
}

/*----------------------------------------------------------------
* 数据：阳面{顶层}
----------------------------------------------------------------*/

/**
 * @brief 数据文本写入。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PFormatTextPo 格式文本Po。
 * @param PDataTextBA 数据文本Po。
 * @return 成功返回：0；失败返回：!0；
 *
 * 添加 数据 到 格式数据 群组 的 条目 中。
 * 格式文本格式 "群组:条目"。
 *
 */
extern uint8_t ZHFD_DataTextWrite_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const char* PDataTextPo)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL || PFormatTextPo == NULL) return 1;
	格式文本类型Po 格式文本信息Po = 格式文本开始FFu(PFormatTextPo);
	if (格式文本信息Po == NULL) return 1;
	群组类型Po 群组Po = 群组增加FFu(PFDPoPo, 格式文本信息Po->群组文本Po);
	if (群组Po == NULL)
	{
		格式文本结束FFu(格式文本信息Po);
		return 1;
	}
	条目类型Po 条目Po = 条目增加FFu(*PFDPoPo, &群组Po, 格式文本信息Po->条目文本Po);
	if (条目Po == NULL)
	{
		格式文本结束FFu(格式文本信息Po);
		return 1;
	}
	格式文本结束FFu(格式文本信息Po);
	数据类型Po 数据Po = 数据增加FFu(群组Po, &条目Po, PDataTextPo);
	if (数据Po == NULL) return 1;
	return 0;
}
/**
 * @brief 数据文本读取。
 * @param PFDPo 格式数据结构Po。
 * @param PFormatTextPo 格式文本Po。
 * @param PDataTextPo 数据文本Po。
 * @param PDataTextBA 数据文本字节数量。
 * @return 成功返回：0；失败返回：!0；
 *
 * 读取 数据 到 PDataTextPo。
 * 如果 数据文本 为 NULL，则置〇 PDataTextPo，如果 PDataTextPo 为 NULL，则 返回失败。
 * 如果 PDataTextBA 小于 数据文本字节数量，则 PDataTextBA 返回需要的字节数。
 * 格式文本格式 "群组:条目"。
 *
 * 可以获取所需字节数据 ZHFD_DataTextRead_FFu(PFDPo,"群组:条目",NULL,&PDataTextBA);。
 *
 */
extern uint8_t ZHFD_DataTextRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ const char* PDataTextPo, _PA_IN_OUT_ size_t* PDataTextBA)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	格式文本类型Po 格式文本信息Po = 格式文本开始FFu(PFormatTextPo);
	if (格式文本信息Po == NULL) return 1;
	群组类型Po 群组Po = 搜索群组FFu(PFDPo, 格式文本信息Po->群组文本Po);
	if (群组Po == NULL)
	{
		格式文本结束FFu(格式文本信息Po);
		return 1;
	}
	条目类型Po 条目Po = 搜索条目FFu(群组Po, 格式文本信息Po->条目文本Po);
	if (条目Po == NULL)
	{
		格式文本结束FFu(格式文本信息Po);
		return 1;
	}
	DATAMAXI 编号 = 格式文本信息Po->数据标识;
	格式文本结束FFu(格式文本信息Po);
	if (条目Po->数据PoAr[编号]->文本Po == NULL)
	{/*没有文本，置 0，返回成功*/
		if (PDataTextPo == NULL) return 1;
		memset(PDataTextPo, 0, *PDataTextBA);
		return 0;
	}
	DATAMAXI 文本BA = strlen(条目Po->数据PoAr[编号]->文本Po) + 1;
	if (*PDataTextBA < 文本BA)
	{
		*PDataTextBA = 文本BA;
		return 1;
	}
	if (PDataTextPo == NULL) return 1;
	strcpy(PDataTextPo, 条目Po->数据PoAr[编号]->文本Po);
	return 0;
}

/**
 * @brief 数据状态写入。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PFormatTextPo 格式文本Po。
 * @param PState 状态。
 * @return 成功返回：0；失败返回：!0；
 */
extern uint8_t ZHFD_DataStateWrite_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const uint8_t PState)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL || PFormatTextPo == NULL) return 1;
	格式文本类型Po 格式文本信息Po = 格式文本开始FFu(PFormatTextPo);
	if (格式文本信息Po == NULL) return 1;
	群组类型Po 群组Po = 群组增加FFu(PFDPoPo, 格式文本信息Po->群组文本Po);
	if (群组Po == NULL)
	{
		格式文本结束FFu(格式文本信息Po);
		return 1;
	}
	条目类型Po 条目Po = 条目增加FFu(PFDPoPo, &群组Po, 格式文本信息Po->条目文本Po);
	if (条目Po == NULL)
	{
		格式文本结束FFu(格式文本信息Po);
		return 1;
	}
	格式文本结束FFu(格式文本信息Po);
	数据类型Po 数据Po = NULL;
	if (PState == 0) 数据Po = 数据增加FFu(群组Po, &条目Po, 结束文本);
	else  数据Po = 数据增加FFu(群组Po, &条目Po, 开始文本);
	if (数据Po == NULL) return 1;
	return 0;
}
/**
 * @brief 数据状态读取。
 * @param PFDPo 格式数据结构Po。
 * @param PFormatTextPo 格式文本Po。
 * @param PStatePo 状态Po。
 * @return 成功返回：0；失败返回：!0；
 */
extern uint8_t ZHFD_DataStateRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ uint8_t* PStatePo)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	数据类型Po 数据Po = 结构数据读取FFu(PFDPo, PFormatTextPo);
	if (数据Po == NULL) return 1;
	const char* 文本Po = 数据Po->文本Po;
	for (size_t i = 0; i < ArrayLength(结束状态Ar); i++)
		if (文本Po[0] == 结束状态Ar[i])
		{
			*PStatePo = 0;
			return 0;
		}
	for (size_t i = 0; i < ArrayLength(开始状态Ar); i++)
		if (文本Po[0] == 开始状态Ar[i])
		{
			*PStatePo = 1;
			return 0;
		}
	return 1;
}

/**
 * @brief 数据写入。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PFormatTextPo 格式文本Po。
 * @param PNSData 数据。
 * @return 成功返回：0；失败返回：!0；
 */
extern uint8_t ZHFD_DataNSWrite_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const uint64_t PNSData)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL || PFormatTextPo == NULL) return 1;
	格式文本类型Po 格式文本信息Po = 格式文本开始FFu(PFormatTextPo);
	if (格式文本信息Po == NULL) return 1;
	群组类型Po 群组Po = 群组增加FFu(PFDPoPo, 格式文本信息Po->群组文本Po);
	if (群组Po == NULL)
	{
		格式文本结束FFu(格式文本信息Po);
		return 1;
	}
	条目类型Po 条目Po = 条目增加FFu(*PFDPoPo, &群组Po, 格式文本信息Po->条目文本Po);
	if (条目Po == NULL)
	{
		格式文本结束FFu(格式文本信息Po);
		return 1;
	}
	格式文本结束FFu(格式文本信息Po);
	文本类型 文本Ar[0x100] = { 0 };
	sprintf(&文本Ar, "%llu", PNSData);
	数据类型Po 数据Po = 数据增加FFu(群组Po, &条目Po, 文本Ar);
	if (数据Po == NULL) return 1;
	return 0;
}
/**
 * @brief 数据读取。
 * @param PFDPo 格式数据结构Po。
 * @param PFormatTextPo 格式文本Po。
 * @param PNSDataPo 数据Po。
 * @return 成功返回：0；失败返回：!0；
 */
extern uint8_t ZHFD_DataNSRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ uint64_t* PNSDataPo)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	数据类型Po 数据Po = 结构数据读取FFu(PFDPo, PFormatTextPo);
	if (数据Po == NULL) return 1;
	*PNSDataPo = strtoull(数据Po->文本Po, NULL, 10);
	return 0;
}

/**
 * @brief 符号数据写入。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PFormatTextPo 格式文本Po。
 * @param PSIData 符号数据。
 * @return 成功返回：0；失败返回：!0；
 */
extern uint8_t ZHFD_DataSIWrite_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const int64_t PSIData)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL || PFormatTextPo == NULL) return 1;
	格式文本类型Po 格式文本信息Po = 格式文本开始FFu(PFormatTextPo);
	if (格式文本信息Po == NULL) return 1;
	群组类型Po 群组Po = 群组增加FFu(PFDPoPo, 格式文本信息Po->群组文本Po);
	if (群组Po == NULL)
	{
		格式文本结束FFu(格式文本信息Po);
		return 1;
	}
	条目类型Po 条目Po = 条目增加FFu(*PFDPoPo, &群组Po, 格式文本信息Po->条目文本Po);
	if (条目Po == NULL)
	{
		格式文本结束FFu(格式文本信息Po);
		return 1;
	}
	格式文本结束FFu(格式文本信息Po);
	文本类型 文本Ar[0x100] = { 0 };
	sprintf(&文本Ar, "%lld", PSIData);
	数据类型Po 数据Po = 数据增加FFu(群组Po, &条目Po, 文本Ar);
	if (数据Po == NULL) return 1;
	return 0;
}
/**
 * @brief 符号数据读取。
 * @param PFDPo 格式数据结构Po。
 * @param PFormatTextPo 格式文本Po。
 * @param PSIDataPo 符号数据。
 * @return 成功返回：0；失败返回：!0；
 */
extern uint8_t ZHFD_DataSIRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ int64_t* PSIDataPo)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	数据类型Po 数据Po = 结构数据读取FFu(PFDPo, PFormatTextPo);
	if (数据Po == NULL) return 1;
	*PSIDataPo = strtoll(数据Po->文本Po, NULL, 10);
	return 0;
}

/**
 * @brief 浮点数据写入。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PFormatTextPo 格式文本Po。
 * @param PPointData 浮点数据。
 * @return 成功返回：0；失败返回：!0；
 */
extern uint8_t ZHFD_DataFloatWrite_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const long double PPointData)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL || PFormatTextPo == NULL) return 1;
	格式文本类型Po 格式文本信息Po = 格式文本开始FFu(PFormatTextPo);
	if (格式文本信息Po == NULL) return 1;
	群组类型Po 群组Po = 群组增加FFu(PFDPoPo, 格式文本信息Po->群组文本Po);
	if (群组Po == NULL)
	{
		格式文本结束FFu(格式文本信息Po);
		return 1;
	}
	条目类型Po 条目Po = 条目增加FFu(*PFDPoPo, &群组Po, 格式文本信息Po->条目文本Po);
	if (条目Po == NULL)
	{
		格式文本结束FFu(格式文本信息Po);
		return 1;
	}
	格式文本结束FFu(格式文本信息Po);
	文本类型 文本Ar[0x100] = { 0 };
	sprintf(&文本Ar, "%lf", PPointData);
	数据类型Po 数据Po = 数据增加FFu(群组Po, &条目Po, 文本Ar);
	if (数据Po == NULL) return 1;
	return 0;
}
/**
 * @brief 浮点数据读取。
 * @param PFDPo 格式数据结构Po。
 * @param PFormatTextPo 格式文本Po。
 * @param PPointDataPo 符号数据。
 * @return 成功返回：0；失败返回：!0；
 */
extern uint8_t ZHFD_DataFloatRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ long double* PPointDataPo)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	数据类型Po 数据Po = 结构数据读取FFu(PFDPo, PFormatTextPo);
	if (数据Po == NULL) return 1;
	*PPointDataPo = strtold(数据Po->文本Po, NULL);
	return 0;
}
