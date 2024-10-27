#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"ZHFormatData.h"

#define ArrayLength(Ar) (sizeof(Ar)/sizeof(Ar[0]))

#define �����ַ�		('\0')
#define �����ַ�		('`')

#define �հ��ı�		("")

#define Ⱥ�鿪ʼ�ַ�		('(')
#define Ⱥ������ַ�		(')')
#define ��Ŀ��ʼ�ַ�		('<')
#define ��Ŀ�����ַ�		('>')
#define ���ݿ�ʼ�ַ�		('[')
#define ���ݽ����ַ�		(']')
#define ע�Ϳ�ʼ�ַ�		('{')
#define ע�ͽ����ַ�		('}')

#define ��ʼ�ı�		("True")
#define �����ı�		("False")

#define Ⱥ���ı�(�ı�) ("("##�ı�")")
#define ��Ŀ�ı�(�ı�) ("("##�ı�")")
#define �����ı�(�ı�) ("("##�ı�")")
#define Ⱥ��ע��(ע��) ("{("##ע��")}")
#define ��Ŀע��(ע��) ("{("##ע��")}")
#define ����ע��(ע��) ("{("##ע��")}")

typedef void VOID, * VOIDPo;
typedef size_t DATAMAXI, * DATAMAXIPo;
typedef char �ַ�����, * �ַ�����Po, �ı�����, * �ı�����Po;

typedef enum StateEn
{
	F = 0,
	T = 1
} STATE;

/*Ԫ��*/
typedef struct ��������St
{
	�ı�����Po �ı�Po;		/*�����ı�*/
	�ı�����Po ע��Po;		/*����ע��*/
} ��������, * ��������Po;
typedef struct ��Ŀ����St
{
	�ı�����Po �ı�Po;		/*��Ŀ�ı�*/
	�ı�����Po ע��Po;		/*��Ŀע��*/
	DATAMAXI ��������;		/*��������*/
	��������Po ����PoAr[0];	/*��������Ⱥ��{��������}*/
} ��Ŀ����, * ��Ŀ����Po;
typedef struct Ⱥ������St
{
	�ı�����Po �ı�Po;		/*Ⱥ���ı�*/
	�ı�����Po ע��Po;		/*Ⱥ��ע��*/
	DATAMAXI ��Ŀ����;		/*��Ŀ����*/
	��Ŀ����Po ��ĿPoAr[0];	/*��Ŀ����Ⱥ��{��������}*/
} Ⱥ������, * Ⱥ������Po;
typedef struct ZHFormatDataSt
{
	DATAMAXI Ⱥ������;		/*Ⱥ������*/
	Ⱥ������Po Ⱥ��PoAr[0];	/*Ⱥ������Ⱥ��{��������}*/
} ��ʽ��������, * ��ʽ��������Po, ZHFDSt, * ZHFDStPo;

/*��ʽ�ı�*/
typedef struct ��ʽ�ı�St
{
	�ı�����Po Ⱥ���ı�Po;		/*Ⱥ���ı�*/
	�ı�����Po ��Ŀ�ı�Po;		/*��Ŀ�ı�*/
	size_t ���ݱ�ʶ;			/*��������*/
} ��ʽ�ı�����, * ��ʽ�ı�����Po;

static const char �ָ��ַ�Ar[] = { ':', '.' };

static const �ı����� ��ʼ״̬Ar[] = { 'T','t','S','s','O','o','+','*','1','2','3','4','5','6','7','8','9' };
static const �ı����� ����״̬Ar[] = { 'F','f','E','e','C','c','-','/','0' };


/*----------------------------------------------------------------
�ı�������{�ײ�}
----------------------------------------------------------------*/

/**
 * @brief �ı���ʼ��
 * @param P�ı�BA �ı��ֽ�������
 * @return �ɹ����أ��ı��ڴ�Po��ʧ�ܷ��أ�NULL��
 *
 * ע�⣺
 * - �������� �ı��ڴ棬�� �ı��ڴ� д��0��
 * - ������Ҫʹ�� �ı�����FFu �����ͷš�
 *
 * ʾ����
 * - �ı�����Po �ı�Po = �ı���ʼFFu(�ı����� + 1);
 */
static �ı�����Po �ı���ʼFFu(DATAMAXI P�ı�BA)
{
	if (P�ı�BA == 0) return NULL;
	�ı�����Po �ı�Po = malloc(P�ı�BA * sizeof(�ı�����));
	if (�ı�Po != NULL) memset(�ı�Po, 0, sizeof(�ı�����));
	return �ı�Po;
}
/**
 * @brief �ı�������
 * @param P�ı�Po �ı�Po��
 *
 * ע�⣺
 * - �� �ı����� �ڴ� ���١�
 *
 * ʾ����
 * - �ı�����FFu(�ı�Po);
 */
static VOID �ı�����FFu(�ı�����Po P�ı�Po)
{
	free(P�ı�Po);
}

/**
 * @brief �ı��Ƚϡ�
 * @param P�ı���Po �ı�Po������ΪNULL��
 * @param P�ı���Po �ı�Po������ΪNULL��
 * @param P��� F�����Դ�Сд�������жϴ�Сд��
 * @return F���ı���ͬ��T���ı���ͬ��
 *
 * ע�⣺
 * - �Ƚ� P�ı���Po �� P�ı���Po �Ƿ� ��ͬ��
 * - ��� P�ı���Po �� P�ı���Po ͬʱΪ NULL���� ��ͬ��
 *
 * ʾ����
 * - if (�ı��Ƚ�FFu(P�ı���Po, P�ı���Po, F) == F)
 * - if (�ı��Ƚ�FFu(P�ı���Po, P�ı���Po, F) != F)
 */
static STATE �ı��Ƚ�FFu(const char* P�ı���Po, const char* P�ı���Po, STATE P���)
{
	/*�ж� P�ı���Po �� P�ı���Po ͬʱΪ NULL*/
	if (P�ı���Po == NULL && P�ı���Po == NULL) return T;
	if (P�ı���Po == NULL || P�ı���Po == NULL) return F;
	size_t �ı����� = strlen(P�ı���Po);
	if (�ı����� != strlen(P�ı���Po)) return F;
	if (P��� == F)
	{
		for (size_t Accu = 0; Accu < �ı�����; Accu++)
			if ((P�ı���Po[Accu] >= 'a' && P�ı���Po[Accu] <= 'z' ? P�ı���Po[Accu] - 32 : P�ı���Po[Accu]) !=
				(P�ı���Po[Accu] >= 'a' && P�ı���Po[Accu] <= 'z' ? P�ı���Po[Accu] - 32 : P�ı���Po[Accu])) return F;
	}
	else if (strcmp(P�ı���Po, P�ı���Po) != 0) return F;
	return T;
}

/*----------------------------------------------------------------
��ʽ�ı�������{�ײ�}
----------------------------------------------------------------*/

VOID ��ʽ�ı�����FFu(��ʽ�ı�����Po P��ʽ�ı���ϢPo);

/**
 * @brief ��ʽ�ı���ʼ��
 * @param P��ʽ�ı�Po ��ʽ�ı���
 * @return �ɹ����أ���ʽ�ı�����Po��ʧ�ܷ��أ�NULL��
 *
 * ע�⣺
 * - �������� ��ʽ�ı����� �ڴ棬P��ʽ�ı�Po ���� д�� ��ʽ�ı����� �ڴ档
 * - ��ʽ������Ϣ���ԣ���Ϣ֮���� �ָ����� �ָ���
 * - ��� ��� ������ֵ���򷵻� ʧ�ܡ�
 * - ������Ҫʹ�� ��ʽ�ı�����FFu �����ͷš�
 *
 * ʾ����
 * - ��ʽ�ı�����Po ��ʽ�ı�Po = ��ʽ�ı���ʼFFu(""); Ϊ{NULL,NULL,0}
 * - ��ʽ�ı�����Po ��ʽ�ı�Po = ��ʽ�ı���ʼFFu("Ⱥ��"); Ϊ{Ⱥ��,NULL,0}
 * - ��ʽ�ı�����Po ��ʽ�ı�Po = ��ʽ�ı���ʼFFu("Ⱥ��:��Ŀ"); Ϊ{Ⱥ��,��Ŀ,0}
 * - ��ʽ�ı�����Po ��ʽ�ı�Po = ��ʽ�ı���ʼFFu("Ⱥ��:��Ŀ:1"); Ϊ{Ⱥ��,��Ŀ,1}
 * - ��ʽ�ı�����Po ��ʽ�ı�Po = ��ʽ�ı���ʼFFu(":��Ŀ:1"); Ϊ{NULL,��Ŀ,1}
 * - ��ʽ�ı�����Po ��ʽ�ı�Po = ��ʽ�ı���ʼFFu("::1"); Ϊ{NULL,NULL,1}
 * - ��ʽ�ı�����Po ��ʽ�ı�Po = ��ʽ�ı���ʼFFu("::"); Ϊ{NULL,NULL,0}
 */
static ��ʽ�ı�����Po ��ʽ�ı���ʼFFu(const �ı�����Po P��ʽ�ı�Po)
{
	if (P��ʽ�ı�Po == NULL) return NULL;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = malloc(sizeof(��ʽ�ı�����));
	if (��ʽ�ı���ϢPo == NULL) return NULL;
	memset(��ʽ�ı���ϢPo, 0, sizeof(��ʽ�ı�����));
	const DATAMAXI ��Ϣ���� = 3, �ı�BA = strlen(P��ʽ�ı�Po) + 1;
	DATAMAXI ��ʼ���� = 0, �������� = 0;
	/*Ⱥ���ı�*/
	�ı�����Po Ⱥ���ı�Po = NULL;
	{
		DATAMAXI Ⱥ���ı����� = 0;
		while (1)
		{
			if (P��ʽ�ı�Po[��������] == �����ַ�) break;
			STATE ����״̬ = F;
			for (size_t i = 0; i < ArrayLength(�ָ��ַ�Ar); i++)
				if (P��ʽ�ı�Po[��������] == �ָ��ַ�Ar[i]) ����״̬ = T;
			if (����״̬ == T) break;
			��������++;
		}
		Ⱥ���ı����� = �������� - ��ʼ����;
		/*��ʼ�ı�*/
		if (Ⱥ���ı����� == 0);
		else
		{
			Ⱥ���ı�Po = �ı���ʼFFu(Ⱥ���ı����� + 1);
			if (Ⱥ���ı�Po == NULL) goto Error;
			/*��ȡ�ı�*/
			for (size_t i = 0; i < Ⱥ���ı�����; i++)
				Ⱥ���ı�Po[i] = P��ʽ�ı�Po[��ʼ���� + i];
			Ⱥ���ı�Po[Ⱥ���ı�����] = �����ַ�;
		}
	}
	��ʽ�ı���ϢPo->Ⱥ���ı�Po = Ⱥ���ı�Po;
	if (P��ʽ�ı�Po[�������� + 1] == �����ַ�) return ��ʽ�ı���ϢPo;
	�������� += 1;
	��ʼ���� = ��������;
	/*��Ŀ�ı�*/
	�ı�����Po ��Ŀ�ı�Po = NULL;
	{
		DATAMAXI ��Ŀ�ı����� = 0;
		while (1)
		{
			if (P��ʽ�ı�Po[��������] == �����ַ�) break;
			STATE ����״̬ = F;
			for (size_t i = 0; i < ArrayLength(�ָ��ַ�Ar); i++)
				if (P��ʽ�ı�Po[��������] == �ָ��ַ�Ar[i]) ����״̬ = T;
			if (����״̬ == T) break;
			��������++;
		}
		��Ŀ�ı����� = �������� - ��ʼ����;
		/*��ʼ�ı�*/
		if (��Ŀ�ı����� == 0);
		else
		{
			��Ŀ�ı�Po = �ı���ʼFFu(��Ŀ�ı����� + 1);
			if (��Ŀ�ı�Po == NULL) goto Error;
			/*��ȡ�ı�*/
			for (size_t i = 0; i < ��Ŀ�ı�����; i++)
				��Ŀ�ı�Po[i] = P��ʽ�ı�Po[��ʼ���� + i];
			��Ŀ�ı�Po[��Ŀ�ı�����] = �����ַ�;
		}
	}
	��ʽ�ı���ϢPo->��Ŀ�ı�Po = ��Ŀ�ı�Po;
	if (P��ʽ�ı�Po[�������� + 1] == �����ַ�) return ��ʽ�ı���ϢPo;
	�������� += 1;
	��ʼ���� = ��������;
	/*����ı�*/
	�ı�����Po ����ı�Po = NULL;
	{
		DATAMAXI ����ı����� = 0;
		while (1)
		{
			if (P��ʽ�ı�Po[��������] == �����ַ�) break;
			STATE ����״̬ = F;
			for (size_t i = 0; i < ArrayLength(�ָ��ַ�Ar); i++)
				if (P��ʽ�ı�Po[��������] == �ָ��ַ�Ar[i]) ����״̬ = T;
			if (����״̬ == T) break;
			��������++;
		}
		����ı����� = �������� - ��ʼ����;
		/*��ʼ�ı�*/
		if (����ı����� == 0);
		else
		{
			����ı�Po = �ı���ʼFFu(����ı����� + 1);
			if (����ı�Po == NULL) goto Error;
			/*��ȡ�ı�*/
			for (size_t i = 0; i < ����ı�����; i++)
				����ı�Po[i] = P��ʽ�ı�Po[��ʼ���� + i];
			����ı�Po[����ı�����] = �����ַ�;
		}
	}
	if (����ı�Po == NULL)
		��ʽ�ı���ϢPo->���ݱ�ʶ = 0;
	else
		��ʽ�ı���ϢPo->���ݱ�ʶ = strtoull(����ı�Po, NULL, 10);
	/*����||���*/
	if (errno == EINVAL || errno == ERANGE) goto Error;
	return ��ʽ�ı���ϢPo;
Error:
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	return NULL;
}
/**
 * @brief ��ʽ�ı���Ϣ������
 * @param P��ʽ�ı���ϢPo ��ʽ�ı���ϢPo��
 *
 * ע�⣺
 * - �����ͷ� ��ʽ�ı����� �ڴ档
 *
 * ʾ����
 * - ��ʽ�ı�����FFu(��ʽ�ı�Po);
 */
