import re

FAQ_PAIRS = [
    {
        "keywords": {"open", "account"},
        "answer": "You can open a new account online via our website or by visiting the nearest branch with valid ID proof."
    },
    {
        "keywords": {"close", "account"},
        "answer": "To close your account, please visit your home branch with your ID proof, or contact customer support."
    },
    {
        "keywords": {"lost", "card"},
        "answer": "If you’ve lost your card, please block it immediately using our mobile app or call our 24x7 helpline: 1800-XXX-XXXX."
    },
    {
        "keywords": {"reset", "pin"},
        "answer": "You can reset your card PIN from our mobile banking app under ‘Card Services’ → ‘Reset PIN’."
    },
    {
        "keywords": {"loan", "interest", "rate"},
        "answer": "Our loan interest rates vary by product. Please visit the ‘Loans’ section on our website or contact support for exact rates."
    },
    {
        "keywords": {"balance", "check"},
        "answer": "You can check your balance using our mobile app, internet banking, or by sending an SMS ‘BAL’ to 9XXXXXXXXX."
    },
]


def preprocess(text: str) -> set:
    """Lowercase + simple tokenization, returns set of words."""
    tokens = re.findall(r"\w+", text.lower())
    return set(tokens)


def find_best_answer(user_query: str) -> str:
    """Match user query to FAQ_PAIRS using keyword overlap."""
    user_tokens = preprocess(user_query)

    best_score = 0
    best_answer = None

    for item in FAQ_PAIRS:
        kws = item["keywords"]
        score = len(user_tokens & kws)  # overlap count

        if score > best_score:
            best_score = score
            best_answer = item["answer"]

    if best_score == 0 or best_answer is None:
        return ("Sorry, I couldn't understand your query clearly. "
                "Please contact customer care or rephrase your question.")

    return best_answer


def run_chatbot():
    print("Bank Support Bot 🤖 (type 'exit' to quit)")
    while True:
        user_input = input("\nYou: ")

        if user_input.strip().lower() in {"exit", "quit", "q"}:
            print("Bot: Thank you for banking with us. Goodbye! 👋")
            break

        response = find_best_answer(user_input)
        print("Bot:", response)


if __name__ == "__main__":
    run_chatbot()