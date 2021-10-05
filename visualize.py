import matplotlib.pyplot as plt
import matplotlib
import numpy as np

matplotlib.use("template")

ARRAY_SIZES_LABELS = list(range(7, 16))
ALG_NAMES = ["Insertion Sort", "Merge Sort", "Selection Sort", "Shell Sort"]
EXP_NAMES = ["Random", "Ascending Sorted", "Descending Sorted", "Random {1,2,3}"]

def read_chunk(file : str):
    """
    Reads data from file.
    Expects data to be in the following format:

    _time_ _comparisons_ | _time_ _comparisons_ | ... | _time_ _comparisons_
    _time_ _comparisons_ | _time_ _comparisons_ | ... | _time_ _comparisons_
    _time_ _comparisons_ | _time_ _comparisons_ | ... | _time_ _comparisons_
    ...

    _time_ _comparisons_ | _time_ _comparisons_ | ... | _time_ _comparisons_
    _time_ _comparisons_ | _time_ _comparisons_ | ... | _time_ _comparisons_
    _time_ _comparisons_ | _time_ _comparisons_ | ... | _time_ _comparisons_
    ...

    ...
    
    This means that in each row different algorithms are seperated by "|" character
    and for each algorithm time and comparisons value are seperated by " " (whitespace)

    For different data sizes, blocks are seperated by new line
    """
    raw_data = [[[[]]]]     # [sizes][exps_data][algs_data][meas_data]
    s = 7   # size
    e = 0   # experiment type
    a = 0   # algorithm
    with open(file) as file:
        counter = 0
        exps_data = []

        for line in file:
            if counter==4:
                counter = 0
                s+=1;
                raw_data.append(exps_data)
                exps_data = []
                continue
            e = counter%4

            algs = line.strip().split("|")
            algs_data = []
            for alg in algs:
                time, comp = alg.strip().split()
                meas_data = [time, comp]
                algs_data.append(meas_data)
                a+=1
            exps_data.append(algs_data)
            counter+=1
    return raw_data


def extract_data(raw_data :list, exp_num :int, alg_num :int, row :int):
    """
    Parameters:
        * row : row = 0 - time will be returned,
                row = 1 - number comparisons will be returned
                else nothing will be returned
    """
    accessed_data = []
    for s in range(len(raw_data)):
        try:
            time_data = raw_data[s][exp_num][alg_num][row]
            accessed_data.append(time_data)
        except IndexError:
            continue

    return accessed_data

def main():
    raw_data = read_chunk("data.txt")
    for exp_n in range(4):
        exp_data_time = []
        exp_data_comp = []
        for alg_n in range(4):
            if exp_data_time == []:
                exp_data_time = [ extract_data(raw_data, exp_n, alg_n, 0) ]
            else:
                exp_data_time += [ extract_data(raw_data, exp_n, alg_n, 0) ]
            if exp_data_comp == []:
                exp_data_comp = [ extract_data(raw_data, exp_n, alg_n, 1) ]
            else:
                exp_data_comp += [ extract_data(raw_data, exp_n, alg_n, 1) ]

        print(exp_data_time)
        print(exp_data_comp)
        print()
        draw_graph(exp_data_time, str(exp_n)+"_time.png", EXP_NAMES[exp_n], time=True)
        draw_graph(exp_data_comp, str(exp_n)+"_comp.png", EXP_NAMES[exp_n], time=False)
    # draw_graph(exp_data_time, "my_test_plot.png")
    # test_graph()


def draw_graph(algs :list, plot_name :str, graph_label :str, time=True):
    plt.magma()
    for i in range(len(algs)):
        algs[i] = list(map(int, algs[i]))
        print("***********")
        print(algs[i])
        print("***********")
        plt.plot(ARRAY_SIZES_LABELS, algs[i], label=ALG_NAMES[i])

    plt.xscale("log")
    plt.semilogx(base=2)
    plt.yscale("log")
    plt.semilogy(base=2)

    plt.xlabel('Array size')
    if time:
        plt.ylabel('Time (milliseconds)')
    else:
        plt.ylabel('Comp')

    plt.title(graph_label)
    plt.legend()

    plt.savefig("graphs/"+plot_name)
    plt.clf()


if __name__ == "__main__":
    main()




def test_graph():
    data1 = ['13', '29', '34', '51', '101', '226', '500', '1069', '2247']
    plt.plot(ARRAY_SIZES_LABELS, data1)

    data2 = ['25', '53', '62', '87', '163', '352', '745', '1541', '3264']
    plt.plot(ARRAY_SIZES_LABELS, data2)

    data3 = ['58', '231', '452', '1253', '4658', '18752', '77707', '305626', '1249006']
    plt.plot(ARRAY_SIZES_LABELS, data3)

    data4 = ['54', '193', '393', '1086', '4022', '16227', '72830', '257156', '1075099']
    plt.plot(ARRAY_SIZES_LABELS, data4)

    plt.savefig('test.png')

