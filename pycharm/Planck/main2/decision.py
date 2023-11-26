import sys
from typing import List
from robot_control import robot_control
from state import State
from utils import calculate_distance
from beans.worktable import Worktable
from utils import material_check

product_info = {  # 产品信息
    """
    1 无 3000 6000
    2 无 4400 7600
    3 无 5800 9200
    4 1+2 15400 22500
    5 1+3 17200 25000
    6 2+3 19200 27500
    7 4+5+6 76000 105000
    """
    "1": [3000, 6000],
    "2": [4400, 7600],
    "3": [5800, 9200],
    "4": [15400, 22500],
    "5": [17200, 25000],
    "6": [19200, 27500],
    "7": [76000, 105000]
}


def make_decision(state, task_list, robot_state):
    # 命令列表
    command_list = []  # 一维列表
    if state.frame_no == 1034:
        sys.stderr.write("fuck")
    for robot_id in range(4):
        # 若正在忙，则继续任务
        if robot_state[robot_id]["busy"]:
            command_list.extend(continue_task(robot_id, state, task_list, robot_state))
        # 若不忙，则分配任务
        else:
            if state.frame_no > 8000 and state.robots[robot_id].cargo_type == "0":  # 疯狂模式
                command_list.extend(sell_all(robot_id, state, task_list, robot_state))
            else:
                command_list.extend(distribute_task(robot_id, state, task_list, robot_state))
    return command_list
    # if state.frame_no<1000:
    #     command_list = []  # 一维列表
    #     for robot_id in range(4):
    #         # 若正在忙，则继续任务
    #         if robot_state[robot_id]["busy"]:
    #             command_list.extend(continue_task(robot_id, state, task_list, robot_state))
    #         # 若不忙，则分配任务
    #         else:
    #             command_list.extend(distribute_task(robot_id, state, task_list, robot_state))
    #     return command_list
    # else:
    #     command_list = []  # 一维列表
    #     for robot_id in range(4):
    #         # 若正在忙，则继续任务
    #         if robot_state[robot_id]["busy"]:
    #             command_list.extend(continue_task(robot_id, state, task_list, robot_state))
    #         # 若不忙，则分配任务
    #         else:
    #             command_list.extend(sell_all(robot_id, state, task_list, robot_state))
    #     return command_list


# def sell_all(robot_id, state: State, task_list, robot_state):
#     """
#     最后关头卖掉所有
#     robot_id:当前机器人下标
#     首先从state中提取出地图中所有有产品的的worktable，然后计算从机器人当前位置到worktable和worktable的位置到8号或者9号工作台的最近路线
#     找到最短路线后，更新task_list和robot_state，并且返回command列表
#     """
#     command = []
#     robot = state.robots[robot_id]
#     a = 1
#     if robot_id == 0 and state.frame_no == 1033:
#         a = 2
#         if a > 3:
#             a = 4
#             a = a * 5
#     # 1. 筛选出所有有产品的工作台
#     product_worktables = []
#     for worktable in state.worktables.values():
#         if worktable is not None:
#             for w in worktable:
#                 if int(w.product) == 1:
#                     product_worktables.append(w)
#
#     # 2. 计算从机器人当前位置到有产品的工作台，以及从有产品的工作台到8号或9号工作台的距离
#     min_distance = float("inf")
#     target_worktable = None
#     # worktable_9_exists = "9" in state.worktables and state.worktables["9"] is not None
#     worktable_9_exists = len(state.worktables["9"]) != 0
#
#     for product_worktable in product_worktables:
#         distance_to_product = calculate_distance(robot.position, product_worktable.location)
#
#         distance_to_sell_8 = calculate_distance(product_worktable.location, state.worktables["8"][0].location)
#
#         if worktable_9_exists:
#             distance_to_sell_9 = calculate_distance(product_worktable.location, state.worktables["9"][0].location)
#             distance_to_sell = min(distance_to_sell_8, distance_to_sell_9)
#         else:
#             distance_to_sell = distance_to_sell_8
#
#         total_distance = distance_to_product + distance_to_sell
#
#         # 3. 找到总距离最短的工作台
#         if total_distance < min_distance:
#             min_distance = total_distance
#             target_worktable = product_worktable
#
#     if target_worktable is not None:
#         # 4. 更新task_list和robot_state
#         robot_state[robot_id]["busy"] = True
#         robot_state[robot_id]["wk_id"] = target_worktable.id
#         robot_state[robot_id]["wk_pos"] = target_worktable.location
#         task_list.append((robot_state[robot_id]["wk_id"], 1))
#
#         # 5. 返回相应的命令列表
#         # return command.extend(continue_task(robot_id, state, task_list, robot_state))
#         return continue_task(robot_id, state, task_list, robot_state)
#
#     return []

