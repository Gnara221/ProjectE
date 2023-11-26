import math
from typing import List
from beans.robot import Robot
from utils import check_collision
from utils import calculate_distance
import numpy as np


def check_obstacles(robot_id, robots: List[Robot]):
    """
    检测下标为robot_id的机器人是否与其他机器人有相撞的可能，若有，则返回障碍物的坐标列表,
    比如[(3,4),(5,6)...],若没有可能,则返回空列表，也就是[]
    """
    obstacles_pos_list = []
    safe_distance = 2
    for i, other_robot in enumerate(robots):
        if i <= robot_id:
            continue
        distance = math.sqrt((float(robots[robot_id].position[0]) - float(other_robot.position[0])) ** 2 + (
                float(robots[robot_id].position[1]) - float(other_robot.position[1])) ** 2)
        if distance < safe_distance:
            obstacles_pos_list.append((float(other_robot.position[0]), float(other_robot.position[1])))
    return obstacles_pos_list


def dwa_control(robot_id, robot, obstacles_pos_list,workstation_pos):
    """
    dwa实现算法
    robot_id为当前机器人的下标，robot为当前机器人对象，属性有速度，坐标等
    obstacles_pos_list为障碍物坐标列表，也就是可能碰撞的其他机器人的坐标
    函数返回command
    """
    # 基本参数设置
    v_min, v_max = -2, 6  # 速度范围
    omega_min, omega_max = -math.pi, math.pi  # 角速度范围
    delta_v = 0.2  # 遍历速度的步长
    delta_omega = 0.1  # 遍历角速度的步长

    best_v, best_omega = robot.linear_velocity[0], robot.angular_velocity
    min_cost = float("inf")  # 初始化为无穷大

    # 加入随机扰动，扰动量为0.1
    # delta_v_noise = 0.1
    # delta_omega_noise = 0.1

    for v in np.arange(v_min, v_max, delta_v):
        for omega in np.arange(omega_min, omega_max, delta_omega):

            # 计算预测的位置
            x_pred = float(robot.position[0]) + v * math.cos(float(robot.orientation)) * 1.0
            y_pred = float(robot.position[1]) + v * math.sin(float(robot.orientation)) * 1.0

            # 计算预测位置与障碍物之间的距离
            min_obstacle_dist = float("inf")
            for obstacle_pos in obstacles_pos_list:
                dist = math.sqrt((x_pred - obstacle_pos[0]) ** 2 + (y_pred - obstacle_pos[1]) ** 2)
                min_obstacle_dist = min(min_obstacle_dist, dist)

            # 计算当前朝向和目标方向之间的夹角，作为新的成本因素
            orientation_vector = np.array([math.cos(float(robot.orientation)), math.sin(float(robot.orientation))])
            target_vector = np.array([float(workstation_pos[0]) -float(robot.position[0]), float(workstation_pos[1]) -float( robot.position[1])])
            cos_angle = np.dot(orientation_vector, target_vector) / (
                    np.linalg.norm(orientation_vector) * np.linalg.norm(target_vector))
            angle = np.arccos(cos_angle)
            angle_cost = angle / math.pi

            # 综合考虑障碍物距离和朝向与目标方向之间的夹角，计算成本
            cost = 1.0 / min_obstacle_dist + angle_cost

            # 更新最佳速度和角速度
            if cost < min_cost:
                min_cost = cost
                best_v = v
                best_omega = omega

    command = [f"rotate {robot_id} {best_omega}\n", f"forward {robot_id} {best_v}\n"]
    return command
def dwa_control2(robot_id, robot, obstacles_pos_list,workstation_pos):
    command = []
    command.append(f"rotate {robot_id} {-math.pi}\n")
    # command.append(f" {robot_id} {-math.pi}\n")
    return command

def robot_control(robot_id, state, workstation_pos, is_wait):
    command = []
    robot = state.robots[robot_id]
    obstacles_pos_list = check_obstacles(robot_id, state.robots)
    if len(obstacles_pos_list) != 0:
        # 若有，则进入dwa算法实现函数
        return dwa_control2(robot_id, robot, obstacles_pos_list,workstation_pos)
    # 若无当前机器人的周围没有其他机器人，则不进行dwa算法处理
    # 转变方向,控制机器人朝向工作台
    orientation_d_value = math.atan2(float(workstation_pos[1]) - float(robot.position[1]),
                                     float(workstation_pos[0]) - float(robot.position[0])) - float(robot.orientation)
    robot_speed = math.sqrt(float(robot.linear_velocity[0]) ** 2 + float(robot.linear_velocity[1]) ** 2)
    # 为了确保角度值在 - π到π之间，做了一些调整
    # 大于π:
    if orientation_d_value > math.pi:
        orientation_d_value -= (2 * math.pi)
    # 小于-π:
    elif orientation_d_value < -math.pi:
        orientation_d_value += (2 * math.pi)
    # 角加速度
    v53 = 3.454092653589793
    if orientation_d_value <= 0.0:
        v53 = -3.454092653589793
    # 太小就不动
    if abs(orientation_d_value) <= 0.08:
        result_speed = 6
        result_orientation = 0
    # 小于π/2
    elif abs(orientation_d_value) <= (math.pi / 2):
        result_speed = math.cos(orientation_d_value) * 6
        result_orientation = math.sin(abs(orientation_d_value)) * v53
    else:
        result_orientation = v53
        result_speed = 0
    # 接下来是出界问题
    x_maybe = float(robot.position[0]) + math.cos(float(robot.orientation)) * float(robot_speed) * 15 / 50
    y_maybe = float(robot.position[1]) + math.sin(float(robot.orientation)) * float(robot_speed) * 15 / 50
    if x_maybe > 49.75 or y_maybe > 49.75 or x_maybe < 0.25 or y_maybe < 0.25:
        result_speed = -result_speed
    for other_id in range(4):
        if other_id==robot_id:
            continue
        other_robot = state.robots[other_id]
        me = state.robots[robot_id]
        # if other_robot.radius + me.radius + 0.1 > calculate_distance(me.position, other_robot.position):
        if other_robot.radius + me.radius + 0.002 > calculate_distance(me.position, other_robot.position):
            if float(other_robot.position[0]) > float(me.position[0]):
                if float(me.orientation) <= 0:
                    #forward 0 3.069281
                    result_speed -= 0.7675761452421762
            elif float(me.orientation) > 0:
                result_speed -= 0.7675761452421762
            else:
                result_speed += 0.7675761452421762
    command.append(f"rotate {robot_id} {result_orientation}\n")
    command.append(f"forward {robot_id} {result_speed}\n")
    return command
