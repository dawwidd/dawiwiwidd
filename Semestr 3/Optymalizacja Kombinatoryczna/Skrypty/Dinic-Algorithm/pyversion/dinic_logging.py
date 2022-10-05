"""
Logging functions for Dinic module.

"""

import logging

LEVEL = logging.INFO

logger = logging.getLogger('dinic_app')
logger.setLevel(LEVEL)

fh = logging.FileHandler('dinic.log')
fh.setLevel(logging.DEBUG)

ch = logging.StreamHandler()
ch.setLevel(logging.INFO)

formatter = logging.Formatter("%(asctime)s - %(name)s - %(levelname)s - %(message)s")
fh.setFormatter(formatter)
ch.setFormatter(formatter)

logger.addHandler(fh)
logger.addHandler(ch)


def print_init():
    logger.debug("\nNew Dinic Run\n")

def print_edges(edges):
    """Print all network edges information"""
    logger.debug("Maximal Flow:")
    for e in edges:
        logger.debug("%d -> %d: %d (%d)" % 
                     (e['first'], e['last'], e['flow'], e['capacity']))


def print_na(na, na_num):
    """Print a auxiliar network"""

    logger.debug("Auxiliar Network: %d", na_num)
    for key in na:
        logger.debug("Node %s has neightbords: %s" % (str(key), str([v['id'] for v in na[key]])))


def print_path(path):
    """Print a path"""

    logger.debug("Path: %s Flow carried: %s" % 
                 (str([v['id'] for v in path['path']]), 
                  str(path['minflow'])))

