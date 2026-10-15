INF = 999

N = int(input("enter no. of routers: "))

def distance_vector_routing(cost):
    # distance matrix
    dist = [[0] * N for _ in range(N)]

    # nexthop matrix
    next_hop = [[-1] * N for _ in range(N)]

    for i in range(N):
        for j in range(N):
            dist[i][j] = cost[i][j]

            if i == j:
                next_hop[i][j] = i

            elif cost[i][j] != INF:
                next_hop[i][j] = j

            else:
                next_hop[i][j] = -1

    # distance vector updates
    while True:
        updated = False

        for i in range(N):
            for j in range(N):
                for k in range(N):

                    # check that both paths are reachable
                    if (dist[i][k] != INF and
                            dist[k][j] != INF):

                        new_cost = dist[i][k] + dist[k][j]

                        if dist[i][j] > new_cost:

                            dist[i][j] = new_cost
                            next_hop[i][j] = next_hop[i][k]

                            updated = True

        # stop when no changes occur
        if not updated:
            break

    return dist, next_hop


def display_routing_tables(dist, next_hop):
    for i in range(N):
        print(f"\nrouting table for router {chr(65 + i)}")
        print("-" * 35)
        print("Destination\tCost\tNext Hop")

        for j in range(N):

            destination = chr(65 + j)

            if dist[i][j] == INF:
                cost = "INF"
                hop = "-"
            else:
                cost = dist[i][j]
                hop = chr(65 + next_hop[i][j])

            print(f"{destination}\t\t{cost}\t{hop}")

def main():

    print("enter the cost matrix")
    print("use 999 for INF")
    cost = []

    for i in range(N):
        row = list(map(int, input(f"enter row {i + 1}: ").split()))
        cost.append(row)

    print("\ninitial cost matrix:")
    for row in cost:
        print(row)

    # apply dvr
    dist, next_hop = distance_vector_routing(cost)

    print("\nfinal routing tables:")
    display_routing_tables(dist, next_hop)
    print("\nshortest path query->")

    source = int(input("enter source router int input(0=A, 1=B, 2=C, 3=D): "))
    destination = int(input("enter destination router (0=A, 1=B, 2=C, 3=D): "))

    if dist[source][destination] == INF:
        print("destination is unreachable")

    else:
        print(
            f"\nmin cost from "
            f"{chr(65 + source)} to "
            f"{chr(65 + destination)} = "
            f"{dist[source][destination]}"
        )

        print(
            f"next hop = "
            f"{chr(65 + next_hop[source][destination])}"
        )

if __name__ == "__main__":
    main()