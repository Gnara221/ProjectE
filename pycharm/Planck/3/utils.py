import math
from beans.robot import Robot
from state import State


def calculate_distance(point1, point2):
    """
    计算两个点之间的欧几里得距离
    :param point1: 点1，[x1, y1]
    :param point2: 点2，[x2, y2]
    :return: 两点之间的距离
    """
    x1, y1 = map(float, point1)
    x2, y2 = map(float, point2)
    return math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)


def calculate_orientation(current_pos, target_pos):
    x1, y1 = map(float, current_pos)
    x2, y2 = map(float, target_pos)
    angle = math.atan2(y2 - y1, x2 - x1)
    return angle


def material_check(material, cargo_type):
    """
    检测cargo_type原材料格，返回True or False
    """
    material = int(material)
    cargo_type = int(cargo_type)
    s = "1"
    for i in range(cargo_type):
        s += "0"
    tmp = int(s, 2)
    result = tmp & material
    return result != tmp


def check_full(state: State):
    robots = state.robots
    for k, robot in enumerate(robots):
        # 若有一个机器人没有携带货物，就返回False
        if robot.cargo_type == "0":
            return False, None
    min_value = min(robots, key=lambda x: x.cargo_type)
    min_key = robots.index(min_value)
    return True, min_key


def check_collision(state, command_list):
    for robot_id in range(4):
        me = state.robots[robot_id]
        for k, other_robot in enumerate(state.robots):
            if k == robot_id:
                continue

            if other_robot.radius + me.radius + 0.002 > calculate_distance(me.position, other_robot.position):
                if float(other_robot.position[0]) > float(me.position[0]):
                    if float(me.orientation) <= 0:
                        #forward 0 3.069281

                        command_list[robot_id] -= 0.7675761452421762
                elif float(me.orientation) > 0:
                    command_list[robot_id] -= 0.7675761452421762
                else:
                    command_list[robot_id] += 0.7675761452421762
