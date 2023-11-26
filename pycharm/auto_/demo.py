import datetime
import re

import openpyxl
import requests
from lxml import etree


def get_url_html(url):
    """
    定义一个函数, 新建一个空变量html_str， 请求网页获取网页源码，如果请求成功，则返回结果，如果失败则返回空值
    url: 入参参数, 指的是我们普通浏览器中的访问网址
    """
    html_str = ""
    try:
        """获取网页请求之后，返回的网页源码，类似于在浏览器中右击选择网页源码, 使用三方库etree把网页源码字符串转换成HTML格式"""
        r = requests.get(url, timeout=200).text
        html_str = etree.HTML(r)
    except Exception as e:
        print(e)
    return html_str


def get_page_total(html_str):
    """
    定义一个函数, 新建一个变量pages初始值为0， 在网页源码中匹配出总页数的数值，如果匹配成功返回结果，如果失败则返回0
    html_str: 入参参数, 指的是网页源码，HTML格式的
    """
    pages = 0
    try:
        """查找网页源码中的xpath，找到总页数所在的xptah位置，并获取它的文本，举例子：页/78页，然后通过正则匹配出78这两个数字"""
        pages_str = html_str.xpath('//div[@class="contentshow"]//div[@class="box"]//div[@class="page"][2]//div[@class="goTextInput"]/text()')
        pages = re.findall("\d+", pages_str[1])[0]
    except Exception as e:
        print(e)
    return pages


def get_page_data(html_str):
    """
    定义一个函数, 新建一个变量pdata_list初始值为空列表（也可以叫空数组）， 在网页源码中匹配出每一行的内容
    html_str: 入参参数, 指的是网页源码，HTML格式的
    """
    data_list = []
    try:
        """查找网页源码中的xpath，找到每一行的位置"""
        option = html_str.xpath('//div[@class="contentshow"]//div[@class="box"]/table/tbody[2]//tr')
        for op in option:
            """根据每一行，匹配出第一列的字符串，比如'2021年10月20日'，再通过正则匹配出它的数字部分用'/'隔开，则把字符串转换成2021/10/20"""
            col1 = "/".join(re.findall("\d+", op.xpath("./td[1]/text()")[0]))
            """根据每一行，匹配出其他4列的数字字符串，然后通过函数转换，将字符串转换成浮点类型, 获取失败则为空值"""
            try:
                col2 = float(op.xpath("./td[2]/text()")[0])
            except:
                col2 = ""
            try:
                col3 = float(op.xpath("./td[3]/text()")[0])
            except:
                col3 = ""
            try:
                col4 = float(op.xpath("./td[4]/text()")[0])
            except:
                col4 = ""
            try:
                col5 = float(op.xpath("./td[5]/text()")[0])
            except:
                col5 = ""
            data_list.append([col1, col2, col3, col4, col5])
    except Exception as e:
        print(e)
    return data_list


def write_excel(file_name, write_list):
    """
    定义一个函数, 将每一行的数据汇总的数组，进行遍历，依次写到excel中
    file_name: 入参参数, 指的是写入excel的名字
    write_list: 入参参数, 指的是写入excel的每一行汇总的数组
    """
    full_excel = openpyxl.Workbook()
    full_sheet = full_excel.active
    for i in range(0, len(write_list)):
        full_sheet.append(write_list[i])
    full_excel.save(file_name)


if __name__ == '__main__':
    start_time = datetime.datetime.now()

    """
    URL的规律是XXXX+当前日期+XXXX+当前页号
    """
    now_date = datetime.datetime.now().strftime("%Y-%m-%d")
    every_page_result_list = []  # 空数组接受每一页的所有数据行汇总数据

    """循环每一页获取数据"""
    # pages = 78
    pages = 5
    for index in range(1, pages+1):
        url = "http://fx.cmbchina.com/Hq/History.aspx?nbr=%e7%be%8e%e5%85%83&startdate=2009-01-01&enddate=" + now_date + "&page=" + index.__str__()
        every_page_result_list = every_page_result_list + get_page_data(get_url_html(url))
        print("获取第{0}页成功...".format(index))

    """这里是文件excel写入路径，你可以指定任意存在或者不存在的文件"""
    write_excel(r"\test.xlsx", every_page_result_list)

    end_time = datetime.datetime.now()
    print(f"耗时总共{(end_time - start_time).seconds}秒")

