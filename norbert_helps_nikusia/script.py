from itertools import combinations


def main():
    vertices = get_vertices()
    stars = set()
    for v, neighbours in vertices.items():
        res = get_star(v, vertices, neighbours)
        if res is not None:
            stars.add(res)
            break

    for idx, star in enumerate(stars):
        print(f"{idx}: {star}")


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
