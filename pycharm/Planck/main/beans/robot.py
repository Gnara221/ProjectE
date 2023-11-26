class Robot:
    def __init__(self, table_id, cargo_type, time_coef, collide_coef, angular_velocity, linear_velocity,
                 orientation, position):
        self.table_id = table_id  # 所处工作台ID
        self.cargo_type = cargo_type  # 携带物品类型
        self.time_coef = time_coef  # 时间价值系数
        self.collide_coef = collide_coef  # 碰撞价值系数
        self.angular_velocity = angular_velocity  # 角速度
        self.linear_velocity = linear_velocity  # 线速度
        self.orientation = orientation  # 朝向
        self.position = position  # 坐标
