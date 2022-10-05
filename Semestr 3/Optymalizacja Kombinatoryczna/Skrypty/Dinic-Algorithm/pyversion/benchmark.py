"""
Benchmarck Dinic Algorithm

"""

if __name__ == '__main__':
    from timeit import Timer
    t = Timer("run_dinic('tests/networks/numericosimple.in')", "from dinic import run_dinic")
    print("%.2f sec" % (t.timeit(number=10000)))