static VOID ��ʽ�ı�����FFu(��ʽ�ı�����Po P��ʽ�ı���ϢPo)
{
	free(P��ʽ�ı���ϢPo->Ⱥ���ı�Po);
	free(P��ʽ�ı���ϢPo->��Ŀ�ı�Po);
	free(P��ʽ�ı���ϢPo);
}

/*----------------------------------------------------------------
����������{�ײ�}
----------------------------------------------------------------*/

/**
 * @brief ����Ⱥ�顣
 * @param P��ʽ����Po ��ʽ��������Po��
 * @param P�ı�Po Ⱥ���ı�Po��
 * @return �ɹ����أ�Ⱥ��Po��ʧ�ܷ��أ�NULL��
 *
 * ע�⣺
 * - P�ı�Po ����Ϊ NULL��
 * - ����������ָ��Ϊ NULL �� Ⱥ�顣
 *
 * ʾ����
 * - Ⱥ������Po Ⱥ��Po = ����Ⱥ��FFu(P��ʽ����Po, P�ı�Po);
 */
static Ⱥ������Po ����Ⱥ��FFu(const ��ʽ��������Po P��ʽ����Po, const �ı�����Po P�ı�Po)
{
	if (P��ʽ����Po == NULL) return NULL;
	if (P��ʽ����Po->Ⱥ������ == 0) return NULL;/*û��Ⱥ��*/
	Ⱥ������Po Ⱥ��Po = NULL;
	for (size_t i = 0; i < P��ʽ����Po->Ⱥ������; i++)
	{/*ѭ��Ѱ��Ⱥ��*/
		if (P��ʽ����Po->Ⱥ��PoAr[i] == NULL) continue;/*���� NULL Ⱥ��*/
		if (�ı��Ƚ�FFu(P��ʽ����Po->Ⱥ��PoAr[i]->�ı�Po, P�ı�Po, T) == T)
		{/*��ͬ����*/
			Ⱥ��Po = P��ʽ����Po->Ⱥ��PoAr[i];
			break;
		}
	}
	return Ⱥ��Po;
}
/**
 * @brief ������Ŀ��
 * @param PȺ��Po Ⱥ������Po��
 * @param P�ı�Po �ı�����Po��
 * @return �ɹ����أ���ĿPo��ʧ�ܷ��أ�NULL��
 *
 * ע�⣺
 * - P�ı�Po ����Ϊ NULL��
 * - ����������ָ��Ϊ NULL �� ��Ŀ��
 *
 * ʾ����
 * - ��Ŀ����Po ��ĿPo = ������ĿFFu(PȺ��Po, P�ı�Po);
 */
static ��Ŀ����Po ������ĿFFu(const Ⱥ������Po PȺ��Po, const �ı�����Po P�ı�Po)
{
	if (PȺ��Po == NULL) return NULL;
	if (PȺ��Po->��Ŀ���� == 0) return NULL;/*û����Ŀ*/
	��Ŀ����Po ��ĿPo = NULL;
	for (size_t i = 0; i < PȺ��Po->��Ŀ����; i++)
	{/*ѭ��Ѱ����Ŀ*/
		if (PȺ��Po->��ĿPoAr[i] == NULL) continue;/*���� NULL ��Ŀ*/
		if (�ı��Ƚ�FFu(PȺ��Po->��ĿPoAr[i]->�ı�Po, P�ı�Po, T) == T)
		{/*��ͬ����*/
			��ĿPo = PȺ��Po->��ĿPoAr[i];
			break;
		}
	}
	return ��ĿPo;
}

/*----------------------------------------------------------------
�ṹ������{�ײ�}
----------------------------------------------------------------*/

/**
 * @brief ��ʼ���ݽṹ��
 * @return �ɹ����أ�����Po��ʧ�ܷ��أ�NULL��
 *
 * ע�⣺
 * - �������ݽṹ�ڴ棬�����ڴ�д��0��
 * - ������Ҫʹ�� �ṹ���ݽ���FFu �����ͷš�
 *
 * ʾ����
 * - ��������Po ����Po = �ṹ���ݿ�ʼFFu();
 */
static ��������Po �ṹ���ݿ�ʼFFu(VOID) {
	��������Po StPo = malloc(sizeof(��������));
	if (StPo == NULL) return NULL;
	memset(StPo, 0, sizeof(��������));
	return StPo;
}
/**
 * @brief �������ݽṹ��
 * @param P����Po ���ݽṹPo������Ϊ NULL��
 *
 * ע�⣺
 * - �� �������� �ڴ� ���١�
 *
 * ʾ����
 * - �ṹ���ݽ���FFu(P����Po);
 */
static VOID �ṹ���ݽ���FFu(��������Po P����Po)
{
	free(P����Po->�ı�Po);
	P����Po->�ı�Po = NULL;
	free(P����Po->ע��Po);
	P����Po->ע��Po = NULL;
	free(P����Po);
}

/**
 * @brief ��ʼ��Ŀ�ṹ��
 * @return �ɹ����أ���ĿPo��ʧ�ܷ��أ�NULL��
 *
 * ע�⣺
 * - ������Ŀ�ṹ�ڴ棬�����ڴ�д��0��
 * - ������Ҫʹ�� �ṹ��Ŀ����FFu �����ͷš�
 *
 * ʾ����
 * - ��Ŀ����Po ��ĿPo = �ṹ��Ŀ��ʼFFu();
 */
static ��Ŀ����Po �ṹ��Ŀ��ʼFFu(VOID) {
	��Ŀ����Po StPo = malloc(sizeof(��Ŀ����));
	if (StPo == NULL) return NULL;
	memset(StPo, 0, sizeof(��Ŀ����));
	return StPo;
}
/**
 * @brief ������Ŀ�ṹ��
 * @param P��ĿPo ���ݽṹPo��
 *
 * ע�⣺
 * - �� ��Ŀ���� �ڴ� �� �������� �ڴ� ���١�
 *
 * ʾ����
 * - �ṹ��Ŀ����FFu(P��ĿPo);
 */
static VOID �ṹ��Ŀ����FFu(��Ŀ����Po P��ĿPo)
{
	if (P��ĿPo == NULL) return;
	for (size_t i = 0; i < P��ĿPo->��������; i++)
	{
		�ṹ���ݽ���FFu(P��ĿPo->����PoAr[i]);
		P��ĿPo->����PoAr[i] = NULL;
	}
	free(P��ĿPo->�ı�Po);
	P��ĿPo->�ı�Po = NULL;
	free(P��ĿPo->ע��Po);
	P��ĿPo->ע��Po = NULL;
	free(P��ĿPo);
}

/**
 * @brief ��ʼȺ��ṹ��
 * @return �ɹ����أ�Ⱥ��Po��ʧ�ܷ��أ�NULL��
 *
 * ע�⣺
 * - ����Ⱥ��ṹ�ڴ棬�����ڴ�д��0��
 * - ������Ҫʹ�� �ṹȺ�����FFu �����ͷš�
 *
 * ʾ����
 * - Ⱥ������Po Ⱥ��Po = �ṹȺ�鿪ʼFFu();
 */
static Ⱥ������Po �ṹȺ�鿪ʼFFu(VOID) {
	Ⱥ������Po StPo = malloc(sizeof(Ⱥ������));
	if (StPo == NULL) return NULL;
	memset(StPo, 0, sizeof(Ⱥ������));
	return StPo;
}
/**
 * @brief ����Ⱥ��ṹ��
 * @param PȺ��Po ���ݽṹPo��
 *
 * ע�⣺
 * - �� Ⱥ������ �ڴ桢��Ŀ���� �ڴ� �� �������� �ڴ� ���١�
 *
 * ʾ����
 * - �ṹȺ�����FFu(PȺ��Po);
 */
static VOID �ṹȺ�����FFu(Ⱥ������Po PȺ��Po)
{
	if (PȺ��Po == NULL) return;
	for (size_t i = 0; i < PȺ��Po->��Ŀ����; i++)
	{
		�ṹ��Ŀ����FFu(PȺ��Po->��ĿPoAr[i]);
		PȺ��Po->��ĿPoAr[i] = NULL;
	}
	free(PȺ��Po->�ı�Po);
	PȺ��Po->�ı�Po = NULL;
	free(PȺ��Po->ע��Po);
	PȺ��Po->ע��Po = NULL;
	free(PȺ��Po);
}

/**
 * @brief ��ʼ��ʽ���ݽṹ��
 * @return �ɹ����أ���ʽ����Po��ʧ�ܷ��أ�NULL��
 *
 * ע�⣺
 * - ������ʽ���ݽṹ�ڴ棬�����ڴ�д��0��
 * - ������Ҫʹ�� �ṹ��ʽ���ݽ���FFu �����ͷš�
 *
 * ʾ����
 * - ��ʽ��������Po ��ʽ����Po = �ṹ��ʽ���ݿ�ʼFFu();
 */
static ��ʽ��������Po �ṹ��ʽ���ݿ�ʼFFu(VOID) {
	��ʽ��������Po StPo = malloc(sizeof(��ʽ��������));
	if (StPo == NULL) return NULL;
	memset(StPo, 0, sizeof(��ʽ��������));
	return StPo;
}
/**
 * @brief ���ٸ�ʽ���ݽṹ���Լ��ڲ�������ڴ档
 * @param P��ʽ����Po ���ݽṹPo������Ϊ NULL��
 *
 * ע�⣺
 * - �� Ⱥ������ �ڴ桢��Ŀ���� �ڴ� �� �������� �ڴ� ���١�
 *
 * ʾ����
 * - �ṹ��ʽ���ݽ���FFu(PȺ��Po);
 */
