from sys import maxsize


def getPath(currNode: int, toNode: int, graph: list, nodePriority: list, graphUsed: list, visitedNodes: list,
            path: list):
    if currNode == toNode:
        path.append(currNode)
        return True

    nodeNum = len(graph)

    nextNodes = []
    for nodeIndex in range(nodeNum):
        if not visitedNodes[nodeIndex] and (
                (graph[currNode][nodeIndex] - graphUsed[currNode][nodeIndex]) != 0 or graphUsed[nodeIndex][
            currNode] != 0):
            nextNodes.append(nodeIndex)
            visitedNodes[nodeIndex] = True

    nextNodes = sorted(nextNodes, key=lambda x: nodePriority[x])

    for nodeIndex in nextNodes:
        if getPath(nodeIndex, toNode, graph, nodePriority, graphUsed, visitedNodes, path):
            path.append(currNode)
            return True

    for nodeIndex in nextNodes:
        visitedNodes[nodeIndex] = False

    return False


def applyPath(pIndex: int, maxFlow: int, path: list, graph: list, graphUsed: list):
    if pIndex != len(path) - 1:
        if graph[path[pIndex]][path[pIndex + 1]] - graphUsed[path[pIndex]][path[pIndex + 1]] != 0:
            maxFlow = applyPath(
                pIndex + 1,
                min(maxFlow, graph[path[pIndex]][path[pIndex + 1]] - graphUsed[path[pIndex]][path[pIndex + 1]]),
                path,
                graph,
                graphUsed
            )
            graphUsed[path[pIndex]][path[pIndex + 1]] += maxFlow
        else:
            maxFlow = applyPath(
                pIndex + 1,
                min(maxFlow, graphUsed[path[pIndex + 1]][path[pIndex]]),
                path,
                graph,
                graphUsed
            )
            graphUsed[path[pIndex + 1]][path[pIndex]] -= maxFlow
    return maxFlow


def dinic(fromNode: int, toNode: int, graph: list, nodePriority: list, nodeNames: list):
    n = len(graph)

    graphUsed = []
    for i in range(n):
        graphUsed.append([0] * n)

    deltaSum = 0
    while True:
        path = []
        visitedNodes = [False] * n
        visitedNodes[fromNode] = True
        if getPath(fromNode, toNode, graph, nodePriority, graphUsed, [False] * n, path):
            path.reverse()
            delta = applyPath(0, maxsize, path, graph, graphUsed)

            # print section [can be safely removed]
            print('Path: {}, delta = {}'.format([nodeNames[n] for n in path], delta))
            # end: print section

            deltaSum += delta
        else:
            return deltaSum


myNodeNames = ['s', '1', '2', '3', '4', 't']
#             s  1  2  3  4  t
myPriority = [0, 1, 2, 3, 4, -1]
myGraph = [
# fr:s  1  2  3  4  t      to
    [0, 10, 10, 0, 0, 0],  # s
    [10, 0, 2, 4, 8, 0],  # 1
    [10, 2, 0, 0, 9, 0],  # 2
    [0, 4, 0, 0, 6, 10],  # 3
    [0, 8, 9, 6, 0, 10],  # 4
    [0, 0, 0, 10, 10, 0]   # t

# # fr:s  1  2  3  4  t      to
#     [0, 0, 0, 0, 0, 0],  # s
#     [0, 0, 0, 0, 0, 0],  # 1
#     [0, 0, 0, 0, 0, 0],  # 2
#     [0, 0, 0, 0, 0, 0],  # 3
#     [0, 0, 0, 0, 0, 0],  # 4
#     [0, 0, 0, 0, 0, 0]   # t
]

myDeltaSum = dinic(0, len(myGraph) - 1, myGraph, myPriority, myNodeNames)
print('Max flow is {}'.format(myDeltaSum))