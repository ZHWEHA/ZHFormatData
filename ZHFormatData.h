#pragma once
#include<stdint.h>
#include<float.h>

#define _PA_IN_
#define _PA_OUT_
#define _PA_IN_OUT_

/*��ʽ���ݽṹ*/
typedef struct ZHFormatDataSt* ZHFDStPo;

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
ZHFDStPo ZHFD_FDStart_PFu(void);
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
void ZHFD_FDEnd_PFu(_PA_IN_ ZHFDStPo PFoDaPo);

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
uint8_t ZHFD_FDFWrite_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFileNamePo);
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
uint8_t ZHFD_FDFRead_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFileNamePo);

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
uint8_t ZHFD_FDGroupStart_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PTextPo, _PA_IN_ const char* PCommentPo);
/**
 * @brief ����Ⱥ�顣
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
uint8_t ZHFD_FDGroupEnd_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo);

/**
 * @brief ��ʼ��Ŀ��
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PFormatTextPo ��ʽ�ı�ָ�롣
 * @param PTextPo �ı�Po��
 * @param PCommentPo ע���ı�Po��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
uint8_t ZHFD_FDItemStart_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const char* PTextPo, _PA_IN_ const char* PCommentPo);
/**
 * @brief ������Ŀ��
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 *
 * ���Ⱥ����û��Ŀ����Ŀ���򷵻سɹ���
 *
 */
uint8_t ZHFD_FDItemEnd_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo);

/**
 * @brief ��ʼ���ݡ�
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PTextPo �ı�Po��
 * @param PCommentPo ע���ı�Po��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
uint8_t ZHFD_FDDataStart_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const char* PTextPo, _PA_IN_ const char* PCommentPo);
/**
 * @brief �������ݡ�
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
uint8_t ZHFD_FDDataEnd_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo);

/*----------------------------------------------------------------
* Ԫ�ض�д������{�ײ�}
----------------------------------------------------------------*/

/**
 * @brief Ⱥ��д�롣
 * @param PFDPo ��ʽ����ָ�롣
 * @param PFormatTextPo ��ʽ�ı�ָ�롣
 * @param PTextPo �ı�ָ�롣
 * @param PCommentPo ע���ı�ָ�롣
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
uint8_t ZHFD_FDGroupWrite_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ char* PTextPo, _PA_IN_ char* PCommentPo);
/**
 * @brief Ⱥ���ȡ��
 * @param PFDPo ��ʽ����ָ�롣
 * @param PFormatTextPo ��ʽ�ı�ָ�롣
 * @param PTextPo �ı�ָ�롣
 * @param PTextBA �ı��ֽ�������
 * @param PCommentPo ע���ı�ָ�롣
 * @param PCommentBA ע���ֽ�������
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
uint8_t ZHFD_FDGroupRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ char* PTextPo, _PA_IN_OUT_ size_t* PTextBA, _PA_OUT_ char* PCommentPo, _PA_IN_OUT_ size_t* PCommentBA);

/**
 * @brief ��Ŀд�롣
 * @param PFDPo ��ʽ����ָ�롣
 * @param PFormatTextPo ��ʽ�ı�ָ�롣
 * @param PTextPo �ı�ָ�롣
 * @param PCommentPo ע���ı�ָ�롣
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
uint8_t ZHFD_FDItemWrite_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ char* PTextPo, _PA_IN_ char* PCommentPo);
/**
 * @brief ��Ŀ��ȡ��
 * @param PFDPo ��ʽ����ָ�롣
 * @param PFormatTextPo ��ʽ�ı�ָ�롣
 * @param PTextPo �ı�ָ�롣
 * @param PTextBA �ı��ֽ�������
 * @param PCommentPo ע���ı�ָ�롣
 * @param PCommentBA ע���ֽ�������
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
uint8_t ZHFD_FDItemRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ char* PTextPo, _PA_IN_OUT_ size_t* PTextBA, _PA_OUT_ char* PCommentPo, _PA_IN_OUT_ size_t* PCommentBA);

/**
 * @brief ����д�롣
 * @param PFDPo ��ʽ����ָ�롣
 * @param PFormatTextPo ��ʽ�ı�ָ�롣
 * @param PTextPo �ı�ָ�롣
 * @param PCommentPo ע���ı�ָ�롣
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
uint8_t ZHFD_FDDataWrite_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ char* PTextPo, _PA_IN_ char* PCommentPo);
/**
 * @brief ���ݶ�ȡ��
 * @param PFDPo ��ʽ����ָ�롣
 * @param PFormatTextPo ��ʽ�ı�ָ�롣
 * @param PTextPo �ı�ָ�롣
 * @param PTextBA �ı��ֽ�������
 * @param PCommentPo ע���ı�ָ�롣
 * @param PCommentBA ע���ֽ�������
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
uint8_t ZHFD_FDDataRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ char* PTextPo, _PA_IN_OUT_ size_t* PTextBA, _PA_OUT_ char* PCommentPo, _PA_IN_OUT_ size_t* PCommentBA);

/*----------------------------------------------------------------
* ���ݣ�����{����}
----------------------------------------------------------------*/