static VOID �ṹ��ʽ���ݽ���FFu(��ʽ��������Po P��ʽ����Po)
{
	if (P��ʽ����Po == NULL) return;
	for (size_t i = 0; i < P��ʽ����Po->Ⱥ������; i++)
	{
		�ṹȺ�����FFu(P��ʽ����Po->Ⱥ��PoAr[i]);
		P��ʽ����Po->Ⱥ��PoAr[i] = NULL;
	}
	P��ʽ����Po->Ⱥ������ = 0;
	free(P��ʽ����Po);
}

/*----------------------------------------------------------------
�ļ�������{�ײ�}
----------------------------------------------------------------*/

/**
 * @brief ��ȡ�ļ������ַ������ַ�ת����ȡ��
 * @param P�ļ�Po �ļ�Po��
 * @return �ַ���
 *
 * ע�⣺
 * - �� �ļ������ַ� ����ת��������ת������ַ���
 */
static int �ļ��ַ���ȡFFu(FILE* P�ļ�Po)
{
	int �ַ� = fgetc(P�ļ�Po);
	if (�ַ� == �����ַ�)
	{
		/*��¼λ��*/
		fpos_t ��ȡλ�� = 0;
		if (fgetpos(P�ļ�Po, &��ȡλ��)) return EOF;
		/*��ȡ��һ�ַ�*/
		if ((�ַ� = fgetc(P�ļ�Po)) == EOF) return EOF;
		/*�Ƿ�Ϊת���ַ�*/
		switch (�ַ�)
		{
		case 'a':/*����*/
			return '\a';
		case 'b':/*�˸�*/
			return '\b';
		case 't':/*��ֱ�Ʊ�*/
			return '\t';
		case 'n':/*����*/
			return '\n';
		case 'v':/*ˮƽ�Ʊ�*/
			return '\v';
		case 'f':/*��ҳ*/
			return '\f';
		case 'r':/*��������*/
			return '\r';
			/*�����ַ�*/
		case �����ַ�:
			/*Ԫ���ַ�*/
		case Ⱥ�鿪ʼ�ַ�:
		case Ⱥ������ַ�:
		case ��Ŀ��ʼ�ַ�:
		case ��Ŀ�����ַ�:
		case ���ݿ�ʼ�ַ�:
		case ���ݽ����ַ�:
		case ע�Ϳ�ʼ�ַ�:
		case ע�ͽ����ַ�:
			break;
		default:/*����ת���ַ�*/
			/*��ԭ��ȡλ��*/
			if (fsetpos(P�ļ�Po, &��ȡλ��)) return EOF;
			/*���ط����ַ�*/
			return �����ַ�;
		}
	}
	return �ַ�;
}
/**
 * @brief �����ļ�����Ԫ���ı�����д��Ԫ���ı���
 * @param P�ļ�Po �ļ�Po��
 * @param P�����ַ� �����ַ���
 * @param �ı�PoPo �ı�PoPo��
 * @return �ɹ����أ�T��ʧ�ܷ��أ�F��
 *
 * ע�⣺
 * - ������ı�Ϊ ""���ı�PoPo ��Ϊ NULL��
 * - ������Ҫʹ�� �����ı�FFu �����ͷš�
 */
static STATE �ļ�Ԫ���ı���ʼFFu(FILE* P�ļ�Po, int P�����ַ�, �ı�����Po* P�ı�PoPo)
{
	if (P�ļ�Po == NULL) return F;
	int �ַ� = 0;
	�ı�����Po �ı�Po = NULL;
	/*��ȡ�ı�����*/
	DATAMAXI �ı����� = 0;
	{
		fpos_t �ļ�λ�� = 0;
		if (fgetpos(P�ļ�Po, &�ļ�λ��)) return F;
		while ((�ַ� = fgetc(P�ļ�Po)) != EOF)
		{
			if (�ַ� == �����ַ�)
			{/*�����ַ�����һ������*/
				�ַ� = fgetc(P�ļ�Po);
				�ı�����++;
				continue;
			}
			else if (�ַ� == P�����ַ�) break;
			�ı�����++;
		}
		if (fsetpos(P�ļ�Po, &�ļ�λ��)) return F;
	}
	if (�ı����� == 0)
		*P�ı�PoPo = NULL;
	else
	{
		/*�����ڴ�*/
		if ((�ı�Po = �ı���ʼFFu(�ı����� + 1)) == NULL) return F;
		/*д���ڴ�*/
		for (size_t i = 0; i < �ı�����; i++)
			�ı�Po[i] = �ļ��ַ���ȡFFu(P�ļ�Po);
		�ı�Po[�ı�����] = �����ַ�;
		*P�ı�PoPo = �ı�Po;
	}
	return T;
}

/*----------------------------------------------------------------
Ԫ�أ�����{����}{����û��ͬ���ṹ���ڽṹ��ɾ���ṹ}
----------------------------------------------------------------*/

static STATE Ⱥ��ɾ��FFu(��ʽ��������Po* P��ʽ����PoPo, Ⱥ������Po PȺ��Po);
static STATE ��Ŀɾ��FFu(Ⱥ������Po* PȺ��PoPo, ��Ŀ����Po P��ĿPo);
static STATE ����ɾ��FFu(��Ŀ����Po* P��ĿPoPo, ��������Po P����Po);

/**
 * @brief �� ��ʽ���� ������ Ⱥ�顣
 * @param P��ʽ����PoPo ��ʽ��������Po��Po��
 * @param P�ı�Po ��Ŀ�ı���
 * @return �ɹ����أ����ӵ�Ⱥ��Po��ʧ�ܷ��أ�NULL��
 *
 * ��� Ⱥ�� �������򷵻� Ⱥ�顣
 * ��� Ⱥ�� ����ʧ�ܣ��� ʧ�ܡ�
 * ��� ��ʽ���� ����ʧ�ܣ��� ʧ�ܡ�
 * ��� �ı� Ϊ NULL��""�����ı�Ϊ NULL��
 * ��� �ı� ����ʧ�ܣ��� ʧ�ܡ�
 *
 */
static Ⱥ������Po Ⱥ������FFu(��ʽ��������Po* P��ʽ����PoPo, const �ı�����Po P�ı�Po)
{
	if (P��ʽ����PoPo == NULL || *P��ʽ����PoPo == NULL) return NULL;
	Ⱥ������Po Ⱥ��Po = ����Ⱥ��FFu(*P��ʽ����PoPo, P�ı�Po);
	if (Ⱥ��Po == NULL)
	{/*û��ͬ��*/
		Ⱥ��Po = �ṹȺ�鿪ʼFFu();
		if (Ⱥ��Po == NULL) return NULL;
		��ʽ��������Po ��ʽ����Po = realloc(*P��ʽ����PoPo, sizeof(��ʽ��������) + (sizeof(Ⱥ������Po) * ((*P��ʽ����PoPo)->Ⱥ������ + 1)));
		if (��ʽ����Po == NULL)
		{/*ʧ�ܷ��أ�ԭ��ʽ����û���ͷ�*/
			�ṹȺ�����FFu(Ⱥ��Po);
			return NULL;
		}
		*P��ʽ����PoPo = ��ʽ����Po;
		��ʽ����Po->Ⱥ������++;
		��ʽ����Po->Ⱥ��PoAr[��ʽ����Po->Ⱥ������ - 1] = Ⱥ��Po;
		if (P�ı�Po == NULL) return Ⱥ��Po;
		DATAMAXI �ı����� = strlen(P�ı�Po);
		if (�ı����� == 0) return Ⱥ��Po;
		�ı�����Po �ı�Po = �ı���ʼFFu(�ı����� + 1);
		if (�ı�Po == NULL)
		{
			Ⱥ��ɾ��FFu(P��ʽ����PoPo, Ⱥ��Po);
			return NULL;
		}
		strcpy(�ı�Po, P�ı�Po);
		Ⱥ��Po->�ı�Po = �ı�Po;
	}
	return Ⱥ��Po;
}
/**
 * @brief �ڸ�ʽ������ɾ��Ⱥ�顣
 * @param P��ʽ����PoPo ��ʽ��������Po��Po��
 * @param PȺ��Po Ⱥ������Po��
 * @return �ɹ����أ�T��ʧ�ܷ��أ�F��
 *
 * ��� Ⱥ�� Ϊ NULL���� �ɹ���
 * ��� Ⱥ�� ���� ��ʽ���� �� Ⱥ�飬�� ʧ�ܡ�
 * ��� ��ʽ���� ����ʧ�ܣ��� ʧ�ܡ�
 *
 */
static STATE Ⱥ��ɾ��FFu(��ʽ��������Po* P��ʽ����PoPo, Ⱥ������Po PȺ��Po)
{
	if (P��ʽ����PoPo == NULL || *P��ʽ����PoPo == NULL) return F;
	if (PȺ��Po == NULL) return T;
	size_t ���� = 0;
	{
		for (; ���� < (*P��ʽ����PoPo)->Ⱥ������; ����++)
			if ((*P��ʽ����PoPo)->Ⱥ��PoAr[����] == PȺ��Po) break;
		if (���� == (*P��ʽ����PoPo)->Ⱥ������) return F;
	}
	�ṹȺ�����FFu(PȺ��Po);
	/*����Ⱥ��ǰ��*/
	for (; ���� < (*P��ʽ����PoPo)->Ⱥ������ - 1; ����++)
		(*P��ʽ����PoPo)->Ⱥ��PoAr[����] = (*P��ʽ����PoPo)->Ⱥ��PoAr[���� + 1];
	/*��ֹ����ʧ�ܣ���ǰ������NULL*/
	(*P��ʽ����PoPo)->Ⱥ��PoAr[����] = NULL;
	/*���·����ڴ�*/
	��ʽ��������Po ��ʽ����Po = realloc(*P��ʽ����PoPo, sizeof(��ʽ��������) + (sizeof(Ⱥ������Po) * ((*P��ʽ����PoPo)->Ⱥ������ - 1)));
	if (��ʽ����Po == NULL) return F;
	*P��ʽ����PoPo = ��ʽ����Po;
	��ʽ����Po->Ⱥ������--;
	return T;
}

/**
 * @brief ����Ŀ������Ⱥ�顣
 * @param P��ʽ����Po ��ʽ��������Po��
 * @param PȺ��PoPo Ⱥ������Po��
 * @param P�ı�Po ��Ŀ�ı�Po��
 * @return �ɹ����أ����ӵ���ĿPo��ʧ�ܷ��أ�NULL��
 *
 * ��� ��Ŀ �������򷵻� ��Ŀ��
 * ��� ��Ŀ ����ʧ�ܣ��� ʧ�ܡ�
 * ��� Ⱥ�� ����ʧ�ܣ��� ʧ�ܡ�
 * ��� �ı� Ϊ NULL��""�����ı�Ϊ NULL��
 * ��� �ı� ����ʧ�ܣ��� ʧ�ܡ�
 *
 */
