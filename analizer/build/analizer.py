#!/usr/bin/env python3

import hashlib
import numpy as np
import random
import string
import matplotlib.pyplot as plt
import math
import subprocess

def addWithOverflow(a, b):
    # run add executable with a and b as arguments
    # return the sum of a and b
    # output: sum (unsigned long long int)
    process = subprocess.Popen(["./add", str(a), str(b)], stdout=subprocess.PIPE)
    output = process.communicate()[0].decode().strip()
    return int(output)

def genPseudouniqueInteger(text):
    # run pseudounique executable with text as argument
    # return the pseudounique integer value and the number of elements in the text
    # output: pseudouniqueValue element1 element2 ... elementN (unsigned long long int)
    # example: 123 4 5 6 7
    process = subprocess.Popen(["./pseudouniq", text], stdout=subprocess.PIPE)
    output = process.communicate()[0].decode().strip()
    output = output.split()
    pseudouniqueValue = int(output[0])
    elements = [int(x) for x in output[1:]]
    return pseudouniqueValue, elements

def hashString(string):
    hash = hashlib.sha512(string.encode()).hexdigest()
    return hash

def genRandomWord(length=8):
    return ''.join(random.choices(string.ascii_lowercase, k=length))

def main():
    MAX_ATTEMPTS = 10000000
    pseudouniqueValues = set()
    allPseudouniqueValues = []

    print("Press 'Ctrl + C' to stop and display the plot.\n")
    input("Press 'Enter' to start generating words...")
    try:
        elementsPerValue = []
        attempts = 1
        nonUnique = 0
        while True and attempts < MAX_ATTEMPTS + 1:
            word = genRandomWord()
            hashed = hashString(word)
            pseudouniqueValue, elems = genPseudouniqueInteger(hashed)
            elementsPerValue.append(elems)
            if pseudouniqueValue not in pseudouniqueValues:
                print(f"attempt: {attempts} | unique: {word}")
                pseudouniqueValues.add(pseudouniqueValue)
            else:
                print(f"attempt: {attempts} | not unique: {word}")
                nonUnique += 1
            allPseudouniqueValues.append(pseudouniqueValue)
            attempts += 1
        if attempts == MAX_ATTEMPTS + 1:
            raise KeyboardInterrupt
    except KeyboardInterrupt:
        print(f"\nUnique values generated: {len(pseudouniqueValues)}")
        print(f"Non-unique values generated: {nonUnique}")

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

        probe = 20
        plt.figure(figsize=(12, 8))
        for i in range(probe):
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
        plt.title(f"Plot of Cumulative Sum of Elements for {probe} Pseudounique Values")

        plt.show()

if __name__ == "__main__":
    main()
