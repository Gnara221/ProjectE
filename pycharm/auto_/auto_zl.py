'''
description: 
param: 
return: 
'''
'''
description: 
param: 
return: 
'''
import pandas as pd
import os

# 定义输入文件夹路径和输出文件路径
input_folder = 'E:/Documents/Project/pycharm/auto_/xlsx'
output_file = 'E:/Documents/Project/pycharm/auto_/file.xlsx'

# 获取所有xlsx文件的文件名
file_names = [f for f in os.listdir(input_folder) if f.endswith('.xlsx')]

# 初始化一个空的DataFrame
df = pd.DataFrame(columns=['ID', '姓名', '手机号码', '身份证号码', '所属组织', '服务时长'])

# 遍历所有文件，将它们的数据合并到一个DataFrame中
for file_name in file_names:
    file_path = os.path.join(input_folder, file_name)
    temp_df = pd.read_excel(file_path, header=None)
    df = pd.concat([df, temp_df], axis=0, ignore_index=True)

# 将合并后的DataFrame写入到一个新的xlsx文件中
df.to_excel(output_file, index=False)
