import matplotlib.pyplot as plt
import matplotlib
import numpy as np

matplotlib.use("template")

# Global variables to parametrize experiments outcomes data e.g. for proper parsing
EXPS_NUM = 4
ALGS_NUM = 4
SIZES_NUM = 9
INIT_SIZE = 7

ARRAY_SIZES_LABELS = [2**x for x in range(INIT_SIZE,INIT_SIZE+SIZES_NUM)]
ALG_NAMES = ["Insertion Sort", "Merge Sort", "Selection Sort", "Shell Sort"]
EXP_NAMES = ["Random", "Ascending Sorted", "Descending Sorted", "Random {1,2,3}"]

def read_chunk(file : str):
    """
    Reads data from file.
    Expects data to be in the following format:

                      Algorithm#            Algorithm#                   Algorithm#

    Experiment#    _time_ _comparisons_ | _time_ _comparisons_ | ... | _time_ _comparisons_
    Experiment#    _time_ _comparisons_ | _time_ _comparisons_ | ... | _time_ _comparisons_
    Experiment#    _time_ _comparisons_ | _time_ _comparisons_ | ... | _time_ _comparisons_
                   ...

    Experiment#    _time_ _comparisons_ | _time_ _comparisons_ | ... | _time_ _comparisons_
    Experiment#    _time_ _comparisons_ | _time_ _comparisons_ | ... | _time_ _comparisons_
    Experiment#    _time_ _comparisons_ | _time_ _comparisons_ | ... | _time_ _comparisons_
                   ...

                   ...

    E.g.:

    25 8092 | 22 3904 | 40 16384 | 16 1464
    0 127 | 14 3324 | 34 16384 | 4 776
    54 16383 | 15 3324 | 36 16384 | 8 1224
    19 5326 | 18 3737 | 36 16384 | 9 939

    ...

    So in each row different algorithms are seperated by "|" character
    and for each algorithm time and comparisons value are seperated by " " (whitespace).
    Each experiment is in new line. Array sizes are seperated by a line, which will be
    ignored

    Currently this algorithm expects to have EXPS_NUM of experiments for SIZE_NUM different
    array sizes. This can be tweaked by chaning global variables in the beggining of the file
    """
    raw_data = [[[[]]]]     # [sizes][exps_data][algs_data][meas_data]
    with open(file) as file:
        counter = 0
        exps_data = []

        for line in file:
            if counter == EXPS_NUM:
                counter = 0
                raw_data.append(exps_data)
                exps_data = []
                continue

            algs = line.strip().split("|")
            algs_data = []

            for alg in algs:
                time, comp = alg.strip().split()
                meas_data = [ time, comp ]
                algs_data.append(meas_data)

            exps_data.append(algs_data)
            counter += 1
    return raw_data


def extract_data(raw_data :list, exp_num :int, alg_num :int, row :int):
    """
    Parameters:
        * raw_data - 4d array of data, generated by read_chunk function
        * exp_num  - experiment's number (Non-negative integer)
        * algs_num - algorithm's
        * row : row = 0 - time will be returned,
                row = 1 - number comparisons will be returned
                else nothing will be returned

    If requested entry is not found, it will be skipped
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
    for exp_n in range(EXPS_NUM):
        exp_data_time = []
        exp_data_comp = []
        for alg_n in range(ALGS_NUM):
            if exp_data_time == []:
                exp_data_time = [ extract_data(raw_data, exp_n, alg_n, 0) ]
            else:
                exp_data_time += [ extract_data(raw_data, exp_n, alg_n, 0) ]
            if exp_data_comp == []:
                exp_data_comp = [ extract_data(raw_data, exp_n, alg_n, 1) ]
            else:
                exp_data_comp += [ extract_data(raw_data, exp_n, alg_n, 1) ]

        draw_graph(exp_data_time, str(exp_n)+"_time.png", EXP_NAMES[exp_n], time=True)
        draw_graph(exp_data_comp, str(exp_n)+"_comp.png", EXP_NAMES[exp_n], time=False)
        print(f"Built graphs for {EXP_NAMES[exp_n]} experiment")


def draw_graph(algs :list, plot_name :str, graph_label :str, time=True):
    plt.magma()

    fig, ax = plt.subplots()

    ax.set_xscale('log', base=2)
    ax.set_yscale('log', base=10)

    for i in range(len(algs)):
        algs[i] = list(map(int, algs[i]))
        ax.plot(ARRAY_SIZES_LABELS, algs[i], label=ALG_NAMES[i], marker='2')

    plt.xlabel('Array size')
    if time:
        plt.ylabel('Time (microseconds)')
    else:
        plt.ylabel('Number of Comparisons')

    plt.title(graph_label)
    plt.legend()
    plt.grid(color='g', linestyle='-.', linewidth=.1)

    plt.savefig("graphs/"+plot_name)
    plt.clf()


if __name__ == "__main__":
    main()
