## ZHFormatData

## 说明

`ZHFormatData`是一个功能丰富的 C 语言代码库，旨在提供一种高效、灵活的方式来处理配置文件和数据存储。它支持多种数据类型，包括文本、数值、符号和浮点数，并允许开发者以树状结构组织数据。

## 特点：

1. **树状数据结构**：`ZHFormatData`使用群组`Group`、条目`Item`和数据`Data`的概念来组织数据，形成了一个类似树状的结构，使得数据层次分明，易于管理。
  
2. **多种数据类型支持**：除了基本的文本数据，`ZHFormatData` 还支持无符号整数（`uint64_t`）、有符号整数（`int64_t`）和浮点数（`long double`）类型的数据存储和读取。
  
3. **注释功能**：允许在群组、条目、数据后中添加注释，增强了代码的可读性和维护性。
  
4. **格式文本**：格式文本是人类可读的，便于用户的修改。
  
5. **内存管理**：提供了明确的内存分配和释放函数，确保资源的有效管理，防止内存泄漏。并且利于开发新功能。
  
6. **错误处理**：函数返回值明确指示操作的成功或失败，便于错误处理和调试。
  
7. **文件读写**：支持将数据结构直接读写到文件中，方便数据的持久化存储和加载。
  
8. **文件结构**：文件的结构不是特别的严格，有部分的错误是可以忽略的。
  

## 功能：

1. **数据结构的创建和销毁**：
  
  - `ZHFD_FDStart_PFu`：初始化一个新的格式数据结构。
  - `ZHFD_FDEnd_PFu`：释放格式数据结构及其所有子结构的内存。
2. **文件操作**：
  
  - `ZHFD_FDFWrite_FFu`：将格式数据写入文件。
  - `ZHFD_FDFRead_FFu`：从文件读取数据到格式数据结构。
3. **群组操作**：
  
  - `ZHFD_FDGroupStart_FFu` 和 `ZHFD_FDGroupEnd_FFu`：开始和结束一个群组的定义。
  - `ZHFD_FDGroupWrite_FFu` 和 `ZHFD_FDGroupRead_FFu`：写入和读取群组信息。
4. **条目操作**：
  
  - `ZHFD_FDItemStart_FFu` 和 `ZHFD_FDItemEnd_FFu`：开始和结束一个条目定义。
  - `ZHFD_FDItemWrite_FFu` 和 `ZHFD_FDItemRead_FFu`：写入和读取条目信息。
5. **数据操作**：
  
  - `ZHFD_FDDataStart_FFu` 和 `ZHFD_FDDataEnd_FFu`：开始和结束一个数据定义。
  - `ZHFD_FDDataWrite_FFu` 和 `ZHFD_FDDataRead_FFu`：写入和读取数据信息。
6. **高级数据写入**：
  
  - `ZHFD_DataTextWrite_FFu` 和 `ZHFD_DataTextRead_FFu`：针对文本数据的写入和读取。
  - `ZHFD_DataStateWrite_FFu` 和 `ZHFD_DataStateRead_FFu`：针对状态数据的写入和读取。
  - `ZHFD_DataNSWrite_FFu` 和 `ZHFD_DataNSRead_FFu`：针对无符号整数数据的写入和读取。
  - `ZHFD_DataSIWrite_FFu` 和 `ZHFD_DataSIRead_FFu`：针对有符号整数数据的写入和读取。
  - `ZHFD_DataFloatWrite_FFu` 和 `ZHFD_DataFloatRead_FFu`：针对浮点数数据的写入和读取。
