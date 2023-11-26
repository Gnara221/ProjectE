'''
description: 
param: 
return: 
'''
import math


class Robot:
    def __init__(self, table_id, cargo_type, time_coef, collide_coef, angular_velocity, linear_velocity, orientation, position, radius):
        self.table_id = table_id  # 所处工作台ID
        self.cargo_type = cargo_type  # 携带物品类型
        self.time_coef = time_coef  # 时间价值系数
        self.collide_coef = collide_coef  # 碰撞价值系数
        self.angular_velocity = angular_velocity  # 角速度
        self.linear_velocity = linear_velocity  # 线速度
        self.orientation = orientation  # 朝向
        self.position = position  # 坐标
        self.radius = radius
        # self.busy = False
        # self.target_worktable = None

robot1 = Robot(1, 3, 0.8, 0.8, 0.337, 2.2, math.pi/2, (4.25, 5.75), 0.45)
robot2 = Robot(2, 3, 0.8, 0.8, 0.337, 2.2, math.pi/2, (4.25, 5.75), 0.45)
robot3 = Robot(3, 3, 0.8, 0.8, 0.337, 2.2, math.pi/2, (4.25, 5.75), 0.45)
robots = []
robots1 = [robot1, robot2, robot3]
for i in robots1:
    robots.append(i)
for i in robots:
    print(i.table_id)