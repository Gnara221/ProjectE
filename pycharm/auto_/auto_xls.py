import xlrd
import xlwt
'''
在同一个文件中查找相同姓名并将所在行的数据复制到另外的区域
'''
# 打开 Excel 文件
workbook = xlrd.open_workbook('5.6信软学院寝室卫生安全检查活动.xls')
worksheet = workbook.sheet_by_index(0)

# 创建一个新的 Excel 文件，用于保存结果
output_workbook = xlwt.Workbook()
output_worksheet = output_workbook.add_sheet('output.xls')

# 遍历第 X 列第 156 行开始的所有姓名数据
X = 1
L1_start = 3690
L1_end = 3696
L2_start = 0
L2_end = 3680
Q = 3
#L1为需要被查找的数据起始行
for i in range(L1_start, L1_end):
    name = worksheet.cell_value(i, 1)
    output_worksheet.write(i, 1, name)
    found = False
    # 在同一列第 L2 行开始遍历查询姓名,Q 为查询到姓名所对应的身份证号码列数
    for j in range(L2_start, L2_end):
        if worksheet.cell_value(j, X) != name:
            continue
        if worksheet.cell_value(j, X) == name and worksheet.cell_value(j, Q) != '':
            # 如果查询到的那一行第 4 列的属性 '身份证号码' 不为空，就将对应的身份证号码写进最开始得到姓名数据的那一行对应的第 Q 列里面
            output_worksheet.write(i, Q, worksheet.cell_value(j, Q))
            output_worksheet.write(i, Q-3, worksheet.cell_value(j, Q-3))
            output_worksheet.write(i, Q-1, worksheet.cell_value(j, Q-1))
            found = True
            break
    if not found:
        output_worksheet.write(i, Q, '')

# 将结果保存到 Excel 文件
output_workbook.save('output.xls')
print('OK')
