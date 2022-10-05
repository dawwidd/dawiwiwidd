import matplotlib.pyplot as plt
import pandas as pd
import numpy


def format_x_axis(data):
    result = []
    for d in data:
        result.append(float(d/1000.0))
    
    return result


def format_y_axis(data):
    result = []
    for i in range(len(data)):
        result.append(float(data[i]*100.0))

    return result


def plot_line(file, mrkr, lbl, clr):
    data = pd.read_csv(file)

    x = data['effort']
    y = []

    for i in range(len(data)):
        y.append(numpy.mean(data.iloc[i][2:32]))

    plt.plot(format_x_axis(x), format_y_axis(y), marker=mrkr, markersize=5, ls='-', label=lbl, color=clr, markevery=25, linewidth=1)
    plt.legend(numpoints=2, loc='lower right')
    

plot_line('1coev.csv', 's', '1-Coev', 'black')
plot_line('1coevrs.csv', 'v', '1-Coev-RS', 'green')
plot_line('1evolrs.csv', 'o', '1-Evol-RS', 'blue')
plot_line('2coev.csv', 'd', '2-Coev', 'magenta')
plot_line('2coevrs.csv', 'D', '2-Coev-RS', 'red')

plt.xlabel('Rozegranych gier (x1000)')
plt.ylabel('Odsetek wygranych gier [%]')
plt.xlim(0,500)
plt.ylim(60,100)

top_x = plt.twiny()
top_x.set_xlim(0,200)
top_x.set_xticks([0,40,80,120,160,200])
top_x.set_xlabel("Pokolenie")

plt.grid(linestyle='--')
plt.savefig('myplot.pdf')
plt.show()
plt.close()