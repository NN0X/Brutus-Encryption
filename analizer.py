#!/usr/bin/env python3

import hashlib
import numpy as np
import random
import string
import matplotlib.pyplot as plt
import math

def f(x, a=2**60, b=0.004, c=0.5):
    return -(a * np.exp(-b * (x - 64)**2) + c * x)

def flip(f, line, axis='x'):
    if axis == 'x':
         return lambda x: f(2 * line - x)
    elif axis == 'y':
        return lambda x: 2 * line - f(x)
    else:
        raise ValueError("axis must be 'x' or 'y'")

def fFlip(x):
    return flip(f, 0, axis='y')(x)

def doubleToUInt64(value):
    value = int(value)
    return value & 0xFFFFFFFFFFFFFFFF

def addWithOverflow(a, b):
    a = int(a)
    b = int(b)
    return (a + b) & 0xFFFFFFFFFFFFFFFF

def multiplyWithOverflow(a, b):
    a = int(a)
    b = int(b)
    return (a * b) & 0xFFFFFFFFFFFFFFFF

def genPseudouniqueInteger(text):
    num = 0
    elements = []
    E = 2.71828182845904523536
    for i in range(len(text)):
        integerComponent = np.power(E, i) * np.sin(i) * np.cos(i) + fFlip(i) + np.sin(1 / (np.sqrt(i + 1)))
        integerComponent = doubleToUInt64(integerComponent)
        wordComponent = np.power(E, ord(text[i]))
        wordComponent = doubleToUInt64(wordComponent)
        elements.append(multiplyWithOverflow(wordComponent, integerComponent))
        #elements.append(ord(text[i]) * integerComponent)
        num = addWithOverflow(num, elements[-1])
    return num, elements

def hashString(string):
    hash = hashlib.sha512(string.encode()).hexdigest()
    return hash

def genRandomWord(length=8):
    return ''.join(random.choices(string.ascii_lowercase, k=length))

def main():
    pseudouniqueValues = set()
    allPseudouniqueValues = []

    print("Press 'Ctrl + C' to stop and display the plot.\n")

    try:
        elementsPerValue = []
        while True:
            word = genRandomWord()
            hashed = hashString(word)
            pseudouniqueValue, elems = genPseudouniqueInteger(hashed)
            elementsPerValue.append(elems)
            if pseudouniqueValue not in pseudouniqueValues:
                print(f"unique: {word}")
                pseudouniqueValues.add(pseudouniqueValue)
            else:
                print(f"not unique: {word}")
                input()
            allPseudouniqueValues.append(pseudouniqueValue)
    except KeyboardInterrupt:
        print("\nStopping word generation. Generating plot...")

        plt.figure(figsize=(12, 8))
        plt.scatter(range(len(allPseudouniqueValues)), allPseudouniqueValues, color='blue', alpha=0.5)
        plt.xlabel("Index of Generated Value")
        plt.ylabel("Pseudounique Integer Value")
        plt.title("Scatter Plot of Pseudounique Values")

        allPseudouniqueValues = np.array(allPseudouniqueValues)
        elementsPerValue = np.array(elementsPerValue)
        contributionsPerValue = []
        for i in range(len(elementsPerValue)):
            contributions = elementsPerValue[i] / allPseudouniqueValues[i]
            contributionsPerValue.append(contributions)
        contributionsPerValue = np.array(contributionsPerValue, dtype=np.float64)

        plt.figure(figsize=(12, 8))
        plt.scatter(range(len(contributionsPerValue[0])), np.mean(contributionsPerValue, axis=0), color='red', alpha=0.5)
        plt.xlabel("Index of Element")
        plt.ylabel("Average Contribution to Pseudounique Value")
        plt.title("Scatter Plot of Average Contribution of Elements to Pseudounique Values")

        plt.figure(figsize=(12, 8))
        plt.scatter(range(len(contributionsPerValue[0])), np.median(contributionsPerValue, axis=0), color='green', alpha=0.5)
        plt.xlabel("Index of Element")
        plt.ylabel("Median Contribution to Pseudounique Value")
        plt.title("Scatter Plot of Median Contribution of Elements to Pseudounique Values")

        plt.figure(figsize=(12, 8))
        plt.scatter(range(len(contributionsPerValue[0])), np.std(contributionsPerValue, axis=0), color='purple', alpha=0.5)
        plt.xlabel("Index of Element")
        plt.ylabel("Standard Deviation of Contribution to Pseudounique Value")
        plt.title("Scatter Plot of Standard Deviation of Contribution of Elements to Pseudounique Values")

        x = np.linspace(0, 128)
        y = fFlip(x)
        plt.figure(figsize=(12, 8))
        plt.plot(x, y, color='orange')
        plt.xlabel("x")
        plt.ylabel("f(x)")
        plt.title("Plot of f(x) = 100 * exp(-0.01 * (x - 25)^2) + 0.5 * x")

        # plot the process of adding elements to the pseudounique value for randomly selected 100 pseudounique values
        # use function addWithOverflow to add elements to the pseudounique value
        plt.figure(figsize=(12, 8))
        for i in range(10):
            randomIndex = random.randint(0, len(allPseudouniqueValues) - 1)
            pseudouniqueValue = allPseudouniqueValues[randomIndex]
            elements = elementsPerValue[randomIndex]
            cumulativeSum = []
            for j in range(len(elements)):
                pseudouniqueValue = addWithOverflow(pseudouniqueValue, elements[j])
                cumulativeSum.append(pseudouniqueValue)
            plt.plot(range(len(cumulativeSum)), cumulativeSum, label=f"Pseudounique Value {randomIndex}")
        plt.xlabel("Index of Element")
        plt.ylabel("Cumulative Sum of Elements")
        plt.title("Plot of Cumulative Sum of Elements for 10 Pseudounique Values")

        plt.show()

if __name__ == "__main__":
    main()