/**
 * @brief �����ı�д�롣
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PFormatTextPo ��ʽ�ı�ָ�롣
 * @param PDataTextPo �����ı�ָ�롣
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 *
 * ��� ���� �� ��ʽ���� Ⱥ�� �� ��Ŀ �С�
 * ��ʽ�ı���ʽ "Ⱥ��:��Ŀ"��
 *
 */
uint8_t ZHFD_DataTextWrite_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const char* PDataTextPo);
/**
 * @brief �����ı���ȡ��
 * @param PFDPo ��ʽ���ݽṹPo��
 * @param PFormatTextPo ��ʽ�ı�ָ�롣
 * @param PDataTextPo �����ı�ָ�롣
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
uint8_t ZHFD_DataTextRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ const char* PDataTextPo, _PA_IN_OUT_ size_t* PDataTextBA);

/**
 * @brief ����״̬д�롣
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PFormatTextPo ��ʽ�ı�ָ�롣
 * @param PState ״̬��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
uint8_t ZHFD_DataStateWrite_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const uint8_t PState);
/**
 * @brief ����״̬��ȡ��
 * @param PFDPo ��ʽ���ݽṹPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PStatePo ״̬Po��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
uint8_t ZHFD_DataStateRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ uint8_t* PStatePo);

/**
 * @brief ����д�롣
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PNSData ���ݡ�
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
uint8_t ZHFD_DataNSWrite_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const uint64_t PNSData);
/**
 * @brief ���ݶ�ȡ��
 * @param PFDPo ��ʽ���ݽṹPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PNSDataPo ����Po��
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
uint8_t ZHFD_DataNSRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ uint64_t* PNSDataPo);

/**
 * @brief ��������д�롣
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PSIData �������ݡ�
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
uint8_t ZHFD_DataSIWrite_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const int64_t PSIData);
/**
 * @brief �������ݶ�ȡ��
 * @param PFDPo ��ʽ���ݽṹPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PSIDataPo �������ݡ�
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
uint8_t ZHFD_DataSIRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ int64_t* PSIDataPo);

/**
 * @brief ��������д�롣
 * @param PFDPoPo ��ʽ���ݽṹPoPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PPointData �������ݡ�
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
uint8_t ZHFD_DataFloatWrite_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const long double PPointData);
/**
 * @brief �������ݶ�ȡ��
 * @param PFDPo ��ʽ���ݽṹPo��
 * @param PFormatTextPo ��ʽ�ı�Po��
 * @param PPointDataPo �������ݡ�
 * @return �ɹ����أ�0��ʧ�ܷ��أ�!0��
 */
uint8_t ZHFD_DataFloatRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ long double* PPointDataPo);
