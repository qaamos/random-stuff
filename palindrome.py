def checkPalindrome(word):
    i = 0
    for letter in word:
        if letter == word[len(word)-i-1]:
            ++i
        else:
            print(word, "is not a palindrome.")
            return
        print(word, "is a palindrome.")
        return


def main():
    word = input("Please enter a word: ")
    checkPalindrome(word)
    return 0

main()
