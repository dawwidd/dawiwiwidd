import sys

if __name__ == '__main__':
    key = int(input("Key: "))
    n = int(input("n (p*q): "))
    encryptedMessageFilePath = input("Encrypted message file: ")

    encryptedMessageFile = open(encryptedMessageFilePath, 'r')

    numbers = encryptedMessageFile.read().split(' ')[:-1]

    message = ''
    for number in numbers:
        message += chr(int(number) ** key % n)

    messageFile = open(encryptedMessageFilePath+".dec", "w")
    messageFile.write(message)

    encryptedMessageFile.close()
    messageFile.close()