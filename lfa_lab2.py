f = open("date.in", "r");
words = set()
states = {}
validation = True
invMessage = ""


def line():
    linie = f.readline()
    linie = linie.strip()
    linie = linie.replace(" ", "")
    return linie


def readwords():
    global validation
    global invMessage
    linie = line()
    while linie != "End" and linie != "":
        if linie[0] == '#':
            linie = line()
            continue
        words.add(linie)
        linie = line();


def readstates():
    global startState
    global validation
    global invMessage
    startState = ""
    linie = line()
    while linie != "End" and linie != "":
        if linie[0] == '#':
            linie = line()
            continue
        v = linie.split(',')
        start = final = False
        if len(v) > 1:
            if v[1] == "S":
                start = True
            else:
                final = True
            if len(v) > 2:
                if v[2] == "S":
                    start = True
                else:
                    final = True
        states[v[0]] = (start, final, {} );
        if start == True:
            if startState == "":
                startState = v[0]
            else:
                validation = False
                invMessage = "Two or more start states!"
                break
        linie = line()

def readtransitions():
    global validation
    global invMessage
    linie = line()
    while linie != "End" and linie != "":
        if linie[0] == '#':
            linie = line()
            continue
        v = linie.split(",")
        if v[0] not in states or v[2] not in states or v[1] not in words:
            validation = False
            if v[0] not in states:
                invMessage = v[0] + " is not a valid state!"
                cuv = input()
            else:
                if v[2] not in states:
                    invMessage = v[2] + " is not a valid state!"
                else:
                    invMessage = v[1] + " is not a valid word!"
            break
        tr = states[v[0]][2]
        if v[1] in tr:
            validate = False
            invMessage = "Input is not a DFA!"
        tr[v[1]] = v[2]
        linie = line()


def isAccepted(str):
    currentState = startState
    n = len(str)
    for i in range(n):
        transitions = states[ currentState ][2]
        if str[i] in transitions:
            currentState = transitions[ str[i] ]
        else:
            return False
    return states[ currentState ][1]

linie = line()
while linie != "" and validation:
    linie = line()
    if linie[0] == '#':
        linie = line()
        continue
    if linie == "Sigma:":
        readwords()
    if linie == "States:":
        readstates()
    if linie == "Transitions:":
        readtransitions()
    linie = f.readline();

if validation == True:
    print("Input is a DFA")
    while True:
        str = input()
        if str == "":
            break
        if isAccepted(str) == True:
            print("accept")
        else:
            print("reject")
else:
    print("Invalid input. " + invMessage)