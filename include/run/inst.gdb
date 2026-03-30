# 打开pretty print
set print pretty on
set pagination off
set print element 0
# 运行
run
# 如果从文件读取输入
# run < input.txt
# 断点
b main # main函数
b 23 # 23行
i b # 查看断点
delete 1 # 删除1号断点
disable 1 # 禁用1号断点
enable 1 # 启用1号断点
b dfs if u == 21 && fa != -1 # 条件断点
condition 1 argc != 1 # 更改为条件断点
condition 2 # 更改为无条件
c # 在断点处暂停后，继续运行，直到走到下一个断点
n # 单步执行，不进入函数
s # 单步执行，进入函数
# 打印数据
p x # 输出x的值
p arr[0]@10 # 打印arr[0]到arr[0+10-1]
watch x # 当暂停时显示
display x # 当x更改时显示
# 调用函数
p nums.size()
call nums.push_back(2)
# 设置变量
set var x = 5 # 给x赋值为5
