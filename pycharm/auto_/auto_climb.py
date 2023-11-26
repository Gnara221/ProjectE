'''
description: 
param: 
return: 
'''
import requests
import xlrd
import xlwt
from pandas._libs import json
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC


cookie_jar = requests.cookies.RequestsCookieJar()

with open('cookie.txt') as f:
    cookiejson = json.loads(f.read())
    for cookie in cookiejson():
        cookie_jar.set(
            name = cookie['name'],
            value = cookie['value'],
            domain = cookie['domain'],
            path = cookie['path']
        )

# # 打开 Excel 文件
# workbook = xlrd.open_workbook('test.xls')
# worksheet = workbook.sheet_by_index(0)

# # 创建一个新的 Excel 文件，用于保存结果
# output_workbook = xlwt.Workbook()
# output_worksheet = output_workbook.add_sheet('Output')

# # 初始化 Webdriver
# driver = webdriver.Chrome()

# # 在指定位置查询信息并将结果写入输出文件
# for i in range(160, worksheet.nrows):
#     name = worksheet.cell_value(i, 2)
#     id_card = worksheet.cell_value(i, 3)
#     if not id_card:
#         driver.get('https://sczyz.org.cn/zysc/#/volunteer/managingVolunteers')
#         search_box = WebDriverWait(driver, 10).until(
#             EC.presence_of_element_located((By.NAME, '搜索'))
#         )
#         search_box.send_keys(name)
#         search_box.send_keys(Keys.RETURN)
#         WebDriverWait(driver, 10).until(
#             EC.url_contains('/results')
#         )
#         data_element = WebDriverWait(driver, 10).until(
#             EC.presence_of_element_located((By.XPATH, '//table/tbody/tr'))
#         )
#         data = data_element.text.split('\n')
#         if len(data) > 1:
#             id_card = data[1].split()[1]
#             output_worksheet.write(i, 3, id_card)

# # 将结果保存到 Excel 文件
# output_workbook.save('output.xls')

# # 关闭 Webdriver
# driver.quit()
