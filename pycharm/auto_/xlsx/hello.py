import pandas as pd

# 读取Excel文件
file_path = 'E:/WeChat Files/WeChat Files/wxid_zgdnaj2cqtfj22/FileStorage/File/2023-11/中小学报单模板汇总1hgfh12.xlsx'
# df = pd.read_excel(file_path)
#
# # 提取C、D和E列的数据
# # 假设C、D和E列分别对应的是 '食材名称', '单位数量', '价格'
# # 如果列名不同，请替换为实际的列名
# extracted_data = df[['食材名称', '单位数量', '价格']]
#
# # 只选择第4行及之后的数据（基于0索引，所以使用3:）
# extracted_data = extracted_data.iloc[3:]
#
# # 将提取的数据保存到新的Excel文件中
# new_file_path = 'E:/Documents/ProjectE/VS_code/py/xls/extracted_data.xlsx'  # 可以更改新文件的名称和路径
# extracted_data.to_excel(new_file_path, index=False)
# import pandas as pd
#
# file_path = 'your_file_path_here.xlsx'  # 替换为你的文件路径
df = pd.read_excel(file_path)
print(df.columns)  # 打印列名
