with open("input.txt", 'r') as file:
    lines = file.readlines()
    cals = []
    cal = 0
    for line in lines:
        if line != "\n":
            try:
                cal += int(line)
            except Exception:
                print(lines.index(line))
                print(Exception)
        else:
            cals += [cal]
            cal = 0

    print(max(cals))
