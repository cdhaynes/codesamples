#Casey Haynes
#Summer 2019

def max(elements):
    max = null
    for element in elements:
        if element > max:
            max = element
    return max

def min(elements):
    min = null
    for element in elements:
        if element < min:
            min = element
    return min

def sum(elements):
    sum = 0
    for element in elements:
        sum += element
    return sum

def odds(elements):
    for index, element in enumerate(elements):
        if element % 2 == 0:
            elements.pop(index)
    return elements

def evens(elements):
    for index, element in enumerate(elements):
        if element % 2 == 1:
            elements.pop(index)
    return elements

def every_other(elements):
    i = 0
    resultant = []
    while i < len(elements):
        resultant.append(elements[i])
        i += 2
    return resultant

def every_other_odd(elements):
    resultant = []
    elements = every_other(elements)
    for index, element in enumerate(elements):
        if element % 2 == 1:
            resultant.append(element)
    return resultant

def every_other_even(elements):
    resultant = []
    elements = every_other(elements)
    for index, element in enumerate(elements):
        if element % 2 == 0:
            resultant.append(element)
    return resultant
