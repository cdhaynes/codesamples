#Casey Haynes
#Summer 2019

sum = 0
count = 0
running_average = 0
for i in range(10):
	user_input = input("Enter a float: ")
	input_float = float(user_input)
	count = count + 1
	sum = input_float + sum
	running_average = sum / count

	print(running_average)
