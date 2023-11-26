'''
description: 
param: 
return: 
'''
import base64
from io import BytesIO
import requests
from PIL import Image
from bs4 import BeautifulSoup
from lxml import etree



def get_page_source(url):
    headers = {'user-agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/111.0.0.0 Safari/537.36'
    }
    try:
        r = requests.get(url, headers=headers, timeout=30)
        if r.status_code == 200:
            return r.content
        else:
            print(f"Request failed with status code {r.status_code}")
            return None
    except Exception as e:
        print(f"Request failed with error: {e}")
        return None
def get_captcha(html):
    soup = BeautifulSoup(html, 'lxml')
    div_img = soup.find('div', class_='el-image__inner')
    img = div_img.find('img').get('src')
    img_data = img.split(',')[1]
    binary_img_data = base64.b64decode(img_data)
    file_like = BytesIO(binary_img_data)
    image = Image.open(file_like)
    image.show()
    
def main():
    url = 'https://sczyz.org.cn/zysc/#/login'
    html = get_page_source(url)
    get_captcha(html)
    

if __name__ == '__main__':
    main()

# headers = {'user-agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/111.0.0.0 Safari/537.36'
#     }
# url = 'https://sczyz.org.cn/zysc/#/login'
# pagetext = requests.get(url=url,headers=headers).text

# #解析验证码图面img中的src属性
# tree = etree.HTML(pagetext)
# tree.xpath('//img[@id="captchaImg"]/@src')
# data:image/png;base64,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
# data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAJYAAAAoCAIAAACTo5SwAAAEdUlEQVR42u2a+0uTURjH/WeCIuinoPylDArBKEuzCwRiEBZFhVp0w6yICsKKgjKozMos1HnXWnlpljl30ZmXbc3b5ttc25x52Wbba4888Taazu19dzlvO4fvD+bQ3nM+3+d7nnNeExboEPlIoEtAEdJBEdJBEVKEdMQfwkeKck4kz23Vrkp/xTVCX3IkI1ySXFwjXJIcmRQDw/tfKSbwIAefeln2VW8jfP1hqDOk/+/xOiMqCvzifS9csdqUTD9885m6Zm7eRRTCsP/m83VKELkIm7ZL3+3+0HaoHSTL/iw/qwAp8lW9t/sqLjaAtMV6/UsDaKzBaJKOg5g2M6Myv6ioLZZI+gZ0c+Y5l90dKsWIBmkkEBJLcRFheNVysA0N8SVX7msIUN/9AXTD0JvhV4lf0RA/FFabxg6aMc6AG0I1xJIURVeI2zc4AyuqCMMo/3gA9dzUoCH84wHckJJaDeLc4HV7Cae4IrwVKRKNMJxu2N/iv1P8EwzcNoGpMDngEJ4KQVJc7qO6cg/ye3hrPlA7A1bFZwXz4tODnXE+IJgbThJmi9OGOmjJkVUfa6w98rY1SwZLA+EZFz4ILhUCuCHUYFDLvYjwwnF3OG9nnL/c0IhCO9r9fdD/U/AsPis89z+GgMTDScJsK5PkIJg5FASuBawLLlCcGIJrGjhDqK52oxtA+uff1A8M15L1eZtGrqWNDtWNW9U2XM8p3RSusMfp4YmwfVQF/F5q6r0s/50mmL7UPx5AYO3l4sHfDVA3/70V+CC0zTnwpNhvMQhEGKHTxXLZgFY4mydL3VlzcGfNpxKtbzBw2wT6ADpqUaQCH4S1g61YhewCK2RZo4nQd6gGbXj2yCnsCukHL1Ypr5TKQYFTIYAbIhEM/N9UaMw6gUsZ5UL8m88siwg3ZtbH8GjBNQ2cISY6LOiGhhvGgiTd5S3asqNabnfsuqBEQ3w+1YlukKY380E4Msm8+foWED5RVXm8HjEi9L0EWJtRReBNTY/CuyNxhUZUUEeKVfhpTC38WWOFcHh8GhFuPtxEGsLvJvZAsgv4Hd7jmv7Jhh+hwW5EhNbZyXAhjD7Fu6X9iLCgqJsohMAse+8iv31bXcBS0JuK5YZkoBkRQpyKF2FXn3VNehUgXLe/mrRb70un3HichziNCEKHcxoRdpp6yUeYcaa1tGlIOzoFLQw2Mhq9/frT3tVpEuAHFN93MibLLDkIiwrnkV9DRbB9RsgIoRFFhKMOJiwPHVGEvm+AERunlBPv4XRB2rsnHjfdISOUGjrwdg0ksCONTiEODjug7HbnNkPzCWUHyZl+uuXcPaVMPSHwrUVMKPqzjP0fIcb2aEEgwmDokoUwhkcL0SH0ZUkiQkqR36AIKUKapRQhLURRIqzPsvj+0zvPIr/i9aYFOsRShTrJjGvyzwUSI3chwtfJDEUiGoRQcBibjpFfdZkWRNh6zkaRiAahReOW5du5LRBlVrspEpG1M2XbGCjHkkQTIuy646BIxNqRSk9ajR+dlAeP8RvvPycCAHXm3gAAAABJRU5ErkJggg==