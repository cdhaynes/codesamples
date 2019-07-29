#Casey Haynes
#Summer 2019

import turtle

user_input = input("Enter an angle in degrees: ")
angle = float(user_input)
user_input = input("Enter initial length: ")
length = float(user_input)
user_input = input("Enter iterative delta: ")
delta = float(user_input)
user_input = input("Enter number of iterations: ")
num = int(user_input)
pathbool = input("Do you want to see it being drawn? (Y/n): ")
turtle.speed('fastest') #Change speed of drawing

if pathbool == "Y" or pathbool == "y":
	turtle.tracer(True)
elif pathbool == "N" or pathbool == "n":
	turtle.tracer(False)
else:
	turtle.tracer(True) #switch boolean value to see it draw
turtle.penup()

width = (turtle.window_width() / 2) * 0.1
height = (turtle.window_height() / 2) * 0.1

#turtle.goto(width, height)

turtle.pendown()

turtle.left(angle)

for i in range(num):
	turtle.forward(length)
	turtle.left(angle)
	length = length + delta
turtle.update()
turtle.done()
