from typing import List
from robot_control0 import robot_control
from state import State
import copy
from utils import calculate_distance
from beans.worktable import Worktable
from utils import material_check
from itertools import permutations

product_info = {
    # 产品信息：进价和售价
    "1": [3000, 6000],
    "2": [4400, 7600],
    "3": [5800, 9200],
    "4": [15400, 22500],
    "5": [17200, 25000],
    "6": [19200, 27500],
    "7": [76000, 105000]
}


def make_decision(state):
    a=1
    if state.frame_no==7939:
        a+=1
    perms = permutations(range(4), 4)
    tmp_distance = 8003
    final_command = []
    material_bak = copy.deepcopy(state.material_demand_num_list)
    num_of_product_bak = copy.deepcopy(state.nums_of_products)
    final_log = []
    for i in perms:
        distance_total = 0
        command_list = []  # 一维列表
        tmp_task_info = []
        state.nums_of_products = copy.deepcopy(num_of_product_bak)
        state.material_demand_num_list = copy.deepcopy(material_bak)
        tmp_logs = []
        for robot_id in i:
            distance, command, tmp_log = greedy_decision(robot_id, state, tmp_task_info)
            distance_total += distance
            command_list.extend(command)
            tmp_logs.append(tmp_log[:])
        # print(tmp_logs,end="")
        # print(i,distance_total)
        if tmp_distance > distance_total:
            tmp_distance = distance_total
            final_command = command_list[:]
            final_log = copy.deepcopy(tmp_logs)
    # print(final_log)
    return final_command


def get_demand_index(worktable):
    score_index = [0, 1, 1, 1, 10, 10, 10, 10, 1, 1]
    demand_index = 0
    # 类型为"i"的工作台需要的原料
    material_info = {  # 每一个工作台，需要什么类型的物品
        "4": [1, 2],
        "5": [1, 3],
        "6": [2, 3],
        "7": [4, 5, 6],
        "8": [7],
        "9": [1, 2, 3, 4, 5, 6, 7]
    }
    for i in material_info[worktable.type]:
        if material_check(worktable.material, str(i)):
            demand_index += score_index[i]
    return demand_index


def greedy_decision(robot_id, state, tmp_task_info):
    tmp_log = []
    command = []
    sell_info = {  # 机器人携带货物：可交付的工作台
        "1": [4, 5, 9],
        "2": [4, 6, 9],
        "3": [5, 6, 9],
        "4": [7, 9],
        "5": [7, 9],
        "6": [7, 9],
        "7": [8, 9],
    }
    # 当前机器人
    robot = state.robots[robot_id]
    # 若机器人携带货物
    if robot.cargo_type != "0":
        # 找到所有可以交付的工作台
        sellable_areas_matrix = [state.worktables[str(sellable_index_worktable_1)] for sellable_index_worktable_1 in
                                 sell_info[robot.cargo_type]]
        sellable_areas_result = []  # 注意，此时的sellable_areas_matrix是二维的[[wx,wy,wz],[wi,wj,wk],[wm,wn]]
        # 除去有原料的 或者被其他机器人占据任务的
        # 在可交付的工作台中，若原料格中无对应产品，则添加到sellable_areas_result中
        for sellable_areas in sellable_areas_matrix:
            for sellable_area in sellable_areas:
                if material_check(sellable_area.material, robot.cargo_type) and (
                        (sellable_area.id, 0, robot.cargo_type) not in tmp_task_info):
                    sellable_areas_result.append(sellable_area)  # sellable_areas_result是一维的, 存储单个工作台
        if len(sellable_areas_result) != 0:
            # 选取目标工作台
            target_worktable = choose_target(robot, sellable_areas_result, state)
            tmp_log.append((robot_id, target_worktable.location))
            # robot和worktable的距离
            r_w_d = calculate_distance(robot.position, target_worktable.location)
            # 加入到任务列表
            tmp_task_info.append((target_worktable.id, 0, robot.cargo_type))
            if r_w_d < 0.4:
                command.append(f"sell {robot_id}\n")
            else:
                command.extend(robot_control(robot_id, state, target_worktable.location, False))
            return r_w_d - get_demand_index(target_worktable), command, tmp_log
        else:
            return 20000, [], []
    # 若机器人不携带货物
    else:
        # 获取全部工作台信息
        target_worktable_obj_list = [target_worktable for target_worktable in state.worktables.values() if
                                     target_worktable is not None]
        # 除去无产品的 除去无需求的 除去在任务列表中的
        # 剩余帧数为0
        target_worktable_list_0 = []
        for target_worktable_obj in target_worktable_obj_list:
            for worktable in target_worktable_obj:
                # 机器人没有携带货物时首先查找有没有生产完的 并且需要没有被占据，并且需要有需求
                if int(worktable.product) == 1 and (state.material_demand_num_list[worktable.type] > 0) and (
                        ((worktable.id, 1) not in tmp_task_info) or state.nums_of_products <= 0):
                    target_worktable_list_0.append(worktable)
        # 如果有地方去
        if len(target_worktable_list_0) != 0:
            # 找到最理想的工作台
            target_worktable = choose_target(robot, target_worktable_list_0, state)
            assert type(target_worktable) == Worktable
            tmp_log.append((robot_id, target_worktable.location))
            r_w_d = calculate_distance(robot.position, target_worktable.location)
            state.nums_of_products -= 1
            state.material_demand_num_list[target_worktable.type] -= 1
            tmp_task_info.append((target_worktable.id, 1))
            if r_w_d < 0.4:
                command.append(f"buy {robot_id}\n")
            else:
                command.extend(robot_control(robot_id, state, target_worktable.location, False))
            return r_w_d, command, tmp_log
        # 若无地方去，就暂时不发送操作命令
        else:
            return 20000, [], []


def calculate_score(robot, worktable, state):
    """
    计算综合评分
    """
    # 距离
    distance = calculate_distance(robot.position, worktable.location)
    # 收益
    if robot.cargo_type == "0":
        profit = product_info[worktable.type][0] / distance
    else:
        profit = product_info[robot.cargo_type][1] / distance
    score = profit

    return score


def choose_target(robot, sellable_areas_result: List[Worktable], state) -> Worktable:
    """
    根据距离和收益，选择工作台
    """
    # 选择距离最近的工作台
    target_worktable = min(sellable_areas_result, key=lambda x: calculate_distance(robot.position, x.location))
    # target_worktable = min(sellable_areas_result, key=lambda x: calculate_score(robot, x, state))
    return target_worktable
