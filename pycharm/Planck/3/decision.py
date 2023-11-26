import math
from typing import List
from robot_control0 import robot_control
from state import State
import copy
from utils import calculate_distance
from beans.worktable import Worktable
from utils import material_check
from itertools import permutations


product_info = {  # 产品信息

    "1": [3000, 6000, 3000],
    "2": [4400, 7600, 3200],
    "3": [5800, 9200, 3400],
    "4": [15400, 22500, 7100],
    "5": [17200, 25000, 7800],
    "6": [19200, 27500, 8300],
    "7": [76000, 105000, 29000]
}
"""
	1 无 3000 6000
	2 无 4400 7600
	3 无 5800 9200
	4 1+2 15400 22500
	5 1+3 17200 25000
	6 2+3 19200 27500
	7 4+5+6 76000 105000
"""


def make_decision(state):
    perms = permutations(range(4), 4)
    tmp_distance = 100001
    final_command = []
    material_bak = copy.deepcopy(state.material_demand_num_list)
    num_of_product_bak = copy.deepcopy(state.nums_of_products)
    for i in perms:
        distance_total = 0
        command_list = []  # 一维列表
        tmp_task_info = []
        state.nums_of_products = copy.deepcopy(num_of_product_bak)
        state.material_demand_num_list = copy.deepcopy(material_bak)
        for robot_id in i:
            distance, command, tmp_log = greedy_decision(robot_id, state, tmp_task_info)
            distance_total += distance
            command_list.extend(command)
        if tmp_distance > distance_total:
            tmp_distance = distance_total
            final_command = command_list[:]
    return final_command


# 当前工作台已有的原料的score之和
def get_demand_index(worktable):
#    score_index = [0, 1, 1, 1, 10, 10, 10, 10, 1, 1]
    score_index_0 = [0, 1, 1, 2, 7, 8, 9, 10, 1, 1]
    score_index = [i * 1 for i in score_index_0]
    demand_index = 0
    # 类型为"i"的工作台需要的原料
    material_info = {  # 每一个工作台，需要什么类型的物品
        "1": [],
        "2": [],
        "3": [],
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
            # target_worktable = min(sellable_areas_result, key=lambda x: calculate_distance(robot.position, x.location))
            target_worktable = choose_target(robot, sellable_areas_result)
            tmp_log.append((robot_id, target_worktable.location))
            # robot和worktable的距离
            r_w_d = calculate_distance(robot.position, target_worktable.location)
            # distance per profit
            r_w_d_profit = (r_w_d - get_demand_index(target_worktable)
                            ) / calc_priority(robot, target_worktable, r_w_d)
            # 加入到任务列表
            tmp_task_info.append((target_worktable.id, 0, robot.cargo_type))
            if r_w_d < 0.4:
                command.append(f"sell {robot_id}\n")
            else:
                command.extend(robot_control(robot_id, state, target_worktable.location, False))
            # return r_w_d - get_demand_index(target_worktable), command, tmp_log
            return r_w_d_profit, command, tmp_log
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
            # target_worktable = min(target_worktable_list_0, key=lambda x: calculate_distance(robot.position, x.location))
            target_worktable = choose_target(robot, target_worktable_list_0)
            assert type(target_worktable) == Worktable
            tmp_log.append((robot_id, target_worktable.location))
            r_w_d = calculate_distance(
                robot.position, target_worktable.location)
            # distance per profit
            r_w_d_profit = (r_w_d - get_demand_index(target_worktable)) / calc_priority(robot, target_worktable, r_w_d)
            state.nums_of_products -= 1
            state.material_demand_num_list[target_worktable.type] -= 1
            tmp_task_info.append((target_worktable.id, 1))
            if r_w_d < 0.4:
                command.append(f"buy {robot_id}\n")
            else:
                command.extend(robot_control(robot_id, state, target_worktable.location, False))
            # return r_w_d, command, tmp_log
            return r_w_d_profit, command, tmp_log
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


def calc_rate(x, maxX, minRate=0.8):
    if x >= maxX:
        return minRate
    else:
        return (1 - math.sqrt(1 - math.pow(1 - x / maxX, 2))) * (1 - minRate) + minRate


def calc_profit(robot, sellable_area: Worktable):
    """
    计算收益
    """
    distance = calculate_distance(robot.position, sellable_area.location)
    profit = product_info[robot.cargo_type][1] / distance
    return profit


def calc_priority(robot, target: Worktable, distance):
    """
    计算优先级
    """
    """
    携带物品：robot.cargo_type
    工作台类型：target.type	
    工作台物品：target.material
    """
    # priority = int(target.type)+5
    # if priority == 7:
    # 	priority += 5
    # if target.material != "0":
    # 	priority += 6
    # if target.product != "0":
    # 	priority += 4
    # priority -= 10/calc_rate(10*distance, 9000, 0.8)
    # return priority
    priority = 0
    material_rate = 1
    # 原料格已放置
    if target.material != "0":

       material_rate += 8
    # 机器人携带物品的收益
    if robot.cargo_type != "0":
        priority = product_info[str(robot.cargo_type)][1] * calc_rate(10 * distance, 9000, 0.8) * material_rate
    # 产品格有产出，算出收益
    if target.product != "0":
        priority += product_info[target.type][2]
    # 算出单位距离的收益
    priority /= distance
    return priority


def choose_target(robot, sellable_areas_result: List[Worktable]) -> Worktable:
    """
    根据距离和收益，选择工作台
    """
    # 选择距离最近的工作台
    target_worktable = min(sellable_areas_result, key=lambda x: calculate_distance(robot.position, x.location))
    target_distance = calculate_distance(robot.position, target_worktable.location)
    target_priority = calc_priority(robot, target_worktable, target_distance)

    # 选择priority最高的工作台
    for current_worktable in sellable_areas_result:
        current_distance = calculate_distance(robot.position, current_worktable.location)
        current_priority = calc_priority(robot, current_worktable, current_distance)
        if current_priority > target_priority:
            target_priority = current_priority
            target_distance = current_distance
            target_worktable = current_worktable
    return target_worktable
