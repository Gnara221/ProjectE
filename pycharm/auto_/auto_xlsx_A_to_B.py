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

# 定义A表格和B表格的路径
a_file_path = 'E:/Documents/Project/pycharm/auto_/test2.xlsx'
b_file_path = 'E:/Documents/Project/pycharm/auto_/test1.xlsx'

# 读取A表格的数据，并提取姓名列
a_df = pd.read_excel(a_file_path)


names = a_df.iloc[0:, 2].tolist()
dates = a_df.iloc[0:, 3].tolist()



# 读取B表格的数据，并根据姓名匹配数据
b_df = pd.read_excel(b_file_path)
matched_data = []
for name in names:
    temp_df = b_df[b_df['number'] == name]
    if not temp_df.empty:
        matched_data.append(temp_df.iloc[0])

# 将匹配到的数据写入到C表格的相应位置
for i, row in a_df.iterrows():
    a_df.iloc[i, 1] = a_df.iloc[i, 2]
    a_df.iloc[i, 0] = a_df.iloc[i, 3]
    name = row[2]
    for data in matched_data:
        if data['number'] == name:
            a_df.iloc[i, 1] = a_df.iloc[i, 2]
            a_df.iloc[i, 2] = data.iloc[15]

    new_column = ['date', 'number', 'name']
    for i in range(15):
        new_column.append('')

    a_df = a_df.rename(columns = {a_df.columns[0]: 'date', a_df.columns[1]: 'number', a_df.columns[2]: 'name' } )



# 读取更新后的A表格
a_file_path = 'E:/Documents/Project/pycharm/auto_/updated_A3.xlsx'

# 读取更新后的A表格数据，仅保留前三列
a_df = pd.read_excel(a_file_path, usecols=[0, 1, 2])

# 将date列转换为日期类型
a_df['date'] = pd.to_datetime(a_df['date'])

# 对数据按照date列进行分组，将每组的name列数值相加并转换为浮点数
a_df['name'] = a_df['name'].astype(float)
grouped = a_df.groupby('date').agg({'number': 'first', 'name': 'sum'}).reset_index()

# 将每组的最后一行下方插入一行数据，'date'列与上一行一致，'number'列为空，‘name’列为前面加到一起的name浮点数
new_rows = []
for i, row in grouped.iterrows():
    new_row = {'date': row['date'], 'number': '', 'name': row['name']}
    new_rows.append(row)
    new_rows.append(new_row)

new_rows_list = [row.tolist() for row in new_rows]
new_df = pd.concat([a_df, pd.DataFrame(new_rows_list)], ignore_index=True)


# 将更新后的数据保存为新文件
new_df.to_excel('E:/Documents/Project/pycharm/auto_/new_updated_A3.xlsx', index=False)