def sell_all(robot_id, state: State, task_list, robot_state):
    """
    最后关头卖掉所有
    robot_id:当前机器人下标
    首先从state中提取出地图中所有有产品的的worktable，然后计算从机器人当前位置到worktable和worktable的位置到8号或者9号工作台的最近路线
    找到最短路线后，更新task_list和robot_state，并且返回command列表
    """
    command = []
    robot = state.robots[robot_id]

    # 1. 筛选出所有有产品的工作台
    product_worktables = []
    for worktable in state.worktables.values():
        if worktable is not None:
            for w in worktable:
                if int(w.product) == 1:
                    product_worktables.append(w)

    # 2. 计算从机器人当前位置到有产品的工作台，以及从有产品的工作台到8号或9号工作台的距离
    min_distance = float("inf")
    target_worktable = None
    worktable_8_exists = len(state.worktables["8"]) != 0
    worktable_9_exists = len(state.worktables["9"]) != 0
    # worktable_8_exists = "8" in state.worktables and state.worktables["8"] is not None
    # worktable_9_exists = "9" in state.worktables and state.worktables["9"] is not None

    for product_worktable in product_worktables:
        distance_to_product = calculate_distance(robot.position, product_worktable.location)

        if worktable_8_exists:
            distance_to_sell_8 = calculate_distance(product_worktable.location, state.worktables["8"][0].location)
        if worktable_9_exists:
            distance_to_sell_9 = calculate_distance(product_worktable.location, state.worktables["9"][0].location)

        if worktable_8_exists and worktable_9_exists:
            distance_to_sell = min(distance_to_sell_8, distance_to_sell_9)
        elif worktable_8_exists:
            distance_to_sell = distance_to_sell_8
        elif worktable_9_exists:
            distance_to_sell = distance_to_sell_9
        else:
            continue  # 如果8号和9号工作台都不存在，跳过当前循环

        total_distance = distance_to_product + distance_to_sell

        # 3. 找到总距离最短的工作台
        if total_distance < min_distance:
            min_distance = total_distance
            target_worktable = product_worktable

    if target_worktable is not None:
        # 4. 更新task_list和robot_state
        robot_state[robot_id]["busy"] = True
        robot_state[robot_id]["wk_id"] = target_worktable.id
        robot_state[robot_id]["wk_pos"] = target_worktable.location
        task_list.append((robot_state[robot_id]["wk_id"], 1))

        # 5. 返回相应的命令列表
        command.extend(continue_task(robot_id, state, task_list, robot_state))

    return command