static ��Ŀ����Po ��Ŀ����FFu(��ʽ��������Po P��ʽ����Po, Ⱥ������Po* PȺ��PoPo, const �ı�����Po P�ı�Po)
{
	if (P��ʽ����Po == NULL || PȺ��PoPo == NULL || *PȺ��PoPo == NULL) return NULL;
	/*����ͬ��Ⱥ��*/
	��Ŀ����Po ��ĿPo = ������ĿFFu(*PȺ��PoPo, P�ı�Po);
	if (��ĿPo == NULL)
	{/*û��ͬ��*/
		/*�ж� Ⱥ�� �Ƿ� Ϊ��ʽ�����е�Ⱥ��*/
		{
			size_t i = 0;
			for (; i < P��ʽ����Po->Ⱥ������; i++)
				if (P��ʽ����Po->Ⱥ��PoAr[i] == *PȺ��PoPo) break;
			if (i == P��ʽ����Po->Ⱥ������) return NULL;
		}
		/*������Ŀ*/
		��ĿPo = �ṹ��Ŀ��ʼFFu();
		if (��ĿPo == NULL) return NULL;
		Ⱥ������Po Ⱥ��Po = realloc(*PȺ��PoPo, sizeof(Ⱥ������) + (sizeof(��Ŀ����Po) * ((*PȺ��PoPo)->��Ŀ���� + 1)));
		if (Ⱥ��Po == NULL)
		{/*ʧ�ܷ��أ�ԭȺ��û���ͷ�*/
			�ṹ��Ŀ����FFu(��ĿPo);
			return NULL;
		}
		/*���¸�ʽ����*/
		for (size_t i = 0; i < P��ʽ����Po->Ⱥ������; i++)
			if (P��ʽ����Po->Ⱥ��PoAr[i] == *PȺ��PoPo)
			{
				P��ʽ����Po->Ⱥ��PoAr[i] = Ⱥ��Po;
				break;
			}
		/*����Ⱥ��*/
		*PȺ��PoPo = Ⱥ��Po;
		/*������Ŀ*/
		Ⱥ��Po->��Ŀ����++;
		Ⱥ��Po->��ĿPoAr[Ⱥ��Po->��Ŀ���� - 1] = ��ĿPo;
		if (P�ı�Po == NULL) return ��ĿPo;
		DATAMAXI �ı����� = strlen(P�ı�Po);
		if (�ı����� == 0) return ��ĿPo;
		�ı�����Po �ı�Po = �ı���ʼFFu(�ı����� + 1);
		if (�ı�Po == NULL)
		{
			��Ŀɾ��FFu(PȺ��PoPo, ��ĿPo);
			return NULL;
		}
		strcpy(�ı�Po, P�ı�Po);
		��ĿPo->�ı�Po = �ı�Po;
	}
	return ��ĿPo;
}
/**
 * @brief ��Ⱥ����ɾ����Ŀ��
 * @param PȺ��PoPo Ⱥ������Po��Po��
 * @param P��ĿPo ��Ŀ����Po��
 * @return �ɹ����أ�T��ʧ�ܷ��أ�F��
 *
 * ��� ��Ŀ Ϊ NULL���� �ɹ���
 * ��� ��Ŀ ���� Ⱥ�� �� ��Ŀ���� ʧ�ܡ�
 * ��� Ⱥ�� ����ʧ�ܣ��� ʧ�ܡ�
 *
 */
static STATE ��Ŀɾ��FFu(Ⱥ������Po* PȺ��PoPo, ��Ŀ����Po P��ĿPo)
{
	if (PȺ��PoPo == NULL || *PȺ��PoPo == NULL) return F;
	if (P��ĿPo == NULL) return T;
	size_t ���� = 0;
	{
		for (; ���� < (*PȺ��PoPo)->��Ŀ����; ����++)
			if ((*PȺ��PoPo)->��ĿPoAr[����] == P��ĿPo) break;
		if (���� == (*PȺ��PoPo)->��Ŀ����) return F;
	}
	�ṹ��Ŀ����FFu(P��ĿPo);
	/*����Ⱥ��ǰ��*/
	for (; ���� < ((*PȺ��PoPo)->��Ŀ���� - 1); ����++)
		(*PȺ��PoPo)->��ĿPoAr[����] = (*PȺ��PoPo)->��ĿPoAr[���� + 1];
	/*��ֹ����ʧ�ܣ���ǰ������NULL*/
	(*PȺ��PoPo)->��ĿPoAr[����] = NULL;
	/*���·����ڴ�*/
	Ⱥ������Po Ⱥ��Po = realloc(*PȺ��PoPo, sizeof(Ⱥ������) + (sizeof(��Ŀ����Po) * ((*PȺ��PoPo)->��Ŀ���� - 1)));
	if (Ⱥ��Po == NULL) return F;
	/*�ɹ�д����Ϣ*/
	*PȺ��PoPo = Ⱥ��Po;
	Ⱥ��Po->��Ŀ����--;
	return T;
}

/**
 * @brief ����Ŀ���������ݡ�
 * @param PȺ��Po Ⱥ��Po��
 * @param P��ĿPoPo ��Ŀ����Po��Po��
 * @param P�ı�Po ��Ŀ�ı���
 * @return �ɹ����أ����ӵ�����Po��ʧ�ܷ��أ�NULL��
 *
 * ��� ���� ����ʧ�ܣ��� ʧ�ܡ�
 * ��� ��Ŀ ����ʧ�ܣ��� ʧ�ܡ�
 * ��� �ı� Ϊ NULL��""�����ı�Ϊ NULL��
 * ��� �ı� ����ʧ�ܣ��� ʧ�ܡ�
 *
 */
static ��������Po ��������FFu(Ⱥ������Po PȺ��Po, ��Ŀ����Po* P��ĿPoPo, const �ı�����Po P�ı�Po)
{
	if (PȺ��Po == NULL || P��ĿPoPo == NULL || *P��ĿPoPo == NULL) return NULL;
	/*�ж� ��Ŀ �Ƿ� Ϊ Ⱥ�� �е� ��Ŀ*/
	{
		size_t i = 0;
		for (; i < PȺ��Po->��Ŀ����; i++)
			if (PȺ��Po->��ĿPoAr[i] == *P��ĿPoPo) break;
		if (i == PȺ��Po->��Ŀ����) return NULL;
	}
	��������Po ����Po = �ṹ���ݿ�ʼFFu();
	if (����Po == NULL) return NULL;
	��Ŀ����Po ��ĿPo = realloc(*P��ĿPoPo, sizeof(��Ŀ����) + (sizeof(��������Po) * ((*P��ĿPoPo)->�������� + 1)));
	if (��ĿPo == NULL)
	{/*ʧ�ܷ��أ�ԭ��Ŀû���ͷ�*/
		�ṹ���ݽ���FFu(����Po);
		return NULL;
	}
	/*����Ⱥ��*/
	for (size_t i = 0; i < PȺ��Po->��Ŀ����; i++)
		if (PȺ��Po->��ĿPoAr[i] == *P��ĿPoPo)
			PȺ��Po->��ĿPoAr[i] = ��ĿPo;
	/*������Ŀ*/
	*P��ĿPoPo = ��ĿPo;
	/*��������*/
	��ĿPo->��������++;
	��ĿPo->����PoAr[��ĿPo->�������� - 1] = ����Po;
	if (P�ı�Po == NULL) return ����Po;
	DATAMAXI �ı����� = strlen(P�ı�Po);
	if (�ı����� == 0) return ����Po;
	�ı�����Po �ı�Po = �ı���ʼFFu(�ı����� + 1);
	if (�ı�Po == NULL)
	{
		����ɾ��FFu(P��ĿPoPo, ����Po);
		return NULL;
	}
	strcpy(�ı�Po, P�ı�Po);
	����Po->�ı�Po = �ı�Po;
	return ����Po;
}
/**
 * @brief ����Ŀ��ɾ�����ݡ�
 * @param P��ĿPoPo ��Ŀ����Po��Po��
 * @param P����Po ��������Po��
 * @return �ɹ����أ�T��ʧ�ܷ��أ�F��
 *
 * ��� ���� Ϊ NULL���� �ɹ���
 * ��� ���� ���� ��Ŀ �� ���ݣ��� ʧ�ܡ�
 * ��� ��Ŀ ����ʧ�ܣ��� ʧ�ܡ�
 *
 */
static STATE ����ɾ��FFu(��Ŀ����Po* P��ĿPoPo, ��������Po P����Po)
{
	if (P��ĿPoPo == NULL || *P��ĿPoPo == NULL) return F;
	if (P����Po == NULL) return T;
	size_t ���� = 0;
	{
		for (; ���� < (*P��ĿPoPo)->��������; ����++)
			if ((*P��ĿPoPo)->����PoAr[����] == P����Po) break;
		if (���� == (*P��ĿPoPo)->��������) return F;
	}
	�ṹ���ݽ���FFu(P����Po);
	/*��������ǰ��*/
	for (; ���� < ((*P��ĿPoPo)->�������� - 1); ����++)
		(*P��ĿPoPo)->����PoAr[����] = (*P��ĿPoPo)->����PoAr[���� + 1];
	/*��ֹ����ʧ�ܣ���ǰ������NULL*/
	(*P��ĿPoPo)->����PoAr[����] = NULL;
	/*���·����ڴ�*/
	��Ŀ����Po ��ĿPo = realloc(*P��ĿPoPo, sizeof(��Ŀ����) + (sizeof(��������Po) * ((*P��ĿPoPo)->�������� - 1)));
	if (��ĿPo == NULL) return F;
	/*�ɹ�д����Ϣ*/
	*P��ĿPoPo = ��ĿPo;
	��ĿPo->��������--;
	return T;
}

/*----------------------------------------------------------------
�ṹ������{����}
----------------------------------------------------------------*/

/**
 * @brief ͨ����ʽ�ı���Ѱ�Ҳ�����Ⱥ�顣
 * @param P��ʽ����Po ��ʽ��������Po��
 * @param P��ʽ�ı�Po ��ʽ�ı�Po��
 * @return �ɹ����أ�����Po��ʧ�ܷ��أ�NULL��
 */
static Ⱥ������Po �ṹȺ���ȡFFu(const ��ʽ��������Po P��ʽ����Po, const �ı�����Po P��ʽ�ı�Po)
{
	if (P��ʽ����Po == NULL || P��ʽ�ı�Po == NULL) return NULL;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = ��ʽ�ı���ʼFFu(P��ʽ�ı�Po);
	if (��ʽ�ı���ϢPo == NULL) return NULL;
	Ⱥ������Po Ⱥ��Po = ����Ⱥ��FFu(P��ʽ����Po, ��ʽ�ı���ϢPo->Ⱥ���ı�Po);
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	if (Ⱥ��Po == NULL) return NULL;
	return Ⱥ��Po;
}
/**
 * @brief ͨ����ʽ�ı���Ѱ�Ҳ�������Ŀ��
 * @param P��ʽ����Po ��ʽ��������Po��
 * @param P��ʽ�ı�Po ��ʽ�ı�Po��
 * @return �ɹ����أ�����Po��ʧ�ܷ��أ�NULL��
 */
static ��Ŀ����Po �ṹ��Ŀ��ȡFFu(const ��ʽ��������Po P��ʽ����Po, const �ı�����Po P��ʽ�ı�Po)
{
	if (P��ʽ����Po == NULL || P��ʽ�ı�Po == NULL) return NULL;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = ��ʽ�ı���ʼFFu(P��ʽ�ı�Po);
	if (��ʽ�ı���ϢPo == NULL) return NULL;
	��Ŀ����Po ��ĿPo = NULL;
	{
		/*Ѱ��Ⱥ��*/
		Ⱥ������Po Ⱥ��Po = ����Ⱥ��FFu(P��ʽ����Po, ��ʽ�ı���ϢPo->Ⱥ���ı�Po);
		if (Ⱥ��Po == NULL) goto Error;
		/*Ѱ����Ŀ*/
		��ĿPo = ������ĿFFu(Ⱥ��Po, ��ʽ�ı���ϢPo->��Ŀ�ı�Po);
		if (��ĿPo == NULL) goto Error;
	}
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	return ��ĿPo;
Error:
	{
		��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
		return NULL;
	}
}
/**
 * @brief ͨ����ʽ�ı���Ѱ�Ҳ��������ݡ�
 * @param P��ʽ����Po ��ʽ��������Po��
 * @param P��ʽ�ı�Po ��ʽ�ı�Po��
 * @return �ɹ����أ�����Po��ʧ�ܷ��أ�NULL��
 */
