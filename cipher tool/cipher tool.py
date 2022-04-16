import random

#This script was made when one of my friends created a cipher and challenged me to crack it.
#While cracking the cipher, I made this script to encode and decode it. It was also helpful
#during the process of cracking it to have python handy, because its string manipulation capabilities
#are very versatile and assist in brute-forcing possible encodings.
#The format is as follows: "hello (there) world!" encodes to the numeric equivalent of "htw-ello(-here)-orld"

while True:
    #Take the first letter of user input to distinguish their choice
    choice = input("1. Enter E to encode, D to decode, and Q to quit: ")[0]
    if choice.upper() == "E":
        #Encode

        initial_text = input("2. You selected encoding. Input text: ")
        print("Encoding...")
        cipherText = ""
        #Prepare text for encoding
        initial_text = initial_text.lower()
        for char in initial_text:
            if char not in "abcdefghijklmnopqrstuvwxyz=,.():; ":
                print("Warning: character '" + char + "' will be ignored, only alphabetical characters and the following symbols are allowed: =,.():;")
                #Remove garbage characters
                initial_text = initial_text.replace(char, '')
        #Create space around symbols so they will be split into unique 'words'
        for char in '=,.():;':
            initial_text = initial_text.replace(char, ' ' + char + ' ')
        text_a = initial_text.split()
        text = ""

        code = "_zyxwvutsrqponmlkjihgfedcba"
        code_dot = "_yxwvutsrqponmlkjihgfedcbaz"

        #Symbols stay in the second group of characters, so they are a special case
        #Otherwise, append the first letter of each word to the first group, and the bodies
        #of each word to the second group.
        text = ''.join([word[0] for word in text_a if word not in '=,.():;'])
        text += ''.join([word[0] if word in '=,.():;' else '-' + word[1:] for word in text_a])
        print("Partially encoded ciphertext: " + text)

        for char in text:
            if char.isalpha():
                
                i = random.randint(1, 100)
                append_dot = (i % 2 == 0)

                if append_dot:
                    numeral = str(code_dot.index(char))
                else:
                    numeral = str(code.index(char))
                
                cipherText += str(numeral)
                if append_dot:
                    cipherText = cipherText + "•"
                cipherText += " "

            elif char in '-=,.():;':
                cipherText = cipherText.rstrip() #Remove the trailing space
                cipherText += char

        print("Fully encoded ciphertext: " + cipherText)

    elif choice.upper() == "D":
        #Decode

        initial_text = input("2. You selected decoding. Input cipher text: ")
        print("Decoding...")
        cipherText = ""
        
        #Prepare text for decoding
        for char in '-=,.():;':
            initial_text = initial_text.replace(char, ' ' + char + ' ')
        text_a = initial_text.split()
        try:
            for char in initial_text:
                if char not in "1234567890•-=,.():; \n":
                    raise ValueError
        except:
            print("Error: invalid ciphertext entered. Must contain only numeric digits, the symbols •-=,.():; and at least one hyphen.")
            continue
        code = "_zyxwvutsrqponmlkjihgfedcba"
        code_dot = "_yxwvutsrqponmlkjihgfedcbaz"

        #Decode ciphertext
        for token in text_a:
            if token not in '-=,.():;\n':
                if token.endswith("•"):
                    token = token[0:-1]
                    cipherText += code_dot[abs(int(token))]
                else:
                    cipherText += code[abs(int(token))]
            elif token in '-=,.():;\n':
                cipherText += token
                
        print("Partially decoded ciphertext: " + cipherText)
        #Fully decode text by pairing each letter in first group with word from second
        scrambledText = cipherText.split("-")
        print("Fully decoded ciphertext: ", end='')
        i = 0
        for word in scrambledText[1:]:
            print(''.join(scrambledText[0][i] + word), end=' ')
            i = i + 1
        print("")
    elif choice.upper() == 'Q':
        break
    else:
        print("Please enter only either E, D or Q.")
