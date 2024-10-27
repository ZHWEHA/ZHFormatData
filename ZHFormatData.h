#pragma once
#include<stdint.h>
#include<float.h>

#define _PA_IN_
#define _PA_OUT_
#define _PA_IN_OUT_

/*格式数据结构*/
typedef struct ZHFormatDataSt* ZHFDStPo;

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
ZHFDStPo ZHFD_FDStart_PFu(void);
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
void ZHFD_FDEnd_PFu(_PA_IN_ ZHFDStPo PFoDaPo);

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
uint8_t ZHFD_FDFWrite_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFileNamePo);
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
uint8_t ZHFD_FDFRead_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFileNamePo);

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
uint8_t ZHFD_FDGroupStart_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PTextPo, _PA_IN_ const char* PCommentPo);
/**
 * @brief 结束群组。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PFormatTextPo 格式文本Po。
 * @return 成功返回：0；失败返回：!0；
 */
uint8_t ZHFD_FDGroupEnd_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo);

/**
 * @brief 开始条目。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PFormatTextPo 格式文本指针。
 * @param PTextPo 文本Po。
 * @param PCommentPo 注释文本Po。
 * @return 成功返回：0；失败返回：!0；
 */
uint8_t ZHFD_FDItemStart_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const char* PTextPo, _PA_IN_ const char* PCommentPo);
/**
 * @brief 结束条目。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PFormatTextPo 格式文本Po。
 * @return 成功返回：0；失败返回：!0；
 *
 * 如果群组内没有目标条目，则返回成功。
 *
 */
uint8_t ZHFD_FDItemEnd_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo);

/**
 * @brief 开始数据。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PFormatTextPo 格式文本Po。
 * @param PTextPo 文本Po。
 * @param PCommentPo 注释文本Po。
 * @return 成功返回：0；失败返回：!0；
 */
uint8_t ZHFD_FDDataStart_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const char* PTextPo, _PA_IN_ const char* PCommentPo);
/**
 * @brief 结束数据。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PFormatTextPo 格式文本Po。
 * @return 成功返回：0；失败返回：!0；
 */
uint8_t ZHFD_FDDataEnd_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo);

/*----------------------------------------------------------------
* 元素读写：阴面{底层}
----------------------------------------------------------------*/

/**
 * @brief 群组写入。
 * @param PFDPo 格式数据指针。
 * @param PFormatTextPo 格式文本指针。
 * @param PTextPo 文本指针。
 * @param PCommentPo 注释文本指针。
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
uint8_t ZHFD_FDGroupWrite_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ char* PTextPo, _PA_IN_ char* PCommentPo);
/**
 * @brief 群组读取。
 * @param PFDPo 格式数据指针。
 * @param PFormatTextPo 格式文本指针。
 * @param PTextPo 文本指针。
 * @param PTextBA 文本字节数量。
 * @param PCommentPo 注释文本指针。
 * @param PCommentBA 注释字节数量。
 * @return 成功返回：0；失败返回：!0；
 */
uint8_t ZHFD_FDGroupRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ char* PTextPo, _PA_IN_OUT_ size_t* PTextBA, _PA_OUT_ char* PCommentPo, _PA_IN_OUT_ size_t* PCommentBA);

/**
 * @brief 条目写入。
 * @param PFDPo 格式数据指针。
 * @param PFormatTextPo 格式文本指针。
 * @param PTextPo 文本指针。
 * @param PCommentPo 注释文本指针。
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
uint8_t ZHFD_FDItemWrite_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ char* PTextPo, _PA_IN_ char* PCommentPo);
/**
 * @brief 条目读取。
 * @param PFDPo 格式数据指针。
 * @param PFormatTextPo 格式文本指针。
 * @param PTextPo 文本指针。
 * @param PTextBA 文本字节数量。
 * @param PCommentPo 注释文本指针。
 * @param PCommentBA 注释字节数量。
 * @return 成功返回：0；失败返回：!0；
 */
uint8_t ZHFD_FDItemRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ char* PTextPo, _PA_IN_OUT_ size_t* PTextBA, _PA_OUT_ char* PCommentPo, _PA_IN_OUT_ size_t* PCommentBA);