static ��������Po �ṹ���ݶ�ȡFFu(const ��ʽ��������Po P��ʽ����Po, const �ı�����Po P��ʽ�ı�Po)
{
	if (P��ʽ����Po == NULL || P��ʽ�ı�Po == NULL) return NULL;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = ��ʽ�ı���ʼFFu(P��ʽ�ı�Po);
	if (��ʽ�ı���ϢPo == NULL) return NULL;
	��������Po ����Po = NULL;
	{
		/*Ѱ��Ⱥ��*/
		Ⱥ������Po Ⱥ��Po = ����Ⱥ��FFu(P��ʽ����Po, ��ʽ�ı���ϢPo->Ⱥ���ı�Po);
		if (Ⱥ��Po == NULL) goto Error;
		/*Ѱ����Ŀ*/
		��Ŀ����Po ��ĿPo = ������ĿFFu(Ⱥ��Po, ��ʽ�ı���ϢPo->��Ŀ�ı�Po);
		if (��ĿPo == NULL) goto Error;
		if (��ĿPo->�������� < ��ʽ�ı���ϢPo->���ݱ�ʶ) goto Error;
		����Po = ��ĿPo->����PoAr[��ʽ�ı���ϢPo->���ݱ�ʶ];
	}
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	return ����Po;
Error:
	{
		��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
		return NULL;
	}
}

/*----------------------------------------------------------------
�ļ�������{�ײ�}
----------------------------------------------------------------*/

/**
 * @brief ��ȡ�ļ�д��ṹ���ݡ�
 * @param P��ʽ����PoPo ��ʽ��������Po��
 * @param P�ļ�����Po �ļ�����Po��
 * @return �ɹ����أ�T��ʧ�ܷ��أ�F��
 *
 * ���Խ�һ���Ѿ�ӵ�����ݵĸ�ʽ���ݴ��룬���ļ����ݺ͸�ʽ���ݵ����ݺϲ���һ����ʽ���ݡ�
 *
 */
static STATE �ļ���ȡFFu(��ʽ��������Po* P��ʽ����PoPo, const �ı�����Po P�ļ�����Po)
{
	if (P�ļ�����Po == NULL || P��ʽ����PoPo == NULL || *P��ʽ����PoPo == NULL) return F;
	const FILE* �ļ�Po = fopen(P�ļ�����Po, "r");
	if (�ļ�Po == NULL) return F;
	/*��ȡ�ļ�*/
	{
		Ⱥ������Po Ⱥ��Po = NULL;
		��Ŀ����Po ��ĿPo = NULL;
		��������Po ����Po = NULL;
		/*��ǰ�ַ�*/
		int �ַ� = 0;
		while ((�ַ� = fgetc(�ļ�Po)) != EOF)
		{
			/*��������*/
			switch (�ַ�)
			{
			case Ⱥ�鿪ʼ�ַ�:
			{
				/*������ȡȺ���ı�*/
				�ı�����Po �ı�Po = NULL;
				if (�ļ�Ԫ���ı���ʼFFu(�ļ�Po, Ⱥ������ַ�, &�ı�Po) == F) goto Error;
				Ⱥ��Po = Ⱥ������FFu(P��ʽ����PoPo, �ı�Po);
				�ı�����FFu(�ı�Po);
				if (Ⱥ��Po == NULL) goto Error;
				/*�����ϵ*/
				��ĿPo = NULL;
				����Po = NULL;
			}
			break;
			case ��Ŀ��ʼ�ַ�:
			{
				/*����Ⱥ��*/
				if (Ⱥ��Po == NULL)
					Ⱥ��Po = Ⱥ������FFu(P��ʽ����PoPo, NULL);
				if (Ⱥ��Po == NULL) goto Error;
				/*������Ŀ*/
				�ı�����Po �ı�Po = NULL;
				if (�ļ�Ԫ���ı���ʼFFu(�ļ�Po, ��Ŀ�����ַ�, &�ı�Po) == F) goto Error;
				��ĿPo = ��Ŀ����FFu(*P��ʽ����PoPo, &Ⱥ��Po, �ı�Po);
				�ı�����FFu(�ı�Po);
				if (��ĿPo == NULL) goto Error;
				/*�����ϵ*/
				����Po = NULL;
			}
			break;
			case ���ݿ�ʼ�ַ�:
			{
				/*����Ⱥ�顢��Ŀ*/
				if (��ĿPo == NULL)
				{
					/*����Ⱥ��*/
					if (Ⱥ��Po == NULL)
						Ⱥ��Po = Ⱥ������FFu(P��ʽ����PoPo, NULL);
					if (Ⱥ��Po == NULL) goto Error;
					/*������Ŀ*/
					��ĿPo = ��Ŀ����FFu(*P��ʽ����PoPo, &Ⱥ��Po, NULL);
					if (��ĿPo == NULL) goto Error;
				}
				/*��������*/
				�ı�����Po �ı�Po = NULL;
				if (�ļ�Ԫ���ı���ʼFFu(�ļ�Po, ���ݽ����ַ�, &�ı�Po) == F) goto Error;
				����Po = ��������FFu(Ⱥ��Po, &��ĿPo, �ı�Po);
				�ı�����FFu(�ı�Po);
				if (����Po == NULL) goto Error;
			}
			break;
			case ע�Ϳ�ʼ�ַ�:
			{
				fpos_t �ļ�λ�� = 0;
				if (fgetpos(�ļ�Po, &�ļ�λ��)) goto Error;
				if ((�ַ� = fgetc(�ļ�Po)) == EOF) goto Error;
				switch (�ַ�)
				{
				case Ⱥ�鿪ʼ�ַ�:
				{
					if (Ⱥ��Po == NULL) break;
					if (Ⱥ��Po->ע��Po != NULL) break;
					�ı�����Po ע���ı�Po = NULL;
					if (�ļ�Ԫ���ı���ʼFFu(�ļ�Po, Ⱥ������ַ�, &ע���ı�Po) == F) goto Error;
					Ⱥ��Po->ע��Po = ע���ı�Po;
				}
				break;
				case ��Ŀ��ʼ�ַ�:
				{
					if (��ĿPo == NULL) break;
					if (��ĿPo->ע��Po != NULL) break;
					�ı�����Po ע���ı�Po = NULL;
					if (�ļ�Ԫ���ı���ʼFFu(�ļ�Po, ��Ŀ�����ַ�, &ע���ı�Po) == F) goto Error;
					��ĿPo->ע��Po = ע���ı�Po;
				}
				break;
				case ���ݿ�ʼ�ַ�:
				{
					if (����Po == NULL) break;
					if (����Po->ע��Po != NULL) break;
					�ı�����Po ע���ı�Po = NULL;
					if (�ļ�Ԫ���ı���ʼFFu(�ļ�Po, ���ݽ����ַ�, &ע���ı�Po) == F) goto Error;
					����Po->ע��Po = ע���ı�Po;
				}
				break;
				default:
					if (fsetpos(�ļ�Po, &�ļ�λ��) != 0) goto Error;
					break;
				}
			}
			break;
			default:
				break;
			}
		}
		if (�ַ� != EOF) goto Error;
	}
	fclose(�ļ�Po);
	return T;
Error:
	{
		fclose(�ļ�Po);
		/*�����ո�ʽ����*/
		/*��ʽ�������´���
		�ṹ��ʽ���ݽ���FFu(*P��ʽ����PoPo);
		*P��ʽ����PoPo = �ṹ��ʽ���ݿ�ʼFFu();
		*/
		return F;
	}
}
/**
 * @brief ��ȡ�ṹ����д���ļ���
 * @param P��ʽ����PoPo ��ʽ��������Po��
 * @param P�ļ�����Po �ļ�����Po��
 * @return �ɹ����أ�T��ʧ�ܷ��أ�F��
 */
static STATE �ļ�д��FFu(const ��ʽ��������Po P��ʽ����PoPo, const �ı�����Po P�ļ�����Po)
{
	if (P��ʽ����PoPo == NULL || P�ļ�����Po == NULL) return F;
	/*���ļ�*/
	const FILE* �ļ�Po = fopen(P�ļ�����Po, "w");
	if (�ļ�Po == NULL) return F;
	for (size_t i = 0; i < P��ʽ����PoPo->Ⱥ������; i++)
	{/*Ⱥ��ѭ��*/
		if (P��ʽ����PoPo->Ⱥ��PoAr[i]->�ı�Po == NULL);//fprintf(�ļ�Po, Ⱥ���ı�());
		else fprintf(�ļ�Po, Ⱥ���ı�("%s"), P��ʽ����PoPo->Ⱥ��PoAr[i]->�ı�Po);
		if (P��ʽ����PoPo->Ⱥ��PoAr[i]->ע��Po == NULL);//fprintf(�ļ�Po, Ⱥ��ע��());
		else fprintf(�ļ�Po, Ⱥ��ע��("%s"), P��ʽ����PoPo->Ⱥ��PoAr[i]->ע��Po);
		fprintf(�ļ�Po, "\n");
		for (size_t j = 0; j < P��ʽ����PoPo->Ⱥ��PoAr[i]->��Ŀ����; j++)
		{
			if (P��ʽ����PoPo->Ⱥ��PoAr[i]->��ĿPoAr[j]->�ı�Po == NULL);//fprintf(�ļ�Po, ��Ŀ�ı�());
			else fprintf(�ļ�Po, ��Ŀ�ı�("%s"), P��ʽ����PoPo->Ⱥ��PoAr[i]->��ĿPoAr[j]->�ı�Po);
			if (P��ʽ����PoPo->Ⱥ��PoAr[i]->��ĿPoAr[j]->ע��Po == NULL);//fprintf(�ļ�Po, ��Ŀע��());
			else fprintf(�ļ�Po, ��Ŀע��("%s"), P��ʽ����PoPo->Ⱥ��PoAr[i]->��ĿPoAr[j]->ע��Po);
			fprintf(�ļ�Po, "\n");
			for (size_t k = 0; k < P��ʽ����PoPo->Ⱥ��PoAr[i]->��ĿPoAr[j]->��������; k++)
			{
				if (P��ʽ����PoPo->Ⱥ��PoAr[i]->��ĿPoAr[j]->����PoAr[k]->�ı�Po == NULL);//fprintf(�ļ�Po, �����ı�());
				else fprintf(�ļ�Po, �����ı�("%s"), P��ʽ����PoPo->Ⱥ��PoAr[i]->��ĿPoAr[j]->����PoAr[k]->�ı�Po);
				if (P��ʽ����PoPo->Ⱥ��PoAr[i]->��ĿPoAr[j]->����PoAr[k]->ע��Po == NULL);//fprintf(�ļ�Po, ����ע��());
				else fprintf(�ļ�Po, ����ע��("%s"), P��ʽ����PoPo->Ⱥ��PoAr[i]->��ĿPoAr[j]->����PoAr[k]->ע��Po);
				fprintf(�ļ�Po, "\n");
			}
		}
	}
	fclose(�ļ�Po);
	return T;
}




/*----------------------------------------------------------------
�ӿں���
*/

/*----------------------------------------------------------------
* ��ʽ���ݣ�����{�ײ�}
----------------------------------------------------------------*/

/**
 * @brief ��ʽ���ݽṹ��ʼ��
 * @return �ɹ����أ���ʽ���ݽṹPo��ʧ�ܷ��أ�NULL��
 *
 * ע�⣺
 * - ������Ҫʹ�� ZHFD_FDEnd_PFu �����ͷš�
 *
 * ʾ����
 * - ZHFDStPo ZHFDPo = ZHFD_FDStart_PFu();
 */
extern ZHFDStPo ZHFD_FDStart_PFu(void)
{
	return �ṹ��ʽ���ݿ�ʼFFu();
}
/**
 * @brief ��ʽ���ݽṹ������
 * @param PFDPo ��ʽ���ݽṹPo��
 *
 * ע�⣺
 * - �����ͷ� ZHFDSt �ڴ档
 *
 * ʾ����
 * - ZHFD_FDEnd_PFu(ZHFDSt);
 */
