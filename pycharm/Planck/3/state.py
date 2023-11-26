class State:
    def __init__(self, frame_no, money, worktable_num, worktables, robots,material_demand_num_list,nums_of_products):
        self.frame_no = frame_no  # 帧的序列号
        self.money = money  # 钱有多少
        self.worktable_num = worktable_num  # 工作台的数量
        self.robot_num = 4  # 机器人的数量
        self.map_size = 50  # 地图大小
        self.worktables = worktables  # 工作台的状态
        self.robots = robots  # 机器人的状态
        self.material_demand_num_list = material_demand_num_list # 每种材料的需求量
        self.nums_of_products = nums_of_products