def distribute_task(robot_id, state: State, task_list, robot_state):
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
        # 除去有原料的
        sellable_areas_result = []  # 注意，此时的sellable_areas_matrix是二维的[[wx,wy,wz],[wi,wj,wk],[wm,wn]]
        # 在可交付的工作台中，若原料格中无对应产品，则添加到sellable_areas_result中
        for sellable_areas in sellable_areas_matrix:
            for sellable_area in sellable_areas:
                if material_check(sellable_area.material, robot.cargo_type) and (
                        (sellable_area.id, 0, robot.cargo_type) not in task_list):
                    sellable_areas_result.append(sellable_area)  # sellable_areas_result是一维的, 存储单个工作台
        if len(sellable_areas_result) != 0:
            # target_worktable = choose_target(robot, sellable_areas_result)
            target_worktable = min(sellable_areas_result,
                                   key=lambda x: calculate_distance(robot.position, x.location))
            robot_state[robot_id]["busy"] = True
            robot_state[robot_id]["wk_id"] = target_worktable.id
            robot_state[robot_id]["wk_pos"] = target_worktable.location
            task_list.append((robot_state[robot_id]["wk_id"], 0, robot.cargo_type))
            return continue_task(robot_id, state, task_list, robot_state)
        else:
            return []
    # 若机器人不携带货物
    else:
        # 获取全部工作台信息
        target_worktable_obj_list = [target_worktable for target_worktable in state.worktables.values() if
                                     target_worktable is not None]
        # 若有产品 并且没有机器人分配到这个任务 并且 当前有需求 就加入到target_worktable_list_0
        # 剩余帧数为0
        target_worktable_list_0 = []
        for target_worktable_obj in target_worktable_obj_list:
            for worktable in target_worktable_obj:
                # 机器人没有携带货物时首先查找有没有生产完的 并且需要没有被占据，并且需要有需求
                if int(worktable.product) == 1 and ((worktable.id, 1) not in task_list) and (
                        state.material_demand_num_list[worktable.type] > 0):
                    target_worktable_list_0.append(worktable)
        # 如果有地方去
        if len(target_worktable_list_0) != 0:
            # 找到最理想的工作台
            target_worktable = min(target_worktable_list_0,
                                   key=lambda x: calculate_distance(robot.position, x.location))
            assert type(target_worktable) == Worktable
            robot_state[robot_id]["busy"] = True  # bool型
            robot_state[robot_id]["wk_id"] = target_worktable.id  # int型
            robot_state[robot_id]["wk_pos"] = target_worktable.location  # 元组
            task_list.append((robot_state[robot_id]["wk_id"], 1))
            return continue_task(robot_id, state, task_list, robot_state)
        # 若无地方去，就暂时不发送操作命令
        else:
            return []


def continue_task(robot_id, state: State, task_list, robot_state):
    command = []
    # 当前机器人
    robot = state.robots[robot_id]
    target_worktable_pos = robot_state[robot_id]["wk_pos"]
    # 若携带货物
    if robot.cargo_type != "0":
        # 距离很近
        if calculate_distance(target_worktable_pos, robot.position) < 0.4:
            # 机器人设置为闲，从任务列表中移除任务
            robot_state[robot_id]["busy"] = False
            command.append(f'sell {str(robot_id)}\n')
            task_list.remove((robot_state[robot_id]["wk_id"], 0, robot.cargo_type))
        # 若不可以交付(距离很远)，则前往
        else:
            command.extend(robot_control(robot_id, state, robot_state[robot_id]["wk_pos"], False))
        return command
    # 若不携带货物
    else:
        # 距离很近
        if calculate_distance(target_worktable_pos, robot.position) < 0.4:
            a = 1
            if robot_id == 0 and state.frame_no == 1033:
                a = 2
                if a > 3:
                    a = 4
                    a = a * 5
            # 机器人设置为闲，从任务列表中移除任务
            robot_state[robot_id]["busy"] = False
            command.append(f'buy {str(robot_id)}\n')
            task_list.remove((robot_state[robot_id]["wk_id"], 1))
        # 若距离很远，买不到
        else:
            command.extend(robot_control(robot_id, state, robot_state[robot_id]["wk_pos"], False))
        return command


def calc_profit(robot, sellable_area: Worktable):
    """
    计算收益
    """
    distance = calculate_distance(robot.position, sellable_area.location)
    profit = product_info[robot.cargo_type][1] / distance
    return profit


def choose_target(robot, sellable_areas_result: List[Worktable]) -> Worktable:
    """
    根据距离和收益，选择工作台
    """
    # 选择距离最近的工作台
    target_worktable = min(sellable_areas_result, key=lambda x: calc_profit(robot, x))
    return target_worktable