extern void ZHFD_FDEnd_PFu(_PA_IN_ ZHFDStPo PFDPo)
{
	�ṹ��ʽ���ݽ���FFu(PFDPo);
	return;
}

/*----------------------------------------------------------------
* �ļ���д������{�ײ�}
----------------------------------------------------------------*/

/**
 * @brief ��ʽ����д���ļ���
 * @param PFDPo ��ʽ���ݽṹPo��
 * @param PFileNamePo �ļ����ơ�
 * @return �ɹ����أ�0��ʧ�ܷ��أ�1��
 *
 * ע�⣺
 * - ������ ��ʽ���� д�� �ļ���
 *
 * ʾ����
 * - if(ZHFD_FDFWrite_FFu(PFDPo,PFileNamePo)) //Error;
 */
extern uint8_t ZHFD_FDFWrite_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFileNamePo)
{
	return �ļ�д��FFu(PFDPo, PFileNamePo) == F ? 1 : 0;
}
/**
 * @brief �ļ�д���ʽ���ݡ�
 * @param PFDPoPo ��ʽ���ݽṹPo��Po��
 * @param PFileNamePo �ļ����ơ�
 * @return �ɹ����أ�0��ʧ�ܷ��أ�1��
 *
 * ע�⣺
 * - ������ �ļ� д�� ��ʽ���ݡ�
 * - ����ʧ�� PFDPo ���ܻᱻ�ƻ���
 *
 * ʾ����
 * - if(ZHFD_FDFRead_FFu(&PFDPo,PFileNamePo)) //Error;
 */
extern uint8_t ZHFD_FDFRead_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFileNamePo)
{
	return �ļ���ȡFFu(PFDPoPo, PFileNamePo) == F ? 1 : 0;
}

/*----------------------------------------------------------------
* Ԫ�أ�����{�ײ�}
----------------------------------------------------------------*/

/**
 * @brief ��ʼȺ�顣
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PTextPo �ı�Po��
 * @param PCommentPo ע���ı�Po��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 *
 * ���ڴ���Ⱥ�飬д���ı���ע����Ϣ��
 * �����ͬ�ı�Ⱥ�飬������ע�ͣ�����ע��д��Ⱥ�顣
 *
 */
extern uint8_t ZHFD_FDGroupStart_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PTextPo, _PA_IN_ const char* PCommentPo)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL) return 1;
	Ⱥ������Po Ⱥ��Po = Ⱥ������FFu(PFDPoPo, PTextPo);
	if (Ⱥ��Po == NULL) return 1;
	if (PCommentPo != NULL)
	{
		DATAMAXI �ı����� = strlen(PCommentPo);
		if (�ı����� == 0) return 0;
		�ı�����Po ע��Po = �ı���ʼFFu(�ı����� + 1);
		if (ע��Po == NULL)
		{
			Ⱥ��ɾ��FFu(PFDPoPo, Ⱥ��Po);
			return 1;
		}
		strcpy(ע��Po, PCommentPo);
		Ⱥ��Po->ע��Po = ע��Po;
	}
	return 0;
}
/**
 * @brief ����Ⱥ�顣
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
extern uint8_t ZHFD_FDGroupEnd_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL || PFormatTextPo == NULL) return 1;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = ��ʽ�ı���ʼFFu(PFormatTextPo);
	if (��ʽ�ı���ϢPo == NULL) return 1;
	Ⱥ������Po Ⱥ��Po = ����Ⱥ��FFu(*PFDPoPo, ��ʽ�ı���ϢPo->Ⱥ���ı�Po);
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	if (Ⱥ��Po == NULL) return 1;
	if (Ⱥ��ɾ��FFu(PFDPoPo, Ⱥ��Po) == F) return 1;
	return 0;
}

/**
 * @brief ��ʼ��Ŀ��
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PTextPo �ı�Po��
 * @param PCommentPo ע���ı�Po��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
extern uint8_t ZHFD_FDItemStart_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const char* PTextPo, _PA_IN_ const char* PCommentPo)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL || PFormatTextPo == NULL) return 1;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = ��ʽ�ı���ʼFFu(PFormatTextPo);
	if (��ʽ�ı���ϢPo == NULL) return 1;
	Ⱥ������Po Ⱥ��Po = Ⱥ������FFu(PFDPoPo, ��ʽ�ı���ϢPo->Ⱥ���ı�Po);
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	if (Ⱥ��Po == NULL) return 1;
	��Ŀ����Po ��ĿPo = ��Ŀ����FFu(*PFDPoPo, &Ⱥ��Po, PTextPo);
	if (��ĿPo == NULL)
	{
		Ⱥ��ɾ��FFu(PFDPoPo, Ⱥ��Po);
		return 1;
	}
	if (PCommentPo != NULL)
	{
		DATAMAXI �ı����� = strlen(PCommentPo);
		if (�ı����� == 0) return 0;
		�ı�����Po ע��Po = �ı���ʼFFu(�ı����� + 1);
		if (ע��Po == NULL)
		{
			��Ŀɾ��FFu(&Ⱥ��Po, ��ĿPo);
			Ⱥ��ɾ��FFu(PFDPoPo, Ⱥ��Po);
			return 1;
		}
		strcpy(ע��Po, PCommentPo);
		��ĿPo->ע��Po = ע��Po;
	}
	return 0;
}
/**
 * @brief ������Ŀ��
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 *
 * ���Ⱥ����û��Ŀ����Ŀ���򷵻سɹ���
 *
 */
extern uint8_t ZHFD_FDItemEnd_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL || PFormatTextPo == NULL) return 1;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = ��ʽ�ı���ʼFFu(PFormatTextPo);
	if (��ʽ�ı���ϢPo == NULL) return 1;
	Ⱥ������Po Ⱥ��Po = ����Ⱥ��FFu(*PFDPoPo, ��ʽ�ı���ϢPo->Ⱥ���ı�Po);
	if (Ⱥ��Po == NULL) goto Error;
	��Ŀ����Po ��ĿPo = ������ĿFFu(Ⱥ��Po, ��ʽ�ı���ϢPo->��Ŀ�ı�Po);
	if (��ĿPo != NULL)
		if (��Ŀɾ��FFu(&Ⱥ��Po, ��ĿPo) == F) goto Error;
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	return 0;
Error:
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	return 1;
}

/**
 * @brief ��ʼ���ݡ�
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PTextPo �ı�Po��
 * @param PCommentPo ע���ı�Po��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
extern uint8_t ZHFD_FDDataStart_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const char* PTextPo, _PA_IN_ const char* PCommentPo)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL || PFormatTextPo == NULL || PTextPo == NULL || PCommentPo == NULL) return 1;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = ��ʽ�ı���ʼFFu(PFormatTextPo);
	if (��ʽ�ı���ϢPo == NULL) return 1;
	Ⱥ������Po Ⱥ��Po = Ⱥ������FFu(PFDPoPo, ��ʽ�ı���ϢPo->Ⱥ���ı�Po);
	if (Ⱥ��Po == NULL)
	{
		��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
		return 1;
	}
	��Ŀ����Po ��ĿPo = ��Ŀ����FFu(*PFDPoPo, &Ⱥ��Po, ��ʽ�ı���ϢPo->��Ŀ�ı�Po);
	if (��ĿPo == NULL)
	{
		��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
		return 1;
	}
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	��������Po ����Po = ��������FFu(Ⱥ��Po, &��ĿPo, PTextPo);
	if (PCommentPo != NULL)
	{
		DATAMAXI �ı����� = strlen(PCommentPo);
		if (�ı����� == 0) return 0;
		�ı�����Po ע��Po = �ı���ʼFFu(�ı����� + 1);
		if (ע��Po == NULL)
		{
			����ɾ��FFu(&��ĿPo, ����Po);
			��Ŀɾ��FFu(&Ⱥ��Po, ��ĿPo);
			Ⱥ��ɾ��FFu(PFDPoPo, Ⱥ��Po);
			return 1;
		}
		strcpy(ע��Po, PCommentPo);
		����Po->ע��Po = ע��Po;
	}
	return 0;
}
/**
 * @brief �������ݡ�
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
extern uint8_t ZHFD_FDDataEnd_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL || PFormatTextPo == NULL) return 1;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = ��ʽ�ı���ʼFFu(PFormatTextPo);
	if (��ʽ�ı���ϢPo == NULL) return 1;
	Ⱥ������Po Ⱥ��Po = ����Ⱥ��FFu(*PFDPoPo, ��ʽ�ı���ϢPo->Ⱥ���ı�Po);
	if (Ⱥ��Po == NULL) goto Error;
	��Ŀ����Po ��ĿPo = ������ĿFFu(Ⱥ��Po, ��ʽ�ı���ϢPo->��Ŀ�ı�Po);
	if (��ĿPo == NULL) goto Error;
	����ɾ��FFu(&��ĿPo, ��ĿPo->����PoAr[��ʽ�ı���ϢPo->���ݱ�ʶ]);
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	return 0;
Error:
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	return 1;
}

/*----------------------------------------------------------------
* Ԫ�ض�д������{�ײ�}
----------------------------------------------------------------*/

/**
 * @brief Ⱥ��д�롣
 * @param PFDPo ��ʽ����Po��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PTextPo �ı�Po��
 * @param PCommentPo ע���ı�Po��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 *
 * ��Ⱥ����д���µ���Ϣ��
 * PTextPo �� PCommentPo ���Ϊ NULL �򲻸ı䡣
 * PTextPo �� PCommentPo ���Ϊ ""�����Ϊ NULL��
 * PTextPo �� PCommentPo �����Ϊ NULL �� ""�������ı���Ⱥ�顣
 * ����������򷵻�ʧ�ܡ�
 * �˺���ʧ�ܿ��ܻᵼ��Ⱥ��ṹ����
 *
 */
