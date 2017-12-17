#运算符优先级，用于在构建后缀表达式时对优先级进行比较#
operator_precedence = {
    '(': 0,
    ')': 0,
    '+': 1,
    '-': 1,
    '*': 2,
    '/': 2
}


def convert2postfix(exp):
    '''
    将字符串转化为后缀形式，并存在栈里
    '''
    stack = []  # 运算符栈，存放运算符
    postfix = []  # 后缀表达式栈
    for char in exp:
        if char not in operator_precedence:  # 非符号，直接进栈
            postfix.append(char)
        else:
            if len(stack) == 0:  # 若是运算符栈啥也没有，直接将运算符进栈
                stack.append(char)
            else:
                if char == "(":
                    stack.append(char)
                elif char == ")":  # 遇到了右括号，运算符出栈到postfix中，并且将左括号出栈
                    while stack[-1] != "(":
                        postfix.append(stack.pop())
                    stack.pop()
                elif operator_precedence[char] > operator_precedence[stack[-1]]:
                    # 只要优先级数字大，那么就继续追加
                    stack.append(char)
                else:
                    while len(stack) != 0:
                        if stack[-1] == "(":  # 运算符栈一直出栈，直到遇到了左括号或者长度为0
                            break
                        postfix.append(stack.pop())  # 将运算符栈的运算符，依次出栈放到表达式栈里面
                    stack.append(char)  # 并且将当前符号追放到符号栈里面
        print("stack:", stack, "postFix", postfix)

    while len(stack) != 0:  # 如果符号站里面还有元素，就直接将其出栈到表达式栈里面
        postfix.append(stack.pop())
    print("stack:", stack, "postFix", postfix)
    return postfix


# ===========================这部分用于构造表达式树，不涉及计算================================#
class Node(object):
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None


def create_expression_tree(postfix):
    """
    利用后缀表达式，构造二叉树
    """
    stack = []
    # print postfix
    for char in postfix:
        if char not in operator_precedence:
            # 非操作符，即叶子节点
            node = Node(char)
            stack.append(node)
        else:
            # 遇到了运算符，出两个，进一个。
            node = Node(char)
            right = stack.pop()
            left = stack.pop()
            node.right = right
            node.left = left
            stack.append(node)
            # 将最后一个出了即可。
    return stack.pop()


# =============================这部分用于计算值===================================#
def calculate(num1, op, num2):
    print("Calculate %s %s %s" % (num1, op, num2))
    num1 = float(num1)
    num2 = float(num2)
    if op == "+":
        return num1 + num2
    elif op == "-":
        return num1 - num2
    elif op == "*":
        return num1 * num2
    elif op == "/":
        if num2 == 0:
            raise "zeros error"
        else:
            return num1 / num2
    else:
        raise "op error"


def cal_expression_tree(postfix):
    stack = []
    for char in postfix:
        stack.append(char)
        if char in "+-*/":
            op = stack.pop()
            num2 = stack.pop()
            num1 = stack.pop()
            value = calculate(num1, op, num2)
            value = str(value)
            stack.append(value)
    return float(stack[0])


if __name__ == "__main__":

    exp1 = "1+2*(3-1)-4"
    exp2 = "1-6*5/(2+3)"
    exp3 = "5/2*2+(5/2)"

    print(">>>exp1 calculating...")
    p1 = convert2postfix(exp1)
    print(cal_expression_tree(p1))
    print(">>>exp2 calculating...")
    p2 = convert2postfix(exp2)
    print(cal_expression_tree(p2))
    print(">>>exp3 calculating...")
    p3 = convert2postfix(exp3)
    print(cal_expression_tree(p3)) 
