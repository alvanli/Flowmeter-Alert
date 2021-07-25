import pandas as pd

file_to_read = 'photoresistor_vhigh.txt'
file_to_write = 'photoresistor_vhigh.csv'

def nonempty_lines(file):
    for line in file:
        l = line.rstrip('\n')
        if l:
            yield l

def txt_to_csv(input, output):
    data_list1 = []
    data_list2 = []
    with open(input, 'r') as f_in:
        line_count = 0
        for line in nonempty_lines(f_in):
            line_count += 1
            if line_count % 2 == 0:
                if line_count % 4 == 0:
                    values = line[22:]
                    data_list2.append(int(values))
                else:
                    values = line[24:]
                    data_list1.append(int(values))
    if len(data_list1) > len(data_list2):
        data_list1 = data_list1[:-1]
    list_dict = {'Uncovered Top Resistor': data_list1, 'Lasered Top Resistor': data_list2}
    with open(output, 'w') as f_out:
        df = pd.DataFrame(list_dict)
        df.to_csv(output)

txt_to_csv(file_to_read, file_to_write)