extern uint8_t ZHFD_FDGroupWrite_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ char* PTextPo, _PA_IN_ char* PCommentPo)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	/*��������ʧ��*/
	if (����Ⱥ��FFu(PFDPo, PTextPo) != NULL) return 1;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = ��ʽ�ı���ʼFFu(PFormatTextPo);
	if (��ʽ�ı���ϢPo == NULL) return 1;
	Ⱥ������Po Ⱥ��Po = ����Ⱥ��FFu(PFDPo, ��ʽ�ı���ϢPo->Ⱥ���ı�Po);
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	if (Ⱥ��Po == NULL) return 1;
	/*�ı�*/
	if (PTextPo == NULL)
		/*NULL���򲻱�*/;
	else if (�ı��Ƚ�FFu(PTextPo, �հ��ı�, F) == F)
		/*""��������ı�*/
		�ı�����FFu(Ⱥ��Po->�ı�Po);
	else
	{/*�����ı�*/
		DATAMAXI �ı����� = strlen(PTextPo);
		�ı�����Po �ı�Po = �ı���ʼFFu(�ı����� + 1);
		if (�ı�Po == NULL) return 1;
		strcpy(�ı�Po, PTextPo);
		�ı�����FFu(Ⱥ��Po->�ı�Po);
		Ⱥ��Po->�ı�Po = �ı�Po;
	}
	/*ע��*/
	if (PCommentPo == NULL)
		/*NULL���򲻱�*/;
	else if (�ı��Ƚ�FFu(PCommentPo, �հ��ı�, F) == F)
		/*""��������ı�*/
		�ı�����FFu(Ⱥ��Po->ע��Po);
	else
	{/*�����ı�*/
		DATAMAXI �ı����� = strlen(PCommentPo);
		�ı�����Po ע��Po = �ı���ʼFFu(�ı����� + 1);
		if (ע��Po == NULL) return 1;
		strcpy(ע��Po, PCommentPo);
		�ı�����FFu(Ⱥ��Po->ע��Po);
		Ⱥ��Po->ע��Po = ע��Po;
	}
	return 0;
}
/**
 * @brief Ⱥ���ȡ��
 * @param PFDPo ��ʽ����Po��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PTextPo �ı�Po��
 * @param PTextBA �ı��ֽ�������
 * @param PCommentPo ע���ı�Po��
 * @param PCommentBA ע���ֽ�������
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
extern uint8_t ZHFD_FDGroupRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo,
	_PA_OUT_ char* PTextPo, _PA_IN_OUT_ size_t* PTextBA, _PA_OUT_ char* PCommentPo, _PA_IN_OUT_ size_t* PCommentBA)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	if (PTextPo != NULL && *PTextBA == 0) return 1;
	if (PCommentPo != NULL && *PCommentBA == 0) return 1;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = ��ʽ�ı���ʼFFu(PFormatTextPo);
	if (��ʽ�ı���ϢPo == NULL) return 1;
	Ⱥ������Po Ⱥ��Po = ����Ⱥ��FFu(PFDPo, ��ʽ�ı���ϢPo->Ⱥ���ı�Po);
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	if (Ⱥ��Po == NULL) return 1;
	if (PTextPo != NULL && Ⱥ��Po->�ı�Po != NULL)
	{
		DATAMAXI �ı�BA = strlen(Ⱥ��Po->�ı�Po) + 1;
		if (�ı�BA > *PTextBA) goto Error;
		strcpy(PTextPo, Ⱥ��Po->�ı�Po);
	}
	if (PCommentPo != NULL && Ⱥ��Po->ע��Po != NULL)
	{
		DATAMAXI �ı�BA = strlen(Ⱥ��Po->ע��Po) + 1;
		if (�ı�BA > *PCommentBA) goto Error;
		strcpy(PCommentPo, Ⱥ��Po->ע��Po);
	}
	return 0;
Error:
	if (Ⱥ��Po->�ı�Po != NULL)
		*PTextBA = strlen(Ⱥ��Po->�ı�Po) + 1;
	if (Ⱥ��Po->ע��Po != NULL)
		*PCommentBA = strlen(Ⱥ��Po->ע��Po) + 1;
	return 1;
}

/**
 * @brief ��Ŀд�롣
 * @param PFDPo ��ʽ����Po��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PTextPo �ı�Po��
 * @param PCommentPo ע���ı�Po��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 *
 * ����Ŀ��д���µ���Ϣ��
 * PTextPo �� PCommentPo ���Ϊ NULL �򲻸ı䡣
 * PTextPo �� PCommentPo ���Ϊ ""�����Ϊ NULL��
 * PTextPo �� PCommentPo �����Ϊ NULL �� ""�������ı�����Ŀ��
 * ����������򷵻�ʧ�ܡ�
 * �˺���ʧ�ܿ��ܻᵼ����Ŀ�ṹ����
 *
 */
extern uint8_t ZHFD_FDItemWrite_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ char* PTextPo, _PA_IN_ char* PCommentPo)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	/*��������ʧ��*/
	if (������ĿFFu(PFDPo, PTextPo) != NULL) return 1;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = ��ʽ�ı���ʼFFu(PFormatTextPo);
	if (��ʽ�ı���ϢPo == NULL) return 1;
	Ⱥ������Po Ⱥ��Po = ����Ⱥ��FFu(PFDPo, ��ʽ�ı���ϢPo->Ⱥ���ı�Po);
	if (Ⱥ��Po == NULL)
	{
		��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
		return 1;
	}
	��Ŀ����Po ��ĿPo = ������ĿFFu(Ⱥ��Po, ��ʽ�ı���ϢPo->��Ŀ�ı�Po);
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	if (��ĿPo == NULL) return 1;
	/*�ı�*/
	if (PTextPo == NULL)
		/*NULL���򲻱�*/;
	else if (�ı��Ƚ�FFu(PTextPo, �հ��ı�, F) == F)
		/*""��������ı�*/
		�ı�����FFu(��ĿPo->�ı�Po);
	else
	{/*�����ı�*/
		DATAMAXI �ı����� = strlen(PTextPo);
		�ı�����Po �ı�Po = �ı���ʼFFu(�ı����� + 1);
		if (�ı�Po == NULL) return 1;
		strcpy(�ı�Po, PTextPo);
		�ı�����FFu(��ĿPo->�ı�Po);
		��ĿPo->�ı�Po = �ı�Po;
	}
	/*ע��*/
	if (PCommentPo == NULL)
		/*NULL���򲻱�*/;
	else if (�ı��Ƚ�FFu(PCommentPo, �հ��ı�, F) == F)
		/*""��������ı�*/
		�ı�����FFu(��ĿPo->ע��Po);
	else
	{/*�����ı�*/
		DATAMAXI �ı����� = strlen(PCommentPo);
		�ı�����Po ע��Po = �ı���ʼFFu(�ı����� + 1);
		if (ע��Po == NULL) return 1;
		strcpy(ע��Po, PCommentPo);
		�ı�����FFu(��ĿPo->ע��Po);
		��ĿPo->ע��Po = ע��Po;
	}
	return 0;
}
/**
 * @brief ��Ŀ��ȡ��
 * @param PFDPo ��ʽ����Po��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PTextPo �ı�Po��
 * @param PTextBA �ı��ֽ�������
 * @param PCommentPo ע���ı�Po��
 * @param PCommentBA ע���ֽ�������
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
extern uint8_t ZHFD_FDItemRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo,
	_PA_OUT_ char* PTextPo, _PA_IN_OUT_ size_t* PTextBA, _PA_OUT_ char* PCommentPo, _PA_IN_OUT_ size_t* PCommentBA)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	if (PTextPo != NULL && *PTextBA == 0) return 1;
	if (PCommentPo != NULL && *PCommentBA == 0) return 1;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = ��ʽ�ı���ʼFFu(PFormatTextPo);
	if (��ʽ�ı���ϢPo == NULL) return 1;
	Ⱥ������Po Ⱥ��Po = ����Ⱥ��FFu(PFDPo, ��ʽ�ı���ϢPo->Ⱥ���ı�Po);
	if (Ⱥ��Po == NULL)
	{
		��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
		return 1;
	}
	��Ŀ����Po ��ĿPo = ������ĿFFu(Ⱥ��Po, ��ʽ�ı���ϢPo->��Ŀ�ı�Po);
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	if (PTextPo != NULL && ��ĿPo->�ı�Po != NULL)
	{
		DATAMAXI �ı�BA = strlen(��ĿPo->�ı�Po) + 1;
		if (�ı�BA > *PTextBA) goto Error;
		strcpy(PTextPo, ��ĿPo->�ı�Po);
	}
	if (PCommentPo != NULL && ��ĿPo->ע��Po != NULL)
	{
		DATAMAXI �ı�BA = strlen(��ĿPo->ע��Po) + 1;
		if (�ı�BA > *PCommentBA) goto Error;
		strcpy(PCommentPo, ��ĿPo->ע��Po);
	}
	return 0;
Error:
	if (��ĿPo->�ı�Po != NULL)
		*PTextBA = strlen(��ĿPo->�ı�Po) + 1;
	if (��ĿPo->ע��Po != NULL)
		*PCommentBA = strlen(��ĿPo->ע��Po) + 1;
	return 1;
}

/**
 * @brief ����д�롣
 * @param PFDPo ��ʽ����Po��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PTextPo �ı�Po��
 * @param PCommentPo ע���ı�Po��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 *
 * ��������д���µ���Ϣ��
 * PTextPo �� PCommentPo ���Ϊ NULL �򲻸ı䡣
 * PTextPo �� PCommentPo ���Ϊ ""�����Ϊ NULL��
 * PTextPo �� PCommentPo �����Ϊ NULL �� ""�������ı������ݡ�
 * ����������򷵻�ʧ�ܡ�
 * �˺���ʧ�ܿ��ܻᵼ�����ݽṹ����
 *
 */
extern uint8_t ZHFD_FDDataWrite_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ char* PTextPo, _PA_IN_ char* PCommentPo)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = ��ʽ�ı���ʼFFu(PFormatTextPo);
	if (��ʽ�ı���ϢPo == NULL) return 1;
	Ⱥ������Po Ⱥ��Po = ����Ⱥ��FFu(PFDPo, ��ʽ�ı���ϢPo->Ⱥ���ı�Po);
	if (Ⱥ��Po == NULL)
	{
		��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
		return 1;
	}
	��Ŀ����Po ��ĿPo = ������ĿFFu(Ⱥ��Po, ��ʽ�ı���ϢPo->��Ŀ�ı�Po);
	DATAMAXI �������� = ��ʽ�ı���ϢPo->���ݱ�ʶ;
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	if (��ĿPo == NULL) return 1;
	/*�ı�*/
	if (PTextPo == NULL)
		/*NULL���򲻱�*/;
	else if (�ı��Ƚ�FFu(PTextPo, �հ��ı�, F) == F)
		/*""��������ı�*/
		�ı�����FFu(��ĿPo->����PoAr[��������]->�ı�Po);
	else
	{/*�����ı�*/
		DATAMAXI �ı����� = strlen(PTextPo);
		�ı�����Po �ı�Po = �ı���ʼFFu(�ı����� + 1);
		if (�ı�Po == NULL) return 1;
		strcpy(�ı�Po, PTextPo);
		�ı�����FFu(��ĿPo->����PoAr[��������]->�ı�Po);
		��ĿPo->����PoAr[��������]->�ı�Po = �ı�Po;
	}
	/*ע��*/
	if (PCommentPo == NULL)
		/*NULL���򲻱�*/;
	else if (�ı��Ƚ�FFu(PCommentPo, �հ��ı�, F) == F)
		/*""��������ı�*/
		�ı�����FFu(��ĿPo->����PoAr[��������]->ע��Po);
	else
	{/*�����ı�*/
		DATAMAXI �ı����� = strlen(PCommentPo);
		�ı�����Po ע��Po = �ı���ʼFFu(�ı����� + 1);
		if (ע��Po == NULL) return 1;
		strcpy(ע��Po, PCommentPo);
		�ı�����FFu(��ĿPo->����PoAr[��������]->ע��Po);
		��ĿPo->����PoAr[��������]->ע��Po = ע��Po;
	}
	return 0;
}
/**
 * @brief ���ݶ�ȡ��
 * @param PFDPo ��ʽ����Po��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PTextPo �ı�Po��
 * @param PTextBA �ı��ֽ�������
 * @param PCommentPo ע���ı�Po��
 * @param PCommentBA ע���ֽ�������
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
extern uint8_t ZHFD_FDDataRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo,
	_PA_OUT_ char* PTextPo, _PA_IN_OUT_ size_t* PTextBA, _PA_OUT_ char* PCommentPo, _PA_IN_OUT_ size_t* PCommentBA)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	if (PTextPo != NULL && *PTextBA == 0) return 1;
	if (PCommentPo != NULL && *PCommentBA == 0) return 1;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = ��ʽ�ı���ʼFFu(PFormatTextPo);
	if (��ʽ�ı���ϢPo == NULL) return 1;
	Ⱥ������Po Ⱥ��Po = ����Ⱥ��FFu(PFDPo, ��ʽ�ı���ϢPo->Ⱥ���ı�Po);
	if (Ⱥ��Po == NULL) return 1;
	��Ŀ����Po ��ĿPo = ������ĿFFu(Ⱥ��Po, ��ʽ�ı���ϢPo->��Ŀ�ı�Po);
	if (��ĿPo == NULL) return 1;
	DATAMAXI ��� = ��ʽ�ı���ϢPo->���ݱ�ʶ;
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	if (PTextPo != NULL && ��ĿPo->����PoAr[���]->�ı�Po != NULL)
	{
		DATAMAXI �ı�BA = strlen(��ĿPo->����PoAr[���]->�ı�Po) + 1;
		if (�ı�BA > *PTextBA) goto Error;
		strcpy(PTextPo, ��ĿPo->����PoAr[���]->�ı�Po);
	}
	if (PCommentPo != NULL && ��ĿPo->����PoAr[���]->ע��Po != NULL)
	{
		DATAMAXI �ı�BA = strlen(��ĿPo->����PoAr[���]->ע��Po) + 1;
		if (�ı�BA > *PCommentBA) goto Error;
		strcpy(PCommentPo, ��ĿPo->����PoAr[���]->ע��Po);
	}
	return 0;
Error:
	if (��ĿPo->����PoAr[���]->�ı�Po != NULL)
		*PTextBA = strlen(��ĿPo->����PoAr[���]->�ı�Po) + 1;
	if (��ĿPo->����PoAr[���]->ע��Po != NULL)
		*PCommentBA = strlen(��ĿPo->����PoAr[���]->ע��Po) + 1;
	return 1;
}

/*----------------------------------------------------------------
* ���ݣ�����{����}
----------------------------------------------------------------*/

