'''
description: 
param: 
return: 
'''
#a python script to run command ./Robot -f -m 2.txt -c ./ "python main.py" in the current directory
# 
import subprocess


# D:\study\contest\华为软挑\code\3\Robot.exe -f -m 1.txt -c .\ "python main.py"
# D:\study\contest\hw\pre_official\pre_official_map
# D:\\study\\contest\\hw\\pre_official\\pre_official_map
# 定义要执行的命令列表
# commands = [
#     'D:\\study\\contest\\hw\\code\\3\\Robot.exe -f -m D:\\study\\contest\\hw\\code\\3\\1.txt -c .\ "python D:\\study\\contest\\hw\\code\\3\\main.py"',
    
#     'D:\\study\\contest\\hw\\code\\3\\Robot.exe -f -m D:\\study\\contest\\hw\\code\\3\\2.txt -c .\ "python D:\\study\\contest\\hw\\code\\3\\main.py"',
    
#     'D:\\study\\contest\\hw\\code\\3\\Robot.exe -f -m D:\\study\\contest\\hw\\code\\3\\3.txt -c .\ "python D:\\study\\contest\\hw\\code\\3\\main.py"',
    
#     'D:\\study\\contest\\hw\\code\\3\\Robot.exe -f -m D:\\study\\contest\\hw\\code\\3\\4.txt -c .\ "python D:\\study\\contest\\hw\\code\\3\\main.py"',
# ]
commands = [
     'E:\\Documents\\Project\\pycharm\\Planck\\3\\Robot.exe -f -m E:\\Documents\\Project\\pycharm\\Planck\\3\\maps\\1.txt -c .\ "python E:\\Documents\\Project\\pycharm\\Planck\\3\\main.py"',

    'E:\\Documents\\Project\\pycharm\\Planck\\3\\Robot.exe -f -m E:\\Documents\\Project\\pycharm\\Planck\\3\\maps\\2.txt -c .\ "python E:\\Documents\\Project\\pycharm\\Planck\\3\\main.py"',

    'E:\\Documents\\Project\\pycharm\\Planck\\3\\Robot.exe -f -m E:\\Documents\\Project\\pycharm\\Planck\\3\\maps\\3.txt -c .\ "python E:\\Documents\\Project\\pycharm\\Planck\\3\\main.py"',

    'E:\\Documents\\Project\\pycharm\\Planck\\3\\Robot.exe -f -m E:\\Documents\\Project\\pycharm\\Planck\\3\\maps\\4.txt -c .\ "python E:\\Documents\\Project\\pycharm\\Planck\\3\\main.py"',
]

with open('output.txt', 'a') as f:
    scores = []
    for command in commands:
        process = subprocess.run(
            command, stdout=subprocess.PIPE, text=True, shell=True, cwd="E:\\Documents\\Project\\pycharm\\Planck\\3\\")
        # 使用 split() 函数分离字符串，获取分数
        # score = int(process.stdout.split(':')[2][:-1])
        score_str = (process.stdout.split(':')[2].strip(' }'))
        score_str = score_str[:-3]
        score = int(score_str)
        scores.append(score)
        f.write(process.stdout)

    total_score = sum(scores)
    f.write('Total score: {}'.format(total_score))
    f.write('\n')
