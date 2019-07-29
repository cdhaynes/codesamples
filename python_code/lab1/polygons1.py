#Casey Haynes
#Summer 2019

import turtle


user_input = input("Enter a positive integer: ")
length = int(user_input)
zoom = 0.005
separation = 20

turtle.tracer(True)

turtle.bgcolor('white')

turtle.penup()

height = turtle.window_height()
width = turtle.window_width()

turtle.goto(0, 0)

turtle.forward(-width / 2 * 0.95)

turtle.pendown()

for i in range(3):
	turtle.forward(length)
	turtle.left(120)
turtle.update()
################################################################
turtle.penup()

turtle.forward(125)

turtle.pendown()

for i in range(4):
	turtle.forward(length)
	turtle.left(90)
turtle.update()
###############################################################
turtle.penup()

turtle.forward(150)

turtle.pendown()

for i in range(5):
        turtle.forward(length)
        turtle.left(72)
turtle.update()
###############################################################
turtle.penup()

turtle.forward(200)

turtle.pendown()

for i in range(6):
        turtle.forward(length)
        turtle.left(60)
turtle.update()
###############################################################
turtle.penup()

turtle.forward(225)

turtle.pendown()

for i in range(7):
        turtle.forward(length)
        turtle.left(51.4285714)
turtle.update()
###############################################################

turtle.done()
