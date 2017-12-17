'''
-2表示空的格子
-1表示是障碍物
'''

###测试数据1###
# a_little_box = [
#     [-2,-1,-1,-2,-2,-2,-1,-1,-2,-2,-1,-1,-1,-1,-2,-2],
#     [-2,-1,-1,-1,-2,-2,-2,-2,-2,-2,-1,-1,-1,-1,-2,-2],
#     [-2,-2,-2,-1,-2,-2,-2,-2,-2,-2,-1,-1,-2,-2,-2,-2],
#     [-2,-2,-2,-2,-2,-2,-1,-2,-2,-2,-2,-2,-2,-2,-2,-2],
#     [-2,-2,-1,-2,-2,-2,-1,-1,-2,-2,-2,-2,-2,-2,-2,-2],
#     [-1,-2,-1,-1,-2,-2,-2,-2,-2,-2,-2,-2,-1,-2,-2,-2],
#     [-1,-2,-1,-1,-2,-1,-1,-1,-1,-2,-2,-2,-1,-2,-2,-2],
#     [-1,-2,-1,-1,-2,-1,-1,-1,-2,-2,-2,-2,-1,-2,-2,-2],
#     [-2,-2,-1,-1,-2,-1,-1,-1,-2,-2,-2,-2,-1,-2,-2,-2],
#     [-2,-2,-1,-1,-2,-2,-2,-2,-2,-2,-1,-1,-1,-2,-1,-2],
#     [-1,-2,-2,-1,-2,-1,-1,-1,-2,-2,-1,-1,-1,-2,-2,-2],
#     [-1,-1,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2],
# ]
# start, end = (3, 3), (10, 14)

###测试数据2###
a_little_box = [
    [-2,-2,-2,-2],
    [-1,-2,-1,-2],
    [-2,-2,-2,-2]
]
start, end = (0, 0), (1, 3)

print("The box is as shown:")
a=0
while a < len(a_little_box):
    b=0
    while b < len(a_little_box[0]):
        if a_little_box[a][b] == -2:
            print("⚪", end="")
        else:
            print("⚫", end="")
        b = b+1
    print("")
    a = a+1

playerunknowns_queue = []#瞎起的名，这个是寻路过程中用来存放数据的队列
i, j = start
a_little_box[i][j] = 0
tag = 1

while a_little_box[end[0]][end[1]] == -2:
    if i-1>=0:
        if a_little_box[i-1][j] == -2:
            a_little_box[i - 1][j] = tag
            playerunknowns_queue.append((i-1, j))
            print("set (%s,%s) as %s" % (i - 1, j, tag))
    if j+1<len(a_little_box[0]):
        if a_little_box[i][j+1] == -2:
            a_little_box[i][j + 1] = tag
            playerunknowns_queue.append((i, j+1))
            print("set (%s,%s) as %s" % (i, j + 1, tag))
    if i+1<len(a_little_box):
        if a_little_box[i+1][j] == -2:
            a_little_box[i + 1][j] = tag
            playerunknowns_queue.append((i+1, j))
            print("set (%s,%s) as %s" % (i + 1, j, tag))
    if j-1>=0:
        if a_little_box[i][j-1] == -2:
            a_little_box[i][j - 1] = tag
            playerunknowns_queue.append((i, j-1))
            print("set (%s,%s) as %s" % (i, j - 1, tag))
    print(playerunknowns_queue)
    i, j = playerunknowns_queue[0]
    if a_little_box[i][j] == tag:
        tag = tag + 1
    playerunknowns_queue.pop(0)

path_list = [(end[0],end[1])]
i, j = end
while not (i, j) == start:
    if i-1>=0:
        if a_little_box[i-1][j] == a_little_box[i][j]-1:
            i, j = i-1, j
            path_list.append((i, j))
            continue
    if j+1<len(a_little_box[0]):
        if a_little_box[i][j+1] == a_little_box[i][j]-1:
            i, j = i, j+1
            path_list.append((i, j))
            continue
    if i+1<len(a_little_box):
        if a_little_box[i+1][j] == a_little_box[i][j]-1:
            i, j = i+1, j
            path_list.append((i, j))
            continue
    if j-1>=0:
        if a_little_box[i][j-1] == a_little_box[i][j]-1:
            i, j = i, j-1
            path_list.append((i, j))
            continue

print("The length of the shortest path is",a_little_box[end[0]][end[1]])
print("The path is as shown:")
print(path_list)
a=0
while a < len(a_little_box):
    b=0
    while b < len(a_little_box[0]):
        if (a, b) in path_list:
            print("⚪", end="")
        else:
            print("⚫", end="")
        b = b+1
    print("")
    a = a+1
