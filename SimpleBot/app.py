import streamlit as st
from google import genai
from google.genai import types

# --- Initialize Gemini client ---
client = genai.Client(api_key="###")
MODEL = "gemini-2.5-flash"


def generate_reply(user_message: str, history: list[dict]):
    contents = []

    # Convert history to valid roles for Gemini (user/model)
    for turn in history:
        role = "user" if turn["role"] == "user" else "model"
        contents.append(
            types.Content(
                role=role,
                parts=[types.Part(text=turn["text"])]
            )
        )

    # Add current user message
    contents.append(
        types.Content(
            role="user",
            parts=[types.Part(text=user_message)]
        )
    )

    # Generate response
    response = client.models.generate_content(model=MODEL, contents=contents)

    reply_text = response.candidates[0].content.parts[0].text
    return reply_text


def main():
    st.set_page_config(page_title="Chatbot")

    if "history" not in st.session_state:
        st.session_state.history = []

    st.title("Chatbot")

    user_input = st.text_input("You:")

    if user_input:
        # Store user message
        st.session_state.history.append({"role": "user", "text": user_input})

        # Generate bot reply
        reply = generate_reply(user_input, st.session_state.history)

        # Store model reply with correct role
        st.session_state.history.append({"role": "model", "text": reply})

        st.write(f"Bot: {reply}")

    # Show chat history
    st.write("---")
    for turn in st.session_state.history:
        if turn["role"] == "user":
            st.write(f"You: {turn['text']}")
        else:
            st.write(f"Bot: {turn['text']}")


if __name__ == "__main__":
    main()


#how to run
#pip install -r requirements.txt
#streamlit run app.py
