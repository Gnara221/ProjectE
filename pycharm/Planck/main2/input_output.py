import sys
from beans.robot import Robot
from beans.worktable import Worktable
from utils import material_check


def finish():
    sys.stdout.write('OK\n')
    sys.stdout.flush()


def read_map():
    """
    读取初始化的地图数据
    :return:
    """
    worktables_pos = {f"{i}": [] for i in range(9)}
    for i in range(100):
        data = input()
        for k, j in enumerate(data):
            if j != "." and j != "A":
                x = k * 0.5 + 0.25
                y = 50 - (0.5 * i + 0.25)
                pos = (x, y)
                worktables_pos[str(int(j) - 1)].append(pos)
    input()
    return worktables_pos


def read_frame():
    """
    读取每一帧的数据
    :return:
    """
    demand_info = {  # 机器人所需原料
        "4": [1, 2],
        "5": [1, 3],
        "6": [2, 3],
        "7": [4, 5, 6],
    }
    material_demand_num_list = {f"{i + 1}": 0 for i in range(7)}
    # 读取第一行
    frame_no, money = map(int, input().split())
    # 读取工作台数量
    worktable_num = int(input())
    # 读取每一个工作台的信息,并存储成工作台类，放在字典中
    work_tables = {f"{i + 1}": [] for i in range(9)}
    for i in range(worktable_num):
        worktable_info = input().split()  # 每一个工作台的信息
        worktable = Worktable(i, worktable_info[0], (worktable_info[1], worktable_info[2]), worktable_info[3],
                              worktable_info[4], worktable_info[5], False)
        # 读取需求原料数
        if 4 <= int(worktable_info[0]) <= 7:
            for i in demand_info[worktable_info[0]]:
                if material_check(worktable_info[4], i):
                    material_demand_num_list[str(i)] += 1
        work_tables[str(worktable_info[0])].append(worktable)
    # 读取4个机器人信息
    robots = []
    for i in range(4):
        robot_data = input().split()
        robot = Robot(robot_data[0], robot_data[1], robot_data[2], robot_data[3], robot_data[4],
                      (robot_data[5], robot_data[6]), robot_data[7], (robot_data[8], robot_data[9]))
        if robot_data[1] != "0":
            material_demand_num_list[robot_data[1]] -= 1
            if material_demand_num_list[robot_data[1]] < 0:
                material_demand_num_list[robot_data[1]] = 0
        robots.append(robot)
    input()  # 读取 OK
    return frame_no, money, worktable_num, work_tables, robots, material_demand_num_list


def output(frame_id, command_list):
    sys.stdout.write('%d\n' % frame_id)
    for command in command_list:
        sys.stdout.write(command)  # command是字符串
