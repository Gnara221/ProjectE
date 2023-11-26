'''
description: 
param: 
return: 
'''
# encoding=utf-8
import time
from input_output import read_map, finish, read_frame, output
from decision import make_decision
from state import State
from utils import check_collision
if __name__ == '__main__':
    # time.sleep(8)
    # 读取初始地图状态
    map_data = read_map()
    # 发送OK
    finish()
    while True:
        try:
            # 读取当前场景信息并更新状态
            frame_no, money, worktable_num, worktables, robots, material_demand_num_list,nums_of_products = read_frame()
            state = State(frame_no, money, worktable_num, worktables, robots, material_demand_num_list,nums_of_products)
            # 根据state生成控制指令
            command_list = make_decision(state)
            # 输出控制指令并结束该帧
            output(frame_no, command_list)
            finish()
        except EOFError as e:
            break
