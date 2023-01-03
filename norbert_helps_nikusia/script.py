from itertools import combinations


def main():
    heuristic_xd(get_vertices())
    # vertices = get_vertices()
    # stars = set()
    # for v, neighbours in vertices.items():
    #     res = get_star(v, vertices, neighbours)
    #     if res is not None:
    #         stars.add(res)
    # print(stars)


def get_star(verticle, all_vertices, neighbours) -> tuple | None:
    for c in combinations(neighbours, r=4):
        d = dict.fromkeys(c, 1)
        d[verticle] = 1
        for n in c:
            if n in all_vertices.keys():
                d[n] = d[n] + 1
                for nn in all_vertices[n]:
                    if nn in d.keys():
                        d[nn] = d[nn] + 1
        for times_present in d.values():
            if times_present != 5:
                return None
        return tuple(sorted(d.keys()))


def heuristic_xd(vertices: dict):
    while True:
        smallest_degree = len(vertices) - 1
        smallest_degree_verticle = -1
        smallest_degree_neighbours = None

        for v, neighbours in vertices.items():
            if len(neighbours) < smallest_degree:
                smallest_degree_verticle = v
                smallest_degree_neighbours = neighbours
                smallest_degree = len(neighbours)
        if smallest_degree == len(vertices) - 1:
            break
        elif smallest_degree_verticle != -1:
            del vertices[smallest_degree_verticle]
            for neighbour in smallest_degree_neighbours:
                vertices[neighbour].remove(smallest_degree_verticle)
    print(vertices)


def get_vertices() -> dict:
    res = {}
    with open("input.txt", "r") as f:
        for l in f.readlines():
            tmp = l.split('->')
            neighbours = list(
                map(lambda x: int(x.strip()), filter(lambda x: x != tmp[0], tmp[1].split())))
            if len(neighbours) >= 4:
                res[int(tmp[0])] = neighbours
    return res


if __name__ == "__main__":
    main()
