from dinic import *

def profile_dinic():
    for i in range(100):
        run_dinic("net02.txt")

if __name__ == "__main__":
    import cProfile
    import pstats
    
    cProfile.run("profile_dinic()", "dinic.profile")
    p = pstats.Stats("dinic.profile")
    p.sort_stats('time').print_stats('dinic.py')
