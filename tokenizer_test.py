from transformers import AutoTokenizer

import grpc
import tokenizer_pb2
import tokenizer_pb2_grpc


def run():
    tokenizer = AutoTokenizer.from_pretrained("meta-llama/Meta-Llama-3-8B")
    string = "CONTEXT: You are a test agent"
    tokens = tokenizer.tokenize(string)

    with grpc.insecure_channel("localhost:50051") as channel:
        stub = tokenizer_pb2_grpc.TokenizerStub(channel)

        request = tokenizer_pb2.TokenRequest()
        for token in tokens: 
            request.tokens.append(token)

        response = stub.SendTokens(request)
        print("Tokenizer client received: " + response.message)


if __name__ == "__main__":
    run()