def compareCoin(purse):
    if purse[0] == purse[len(purse)-1]:
        purse.pop(len(purse)-1)
        compareCoin(purse)
    else:
        fakeCoin = purse[0]
        if purse[0] < purse[len(purse)-1]:
            fakeCoin = purse[len(purse)-1]
        print("COIN NUMBER", purse.index(fakeCoin)+1, "IS FRAUDULENT")
        return

def main():
    purse = [2, 1, 1, 1, 1, 1]
    compareCoin(purse)
    return 0

main()
