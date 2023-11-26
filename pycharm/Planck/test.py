#记录每个产品被哪些工作台所需要
#产品号：工作台
demand_of_worktable = {
	"1":[],
	"2":[],
	"3":[],
	"4":[],
	"5":[],
	"6":[],
	"7":[],
}

def update_worktables(state):
    global demand_of_worktable
    demand_of_worktable = {
	"1":[],
	"2":[],
	"3":[],
	"4":[],
	"5":[],
	"6":[],
	"7":[],
	"8":[],
	"9":[],
}
    
    worktable_list_tmp = [target_worktable for target_worktable in state.worktables.values() if
                                    target_worktable is not None]

    #提取出worktable_list_tmp中的每个元素进入worktable_list
    #设置工作台最大个数
    max_num = 2
    worktable_type_map_flag = {
		4 : max_num,
		5 : max_num,
		6 : max_num,
		7 : 3,
	}
    worktable_list = []
    for worktables in worktable_list_tmp:
        for worktable in worktables:
            type = int(worktable.type)
            if type > 7 or type < 4:
                worktable_list.append(worktable)
            elif worktable_type_map_flag[type] > 0:
                worktable_type_map_flag[type] -= 1
                worktable_list.append(worktable)
            
    #遍历所有工作台
    for worktable in worktable_list:
        #如果工作台需要原材料
        if worktable.material_left_list != None:
            #遍历工作台需要的各个原材料，将工作台放入demand_of_worktable对应的材料项中
            for i in worktable.material_left_list:
                demand_of_worktable[str(i)].append(worktable)

    #遍历所有产出产品的工作台
    for worktable in worktable_list :
        if worktable.product != "0":
            #更新产品优先级（需求量）
            for demand_worktable in demand_of_worktable[worktable.type]:
                #update priority for demand_worktable
                pass
		
    return