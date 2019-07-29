import turtle

#program inputs
print('Welcome to the Radically-Precise, Pre-17th Century Planetarium!')
zoom = 0.005 #input('How far to zoom in?')
separation = 20 #input('How far apart should the planets be drawn?')

turtle.tracer(False)

#Screen and turtle colors
turtle.bgcolor('black')

#Do not draw the turtle's path
turtle.penup()

#Get window size
height = turtle.window_height()
width = turtle.window_width()

#Draw (2 * decoration) ** 2 stars
decoration = 15
scale = max(height, width)
for col in range(-decoration, decoration):
	for row in range(-decoration, decoration):
		#row / decoration gives a number between -1 and 1
		#the 'scale' variable determines the space between stars
		y = row / decoration * scale
		#shift every other row of stars by 50%
		x = col + 0.5 * (row % 2)
		x = x / decoration * scale

		turtle.goto(x, y)

		#make every other star's radius larger
		turtle.dot(1 + col % 2, 'white')

#Go back to the center of the window
turtle.goto(0, 0)

#Move close to the edge
turtle.forward(-width / 2 * 0.9)

#Draw Mercury
turtle.dot(2 * 2439.7 * zoom, "gray")
turtle.forward((2439.7 + 6051.8) * zoom + separation)

#Draw Venus
turtle.dot(2 * 6051.8 * zoom, "tan")
turtle.forward((6051.8 + 6371.0) * zoom + separation)

# Draw Earth
turtle.dot(2 * 6371.0 * zoom, "blue")
turtle.forward((6371.0 + 3389.5) * zoom + separation)

# Draw Mars
turtle.dot(2 * 3389.5 * zoom, "red")
turtle.forward((3389.5 + 69911) * zoom + separation)

# Draw Jupiter
turtle.dot(2 * 69911 * zoom, "orange")
turtle.forward((69911 + 58232) * zoom + separation)

# Draw Saturn
turtle.dot(2 * 58232 * zoom, "tan3")
turtle.forward(58232 * zoom + separation)

turtle.done()
