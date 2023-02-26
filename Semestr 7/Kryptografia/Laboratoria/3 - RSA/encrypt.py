import sys

if __name__ == '__main__':
    key = int(input("Key: "))
    n = int(input("n (p*q): "))
    messageFilePath = input("Message file: ")

    messageFile = open(messageFilePath, 'r')

    content = messageFile.read()

    encryptedContent = ''
    for letter in content:
        encryptedContent += str(ord(letter) ** key % n) + " "

    encryptedMessageFile = open(messageFilePath+".rsa", "w")
    encryptedMessageFile.write(encryptedContent)

    messageFile.close()
    encryptedMessageFile.close()
