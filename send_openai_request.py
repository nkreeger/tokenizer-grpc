from openai import OpenAI


def run():
    client = OpenAI(api_key="asdf", base_url="http://127.0.0.1:8000")
    print(client)

    chat_completion = client.chat.completions.create(
        messages=[
            {
                "role": "user",
                "content": "Say this is a test",
            }
        ],
        model="llama3",
    )
    print(chat_completion)


if __name__ == "__main__":
    run()
