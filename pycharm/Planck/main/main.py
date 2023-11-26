# encoding=utf-8
import sys
import os
import logging
import time

from input_output import read_map, finish, read_frame, output
from decision import make_decision
from state import State

if __name__ == '__main__':
    # 读取初始地图状态
    # time.sleep(5)
    map_data = read_map()
    finish()  # 发送OK
    while True:
        try:
            # 读取当前场景信息并更新状态
            frame_no, money, worktable_num, worktables, robots = read_frame()
            
            state = State(frame_no, money, worktable_num, worktables, robots)
            # 根据state生成控制指令
            command_list = make_decision(state)
            # 输出控制指令并结束该帧
            output(frame_no, command_list)
            finish()
        except EOFError as e:
            break