/**
 * @brief 数据写入。
 * @param PFDPo 格式数据指针。
 * @param PFormatTextPo 格式文本指针。
 * @param PTextPo 文本指针。
 * @param PCommentPo 注释文本指针。
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
uint8_t ZHFD_FDDataWrite_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ char* PTextPo, _PA_IN_ char* PCommentPo);
/**
 * @brief 数据读取。
 * @param PFDPo 格式数据指针。
 * @param PFormatTextPo 格式文本指针。
 * @param PTextPo 文本指针。
 * @param PTextBA 文本字节数量。
 * @param PCommentPo 注释文本指针。
 * @param PCommentBA 注释字节数量。
 * @return 成功返回：0；失败返回：!0；
 */
uint8_t ZHFD_FDDataRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ char* PTextPo, _PA_IN_OUT_ size_t* PTextBA, _PA_OUT_ char* PCommentPo, _PA_IN_OUT_ size_t* PCommentBA);

/*----------------------------------------------------------------
* 数据：阳面{顶层}
----------------------------------------------------------------*/

/**
 * @brief 数据文本写入。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PFormatTextPo 格式文本指针。
 * @param PDataTextPo 数据文本指针。
 * @return 成功返回：0；失败返回：!0；
 *
 * 添加 数据 到 格式数据 群组 的 条目 中。
 * 格式文本格式 "群组:条目"。
 *
 */
uint8_t ZHFD_DataTextWrite_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const char* PDataTextPo);
/**
 * @brief 数据文本读取。
 * @param PFDPo 格式数据结构Po。
 * @param PFormatTextPo 格式文本指针。
 * @param PDataTextPo 数据文本指针。
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
uint8_t ZHFD_DataTextRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ const char* PDataTextPo, _PA_IN_OUT_ size_t* PDataTextBA);

/**
 * @brief 数据状态写入。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PFormatTextPo 格式文本指针。
 * @param PState 状态。
 * @return 成功返回：0；失败返回：!0；
 */
uint8_t ZHFD_DataStateWrite_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const uint8_t PState);
/**
 * @brief 数据状态读取。
 * @param PFDPo 格式数据结构Po。
 * @param PFormatTextPo 格式文本Po。
 * @param PStatePo 状态Po。
 * @return 成功返回：0；失败返回：!0；
 */
uint8_t ZHFD_DataStateRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ uint8_t* PStatePo);

/**
 * @brief 数据写入。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PFormatTextPo 格式文本Po。
 * @param PNSData 数据。
 * @return 成功返回：0；失败返回：!0；
 */
uint8_t ZHFD_DataNSWrite_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const uint64_t PNSData);
/**
 * @brief 数据读取。
 * @param PFDPo 格式数据结构Po。
 * @param PFormatTextPo 格式文本Po。
 * @param PNSDataPo 数据Po。
 * @return 成功返回：0；失败返回：!0；
 */
uint8_t ZHFD_DataNSRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ uint64_t* PNSDataPo);

/**
 * @brief 符号数据写入。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PFormatTextPo 格式文本Po。
 * @param PSIData 符号数据。
 * @return 成功返回：0；失败返回：!0；
 */
uint8_t ZHFD_DataSIWrite_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const int64_t PSIData);
/**
 * @brief 符号数据读取。
 * @param PFDPo 格式数据结构Po。
 * @param PFormatTextPo 格式文本Po。
 * @param PSIDataPo 符号数据。
 * @return 成功返回：0；失败返回：!0；
 */
uint8_t ZHFD_DataSIRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ int64_t* PSIDataPo);

/**
 * @brief 浮点数据写入。
 * @param PFDPoPo 格式数据结构PoPo。
 * @param PFormatTextPo 格式文本Po。
 * @param PPointData 浮点数据。
 * @return 成功返回：0；失败返回：!0；
 */
uint8_t ZHFD_DataFloatWrite_FFu(_PA_IN_OUT_ ZHFDStPo* PFDPoPo, _PA_IN_ const char* PFormatTextPo, _PA_IN_ const long double PPointData);
/**
 * @brief 浮点数据读取。
 * @param PFDPo 格式数据结构Po。
 * @param PFormatTextPo 格式文本Po。
 * @param PPointDataPo 符号数据。
 * @return 成功返回：0；失败返回：!0；
 */
uint8_t ZHFD_DataFloatRead_FFu(_PA_IN_ const ZHFDStPo PFDPo, _PA_IN_ const char* PFormatTextPo, _PA_OUT_ long double* PPointDataPo);
