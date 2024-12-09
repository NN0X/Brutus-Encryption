#!/usr/bin/env python3

import hashlib
import numpy as np
import random
import string
import matplotlib.pyplot as plt
import math
import subprocess


def runAnalizerExec(word, key):
    output = subprocess.run(["./analizer", word, key], stdout=subprocess.PIPE)
    output = output.stdout.decode("utf-8").split("\n")
    pseudouniqueInt = int(output[0])
    charnums = list(map(int, output[1].split()))
    return pseudouniqueInt, charnums

def genRandomWord(length=8):
    return ''.join(random.choices(string.ascii_lowercase, k=length))

def main():
    MAX_ATTEMPTS = 10000000
    pseudouniqueValues = set()
    allPseudouniqueValues = []

    print("Press 'Ctrl + C' to stop and display the plot.\n")
    input("Press 'Enter' to start generating words...")
    try:
        allCharnums = []
        attempts = 1
        nonUnique = 0
        word = "hello"
        while True and attempts < MAX_ATTEMPTS + 1:
            key = genRandomWord()
            pseudouniqueValue, charnums = runAnalizerExec(word, key)
            if pseudouniqueValue not in pseudouniqueValues:
                print(f"attempt: {attempts} | unique: {key}")
                pseudouniqueValues.add(pseudouniqueValue)
            else:
                print(f"attempt: {attempts} | not unique: {key}")
                nonUnique += 1
            allPseudouniqueValues.append(pseudouniqueValue)
            allCharnums.append(charnums)
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

        plt.show()

if __name__ == "__main__":
    main()
