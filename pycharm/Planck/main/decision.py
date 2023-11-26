import sys
import math
from robot_control import robot_control
from utils import calculate_distance
from utils import calculate_orientation
from beans.worktable import Worktable
from utils import material_check
from utils import check_full


def make_decision(state):
    # 命令列表
    command_list = []  # 一维列表
    for i in range(4):
        command_list.extend(greedy_decision(state, i))
    return command_list


def greedy_decision(state, robot_id):
    """
    根据每一个当前状态进行贪心决策
    """
    command = []  # 一维
    robot = state.robots[robot_id]  # 机器人类，存放一系列信息
    sell_info = {
        "1": [4, 5, 9],
        "2": [4, 6, 9],
        "3": [5, 6, 9],
        "4": [7, 9],
        "5": [7, 9],
        "6": [7, 9],
        "7": [8, 9],
    }
    # 如果机器人携带货物，前往配送区域进行交付
    if robot.cargo_type != "0":
        # 找到所有可以交付的工作台
        sellable_areas_matrix = [state.worktables[str(sellable_index_worktable_1)] for sellable_index_worktable_1 in
                                 sell_info[robot.cargo_type]]
        # 找到最近的工作台坐标
        sellable_areas_result = []  # 注意，此时的sellable_areas_是二维的[[w1,w1,w1],[w2,w2,w2],[w3,w3]]
        # 在可交付的工作台中，若原料格中无对应产品，则添加到sellable_areas_result中
        for sellable_areas in sellable_areas_matrix:
            for sellable_area in sellable_areas:
                if material_check(sellable_area.material, robot.cargo_type):
                    sellable_areas_result.append(sellable_area)
        #  若没地方去
        if len(sellable_areas_result) == 0:
            full, robot_destroy_id = check_full(state)
            if full:  # 若没地方去并且都携带着东西
                command.append(f"destroy {robot_destroy_id}\n")
            else:  # 没地方去，不存在死锁的问题的话，就不管了
                pass
        else:
            # 若有地方去
            target_pos = min(sellable_areas_result,
                             key=lambda x: calculate_distance(robot.position, x.location)).location
            # 若可以交付(距离很近)：
            if calculate_distance(target_pos, robot.position) <= 0.4:
                command.append(f'sell {str(robot_id)}\n')
            else:
                # 若不可以交付(距离很远)，则前往
                command.extend(robot_control(robot_id, robot, target_pos, False))

    else:  # 机器人没有货物就前往工作台获取货物
        # 获取全部工作台信息
        target_worktable_obj_list = [target_worktable for target_worktable in state.worktables.values() if
                                     target_worktable is not None]

        target_worktable_list_0 = []  # 剩余帧数为0
        target_worktable_list_n = []  # 剩余帧数为n
        # 查找目的工作台坐标点列表
        for target_worktable_obj in target_worktable_obj_list:
            for worktable in target_worktable_obj:
                # 机器人没有携带货物时首先查找有没有生产完的 并且需要没有被占据
                if int(worktable.remaining_time) == 0 and (worktable.occupied == False):
                    target_worktable_list_0.append(worktable)
                elif int(worktable.remaining_time) > 0 and (worktable.occupied == False):
                    target_worktable_list_n.append(worktable)
        # 如果找到有货产出的工作台，就前往
        if len(target_worktable_list_0) != 0:
            target_worktable = min(target_worktable_list_0,
                                   key=lambda x: calculate_distance(robot.position, x.location))
            assert type(target_worktable) == Worktable
            # 若够，就买
            if calculate_distance(robot.position, target_worktable.location) <= 0.4:
                command.append(f"buy {str(robot_id)}\n")
            else:
                # 距离工作台距离远就进行移动，返回控制指令
                is_wait = False
                target_worktable.occupied = True  # 表示被占据
                command.extend(robot_control(robot_id, robot, target_worktable.location, is_wait))
        else:
            # 若找不到，就原地转圈圈
            command.append(f"rotate {str(robot_id)} 3.1415\n")
    return command
