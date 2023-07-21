import os
import openai
import random

openai.api_key = os.getenv("OPENAI_API_KEY")

board = []

f = open(".wire", "r+")
for line in f:
    for s in line.split(' '):
        if (s != ''):
            board.append(int(s))

print(board)
player = 'X'
num = random.randint(0, 15)

if (num == 7):
    response = openai.ChatCompletion.create(
        model = 'gpt-3.5-turbo',
        messages = [
            {
            "role": "system", 
            "content": 
            "The user will give you the state of a tic-tac-toe board, \
            in the form of 9 numbers. The first three numbers represent the top row from left to right, the second three numbers represent the middle row \
            from left to right, and the last three numbers represent the bottom row from left to right. \
            1 represents an X, 0 represents a blank, -1 represents an O. The user will then tell you which player he or she is playing. \
            Creatively insult the user about how he or she is bad at tic-tac-toe."
            },

            {
                "role": "user",
              "content": str(board)
            },
            {
                "role": "user",
                "content": f"I am playing as: {player}"
            }
        ],
        temperature = 1
    )
    print("-1")
elif (num % 2 == 0 and num != 7):
    response = openai.ChatCompletion.create(
        model = 'gpt-3.5-turbo',
        messages = [
            {
            "role": "system", 
            "content": 
            "The user will give you the state of a tic-tac-toe board, \
            in the form of 9 numbers. The first three numbers represent the top row from left to right, the second three numbers represent the middle row \
            from left to right, and the last three numbers represent the bottom row from left to right. \
            1 represents an X, 0 represents a blank, -1 represents an O. The user will then tell you which player he or she is playing. \
            Give the user bad advice. Do not tell the user to play a spot that has already been played, or that you are giving bad advice."
            },

            {
                "role": "user",
              "content": str(board)
            },
            {
                "role": "user",
                "content": f"I am playing as: {player}"
            }
        ],
        temperature = 1
    )
    print("0")
else:
    response = openai.ChatCompletion.create(
        model = 'gpt-3.5-turbo',
        messages = [
            {
            "role": "system", 
            "content": 
            "The user will give you the state of a tic-tac-toe board, \
            in the form of 9 numbers. The first three numbers represent the top row from left to right, the second three numbers represent the middle row \
            from left to right, and the last three numbers represent the bottom row from left to right. \
            1 represents an X, 0 represents a blank, -1 represents an O. The user will then tell you which player he or she is playing. \
            Give the user unhelpful advice. Do not tell the user you are giving unhelpful advice."
            },

            {
                "role": "user",
              "content": str(board)
            },
            {
                "role": "user",
                "content": f"I am playing as: {player}"
            }
        ],
        temperature = 1
    )
    print("1")

print(response.choices[0].message.content)