# import math
# v53 = 3.454092653589793
# robot_ori = 2.405294418
# robot_x = 17.71426392
# robot_y = 28.60106468
# wk_x = 14.235323
# wk_y = 34.32511
# tmp =math.atan2(wk_y-robot_y,wk_x-robot_x)-robot_ori
# print(tmp)
# print(math.cos(abs(tmp))*6)
# print(math.sin(abs(tmp))*v53)
# task_list = [(28, 1), (27, 0, 4)]
# task_list.remove((28, 1))
# print(task_list)
for robot_id in range(4):
    robot_control(robot_id, state, workstation_pos)