class Worktable:
    def __init__(self, type, location, remaining_time, material, product, occupied):
        self.type = type  # 类型
        self.location = location  # 坐标
        self.remaining_time = remaining_time  # 剩余时间
        self.material = material  # 原料格
        self.product = product  # 产品格
        self.occupied = occupied  # 是否被占据

    # def update(self, remaining_time, material, product):
    #     self.remaining_time = remaining_time
    #     self.material = material
    #     self.product = product
