# encoding=utf-8
import time
from input_output import read_map, finish, read_frame, output
from decision_1 import make_decision_1
from state import State
from utils import check_collision
if __name__ == '__main__':
    # time.sleep(8)
    # 读取初始地图状态
    map_data , worktable_num = read_map()
    # 发送OK
    finish()
    #无用的代码，必要的初始化
    # 1:43 2:25 3:50 4:18
    #建立名为num_map的反向映射
    num_map = {43:1, 25:2, 50:3, 18:4}
    global map_flag
    map_flag = num_map[worktable_num]
    while True:
        try:
            # 读取当前场景信息并更新状态
            frame_no, money, worktable_num, worktables, robots, material_demand_num_list, nums_of_products = read_frame()
            state = State(frame_no, money, worktable_num, worktables, robots, material_demand_num_list, nums_of_products)
            # 根据state生成控制指令
            # if map_flag == 1:
            #     command_list = make_decision_1(state)
            # else:
            #     command_list = make_decision(state)
            command_list = make_decision_1(state)
            # 输出控制指令并结束该帧
            output(frame_no, command_list)
            finish()
        except EOFError as e:
            break
