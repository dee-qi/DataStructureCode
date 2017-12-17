maze = [
    [1,1,1,1,1,1,1,1,1,1,1,1],
    [1,0,1,1,1,1,1,0,0,0,0,1],
    [1,0,0,0,0,0,1,0,1,0,0,1],
    [1,1,1,1,1,0,1,0,1,1,1,1],
    [1,1,1,1,1,0,1,1,1,1,1,1],
    [1,1,0,0,0,0,0,1,1,1,1,1],
    [1,1,0,1,1,1,1,0,0,0,1,1],
    [1,0,0,0,0,1,1,1,1,0,1,1],
    [1,0,1,1,1,0,0,0,1,0,1,1],
    [1,0,0,0,0,0,1,0,0,0,1,1],
    [1,1,1,1,1,0,1,1,1,0,0,1],
    [1,1,1,1,1,1,1,1,1,1,1,1],
]

route_stack = [(1,1)]

i, j = 1, 1
while not i == 10 and not j == 10:
    if maze[i-1][j] == 0:
        i, j = i-1, j
        maze[i][j] = 1
        route_stack.append((i, j))
    elif maze[i][j+1] == 0:
        i, j = i, j+1
        maze[i][j] = 1
        route_stack.append((i, j))
    elif maze[i+1][j] == 0:
        i, j = i+1, j
        maze[i][j] = 1
        route_stack.append((i, j))
    elif maze[i][j-1] == 0:
        i, j = i, j-1
        maze[i][j] = 1
        route_stack.append((i, j))
    else:
        route_stack.pop()
        i,j = route_stack[-1]

    if len(route_stack) == 0:
        print("No Path Found!")
        break
route_stack.append((10, 10))
print("Path Found:", route_stack)
print("Path shown in gragh:") 
a=0
while a < 10:
    b=0
    while b < 10:
        if (a+1, b+1) in route_stack:
            print("⚪", end="")
        else:
            print("⚫", end="")
        b = b+1
    print("")
    a = a+1
