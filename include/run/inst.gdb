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
# 打印数据
p x # 输出x的值
p arr[0]@10 # 打印arr[0]到arr[0+10-1]
display x # 当x更改时显示
# 调用函数
p nums.size()
call nums.push_back(2)
