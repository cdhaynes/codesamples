#Casey Haynes
#Summer 2019
import turtle

def constant(direction, angle):
    turtle.tracer(True)
    turtle.pendown()
    if direction == "right":
        turtle.right(float(angle))
    elif direction == "left":
        turtle.left(float(angle))
    turtle.forward(50)
    turtle.update()


def main():
    u_in = ""
    InputList = []
    while u_in != "stop":
        u_in = input("Entry: ")
        InputList.append(u_in)
    InputList.pop(-1) #Fencepost: Get rid of last "stop" in list
    for index, string in enumerate(InputList):
        if string == "left" or string == "right":
            constant(string, InputList[index + 1])
            InputList.pop(index + 1)
            turtle.update()
        else:
            constant(string, 0)
            turtle.update()
    turtle.done()
    print(InputList)

if __name__ == "__main__":
    main()
