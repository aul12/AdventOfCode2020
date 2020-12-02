def get_policy(text):
    minNum, rest = text.split("-")
    maxNum, letter = rest.split(" ")
    return int(minNum), int(maxNum), letter[0]

if __name__ == "__main__":
    f = open("input", "r")
    
    line = f.readline()
    passCountOld = 0
    passCountNew = 0
    while line:
        policyStr, password = line.split(": ")
        minNum, maxNum, letter = get_policy(policyStr)
        count = 0
        
        for c in password:
            if c == letter:
                count += 1
        if minNum <= count <= maxNum:
            passCountOld += 1

        if (password[minNum-1] == letter) != (password[maxNum-1] == letter):
            passCountNew += 1

        line = f.readline()

    print("Old: %d" % passCountOld)
    print("New: %d" % passCountNew)
        
