import matplotlib.pyplot as pt
import sys

algos=["RANDOM","NFU","OPTIMAL", "NRU", "LRU", "WORKINGSET", "CLOCK", "AGING" , "FIFO", "FIFO_SECOND_CHANCE", "WSCLOCK"]
colors=["blue","black","red","yellow","green","pink","violet","brown","lavender","grey","maroon"]
index=0
file_names=["random_output.txt","nfu_output.txt","optimal_output.txt",
    "nru_output.txt", "lru_output.txt","wset_output.txt","clock_output.txt","aging_output.txt",
    "fifo_output.txt","fifo2_output.txt","wsclock_output.txt"]
print(file_names)
for file_name in file_names:
    my_file = open(file_name)
    op = my_file.readlines()
    num_lines = len(op)
    #num_cases = num_lines/5
    offset = 0
    x_val = list()
    y_val = list()
    tcase = 0
    for i in range(num_lines):
        cur_line = op[i].split(",")
        x_val.append(int(cur_line[0])) #frames
        y_val.append(float(cur_line[3])) # hit ratio
    pt.plot(x_val, y_val,label=algos[index],color=colors[index])    
    # pt.title('Test_case_'+str(tcase))
    index+=1
pt.xlabel('Frames')
pt.ylabel('Number of swaps')
pt.legend()
pt.show()