import numpy as np 
init_lst = np.linspace(-5, 5, 11)
initial_value_list = []
for i in range(len(init_lst)):
    for j in range(len(init_lst)):
        initial_value = [round(init_lst[i], 2), round(init_lst[j], 2)]
        initial_value_list.append(initial_value)
print(initial_value_list)

f_name = "./test.csv"
f = open(f_name, 'w')
for i in range(len(initial_value_list)):
    f.write("{")
    for j in range(len(initial_value_list[i])):
        f.write(str(initial_value_list[i][j]))
        if j < len(initial_value_list[i]) - 1:
            f.write(",")
    f.write("},")
    f.write("\n")
f.close()