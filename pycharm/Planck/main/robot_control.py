import math
from beans.robot import Robot
from utils import calculate_orientation
from utils import calculate_distance

LONG_DISTANCE = 0.4
MAX_SPEED = 6
MIN_SPEED = -2


def control_orientation(robot_id, robot, workstation_pos):
    # 转变方向,控制机器人朝向工作台
    target_orientation = calculate_orientation((robot.position[0], robot.position[1]), workstation_pos)
    robot_orientation = float(robot.orientation)
    command = []
    if robot_orientation == target_orientation:
        command.append(f"rotate {robot_id} 0\n")
    else:
        if (robot_orientation >= 0 and target_orientation >= 0) or (robot_orientation <= 0 and target_orientation <= 0):
            if robot_orientation > target_orientation:
                # 右转
                command.append(f"rotate {robot_id} {-math.pi}\n")
            else:
                # 左转
                command.append(f"rotate {robot_id} {math.pi}\n")
        elif robot_orientation <= 0 and target_orientation >= 0:
            if target_orientation > (math.pi - abs(robot_orientation)):
                # 右转
                command.append(f"rotate {robot_id} {-math.pi}\n")
            else:
                # 左转
                command.append(f"rotate {robot_id} {math.pi}\n")
        else:
            if robot_orientation < (math.pi - abs(target_orientation)):
                # 左转
                command.append(f"rotate {robot_id} {math.pi}\n")
            else:
                # 右转
                command.append(f"rotate {robot_id} {-math.pi}\n")
    return command


def robot_control(robot_id, robot: Robot, workstation_pos, is_wait):
    command = []
    robot_pos = (robot.position[0], robot.position[1], robot.orientation)
    distance = calculate_distance((robot_pos[0], robot_pos[1]), workstation_pos)  # 目标距离
    robot_speed = math.sqrt(float(robot.linear_velocity[0]) ** 2 + float(robot.linear_velocity[1]) ** 2)  # 机器人速度
    # 方向控制
    # command.extend(control_orientation(robot_id, robot, workstation_pos))
    target_orientation = calculate_orientation((robot.position[0], robot.position[1]), workstation_pos)
    # # 转变方向,控制机器人朝向工作台
    if float(robot_pos[2]) > target_orientation:
        # 右转
        command.append(f"rotate {robot_id} {-math.pi}\n")
    elif float(robot_pos[2]) < target_orientation:
        # 左转
        command.append(f"rotate {robot_id} {math.pi}\n")
    else:
        command.append(f"rotate {robot_id} 0\n")
    # 接下来是速度控制
    if distance > LONG_DISTANCE:  # 若距离比较远,则加速
        command.append(f"forward {robot_id} {MAX_SPEED}\n")
    # 若距离比较近
    else:
        # 若等待，就速度设为0
        if is_wait:
            command.append(f"forward {robot_id} 0\n")
        # 若不等待，就直接过去
        else:
            # 若速度大，则减速
            if robot_speed > 0:
                command.append(f"forward {robot_id} 0\n")
            # 速度为0时,等到方向对再移动
            else:
                if abs(float(robot_pos[2]) - target_orientation) <= math.pi / 180:
                    command.append(f"forward {robot_id} {MAX_SPEED}\n")
    return command