/**
 * @brief �����ı�д�롣
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PDataTextBA �����ı�Po��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 *
 * ��� ���� �� ��ʽ���� Ⱥ�� �� ��Ŀ �С�
 * ��ʽ�ı���ʽ "Ⱥ��:��Ŀ"��
 *
 */
extern uint8_t ZHFD_DataTextWrite_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const char* PDataTextPo)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL || PFormatTextPo == NULL) return 1;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = ��ʽ�ı���ʼFFu(PFormatTextPo);
	if (��ʽ�ı���ϢPo == NULL) return 1;
	Ⱥ������Po Ⱥ��Po = Ⱥ������FFu(PFDPoPo, ��ʽ�ı���ϢPo->Ⱥ���ı�Po);
	if (Ⱥ��Po == NULL)
	{
		��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
		return 1;
	}
	��Ŀ����Po ��ĿPo = ��Ŀ����FFu(*PFDPoPo, &Ⱥ��Po, ��ʽ�ı���ϢPo->��Ŀ�ı�Po);
	if (��ĿPo == NULL)
	{
		��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
		return 1;
	}
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	��������Po ����Po = ��������FFu(Ⱥ��Po, &��ĿPo, PDataTextPo);
	if (����Po == NULL) return 1;
	return 0;
}
/**
 * @brief �����ı���ȡ��
 * @param PFDPo ��ʽ���ݽṹPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PDataTextPo �����ı�Po��
 * @param PDataTextBA �����ı��ֽ�������
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 *
 * ��ȡ ���� �� PDataTextPo��
 * ��� �����ı� Ϊ NULL�����é� PDataTextPo����� PDataTextPo Ϊ NULL���� ����ʧ�ܡ�
 * ��� PDataTextBA С�� �����ı��ֽ��������� PDataTextBA ������Ҫ���ֽ�����
 * ��ʽ�ı���ʽ "Ⱥ��:��Ŀ"��
 *
 * ���Ի�ȡ�����ֽ����� ZHFD_DataTextRead_FFu(PFDPo,"Ⱥ��:��Ŀ",NULL,&PDataTextBA);��
 *
 */
extern uint8_t ZHFD_DataTextRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ const char* PDataTextPo, _PA_IN_OUT_ size_t* PDataTextBA)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = ��ʽ�ı���ʼFFu(PFormatTextPo);
	if (��ʽ�ı���ϢPo == NULL) return 1;
	Ⱥ������Po Ⱥ��Po = ����Ⱥ��FFu(PFDPo, ��ʽ�ı���ϢPo->Ⱥ���ı�Po);
	if (Ⱥ��Po == NULL)
	{
		��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
		return 1;
	}
	��Ŀ����Po ��ĿPo = ������ĿFFu(Ⱥ��Po, ��ʽ�ı���ϢPo->��Ŀ�ı�Po);
	if (��ĿPo == NULL)
	{
		��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
		return 1;
	}
	DATAMAXI ��� = ��ʽ�ı���ϢPo->���ݱ�ʶ;
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	if (��ĿPo->����PoAr[���]->�ı�Po == NULL)
	{/*û���ı����� 0�����سɹ�*/
		if (PDataTextPo == NULL) return 1;
		memset(PDataTextPo, 0, *PDataTextBA);
		return 0;
	}
	DATAMAXI �ı�BA = strlen(��ĿPo->����PoAr[���]->�ı�Po) + 1;
	if (*PDataTextBA < �ı�BA)
	{
		*PDataTextBA = �ı�BA;
		return 1;
	}
	if (PDataTextPo == NULL) return 1;
	strcpy(PDataTextPo, ��ĿPo->����PoAr[���]->�ı�Po);
	return 0;
}

/**
 * @brief ����״̬д�롣
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PState ״̬��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
extern uint8_t ZHFD_DataStateWrite_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const uint8_t PState)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL || PFormatTextPo == NULL) return 1;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = ��ʽ�ı���ʼFFu(PFormatTextPo);
	if (��ʽ�ı���ϢPo == NULL) return 1;
	Ⱥ������Po Ⱥ��Po = Ⱥ������FFu(PFDPoPo, ��ʽ�ı���ϢPo->Ⱥ���ı�Po);
	if (Ⱥ��Po == NULL)
	{
		��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
		return 1;
	}
	��Ŀ����Po ��ĿPo = ��Ŀ����FFu(PFDPoPo, &Ⱥ��Po, ��ʽ�ı���ϢPo->��Ŀ�ı�Po);
	if (��ĿPo == NULL)
	{
		��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
		return 1;
	}
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	��������Po ����Po = NULL;
	if (PState == 0) ����Po = ��������FFu(Ⱥ��Po, &��ĿPo, �����ı�);
	else  ����Po = ��������FFu(Ⱥ��Po, &��ĿPo, ��ʼ�ı�);
	if (����Po == NULL) return 1;
	return 0;
}
/**
 * @brief ����״̬��ȡ��
 * @param PFDPo ��ʽ���ݽṹPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PStatePo ״̬Po��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
extern uint8_t ZHFD_DataStateRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ uint8_t* PStatePo)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	��������Po ����Po = �ṹ���ݶ�ȡFFu(PFDPo, PFormatTextPo);
	if (����Po == NULL) return 1;
	const char* �ı�Po = ����Po->�ı�Po;
	for (size_t i = 0; i < ArrayLength(����״̬Ar); i++)
		if (�ı�Po[0] == ����״̬Ar[i])
		{
			*PStatePo = 0;
			return 0;
		}
	for (size_t i = 0; i < ArrayLength(��ʼ״̬Ar); i++)
		if (�ı�Po[0] == ��ʼ״̬Ar[i])
		{
			*PStatePo = 1;
			return 0;
		}
	return 1;
}

/**
 * @brief ����д�롣
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PNSData ���ݡ�
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
extern uint8_t ZHFD_DataNSWrite_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const uint64_t PNSData)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL || PFormatTextPo == NULL) return 1;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = ��ʽ�ı���ʼFFu(PFormatTextPo);
	if (��ʽ�ı���ϢPo == NULL) return 1;
	Ⱥ������Po Ⱥ��Po = Ⱥ������FFu(PFDPoPo, ��ʽ�ı���ϢPo->Ⱥ���ı�Po);
	if (Ⱥ��Po == NULL)
	{
		��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
		return 1;
	}
	��Ŀ����Po ��ĿPo = ��Ŀ����FFu(*PFDPoPo, &Ⱥ��Po, ��ʽ�ı���ϢPo->��Ŀ�ı�Po);
	if (��ĿPo == NULL)
	{
		��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
		return 1;
	}
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	�ı����� �ı�Ar[0x100] = { 0 };
	sprintf(&�ı�Ar, "%llu", PNSData);
	��������Po ����Po = ��������FFu(Ⱥ��Po, &��ĿPo, �ı�Ar);
	if (����Po == NULL) return 1;
	return 0;
}
/**
 * @brief ���ݶ�ȡ��
 * @param PFDPo ��ʽ���ݽṹPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PNSDataPo ����Po��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
extern uint8_t ZHFD_DataNSRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ uint64_t* PNSDataPo)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	��������Po ����Po = �ṹ���ݶ�ȡFFu(PFDPo, PFormatTextPo);
	if (����Po == NULL) return 1;
	*PNSDataPo = strtoull(����Po->�ı�Po, NULL, 10);
	return 0;
}

/**
 * @brief ��������д�롣
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PSIData �������ݡ�
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
extern uint8_t ZHFD_DataSIWrite_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const int64_t PSIData)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL || PFormatTextPo == NULL) return 1;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = ��ʽ�ı���ʼFFu(PFormatTextPo);
	if (��ʽ�ı���ϢPo == NULL) return 1;
	Ⱥ������Po Ⱥ��Po = Ⱥ������FFu(PFDPoPo, ��ʽ�ı���ϢPo->Ⱥ���ı�Po);
	if (Ⱥ��Po == NULL)
	{
		��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
		return 1;
	}
	��Ŀ����Po ��ĿPo = ��Ŀ����FFu(*PFDPoPo, &Ⱥ��Po, ��ʽ�ı���ϢPo->��Ŀ�ı�Po);
	if (��ĿPo == NULL)
	{
		��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
		return 1;
	}
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	�ı����� �ı�Ar[0x100] = { 0 };
	sprintf(&�ı�Ar, "%lld", PSIData);
	��������Po ����Po = ��������FFu(Ⱥ��Po, &��ĿPo, �ı�Ar);
	if (����Po == NULL) return 1;
	return 0;
}
/**
 * @brief �������ݶ�ȡ��
 * @param PFDPo ��ʽ���ݽṹPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PSIDataPo �������ݡ�
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
extern uint8_t ZHFD_DataSIRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ int64_t* PSIDataPo)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	��������Po ����Po = �ṹ���ݶ�ȡFFu(PFDPo, PFormatTextPo);
	if (����Po == NULL) return 1;
	*PSIDataPo = strtoll(����Po->�ı�Po, NULL, 10);
	return 0;
}

/**
 * @brief ��������д�롣
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PPointData �������ݡ�
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
extern uint8_t ZHFD_DataFloatWrite_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const long double PPointData)
{
	if (PFDPoPo == NULL || *PFDPoPo == NULL || PFormatTextPo == NULL) return 1;
	��ʽ�ı�����Po ��ʽ�ı���ϢPo = ��ʽ�ı���ʼFFu(PFormatTextPo);
	if (��ʽ�ı���ϢPo == NULL) return 1;
	Ⱥ������Po Ⱥ��Po = Ⱥ������FFu(PFDPoPo, ��ʽ�ı���ϢPo->Ⱥ���ı�Po);
	if (Ⱥ��Po == NULL)
	{
		��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
		return 1;
	}
	��Ŀ����Po ��ĿPo = ��Ŀ����FFu(*PFDPoPo, &Ⱥ��Po, ��ʽ�ı���ϢPo->��Ŀ�ı�Po);
	if (��ĿPo == NULL)
	{
		��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
		return 1;
	}
	��ʽ�ı�����FFu(��ʽ�ı���ϢPo);
	�ı����� �ı�Ar[0x100] = { 0 };
	sprintf(&�ı�Ar, "%lf", PPointData);
	��������Po ����Po = ��������FFu(Ⱥ��Po, &��ĿPo, �ı�Ar);
	if (����Po == NULL) return 1;
	return 0;
}
/**
 * @brief �������ݶ�ȡ��
 * @param PFDPo ��ʽ���ݽṹPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PPointDataPo �������ݡ�
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
extern uint8_t ZHFD_DataFloatRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ long double* PPointDataPo)
{
	if (PFDPo == NULL || PFormatTextPo == NULL) return 1;
	��������Po ����Po = �ṹ���ݶ�ȡFFu(PFDPo, PFormatTextPo);
	if (����Po == NULL) return 1;
	*PPointDataPo = strtold(����Po->�ı�Po, NULL);
	return 0;
}
