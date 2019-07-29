#Casey Haynes
#Summer 2019

def main():
	import turtle

	turtles = []
	first = turtle.Turtle()
	first.speed(0)
	turtles.append(first)

	second = turtle.Turtle()
	second.speed(0)
	second.right(90)
	turtles.append(second)

	third = turtle.Turtle()
	third.speed(0)
	third.right(180)
	turtles.append(third)

	fourth = turtle.Turtle()
	fourth.speed(0)
	fourth.right(270)
	turtles.append(fourth)

	for i in range(200):
		for turt in turtles:
			turt.forward(i/5)
			turt.left(10)
	turtle.done()

if __name__ == "__main__":
	main()
