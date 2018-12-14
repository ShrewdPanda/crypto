#!/usr/bin/python

import os
import sys
import hashlib

BUF_SIZE = 65536
sha = hashlib.sha512()


def checks(count, values, combo_count, combvals, root_count, rootvals, stdout):
    
    while count < len(sys.argv):
        load(sys.argv[count], count, stdout)
        values.append(sha.hexdigest())
    
        if count >= 2 and count % 2 == 0:
            combo(values, combo_count, combvals, stdout)
            combo_count += 1
        count += 1

        if combo_count >= 2 and combo_count % 2 == 0:
            root(root_count, combvals, rootvals, stdout)


def load(_file_, count, stdout):
    
    sigfile = sys.argv[count] + '_hash'
    if not os.path.exists(sigfile):
        update(_file_, sigfile, count, stdout)
    

def update(_file_, sigfile, count, stdout): 
    
    sig = open('{0}'.format(sigfile), 'w+')
    with open(_file_, 'rb') as f:
        while True:
            data = f.read(BUF_SIZE)
            if not data:
                break
            sha.update(data)
    sys.stdout = sig
    print("{0} :: {1}".format(unicode(sys.argv[count]), sha.hexdigest()))
    sys.stdout = stdout


def combo(values, combo_count, combvals, stdout):
    
    combo_file = open('combo{0}'.format(combo_count + 1), 'w+')
    combined = values[combo_count] + values[combo_count + 1]
    sha.update(combined)
    
    sys.stdout = combo_file
    print("{0} :: {1}".format(unicode("combo", 'utf-8'), sha.hexdigest()))
    combvals.append(sha.hexdigest())
    sys.stdout = stdout


def root(root_count, combvals, rootvals, stdout):
    
    root_file = open('root{0}'.format(root_count + 1), 'w+')
    rooted = combvals[root_count] + combvals[root_count]
    sha.update(rooted)

    sys.stdout = root_file
    print("{0} :: {1}".format(unicode("root", 'utf-8'), sha.hexdigest()))
    rootvals.append(sha.hexdigest())
    sys.stdout = stdout


def prompt(values, combvals, rootvals):
    
    print("Hello! Welcome to the document hashing software")
    print("Would you like to:")
    print("(p) Print all existing hashes")
    
    choice = input()

    if choice == "p":
        display(values, combvals, rootvals)
    if choice == 'u':
        print 'Hello!'

def display(values, combvals, rootvals):
    
    print("\n{0} :: {1}\n".format(unicode("root", 'utf-8'), rootvals))
    print("{0} :: {1}\n".format(unicode("combo", 'utf-8'), combvals))
    print("{0} :: {1}\n".format(unicode("nodes", 'utf-8'), values))


def main():

    values = []
    combvals = []
    rootvals = []

    count = 1
    combo_count = 0
    root_count = 0

    stdout = sys.stdout

    checks(count, values, combo_count, combvals, root_count, rootvals, stdout) 
    prompt(values, combvals, rootvals)


if __name__ == '__main__':
    main()
