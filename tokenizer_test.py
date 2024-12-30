from transformers import AutoTokenizer


def run():
    tokenizer = AutoTokenizer.from_pretrained("meta-llama/Meta-Llama-3-8B")
    string = "CONTEXT: You are a test agent"
    tokens = tokenizer.tokenize(string)
    print(tokens)


if __name__ == "__main__":
    run()