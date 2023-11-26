# encoding=utf-8
import sys
import time

from input_output import read_map, finish, read_frame, output
from decision import make_decision
from state import State

if __name__ == '__main__':
    # time.sleep(8)
    # 读取初始地图状态
    map_data = read_map()
    # 发送OK
    finish()
    # 全局变量
    task_list = []  # 若为送货物，则是(工作台id,0,物品类型) 若为拿货物，则是(工作台id,1)
    # 机器人的状态[是否忙，目的工作台的id，目的工作台的pos]
    robot_state = [{"busy": False, "wk_id": 0, "wk_pos": (0, 0)},
                   {"busy": False, "wk_id": 0, "wk_pos": (0, 0)},
                   {"busy": False, "wk_id": 0, "wk_pos": (0, 0)},
                   {"busy": False, "wk_id": 0, "wk_pos": (0, 0)}]
    while True:
        try:
            # 读取当前场景信息并更新状态
            frame_no, money, worktable_num, worktables, robots, material_demand_num_list = read_frame()
            state = State(frame_no, money, worktable_num, worktables, robots, material_demand_num_list)
            # 根据state生成控制指令
            command_list = make_decision(state, task_list, robot_state)
            # 输出控制指令并结束该帧
            output(frame_no, command_list)
            finish()
        except EOFError as e:
            break
