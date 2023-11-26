import requests
import xlrd
import xlwt
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

# 打开 Excel 文件
workbook = xlrd.open_workbook('test.xls')
worksheet = workbook.sheet_by_index(0)

# 创建一个新的 Excel 文件，用于保存结果
output_workbook = xlwt.Workbook()
output_worksheet = output_workbook.add_sheet('Output')


# 在指定位置查询信息并将结果写入输出文件
for i in range(worksheet.nrows):
    name = worksheet.cell_value(147, 2)

    data_element = WebDriverWait(driver, 10).until(
        EC.presence_of_element_located((By.CLASS_NAME, '身份证号码'))
    )
    data = data_element.text.split('\n')
    if data:
        output_worksheet.write(i, 1, data[0])

# 将结果保存到 Excel 文件
output_workbook.save('output.xls')

# 关闭 Webdriver
driver.quit()
