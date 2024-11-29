#!/usr/bin/env python3

import hashlib
import numpy as np
import random
import string
import matplotlib.pyplot as plt

def f(x, a=2**60, b=0.004, c=0.5):
    return -(a * np.exp(-b * (x - 64)**2) + c * x)

def doubleToUInt64(value):
    return np.uint64(value)

def genPseudouniqueInteger(text):
    num = 0
    elements = []
    E = 2.71828182845904523536
    for i in range(len(text)):
        integerComponent = np.power(E, i) * np.sin(i) * np.cos(i) + f(i) * np.sinh(i)
        integerComponent = doubleToUInt64(integerComponent)
        elements.append(ord(text[i]) * integerComponent)
        num += elements[i]
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
        y = f(x)
        plt.figure(figsize=(12, 8))
        plt.plot(x, y, color='black')
        plt.xlabel("x")
        plt.ylabel("f(x)")
        plt.title("Plot of f(x) = 100 * exp(-0.01 * (x - 25)^2) + 0.5 * x")

        plt.show()

if __name__ == "__main__":
    main()
